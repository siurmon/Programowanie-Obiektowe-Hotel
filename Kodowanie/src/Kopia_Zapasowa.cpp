#include "Kopia_Zapasowa.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

KopiaZapasowa::KopiaZapasowa(int id, DataCzas data_utworzenia, const string& sciezka_pliku) 
    : id(id), data_utworzenia_(data_utworzenia), sciezka_pliku_(sciezka_pliku), status_(StatusKopii::NieZapisana) {}


bool KopiaZapasowa::zapisz(const string& dane) {
    ofstream plik(sciezka_pliku_);
    if (!plik) {
        status_ = StatusKopii::Blad;
        return false;
    }

    plik << dane;
    plik.close();
    status_ = plik ? StatusKopii::Zapisana : StatusKopii::Blad;
    return status_ == StatusKopii::Zapisana;
}

bool KopiaZapasowa::zweryfikuj() const {
    ifstream plik(sciezka_pliku_);
    return status_ == StatusKopii::Zapisana && plik.good();
}

int KopiaZapasowa::pobierzId() const { return id; }
StatusKopii KopiaZapasowa::pobierzStatus() const { return status; }
string KopiaZapasowa::pobierzSciezke() const { return sciezkaPliku; }
DataCzas KopiaZapasowa::pobierzDateUtworzenia() const { return data_utworzenia_;}