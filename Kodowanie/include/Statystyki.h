#pragma once
#include <vector>
#include "typy.h"

class Rezerwacja;

class Statystyki {
private:
    Data okres_od_;
    Data okres_do_;
    int liczba_rezerwacji_;
    double oblozenie_proc_;
    Kwota przychod_z_faktur_;
public:
    Statystyki();
    
    void oblicz(const std::vector<Rezerwacja>& rezerwacje, int liczba_pokoi, const Data& od, const Data& do_daty);
    
    // Gettery
    double pobierzOblozenie() const;
    Kwota pobierzPrzychod() const;
    int pobierzLiczbeRezerwacji() const;
};

