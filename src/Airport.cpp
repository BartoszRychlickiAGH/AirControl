#include "Airport.hpp"
#include "validation.hpp"


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

// display parked flights
void Airport::displayParked() {
    int i = 0;
    cout << "Parked: | ";
    for(shared_ptr<Flight>flight : parked_){
        cout << i << ". Flight " << flight->getId() << " | ";
        ++i;
    }
    cout << endl;
}

// add new flight
void Airport::addFlight(shared_ptr<Flight>flight){
    if(flight->getBase() == name_){
        departures_.push(flight);
    }else if(flight->getDestination() == name_){
        arrivals_.push(flight);
    }
}

// check demands for all flights pinned to the airport
void Airport::checkDemands() {
    priority_queue<shared_ptr<Flight>>temp1 = departures_, temp2 = arrivals_,temp_dep,temp_arr;
    
    // for all flights in departure_ check
    for (int j = 0; j <= (int)fmax(departures_.size(), arrivals_.size()); j++) {
        if (j < departures_.size()) {
            
            // check if given demand exist ifn then add do pendingDemands
            
            if (Validation::isInMultimap(temp1.top()->getDemandIndicator(), temp1.top(), pendingDemands)) {
            
                pendingDemands.insert(std::make_pair(temp1.top()->getDemandIndicator(), temp1.top()));

            }

            if (temp1.top()->getDemandIndicator() == 1) {
                temp_dep.push(temp1.top());
            }

            temp1.pop();
        }
        if (j < arrivals_.size()) {
         
            // check if given demand exist ifn then add do pendingDemands
            if (Validation::isInMultimap(temp2.top()->getDemandIndicator(), temp2.top(), pendingDemands)) {

                pendingDemands.insert(std::make_pair(temp2.top()->getDemandIndicator(), temp2.top()));

            }

            if (temp2.top()->getDemandIndicator() == 1) {
                temp_arr.push(temp2.top());
            }

            temp2.pop();
        }
    }

    // updating arrivals_ and departure_
    arrivals_ = temp_arr;
    departures_ = temp_dep;


    
    // for all flights in parked_ check
    for (shared_ptr<Flight>flight : parked_) {
        
        // if flight is not in pendingDemands then

        if (!Validation::isInMultimap(flight->getDemandIndicator(), flight, pendingDemands)) {
            
            pendingDemands.insert(std::make_pair(flight->getDemandIndicator(), flight));

        }
    
    }

}

void Airport::display(string mode) {
    if(mode == "arrival" || mode == "Arrival"){
        displayArrivals();
    }else if(mode == "departure" || mode == "Departure"){
        displayDepartures();
    }else if(mode == "parked" || mode == "Parked"){
        displayParked();
    }else{
        displayArrivals();
        displayDepartures();
        displayParked();
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