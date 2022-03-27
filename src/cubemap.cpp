#include "cubemap.h"

Cubemap::Cubemap(std::vector<std::string> &face_image_filenames) {
    // Create a unique handle for the texture
    glGenTextures(1, &handle_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, handle_);

    // Set texture wrapping behavior
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Set texture filtering behavior
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load raw pixel data
    int tex_width, tex_height, tex_channels;
    for (int i = 0; i < 6; i++) {
        std::string &filename = face_image_filenames[i];
        unsigned char *data = stbi_load(filename.c_str(), &tex_width,
                                        &tex_height, &tex_channels, 0);
        if (!data) {
            throw std::runtime_error("Failed to load texture");
        }

        // Bind pixel data to texture and generate a mipmap
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, tex_width,
                     tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        // Free raw pixel data
        stbi_image_free(data);
    }
}

Cubemap::~Cubemap() { glDeleteTextures(1, &handle_); }
