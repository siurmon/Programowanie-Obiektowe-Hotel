#include "Personel_pokojowy.h"

using namespace std;


PersonelPokojowy::PersonelPokojowy(int id, const string& imie, const string& nazwisko, const string& numer_pracownika) 
    : Pracownik(id, imie, nazwisko, numer_pracownika) {}

string PersonelPokojowy::rola() const { return "Personel Pokojowy"; }