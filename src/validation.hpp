#pragma once

#include <string>
#include <ctime>
#include <regex>
#include <sstream>
#include <iomanip>
#include <vector>

#include "Airport.hpp"

using std::string, std::regex_match, std::regex, std::vector;

class Validation{
    private:
        //constructor
        Validation() = default;
    public:

    
    // check if given text is string
    static bool istext(string text) {
        for(char c : text) {
            if(!isalpha(c)) {
                return false;
            }
        }
        return true;
    }
    
    // check if given text is number
    static bool isnumber(string text) {
        for(char c : text) {
            if(!isdigit(c)) {
                return false;
            }
        }
        return true;
    }
    
    // check if given number is in range
    static bool isInRange(int number, int min, int max) {
        return (number >= min && number <= max);
    }
    
    // check if given text is date
    static bool isDate(string text) {  // format: YYYY-MM-DD
        if(text.size() != 10) {
            return false;
        }
        if(text[4] != '-' || text[7] != '-') {
            return false;
        }
        for(int i = 0; i < 10; i++) {
            if(i == 4 || i == 7) {
                continue;
            }
            if(!isdigit(text[i])) {
                return false;
            }
        }

        // check format by regex
        if (!regex_match(text, regex(R"(^\d{4}-(0?[1-9]|1[0-2])-(0?[1-9]|[12]\d|3[01])$)"))) {
            return false;
        }

        // check if given date is correct (given date cannot be less than 1.1.2025)
        {
            string year{};
            
            for (char& c : text) {

                if (c == '-') {

                    break;

                }
                else {

                    year.push_back(c);

                }

            }

            if(std::stoi(year)< 2025){
                return false;
            }


        }

        return true;
    }
    
    // check if given text is time
    static bool isTime(string text) { // format: HH:MM

        if(text.size() != 5) {
            return false;
        }

        if(text[2] != ':') {
            return false;
        }

        for(int i = 0; i < 5; i++) {
            if(i == 2) {
                continue;
            }
            if(!isdigit(text[i])) {
                return false;
            }
        }

        // check format by regex
        if (!regex_match(text, regex(R"(^(^([01]?[0-9]|2[0-3]):([0-5]?[0-9])$)$)"))) {
            return false;
        }

        return true;
    }

    static bool checkFlightMode(string mode){
        return (mode == "arrival" || mode == "departure" || mode == "parked" || mode == "Arrival" || mode == "Departure" || mode == "Parked")? true: false;
    }

    // check if airport of given name exist
    static bool airportExist(vector<shared_ptr<Airport>> airports, string& name){
        for(shared_ptr<Airport>airport : airports){
            if(airport->getAirportName() == name){
                return true;
            }
        }
        return false;
    }

    // check if flight is in queue
    static bool isInQueue(shared_ptr<Flight>flight, priority_queue<shared_ptr<Flight>>flights) {
        priority_queue<shared_ptr<Flight>>temp = flights;
        bool valid{ false };
        
        for (int i = 0; i <= flights.size(); i++) {
            
            
            if (
                temp.top()->getId() == flight->getId() ||
                temp.top()->getBase() == flight->getBase() ||
                temp.top()->getDestination() == flight->getDestination() ||
                temp.top()->getPlaneName() == flight->getPlaneName() ||
                temp.top()->getFlightDate() == flight->getFlightDate() ||
                temp.top()->getDepartureTime() == flight->getDepartureTime() ||
                temp.top()->getArrivalTime() == flight->getArrivalTime() ||
                temp.top()->getDemandIndicator() == flight->getDemandIndicator()
                ) 
            {
            
                valid = true;
            }



            temp.pop();
        }


    }

    // check if pair is in multimap
    template<typename T, typename U>
    static bool isInMultimap(T var1, U var2, multimap<T, U>container) {

        for (auto it = container.begin(); it != container.end(); it++) {
            if (it->first == var1 and it->second == var2) {
                return true;
            }
        }

        return false;
    }


    static bool idExist(string id, priority_queue<shared_ptr<Flight>>flights) {
        priority_queue<shared_ptr<Flight>> temp = flights;

        for (int i = 0; i < temp.size(); i++) {
            if (temp.top()->getId() == std::stoi(id)) {
            
                return true;
            }

            temp.pop();
        }


        return false;
    }

    static bool idExist(string id, vector<shared_ptr<Flight>>flights) {
        
        for (shared_ptr<Flight>flight : flights) {
            if (flight->getId() == std::stoi(id)) {
                
                return true;

            }
        }

        return false;
    }


    Validation(const Validation&) = delete;
    Validation& operator=(const Validation&) = delete;
    Validation(const Validation&&) = delete;
    Validation& operator=(const Validation&&) = delete;
};


// get current time
static string getCurrentTime() {
    std::time_t now = std::time(0);
    std::tm* local_time = std::localtime(&now);

    // Formatowanie czasu do formatu HH:MM
    std::ostringstream time_stream;
    time_stream << std::setfill('0') << std::setw(2) << local_time->tm_hour << ":"
        << std::setfill('0') << std::setw(2) << local_time->tm_min;

    // Zwracamy czas w typie string
    return time_stream.str();
}