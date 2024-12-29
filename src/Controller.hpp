#pragma once

#include "IController.hpp"
#include "Airport.hpp"

class Controller : public IController{
    private:
        shared_ptr<Airport>airport_;
    public:
        //constructor
        Controller(shared_ptr<Airport>p_airport = nullptr);

        //methods inherited from interface
        void changeAirport(vector<shared_ptr<Airport>>airports) override;
        void printFlight() override;
        void addFlight() override;
        void removeFlight() override;
        void editFlight() override;
        void checkCollision() override;
        void grantDemand() override;
        void checkDemands() override;

        //setters and getters
        void setAirport(shared_ptr<Airport>p_airports);
        shared_ptr<Airport> getAirport(void) const;

};