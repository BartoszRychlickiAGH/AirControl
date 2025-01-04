#include <iostream>
#include <memory>
#include "validation.hpp"
#include "Database.hpp"

using std::shared_ptr, std::make_shared, std::endl, std::cout;


template<typename T>
vector<string> compress(shared_ptr<T>& obj);


int main(){
    
    
    /*system("echo test");
    
                                    system("timeout /t 5 /nobreak");        <-------  Important
    
    system("cls");*/

    try {
        shared_ptr<Database>db = make_shared<Database>();

        string mode{ "Flights" };
        vector<string>data{ "Krakow","Warsaw","Boeing 747","2025-01-07", "20:44","21:59","-1"};

        db->push(mode,data);
        


    }
    catch (string& e) {
        std::cerr << e << endl;
    }

    return 0;
}



template<typename T>
vector<string> compress(shared_ptr<T>& obj) {
    return obj->compress();
}