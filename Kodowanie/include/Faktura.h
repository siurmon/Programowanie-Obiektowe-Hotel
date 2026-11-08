#pragma once
#include <string>
#include "typy.h"
class Faktura {
private:
    std::string numer_;
    int rezerwacja_id_;
    Data data_wystawienia_;
    Kwota kwota_pobytu_;
    Kwota kwota_uslug_;
public:
    Faktura(const std::string& numer, int rezerwacja_id, const Data& data, Kwota kwota_pobytu, Kwota kwota_uslug);
    Kwota suma() const; 
    Data pobierzDateWystawienia() const;
    std::string pobierzNumer() const;
};