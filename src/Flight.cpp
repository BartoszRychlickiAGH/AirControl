#pragma once

#include "Flight.hpp"

// methods inherited from interfaces
void Flight::display() {
    cout << "Flight Id: " << id_ << " Date: " << flightDate_ << endl;;
    cout << base_ << " -> " << destination_ << endl;
    cout << departureTime_ << "       " << arrivalTime_ << endl;
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