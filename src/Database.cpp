#pragma once

#include "Database.hpp"
#include <map>
#include <iostream>

using std::endl, std::cout, std::multimap;


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
vector<shared_ptr<Airport>> Database::pull() {
    
    vector<shared_ptr<Airport>>airports;
    
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Failed to allocate statement handle.");
    }

    
    // preparing sql query
    std::string SqlQuery = "SELECT * FROM Flights";
    
    ret = SQLPrepare(hStmt, (SQLCHAR*)SqlQuery.c_str(), SQL_NTS);
    
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Failed to prepare SQL SELECT statement.");
    }


    // executing query, if not success then print all diagnosis info
    ret = SQLExecute(hStmt);
    if (!SQL_SUCCEEDED(ret)) {
        SQLCHAR sqlState[6];
        SQLCHAR message[256];
        SQLINTEGER nativeError;
        SQLSMALLINT messageLen;

        SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlState, &nativeError, message, sizeof(message), &messageLen);

        std::cerr << "Error executing SELECT statement:" << std::endl;
        std::cerr << "SQL State: " << sqlState << std::endl;
        std::cerr << "Error Message: " << message << std::endl;

        throw std::runtime_error("Failed to execute SELECT statement.");
    }


    // pulling all flights
    vector<shared_ptr<Flight>>flights;

    SQLCHAR buffer[256]{};
    while (SQLFetch(hStmt) == SQL_SUCCESS) {

        vector<string>tempString;
        vector<int>tempInt;

        for (SQLUSMALLINT i = 1; i <= 8; ++i) {
            ret = SQLGetData(hStmt, i, SQL_C_CHAR, buffer, sizeof(buffer), NULL);
            if (!SQL_SUCCEEDED(ret)) {
                throw std::runtime_error("Failed to retrieve data.");
            }
            
            if (i == 1 || i == 8) {
                tempInt.push_back(reinterpret_cast<int>(buffer));
            }
            else {
                tempString.push_back(reinterpret_cast<char*>(buffer));
            }

        }
        

        // conversion to flight

        shared_ptr<Flight>flight(new Flight(tempInt[0], tempString[1], tempString[2], tempString[3], tempString[4], tempString[5], tempString[6], tempInt[7]));

        flights.push_back(flight);
        
    }
    // at this level, we have all flights with are in database


    // pobieranie lotnisk

    // preparing sql query
    std::string SqlQuery = "SELECT * FROM Airports";

    ret = SQLPrepare(hStmt, (SQLCHAR*)SqlQuery.c_str(), SQL_NTS);

    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Failed to prepare SQL SELECT statement.");
    }


    // executing query, if not success then print all diagnosis info
    ret = SQLExecute(hStmt);
    if (!SQL_SUCCEEDED(ret)) {
        SQLCHAR sqlState[6];
        SQLCHAR message[256];
        SQLINTEGER nativeError;
        SQLSMALLINT messageLen;

        SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlState, &nativeError, message, sizeof(message), &messageLen);

        std::cerr << "Error executing SELECT statement:" << std::endl;
        std::cerr << "SQL State: " << sqlState << std::endl;
        std::cerr << "Error Message: " << message << std::endl;

        throw std::runtime_error("Failed to execute SELECT statement.");
    }


 
    // pulling all airports
    buffer[256] = 0;

    while (SQLFetch(hStmt) == SQL_SUCCESS) {

        vector<string>tempString;
        vector<int>tempInt;

        for (SQLUSMALLINT i = 1; i <= 9; ++i) {
            ret = SQLGetData(hStmt, i, SQL_C_CHAR, buffer, sizeof(buffer), NULL);
            if (!SQL_SUCCEEDED(ret)) {
                throw std::runtime_error("Failed to retrieve data.");
            }

            if (i == 1 || i == 3) {
                tempInt.push_back(reinterpret_cast<int>(buffer));
            }
            else {
                tempString.push_back(reinterpret_cast<char*>(buffer));
            }

        }

        // tempString = {AirportName, DeparturesIds, ArrivalIds, parkedIds, departureDemands, arrivalDemands, parkDemands }

        vector<shared_ptr<Flight>> parked;
        priority_queue<shared_ptr<Flight>>arrivals{}, departures{}, temp{};
        multimap<int, shared_ptr<Flight>>demands{};

        // get Departures
        
        {
            string idString;
            for (char c : tempString[1]) {
                if (c == ',') {

                    shared_ptr<Flight>flight = findFlight(std::stoi(idString), flights);

                    temp.push(flight);

                    idString = "";
                }
                else {

                    idString.push_back(c);

                }
            }
        }

        departures = inverse(temp);



        // get Arrivals
        {
            string idString;
            for (char c : tempString[2]) {
                if (c == ',') {

                    shared_ptr<Flight>flight = findFlight(std::stoi(idString), flights);

                    temp.push(flight);

                    idString = "";
                }
                else {

                    idString.push_back(c);

                }
            }
        }

        arrivals = inverse(temp);


        // get parked
        
            string idString{};
            for (char c : tempString[3]) {

                if (c == ',') {

                    shared_ptr<Flight>flight = findFlight(std::stoi(idString), flights);

                    parked.push_back(flight);

                    idString = "";
                }
                else {

                    idString.push_back(c);

                }

            }
        


       // get Demands 
        for (char c : tempString[4]) {
            if (c == ',') {

                shared_ptr<Flight>flight = findFlight(std::stoi(idString), flights);

                demands.insert(pair<int, shared_ptr<Flight>>(1, flight));

                idString = "";
            }
            else {

                idString.push_back(c);

            }     
        }

        for (char c : tempString[5]) {
            if (c == ',') {

                shared_ptr<Flight>flight = findFlight(std::stoi(idString), flights);

                demands.insert(pair<int, shared_ptr<Flight>>(-1, flight));

                idString = "";
            }
            else {

                idString.push_back(c);

            }
        }

        for (char c : tempString[6]) {
            if (c == ',') {

                shared_ptr<Flight>flight = findFlight(std::stoi(idString), flights);

                demands.insert(pair<int, shared_ptr<Flight>>(0, flight));

                idString = "";
            }
            else {

                idString.push_back(c);

            }
        }
                                               // id       name         capacity                                | 
        shared_ptr<Airport>airport(new Airport(std::to_string(tempInt[0]),tempString[0],tempInt[1],departures, arrivals, parked, demands));
        airports.push_back(airport);

    }

    return airports;
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



// invert queue

static priority_queue<shared_ptr<Flight>> inverse(priority_queue<shared_ptr<Flight>>& obj) {
    priority_queue<shared_ptr<Flight>> temp1, temp2 = obj;

    while (!temp2.empty()) {
        temp1.push(temp2.top());
        temp2.pop();
    }

    return temp1;

}

static shared_ptr<Flight> findFlight(int id, vector<shared_ptr<Flight>>flights) {
    for (shared_ptr<Flight>flight : flights) {
        if (flight->getId() == id) {
            return flight;
        }
    }
}


template <typename T>
void analyzeType(T t) {
    
    // is string -> insert into strings

    // is bool -> insert into bools

    //is int -> insert into ints
}