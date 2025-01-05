#pragma once

#include "IDatabase.hpp"
#include <vector>
#include <string>
#include <windows.h> // must be before sql.h and others
#include <sql.h>
#include <sqlext.h>
#include <cstdint>

using std::vector, std::string;


class Database : public IDatabase {
private:
    SQLHENV hEnv{};
    SQLHDBC hDbc{};
    SQLHSTMT hStmt{};
    SQLRETURN ret{};
    


public:
    Database();


    vector<shared_ptr<Airport>> pull() override;
    void push(string table, vector<string>values) override;


    ~Database();

};