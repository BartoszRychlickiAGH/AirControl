#pragma once

#include "Controller.hpp"
#include "validation.hpp"
#include <stack>


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
    int k{1};
    string i { "" };
    for(shared_ptr<Airport>airport : airports_) {
        
        cout << k  << ". " << airport->getAirportName() << endl;
    
        k++;
    
    }

    // make user to choose airport
    
    do{
        cout << "Choose airport: | To cancel operation enter: -1" << endl;
        cin >> i;

        if (i == "-1") {
            return;
        }

        if(Validation::isnumber(i)) {
            if (Validation::isInRange(std::stoi(i) - 1, 0, airports_.size())) {
                break;
            }
            else {
                cout << "Given number is out of range" << endl;
            }
        }
        else {
            cout << "Given input is NaN" << endl;
        }


    }while(true);

    // set airport by assigning chosen one to class variable
    setAirport(airports_[std::stoi(i)-1]);
}
void Controller::printFlight() {
    // print all flights in general way
    
    

    string i;
    string mode{};
    // make user to choose flight

    chooseMode:

    do{
        do{
            cout << "Choose mode: (arrivals/departure/parked/all)| To cancel operation enter: -1" << endl;

            cin >> mode;
        
            if (mode == "-1") { 
                return; 
            }

        }while(!Validation::istext(mode) and !Validation::checkFlightMode(mode) and mode != " -1");
        
        airport_->display(mode);

        if (mode == "" || mode == "all") {
            goto chooseMode;
        }


        auto isEmpty = [](string mode, shared_ptr<Airport>airport) {
            if (regex_match(mode, regex(R"(^[Pp]arke?d?)"))) {
                return ((airport->getParkedids().size() == 0)? true : false);
            }
            else if (regex_match(mode, regex(R"(^[Dd]epartures?)"))) {
                return ((airport->getDepartureids().size() == 0) ? true : false);
            }
            else if (!regex_match(mode, regex(R"(^[Aa]rrivals?)"))) {
                return ((airport->getArrivalsids().size() == 0) ? true : false);
            }

            return false;
        };

                
        if (isEmpty(mode, airport_)) {

            cout << endl << "Airport has no flights of given mode!" << endl << endl;

            goto chooseMode;
        }

        do {



            cout << "Choose flight: (To cancel operation enter: -1)" << endl;
            
            cin >> i;

            if (i == "-1") { // canceling operation module

                cout << "exiting ..." << endl;

                return;
            }
            
            if (!Validation::isnumber(i)) { // validation module
            
                cout << "Given number is not a decimal!" << endl;
            
            }

        } while (!Validation::isnumber(i) and i != "-1");
    


        // check if given index of flight exist in container of flights for given mode
        if (regex_match(mode,  regex(R"(^[Pp]arke?d?)")) and std::stoi(i) >= airport_->getParkedids().size()) {
        
            cout << "Picked wrong index of flight in parked ones" << endl;
            continue;
        
        }else if (!regex_match(mode, regex(R"(^[Dd]epartures?)")) and std::stoi(i) >= airport_->getDepartureids().size()) {
        
            cout << "Picked wrong index of flight in departure ones" << endl;
            continue;
        
        }else if (!regex_match(mode, regex(R"(^[Aa]rrivals?)")) and std::stoi(i) >= airport_->getArrivalsids().size()) {
            
            cout << "Picked wrong index of flight in arrival ones" << endl;
            continue;

        }

        if(i == "-1") {
            return;
        }

    }while(!Validation::isnumber(i) and !Validation::isInRange(std::stoi(i)-1, 0, airport_->getDepartureids().size()));
    
    // print chosen flight
    if(regex_match(mode, regex(R"(^[Aa]rrivals?)"))){
        printFlight_queue(std::stoi(i) - 1,airport_->getArrivalsids());
    }else if(regex_match(mode, regex(R"(^[Dd]epartures?)"))){
        printFlight_queue(std::stoi(i) - 1, airport_->getDepartureids());
    }else if(regex_match(mode,  regex(R"(^[Pp]arke?d?)"))){
        airport_->getParkedids()[std::stoi(i)-1]->display();
    }
    else {
        airport_->displayFlights();
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

        if (Validation::isnumber(id)) {
            if (Validation::idExist(id,airport_->getDepartureids())) {
                cout << "Given id already exist in Departures' flights" << endl;
            }
            else if (Validation::idExist(id, airport_->getArrivalsids())) {
                cout << "Given id already exist in Arrivals' flights" << endl;
            }
            else if (Validation::idExist(id, airport_->getParkedids())) {
                cout << "Given id already exist in Parked' flights" << endl;
            }
            else {
                break;
            }
        }
        else {
            cout << "Given input is NaN" << endl;
        }


    }while(true);

   
    enterAirport:

    auto exist = [](string airport, vector<shared_ptr<Airport>>airports) {
            return (Validation::istext(airport) && Validation::airportExist(airports, airport)) ? true : false;
        };


    do{
            
        cout << endl <<"Enter base: ";            cin >> base;          if(base == "exit"){ return; }
        if (exist(base, airports_)) {
            break;
        }else{
            cout << "Invalid input - entered not a text or given airport doeas not exist" << endl;
        }

    }while(true);

    

    do{

        cout << endl << "Enter destination: ";    cin >> destination;   if(destination == "exit"){ return; }

        if (exist(destination, airports_)) {
            break;
        }
        else {
            cout << "Invalid input - entered not a text or given airport doeas not exist" << endl;
        }


    }while(true);

    cout << endl << "Enter plane name: ";     cin >> planeName;    if(planeName == "exit"){ return; }

    do{

        cout << endl << "Enter flight date ( format: YYYY-MM-DD ): ";    cin >> flightDate;    if(flightDate == "exit"){ return; }

    }while(!Validation::isDate(flightDate));

    do{

        cout << endl << "Enter departure time ( format: HH:MM ): "; cin >> departureTime; if(departureTime == "exit"){ return; }

    }while(!Validation::isTime(departureTime));

    do{

        cout << endl <<"Enter arrival time ( format: HH:MM ): ";    cin >> arrivalTime;   if(arrivalTime == "exit"){ return; }

    }while(!Validation::isTime(arrivalTime));


    // create new flight
    shared_ptr<Flight> flight(new Flight(std::stoi(id), base, destination, planeName, flightDate, departureTime, arrivalTime));

    // check if given departure time nor arrival time is already taken
    if(checkCollision(flight, -255)) {
        return;
    }

    if( base != airport_->getAirportName() && destination != airport_->getAirportName()) {

        cout << "Invalid permission! Tried to manage another airports" << endl;

        goto  enterAirport;
    }


    // check if airport of given name exist
    if(!Validation::airportExist(getAirports(), base) and !Validation::airportExist(airports_, destination)) {

        cout << "Airport of given name don't exist" << endl;

        goto enterAirport;
    }

    // add flight to airport
    airport_->addFlight(flight);


    cout << "Added flight" << endl;

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
        if (regex_match(mode,  regex(R"(^[Pp]arke?d?)")) and std::stoi(i) >= airport_->getParkedids().size()) {

            cout << "Picked wrong index of flight in parked ones" << endl;

            continue;

        }
        else if (regex_match(mode, regex(R"(^[Dd]epartures?)")) and std::stoi(i) >= airport_->getDepartureids().size()) {

            cout << "Picked wrong index of flight in departure ones" << endl;

            continue;

        }
        else if (regex_match(mode, regex(R"(^[Aa]rrivals?)")) and std::stoi(i) >= airport_->getArrivalsids().size()) {

            cout << "Picked wrong index of flight in arrival ones" << endl;

            continue;

        }

        if (i == "-1") {
            return;
        }
    }while (!Validation::isnumber(i) and !Validation::isInRange(std::stoi(i) - 1, 0, airport_->getDepartureids().size()));


    if (regex_match(mode, regex(R"(^[Aa]rrivals?)"))) {

        // remove flight from airport's arrivals
        
        priority_queue<shared_ptr<Flight>>temp1 = airport_->getArrivalsids(),temp2;
        for (int j = 0; j <= airport_->getArrivalsids().size(); ++j) {
            if (std::stoi(i)-1 != j) {

                if (temp1.size() == 0) { break; }

                temp2.push(temp1.top());
            
                temp1.pop();
            
            }
        
        }

        airport_->setArrivals(temp2);

    }
    else if (regex_match(mode, regex(R"(^[Dd]epartures?)"))) {

        // remove flight from airport's departures
        priority_queue<shared_ptr<Flight>>temp1 = airport_->getDepartureids(), temp2;
        for (int j = 0; j <= airport_->getDepartureids().size(); ++j) {
            if (std::stoi(i) - 1 != j) {


                if (temp1.size() == 0) { break; }

                temp2.push(temp1.top());
            
            }

            temp1.pop();
        }

        airport_->setDepartures(temp2);


    }
    else if (regex_match(mode,  regex(R"(^[Pp]arke?d?)"))) {

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
        
        if (Validation::istext(mode)){
            if(Validation::checkFlightMode(mode)) {

                break;
            }
            else {
                
                cout << "Entered wrong flight mode" << endl;

            }
        }else {

            cout << "Entered input is not a text" << endl;
        
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

            if (i == "0") { i = "1"; }

            if (!Validation::isnumber(i) || regex_match(mode, regex(R"(^[Aa]rrivals?)")) && std::stoi(i) > airport_->getArrivalsids().size()) {
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

            if (!Validation::isnumber(i) || regex_match(mode, regex(R"(^[Dd]epartures?)")) && std::stoi(i) > airport_->getDepartureids().size()) {
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

            if (!Validation::isnumber(i) || regex_match(mode,  regex(R"(^[Pp]arke?d?)")) && std::stoi(i) > airport_->getParkedids().size()) {
                validate = false;
            }

            if (mode == "") {
                cout << "Mode needs to be chosen!" << endl;

                goto choose;
            }

        } while (!validate);

    
    }

    // at this line - i - is correct and - mode - is correct
   

    auto exist = [](vector<shared_ptr<Airport>> airports, string airport) {
        if (Validation::istext(airport)) {
            if (Validation::airportExist(airports, airport)) {
                return true;
            }
            else {
                cout << "Airport does not exitst" << endl;
                return false;
            }
        }
        else {
            cout << "Entered input is not a text" << endl;
        }
    };


    if (regex_match(mode, regex(R"(^[Aa]rrivals?)"))) {
        auto temp = airport_->getArrivalsids();
        for (int j = 0; j < std::stoi(i); j++) {
            if (j == std::stoi(i) - 1) {
                flight = temp.top();
            }
            temp.pop();
        }
    }
    else if (regex_match(mode, regex(R"(^[Dd]epartures?)"))) {
        auto temp = airport_->getDepartureids();
        for (int j = 0; j < std::stoi(i); j++) {
            if (j == std::stoi(i) - 1) {
                flight = temp.top();
            }
            temp.pop();
        }
    }
    else if (regex_match(mode, regex(R"(^[Pp]arke?d?)"))) {
        auto temp = airport_->getParkedids();
        flight = temp[std::stoi(i) - 1];
    }

    // edit mode pseudo - interface


    while(true){
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

            if (Validation::isnumber(k)){
                if (Validation::isInRange(std::stoi(k), 0, 7)) {
            
                    break;

                }
                else {
                
                    cout << "Entered wrong index of action" << endl;

                }
            }
            else {
                cout << "Entered input is NaN!" << endl;
            }
        
        } while (true);

        switch (std::stoi(k)) {
        case 1: {
            string newId;

            chooseId:

            do {
                cout << "Enter new Id: ";
                cin >> newId;

                if (Validation::isnumber(newId)) {
                    bool temp = (Validation::idExist(newId, airport_->getArrivalsids()) || Validation::idExist(newId, airport_->getDepartureids()) || Validation::idExist(newId, airport_->getParkedids()));
                    
                    if (temp) {
                        cout << "Entered Id is taken" << endl; // id exist in one of the containers
                    }
                    else {
                        break;
                        flight->setId(std::stoi(newId));
                    }
                    
                }


            } while (!Validation::idExist(newId,airport_->getArrivalsids()) and !Validation::idExist(newId, airport_->getDepartureids()) and !Validation::idExist(newId, airport_->getParkedids()));
        }
        case 2: {
            string newBase{};
                
            do {
                cout << "Enter new Base: ";
                
                cin >> newBase;
                
                if (exist(airports_, newBase)) {
                    flight->setBase(newBase);
                    break;
                }

            } while (true);
        }
        case 3: {
            string newDestination;
                
            do {
                cout << "Enter new Destination: ";
                cin >> newDestination;

                if (exist(airports_, newDestination)) {
                    flight->setDestination(newDestination);
                    break;
                }


            } while (!Validation::istext(newDestination) and !Validation::airportExist(airports_, newDestination));
        }
        case 4: {
            string newPlaneName;
                
                
            cout << "Enter new Plane Name: ";
                
            cin >> newPlaneName;

            flight->setPlaneName(newPlaneName);
                
        }
        case 5: {
            string newFlightDate;
                
            do {
                cout << "Enter new Flight Date ( format: YYYY-MM-DD ): ";
                cin >> newFlightDate;

                if (Validation::isDate(newFlightDate)) {
                    flight->setFlightDate(newFlightDate);
                    break;
                }
                else {
                    cout << "invalid date" << endl;
                }

            } while (true);
        }
        case 6: {
            string newDepartureTime;
                
            start:

            do {
                cout << "Enter new Departure Time ( format: HH:MM ): ";
                cin >> newDepartureTime;
                    
                if (!Validation::isTime(newDepartureTime)) {
                    cout << "Entered wrong time format";
                }
                else {
                    flight->setDepartureTime(newDepartureTime);
                    break;
                }
                
                
            } while (true);


            if (checkCollision(flight, flight->getDemandIndicator())) {

                cout << "Created Collision!" << endl;

                goto start;
            }
                
            break;
        }
        case 7: {
            string newArrivalTime;

            startArr:

            do {
                cout << "Enter new Arrival Time ( format: HH:MM ): ";
                
                cin >> newArrivalTime;
                
                if (!Validation::isTime(newArrivalTime)) {
                        
                    cout << "Given time is not in time format" << endl;

                }
                else {
                    flight->setArrivalTime(newArrivalTime);

                    break;
                }


            } while (true);

            
                
            if (checkCollision(flight, flight->getDemandIndicator())) {

                cout << "Created Collision!" << endl;

                goto startArr;
            }
                
                
            break;
        }
        case 0:
         
            
            if (mode == "departure") {
                priority_queue<shared_ptr<Flight>> temp = airport_->getDepartureids();
                priority_queue<shared_ptr<Flight>> newQueue;

                for (int j = 0; j < airport_->getDepartureids().size(); ++j) {
                    if (j == std::stoi(i) - 1) {
                        newQueue.push(flight);
                    }
                    else {
                        newQueue.push(temp.top());
                    }
                    temp.pop();
                }
                airport_->setDepartures(newQueue);
            }
            if (mode == "arrival") {
                priority_queue<shared_ptr<Flight>> temp = airport_->getArrivalsids();
                priority_queue<shared_ptr<Flight>> newQueue;

                for (int j = 0; j < airport_->getArrivalsids().size(); ++j) {
                    if (j == std::stoi(i) - 1) {
                        newQueue.push(flight);
                    }
                    else {
                        newQueue.push(temp.top());
                    }
                    temp.pop();
                }
                airport_->setArrivals(newQueue);
            }
            if (mode == "parked") {
                vector<shared_ptr<Flight>> temp = airport_->getParkedids();
                temp[std::stoi(i) - 1] = flight;
                airport_->setParked(temp);
            }
           
            
            return;
        }

    }
}


