#include "Rezerwacja.h"
#include "Usluga_Dodatkowa.h"
#include <stdexcept>

using namespace std;

Rezerwacja::Rezerwacja(int id, int gosc_id, int numer_pokoju, const Data& od, const Data& do_daty, DataCzas utworzono, Kwota stawka_za_dobe)
    : id_(id), gosc_id_(gosc_id), numer_pokoju_(numer_pokoju), data_od_(od), data_do_(do_daty), utworzono_(utworzono),
        status_(StatusRezerwacji::Zarezerwowana), stawka_za_dobe_(stawka_za_dobe), oplata_anulowania_(0.0) {

    if (id <= 0 || gosc_id <= 0 || numer_pokoju <= 0 ||
        stawka_za_dobe < 0.0) {
        throw invalid_argument("Nieprawidlowe dane rezerwacji");
    }
    dniMiedzy(od, do_daty);
}

bool Rezerwacja::koliduje(const Data& od, const Data& do_daty) const {
    return status_ != StatusRezerwacji::Anulowana && (od < data_do_ && data_od_ < do_daty);
}

int Rezerwacja::liczbaDob() const {
    return dniMiedzy(data_od_, data_do_);
}

Kwota Rezerwacja::kosztUslug() const {
    Kwota suma = 0.0;
    for (const auto& usluga : zamowione_uslugi_) {
        suma += usluga.obliczKoszt();
    }
    return suma;
}

Kwota Rezerwacja::obliczKoszt() const {
    return liczbaDob() * stawka_za_dobe_ + kosztUslug();
}

void Rezerwacja::dodajUsluge(const UslugaDodatkowa& usluga, int ilosc) {
    if (status_ == StatusRezerwacji::Wymeldowana || status_ == StatusRezerwacji::Anulowana) { 
        throw logic_error("Nie mozna dodac uslugi do zakonczonej rezerwacji");
    }
    zamowione_uslugi_.emplace_back(usluga, ilosc);
}

void Rezerwacja::zamelduj() {
    if (status_ != StatusRezerwacji::Zarezerwowana) {
        throw logic_error("Mozna zameldowac tylko aktywna rezerwacje");
    }
    status_ = StatusRezerwacji::Zameldowana;
}

void Rezerwacja::wymelduj() {
    if (status_ != StatusRezerwacji::Zameldowana) {
        throw logic_error("Nie mozna wymeldowac niezameldowanego goscia");
    }
    status_ = StatusRezerwacji::Wymeldowana;
}

Faktura Rezerwacja::wystawFakture(const string& numer, const Data& data) {
    if (status_ != StatusRezerwacji::Wymeldowana) {
        throw logic_error("Faktura jest wystawiana po wymeldowaniu");
    }
    if (!faktura_) {
        faktura_.emplace(numer, id_, data,
                         liczbaDob() * stawka_za_dobe_, kosztUslug());
    }
    return *faktura_;
}

Kwota Rezerwacja::anuluj(DataCzas teraz, int limit_godzin, Kwota oplata) {
    if (status_ != StatusRezerwacji::Zarezerwowana) {
        throw logic_error("Anulowac mozna tylko niezameldowana rezerwacje");
    }
    if (limit_godzin < 0 || oplata < 0.0) {
        throw invalid_argument("Nieprawidlowa zasada anulowania");
    }

    double godzin_do_przyjazdu =
        difftime(dataNaCzas(data_od_), teraz) / 3600.0;

    if (godzin_do_przyjazdu < limit_godzin) {
        oplata_anulowania_ = oplata;
    } else {
        oplata_anulowania_ = 0.0;
    }

    status_ = StatusRezerwacji::Anulowana;

    return oplata_anulowania_;
}

int Rezerwacja::pobierzId() const { return id_; }
int Rezerwacja::pobierzGoscId() const { return gosc_id_; }
int Rezerwacja::pobierzNumerPokoju() const { return numer_pokoju_; }
StatusRezerwacji Rezerwacja::pobierzStatus() const { return status_; }
Data Rezerwacja::pobierzDataOd() const { return data_od_; }
Data Rezerwacja::pobierzDataDo() const { return data_do_; }
optional<Faktura> Rezerwacja::pobierzFakture() const { return faktura_; }
