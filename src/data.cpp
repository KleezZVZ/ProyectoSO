#include "data.h"
#include <string>

Data::Data(std::string _name, int _initialTime, int _durationTime){
    name = _name;
    initialTime = _initialTime;
    durationTime = _durationTime;
    finalTime = totalTime = waitTime = 0;
    visited = false;
}

std::string Data::getName(){
    return name;
}

int Data::getInitialTime(){
    return initialTime;
}

int Data::getDurationTime(){
    return durationTime;
}

int Data::getFinalTime(){
    return finalTime;
}

int Data::getTotalTime(){
    return totalTime;
}

int Data::getwaitTime(){
    return waitTime;
}

float Data::getServiceIndex(){
    return serviceIndex;
}

bool Data::getVisited(){
    return visited;
}

void Data::setFinalTime(int _finalTime){
    finalTime = _finalTime;
}

void Data::setTotalTime(int _totalTime){
    totalTime = _totalTime;
}

void Data::setwaitTime(int _waitTime){
    waitTime = _waitTime;
}

void Data::setServiceIndex(float _serviceIndex){
    serviceIndex = _serviceIndex;
}

void Data::setVisited(bool _visited){
    visited = _visited;
}

void Data::resetData(){
    finalTime = totalTime = waitTime = serviceIndex = visited = 0;
}