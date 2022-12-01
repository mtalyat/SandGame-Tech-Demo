#pragma once

#include <vector>
#include <functional>
#include "Object.h"

namespace eng
{
    class Event :
        public Object
    {
    public:
        Event();

        void addFunction(std::function<void()> func);

        void invoke();

    private:
        std::vector<std::function<void()>> functions;
    };

}
