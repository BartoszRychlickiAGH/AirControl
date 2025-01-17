#pragma once

#include "IAirport.hpp"
#include "IController_Airport.hpp"
#include "IPrint.hpp"
#include "Flight.hpp"

#include <map>
#include <queue>

using std::multimap, std::pair, std::priority_queue;

class Airport : public IAirport, public IPrint, public IControlAirport, public IPrintAirport, public ICompress{
    private:
        string id_{};
        string name_{};
        int capacity_{};
        priority_queue<shared_ptr<Flight>>departures_{};
        priority_queue<shared_ptr<Flight>>arrivals_{};
        vector<shared_ptr<Flight>>parked_{};
        multimap<int,shared_ptr<Flight>>pendingDemands{};

    public:
        // constructor
        Airport(string p_id = "", string p_name = "", int p_capacity = 0, priority_queue<shared_ptr<Flight>>p_dep_ids = {}, priority_queue<shared_ptr<Flight>>p_arr_ids = {}, vector<shared_ptr<Flight>>p_park_ids = {}, multimap<int, shared_ptr<Flight>>p_pendingDemands = {});
     
        // methods inherited from interfaces
        void display() override;
        bool isFull() override;
        void displayDepartures() override;
        void displayArrivals() override;
        void displayParked() override;
        void addFlight(shared_ptr<Flight>flight) override;
        void checkDemands() override;
        void display(string mode) override;
        vector<string> compress() override;


        // getters
        string getAirportId(void) const;
        string getAirportName(void) const;
        int getCapacity(void) const;
        priority_queue<shared_ptr<Flight>> getDepartureids(void) const;
        priority_queue<shared_ptr<Flight>> getArrivalsids(void) const;
        vector<shared_ptr<Flight>> getParkedids(void) const;
        multimap<int,shared_ptr<Flight>> getPendingDemands(void) const;

        // setters
        void setId(string p_id);
        void setName(string p_name);
        void setCapacity(int p_capacity);
        void setDepartures(priority_queue<shared_ptr<Flight>>p_dep_ids);
        void setArrivals(priority_queue<shared_ptr<Flight>>p_arr_ids);
        void setParked(vector<shared_ptr<Flight>>p_park_ids);
        void setPendingDemands(multimap<int,shared_ptr<Flight>>);
};