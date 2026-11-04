#include "Zamowiona_Usluga.h"

Zamowiona_Usluga::Zamowiona_Usluga(int id, std::string nazwa, Kwota cena, int ilosc) 
    : uslugaId(id), nazwa(nazwa), cenaJednostkowa(cena), ilosc(ilosc) {}

Kwota Zamowiona_Usluga::obliczKoszt() const { return cenaJednostkowa * ilosc; }