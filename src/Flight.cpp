#include "Flight.hpp"



// constructor
Flight::Flight(string p_id, string p_base, string p_destination, string p_planeName, string p_flightDate, string p_departureTime, string p_arrivalTime, int p_demandIndicator):
    id_(p_id),
    base_(p_base),
    destination_(p_destination),
    planeName_(p_planeName),
    flightDate_(p_flightDate),
    departureTime_(p_departureTime),
    arrivalTime_(p_arrivalTime),
    demandIndicator(p_demandIndicator)
{}


// methods inherited from interfaces
void Flight::display() {
    cout << "Flight Id: " << id_ << " Date: " << flightDate_ << endl;;
    cout << base_ << " -> " << destination_ << endl;
    cout << departureTime_ << "     " << arrivalTime_ << endl;
    cout << "Plane Name: " << planeName_ << endl;
}

void Flight::departure(){
    demandIndicator = 1;
}

void Flight::arrival() {
    demandIndicator = -1;
}

void Flight::park(){
  demandIndicator = 0;  
}

// getters                                             and            setters
string Flight::getId(void)            const{ return id_;  }             void Flight::setId(string p_Id){ id_ = p_Id; }
string Flight::getBase(void)          const{ return base_; }            void Flight::setBase(string p_Base){ base_ = p_Base; }
string Flight::getDestination(void)   const{ return destination_;}      void Flight::setDestination(string p_Destination){ destination_ = p_Destination; }
string Flight::getPlaneName(void)     const{ return planeName_; }       void Flight::setPlaneName(string p_PlaneName){ planeName_  = p_PlaneName; }
string Flight::getFlightDate(void)    const{ return flightDate_; }      void Flight::setFlightDate(string p_FlightDate){ flightDate_ = p_FlightDate; }
string Flight::getDepartureTime(void) const{return departureTime_;}     void Flight::setDepartureTime(string p_DepartureTime){ departureTime_ = p_DepartureTime; }
string Flight::getArrivalTime(void)   const{ return arrivalTime_; }     void Flight::setArrivalTime(string p_ArrivalTime){ arrivalTime_ = p_ArrivalTime;}
int Flight::getDemandIndicator(void)  const{ return demandIndicator;}   void Flight::setdemandIndicator(int p_demandIndicator){demandIndicator = p_demandIndicator;}