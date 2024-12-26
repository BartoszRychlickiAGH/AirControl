#pragma once

#include "IAirport.hpp"
#include "IPrint.hpp"
#include <vector>

using std::vector;

class Airport : public IAirport, public IPrint{
    private:
        string id_{};
        string name_{;}
        int capacity_{};
        vector<string>departures_ids{};
        vector<string>arrivals_ids{};
        vector<string>parked_ids{};
    public:
        // constructor
        Airport(string p_id, string p_name, int p_capacity, vector<string>p_dep_ids = {},vector<string>p_arr_ids = {}, vector<string>p_park_ids = {});
     
        // methods inherited from interfaces
        void display() override;
        bool departuresCollision() override;
        bool arrivalsCollision() override;
        bool isEmpty() override;

        // getters
        string getAirportId(void) const;
        string getAirportName(void) const;
        int getCapacity(void) const;
        vector<string> getDepartureids(void) const;
        vector<string> getArrivalsids(void) const;
        vector<string> getParkedids(void) const;

        // setters
        void setId(string p_id);
        void setName(string p_name);
        void seyCapacity(int p_capacity);
        void setDeparturesIds(vector<string>p_dep_ids);
        void setArrivalsIds(vector<string>p_arr_ids);
        void setParkedIds(vector<string>p_park_ids);
};