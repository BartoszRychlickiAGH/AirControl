#include <iostream>
#include <memory>
#include "validation.hpp"
#include "Database.hpp"
#include "Controller.hpp"

using std::shared_ptr, std::make_shared, std::endl, std::cout;


template<typename T>
vector<string> compress(shared_ptr<T>& obj);


int main(){
    
    
    /*system("echo test");
    
                                    system("timeout /t 5 /nobreak");        <-------  Important
    
    system("cls");*/
    shared_ptr<Database>db = make_shared<Database>();
    vector<shared_ptr<Airport>>airports{ db->pullAirports() };
    vector<shared_ptr<Flight>>flights{ db->pullFlights() };


    int i{ 1 }; // index of exact airport
    string input{};

    // displaying all airports
    
    for (shared_ptr<Airport>airport : airports) {
        cout << i << ". " << endl << "..............................." << endl;
        airport->display();
        cout << "..............................." << endl << endl;
        i++;
    }
        cout << "Select airport to control: ";

    do {
        
        cin >> input;
        cout << endl;

        if (Validation::isnumber(input)) {
            if (Validation::isInRange(std::stoi(input), 1, airports.size())) {
                break;
            }
            else {

                cout << "Given number doesn't match any of airport's indexe" << endl;
            }
        }
        else {
            cout << "Given input is NaN" << endl; 1;
        }

        // check if given index of chosen flight is a number and if given index of flight is in bounds(1, airports.size())
    } while (true);

    shared_ptr<Airport>airport = airports[std::stoi(input) - 1];

    shared_ptr<Controller>controller(new Controller(airport, airports));

    try {
        while (true) {


            // clearing terminal
        choosingActionMain:


            system("timeout /t 5 /nobreak");
            system("cls");



            cout << "Enter action: " << endl;
            cout << "1. Display Airport" << endl;
            cout << "2. Manage Flights" << endl;
            cout << "3. Manage Airports" << endl;
            cout << "4. Demands" << endl;
            cout << "0. Exit" << endl;


            // entering input by user
            do {
                cin >> input;
                if (Validation::isnumber(input)) {
                    if (Validation::isInRange(std::stoi(input), 0, 4)) {

                        break;

                    }
                    else {

                        cout << "Given input is not in bounds" << endl;

                    }

                }
                else {

                    cout << "Given input is NaN" << endl;

                }
            } while (true);


            if (std::stoi(input) == 0) { // exit program
                break;
            }

            // calling chosen action
            switch (std::stoi(input)) {
            case 1:
                controller->getAirport()->display("");
                break;
            case 2:

                while (true) {
                    // manage flights interface
                    cout << "Choose action to be done on flight" << endl;
                    cout << "1. Print Flight" << endl;
                    cout << "2. Add Flight" << endl;
                    cout << "3. Edit Flight" << endl;
                    cout << "4. Remove flight" << endl;
                    cout << "0. Exit" << endl;

                    do {
                        cin >> input;

                        if (Validation::isnumber(input)) {
                            if (Validation::isInRange(std::stoi(input), 0, 4)) {
                                break;
                            }
                            else {
                                cout << "Given number is not in bounds" << endl;
                            }
                        }
                        else {
                            cout << "Given input is NaN" << endl;
                        }
                    } while (true);

                    if (std::stoi(input) == 0) { break; } // exit module

                    switch (std::stoi(input)) {
                    case 1:
                        controller->printFlight(); // done

                        break;
                    case 2:
                        controller->addFlight(); // done

                        break;
                    case 3:
                        controller->editFlight(); // 

                        break;
                    case 4:
                        controller->removeFlight();

                        break;
                    default:
                        goto choosingActionMain;

                        break;
                    }

                    system("timeout /t 5 /nobreak");
                    system("cls");
                }

                break;
            case 3:
                // manage airports
                while (true) {

                    system("timeout /t 5 /nobreak");
                    system("cls");



                    cout << "0. Exit module" << endl;
                    cout << "1. Change airport" << endl;
                    cout << "2. Print Airports" << endl;
                    cout << "3. Print chosen airport" << endl;
                    cout << "Choose action: ";

                    do {
                        cin >> input, cout << endl;

                        if (Validation::isnumber(input)) {
                            if (Validation::isInRange(std::stoi(input), 0, 5)) {
                                break;
                            }
                            else {
                                cout << "Given number is not in bounds" << endl;
                            }
                        }
                        else {
                            cout << "Given input is NaN" << endl;
                        }
                    } while (true);


                    if (std::stoi(input) == 0) { break; } // exit module

                    switch (std::stoi(input)) {
                    case 1:
                        controller->changeAirport();//change airport

                        break;
                    case 2:
                        // print airports

                        for (int i = 1; shared_ptr<Airport>airport : airports) {
                            cout << endl << "................................." << endl;
                            cout << i << endl;
                            cout << "................................." << endl;

                            airport->display();
                            cout << endl;
                            ++i;
                        }

                        break;
                    case 3:
                        // print chosen airport

                        cout << endl <<"Choosen airport: " << endl;
                        
                        controller->getAirport()->display();

                        break;
                    default:
                        continue;

                        break;
                    }
                }

                break;
            case 4:
                // Demands
                controller->grantDemand();

                break;
            default:
                break;
            }

            system("timeout /t 5 /nobreak");
            system("cls");



        }
    
    

    

    
    pushData:
    
    // pushing data to database

    // pushing flights

    for (shared_ptr<Flight>obj : controller->pullFlights()) { // mind to change interated vectror
                
        
        db->update("Flights", obj->compress()); // obj is compressing to vector of strings to help further function (based in db object) push to SQL database 
    }


    // pushing airports
    for (shared_ptr<Airport>obj : airports) {


        db->update("Airports", obj->compress()); // obj is compressing to vector of strings to help further function (based in db object) push to SQL database 
    }

    cout << "Logging out..." << endl;
    system("timeout /t 1 /nobreak");
    system("cls");

    }
    catch (string& e) {
        std::cerr << endl << "Error: " << e << endl;
    }
    catch (std::exception e) {
        std::cerr << endl << "Error: " << e.what() << endl;
    }



    return 0;
}
    


template<typename T>
vector<string> compress(shared_ptr<T>& obj) {
    return obj->compress();
}