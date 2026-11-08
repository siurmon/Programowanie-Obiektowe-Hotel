#pragma once
#include <string>
#include "typy.h"
class UslugaDodatkowa {
private:
    int id_;
    std::string nazwa_;
    Kwota cena_jednostkowa_;
    std::string jednostka_;
public:
    UslugaDodatkowa(int id, const std::string& nazwa, Kwota cena_jednostkowa, const std::string& jednostka);
    int pobierzId() const;
    std::string pobierzNazwe() const;
    Kwota pobierzCene() const;
    std::string pobierzJednostke() const;
};