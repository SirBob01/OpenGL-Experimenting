#include "texture.h"

Texture::Texture(std::string filename) {
    // Create a unique handle for the texture
    glGenTextures(1, &handle_);
    glBindTexture(GL_TEXTURE_2D, handle_);

    // Set texture wrapping behavior
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering behavior
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load raw pixel data
    int tex_width, tex_height, tex_channels;
    unsigned char *data =
        stbi_load(filename.c_str(), &tex_width, &tex_height, &tex_channels, 0);
    if (!data) {
        throw std::runtime_error("Failed to load texture");
    }

    // Bind pixel data to texture and generate a mipmap
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free raw pixel data
    stbi_image_free(data);
}

Texture::~Texture() { glDeleteTextures(1, &handle_); }

void Texture::use(uint32_t index) {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, handle_);
}