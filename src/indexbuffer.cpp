#include "indexbuffer.h"

IndexBuffer::IndexBuffer(std::vector<uint32_t> &indices) {
    count_ = indices.size();

    glGenBuffers(1, &handle_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count_,
                 indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &handle_); }

void IndexBuffer::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle_); }

void IndexBuffer::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

size_t IndexBuffer::get_count() { return count_; }
