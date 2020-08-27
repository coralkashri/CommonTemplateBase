/**
 * This model created with inspiration of Sean Parent:
 * Inheritance Is The Base Class of Evil
 * https://channel9.msdn.com/Events/GoingNative/2013/Inheritance-Is-The-Base-Class-of-Evil
 */

#ifndef COMMON_TEMPLATE_BASE_TEMPLATE_BASE_CONTAINER_H
#define COMMON_TEMPLATE_BASE_TEMPLATE_BASE_CONTAINER_H

#include <memory>

template <typename Interface>
class template_base_container {
public:
    template<typename T> explicit template_base_container(T &obj) : m_obj(std::make_shared<interface_implementation<T>>(obj)) {}

    // Get a pointer to the interface implementation
    std::shared_ptr<Interface> get() { return m_obj; }

private:
    template<typename T>
    class interface_implementation : public Interface {
        T& m_impl_obj; // Contain the target specialized class instance

    public:
        explicit interface_implementation(T& impl_obj) : m_impl_obj(impl_obj) {}

        // Interface should be fully implemented here
        // region [Interface Implementation Begin]
        void input_data() override { return m_impl_obj.input_data(); }

        [[nodiscard]] double area() const override { return m_impl_obj.area(); }
        // endregion [Interface Implementation End]
    };

    std::shared_ptr<Interface> m_obj;
};

#endif //COMMON_TEMPLATE_BASE_TEMPLATE_BASE_CONTAINER_H