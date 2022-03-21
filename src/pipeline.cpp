#include "pipeline.h"

Pipeline::Pipeline(std::string vertex_shader_filename, 
                   std::string fragment_shader_filename) {
    program_ = glCreateProgram();

    // Create the shaders
    int vertex_shader = bind_shader(vertex_shader_filename, GL_VERTEX_SHADER);
    int fragment_shader = bind_shader(fragment_shader_filename, GL_FRAGMENT_SHADER);
    
    // Link the shader pipeline and destroy shader instances when finished
    glLinkProgram(program_);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Error handling
    int success;
    char info_log[512];
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if(!success) {
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
    if(!file.is_open()) {
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
    if(!success) {
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

void Pipeline::use() {
    glUseProgram(program_);
}

void Pipeline::set_uniform_matrix4(std::string identifier, float matrix[]) {
    int uniform_location = glGetUniformLocation(program_, identifier.c_str());
    glUniformMatrix4fv(uniform_location, 1, GL_FALSE, matrix);
}

void Pipeline::set_uniform_int(std::string identifier, uint32_t number) {
    int uniform_location = glGetUniformLocation(program_, identifier.c_str());
    glUniform1i(uniform_location, number);
}

void Pipeline::set_uniform_float(std::string identifier, float number) {
    int uniform_location = glGetUniformLocation(program_, identifier.c_str());
    glUniform1f(uniform_location, number);
}
