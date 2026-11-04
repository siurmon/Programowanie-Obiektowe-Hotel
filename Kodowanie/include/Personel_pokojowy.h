#pragma once
#include "Pracownik.h"

class Personel_Pokojowy : public Pracownik {
public:
    Personel_Pokojowy(int id, std::string im, std::string naz, std::string nr);
    std::string rola() const override;
};