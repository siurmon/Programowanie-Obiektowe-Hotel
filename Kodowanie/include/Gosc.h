#pragma once
#include "Osoba.h"

class Gosc : public Osoba {
private:
    std::string email_;
    std::string telefon_;
public:
    Gosc(int id, const std::string& imie, const std::string& nazwisko, const std::string& email, const std::string& telefon);
    std::string rola() const override;
    std::string pobierzEmail() const;
    std::string pobierzTelefon() const;
};