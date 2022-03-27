#include "renderer.h"

Renderer::Renderer() {
    buffer_bound_ = false;
    glGenVertexArrays(1, &vao_handle_);
    glBindVertexArray(vao_handle_);
}

Renderer::~Renderer() { glDeleteVertexArrays(1, &vao_handle_); }

void Renderer::bind() {
    // Position (x, y, z)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
    // Normal vector (x, y, z)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    // Texture coordinates (u, v)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(6 * sizeof(float)));

    // Enable the vertex attribute arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

Pipeline &Renderer::get_pipeline(std::string vertex_shader_filename,
                                 std::string fragment_shader_filename) {
    std::string key = vertex_shader_filename + fragment_shader_filename;
    if (pipelines_.find(key) == pipelines_.end()) {
        pipelines_[key] = std::make_unique<Pipeline>(vertex_shader_filename,
                                                     fragment_shader_filename);
    }
    return *pipelines_[key];
}

Texture &Renderer::get_texture(std::string image_filename) {
    if (textures_.find(image_filename) == textures_.end()) {
        textures_[image_filename] = std::make_unique<Texture>(image_filename);
    }
    return *textures_[image_filename];
}

Cubemap &
Renderer::get_cubemap(std::vector<std::string> &cubemap_image_filenames) {
    std::string key;
    for (std::string &str : cubemap_image_filenames) {
        key.append(str);
    }
    if (cubemaps_.find(key) == cubemaps_.end()) {
        cubemaps_[key] = std::make_unique<Cubemap>(cubemap_image_filenames);
    }
    return *cubemaps_[key];
}

void Renderer::use_material(Material &material, glm::mat4 &transform) {
    Pipeline &pipeline = get_pipeline(material.vertex_shader_filename,
                                      material.fragment_shader_filename);

    pipeline.bind();

    // Bind the textures
    for (int i = 0; i < material.textures.size(); i++) {
        TextureDescriptor &desc = material.textures[i];
        Texture &texture = get_texture(desc.image_filename);
        texture.bind(i);

        switch (desc.mapping) {
        case TextureMapping::Diffuse:
            pipeline.set_uniform_int("diffuse", i);
            break;
        case TextureMapping::Specular:
            pipeline.set_uniform_int("specular", i);
            break;
        case TextureMapping::Normal:
            pipeline.set_uniform_int("normal", i);
            break;
        default:
            break;
        }
    }

    // Bind the cubemap
    if (material.cubemap_image_filenames.size() == 6) {
        Cubemap &cubemap = get_cubemap(material.cubemap_image_filenames);
        cubemap.bind(material.textures.size() + 1);
    } else if (material.cubemap_image_filenames.size() > 0) {
        throw std::runtime_error(
            "Invalid number of images provided for cubemap");
    }

    material.set_uniforms(pipeline);
    pipeline.set_uniform_matrix4("transform", glm::value_ptr(transform));
}

void Renderer::draw(Mesh &mesh, Material &material, glm::mat4 &transform) {
    mesh.bind();
    if (!buffer_bound_) {
        buffer_bound_ = true;
        bind();
    }
    use_material(material, transform);
    glDrawElements(GL_TRIANGLES, mesh.get_index_count(), GL_UNSIGNED_INT, 0);
}