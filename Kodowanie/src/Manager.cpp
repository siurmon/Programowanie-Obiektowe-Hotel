#include "Manager.h"

using namespace std;

Manager::Manager(int id, const string& imie, const string& nazwisko, const string& numer_pracownika) 
    : Pracownik(id, imie, nazwisko, numer_pracownika) {}

string Manager::rola() const { return "Manager"; }