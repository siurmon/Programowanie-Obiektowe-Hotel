#include "statystyki.h"

#include "rezerwacja.h"

#include <algorithm>
#include <stdexcept>

using namespace std;

Statystyki::Statystyki()
    : okres_od_{1900, 1, 1}, okres_do_{1900, 1, 2},
      liczba_rezerwacji_(0), oblozenie_proc_(0.0),
      przychod_z_faktur_(0.0) {}

void Statystyki::oblicz(const vector<Rezerwacja>& rezerwacje,
                       int liczba_pokoi, const Data& od,
                       const Data& do_daty) {
    if (liczba_pokoi < 0) {
        throw invalid_argument("Liczba pokoi nie moze byc ujemna");
    }

    int dni_okresu = dniMiedzy(od, do_daty);
    okres_od_ = od;
    okres_do_ = do_daty;
    liczba_rezerwacji_ = 0;
    oblozenie_proc_ = 0.0;
    przychod_z_faktur_ = 0.0;
    int zajete_pokojodoby = 0;

    for (const auto& rezerwacja : rezerwacje) {
        if (rezerwacja.pobierzStatus() != StatusRezerwacji::Anulowana) {
            Data poczatek = max(od, rezerwacja.pobierzDataOd());
            Data koniec = min(do_daty, rezerwacja.pobierzDataDo());
            if (poczatek < koniec) {
                ++liczba_rezerwacji_;
                zajete_pokojodoby += dniMiedzy(poczatek, koniec);
            }
        }

        auto faktura = rezerwacja.pobierzFakture();
        if (faktura && !(faktura->pobierzDateWystawienia() < od) &&
            faktura->pobierzDateWystawienia() < do_daty) {
            przychod_z_faktur_ += faktura->suma();
        }
    }

    if (liczba_pokoi > 0) {
        oblozenie_proc_ =
            100.0 * zajete_pokojodoby / (liczba_pokoi * dni_okresu);
    }
}

double Statystyki::pobierzOblozenie() const { return oblozenie_proc_; }
Kwota Statystyki::pobierzPrzychod() const {
    return przychod_z_faktur_;
}
int Statystyki::pobierzLiczbeRezerwacji() const {
    return liczba_rezerwacji_;
}
