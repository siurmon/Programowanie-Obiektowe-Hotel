#include "Usluga_Dodatkowa.h"

using namespace std;

UslugaDodatkowa::UslugaDodatkowa(int id, const string& nazwa, Kwota cena_jednostkowa, const string& jednostka) 
    : id_(id), nazwa_(nazwa), cena_jednostkowa_(cena_jednostkowa), jednostka_(jednostka) {}

int UslugaDodatkowa::pobierzId() const { return id_; }

string UslugaDodatkowa::pobierzNazwe() const { return nazwa_; }

Kwota UslugaDodatkowa::pobierzCene() const { return cena_jednostkowa_; }