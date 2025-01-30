#pragma once

#include "IFlight.hpp"
#include "IPrint.hpp"
#include "ICompress.hpp"

#include <string>
#include <iostream>
#include <memory>

using std::string, std::cin, std::endl, std::cout, std::shared_ptr;

class Flight : public IFlight, public IPrint, public ICompress{
    private:
        int id_{};
        string base_{};
        string destination_{};
        string planeName_{};
        string flightDate_{};
        string departureTime_{};
        string arrivalTime_{};
        int demandIndicator{-255}; // 0 - none demand | -1 - arrival demand | 1 - departure demand  | 255 - access granted ( waiting for another demand)
    public:
        // constructor
        Flight(int p_id, string p_base = "", string p_destination = "", string p_planeName = "", string p_flightDate = "", string p_departureTime = "", string p_arrivalTime = "", int p_demand = -255) :
            id_(p_id),
            base_(p_base),
            destination_(p_destination),
            planeName_(p_planeName),
            flightDate_(p_flightDate),
            departureTime_(p_departureTime),
            arrivalTime_(p_arrivalTime),
            demandIndicator(p_demand)
        {}

        // methods inherited from interfaces
        void display() override;
        void departure() override;
        void arrival() override;
        vector<string> compress() override;

        // getters and setters

        int getId(void) const;               void setId(int p_Id);
        string getBase(void)const;           void setBase(string p_Base);
        string getDestination(void) const;   void setDestination(string p_Destination);
        string getPlaneName(void) const;     void setPlaneName(string p_PlaneName);
        string getFlightDate(void) const;    void setFlightDate(string p_FlightDate);
        string getDepartureTime(void) const; void setDepartureTime(string p_DepartureTime);
        string getArrivalTime(void) const;   void setArrivalTime(string p_ArrivalTime);
        int getDemandIndicator(void) const;  void setdemandIndicator(int p_demandIndicator);


        bool operator==(const shared_ptr<Flight>& obj);
        void operator=(const shared_ptr<Flight>& obj);

};