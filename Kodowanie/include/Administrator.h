#pragma once
#include "Pracownik.h"

class Administrator : public Pracownik {
public:
    Administrator(int id, std::string imie, std::string nazwisko, std::string numer_pracownika);
    std::string rola() const override;
};