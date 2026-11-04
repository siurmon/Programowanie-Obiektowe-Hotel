#pragma once
#include <string>
#include "common.h"
class Zamowiona_Usluga {
private:
    int uslugaId;
    std::string nazwa;
    Kwota cenaJednostkowa;
    int ilosc;
public:
    Zamowiona_Usluga(int id, std::string nazwa, Kwota cena, int ilosc);
    Kwota obliczKoszt() const; 
};