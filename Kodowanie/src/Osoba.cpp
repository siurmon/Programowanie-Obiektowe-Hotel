#include "Osoba.h"

Osoba::Osoba(int id, std::string imie, std::string nazwisko) 
    : id(id), imie(imie), nazwisko(nazwisko) {}

int Osoba::pobierzId() const { return id; }