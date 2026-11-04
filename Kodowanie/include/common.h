#pragma once
#include <string>

using Data = std::string;
using DataCzas = std::string;
using Kwota = double;

enum class StatusRezerwacji { POTWIERDZONA, ANULOWANA, ZAKONCZONA };
enum class StatusSprzatania { DO_SPRZATANIA, W_TRAKCIE, GOTOWY };
enum class StatusKopii { SUKCES, BLAD };