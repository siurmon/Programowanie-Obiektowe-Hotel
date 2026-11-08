#include "Pokoj.h"

using namespace std;

Pokoj::Pokoj(int numer_pokoju, int liczba_miejsc, Kwota stawka_dobowa) 
    : numer_pokoju_(numer_pokoju), liczba_miejsc_(liczba_miejsc), stawka_dobowa_(stawka_dobowa), status_sprzatania_(StatusSprzatania::Czysty) {}

void Pokoj::ustawStatusSprzatania(StatusSprzatania status) { status_sprzatania_ = status; }

StatusSprzatania Pokoj::pobierzStatusSprzatania() const { return status_sprzatania_; }

int Pokoj::pobierzNumerPokoju() const { return numer_pokoju_; }
int Pokoj::pobierzLiczbeMiejsc() const { return liczba_miejsc_; }
Kwota Pokoj::pobierzStawke() const { return stawka_dobowa_; }