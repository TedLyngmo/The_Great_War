#ifndef DIPLOMACY_H
#define DIPLOMACY_H

#pragma once
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <set>
#include "Country.h"

#define RELATIONS_LIMIT 300

enum RequestType {
    alliance, tradeDeal, peaceTreaty
};

struct CountryPair {
public:
    CountryPair(Country* C1, Country* C2);

    bool operator == (const CountryPair& c) const;

    Country* GetC1() const;
    Country* GetC2() const;

private:
    Country *c1, *c2;
};

template<>
struct std::hash<CountryPair> {
    std::size_t operator()(const CountryPair& k) const {
        std::hash<std::string> hasher;

        const std::string& str1 = k.GetC1()->GetTag();
        const std::string& str2 = k.GetC2()->GetTag();

        return hasher(str1 > str2 ? str1 + '\0' + str2 : str2 + '\0' + str1);
    }
};

struct War {
    std::vector<Country*> Side1;
    std::vector<Country*> Side2;
    int Score;
};

class Relations {
public:
    Relations();
    Relations(int relations, bool allied = false);

    void ImproveRelations(int value = 15);
    void WorsenRelations(int value = 15);
    int GetRelationsValue() const;

    void CreateAlliance();
    void BreakAlliance();
    bool GetIfAllied() const;

    void ImposeEmbargo(std::string Instigator);
    void LiftEmbargo(std::string Instigator);
    bool GetIfEmbargoExists();
    bool GetIfHasEmbargo(std::string Instigator);

private:
    std::set<std::string> embargoes;

    int relationsValue;
    bool allied;
};

class Request {
public:
    Request(RequestType id, int senderIndex, std::string senderTag, Relations& rel);

    void Accept();
    void Decline();

    Relations GetRelations();
    std::string GetSender();
    int GetSenderIndex();

private:
    RequestType id;
    int index;
    Relations* rel;
    std::string tag;

};

class Diplomacy {
public:
    std::unordered_map<CountryPair, Relations> relations;
    std::vector<War> wars;
};

#endif
