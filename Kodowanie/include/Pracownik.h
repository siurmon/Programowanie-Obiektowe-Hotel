#pragma once
#include "Osoba.h"

class Pracownik : public Osoba {
private:
    std::string numer_pracownika_;
public:
    Pracownik(int id, const std::string& imie, const std::string& nazwisko, const std::string& numer_pracownika);
    std::string pobierzNumerPracownika() const;
    std::string rola() const override = 0;
};