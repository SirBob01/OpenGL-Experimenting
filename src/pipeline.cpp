#include "pipeline.h"

Pipeline::Pipeline(std::string vertex_shader_filename,
                   std::string fragment_shader_filename) {
    program_ = glCreateProgram();
    key_ = vertex_shader_filename + fragment_shader_filename;

    // Create the shaders
    uint32_t vertex_shader =
        bind_shader(vertex_shader_filename, GL_VERTEX_SHADER);
    uint32_t fragment_shader =
        bind_shader(fragment_shader_filename, GL_FRAGMENT_SHADER);

    // Link the shader pipeline and destroy shader instances when finished
    glLinkProgram(program_);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Error handling
    int success;
    char info_log[512];
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program_, 512, NULL, info_log);
        std::string error;
        error += "Shader linking failed.\n";
        error += info_log;
        error += '\n';
        throw std::runtime_error(error);
    }
}

const std::vector<char> Pipeline::read_from_disk(std::string filename) {
    std::ifstream file(filename, std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to load shader: " + filename);
    }

    size_t size = file.tellg();
    std::vector<char> bytes(size);

    file.seekg(0);
    file.read(&bytes[0], size);
    file.close();
    return bytes;
}

uint32_t Pipeline::bind_shader(std::string filename, GLenum type) {
    uint32_t shader = glCreateShader(type);
    const std::vector<char> shader_source = read_from_disk(filename);
    const char *bytes = shader_source.data();
    glShaderSource(shader, 1, &bytes, nullptr);
    glCompileShader(shader);

    int success;
    char info_log[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, info_log);
        std::string error;
        error += "Compilation of shader `" + filename + "` failed.\n";
        error += info_log;
        error += '\n';
        throw std::runtime_error(error);
    }
    glAttachShader(program_, shader);
    return shader;
}

uint32_t Pipeline::get_uniform_location(std::string identifier) {
    if (cache_.find(identifier) == cache_.end()) {
        cache_[identifier] = glGetUniformLocation(program_, identifier.c_str());
    }
    return cache_[identifier];
}

void Pipeline::bind() { glUseProgram(program_); }

const std::string &Pipeline::get_key() { return key_; }

void Pipeline::set_uniform_matrix4(std::string identifier, float matrix[]) {
    glUniformMatrix4fv(get_uniform_location(identifier), 1, GL_FALSE, matrix);
}

void Pipeline::set_uniform_int(std::string identifier, uint32_t number) {
    glUniform1i(get_uniform_location(identifier), number);
}

void Pipeline::set_uniform_float(std::string identifier, float number) {
    glUniform1f(get_uniform_location(identifier), number);
}
