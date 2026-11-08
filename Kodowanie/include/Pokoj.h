#pragma once
#include "typy.h"
class Pokoj {
private:
    int numer_pokoju_;
    int liczba_miejsc_;
    Kwota stawka_dobowa_;
    StatusSprzatania status_sprzatania_;
public:
    Pokoj(int numer_pokoju, int liczba_miejsc, Kwota stawka_dobowa);
    Kwota pobierzStawke() const;
    StatusSprzatania pobierzStatusSprzatania() const;
    void ustawStatusSprzatania(StatusSprzatania status);
    int pobierzNumerPokoju() const;
    int pobierzLiczbeMiejsc() const;
};