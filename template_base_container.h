/**
 * This model created with inspiration of Sean Parent:
 * Inheritance Is The Base Class of Evil
 * https://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil
 */

#ifndef COMMON_TEMPLATE_BASE_TEMPLATE_BASE_CONTAINER_H
#define COMMON_TEMPLATE_BASE_TEMPLATE_BASE_CONTAINER_H

#include <memory>
#include "template_base_interface_impl.h"

// A generic template base container to match any future interface
template <typename Interface>
class template_base_container {
public:
    template <typename T>
    explicit template_base_container(T &obj) : m_obj(std::make_shared<interface_implementation<Interface, T>>(obj)) {
        static_assert(std::is_base_of_v<Interface, interface_implementation<Interface, T>>, "In template_base_container interface_implementation<Interface, T> should inherit from Interface template param.");
    }

    // Get a pointer to the interface implementation
    std::shared_ptr<Interface> get() { return m_obj; }

private:
    std::shared_ptr<Interface> m_obj;
};

#endif //COMMON_TEMPLATE_BASE_TEMPLATE_BASE_CONTAINER_H