#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Pracownik.h"
#include "Gosc.h"
#include "Pokoj.h"
#include "Rezerwacja.h"
#include "Usluga_Dodatkowa.h"
#include "Kopia_Zapasowa.h"
#include "statystyki.h"

class SystemHotelu {
private:
    Rezerwacja& znajdzRezerwacje(int id);
    Pokoj& znajdzPokoj(int numer_pokoju);
    const Pokoj& znajdzPokoj(int numer_pokoju) const;

    std::vector<std::unique_ptr<Pracownik>> pracownicy_;
    std::vector<Gosc> goscie_;
    std::vector<Pokoj> pokoje_;
    std::vector<Rezerwacja> rezerwacje_;
    std::vector<UslugaDodatkowa> uslugi_;
    std::vector<KopiaZapasowa> kopie_;
    int limit_anulowania_godzin_;
    Kwota oplata_za_pozne_anulowanie_;
    int kolejne_id_rezerwacji_;
public:
    SystemHotelu(int limit_godzin = 24, Kwota oplata = 100.0);

    void dodajPracownika(std::unique_ptr<Pracownik> pracownik);
    void dodajGoscia(const Gosc& gosc);
    void dodajPokoj(const Pokoj& pokoj);
    void dodajUslugeDoOferty(const UslugaDodatkowa& usluga);

    std::vector<int> wyszukajDostepnePokoje(const Data& od,const Data& do_daty) const;
    int zarezerwujPokoj(int gosc_id, int numer_pokoju,const Data& od, const Data& do_daty);
    void dodajUsluge(int rezerwacja_id, int usluga_id, int ilosc);
    void zamelduj(int rezerwacja_id);
    Faktura wymelduj(int rezerwacja_id);
    StatusSprzatania sprawdzStatusPokoju(int numer_pokoju) const;
    void zmienStatusSprzatania(int numer_pokoju,StatusSprzatania status);
    Statystyki pobierzStatystyki(const Data& od,const Data& do_daty) const;
    StanSystemu sprawdzStanSystemu() const;
    KopiaZapasowa utworzKopieZapasowa(const std::string& sciezka);
    Kwota anulujRezerwacje(int rezerwacja_id, DataCzas teraz);
    Kwota anulujRezerwacje(int gosc_id, int rezerwacja_id,DataCzas teraz);
    bool zweryfikujKopie(int kopia_id) const;

};