#pragma once
#include "Pracownik.h"

class Administrator : public Pracownik {
public:
    Administrator(int id, std::string im, std::string naz, std::string nr);
    std::string rola() const override;
};