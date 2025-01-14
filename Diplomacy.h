#ifndef DIPLOMACY_H
#define DIPLOMACY_H

#pragma once
#include <array>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

class Country;

struct CountryPair {
public:
    CountryPair(Country* C1, Country* C2);

    bool operator==(const CountryPair& c) const;

    Country* GetC1() const;
    Country* GetC2() const;
    std::string toString() const;

private:
    Country *c1, *c2;
};

template<>
struct std::hash<CountryPair> {
    std::size_t operator()(const CountryPair& k) const {
        std::hash<std::string> hasher;

        return hasher(k.toString());
    }
};

enum ClaimType { territory, reparations };

struct Claim {
public:
    Claim(Country* Owner, Country* Target, ClaimType Type, void* Data);

    Country* GetOwner() const;
    Country* GetTarget() const;
    ClaimType GetType() const;

protected:
    Country *owner, *target;

    ClaimType type;
    void* data;
};

class War {
public:
    War(Claim claim);

    bool GetIfTargetPairIsAtWar(const CountryPair& pair) const;
    void JoinWar(Country* newParticipant, Country* onTheSideOf);
    const std::set<Country*>& GetFaction(unsigned i) const;

    void AddClaim(Claim claim);
    const std::vector<Claim>& GetClaims(unsigned i) const;

    void AddScore(Country* instigator, int score);
    int GetRelativeScore() const;

private:
    struct Faction {
        Faction(Country* c);

        void AddMember(Country* c);
        void RemoveMember(Country* c);
        bool Contains(Country* c) const;
        const std::set<Country*>& GetFaction() const;

        void AddScore(int c);
        int GetScore() const;

        void AddClaim(Claim c);
        const std::vector<Claim>& GetClaims() const;

    private:
        std::set<Country*> members;
        std::vector<Claim> claims;

        static const int scoreLimit = 100;
        int score = 0;
    };

    std::array<Faction, 2> factions;
};

class Relation {
public:
    Relation();
    Relation(int relations, bool allied = false);

    void DeclareWar(Claim claim);
    bool GetIfAtWar() const;

    void AddClaim(Claim claim);
    const std::vector<Claim> GetClaims(Country* c = nullptr);

    void ImproveRelations(int value = 15);
    void WorsenRelations(int value = 15);
    int GetRelationsValue() const;

    void CreateAlliance();
    void BreakAlliance();
    bool GetIfAllied() const;

    void CreateNonAggressionPact();
    void BreakNonAggressionPact();
    bool GetIfHasNonAggressionPact();

    void ImposeEmbargo(std::string Instigator);
    void LiftEmbargo(std::string Instigator);
    bool GetIfEmbargoExists() const;
    bool GetIfHasEmbargo(std::string Instigator) const;

private:
    static constexpr int RELATIONS_LIMIT = 300;

    static std::vector<War> wars;
    friend class Diplomacy;

    std::vector<std::string> embargoes;
    std::vector<Claim> claims;

    int relationsValue;
    bool allied;
    bool nonAggressionPact;
};

enum RequestType { alliance, nonAgressionPact, tradeDeal, peaceTreaty };

class Request {
public:
    Request(RequestType id, unsigned senderIndex, std::string senderTag, Relation& rel);

    void Accept();
    void Decline();

    Relation& GetRelations() const;
    std::string GetSender() const;
    unsigned GetSenderIndex() const;

private:
    RequestType id;
    unsigned index;
    Relation& rel;
    std::string tag;
};

class Diplomacy {
public:
    Diplomacy();

    std::unordered_map<CountryPair, Relation> relations;
};
#endif
