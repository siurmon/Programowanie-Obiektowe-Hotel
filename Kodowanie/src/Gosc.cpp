#include "Gosc.h"

Gosc::Gosc(int id, std::string imie, std::string nazwisko, std::string email, std::string telefon) 
    : Osoba(id, imie, nazwisko), email(email), telefon(telefon) {}

std::string Gosc::rola() const { return "Gosc"; }