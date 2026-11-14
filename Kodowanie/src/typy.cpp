#include "Typy.h"

#include <cmath>
#include <stdexcept>
#include <tuple>

using namespace std;

bool operator<(const Data& a, const Data& b) {
    return tie(a.rok, a.miesiac, a.dzien) <
           tie(b.rok, b.miesiac, b.dzien);
}

DataCzas dataNaCzas(const Data& data) {
    if (data.rok < 1900 || data.miesiac < 1 || data.miesiac > 12 ||
        data.dzien < 1 || data.dzien > 31) {
        throw invalid_argument("Niepoprawna data");
    }

    tm czas{};
    czas.tm_year = data.rok - 1900;
    czas.tm_mon = data.miesiac - 1;
    czas.tm_mday = data.dzien;
    czas.tm_hour = 12;  // Przyjeta godzina przyjazdu: 12:00.
    czas.tm_isdst = -1;

    DataCzas wynik = mktime(&czas);
    if (wynik == static_cast<DataCzas>(-1)) {
        throw invalid_argument("Nie mozna przeliczyc daty");
    }

    // mktime normalizuje nieistniejace daty, np. 31 lutego.
    if (czas.tm_year + 1900 != data.rok ||
        czas.tm_mon + 1 != data.miesiac ||
        czas.tm_mday != data.dzien) {
        throw invalid_argument("Niepoprawny dzien miesiaca");
    }
    return wynik;
}

int dniMiedzy(const Data& od, const Data& do_daty) {
    if (!(od < do_daty)) {
        throw invalid_argument("Data wyjazdu musi byc pozniejsza");
    }

    // Zaokraglenie uwzglednia zmiane czasu letniego/zimowego.
    double dni = difftime(dataNaCzas(do_daty), dataNaCzas(od)) / 86400.0;
    return static_cast<int>(lround(dni));
}

Data dzisiejszaData() {
    DataCzas teraz = time(nullptr);
    tm* lokalny_czas = localtime(&teraz);
    if (lokalny_czas == nullptr) {
        throw runtime_error("Nie mozna odczytac daty systemowej");
    }
    return {lokalny_czas->tm_year + 1900,
            lokalny_czas->tm_mon + 1,
            lokalny_czas->tm_mday};
}
