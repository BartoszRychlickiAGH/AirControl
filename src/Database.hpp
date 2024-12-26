#pragma once

#include "IDatabase.hpp"

template<typename T>
class Database : public IDatabase<T>{
    private:
        Database() = default;
    public:
        vector<shared_ptr<T>> pull(string table) override;

        void push(string table, vector<shared_ptr<T>> data) override;

        Database(const Database&) = delete;
        Database &operator=(const Database&) = delete;
        Database(const Database&&) = delete;
        Database &operator=(const Database&&) = delete;

};