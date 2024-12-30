#pragma once

#include "IController.hpp"
#include "IController_Airport.hpp"
#include "Airport.hpp"

class Controller : public IController, public IControlAirport{
    private:
        shared_ptr<Airport>airport_;
        vector<shared_ptr<Airport>>airports_;
    public:
        //constructor
        Controller(shared_ptr<Airport>p_airport = nullptr, vector<shared_ptr<Airport>>p_airports = {});

        //methods inherited from interface
        void changeAirport() override;
        void printFlight() override;
        void addFlight() override;
        void removeFlight() override;
        void editFlight() override;
        bool checkCollision(shared_ptr<Flight>flight) override;
        void grantDemand() override;
        void checkDemands() override;

        //setters and getters
        void setAirport(shared_ptr<Airport>p_airports);
        shared_ptr<Airport> getAirport(void) const;

        void setAirports(vector<shared_ptr<Airport>>p_airports);
        vector<shared_ptr<Airport>> getAirports(void) const;

};