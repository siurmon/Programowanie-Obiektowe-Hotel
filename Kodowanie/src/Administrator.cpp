#include "Administrator.h"
using namespace std;

Administrator::Administrator(int id, string imie, string nazwisko, string numer_pracownika) 
    : Pracownik(id, imie, nazwisko, numer_pracownika) {}

string Administrator::rola() const { return "Administrator"; }