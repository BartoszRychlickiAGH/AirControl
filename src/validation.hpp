#pragma once

#include <string>
#include <ctime>
#include <regex>
#include <sstream>
#include <iomanip>


using std::string, std::regex_match, std::regex;

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

    Validation(const Validation&) = delete;
    Validation& operator=(const Validation&) = delete;
    Validation(const Validation&&) = delete;
    Validation& operator=(const Validation&&) = delete;
};


// get current time
static string getCurrentTime() {
    std::time_t now = std::time(0);
    std::tm* local_time = std::localtime(&now);

    // Formatowanie czasu w formacie HH:MM
    std::ostringstream time_stream;
    time_stream << std::setfill('0') << std::setw(2) << local_time->tm_hour << ":"
        << std::setfill('0') << std::setw(2) << local_time->tm_min;

    // Zwracamy czas w formacie string
    return time_stream.str();
}