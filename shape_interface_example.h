#ifndef COMMON_TEMPLATE_BASE_SHAPE_INTERFACE_EXAMPLE_H
#define COMMON_TEMPLATE_BASE_SHAPE_INTERFACE_EXAMPLE_H

#include <iostream>
#include <math.h>
#include "template_base_interface_impl.h"

class shape_interface {
public:
    virtual ~shape_interface() = default;
    virtual void input_data() = 0;
    [[nodiscard]] virtual double area() const = 0;
};

// Interface implementation specialization for shape_interface
template <typename T>
class interface_implementation<shape_interface, T> : public shape_interface {
public:
    explicit interface_implementation(T& impl_obj) : m_impl_obj(impl_obj) {}

    // Interface should be fully implemented here
    // region [Interface Implementation Begin]
    void input_data() override { return m_impl_obj.input_data(); };
    [[nodiscard]] double area() const override { return m_impl_obj.area(); };
    // endregion [Interface Implementation End]

private:
    T& m_impl_obj; // Contain the target specialized class instance
};

class shape_property {
public:
    virtual void input_data() = 0;
};

template <typename T>
concept ShapeProperty = std::is_base_of_v<shape_property, T>;

template <ShapeProperty ...Properties>
class shape : public shape_interface, virtual public Properties... { // Must inherit from the same interface of the collection
public:
    explicit shape(std::string name) : name(std::move(name)) {}
    virtual ~shape() = default;

    void input_data() override {
        (Properties::input_data(), ...);
    }

    [[nodiscard]] std::string get_name() const { return name; }

protected:
    std::string name;
};

class width_shape_property : shape_property {
public:
    [[nodiscard]] double get_width() const { return width; }
    void set_width(double width) { this->width = width; }

    void input_data() override {
        std::cout << "Enter width:" << std::endl;
        std::cin >> width;
    };

protected:
    double width;
};

class height_shape_property : shape_property {
public:
    [[nodiscard]] double get_height() const { return height; }
    void set_height(double height) { this->height = height; }

    void input_data() override {
        std::cout << "Enter height:" << std::endl;
        std::cin >> height;
    };

protected:
    double height;
};

class radios_shape_property : shape_property {
public:
    [[nodiscard]] double get_radios() const { return radios; }
    void set_radios(double radios) { this->radios = radios; }

    void input_data() override {
        std::cout << "Enter radios:" << std::endl;
        std::cin >> radios;
    };

protected:
    double radios;
};

class rectangle : public shape<width_shape_property, height_shape_property> {
public:
    rectangle() : shape("Rectangle") {}

    void input_data() override {
        std::cout << "Input " << name << ":" << std::endl;
        shape::input_data();
    }

    [[nodiscard]] double area() const override {
        return width * height;
    }
};

class triangle : public shape<width_shape_property, height_shape_property> {
public:
    triangle() : shape("Triangle") {}

    void input_data() override {
        std::cout << "Input " << name << ":" << std::endl;
        shape::input_data();
    }

    [[nodiscard]] double area() const override {
        return (width * height) / 2;
    }
};

class circle : public shape<radios_shape_property> {
public:
    circle() : shape("Circle") {}

    void input_data() override {
        std::cout << "Input " << name << ":" << std::endl;
        shape::input_data();
    }

    [[nodiscard]] double area() const override {
        return M_PI * radios * radios;
    }
};

class independent_legal_shape {
public:
    independent_legal_shape() = default;

    void input_data() {
        std::cout << "No input needed for independent_legal_shape." << std::endl;
    }

    [[nodiscard]] double area() const {
        return 50;
    }
};

#endif //COMMON_TEMPLATE_BASE_SHAPE_INTERFACE_EXAMPLE_H