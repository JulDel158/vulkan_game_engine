#include "first_app.hpp"

#include "ve_buffer.hpp"
#include "ve_camera.hpp"
#include "keyboard_movement_controller.hpp"
#include "simple_render_system.hpp"
#include "point_light_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <chrono>
#include <stdexcept>

namespace ve {

    struct GlobalUbo {
        glm::mat4 projection{ 1.f };
        glm::mat4 view{ 1.f };
        glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, 0.02f };
        glm::vec3 pLightPosition{ -1.f };
        alignas(16) glm::vec4 pLightColor{ 1.f }; // w is light intensity
    };

	FirstApp::FirstApp() {
        globalPool = ve_descriptor_pool::Builder(veDevice)
            .setMaxSets(ve_swap_chain::MAX_FRAMES_IN_FLIGHT)
            .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, ve_swap_chain::MAX_FRAMES_IN_FLIGHT)
            .build();
		loadGameObjects();
	}

	FirstApp::~FirstApp() {}

	void FirstApp::run() {

        std::vector<std::unique_ptr<ve_buffer>> uboBuffers(ve_swap_chain::MAX_FRAMES_IN_FLIGHT);

        for (int i = 0; i < uboBuffers.size(); ++i) {
            uboBuffers[i] = std::make_unique<ve_buffer>(
                veDevice,
                sizeof(GlobalUbo),
                1,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            uboBuffers[i]->map();
        }

        auto globalSetLayout = ve_descriptor_set_layout::Builder(veDevice)
            .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
            .build();

        std::vector<VkDescriptorSet> globalDescriptorSets(ve_swap_chain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < globalDescriptorSets.size(); ++i) {
            auto bufferInfo = uboBuffers[i]->descriptorInfo();
            ve_descriptor_writer(*globalSetLayout, *globalPool)
                .writeBuffer(0, &bufferInfo)
                .build(globalDescriptorSets[i]);

        }

		simple_render_system simpleRenderSystem{ 
            veDevice, 
            veRenderer.getSwapChainRenderPass(), 
            globalSetLayout->getDescriptorSetLayout()  };
        point_light_system pointLightSystem{
            veDevice,
            veRenderer.getSwapChainRenderPass(),
            globalSetLayout->getDescriptorSetLayout() };

        ve_camera camera{};
        camera.setViewTarget(glm::vec3(-1.f, -2.f, 2.f), glm::vec3(0.f, 0.f, 2.5f));

        auto viewerObject = ve_game_object::createGameObject();
        viewerObject.transform.translation.z = -2.5f;
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

		while (!veWindow.shouldClose()) {
			glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, 
                std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            cameraController.moveInPlaneXZ(veWindow.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = veRenderer.getAspectRatio();

            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.f);
			
			if (auto commandBuffer = veRenderer.beginFrame()) {
                int frameIndex = veRenderer.getFraneIndex();
                frame_info frameInfo{
                    frameIndex,
                    frameTime,
                    commandBuffer,
                    camera,
                    globalDescriptorSets[frameIndex],
                    gameObjects
                };

                // update
                GlobalUbo ubo{};
                ubo.projection = camera.getProjection();
                ubo.view = camera.getView();
                uboBuffers[frameIndex]->writeToBuffer(&ubo);
                uboBuffers[frameIndex]->flush();

                // render
				veRenderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(frameInfo);
                pointLightSystem.render(frameInfo);
				veRenderer.endSwapChainRenderPass(commandBuffer);
				veRenderer.endFrame();
			}

		}

		vkDeviceWaitIdle(veDevice.device());
	}

	void FirstApp::loadGameObjects() {
        std::shared_ptr<ve_model> veModel = ve_model::createModelFromFile(veDevice, "../assets/models/flat_vase.obj");

        auto flatVase = ve_game_object::createGameObject();
        flatVase.model = veModel;
        flatVase.transform.translation = { -1.f, 0.5f, 0.f };
        flatVase.transform.scale = { 5.f, 3.f, 3.f };
        gameObjects.emplace(flatVase.getId(), std::move(flatVase));

        veModel = ve_model::createModelFromFile(veDevice, "../assets/models/smooth_vase.obj");
        auto smoothVase = ve_game_object::createGameObject();
        smoothVase.model = veModel;
        smoothVase.transform.translation = { 0.5f, 0.5f, 0.f };
        smoothVase.transform.scale = { 5.f, 3.f, 3.f };
        gameObjects.emplace(smoothVase.getId(), std::move(smoothVase));

        veModel = ve_model::createModelFromFile(veDevice, "../assets/models/quad.obj");
        auto floor = ve_game_object::createGameObject();
        floor.model = veModel;
        floor.transform.translation = { 0.f, 0.5f, 0.f };
        floor.transform.scale = { 5.f, 1.f, 5.f };
        gameObjects.emplace(floor.getId(), std::move(floor));
	}

} // namespace ve