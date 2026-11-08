#pragma once
#include <vector>
#include <optional>
#include "typy.h"
#include "Faktura.h"
#include "Zamowiona_Usluga.h"

class Rezerwacja {
private:
    int id_;
    int gosc_id_;
    int numer_pokoju_;
    Data data_od_;
    Data data_do_;
    DataCzas utworzono_;
    StatusRezerwacji status_;
    Kwota stawka_za_dobe_;
    std::optional<Faktura> faktura_;
    std::vector<ZamowionaUsluga> zamowione_uslugi_;
    Kwota oplata_anulowania_;
public:
    Rezerwacja(int id, int gosc_id, int numer_pokoju, const Data& od, const Data& do_daty, DataCzas utworzono, Kwota stawka_za_dobe);
    bool koliduje(const Data& od, const Data& do_daty) const;
    int liczbaDob() const;
    Kwota obliczKoszt() const;
    Kwota kosztUslug() const;
    void zamelduj();
    void wymelduj();
    void dodajUsluge(const UslugaDodatkowa& usluga, int ilosc);
    Faktura wystawFakture(const std::string& numer, const Data& data);
    Kwota anuluj(DataCzas teraz, int limit_godzin, Kwota oplata);
    
    // Gettery
    int pobierzId() const;
    int pobierzGoscId() const;
    int pobierzNumerPokoju() const;
    StatusRezerwacji pobierzStatus() const;
    Data pobierzDataOd() const;
    Data pobierzDataDo() const;
    std::optional<Faktura> pobierzFakture() const;
};

class UslugaDodatkowa;