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
Controller::Controller(shared_ptr<Airport>p_airport, vector<shared_ptr<Airport>>airports):
    airport_(p_airport),
    airports_(airports)
{}


//methods inherited from interface
void Controller::changeAirport() {
    // orint airport
    string i = 0;
    for(shared_ptr<Airport>airport : airports_) {
        cout << airport->getAirportName() << endl;
    }
    // make user to choose airport
    do{
        cout << "Choose airport: | To cancel operation enter: -1" << endl;
        cin >> i;

        if (i == "-1") {
            return;
        }
    }while(!Validation::isnumber(i) and Validation::isInRange(std::stoi(i)-1, 0, airports_.size()));

    // set airport by assigning chosen one to class variable
    setAirport(airports_[std::stoi(i)-1]);
}
void Controller::printFlight() {
    // print all flights in general way
    airport_->display();    
    string i;
    string mode{};
    // make user to choose flight
    do{
        do{
        cout << "Choose mode: (arrivals/departure/parked)| To cancel operation enter: -1" << endl;
        cin >> mode;
        }while(!Validation::istext(mode) and !Validation::checkFlightMode(mode));
        

        do {
            cout << "Choose flight: | To cancel operation enter: -1" << endl;
            cin >> i;

            if (!Validation::isnumber(i)) {
                cout << "Given number is not a decimal!" << endl;
            }
        } while (!Validation::isnumber(i));
    


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
    string id{};
    string base{};
    string destination{};
    string planeName{};
    string flightDate{};
    string departureTime{};
    string arrivalTime{};

    if(airport_ == nullptr) {

        cout << "No airport chosen" << endl;

        return;
    }

        cout << "Enter required data for new flight | To cancel operation enter: exit" << endl;
    do{

        cout << "Enter id: ";                     cin >> id;            if(id == "exit"){ return; }

    }while(!Validation::isnumber(id));

    do{

        cout << endl <<"Enter base: ";            cin >> base;          if(base == "exit"){ return; }

    }while(!Validation::istext(base));

    do{

        cout << endl << "Enter destination: ";    cin >> destination;   if(destination == "exit"){ return; }

    }while(!Validation::istext(destination));

    do{

        cout << endl << "Enter plane name: ";     cin >> planeName;    if(planeName == "exit"){ return; }

    }while(!Validation::istext(planeName));

    do{

        cout << endl << "Enter flight date: ";    cin >> flightDate;    if(flightDate == "exit"){ return; }

    }while(!Validation::isDate(flightDate));

    do{

        cout << endl << "Enter departure time: "; cin >> departureTime; if(departureTime == "exit"){ return; }

    }while(!Validation::isTime(departureTime));

    do{

        cout << endl <<"Enter arrival time: ";    cin >> arrivalTime;   if(arrivalTime == "exit"){ return; }

    }while(!Validation::isTime(arrivalTime));


    // create new flight
    shared_ptr<Flight> flight(new Flight(id, base, destination, planeName, flightDate, departureTime, arrivalTime));

    // check if given departure time nor arrival time is already taken
    if(checkCollision(flight)) {
        return;
    }


    // check if airport of given name exist
    if(!Validation::airportExist(getAirports(), base) and !Validation::airportExist(airports_, destination)) {

        cout << "Airport of given name don't exist" << endl;

        return;
    }



    // add flight to airport
    airport_->addFlight(flight);

}
void Controller::removeFlight() {
    string i{};
    string mode;

    // print all flights in general way
    airport_->display();


    // make user to choose flight
    do{
        do {

            cout << "Choose mode: (arrivals/departure/parked)| To cancel operation enter: -1" << endl;

            cin >> mode;

        } while (!Validation::istext(mode) and !Validation::checkFlightMode(mode));

        
        do {
            cout << "Choose flight: | To cancel operation enter: -1" << endl;

            cin >> i;

            if (!Validation::isnumber(i)){

                cout << "Given index is not a decimal!" << endl;

            }

        } while (!Validation::isnumber(i));



        // check if given index of flight exist in container of flights for given mode
        if (mode == "parked" and std::stoi(i) >= airport_->getParkedids().size()) {

            cout << "Picked wrong index of flight in parked ones" << endl;

            continue;

        }
        else if (mode == "departure" and std::stoi(i) >= airport_->getDepartureids().size()) {

            cout << "Picked wrong index of flight in departure ones" << endl;

            continue;

        }
        else if (mode == "arrival" and std::stoi(i) >= airport_->getArrivalsids().size()) {

            cout << "Picked wrong index of flight in arrival ones" << endl;

            continue;

        }

        if (i == "-1") {
            return;
        }
    }while (!Validation::isnumber(i) and Validation::isInRange(std::stoi(i) - 1, 0, airport_->getDepartureids().size()));


    if (mode == "arrival") {

        // remove flight from airport's arrivals
        
        priority_queue<shared_ptr<Flight>>temp1 = airport_->getArrivalsids(),temp2;
        for (int j = 0; j <= airport_->getArrivalsids().size(); ++j) {
            if (std::stoi(i)-1 != j) {

                temp2.push(temp1.top());
            
                temp1.pop();
            
            }
        
        }

        airport_->setArrivals(temp2);

    }
    else if (mode == "departure") {

        // remove flight from airport's departures
        priority_queue<shared_ptr<Flight>>temp1 = airport_->getDepartureids(), temp2;
        for (int j = 0; j <= airport_->getDepartureids().size(); ++j) {
            if (std::stoi(i) - 1 != j) {

                temp2.push(temp1.top());
            
            }

            temp1.pop();
        }

        airport_->setDepartures(temp2);


    }
    else if (mode == "parked") {

        // delete flight from airport's parked objects
        vector<shared_ptr<Flight>>temp1 = airport_->getParkedids(), temp2;

        for (int j = 0; j <= airport_->getParkedids().size(); ++j) {
            if (std::stoi(i) != j) {
                    
                temp2[j] = temp1[std::stoi(i) - 1];


            }
        
        }
        
    }

}
void Controller::editFlight() {
    // print all flights in general way

    // make user to choose flight

    // make user to input all necessary data

    // edit chosen flight

}
bool Controller::checkCollision(shared_ptr<Flight>flight) {
    int i = 0;
    bool collision{false};
    priority_queue<shared_ptr<Flight>>temp = airport_->getArrivalsids();

    // check all flights for collision
    for (int j = 0; j <= airport_->getArrivalsids().size(); ++j) {

        if(flight->getArrivalTime() == temp.top()->getArrivalTime()) {
            ++i;
            
            cout << i << ". Collision:" << endl;
            cout << "Flight: " << temp.top()->getId() << " and Flight" << flight->getId() << endl << endl;
            
            collision = true;
        }
        temp.pop();
    }

    temp = airport_->getDepartureids();

    for(int j = 0; j <= airport_->getDepartureids().size(); ++j) {
        if(flight->getDepartureTime() == temp.top()->getDepartureTime()) {
            ++i;

            cout << i << ". Collision:" << endl;
            cout << "Flight: " << temp.top()->getId() << " and Flight" << flight->getId() << endl << endl;

            collision = true;
        }
        temp.pop();
    }

    // check if any flight has the same arrival or departure time | includ time delay for arrivals and departures
    
    return collision;

}
void Controller::grantDemand() {
    // if any collision found print it

    // otherwise grant demands by adding flights to airport's vectors and changing flight's indicator, remove from demands

}
void Controller::checkDemands() {
    // check airport for demands
    auto it = airport_->getPendingDemands().begin();





    // print all demands

}

//setters and getters
void Controller::setAirport(shared_ptr<Airport>p_airport) { airport_ = p_airport; }
shared_ptr<Airport> Controller::getAirport(void) const { return airport_; }

void Controller::setAirports(vector<shared_ptr<Airport>>p_airports) { airports_ = p_airports; }
        vector<shared_ptr<Airport>> Controller::getAirports(void) const{return airports_;}
