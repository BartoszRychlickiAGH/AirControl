#pragma once

class IAirport{
    public:
        virtual bool departuresCollision() = 0;
        virtual bool arrivalsCollision() = 0;
        virtual bool isEmpty() = 0;
};