// check if flight, which controller is willing to add, has any collision with parked/departure/arrival flights
bool Controller::checkCollision(shared_ptr<Flight>flight, int mode) {
    int i{ 0 };
    bool collision{false};
    priority_queue<shared_ptr<Flight>>temp = airport_->getArrivalsids();

    // check all flights for collision

    if(mode ==  -1 or mode == -255){
        for (int j = 0; j <= airport_->getArrivalsids().size() - 1; ++j) {
            
            if (!(flight == temp.top())) {
            
                if (flight->getArrivalTime() == temp.top()->getArrivalTime() && flight->getFlightDate() == temp.top()->getFlightDate()) {
                    ++i;

                    cout << i << ". Collision:" << endl;
                    cout << "Flight: " << temp.top()->getId() << " and Flight: " << flight->getId() << endl << endl;

                    collision = true;
                
                }
            }

            temp.pop();
        }
         
    }
    if (mode == 1 or mode == -255) {
        temp = airport_->getDepartureids();

        for (int j = 0; j <= airport_->getDepartureids().size() - 1; ++j) {
            
            if (!(flight == temp.top())) {
                if (flight->getDepartureTime() == temp.top()->getDepartureTime() && flight->getFlightDate() == temp.top()->getFlightDate()) {
                    ++i;

                    cout << i << ". Collision:" << endl;
                    cout << "Flight: " << temp.top()->getId() << " and Flight" << flight->getId() << endl << endl;

                    collision = true;
                }
            }
            
            
            temp.pop();
        }

        // check if any flight has the same arrival or departure time | includ time delay for arrivals and departures
    }

    return collision;
}

