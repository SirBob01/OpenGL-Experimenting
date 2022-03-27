#include "material.h"

Material::Material(Shader &vertex_shader, Shader &fragment_shader) {
    handle_ = glCreateProgram();

    vertex_shader.bind(handle_);
    fragment_shader.bind(handle_);

    glLinkProgram(handle_);

    // Error handling
    int success;
    char info_log[512];
    glGetProgramiv(handle_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(handle_, 512, NULL, info_log);
        std::string error;
        error += "Shader linking failed.\n";
        error += info_log;
        error += '\n';
        throw std::runtime_error(error);
    }
}

Material::~Material() { glDeleteProgram(handle_); }

int Material::get_uniform_location(std::string identifier) {
    if (location_cache_.find(identifier) == location_cache_.end()) {
        location_cache_[identifier] =
            glGetUniformLocation(handle_, identifier.c_str());
        if (location_cache_[identifier] < 0) {
            throw std::runtime_error("GLSL uniform identifier `" + identifier +
                                     "` could not be found");
        }
    }
    return location_cache_[identifier];
}

void Material::bind() {
    glUseProgram(handle_);
    for (auto &pair : integer_values_) {
        glUniform1i(pair.first, pair.second);
    }
    for (auto &pair : float_values_) {
        glUniform1f(pair.first, pair.second);
    }
    for (auto &pair : mat4_values_) {
        glUniformMatrix4fv(pair.first, 1, false, glm::value_ptr(pair.second));
    }

    int index = 3;
    for (auto &pair : texture_values_) {
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, pair.second);
        glUniform1i(pair.first, index);
        index++;
    }
    for (auto &pair : cubemap_values_) {
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_CUBE_MAP, pair.second);
        index++;
    }
}

void Material::set_integer(std::string identifier, int value) {
    int location = get_uniform_location(identifier);
    integer_values_[location] = value;
}

void Material::set_float(std::string identifier, float value) {
    int location = get_uniform_location(identifier);
    float_values_[location] = value;
}

void Material::set_matrix4(std::string identifier, glm::mat4 &value) {
    int location = get_uniform_location(identifier);
    mat4_values_[location] = value;
}

void Material::set_texture(Texture &texture, TextureMapping mapping) {
    int location;
    switch (mapping) {
    case TextureMapping::Diffuse:
        location = get_uniform_location("diffuse");
        break;
    case TextureMapping::Specular:
        location = get_uniform_location("specular");
        break;
    case TextureMapping::Normal:
        location = get_uniform_location("normal");
        break;
    default:
        throw std::runtime_error("Invalid texture mapping type");
        break;
    }
    texture_values_[location] = texture.get_handle();
}

void Material::set_cubemap(std::string identifier, Cubemap &cubemap) {
    int location = get_uniform_location(identifier);
    cubemap_values_[location] = cubemap.get_handle();
}