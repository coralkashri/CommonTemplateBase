#include <iostream>
#include <vector>
#include <memory>
#include <math.h>

class virtual_base {
public:
    template<typename T>
    virtual_base(T &obj) : m_obj(std::make_shared<impl<T>>(obj)) {}

    void input_data() {
        m_obj->input_data();
    }

    [[nodiscard]] double area() const {
        return m_obj->area();
    }

private:
    class interface {
    public:
        virtual ~interface() = default;
        virtual void input_data() = 0;
        [[nodiscard]] virtual double area() const = 0;
    };

    template<typename T>
    class impl : public interface {
        T& m_impl_obj;

    public:
        explicit impl(T& impl_obj) : m_impl_obj(impl_obj) {}

        void input_data() override {
            m_impl_obj.input_data();
        }

        [[nodiscard]] double area() const override {
            return m_impl_obj.area();
        }
    };

    std::shared_ptr<interface> m_obj;
};

class shape_property {};

template <typename T>
concept ShapeProperty = std::is_base_of_v<shape_property, T>;

template <ShapeProperty ...Properties>
class shape : virtual public Properties... {
public:
    explicit shape(std::string name) : name(std::move(name)) {}
    virtual ~shape() = default;

    [[nodiscard]] std::string get_name() const { return name; }

    virtual void input_data() = 0;
    [[nodiscard]] virtual double area() const = 0;

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
    std::vector<virtual_base> shapes;

    rectangle r;
    triangle t;
    circle c;

    shapes.emplace_back(r);
    shapes.emplace_back(t);
    shapes.emplace_back(c);

    for (auto &shape : shapes) {
        shape.input_data();
        std::cout << shape.area() << std::endl;
    }

    r.set_width(10);
    std::cout << shapes[0].area() << std::endl;
    return 0;
}