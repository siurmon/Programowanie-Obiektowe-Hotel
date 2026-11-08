#pragma once
#include <string>
#include "typy.h"

class UslugaDodatkowa;

class ZamowionaUsluga {
private:
    int usluga_id_;
    std::string nazwa_;
    Kwota cena_jednostkowa_;
    int ilosc_;
public:
    ZamowionaUsluga(const UslugaDodatkowa& usluga, int ilosc);
    Kwota obliczKoszt() const; 
    int pobierzUslugaId() const;
    int pobierzIlosc() const;
    std::string pobierzNazwe() const;
};

