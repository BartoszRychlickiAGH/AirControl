#pragma once
#include <queue>

using std::priority_queue;


class IControlAirport{
    public:
        virtual void checkDemands() = 0;
        virtual vector<shared_ptr<Flight>> pullFlights() = 0;
};

class IControllRemoveFlight {
    public:
        virtual void removeFlight(int indicator, shared_ptr<Flight>flight) = 0;     
};