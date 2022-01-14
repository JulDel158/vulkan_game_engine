#pragma once

#include "ve_model.hpp"

// std
#include <memory>


namespace ve {

	struct Transform2dComponent {
		glm::vec2 translation{}; // (position offset)
		glm::vec2 scale{ 1.f, 1.f };
		float rotation;

		glm::mat2 mat2() {
			const float s = glm::sin(rotation);
			const float c = glm::cos(rotation);

			glm::mat2 rotMat{ {c, s}, {-s, c} };

			glm::mat2 scaleMat{ {scale.x, 0.f}, {0.f, scale.y} };
			return rotMat * scaleMat;
		}
	};

	class ve_game_object {
	public:
		using id_t = unsigned int;
		static ve_game_object createGameObject() {
			static id_t currentId = 0;
			return ve_game_object{ currentId++ };
		}

		ve_game_object(const ve_game_object&) = delete;
		ve_game_object &operator=(const ve_game_object&) = delete;
		ve_game_object(ve_game_object&&) = default;
		ve_game_object &operator=(ve_game_object&&) = default;

		id_t getId() { return id; }

		std::shared_ptr<ve_model> model{};
		glm::vec3 color{};
		Transform2dComponent transform2d{};

	private:
		ve_game_object(id_t objId) : id{ objId } {}

		id_t id;
	};

} // namespace ve