#include "Gosc.h"
using namespace std;

Gosc::Gosc(int id, const string& imie, const string& nazwisko, const string& email, const string& telefon) 
    : Osoba(id, imie, nazwisko), email_(email), telefon_(telefon) {}

string Gosc::rola() const { return "Gosc"; }

string Gosc::pobierzEmail() const { return email_; }
string Gosc::pobierzTelefon() const { return telefon_; }