#pragma once

class IAirport{
    public:
        virtual bool isFull() = 0;
        virtual void displayDepartures() = 0;
        virtual void displayArrivals() = 0;
        virtual void displayParked() = 0;
};