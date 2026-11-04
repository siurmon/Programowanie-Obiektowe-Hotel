#pragma once
#include <string>

class Osoba {
protected: 
    int id;
    std::string imie;
    std::string nazwisko;
public:
    Osoba(int id, std::string imie, std::string nazwisko);
    virtual ~Osoba() = default;
    int pobierzId() const;
    virtual std::string rola() const = 0; // abstract
};