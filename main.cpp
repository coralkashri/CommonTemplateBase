#include <iostream>
#include <vector>
#include <memory>
#include <math.h>

class shape_interface {
public:
    virtual ~shape_interface() = default;
    virtual void input_data() = 0;
    [[nodiscard]] virtual double area() const = 0;
};

template <typename Interface>
class virtual_base {
public:
    template<typename T> explicit virtual_base(T &obj) : m_obj(std::make_shared<interface_implementation<T>>(obj)) {}

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

class shape_property {};

template <typename T>
concept ShapeProperty = std::is_base_of_v<shape_property, T>;

template <ShapeProperty ...Properties>
class shape : public shape_interface, virtual public Properties... { // Must inherit from the same interface of the collection
public:
    explicit shape(std::string name) : name(std::move(name)) {}
    virtual ~shape() = default;

    [[nodiscard]] std::string get_name() const { return name; }

protected:
    std::string name;
};

class width_shape_property : shape_property {
public:
    [[nodiscard]] double get_width() const { return width; }
    void set_width(double width) { this->width = width; }

protected:
    double width;
};

class height_shape_property : shape_property {
public:
    [[nodiscard]] double get_height() const { return height; }
    void set_height(double height) { this->height = height; }

protected:
    double height;
};

class radios_shape_property : shape_property {
public:
    [[nodiscard]] double get_radios() const { return radios; }
    void set_radios(double radios) { this->radios = radios; }

protected:
    double radios;
};

class rectangle : public shape<width_shape_property, height_shape_property> {
public:
    rectangle() : shape("Rectangle") {}

    void input_data() override {
        double width, height;
        std::cout << "Enter width & height:" << std::endl;
        std::cin >> width >> height;
        set_width(width);
        set_height(height);
    }

    [[nodiscard]] double area() const override {
        return width * height;
    }
};

class triangle : public shape<width_shape_property, height_shape_property> {
public:
    triangle() : shape("Triangle") {}

    void input_data() override {
        double width, height;
        std::cout << "Enter width & height:" << std::endl;
        std::cin >> width >> height;
        set_width(width);
        set_height(height);
    }

    [[nodiscard]] double area() const override {
        return (width * height) / 2;
    }
};

class circle : public shape<radios_shape_property> {
public:
    circle() : shape("Circle") {}

    void input_data() override {
        double radios;
        std::cout << "Enter radios:" << std::endl;
        std::cin >> radios;
        set_radios(radios);
    }

    [[nodiscard]] double area() const override {
        return M_PI * radios * radios;
    }
};

int main() {
    std::vector<virtual_base<shape_interface>> shapes;

    rectangle r;
    triangle t;
    circle c;

    shapes.emplace_back(r);
    shapes.emplace_back(t);
    shapes.emplace_back(c);

    for (auto &shape : shapes) {
        shape.get()->input_data();
        std::cout << shape.get()->area() << std::endl;
    }

    r.set_width(10);
    std::cout << shapes[0].get()->area() << std::endl;
    return 0;
}