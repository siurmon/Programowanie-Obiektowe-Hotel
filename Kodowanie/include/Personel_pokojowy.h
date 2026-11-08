#pragma once
#include "Pracownik.h"

class PersonelPokojowy : public Pracownik {
public:
    PersonelPokojowy(int id, std::string imie, std::string nazwisko, std::string numer_pracownika);
    std::string rola() const override;
};