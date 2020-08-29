#ifndef COMMON_TEMPLATE_BASE_TEMPLATE_BASE_INTERFACE_IMPL_H
#define COMMON_TEMPLATE_BASE_TEMPLATE_BASE_INTERFACE_IMPL_H

// A generic interface implementation
template <typename Interface, typename T>
class interface_implementation : public Interface {
public:
    explicit interface_implementation(T& impl_obj) : m_impl_obj(impl_obj) {}

    // Interface should be fully implemented here
    // region [Interface Implementation Begin]
    // endregion [Interface Implementation End]

private:
    T& m_impl_obj; // Contain the target specialized class instance
};

#endif //COMMON_TEMPLATE_BASE_TEMPLATE_BASE_INTERFACE_IMPL_H