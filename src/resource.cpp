#include "resource.h"

uint32_t Resource::get_handle() { return handle_; }

template <typename T, typename... Fields>
uint32_t ResourceManager::create(Fields... params) {
    unsigned type_index = registry_.get_id<T>();
    if (type_index >= pools_.size()) {
        pools_.resize(type_index + 1);
    }
    if (pools_[type_index].get() == nullptr) {
        pools_[type_index] = std::make_unique<ResourcePool<T>>();
    }
    ResourcePool<T> *pool = static_cast<ResourcePool<T> *>(pools_[type_index]);

    // Create the resource and get the handle
    std::unique_ptr<T> resource = std::make_unique<T>(params...);
    uint32_t handle = resource->get_handle();

    // Cache this resource
    pool->map[resource->get_handle()] = std::move(resource);
    return handle;
}

template <typename T> T &ResourceManager::get(uint32_t handle) {
    unsigned type_index = registry_.get_id<T>();
    ResourcePool<T> *pool = static_cast<ResourcePool<T> *>(pools_[type_index]);
    return *pool->map[handle];
}