void Controller::grantDemand() {
    // update demands
    airport_->checkDemands();

    string i{""}; // variable that user will be overwriting to choose demand to grand nor to cancel

    auto it = airport_->getPendingDemands().begin();
    auto temp = std::move(airport_->getDepartureids()); // calibrating the auto type
    auto temp2 = std::move(airport_->getParkedids());;


    // print demands
    checkDemands();

    do {
        cout << "Choose demand to approve: (To cancel operation type -255)" << endl;
        
        cin >> i;

        if (i == "-255") { return; }


        if (!Validation::isnumber(i)) { 
            
            cout << "Given data is not a number" << endl; 
        
        }else {


            if (Validation::isInRange(std::stoi(i) - 1, 0, airport_->getPendingDemands().size())) {
                
                break;

            } else{
                cout << "Given number is out of range" << endl;
            }
        }


    } while (true);


    for (int j = 0; j < std::stoi(i)-1; j++) {
        it++;
    }
    // otherwise grant demands by adding flights to airport's vectors and changing flight's indicator, remove from demands

    // choose: accept demand or cancel demand


    switch (it->first) {
        case 1: // departure
        
            // insert obj (which is stored under it->second) into departures_ 
            
            temp.push(it->second);

            // remove from parked
            removeFlight(0, it->second);

            // airport_->setDepartures(temp);

            // it->second->setdemandIndicator(2);
            // refactor: delete from demands

            // remove from demands
            removeFlight(-255, it->second);

            // eof refactor

            break;
        
        case -1: // arrival

        // insert into parked_
            temp2.push_back(it->second);
            
            // delete from arrival
            // removeFlight(-1, it->second);

            // refacotr: delete from demands

            removeFlight(-255, it->second);
            
            // eof refactor

            break;
        case -255:

            return; // exit action
        
            break;
        default: 
           // do nothing
            break;
    }


}
void Controller::checkDemands() {
    // check airport for demands

    int i{1};
    multimap<int, shared_ptr<Flight>>tempMultimap = airport_->getPendingDemands();
    // print all demands

    cout << "Pending Demands: " << endl;

    for (auto it = tempMultimap.begin(); it != tempMultimap.end(); it++) {
        cout << i << ". Demand Type: " << it->first << " | Flight: " << it->second->getId() << endl;
        i++;
    }
    cout << endl;
}

