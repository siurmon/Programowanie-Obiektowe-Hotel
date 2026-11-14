#pragma once
#include <string>
#include "Typy.h"

class ZamowionaUsluga {
private:
    int usluga_id_;
    std::string nazwa_;
    Kwota cena_jednostkowa_;
    int ilosc_;
public:
    ZamowionaUsluga(int usluga_id, const std::string& nazwa, Kwota cena_jednostkowa, int ilosc);
    Kwota obliczKoszt() const; 
    int pobierzUslugaId() const;
    int pobierzIlosc() const;
    std::string pobierzNazwe() const;
};

