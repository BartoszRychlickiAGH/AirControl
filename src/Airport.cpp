#include "Airport.hpp"


Airport::Airport(string p_id, string p_name, int p_capacity, vector<shared_ptr<Flight>>p_dep_ids,vector<shared_ptr<Flight>>p_arr_ids, vector<shared_ptr<Flight>>p_park_ids){}

// methods inherited from interfaces
void Airport::display() {
    cout << "Airport Id: " << id_ << " | Name: "<< name_ << endl;
    cout << "Taken parking slots: " << parked_.size() << "/" << capacity_ << endl;
    displayDepartures();
    displayArrivals();
    displayParked();
}
bool Airport::isFull() { 
    return (parked_.size() < capacity_)? false: true;
}

void Airport::displayDepartures() {
    cout << "Departures: | ";
    for(shared_ptr<Flight>flight : departures_){
        cout << "Flight " << flight->getId() << "(" << flight->getDepartureTime() << ") | ";
    }
    cout << endl;
}
void Airport::displayArrivals() {
    cout << "Arrivals: | ";
    for(shared_ptr<Flight>flight : departures_){
        cout << "Flight " << flight->getId() << "(" << flight->getArrivalTime() << ") | ";
    }
    cout << endl;
}
void Airport::displayParked() {
    cout << "Parked: | ";
    for(shared_ptr<Flight>flight : departures_){
        cout << "Flight " << flight->getId() << " | ";
    }
    cout << endl;
}



// getters
string Airport::getAirportId(void) const{ return id_;}
string Airport::getAirportName(void) const{ return name_;}
int Airport::getCapacity(void) const{ return capacity_;}
vector<shared_ptr<Flight>> Airport::getDepartureids(void) const{ return departures_;}
vector<shared_ptr<Flight>> Airport::getArrivalsids(void) const{ return arrivals_;}
vector<shared_ptr<Flight>> Airport::getParkedids(void) const{ return parked_;}

// setters
void Airport::setId(string p_id){ id_ = p_id; }
void Airport::setName(string p_name){ name_ = p_name;}
void Airport::setCapacity(int p_capacity) { capacity_ = p_capacity;  }
void Airport::setDepartures(vector<shared_ptr<Flight>>p_dep_ids){ departures_ = p_dep_ids; }
void Airport::setArrivals(vector<shared_ptr<Flight>>p_arr_ids){ arrivals_ = p_arr_ids; }
void Airport::setParked(vector<shared_ptr<Flight>>p_park_ids){ parked_ = p_park_ids;}