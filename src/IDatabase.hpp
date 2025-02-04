#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Airport.hpp"

using std::vector, std::string, std::shared_ptr, std::make_shared;


class IDatabase{
    public:
        
        virtual vector<shared_ptr<Airport>> pullAirports() = 0;

        virtual vector<shared_ptr<Flight>> pullFlights() = 0;

        virtual void push(string table, vector<string>values) = 0;

        virtual void update(string table, vector<string>values) = 0;
        virtual ~IDatabase() = default;
};