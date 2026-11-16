#include "Administrator.h"
using namespace std;

Administrator::Administrator(int id, const string& imie, const string& nazwisko, const string& numer_pracownika) 
    : Pracownik(id, imie, nazwisko, numer_pracownika) {}

string Administrator::rola() const { return "Administrator"; }