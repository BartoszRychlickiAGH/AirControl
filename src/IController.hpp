#pragma once

#include "Airport.hpp"


class IController{
    public:
        virtual void changeAirport() = 0;
        virtual void printFlight() = 0;
        virtual void addFlight() = 0;
        virtual void removeFlight() = 0;
        virtual void editFlight() = 0;
        virtual bool checkCollision(shared_ptr<Flight>flight) = 0;
        virtual void grantDemand() = 0;
        virtual void checkDemands() = 0;
};