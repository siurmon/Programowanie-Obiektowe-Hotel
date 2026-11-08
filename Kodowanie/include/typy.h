#pragma once
#include <string>
#include <ctime>

using DataCzas = std::time_t;
using Kwota = double;

struct Data {
    int rok;
    int miesiac;
    int dzien;
};

enum class StatusRezerwacji { Zarezerwowana, Zameldowana, Wymeldowana, Anulowana };
enum class StatusSprzatania { Czysty, DoSprzatania, WTrakcie };
enum class StatusKopii { NieZapisana, Zapisana, Blad };
enum class StanSystemu { Gotowy, BrakPokoi, BrakPracownikow };

bool operator<(const Data& a, const Data& b);
DataCzas dataNaCzas(const Data& data);
int dniMiedzy(const Data& od, const Data& do_daty);
Data dzisiejszaData();
