#pragma once
#include <string>
#include "common.h"

class Kopia_Zapasowa {
private:
    int id;
    DataCzas dataUtworzenia;
    std::string sciezkaPliku;
    StatusKopii status;
public:
    Kopia_Zapasowa(int id, DataCzas data, std::string sciezka);
    bool zapisz(Data dane); // Logika biznesowa
    bool zweryfikuj();      // Tez
    
    // Gettery
    int pobierzId() const;
    StatusKopii pobierzStatus() const;
    std::string pobierzSciezke() const;
};