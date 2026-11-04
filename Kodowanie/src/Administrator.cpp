#include "Administrator.h"

Administrator::Administrator(int id, std::string im, std::string naz, std::string nr) 
    : Pracownik(id, im, naz, nr) {}

std::string Administrator::rola() const { return "Administrator"; }