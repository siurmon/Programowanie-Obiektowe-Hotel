#pragma once
#include "Pracownik.h"

class Recepcjonista : public Pracownik {
public:
    Recepcjonista(int id, std::string im, std::string naz, std::string nr);
    std::string rola() const override;
};