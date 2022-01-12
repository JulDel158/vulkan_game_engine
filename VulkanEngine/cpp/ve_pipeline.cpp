#include "../hpp/ve_pipeline.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace ve {

	VePipeline::VePipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
		createGraphicsPipeline(vertFilepath, fragFilepath);
	}

	std::vector<char> VePipeline::readFile(const std::string& filepath) {
		// opening file at the end of it in binary
		std::ifstream file{ filepath, std::ios::ate | std::ios::binary };

		if (!file.is_open()) {
			throw std::runtime_error{ "failed to open file: " + filepath };
		}

		// since we are at the end of the file we can retrive the size to create our buffer
		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(fileSize);

		//reading data into buffer from the beggining of the file
		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();
		return buffer;
	}

	void VePipeline::createGraphicsPipeline(
		const std::string& vertFilepath, const std::string& fragFilepath) {

		auto vertCode = readFile(vertFilepath);
		auto fragCode = readFile(fragFilepath);

		std::cout << "Vertex Shader Code Size: " << vertCode.size() << std::endl;
		std::cout << "Fragment Shader Code Size: " << fragCode.size() << std::endl;
	}

} // namespace ve