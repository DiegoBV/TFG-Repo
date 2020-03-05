#version 450 core
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    float time;
    float yDirection;
    vec2 resolution;
    vec3 cameraEye;
    vec3 cameraFront;
    vec3 worldUp;
    mat4 viewMat;
} ubo;

layout(location = 0) out vec4 outColor;
layout(std430, binding = 3) buffer ssbo
{
    int data_SSBO[];
};

vec3 rayDirection(float fieldOfView, vec2 size, vec2 fragCoord);

#include ..\\..\\Shaders\\snowTerrain.c

vec3 rayDirection(float fieldOfView, vec2 size, vec2 fragCoord) {
    vec2 uv = vec2(fragCoord.x - (size.x/2.0), fragCoord.y - (size.y/2.0));
    uv.y = ubo.yDirection * uv.y;
    float z = size.y / tan(radians(fieldOfView) / 2.0);
    return normalize(vec3(uv, -z));
}

void main()
{
    vec2 pixelCoord = gl_FragCoord.xy;
    vec3 rayOrigin = ubo.cameraEye;
    vec3 rayDir = rayDirection(45.0, ubo.resolution, pixelCoord);
    rayDir = (ubo.viewMat * vec4(rayDir, 0.0)).xyz; //works
    
    //tracing the ray (getting the distance of the closest object in the ray direction)
	
    float distanceToSurface = rayMarch(rayOrigin, rayDir, MIN_DIST, MAX_DIST);

    data_SSBO[0] = 1;
    data_SSBO[1] = 1;
    data_SSBO[2] = 1;

    vec3 p = rayOrigin + rayDir * distanceToSurface;

    if (distanceToSurface > MAX_DIST - EPSILON) {
        // Didn't hit anything
        outColor = vec4(0.1, 0.1, 0.1, 1.0);
		return;
    }

    outColor = vec4(getColor(p), 1);
}
