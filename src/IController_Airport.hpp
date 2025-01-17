#pragma once

class IControlAirport{
    public:
        virtual void checkDemands() = 0;
};

class IControllRemoveFlight {
    public:
        virtual void removeFlight(int indicator, shared_ptr<Flight>flight) = 0;
};