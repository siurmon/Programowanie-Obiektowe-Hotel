#pragma once
#include <string>
#include "common.h"
class Faktura {
private:
    std::string numer;
    int rezerwacjaId;
    Data dataWystawienia;
    Kwota kwotaPobytu;
    Kwota kwotaUslug;
public:
    Faktura(std::string numer, int rezId, Data data, Kwota pobyt, Kwota uslugi);
    Kwota suma() const; 
    Data pobierzDateWystawienia() const;
};