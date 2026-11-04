#pragma once
#include <string>
#include "common.h"
class Usluga_Dodatkowa {
private:
    int id;
    std::string nazwa;
    Kwota cenaJednostkowa;
    std::string nazwaJednostki;
public:
    Usluga_Dodatkowa(int id, std::string nazwa, Kwota cena, std::string jednostka);
    int pobierzId() const;
    std::string pobierzNazwe() const;
    Kwota pobierzCene() const;
};