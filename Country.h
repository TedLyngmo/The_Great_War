#ifndef COUNTRY_H
#define COUNTRY_H

#include <unordered_map>
#include <string>
#include "State.h"
#include "Stockpile.h"

class Country {
public:
    //Functions

    //Constructor
    Country(std::string tag, int r, int g, int b, int Res[31]);

    //Destructor
    ~Country();

    void AddState(State* state);

    void RemoveState(State* state);

    //This is the representing the pass of a single day
    void Tick();

    //Variables
    std::string countrytag;
    std::unordered_map<std::string, State*>* OwnedStates;
    int Country_State_Count;
    int Country_Population;

    struct {
        float FactoryInput;
        float FactoryThroughput;
        float FactoryOutput;
        float MineralOutput;
        float FarmOutput;
        float WoodOutput;
    } Technology;

    struct {
        int red;
        int green;
        int blue;
    } Color;

    struct {
        int TaxRate;
        int Healthcare;
    } Policy;

    //A country's currently stockpiled resources
    Stockpile Stock;
};

#endif