#include "Manager.h"

using namespace std;

Manager::Manager(int id, string imie, string nazwisko, string numer_pracownika) 
    : Pracownik(id, imie, nazwisko, numer_pracownika) {}

string Manager::rola() const { return "Manager"; }