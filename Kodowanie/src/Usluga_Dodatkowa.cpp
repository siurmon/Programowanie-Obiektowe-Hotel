#include "Usluga_Dodatkowa.h"
#include <stdexcept>

using namespace std;

UslugaDodatkowa::UslugaDodatkowa(int id, const string& nazwa, Kwota cena_jednostkowa, const string& jednostka) 
    : id_(id), nazwa_(nazwa), cena_jednostkowa_(cena_jednostkowa), jednostka_(jednostka) {

        if (id <= 0 || nazwa.empty() || jednostka.empty() ||
        cena_jednostkowa < 0.0) {
        throw invalid_argument("Nieprawidlowe dane uslugi");}}

int UslugaDodatkowa::pobierzId() const { return id_; }
string UslugaDodatkowa::pobierzNazwe() const { return nazwa_; }
Kwota UslugaDodatkowa::pobierzCene() const { return cena_jednostkowa_; }