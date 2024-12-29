#include <iostream>

using std::endl, std::cout;

#include "validation.hpp"

int main(){
    
    // cout << getCurrentTime() << endl;
    cout << ((Validation::isTime(getCurrentTime()))? "yes":"no") << endl;


    return 0;
}