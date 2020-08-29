#include <iostream>
#include <vector>
#include "template_base_container.h"
#include "shape_interface_example.h"

int main() {
    std::vector<template_base_container<shape_interface>> shapes;
    rectangle r;
    triangle t;
    circle c;
    independent_legal_shape my_shape;

    shapes.emplace_back(r);
    shapes.emplace_back(t);
    shapes.emplace_back(c);
    shapes.emplace_back(my_shape);

    for (auto &shape : shapes) {
        shape.get()->input_data();
        std::cout << shape.get()->area() << std::endl;
    }

    r.set_width(10);
    std::cout << shapes[0].get()->area() << std::endl;
    return 0;
}