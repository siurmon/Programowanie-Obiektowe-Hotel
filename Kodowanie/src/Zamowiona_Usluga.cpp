#include "Zamowiona_Usluga.h"

using namespace std;


// przekazujemy obiekt UslugaDodatkowa i ilosc

ZamowionaUsluga::ZamowionaUsluga(const UslugaDodatkowa& usluga, int ilosc) 
    : usluga_id_(usluga.pobierzId()), nazwa_(usluga.pobierzNazwe()), cena_jednostkowa_(usluga.pobierzCene()), ilosc_(ilosc) {}

Kwota ZamowionaUsluga::obliczKoszt() const { return cena_jednostkowa_ * ilosc_; }