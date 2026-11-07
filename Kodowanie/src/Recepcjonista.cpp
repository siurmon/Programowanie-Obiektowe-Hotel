#include "Recepcjonista.h"

using namespace std;

Recepcjonista::Recepcjonista(int id, const string& imie, const string& nazwisko, const string& numer_pracownika) 
    : Pracownik(id, imie, nazwisko, numer_pracownika) {}

string Recepcjonista::rola() const { return "Recepcjonista"; }