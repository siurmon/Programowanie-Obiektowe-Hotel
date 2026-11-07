#include "Osoba.h"

using namespace std;

Osoba::Osoba(int id, const string& imie, const string& nazwisko) 
    : id_(id), imie_(imie), nazwisko_(nazwisko) {}

Osoba::~Osoba() = default;

int Osoba::pobierzId() const { return id_; }