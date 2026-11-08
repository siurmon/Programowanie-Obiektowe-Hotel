#pragma once
#include <string>
#include "typy.h"

class KopiaZapasowa {
private:
    int id_;
    DataCzas data_utworzenia_;
    std::string sciezka_pliku_;
    StatusKopii status_;
public:
    KopiaZapasowa(int id, DataCzas data_utworzenia, const std::string& sciezka_pliku);
    bool zapisz(const std::string& dane);
    bool zweryfikuj() const;
    
    // Gettery
    int pobierzId() const;
    StatusKopii pobierzStatus() const;
    std::string pobierzSciezke() const;
    DataCzas pobierzDateUtworzenia() const;
};