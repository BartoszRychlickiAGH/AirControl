#pragma once

#include "IAirport.hpp"
#include "IPrint.hpp"
#include "Flight.hpp"
#include <vector>
#include <memory>
#include <map>
#include <queue>

using std::vector, std::shared_ptr, std::make_shared, std::multimap, std::pair, std::priority_queue;

class Airport : public IAirport, public IPrint{
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
        Airport(string p_id, string p_name, int p_capacity, priority_queue<shared_ptr<Flight>>p_dep_ids = {}, priority_queue<shared_ptr<Flight>>p_arr_ids = {}, vector<shared_ptr<Flight>>p_park_ids = {}, multimap<int, shared_ptr<Flight>>p_pendingDemands = {});
     
        // methods inherited from interfaces
        void display() override;
        bool isFull() override;
        void displayDepartures() override;
        void displayArrivals() override;
        void displayParked() override;

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