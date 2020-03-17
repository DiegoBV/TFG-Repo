#pragma once
#include <glm.hpp>

struct UniformBufferObject {
	alignas(4) float time;
	alignas(4) float yDirection;
	alignas(8) glm::vec2 resolution;
	alignas(16) glm::vec3 cameraEye;
	alignas(16) glm::vec3 cameraFront;
	alignas(16) glm::vec3 worldUp;
	alignas(16) glm::vec3 playerPos;
	alignas(16) glm::mat4 viewMat;
};

struct StorageBufferObject {
	alignas(4) float deltaTime;
	alignas(4) float velocity;
	alignas(16) glm::vec3 direction;
	alignas(16) glm::vec3 position;
};
