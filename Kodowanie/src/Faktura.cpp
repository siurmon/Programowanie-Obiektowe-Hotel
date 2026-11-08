#include "Faktura.h"
using namespace std;

Faktura::Faktura(const std::string& numer, int rezerwacja_id, const Data& data, Kwota kwota_pobytu, Kwota kwota_uslug) 
    : numer_(numer), rezerwacja_id_(rezerwacja_id), data_wystawienia_(data), kwota_pobytu_(kwota_pobytu), kwota_uslug_(kwota_uslug) {}

Kwota Faktura::suma() const { return kwota_pobytu_ + kwota_uslug_; }

string Faktura::pobierzNumer() const { return numer_; }

Data Faktura::pobierzDateWystawienia() const { return data_wystawienia_; }