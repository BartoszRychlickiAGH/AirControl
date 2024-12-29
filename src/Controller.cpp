#pragma once

#include "Controller.hpp"
#include "validation.hpp"


// function below is made to print use display() function by exact member of priority_queue
static void printFlight_queue(int i, priority_queue<shared_ptr<Flight>>flights) {
    priority_queue<shared_ptr<Flight>> temp = flights;

    for (int j = 0; j <= flights.size() - 1; ++j) {
        if (j == i) {
            temp.top()->display();
            return;
        }
        else {
            temp.pop();
        }
    }
}



//constructor
Controller::Controller(shared_ptr<Airport>p_airport):
    airport_(p_airport)
{}


//methods inherited from interface
void Controller::changeAirport(vector<shared_ptr<Airport>>airports) {
    // orint airport
    string i = 0;
    for(shared_ptr<Airport>airport : airports) {
        cout << airport->getAirportName() << endl;
    }
    // make user to choose airport
    do{
        cout << "Choose airport: | To cancel operation enter: -1" << endl;
        cin >> i;

        if (i == "-1") {
            return;
        }
    }while(!Validation::isnumber(i) and Validation::isInRange(std::stoi(i)-1, 0, airports.size()));

    // set airport by assigning chosen one to class variable
    setAirport(airports[std::stoi(i)-1]);
}
void Controller::printFlight() {
    // print all flights in general way
    airport_->display();    
    string i = 0;
    string mode{};
    // make user to choose flight
    do{
        do{
        cout << "Choose mode: (arrivals/departure/parked)| To cancel operation enter: -1" << endl;
        cin >> mode;
        }while(!Validation::istext(mode) and !Validation::checkFlightMode(mode));
        
        cout << "Choose flight: | To cancel operation enter: -1" << endl;
        cin >> i;
        
        // check if given index of flight exist in container of flights for given mode
        if (mode == "parked" and std::stoi(i) >= airport_->getParkedids().size()) {
        
            cout << "Picked wrong index of flight in parked ones" << endl;
            continue;
        
        }else if (mode == "departure" and std::stoi(i) >= airport_->getDepartureids().size()) {
        
            cout << "Picked wrong index of flight in departure ones" << endl;
            continue;
        
        }else if (mode == "arrival" and std::stoi(i) >= airport_->getArrivalsids().size()) {
            
            cout << "Picked wrong index of flight in arrival ones" << endl;
            continue;

        }

        if(i == "-1") {
            return;
        }
    }while(!Validation::isnumber(i) and Validation::isInRange(std::stoi(i)-1, 0, airport_->getDepartureids().size()));
    
    // print chosen flight
    if(mode == "arrival"){
        printFlight_queue(std::stoi(i) - 1,airport_->getArrivalsids());
    }else if(mode == "departure"){
        printFlight_queue(std::stoi(i) - 1, airport_->getDepartureids());
    }else if(mode == "parked"){
        airport_->getParkedids()[std::stoi(i)-1]->display();
    }
}
void Controller::addFlight() {
    // make user to input all necessary data
    
    // create new flight

    // check if given departure time nor arrival time is already taken

    // check if airport of given name exist

    // check if given date is correct (given date cannot be less than 1.1.2025)

    // add flight to airport

}
void Controller::removeFlight() {
    // print all flights in general way

    // make user to choose flight

    // remove chosen flight

}
void Controller::editFlight() {
    // print all flights in general way

    // make user to choose flight

    // make user to input all necessary data

    // edit chosen flight

}
void Controller::checkCollision() {
    // check all flights for collision

    // check if any flight has the same arrival or departure time | includ time delay for arrivals and departures

    // if collision found print it

}
void Controller::grantDemand() {
    // if any collision found print it

    // otherwise grant demands by adding flights to airport's vectors and changing flight's indicator, remove from demands

}
void Controller::checkDemands() {
    // check airport for demands

    // print all demands

}

//setters and getters
void Controller::setAirport(shared_ptr<Airport>p_airport) { airport_ = p_airport; }
shared_ptr<Airport> Controller::getAirport(void) const { return airport_; }
