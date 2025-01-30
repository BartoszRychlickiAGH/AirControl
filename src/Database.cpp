#pragma once

#include "Database.hpp"
#include <map>
#include <iostream>
#include <string>

using std::endl, std::cout, std::multimap;

Database::Database()
{

    // Allocate environment handle
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

    // Allocate connection handle
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Connect to the database
    SQLCHAR connStr[] = "Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\ProjectModels;Database=AirControl;Trusted_Connection=yes;";
    ret = SQLDriverConnect(hDbc, NULL, connStr, SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

    if (!SQL_SUCCEEDED(ret)) {
        string error{ "cannot connect to database" };
        throw error;
    }
}



// methods inherited from interfaces 

static shared_ptr<Flight> findFlight(int id, vector<shared_ptr<Flight>>flights);
static priority_queue<shared_ptr<Flight>> inverse(priority_queue<shared_ptr<Flight>>& obj);

// pull data from database


// pulling all flights from database
vector<shared_ptr<Flight>> Database::pullFlights() {
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
    vector<shared_ptr<Flight>>flights{};

    SQLCHAR buffer[256]{};
    while (SQLFetch(hStmt) == SQL_SUCCESS) {

        vector<string>tempString;
        vector<int>tempInt;

        for (SQLUSMALLINT i = 1; i <= 8; ++i) {
            ret = SQLGetData(hStmt, i, SQL_C_CHAR, buffer, sizeof(buffer), NULL);
            if (!SQL_SUCCEEDED(ret)) {
                throw std::runtime_error("Failed to retrieve data.");
            }

            if (i == 1) {
                string temp_String{ reinterpret_cast<char*>(buffer) };

                int temp{ std::stoi(temp_String) };

                tempInt.push_back(temp); // correct casting
            }
            else if (i == 8) {

                string temp_String{ reinterpret_cast<char*>(buffer) };

                int temp{ std::stoi(temp_String) };

                tempInt.push_back(temp);


            }
            else {
                tempString.push_back(reinterpret_cast<char*>(buffer));
            }

        }


        // conversion to flight

        shared_ptr<Flight>flight(new Flight(tempInt[0], tempString[0], tempString[1], tempString[2], tempString[3], tempString[4], tempString[5], tempInt[1]));

        flights.push_back(flight);

    }

    return flights;

}





vector<shared_ptr<Airport>> Database::pullAirports() {
    
    vector<shared_ptr<Airport>>airports{};
    SQLCHAR buffer[256]{};
    std::string SqlQuery;

    
    vector<shared_ptr<Flight>>flights{ pullFlights() };

    // downloading all airports

    ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

    // preparing sql query
    std::string new_SqlQuery = "SELECT * FROM Airports";

    ret = SQLPrepare(hStmt, (SQLCHAR*)new_SqlQuery.c_str(), SQL_NTS);

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

    while (SQLFetch(hStmt) == SQL_SUCCESS) {

        vector<string>tempString;
        vector<int>tempInt;

        for (SQLUSMALLINT i = 1; i <= 9; ++i) {
            ret = SQLGetData(hStmt, i, SQL_C_CHAR, buffer, sizeof(buffer), NULL);
            if (!SQL_SUCCEEDED(ret)) {
                throw std::runtime_error("Failed to retrieve data.");
            }

            

            if (i == 1 || i == 3) {
                string tempText{};

                
                for (SQLCHAR c : buffer) {
                    if (c == '\0') {
                        break;
                    }
                    else {
                        tempText.push_back(static_cast<char>(c));
                    }
                }

                tempInt.push_back(std::stoi(tempText));
            }
            else {
                string tempText{""};
                for (SQLCHAR c : buffer) {

                    if (c == '\0') {

                        break;
                    }
                    else {
                        
                        
                        tempText.push_back(static_cast<char>(c));
                    }
                }

                tempString.push_back(tempText);
            }

        }

        // tempString = {AirportName, DeparturesIds, ArrivalIds, parkedIds, departureDemands, arrivalDemands, parkDemands }

        vector<shared_ptr<Flight>> parked;
        priority_queue<shared_ptr<Flight>>arrivals{}, departures{}, temp{};
        multimap<int, shared_ptr<Flight>>demands{};

        // get Departures
        string idString{};
        
        if (tempString[1] != "none") {
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


            departures = inverse(temp);
        }
        else {
            departures = {};
        }

        
        // reset variables
        int size = temp.size();

        for (int i = 0; i < size; ++i) {
            temp.pop();
        }

        idString = "";

        if (tempString[2] != "none") {
            // get Arrivals
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
            arrivals = inverse(temp);
        }
        else {
            arrivals = {};
        }


        // get parked
        if (tempString[3] != "none") {
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
        }
        else {
            parked = {};
        }


       // get Demands 
        
        if (tempString[4] != "none") {
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
        }
        else {
            demands = {};
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
    string SqlQuery;

    if (table == "Flights") {
        // insert Flights

        SqlQuery = "INSERT INTO " + table + " (Base,Destination, PlaneName, FlightDate, DepartureTime, ArrivalTime, DemandIndicator) VALUES (?,?,?,?,?,?,?)";

        SQLPrepare(hStmt, (SQLCHAR*)SqlQuery.c_str(), SQL_NTS);

        // parameters
        size_t i{ 0 }; // indicator of param
        for (const string& s : values) {
            if (i == 7) { // if s is a demandIndicator then insert as int type
                SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(i + 1), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, s.size(), 0, (SQLINTEGER*)std::stoi(s), 0, NULL);
                break;
            }

            SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(i + 1), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, s.size(), 0, (SQLCHAR*)s.c_str(), 0, NULL); // inserting param instead of ? in sql query
            i++; // increment indicator to add new param
        }

        // adding flight to correct airports


    }
    else {
        
        
        // sql query
        SqlQuery = "INSERT INTO " + table + " (AirportName,Capacity, DepartureIds, ArrivalIds, parkedIds, departureDemands, arrivalDemands, parkDemands) VALUES (?,?,?,?,?,?,?,?)";

        SQLPrepare(hStmt, (SQLCHAR*)SqlQuery.c_str(), SQL_NTS);

        // parameters
        size_t i{ 0 }; // indicator of param
        for (const string& s : values) {


            if (i == 1) { // if s is a current element in values then insert as int type
                try {
                    int temp = std::stoi(s);

                    SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(i), SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &temp, 0, NULL);

                    
                    
                }
                catch (const std::exception& e) {
                    std::cerr << "Error converting string to integer: " << e.what() << std::endl;
                    throw;
                };
            }
            else {

                
                SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(i), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, s.size(), 0, (SQLCHAR*)s.c_str(), 0, NULL);
                
                
            } 
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

void Database::update(string table, vector<string> values) {
    if (values.empty()) {
        throw std::invalid_argument("Values vector cannot be empty.");
    }

    // Allocate statement handle
    SQLRETURN ret;
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    string SqlQuery;

    if (table == "Flights") {
        // Update flights
        // values = [Base, Destination, PlaneName, FlightDate, DepartureTime, ArrivalTime, DemandIndicator, FlightId]

        if (values.size() < 8) {
            throw std::invalid_argument("Insufficient values for updating Flights table.");
        }

        SqlQuery = "UPDATE Flights SET Base = ?, Destination = ?, PlaneName = ?, FlightDate = ?, "
            "DepartureTime = ?, ArrivalTime = ?, DemandIndicator = ? WHERE FlightId = ?";

        SQLPrepare(hStmt, (SQLCHAR*)SqlQuery.c_str(), SQL_NTS);

        // Bind parameters
        SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)values[0].c_str(), 0, NULL); // Base
        SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)values[1].c_str(), 0, NULL); // Destination
        SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)values[2].c_str(), 0, NULL); // PlaneName
        SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)values[3].c_str(), 0, NULL); // FlightDate
        SQLBindParameter(hStmt, 5, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)values[4].c_str(), 0, NULL); // DepartureTime
        SQLBindParameter(hStmt, 6, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLCHAR*)values[5].c_str(), 0, NULL); // ArrivalTime

        int demandIndicator = std::stoi(values[6]);
        int flightId = std::stoi(values[7]);
        SQLBindParameter(hStmt, 7, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &demandIndicator, 0, NULL); // DemandIndicator
        SQLBindParameter(hStmt, 8, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &flightId, 0, NULL);        // FlightId


    }else {
        // update airports


        // values = [AirportName, Capacity, DepartureIds, ArrivalIds, parkedIds, departureDemand, arrivalDemand, parkDemand, airportId]

        SqlQuery = "UPDATE Airports SET AirportName = ?, Capacity = ?, DepartureIds = ?, ArrivalIds = ?, "
        "ParkedIds = ?, departureDemands = ?, arrivalDemands = ?, parkDemands = ? WHERE AirportId = ?";

        SQLPrepare(hStmt, (SQLCHAR*)SqlQuery.c_str(), SQL_NTS);

        int temp = std::stoi(values[1]);
        int tempId = std::stoi(values[8]);


        SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(1), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER*)values[0].c_str(), 0, NULL); // AirportName
        SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(2), SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &temp, 0, NULL);                         // Capacity
        SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(3), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER*)values[2].c_str(), 0, NULL); // DepartureIds
        SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(4), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER*)values[3].c_str(), 0, NULL); // ArrivalIds
        SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(5), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER*)values[4].c_str(), 0, NULL); // ParkedIds
        SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(6), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER*)values[5].c_str(), 0, NULL); // DepartureDemand
        SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(7), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER*)values[6].c_str(), 0, NULL); // ArrivalDemand
        SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(8), SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 0, 0, (SQLPOINTER*)values[7].c_str(), 0, NULL); // ParkDemand
        SQLBindParameter(hStmt, static_cast<SQLUSMALLINT>(9), SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &tempId, 0, NULL);

    }

    ret = SQLExecute(hStmt); // execute query

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



//// in case of have a need to compare types
//template <typename T>
//void analyzeType(T t) {
//    
//    // is string -> insert into strings
//    if (T.typeId(string)) {
//        
//    }else if(T.typeId)
//
//
//    // is bool -> insert into bools
//
//    //is int -> insert into ints
//}