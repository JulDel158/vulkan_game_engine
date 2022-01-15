#include "../hpp/first_app.hpp"

#include "../hpp/simple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <stdexcept>
#include <array>

namespace ve {

	FirstApp::FirstApp() {
		loadGameObjects();
	}

	FirstApp::~FirstApp() {}

	void FirstApp::run() {
		simple_render_system simpleRenderSystem{ veDevice, veRenderer.getSwapChainRenderPass() };

		while (!veWindow.shouldClose()) {
			glfwPollEvents();
			
			if (auto commandBuffer = veRenderer.beginFrame()) {
				veRenderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
				veRenderer.endSwapChainRenderPass(commandBuffer);
				veRenderer.endFrame();
			}

		}

		vkDeviceWaitIdle(veDevice.device());
	}

	void FirstApp::loadGameObjects() {
		std::vector<ve_model::Vertex> vertices{
			{{0.f, -0.5f}, {1.f, 0.f, 0.f}},
			{{0.5f, 0.5f}, {0.f, 1.f, 0.f}},
			{{-0.5f, 0.5f}, {0.f, 0.f, 1.f}}
		};

		auto veModel = std::make_shared<ve_model>(veDevice, vertices);

		auto triangle = ve_game_object::createGameObject();
		triangle.model = veModel;
		triangle.color = { .1f, .8f, .1f };
		triangle.transform2d.translation.x = .2f;
		triangle.transform2d.scale = { 2.f, 0.5f };
		triangle.transform2d.rotation = .25f * glm::two_pi<float>();

		gameObjects.push_back(std::move(triangle));
	}

} // namespace ve