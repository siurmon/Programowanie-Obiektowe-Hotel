#include "Manager.h"

Manager::Manager(int id, std::string im, std::string naz, std::string nr) 
    : Pracownik(id, im, naz, nr) {}

std::string Manager::rola() const { return "Manager"; }