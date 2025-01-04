#pragma once

#include "Database.hpp"
#include <iostream>

using std::endl, std::cout;


Database::Database()
{

    // Allocate environment handle
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

    // Allocate connection handle
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Connect to the database
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\ProjectModels;Database=AirDb;Trusted_Connection=yes;";
    ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

    if (!SQL_SUCCEEDED(ret)) {
        string error{ "cannot connect to database" };
        throw error;
    }
}



// methods inherited from interfaces 



// pull data from database
void Database::pull(string table) {
    
    // under constructions

}


void Database::push(string table, vector<string>values) {

    // Allocate statement handle
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    if (table == "Flights") {
        // insert Flights

        string SqlQuery = "INSERT INTO " + table + " (Base,Destination, PlaneName, FlightDate, DepartureTime, ArrivalTime, DemandIndicator) VALUES (?,?,?,?,?,?,?)";

        SQLPrepare(hStmt, (SQLCHAR*)SqlQuery.c_str(), SQL_NTS);

        // parameters
        size_t i{ 0 }; // indicator of param
        for (const string& s : values) {
            if (i == 7) { // if s is a demandIndicator then insert as int type
                SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(i + 1), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, s.size(), 0, (SQLLEN*)std::stoi(s), 0, NULL);
                break;
            }

            SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(i + 1), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, s.size(), 0, (SQLCHAR*)s.c_str(), 0, NULL); // inserting param instead of ? in sql query
            i++; // increment indicator to add new param
        }
    }
    else {
        
        
        // sql query
        string SqlQuery = "INSERT INTO " + table + " (AirportName,Capacity, DepartureIds, ArrivalIds, parkedIds, departureDemands, arrivalDemands, parkDemands) VALUES (?,?,?,?,?,?,?,?)";

        SQLPrepare(hStmt, (SQLCHAR*)SqlQuery.c_str(), SQL_NTS);

        // parameters
        size_t i{ 0 }; // indicator of param
        for (const string& s : values) {
            if (i == 1) { // if s is a current element in values then insert as int type
                SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(i + 1), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, s.size(), 0, (SQLLEN*)std::stoi(s), 0, NULL);
                break;
            }

            // insert as string type
            SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(i + 1), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, s.size(), 0, (SQLCHAR*)s.c_str(), 0, NULL); // inserting param instead of ? in sql query
            i++; // increment indicator to add new param
        }


    }
    // Execute the statement
    ret = SQLExecute(hStmt);

    // check if execution went correct
    if (!SQL_SUCCEEDED(ret)) {
        SQLCHAR sqlState[6];
        SQLCHAR message[256];
        SQLINTEGER nativeError;
        SQLSMALLINT messageLen;

        // Retrieve diagnostic information
        SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlState, &nativeError, message, sizeof(message), &messageLen);

        std::cerr << "Error executing SQL statement:" << std::endl;
        std::cerr << "SQL State: " << sqlState << std::endl;
        std::cerr << "Error Message: " << message << std::endl;

        throw std::runtime_error("Failed to execute SQL statement.");
    }

    // Cleanup
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
}



Database::~Database() {
    // free handles and disconnect from database
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}




template <typename T>
void analyzeType(T t) {
    
    // is string -> insert into strings

    // is bool -> insert into bools

    //is int -> insert into ints
}