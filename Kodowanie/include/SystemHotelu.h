#pragma once
#include <vector>
#include "Pracownik.h"
#include "Gosc.h"
#include "Pokoj.h"
#include "Rezerwacja.h"
#include "Usluga_Dodatkowa.h"
#include "Kopia_Zapasowa.h"

class SystemHotelu {
private:
    std::vector<Pracownik*> pracownicy;
    std::vector<Gosc> goscie;
    std::vector<Pokoj> pokoje;
    std::vector<Rezerwacja> rezerwacje;
    std::vector<Usluga_Dodatkowa> uslugi;
    std::vector<Kopia_Zapasowa> kopie;
public:
    ~SystemHotelu();
    void dodajPokoj(const Pokoj& p);
    void dodajUslugeBazowa(const Usluga_Dodatkowa& u);
    
    std::vector<int> wyszukajDostepnePokoje(Data od, Data do) const;
    int zarezerwujPokoj(int goscId, int numer_pokoju, Data od, Data do);
    void dodajUsluge(int rezerwacjaId, int uslugId, int ilosc);
    void zamelduj(int rezerwacjaId);
    Faktura wymelduj(int rezerwacjaId);
    StatusSprzatania sprawdzStatusPokoju(int numer_pokoju) const;
    void zmienStatusSprzatania(int numer_pokoju, StatusSprzatania status);
    Kwota anulujRezerwacje(int goscId, int rezerwacjaId, DataCzas teraz);
};