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

    while (true) {
        try {
            shared_ptr<Database>db = make_shared<Database>();
            vector<shared_ptr<Airport>>airports{ db->pullAirports() };
            vector<shared_ptr<Flight>>flights{ db->pullFlights() };

            int i{ 1 }; // index of exact airport
            string input{};

            // displaying all airports
            cout << "Select airport to control: " << endl;
            for (shared_ptr<Airport>airport : airports) {
                cout << i << ". " << endl << "..............................." << endl;
                airport->display();
                cout << "..............................." << endl << endl;
                i++;
            }


            do {
                cin >> input;

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

            // clearing terminal
            choosingActionMain:

            
            system("timeout /t 20 /nobreak");
            system("cls");



            cout << "Enter action: " << endl;
            cout << "1. Display Airport" << endl;
            cout << "2. Manage Flights" << endl;
            cout << "3. Manage Airports" << endl;
            cout << "4. Demands" << endl;
            cout << "0. Exit" << endl;


            // entering input by user
            do{
                cin >> input;
                if (Validation::isnumber(input)) {
                    if (Validation::isInRange(std::stoi(input), 0, 4)){
                        
                        break;
                    
                    }else {
                    
                        cout << "Given input is not in bounds" << endl;
                 
                    }
                
                }else {
                
                    cout << "Given input is NaN" << endl;
                
                }
            } while(true);


            // calling chosen action
            switch (std::stoi(input)) {
                case 0:
                    break;
                    break;
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


                        switch (std::stoi(input)) {
                        case 0:
                            break;
                            break;
                        case 1:
                            controller->printFlight();

                            break;
                        case 2:
                            controller->addFlight();

                            break;
                        case 3:
                            controller->editFlight();

                            break;
                        case 4:
                            controller->removeFlight();

                            break;
                        default:
                            goto choosingActionMain;

                            break;
                        }

                        system("timeout /t 20 /nobreak");
                        system("cls");
                    }

                    break;
                case 3:
                        // manage airports
                    while (true) {

                        system("timeout /t 20 /nobreak");
                        system("cls");



                        cout << "Choose action" << endl;
                        cout << "1. Change airport" << endl;
                        cout << "2. Print Airports" << endl;
                        cout << "3. Print chosen airport" << endl;
                        cout << "4. Change airport's name" << endl;
                        cout << "5. Change airport's capacity" << endl;

                        do {
                            cin >> input;

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


                        switch (std::stoi(input)) {
                        case 0:
                            //exit 
                            break;
                            break;
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
                            }

                            break;
                        case 3:
                            // print chosen airport
                            cout << "Choosen airport" << endl;

                            break;
                        case 4:
                            // change chosen airport's name

                            do {
                                cout << "Enter new airport name: (Disclaimer: enter -1 to exit this action!)", cin >> input, cout << endl;
                                
                                if (Validation::istext(input) || input == "-1") {
                            
                                    controller->getAirport()->setName(input);
                                    break;
                                
                                }
                                else {
                                    cout << "Given input is not a name" << endl;
                                }

                            } while (true);

                            controller->getAirport()->setName(input);

       
                            break;
                        case 5:
                            // change chosen airport's capacity
                            
                            do {
                                cout << "Enter new capacity of chosen airport: (Disclaimer: to exit this action enter: -1)", cin >> input, cout << endl;
                            
                                if (Validation::isnumber(input)) {
                                   
                                    controller->getAirport()->setCapacity(std::stoi(input));
                                    break;

                                }else {
                                    cout << "Given input is NaN" << endl;
                                    
                                }
                            
                            } while (true);
                            
                            controller->getAirport()->setCapacity(std::stoi(input));
                            
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
            
            system("timeout /t 20 /nobreak");
            system("cls");

            // pushing data to database
            
                // pushing flights

            for (shared_ptr<Flight>obj : flights) {
                db->push("Flights", obj->compress()); // obj is compressing to vector of strings to help further function (based in db object) push to SQL database 
            }


                // pushing airports
            for(shared_ptr<Airport>obj : airports){
                db->push("Airports", obj->compress()); // obj is compressing to vector of strings to help further function (based in db object) push to SQL database 
            }

        }
        catch (string& e) {
            std::cerr << e << endl;
            break;
        }
        catch (std::exception e) {
            std::cerr << e.what() << endl;
            break;
        }
    }

   
    return 0;
}



template<typename T>
vector<string> compress(shared_ptr<T>& obj) {
    return obj->compress();
}