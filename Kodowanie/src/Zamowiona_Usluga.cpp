#include "Zamowiona_Usluga.h"
#include <stdexcept>

using namespace std;


// przekazujemy obiekt UslugaDodatkowa i ilosc

ZamowionaUsluga::ZamowionaUsluga(const UslugaDodatkowa& usluga, int ilosc) 
    : usluga_id_(usluga.pobierzId()), nazwa_(usluga.pobierzNazwe()), cena_jednostkowa_(usluga.pobierzCene()), ilosc_(ilosc) {
        
        if (ilosc <= 0) {
        throw invalid_argument(
            "Ilosc zamowionych uslug musi byc dodatnia");}}

Kwota ZamowionaUsluga::obliczKoszt() const { return cena_jednostkowa_ * ilosc_; }
