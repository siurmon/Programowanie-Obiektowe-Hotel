#include "Personel_Pokojowy.h"

Personel_Pokojowy::Personel_Pokojowy(int id, std::string im, std::string naz, std::string nr) 
    : Pracownik(id, im, naz, nr) {}

std::string Personel_Pokojowy::rola() const { return "Personel Pokojowy"; }