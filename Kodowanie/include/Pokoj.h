#pragma once
#include "common.h"
class Pokoj {
private:
    int numer_pokoju;
    int liczbaMiejsc;
    Kwota stawkaDobowa;
    StatusSprzatania statusSprzatania;
public:
    Pokoj(int numer, int miejsca, Kwota stawka);
    Kwota pobierzStawke() const;
    StatusSprzatania pobierzStatusSprzatania() const;
    void ustawStatusSprzatania(StatusSprzatania status);
    int pobierzNumerPokoju() const;
};