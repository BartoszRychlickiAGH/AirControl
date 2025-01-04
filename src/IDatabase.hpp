#pragma once

#include <vector>
#include <string>

using std::vector, std::string;


class IDatabase{
    public:
        virtual void pull(string table) = 0;
        virtual void push(string table, vector<string>values) = 0;
        virtual ~IDatabase() = default;
};