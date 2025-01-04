#pragma once
#include <vector>
#include <string>

using std::vector, std::string;

class ICompress{
    public:
        virtual vector<string> compress() = 0;
};