#pragma once
#include <vector>
#include <optional>
#include "common.h"
#include "Faktura.h"
#include "Zamowiona_Usluga.h"
#include "Usluga_Dodatkowa.h"

class Rezerwacja {
private:
    int id;
    int goscId;
    int pokojId;
    Data dataOd;
    Data dataDo;
    DataCzas utworzono;
    StatusRezerwacji status;
    Kwota stawkaZaDobe;
    std::optional<Faktura> faktura;
    std::vector<Zamowiona_Usluga> zamowioneUslugi;
    Kwota oplataAnulowania;
public:
    Rezerwacja(int id, int goscId, int pokojId, Data od, Data do, Kwota stawka);
    bool koliduje(Data od, Data do) const;
    int liczbaDob() const;
    Kwota obliczKoszt() const;
    void zamelduj();
    void wymelduj();
    void dodajUsluge(const Usluga_Dodatkowa& usluga, int ilosc);
    Faktura wystawFakture(std::string numer, Data data);
    Kwota anuluj(DataCzas teraz, int limitGodzin, Kwota oplata);
    
    // Gettery
    int pobierzId() const;
    int pobierzGoscId() const;
    int pobierzNumerPokoju() const;
    StatusRezerwacji pobierzStatus() const;
};