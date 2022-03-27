#define SDL_MAIN_HANDLED

#include "src/loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>

#include "src/material.h"
#include "src/mesh.h"
#include "src/renderer.h"
#include "src/resource.h"
#include "src/texture.h"

int main() {
    // Setup SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    // Setup display
    bool fullscreen = false;

    SDL_DisplayMode native_res;
    SDL_GetDesktopDisplayMode(0, &native_res);

    uint32_t width = 640;
    uint32_t height = 480;

    uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    SDL_Window *window =
        SDL_CreateWindow("OpenGL test", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, width, height, flags);

    // OpenGL setup
    SDL_GLContext context = SDL_GL_CreateContext(window);
    gladLoadGL();
    glViewport(0, 0, width, height);

    // Render vertices
    std::vector<glm::vec3> vertices = {
        {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f},
        {0.5f, 0.5f, -0.5f},   {-0.5f, 0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},

        {-0.5f, -0.5f, 0.5f},  {0.5f, -0.5f, 0.5f},  {0.5f, 0.5f, 0.5f},
        {0.5f, 0.5f, 0.5f},    {-0.5f, 0.5f, 0.5f},  {-0.5f, -0.5f, 0.5f},

        {-0.5f, 0.5f, 0.5f},   {-0.5f, 0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f},

        {0.5f, 0.5f, 0.5f},    {0.5f, 0.5f, -0.5f},  {0.5f, -0.5f, -0.5f},
        {0.5f, -0.5f, -0.5f},  {0.5f, -0.5f, 0.5f},  {0.5f, 0.5f, 0.5f},

        {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, 0.5f},
        {0.5f, -0.5f, 0.5f},   {-0.5f, -0.5f, 0.5f}, {-0.5f, -0.5f, -0.5f},

        {-0.5f, 0.5f, -0.5f},  {0.5f, 0.5f, -0.5f},  {0.5f, 0.5f, 0.5f},
        {0.5f, 0.5f, 0.5f},    {-0.5f, 0.5f, 0.5f},  {-0.5f, 0.5f, -0.5f}};
    std::vector<glm::vec2> texture_coordinates = {
        {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
        {0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {1.0f, 1.0f},
        {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
        {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f},
        {0.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f},
        {1.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f},
        {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f},
        {0.0f, 1.0f},
    };
    std::vector<uint32_t> indices = {
        0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
    std::vector<glm::vec3> positions = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    // Create the renderer
    Renderer renderer;

    // Create the mesh
    Mesh mesh(vertices, texture_coordinates, indices);

    // Create a diffuse (color) texture
    Texture diffuse("../assets/wall.jpg");

    // Create the shaders
    Shader vertex_shader("../src/shaders/default.vert", ShaderStage::Vertex);
    Shader fragment_shader("../src/shaders/default.frag",
                           ShaderStage::Fragment);

    // Create a material
    Material material(vertex_shader, fragment_shader);
    // material.set_texture(diffuse, TextureMapping::Diffuse);

    // Set polygon draw mode
    glPolygonMode(GL_BACK, GL_FILL);

    // Matrices
    glm::mat4 view =
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 proj =
        glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    bool running = true;
    int ticker = 0;

    glEnable(GL_DEPTH_TEST);

    // Main render loop
    while (running) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_WINDOWEVENT) {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    // Update the viewport
                    const uint32_t new_width = event.window.data1;
                    const uint32_t new_height = event.window.data2;
                    glViewport(0, 0, new_width, new_height);
                    std::cout << "Resized to " << new_width << " " << new_height
                              << "\n";
                }
            }
        }

        // Draw everything
        for (auto &position : positions) {
            // Calculate the model transform
            glm::mat4 transform = proj * view;
            transform = glm::translate(transform, position);
            transform = glm::rotate(transform, glm::radians(ticker * 1.0f),
                                    glm::vec3(0.5, 1.0, 0.0));

            // Draw
            renderer.draw(mesh, material, transform);
        }

        SDL_GL_SwapWindow(window);
        ticker++;
    }

    return 0;
}