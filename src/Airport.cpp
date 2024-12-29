#include "Airport.hpp"


Airport::Airport(string p_id, string p_name, int p_capacity, priority_queue<shared_ptr<Flight>>p_dep_ids,priority_queue<shared_ptr<Flight>>p_arr_ids, vector<shared_ptr<Flight>>p_park_ids, multimap<int,shared_ptr<Flight>>p_pendingDemands):
id_(p_id),
name_(p_name),
capacity_(p_capacity),
departures_(p_dep_ids),
arrivals_(p_arr_ids),
parked_(p_park_ids),
pendingDemands(p_pendingDemands)
{}

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
    int i = 0;
    cout << "Departures: | ";
    priority_queue<shared_ptr<Flight>> temp = departures_;
    while (!temp.empty()) {
        shared_ptr<Flight> flight = temp.top();
        cout << i<<". Flight " << flight->getId() << "(" << flight->getDepartureTime() << ") | ";
        temp.pop();
        ++i;
    }
    cout << endl;
}

void Airport::displayArrivals() {
    int i = 0;
    cout << "Arrivals: | ";
    priority_queue<shared_ptr<Flight>> temp = arrivals_;
    while (!temp.empty()) {
        shared_ptr<Flight> flight = temp.top();
        cout << i << ". Flight " << flight->getId() << "(" << flight->getArrivalTime() << ") | ";
        temp.pop();
        ++i;
    }
    cout << endl;
}
void Airport::displayParked() {
    int i = 0;
    cout << "Parked: | ";
    for(shared_ptr<Flight>flight : parked_){
        cout << i << ". Flight " << flight->getId() << " | ";
        ++i;
    }
    cout << endl;
}

void Airport::addFlight(shared_ptr<Flight>flight){
    if(flight->getBase() == name_){
        departures_.push(flight);
    }else if(flight->getDestination() == name_){
        arrivals_.push(flight);
    }
}

// getters
string Airport::getAirportId(void) const{ return id_;}
string Airport::getAirportName(void) const{ return name_;}
int Airport::getCapacity(void) const{ return capacity_;}
priority_queue<shared_ptr<Flight>> Airport::getDepartureids(void) const{ return departures_;}
priority_queue<shared_ptr<Flight>> Airport::getArrivalsids(void) const{ return arrivals_;}
vector<shared_ptr<Flight>> Airport::getParkedids(void) const{ return parked_;}
multimap<int,shared_ptr<Flight>> Airport::getPendingDemands(void) const {return pendingDemands; }

// setters
void Airport::setId(string p_id){ id_ = p_id; }
void Airport::setName(string p_name){ name_ = p_name;}
void Airport::setCapacity(int p_capacity) { capacity_ = p_capacity;  }
void Airport::setDepartures(priority_queue<shared_ptr<Flight>>p_dep_ids){ departures_ = p_dep_ids; }
void Airport::setArrivals(priority_queue<shared_ptr<Flight>>p_arr_ids){ arrivals_ = p_arr_ids; }
void Airport::setParked(vector<shared_ptr<Flight>>p_park_ids){ parked_ = p_park_ids;}
void Airport::setPendingDemands(multimap<int,shared_ptr<Flight>>p_pendingDemands) {pendingDemands = p_pendingDemands;}