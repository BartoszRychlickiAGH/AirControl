#pragma once

#include <memory>
#include <vector>
#include <string>

using std::shared_ptr, std::make_shared, std::vector, std::string;


template<typename T>
class IDatabase{
    public:
        virtual vector<shared_ptr<T>> pull(string table) = 0;
        virtual void push(string table, vector<shared_ptr<T>> data) = 0;
};