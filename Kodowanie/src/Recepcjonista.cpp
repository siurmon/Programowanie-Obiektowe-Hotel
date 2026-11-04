#include "Recepcjonista.h"

Recepcjonista::Recepcjonista(int id, std::string im, std::string naz, std::string nr) 
    : Pracownik(id, im, naz, nr) {}

std::string Recepcjonista::rola() const { return "Recepcjonista"; }