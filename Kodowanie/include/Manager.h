#pragma once
#include "Pracownik.h"

class Manager : public Pracownik {
public:
    Manager(int id, std::string imie, std::string nazwisko, std::string numer_pracownika);
    std::string rola() const override;
};