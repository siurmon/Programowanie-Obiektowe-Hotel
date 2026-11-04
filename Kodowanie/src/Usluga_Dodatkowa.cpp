#include "Usluga_Dodatkowa.h"

Usluga_Dodatkowa::Usluga_Dodatkowa(int id, std::string nazwa, Kwota cena, std::string jednostka) 
    : id(id), nazwa(nazwa), cenaJednostkowa(cena), nazwaJednostki(jednostka) {}

int Usluga_Dodatkowa::pobierzId() const { return id; }

std::string Usluga_Dodatkowa::pobierzNazwe() const { return nazwa; }

Kwota Usluga_Dodatkowa::pobierzCene() const { return cenaJednostkowa; }