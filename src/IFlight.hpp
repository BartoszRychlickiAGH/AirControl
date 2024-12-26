#pragma once

class IFlight{
    public:
        virtual void departure() = 0;
        virtual void arrival() = 0;
        virtual void park() = 0;
};