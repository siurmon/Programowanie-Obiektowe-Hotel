#include "Personel_Pokojowy.h"

using namespace std;


Personel_Pokojowy::Personel_Pokojowy(int id, string imie, string nazwisko, string numer_pracownika) 
    : Pracownik(id, imie, nazwisko, numer_pracownika) {}

string Personel_Pokojowy::rola() const { return "Personel Pokojowy"; }