#pragma once

#include "ve_model.hpp"

// libs
#include <glm/gtc/matrix_transform.hpp>

// std
#include <memory>

namespace ve {

	struct TransformComponent {
		glm::vec3 translation{}; // (position offset)
		glm::vec3 scale{ 1.f, 1.f, 1.f };
		glm::vec3 rotation{};

		// Matrix corrsponds to Translate * Ry * Rx * Rz * Scale
		// Rotations correspond to Tait-bryan angles of Y(1), X(2), Z(3)
		// https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix
		glm::mat4 mat4();
		glm::mat3 normalMatrix();
	};

	class ve_game_object {
	public:
		using id_t = unsigned int;
		static ve_game_object createGameObject() {
			static id_t currentId = 0;
			return ve_game_object{ currentId++ };
		}

		ve_game_object(const ve_game_object&) = delete;
		ve_game_object& operator=(const ve_game_object&) = delete;
		ve_game_object(ve_game_object&&) = default;
		ve_game_object& operator=(ve_game_object&&) = default;

		id_t getId() { return id; }

		std::shared_ptr<ve_model> model{};
		glm::vec3 color{};
		TransformComponent transform{};

	private:
		ve_game_object(id_t objId) : id{ objId } {}

		id_t id;
	};

} // namespace ve