void Controller::removeFlight(int indicator, shared_ptr<Flight>flight) {

    int i{ 0 }; // index of element in vector: parked_

    std::stack<shared_ptr<Flight>>buffer;
    auto tempArrivals = getAirport()->getArrivalsids();
    auto tempDemands = getAirport()->getPendingDemands();

    switch (indicator) {
        
        case 0: // delete from parked

            for (shared_ptr<Flight>obj : getAirport()->getParkedids()) {
                if (obj == flight) {
                    getAirport()->getParkedids().erase(getAirport()->getParkedids().begin() + i);
                    break;
                }
                i++;
            }

            break;
        case -1: // delete from arrivals

            // find flight in arrivals (priority_queue) to delete
            for (int j = 0; j <= tempArrivals.size(); ++j) {
                if (tempArrivals.top() == flight) {
                    break; // if found then skip
                }
                else {
                    buffer.push(tempArrivals.top()); // else push flight to buffer
                }
        
            
                tempArrivals.pop();

            }

            // restore flights from buffer to arrivals

            for (int j = 0; buffer.size() != 0; j++) {
                tempArrivals.push(buffer.top());

                buffer.pop();
            }


            break;
        default: // delete from demands
            

            for (auto it = tempDemands.begin(); it != tempDemands.end(); ++it) {
                if (it->second == flight) {
                    tempDemands.erase(it);
                    break;
                }
            }

            break;
    }

}

vector<shared_ptr<Flight>> Controller::pullFlights() {
    
    vector<shared_ptr<Flight>>flights{};

    bool exist{false};

    for (shared_ptr<Airport> airport : airports_) {
        
        // get all flights from airport
        vector<shared_ptr<Flight>>airport_Flights = airport->pullFlights();

        // check if any of flights in airport_Flight already exist in vector flights
        for (shared_ptr<Flight>obj : airport_Flights) {
            
            for (shared_ptr<Flight> flighInFlights : flights) {
                if (flighInFlights == obj) {
                    exist = true;
                }
            }

            if (!exist) {
                flights.push_back(obj);
            }
            exist = false;

        }

    }

    return flights;

}





//setters and getters
void Controller::setAirport(shared_ptr<Airport>p_airport) { airport_ = p_airport; }
shared_ptr<Airport> Controller::getAirport(void) const { return airport_; }

void Controller::setAirports(vector<shared_ptr<Airport>>p_airports) { airports_ = p_airports; }
        vector<shared_ptr<Airport>> Controller::getAirports(void) const{return airports_;}
