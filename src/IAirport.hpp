#pragma once

#include <memory>
#include "Flight.hpp"
#include <queue>

using std::priority_queue, std::shared_ptr;

class IAirport{
    public:
        virtual bool isFull() = 0;
        virtual void displayDepartures() = 0;
        virtual void displayArrivals() = 0;
        virtual void displayParked() = 0;
        virtual void addFlight(shared_ptr<Flight>flight) = 0;
        

};