#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <memory>
#include <unordered_map>
#include <vector>

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

#endif