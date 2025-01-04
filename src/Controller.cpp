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
    }while(!Validation::isnumber(i) and !Validation::isInRange(std::stoi(i)-1, 0, airports_.size()));

    // set airport by assigning chosen one to class variable
    setAirport(airports_[std::stoi(i)-1]);
}
void Controller::printFlight() {
    // print all flights in general way
    
    string i;
    string mode{};
    // make user to choose flight
    do{
        do{
        cout << "Choose mode: (arrivals/departure/parked)| To cancel operation enter: -1" << endl;
        cin >> mode;
        }while(!Validation::istext(mode) and !Validation::checkFlightMode(mode));
        
        airport_->display(mode);


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
    }while(!Validation::isnumber(i) and !Validation::isInRange(std::stoi(i)-1, 0, airport_->getDepartureids().size()));
    
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
    shared_ptr<Flight> flight(new Flight(std::stoi(id), base, destination, planeName, flightDate, departureTime, arrivalTime));

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
    airport_->display("");


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
    }while (!Validation::isnumber(i) and !Validation::isInRange(std::stoi(i) - 1, 0, airport_->getDepartureids().size()));


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
    string i{}, k{"-1"}; // i - index of chosen flight to be edited, j - index of field that will be chosen
    string mode{};
    shared_ptr<Flight>flight;

    // print all flights in general way
     
    choose:
    
    
    do {
        cout << "Which flight do you want to change: (arrival/departure/parked)" << endl;
        
        cin >> mode;
        
        if (!Validation::istext(mode) or !Validation::checkFlightMode(mode)) {
            cout << "Entered wrong mode" << endl;
        }

    } while (!Validation::istext(mode) or !Validation::checkFlightMode(mode));
    
    airport_->display(mode);
    
    // make user to choose flight

    {
        bool validate{ };
        
        priority_queue<shared_ptr<Flight>>temp;
    
        do {
            validate = true;
            cout << "Enter number of flight which you want to change: " << endl;

            cin >> i;

            if (!Validation::isnumber(i) || mode == "arrival" && std::stoi(i) > airport_->getArrivalsids().size()) {
                validate = false;
            }
            else {
                temp = airport_->getArrivalsids();

                for (int j = 0; j < std::stoi(i); j++) {
                    
                    if (j == std::stoi(i) - 1) {
                        flight = move( temp.top());
                    }


                    temp.pop();
                }
            }

            if (!Validation::isnumber(i) || mode == "departure" && std::stoi(i) > airport_->getDepartureids().size()) {
                validate = false;
            }
            else {
                temp = airport_->getDepartureids();

                for (int j = 0; j < std::stoi(i); j++) {

                    if (j == std::stoi(i) - 1) {
                        flight = move(temp.top());
                    }


                    temp.pop();
                }
            }

            if (!Validation::isnumber(i) || mode == "parked" && std::stoi(i) > airport_->getParkedids().size()) {
                validate = false;
            }

            if (mode == "") {
                cout << "Mode needs to be chosen!" << endl;

                goto choose;
            }

        } while (!validate);

    
    }

    // at this line - i - is correct and - mode - is correct
   

    // edit mode pseudo - interface
    while(std::stoi(k) == 0){
        do {

            cout << "Choose field to change: " << endl;
            cout << "1. Id" << endl;
            cout << "2. Base" << endl;
            cout << "3. Destination" << endl;
            cout << "4. Plane Name" << endl;
            cout << "5. Flight Date" << endl;
            cout << "6. Departure Time" << endl;
            cout << "7. Arrival Time" << endl;
            cout << "0. Exit" << endl;
            cin >> k;

            if (!Validation::isnumber(k) && !Validation::isInRange(std::stoi(k), 0, 7)) {
            
                cout << "Invalid number!" << endl;
        
            }
        
        } while (!Validation::isnumber(k) && !Validation::isInRange(std::stoi(k), 0, 7));

        switch (std::stoi(k)) {
            switch (std::stoi(k)) {
            case 1: {
                string newId;

                chooseId:

                do {
                    cout << "Enter new Id: ";
                    cin >> newId;

                    if (!Validation::isnumber(newId)) {
                        cout << "Entered NaN" << endl;
                    }
                    else if (!Validation::idExist(newId, airport_->getArrivalsids()) and !Validation::idExist(newId, airport_->getDepartureids()) and !Validation::idExist(newId, airport_->getParkedids())) {
                        cout << "Given id already exist" << endl;
                    }


                } while (!Validation::isnumber(newId) and !Validation::idExist(newId,airport_->getArrivalsids()) and !Validation::idExist(newId, airport_->getDepartureids()) and !Validation::idExist(newId, airport_->getParkedids()));

                int newId_int{std::stoi(newId)};

                if (mode == "arrival") {
                    
                    airport_->getArrivalsids().top()->setId(newId_int);

                }else if (mode == "departure") {
                
                    airport_->getDepartureids().top()->setId(newId_int);
                
                }
                else if (mode == "parked") {
                
                    airport_->getParkedids()[std::stoi(i) - 1]->setId(newId_int);
                
                }
                
                break;
            }
            case 2: {
                string newBase;
                
                do {
                    cout << "Enter new Base: ";
                
                    cin >> newBase;
                
                    if (!Validation::istext(newBase)) {
                        cout << "Given string is not a text" << endl;
                    }
                    else if (!Validation::airportExist(airports_,newBase)) {
                        cout << "Airport of given name don't exist" << endl;
                    }


                } while (!Validation::istext(newBase) and !Validation::airportExist(airports_,newBase));

                if (mode == "arrival") {
                
                    airport_->getArrivalsids().top()->setBase(newBase);
                
                }else if (mode == "departure") {
                
                    airport_->getDepartureids().top()->setBase(newBase);
                
                }else if (mode == "parked") {
                
                    airport_->getParkedids()[std::stoi(i) - 1]->setBase(newBase);
                
                }

                break;
            }
            case 3: {
                string newDestination;
                
                do {
                    cout << "Enter new Destination: ";
                    cin >> newDestination;

                    if (!Validation::istext(newDestination)) {
                        cout << "Given string is not a text" << endl;
                    }
                    else if (!Validation::airportExist(airports_, newDestination)) {
                        cout << "Airport of given name don't exist" << endl;
                    }


                } while (!Validation::istext(newDestination) and !Validation::airportExist(airports_, newDestination));
                
                if (mode == "arrival") {
                
                    flight->setDestination(newDestination);
                
                }else if (mode == "departure") {
                
                    flight->setDestination(newDestination);
                
                }else if (mode == "parked") {
                
                    airport_->getParkedids()[std::stoi(i) - 1]->setDestination(newDestination);
                }

                break;
            }
            case 4: {
                string newPlaneName;
                
                do {
                    cout << "Enter new Plane Name: ";
                
                    cin >> newPlaneName;
                
                    if (!Validation::istext(newPlaneName)) {
                        cout << "Given string is not a text" << endl;
                    }

                } while (!Validation::istext(newPlaneName));

                if (mode == "arrival") {
                    
                    airport_->getArrivalsids().top()->setPlaneName(newPlaneName);
                
                }else if (mode == "departure") {
                    
                    airport_->getDepartureids().top()->setPlaneName(newPlaneName);
                
                }else if (mode == "parked") {
                
                    airport_->getParkedids()[std::stoi(i) - 1]->setPlaneName(newPlaneName);
                
                }
                
                break;
            }
            case 5: {
                string newFlightDate;
                
                do {
                    cout << "Enter new Flight Date: ";
                    cin >> newFlightDate;
                } while (!Validation::isDate(newFlightDate));

                if (mode == "arrival") {
                
                    flight->setFlightDate(newFlightDate);
                
                }else if (mode == "departure") {
                    
                    flight->setFlightDate(newFlightDate);
                
                }else if (mode == "parked") {
                
                    airport_->getParkedids()[std::stoi(i) - 1]->setFlightDate(newFlightDate);
                }

                break;
            }
            case 6: {
                string newDepartureTime;
                
                start:

                do {
                    cout << "Enter new Departure Time: ";
                    cin >> newDepartureTime;
                    
                    if (!Validation::isTime(newDepartureTime)) {
                        cout << "Entered wrong time format";
                    }
                
                
                } while (!Validation::isTime(newDepartureTime));
                

                shared_ptr<Flight>temp;

                if (mode == "arrival") {
                    
                    temp = move(flight);

                    if (!checkCollision(temp)) {
                    
                        flight->setDepartureTime(newDepartureTime);
                    
                    }
                    else {
                        cout << "Created Collision!" << endl;

                        goto start;
                    }


                }else if (mode == "departure") {
                    temp = move(flight);

                    if (!checkCollision(temp)) {

                        flight->setDepartureTime(newDepartureTime);

                    }
                    else {
                        cout << "Created Collision!" << endl;

                        goto start;
                    }



                }else if (mode == "parked") {
                
                    airport_->getParkedids()[std::stoi(i) - 1]->setDepartureTime(newDepartureTime);
                
                }
                
                break;
            }
            case 7: {
                string newArrivalTime;

                startArr:

                do {
                    cout << "Enter new Arrival Time: ";
                
                    cin >> newArrivalTime;
                
                    if (!Validation::isTime(newArrivalTime)) {
                        
                        cout << "Given time is not in time format" << endl;

                    }


                } while (!Validation::isTime(newArrivalTime));

                shared_ptr<Flight>temp;

                if (mode == "arrival") {
                
                    temp = move(flight);

                    if (!checkCollision(temp)) {

                        flight->setArrivalTime(newArrivalTime);

                    }
                    else {
                        cout << "Created Collision!" << endl;

                        goto startArr;
                    }
                
                }else if (mode == "departure") {
                
                    temp = move(flight);

                    if (!checkCollision(temp)) {

                        flight->setArrivalTime(newArrivalTime);

                    }
                    else {
                        cout << "Created Collision!" << endl;

                        goto startArr;
                    }
                
                }else if (mode == "parked") {
                
                    airport_->getParkedids()[std::stoi(i) - 1]->setArrivalTime(newArrivalTime);
                
                }
                
                
                break;
            }
            case 0:
                return;
            }

        
        }


    }

    if (std::stoi(k) == 0) {
        return;
    }


    // edit chosen flight





}


