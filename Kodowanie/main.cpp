#include <string>
#include <vector>
#include <memory>

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
using Data = std::string; 
using DataCzas = std::string;
using Kwota = double;

enum class StatusRezerwacji {
    
};

enum class StatusSprzatania {
    
};

enum class StatusKopii {
    
};