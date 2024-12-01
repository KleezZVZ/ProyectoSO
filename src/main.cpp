#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "data.h"
#include <windows.h>
#include <string>
using namespace std;

vector<Data> times;
float bestServiceValue = 0;
int bestAlgorithmIndex;
string names[] = {"FIFO", "LIFO", "Round Robin"};

int loadData(string);
void fifo();
void lifo();
void roundRobin(int);
void resetData();
void winner();

int main(int argc, char** argv){
    if(stoi(argv[2]) <= 0){
        cout<<"No ingreso un quantum valido."<<endl;
        return 0;
    }
    if(loadData(argv[1]) == -1){
        return 0;
    }
    cout<<"Ejecutando FIFO:"<<endl;
    fifo();
    resetData();
    cout<<endl;
    cout<<"Ejecutando LIFO:"<<endl;
    lifo();
    resetData();
    cout<<endl;
    cout<<"Ejecutando Round Robin: "<<endl;
    roundRobin(stoi(argv[2]));
    cout<<endl;
    winner();
    system("pause");
    return 0;
}

int loadData(string path){
    string line, word;
    int count = 0;

    ifstream inFile(path, ifstream::in);
    if(!inFile.is_open()){
        cout<<"Archivo no encontrado."<<endl;
        return -1;
    }

    string name;
    int initialTime, durationTime;

    while(getline(inFile, line)){
        stringstream str(line);
        while(getline(str, word, ',')){
            switch(count){
                case 0: name = word; break;
                case 1: initialTime = stoi(word); break;
                case 2: durationTime = stoi(word); break;
            }
            count++;
        }
        times.push_back(Data(name, initialTime, durationTime));
        count = 0;
    }
    inFile.close();
    return 0;
}

void resetData(){
    for(int i = 0; i < times.size(); i++){
        times[i].resetData();
    }
}

void winner(){
    cout<<"El algoritmo mas eficiente en tiempo de servicio, ha sido: "<<names[bestAlgorithmIndex]<<endl;
    cout<<"Con un indice de servicio de: "<<bestServiceValue<<endl;

}

void fifo(){
    auto now = chrono::system_clock::now();
    auto start = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    int clock = 0;
    int count = 0;
    float totalTimeT, waitTimeT, serviceIndexT;
    totalTimeT = waitTimeT = serviceIndexT = 0;
    bool finished = false;
    bool clockUp = false;
    while(!finished){
        for(int i = 0; i < times.size(); i++){
            if(times[i].getInitialTime() <= clock && !times[i].getVisited()){
                int ft, T, e;
                float I;
                ft = times[i].getDurationTime() + clock;
                T = ft - times[i].getInitialTime();
                e = T - times[i].getDurationTime();
                I = float(times[i].getDurationTime()) / T;
                totalTimeT += T;
                waitTimeT += e;
                serviceIndexT += I;
                times[i].setFinalTime(ft);
                times[i].setTotalTime(T);
                times[i].setwaitTime(e);
                times[i].setServiceIndex(I);
                times[i].setVisited(true);
                Sleep(times[i].getDurationTime() * 10);
                clock += times[i].getDurationTime();
                clockUp = true;
                count++;
                break;
            }else if(count >= times.size()){
                finished = true;
            }
        }
        if(!clockUp && !finished){
            clock++;
        }
        clockUp = false;
    }
    now = chrono::system_clock::now();
    auto end = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    auto total = end - start;
    int divisor = times.size();
    totalTimeT /= divisor;
    waitTimeT /= divisor;
    serviceIndexT /= divisor;

    for(int i = 0; i < times.size(); i++){
        if(i == 0){
            cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"Proceso\t|\t ti \t|\t t \t|\t tf \t|\t T \t|\t E \t|\t I "<<endl;
        }
        cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<times[i].getName()<<"\t|\t"<<times[i].getInitialTime()<<"\t|\t"<<times[i].getDurationTime()<<"\t|\t"<<times[i].getFinalTime()<<"\t|\t"<<times[i].getTotalTime()<<"\t|\t"<<times[i].getwaitTime()<<"\t|\t"<<times[i].getServiceIndex()<<endl;
        if(i == (times.size() - 1)){
            cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
        }      
    }

    if(bestServiceValue < serviceIndexT){
        bestServiceValue = serviceIndexT;
        bestAlgorithmIndex = 0;
    }

    cout<<"\nTiempo Total: "<<totalTimeT<<". Tiempo de Espera: "<<waitTimeT<<". Indice de Servicio: "<<serviceIndexT<<". Tiempo(ms): "<<total<<endl;
    cout<<"Reloj final: "<<clock<<endl;
}

