#include "Kopia_Zapasowa.h"
#include <iostream>

Kopia_Zapasowa::Kopia_Zapasowa(int id, DataCzas data, std::string sciezka) 
    : id(id), dataUtworzenia(data), sciezkaPliku(sciezka), status(StatusKopii::BLAD) {}

bool Kopia_Zapasowa::zapisz(Data dane) {
    // Symulacja zapisu danych do pliku
    if (dane.empty() || sciezkaPliku.empty()) {
        status = StatusKopii::BLAD;
        return false;
    }
    // Tutaj w prawdziwym systemie byłby kod zapisu do pliku (np. ofstream)
    status = StatusKopii::SUKCES;
    std::cout << "Kopia zapasowa zapisana w: " << sciezkaPliku << std::endl;
    return true;
}

bool Kopia_Zapasowa::zweryfikuj() {
    // Sprawdzenie, czy zapis się udał i czy plik istnieje
    if (status == StatusKopii::SUKCES) {
        std::cout << "Weryfikacja kopii: SUKCES." << std::endl;
        return true;
    }
    std::cout << "Weryfikacja kopii: BLAD." << std::endl;
    return false;
}

int Kopia_Zapasowa::pobierzId() const { return id; }
StatusKopii Kopia_Zapasowa::pobierzStatus() const { return status; }
std::string Kopia_Zapasowa::pobierzSciezke() const { return sciezkaPliku; }