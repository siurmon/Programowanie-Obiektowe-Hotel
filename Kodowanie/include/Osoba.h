#pragma once
#include <string>

class Osoba {
private: 
    int id_;
    std::string imie_;
    std::string nazwisko_;
public:
    Osoba(int id, const std::string& imie, const std::string& nazwisko);
    virtual ~Osoba();
    int pobierzId() const;
    virtual std::string rola() const = 0; // abstract
    std::string pobierzImie() const;
    std::string pobierzNazwisko() const;
};