#include "../hpp/first_app.hpp"

#include "../hpp/ve_camera.hpp"
#include "../hpp/keyboard_movement_controller.hpp"
#include "../hpp/simple_render_system.hpp"

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

	FirstApp::FirstApp() {
		loadGameObjects();
	}

	FirstApp::~FirstApp() {}

	void FirstApp::run() {
		simple_render_system simpleRenderSystem{ veDevice, veRenderer.getSwapChainRenderPass() };
        ve_camera camera{};
        //camera.setViewDirection(glm::vec3(0.f), glm::vec3(0.5f, 0.f, 1.f));
        camera.setViewTarget(glm::vec3(-1.f, -2.f, 2.f), glm::vec3(0.f, 0.f, 2.5f));

        auto viewerObject = ve_game_object::createGameObject();
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

            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 10.f);
			
			if (auto commandBuffer = veRenderer.beginFrame()) {
				veRenderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
				veRenderer.endSwapChainRenderPass(commandBuffer);
				veRenderer.endFrame();
			}

		}

		vkDeviceWaitIdle(veDevice.device());
	}

	void FirstApp::loadGameObjects() {
        std::shared_ptr<ve_model> veModel = ve_model::createModelFromFile(veDevice, "assets/flat_vase.obj");

        auto flatBase = ve_game_object::createGameObject();
        flatBase.model = veModel;
        flatBase.transform.translation = { -1.f, 0.5f, 2.5f };
        flatBase.transform.scale = { 5.f, 3.f, 3.f };
        gameObjects.push_back(std::move(flatBase));

        veModel = ve_model::createModelFromFile(veDevice, "assets/smooth_vase.obj");
        auto smoothBase = ve_game_object::createGameObject();
        smoothBase.model = veModel;
        smoothBase.transform.translation = { 0.5f, 0.5f, 2.5f };
        smoothBase.transform.scale = { 5.f, 3.f, 3.f };
        gameObjects.push_back(std::move(smoothBase));
	}

} // namespace ve