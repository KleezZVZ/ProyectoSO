#ifndef DATA_H
#define DATA_H

#include <string>

class Data{
    std::string name;
    int initialTime;
    int durationTime;
    int finalTime;
    int totalTime;
    int waitTime;
    float serviceIndex;
    bool visited;

    public:
        Data(std::string ,int, int);
        std::string getName();
        int getInitialTime();
        int getDurationTime();
        int getFinalTime();
        int getTotalTime();
        int getwaitTime();
        float getServiceIndex();
        bool getVisited();
        void setFinalTime(int);
        void setTotalTime(int);
        void setwaitTime(int);
        void setServiceIndex(float);
        void setVisited(bool);
        void resetData();
};

#endif