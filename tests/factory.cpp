#include "factory.h"

namespace factory {
    template_base_container<base_foo_interface> create(const std::string &type) {
        if (type == "int_float") {
            return template_base_container<base_foo_interface>(*std::make_shared<ThisFoo>(1, 2.f));
        } else if (type == "double_bool") {
            return template_base_container<base_foo_interface>(*std::make_shared<ThatFoo>(1.5, true));
        } else { // Default or throw exception
            return template_base_container<base_foo_interface>(*std::make_shared<BaseFoo<int, int>>(1, 1));
        }
    }
};