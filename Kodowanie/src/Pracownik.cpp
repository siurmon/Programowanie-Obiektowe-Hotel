#include "Pracownik.h"

using namespace std;

Pracownik::Pracownik(int id, const string& imie, const string& nazwisko, const string& numer_pracownika) 
    : Osoba(id, imie, nazwisko), numer_pracownika_(numer_pracownika) {}

string Pracownik::pobierzNumerPracownika() const { return numer_pracownika_; }