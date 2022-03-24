#ifndef VERTEX_H_
#define VERTEX_H_

#include <glm/glm.hpp>

/**
 * A vertex stores its model space coodinates and
 * texture coordinates
 *
 * Data layout is essentially how it's read by the GPU in the shader
 */
struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coordinates;
};

#endif