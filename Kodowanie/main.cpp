#include <iostream>
#include "klasy.h"

using namespace std;

// --- DEKLARACJE KLAS ---
class Pracownik;
class Gosc;
class Pokoj;
class Rezerwacja;
class Usluga_Dodatkowa;
class Kopia_Zapasowa;
class Zamowiona_Usluga;
class Faktura;

// --- STRUKTURY POMOCNICZE ---
using Data = string; 
using DataCzas = string;
using Kwota = double;

enum class StatusRezerwacji {
    
};

enum class StatusSprzatania {
    
};

enum class StatusKopii {
    
};