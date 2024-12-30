#pragma once

#include <string>

class IPrint{
    public:
        virtual void display() = 0;
};

class IPrintAirport{
    public:
        virtual void display(std::string mode = "") = 0;
};