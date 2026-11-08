#pragma once
#include "Pracownik.h"

class Recepcjonista : public Pracownik {
public:
    Recepcjonista(int id, const std::string& imie, const std::string& nazwisko, const std::string& numer_pracownika);
    std::string rola() const override;
};