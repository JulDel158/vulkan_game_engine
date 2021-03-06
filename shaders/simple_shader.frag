#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec3 fragPosWorld;
layout(location = 2) in vec3 fragNormalWorld;

layout (location = 0) out vec4 outColor;


layout(set = 0, binding = 0) uniform GlobaUbo {
	mat4 projection;
	mat4 view;
	vec4 ambientLightColor;
	vec3 pLightPosition;
	vec4 pLightColor;
} ubo;

layout(push_constant) uniform Push {
	mat4 modelMatrix;
	mat4 normalMatrix;
} push;

void main() {
	vec3 directionToLight = ubo.pLightPosition - fragPosWorld;
	float attenuation = 1.0 / dot(directionToLight, directionToLight); // distance square

	vec3 lightColor = ubo.pLightColor.xyz * ubo.pLightColor.w * attenuation;
	vec3 ambientLight = ubo.ambientLightColor.xyz * ubo.ambientLightColor.w;
	vec3 diffuseLight = lightColor * max(dot(normalize(fragNormalWorld), normalize(directionToLight)),0);

	outColor = vec4((diffuseLight + ambientLight) * fragColor, 1.0);
}