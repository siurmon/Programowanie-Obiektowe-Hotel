#include "Faktura.h"

Faktura::Faktura(std::string numer, int rezId, Data data, Kwota pobyt, Kwota uslugi) 
    : numer(numer), rezerwacjaId(rezId), dataWystawienia(data), kwotaPobytu(pobyt), kwotaUslug(uslugi) {}

Kwota Faktura::suma() const { return kwotaPobytu + kwotaUslug; }

Data Faktura::pobierzDateWystawienia() const { return dataWystawienia; }