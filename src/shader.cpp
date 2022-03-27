#include "shader.h"

Shader::Shader(std::string filename, ShaderStage stage) {
    switch (stage) {
    case ShaderStage::Vertex:
        handle_ = glCreateShader(GL_VERTEX_SHADER);
        break;
    case ShaderStage::Fragment:
        handle_ = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    default:
        throw std::runtime_error("Invalid shader stage provided");
        break;
    }
    const std::vector<char> shader_source = read_from_disk(filename);
    const char *bytes = shader_source.data();
    glShaderSource(handle_, 1, &bytes, nullptr);
    glCompileShader(handle_);

    int success;
    char info_log[1024];
    glGetShaderiv(handle_, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(handle_, 1024, nullptr, info_log);
        std::string error;
        error += "Compilation of shader `" + filename + "` failed.\n";
        error += info_log;
        error += '\n';
        throw std::runtime_error(error);
    }
}

Shader::~Shader() { glDeleteShader(handle_); }

const std::vector<char> Shader::read_from_disk(std::string filename) {
    std::ifstream file(filename, std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to load shader: " + filename);
    }

    size_t size = file.tellg();
    std::vector<char> bytes(size);

    file.seekg(0);
    file.read(&bytes[0], size);
    file.close();

    // Make sure file is null terminated
    bytes.push_back(0);
    return bytes;
}

void Shader::bind(uint32_t program_handle_) const {
    glAttachShader(program_handle_, handle_);
}

const ShaderStage &Shader::get_stage() const { return stage_; }