#define SDL_MAIN_HANDLED
#define STB_IMAGE_IMPLEMENTATION

#include "loader/glad.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "util/stb_image.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>

const std::string load_shader(std::string filename) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        throw std::runtime_error("Failed to load shader: " + filename);
    }
    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    return stream.str();
}

int main() {
    // Setup SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Setup display
    bool fullscreen = false;

    SDL_DisplayMode native_res;
    SDL_GetDesktopDisplayMode(0, &native_res);

    uint32_t width = 640;
    uint32_t height = 480;

    uint32_t flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    SDL_Window *window = SDL_CreateWindow(
        "OpenGL test", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        width, height, flags);

    // OpenGL setup
    SDL_GLContext context = SDL_GL_CreateContext(window);
    gladLoadGL();
    glViewport(0, 0, width, height);

    // Render vertices
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    uint32_t indices[] = {
        0, 1, 2, 
        3, 4, 5, 
        6, 7, 8, 
        9, 10, 11, 
        12, 13, 14, 
        15, 16, 17, 
        18, 19, 20, 
        21, 22, 23, 
        24, 25, 26, 
        27, 28, 29, 
        30, 31, 32, 
        33, 34, 35
    };

    // Create a vertex array
    uint32_t vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    // Bind and copy the vertex data to a buffer
    uint32_t vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and copy the index data to a buffer
    uint32_t index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set polygon draw mode
    glPolygonMode(GL_BACK, GL_FILL);

    /**
     * @brief Load shaders and attach them to a pipeline program
     */
    uint32_t shader_program = glCreateProgram();
    int success;
    char info_log[1024];

    // Vertex shader
    uint32_t vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const std::string vertex_shader_string = load_shader("./src/shaders/base.vert");
    const char *vertex_shader_buffer = vertex_shader_string.c_str();
    glShaderSource(vertex_shader, 1, &vertex_shader_buffer, nullptr);
    glCompileShader(vertex_shader);

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex_shader, 1024, nullptr, info_log);
        std::string msg;
        msg += "Vertex shader compilation failed.\n";
        msg += info_log;
        msg += '\n';
        throw std::runtime_error(msg);
    }
    glAttachShader(shader_program, vertex_shader);

    // Fragment shader
    uint32_t frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const std::string frag_shader_string = load_shader("./src/shaders/base.frag");
    const char *frag_shader_buffer = frag_shader_string.c_str();
    glShaderSource(frag_shader, 1, &frag_shader_buffer, nullptr);
    glCompileShader(frag_shader);

    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(frag_shader, 1024, nullptr, info_log);
        std::string msg;
        msg += "Fragment shader compilation failed.\n";
        msg += info_log;
        msg += '\n';
        throw std::runtime_error(msg);
    }
    glAttachShader(shader_program, frag_shader);

    // Link the shaders to the program and destroy artifacts
    glLinkProgram(shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(frag_shader);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        std::string error;
        error += "Shader linking failed.\n";
        error += info_log;
        error += '\n';
        throw std::runtime_error(error);
    }

    /**
     * @brief Describe the model coordinate and texture coordinate data should 
     * be interpreted in GPU memory for each vertex
     */
    // Model coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    
    // Texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind vertex array
    glBindVertexArray(0);

    /**
     * @brief How to handle textures
     */
    uint32_t texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture wrapping behavior
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering behavior
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load texture image data
    int tex_width, tex_height, tex_channels;
    unsigned char *data = stbi_load("./assets/wall.jpg", &tex_width, &tex_height, &tex_channels, 0);
    if(!data) {
        throw std::runtime_error("Failed to load texture");
    }

    // Bind image data to texture and generate mipmap
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free image data
    stbi_image_free(data);
    
    // Matrices
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    /**
     * @brief Main render loop that handles updates and draw calls
     */
    bool running = true;
    int ticker = 0;

    glEnable(GL_DEPTH_TEST);

    while(running) {
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
                    std::cout << "Resized to " << new_width << " " << new_height << "\n";
                }
            }
        }

        // Use the program with the vertex and fragment shaders
        glUseProgram(shader_program);

        /**
         * @brief Set the uniform data
         */
        // Model transform data uniform
        int transform_uniform_location = glGetUniformLocation(shader_program, "transform");
        glm::mat4 transform = proj * view * model;
        glUniformMatrix4fv(transform_uniform_location, 1, GL_FALSE, glm::value_ptr(transform));

        // Texture data uniform
        int texture_uniform_location = glGetUniformLocation(shader_program, "texdata");
        glUniform1i(texture_uniform_location, 0);
        
        // Ticker counter uniform
        int ticker_uniform_location = glGetUniformLocation(shader_program, "ticker");
        glUniform1i(ticker_uniform_location, ticker);

        /**
         * @brief Bind vertex array and texture data
         */
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(vertex_array);
        
        // Draw everything
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

        SDL_GL_SwapWindow(window);
        ticker++;
    }

    return 0;
}