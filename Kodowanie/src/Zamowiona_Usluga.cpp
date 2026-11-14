#include "Zamowiona_Usluga.h"

#include <stdexcept>

using namespace std;

ZamowionaUsluga::ZamowionaUsluga(int usluga_id, const string& nazwa, Kwota cena_jednostkowa, int ilosc)
    : usluga_id_(usluga_id), nazwa_(nazwa), cena_jednostkowa_(cena_jednostkowa), ilosc_(ilosc) {
        
    if (usluga_id <= 0 || nazwa.empty() ||
        cena_jednostkowa < 0.0 || ilosc <= 0) {
        throw invalid_argument("Nieprawidlowe dane zamowionej uslugi");
    }
}

Kwota ZamowionaUsluga::obliczKoszt() const { return cena_jednostkowa_ * ilosc_;}

int ZamowionaUsluga::pobierzUslugaId() const { return usluga_id_; }
int ZamowionaUsluga::pobierzIlosc() const { return ilosc_; }
string ZamowionaUsluga::pobierzNazwe() const { return nazwa_; }
