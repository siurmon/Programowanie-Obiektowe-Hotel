#pragma once
#include "Osoba.h"

class Pracownik : public Osoba {
private:
    std::string numerPracownika;
public:
    Pracownik(int id, std::string imie, std::string nazwisko, std::string nrPracownika);
    std::string pobierzNumerPracownika() const;
    virtual std::string rola() const = 0;
};