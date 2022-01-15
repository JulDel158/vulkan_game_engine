#pragma once

#include "ve_device.hpp"
#include "ve_game_object.hpp"
#include "ve_window.hpp"
#include "ve_renderer.hpp"

// std
#include <memory>
#include <vector>

namespace ve {

class FirstApp {
public:
	static constexpr int WIDTH = 800;
	static constexpr int HEIGHT = 600;

	FirstApp();
	~FirstApp();

	FirstApp(const FirstApp&) = delete;
	FirstApp& operator=(const FirstApp&) = delete;

	void run();
private:
	void loadGameObjects();

	ve_window veWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
	ve_device veDevice{ veWindow };
	ve_renderer veRenderer{ veWindow, veDevice };

	std::vector<ve_game_object> gameObjects;
};


} // namespace ve