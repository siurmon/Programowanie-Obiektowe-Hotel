#include "Kopia_Zapasowa.h"
#include <iostream>

using namespace std;

Kopia_Zapasowa::Kopia_Zapasowa(int id, DataCzas data_utworzenia, const string& sciezka_pliku) 
    : id(id), data_utworzenia_(data_utworzenia), sciezka_pliku_(sciezka_pliku), status_(StatusKopii::NieZapisana) {}

//ZMIENIC METODY ZAPISZ I ZWERYFIKUJ NA WERSJE Z PLIKAMI

bool Kopia_Zapasowa::zapisz(Data dane) {
    // Symulacja zapisu danych do pliku
    if (dane.empty() || sciezkaPliku.empty()) {
        status = StatusKopii::BLAD;
        return false;
    }
    // Tutaj w prawdziwym systemie byłby kod zapisu do pliku (np. ofstream)
    status = StatusKopii::SUKCES;
    cout << "Kopia zapasowa zapisana w: " << sciezkaPliku << endl;
    return true;
}

bool Kopia_Zapasowa::zweryfikuj() {
    // Sprawdzenie, czy zapis się udał i czy plik istnieje
    if (status == StatusKopii::SUKCES) {
        cout << "Weryfikacja kopii: SUKCES." << endl;
        return true;
    }
    cout << "Weryfikacja kopii: BLAD." << endl;
    return false;
}

int Kopia_Zapasowa::pobierzId() const { return id; }
StatusKopii Kopia_Zapasowa::pobierzStatus() const { return status; }
string Kopia_Zapasowa::pobierzSciezke() const { return sciezkaPliku; }