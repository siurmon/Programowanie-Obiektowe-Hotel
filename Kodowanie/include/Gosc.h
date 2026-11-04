#pragma once
#include "Osoba.h"

class Gosc : public Osoba {
private:
    std::string email;
    std::string telefon;
public:
    Gosc(int id, std::string imie, std::string nazwisko, std::string email, std::string telefon);
    std::string rola() const override;
};