void lifo(){
    auto now = chrono::system_clock::now();
    auto start = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    int clock = 0;
    int count = 0;
    float totalTimeT, waitTimeT, serviceIndexT;
    totalTimeT = waitTimeT = serviceIndexT = 0;
    bool finished = false;
    bool clockUp = false;
    while(!finished){
        for(int i = times.size() - 1; i >= 0; i--){
            if(times[i].getInitialTime() <= clock && !times[i].getVisited()){
                int ft, T, e;
                float I;
                ft = times[i].getDurationTime() + clock;
                T = ft - times[i].getInitialTime();
                e = T - times[i].getDurationTime();
                I = float(times[i].getDurationTime()) / T;
                totalTimeT += T;
                waitTimeT += e;
                serviceIndexT += I;
                times[i].setFinalTime(ft);
                times[i].setTotalTime(T);
                times[i].setwaitTime(e);
                times[i].setServiceIndex(I);
                times[i].setVisited(true);
                Sleep(times[i].getDurationTime() * 10);
                clock += times[i].getDurationTime();
                clockUp = true;
                count ++;
                break;
            }else if(count >= times.size()){
                finished = true;
            }
        }
        if(!clockUp && !finished){
            clock++;
        }
        clockUp = false;
    }
    now = chrono::system_clock::now();
    auto end = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    auto total = end - start;
    int divisor = times.size();
    totalTimeT /= divisor;
    waitTimeT /= divisor;
    serviceIndexT /= divisor;

    for(int i = 0; i < times.size(); i++){
        if(i == 0){
            cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"Proceso\t|\t ti \t|\t t \t|\t tf \t|\t T \t|\t E \t|\t I "<<endl;
        }
        cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<times[i].getName()<<"\t|\t"<<times[i].getInitialTime()<<"\t|\t"<<times[i].getDurationTime()<<"\t|\t"<<times[i].getFinalTime()<<"\t|\t"<<times[i].getTotalTime()<<"\t|\t"<<times[i].getwaitTime()<<"\t|\t"<<times[i].getServiceIndex()<<endl;
        if(i == (times.size() - 1)){
            cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
        }      
    }

    if(bestServiceValue < serviceIndexT){
        bestServiceValue = serviceIndexT;
        bestAlgorithmIndex = 1;
    }

    cout<<"Tiempo Total: "<<totalTimeT<<". Tiempo de Espera: "<<waitTimeT<<". Indice de Servicio: "<<serviceIndexT<<". Tiempo(ms): "<<total<<endl;
    cout<<"Reloj final: "<<clock<<endl;
}

void roundRobin(int quantum){
    auto now = chrono::system_clock::now();
    auto start = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    int clock = 0;
    int count = 0;
    float totalTimeT, waitTimeT, serviceIndexT;
    totalTimeT = waitTimeT = serviceIndexT = 0;
    bool finished = false;
    bool clockUp = false;
    vector<int> secondDurationTime;
    for(int i = 0; i < times.size(); i++){
        secondDurationTime.push_back(times[i].getDurationTime());
    }
    while(!finished){
        for(int i = 0; i <  times.size(); i++){
            if(times[i].getInitialTime() <= clock && !times[i].getVisited()){
                if(secondDurationTime[i] > quantum){
                    secondDurationTime[i] -= quantum;
                    Sleep(quantum * 10);
                    clock += quantum;
                    clockUp = true;
                }else{
                    int ft, T, e;
                    float I;
                    ft = secondDurationTime[i] + clock;
                    T = ft - times[i].getInitialTime();
                    e = T - times[i].getDurationTime();
                    I = float(times[i].getDurationTime()) / T;
                    totalTimeT += T;
                    waitTimeT += e;
                    serviceIndexT += I;
                    times[i].setFinalTime(ft);
                    times[i].setTotalTime(T);
                    times[i].setwaitTime(e);
                    times[i].setServiceIndex(I);
                    times[i].setVisited(true);
                    Sleep(secondDurationTime[i] * 10);
                    clock += secondDurationTime[i];
                    clockUp = true;
                    count++;
                }
            }else if(count >= times.size()){
                finished = true;
            }
        }
        if(!clockUp && !finished){
            clock++;
        }
        clockUp = false;
    }
    now = chrono::system_clock::now();
    auto end = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
    auto total = end - start;
    int divisor = times.size();
    totalTimeT /= divisor;
    waitTimeT /= divisor;
    serviceIndexT /= divisor;

    for(int i = 0; i < times.size(); i++){
        if(i == 0){
            cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
            cout<<"Proceso\t|\t ti \t|\t t \t|\t tf \t|\t T \t|\t E \t|\t I "<<endl;
        }
        cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<times[i].getName()<<"\t|\t"<<times[i].getInitialTime()<<"\t|\t"<<times[i].getDurationTime()<<"\t|\t"<<times[i].getFinalTime()<<"\t|\t"<<times[i].getTotalTime()<<"\t|\t"<<times[i].getwaitTime()<<"\t|\t"<<times[i].getServiceIndex()<<endl;
        if(i == (times.size() - 1)){
            cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
        }      
    }

    if(bestServiceValue < serviceIndexT){
        bestServiceValue = serviceIndexT;
        bestAlgorithmIndex = 2;
    }

    cout<<"\nTiempo Total: "<<totalTimeT<<". Tiempo de Espera: "<<waitTimeT<<". Indice de Servicio: "<<serviceIndexT<<". Tiempo(ms): "<<total<<endl;
    cout<<"Reloj final: "<<clock<<endl;
}