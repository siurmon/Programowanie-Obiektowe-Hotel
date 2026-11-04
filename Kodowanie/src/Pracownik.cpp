#include "Pracownik.h"

Pracownik::Pracownik(int id, std::string imie, std::string nazwisko, std::string nrPracownika) 
    : Osoba(id, imie, nazwisko), numerPracownika(nrPracownika) {}

std::string Pracownik::pobierzNumerPracownika() const { return numerPracownika; }