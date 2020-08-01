#ifndef COMMON_TEMPLATE_BASE_FACTORY_H
#define COMMON_TEMPLATE_BASE_FACTORY_H

#include "../template_base_container.h"

struct base_foo_interface {
    int result;
    virtual void do_thing() = 0;
};

template <typename T1, typename T2>
struct BaseFoo : base_foo_interface {
    T1 t1;
    T2 t2;

    explicit BaseFoo(T1 t1, T2 t2) : t1(t1), t2(t2) {}
};

struct ThisFoo : BaseFoo<int, float> {
    int t1;
    float t2;

    ThisFoo(int t1, float t2) : t1(t1), t2(t2), BaseFoo<int, float>(t1, t2) {}

    void do_thing() override {

    }
};

struct ThatFoo : BaseFoo<double, bool> {
    double t1;
    bool t2;
    int result;

    ThatFoo(double t1, bool t2) : t1(t1), t2(t2), BaseFoo<double, bool>(t1, t2) {}

    void do_thing() override {

    }
};

namespace factory {
    template_base_container<base_foo_interface> create(const std::string &type);
};

#endif //COMMON_TEMPLATE_BASE_FACTORY_H
