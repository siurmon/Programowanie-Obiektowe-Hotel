#pragma once
#include <vector>
#include "common.h"
#include "Rezerwacja.h"

class Statystyki {
private:
    Data okresOd;
    Data okresDo;
    int liczbaRezerwacji;
    double oblozenieProc;
    Kwota przychodZFaktur;
public:
    Statystyki(Data od, Data do);
    
    void oblicz(const std::vector<Rezerwacja>& rezerwacje, int liczbaPokoi, Data od, Data do);
    
    // Gettery
    double pobierzOblozenie() const;
    Kwota pobierzPrzychod() const;
    int pobierzLiczbeRezerwacji() const;
};