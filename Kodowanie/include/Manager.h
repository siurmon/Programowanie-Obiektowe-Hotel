#pragma once
#include "Pracownik.h"

class Manager : public Pracownik {
public:
    Manager(int id, std::string im, std::string naz, std::string nr);
    std::string rola() const override;
};