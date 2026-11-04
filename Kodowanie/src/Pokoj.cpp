#include "Pokoj.h"

Pokoj::Pokoj(int numer, int miejsca, Kwota stawka) 
    : numer_pokoju(numer), liczbaMiejsc(miejsca), stawkaDobowa(stawka), statusSprzatania(StatusSprzatania::GOTOWY) {}
    
    Kwota Pokoj::pobierzStawke() const { return stawkaDobowa; }

StatusSprzatania Pokoj::pobierzStatusSprzatania() const { return statusSprzatania; }

void Pokoj::ustawStatusSprzatania(StatusSprzatania status) { statusSprzatania = status; }

int Pokoj::pobierzNumerPokoju() const { return numer_pokoju; }