// check if flight, which controller is willing to add, has any collision with parked/departure/arrival flights
bool Controller::checkCollision(shared_ptr<Flight>flight) {
    int i = 0;
    bool collision{false};
    priority_queue<shared_ptr<Flight>>temp = airport_->getArrivalsids();

    // check all flights for collision
    for (int j = 0; j <= airport_->getArrivalsids().size(); ++j) {

        if(flight->getArrivalTime() == temp.top()->getArrivalTime() && flight->getFlightDate() == temp.top()->getFlightDate()) {
            ++i;
            
            cout << i << ". Collision:" << endl;
            cout << "Flight: " << temp.top()->getId() << " and Flight" << flight->getId() << endl << endl;
            
            collision = true;
        }
        temp.pop();
    }

    temp = airport_->getDepartureids();

    for(int j = 0; j <= airport_->getDepartureids().size(); ++j) {
        if(flight->getDepartureTime() == temp.top()->getDepartureTime() && flight->getFlightDate() == temp.top()->getFlightDate()) {
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
    // update demands
    airport_->checkDemands();

    string i{};
    auto it = airport_->getPendingDemands().begin();

    // print demands
    checkDemands();

    do {
        cout << "Choose demand to approve: (To cancel operation - type -1)" << endl;
        cin >> i;
        if (!!Validation::isnumber(i)) { cout << "Given data is not a number" << endl; }

    } while (!!Validation::isnumber(i) && !Validation::isInRange(std::stoi(i) - 1, 0, airport_->getPendingDemands().size()));


    for (int j = 0; j <= std::stoi(i) - 1; j++) {
        it++;
    }
    // otherwise grant demands by adding flights to airport's vectors and changing flight's indicator, remove from demands

    switch (it->first) {
    case 1: // departure
        {
        auto temp = std::move(airport_->getDepartureids());
        // insert obj (which is stored under it->second) into departures_ 
        temp.push(it->second);

        airport_->setDepartures(temp);

        // change flight indicator
        it->second->setdemandIndicator(-255);

        break;
        }
        
    case -1: // arrival
        {
            auto temp2 = std::move(airport_->getParkedids());

            // insert into parked_
            temp2.push_back(it->second);
            airport_->setParked(temp2);


            // change flight indicator
            it->second->setdemandIndicator(-255);

            break;
        }
        default: 
           // do nothing
            break;
    }


}
void Controller::checkDemands() {
    // check airport for demands
    auto it = airport_->getPendingDemands().begin();
    int i{1};

    // print all demands

    cout << "Pending Demands: " << endl;

    for (it; it != airport_->getPendingDemands().end(); it++) {
        cout << i << ". Demand Type: " << it->first << " | Flight: " << it->second->getId() << endl;
        i++;
    }
    cout << endl;
}

//setters and getters
void Controller::setAirport(shared_ptr<Airport>p_airport) { airport_ = p_airport; }
shared_ptr<Airport> Controller::getAirport(void) const { return airport_; }

void Controller::setAirports(vector<shared_ptr<Airport>>p_airports) { airports_ = p_airports; }
        vector<shared_ptr<Airport>> Controller::getAirports(void) const{return airports_;}
