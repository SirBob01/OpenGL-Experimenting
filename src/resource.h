#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <memory>
#include <unordered_map>
#include <vector>

#include "util/typeid.h"

/**
 * Describes a render resource
 */
class Resource {
  protected:
    uint32_t handle_;

  public:
    /**
     * Get the unique integer handle of this resource
     */
    uint32_t get_handle();
};

/**
 * Empty non-parameterized struct
 */
struct BaseResourcePool {};

/**
 * Generic resource pool
 */
template <typename T> struct ResourcePool : public BaseResourcePool {
    std::unordered_map<uint32_t, std::unique_ptr<T>> map;
};

/**
 * Manages the creation and fetching of rendering resources
 */
class ResourceManager {
    std::vector<std::unique_ptr<BaseResourcePool>> pools_;
    TypeID registry_;

  public:
    /**
     * Create a new generic resource and grab its unique integer handle
     */
    template <typename T, typename... Fields> uint32_t create(Fields... params);

    /**
     * Get a reference to the resource mapped to a unique integer handle
     */
    template <typename T> T &get(uint32_t handle);
};

#endif