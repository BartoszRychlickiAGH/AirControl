#pragma once

#include "IFlight.hpp"
#include "IPrint.hpp"
#include <string>
#include <iostream>

using std::string, std::cin, std::endl, std::cout;


class Flight : public IFlight, public IPrint{
    private:
        string id_{};
        string base_{};
        string destination_{};
        string planeName_{};
        string flightDate_{};
        string departureTime_{};
        string arrivalTime_{};
    public:
        // constructor
        Flight(string p_id, string p_base, string p_destination, string p_planeName, string p_flightDate, string p_departureTime, string p_arrivalTime);

        // methods inherited from interfaces
        void display() override;
        void departure() override;
        void arrival() override;
        void park() override;

        // getters and setters

        string getId(void) const;            void setId(string p_Id);
        string getBase(void)const;           void setBase(string p_Base);
        string getDestination(void) const;   void setDestination(string p_Destination);
        string getPlaneName(void) const;     void setPlaneName(string p_PlaneName);
        string getFlightDate(void) const;    void setFlightDate(string p_FlightDate);
        string getDepartureTime(void) const; void setDepartureTime(string p_DepartureTime);
        string getArrivalTime(void) const;   void setArrivalTime(string p_ArrivalTime);

};