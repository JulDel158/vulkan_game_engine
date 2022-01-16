#pragma once

#include "ve_device.hpp"
#include "ve_buffer.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

// std
#include <memory>
#include <vector>

namespace ve {

	class ve_model {
	public:

		struct Vertex {
			glm::vec3 position{};
			glm::vec3 color{};
			glm::vec3 normal{};
			glm::vec2 uv{};

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

			bool operator==(const Vertex & other) const {
				return position == other.position && 
					color == other.color && 
					normal == other.normal &&
					uv == other.uv;
			}
		};

		struct Builder {
			std::vector<Vertex> vertices{};
			std::vector<uint32_t> indices{};

			void loadModel(const std::string& filePath);
		};

		ve_model(ve_device &device, const ve_model::Builder &builder);
		~ve_model();

		ve_model(const ve_model&) = delete;
		ve_model &operator=(const ve_model&) = delete;

		static std::unique_ptr<ve_model> createModelFromFile(ve_device& device, const std::string& filepath);

		void bind(VkCommandBuffer commandBuffer);
		void draw(VkCommandBuffer commandBuffer);

	private:
		void createVertexBuffers(const std::vector<Vertex> &vertices);
		void createIndexBuffer(const std::vector<uint32_t> &indices);

		ve_device& veDevice;

		std::unique_ptr<ve_buffer> vertexBuffer;
		uint32_t vertexCount;

		bool hasIndexBuffer{ false };
		std::unique_ptr<ve_buffer> indexBuffer;
		uint32_t indexCount;
	};

} // namespace ve