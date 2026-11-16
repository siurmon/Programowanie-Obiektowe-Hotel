#include "System_Hotelu.h"

#include <algorithm> // find()
#include <ctime>
#include <sstream>
#include <stdexcept>
#include <utility>

using namespace std;

SystemHotelu::SystemHotelu(int limit_godzin, Kwota oplata)
    : limit_anulowania_godzin_(limit_godzin), oplata_za_pozne_anulowanie_(oplata), kolejne_id_rezerwacji_(1) {
    if (limit_godzin < 0 || oplata < 0.0) {
        throw invalid_argument("Nieprawidlowa konfiguracja hotelu");
    }
}

void SystemHotelu::dodajPracownika(unique_ptr<Pracownik> pracownik) { //unique_ptr<Pracownik> to wskaźnik, który przechowuje własność obiektu Pracownik i automatycznie go usuwa, gdy zachodzi potrzeba
    if (!pracownik) {
        throw invalid_argument("Nie podano pracownika");
    }
    for (const auto& osoba : pracownicy_) {
        if (osoba->pobierzId() == pracownik->pobierzId()) { //ooba to referencja do unikalnego wskaźnika, dlatego -> zamiast .costam()
            throw logic_error("Pracownik o takim ID juz istnieje");
        }
    }
    pracownicy_.push_back(move(pracownik));
}

void SystemHotelu::dodajGoscia(const Gosc& gosc) {
    for (const auto& osoba : goscie_) {
        if (osoba.pobierzId() == gosc.pobierzId()) {
            throw logic_error("Gosc o takim ID juz istnieje");
        }
    }
    goscie_.push_back(gosc);
}

void SystemHotelu::dodajPokoj(const Pokoj& pokoj) {
    for (const auto& aktualny : pokoje_) {
        if (aktualny.pobierzNumerPokoju() == pokoj.pobierzNumerPokoju()) {
            throw logic_error("Pokoj o takim numerze juz istnieje");
        }
    }
    pokoje_.push_back(pokoj);
}

void SystemHotelu::dodajUslugeDoOferty(const UslugaDodatkowa& usluga) {
    for (const auto& aktualna : uslugi_) {
        if (aktualna.pobierzId() == usluga.pobierzId()) {
            throw logic_error("Usluga o takim ID juz istnieje");
        }
    }
    uslugi_.push_back(usluga);
}

Rezerwacja& SystemHotelu::znajdzRezerwacje(int id) {
    for (auto& rezerwacja : rezerwacje_) {
        if (rezerwacja.pobierzId() == id) {
            return rezerwacja;
        }
    }
    throw out_of_range("Nie znaleziono rezerwacji");
}

//Dwie funkcje do znajdowania pokoju, jedna zwraca const Pokoj&, a druga Pokoj&. 
//Dzięki temu można używać const w funkcjach, które nie modyfikują obiektu, a w funkcjach, które modyfikują obiekt, można używać zwykłego Pokoj&.
Pokoj& SystemHotelu::znajdzPokoj(int numer_pokoju) {
    for (auto& pokoj : pokoje_) {
        if (pokoj.pobierzNumerPokoju() == numer_pokoju) {
            return pokoj;
        }
    }
    throw out_of_range("Nie znaleziono pokoju");
}

const Pokoj& SystemHotelu::znajdzPokoj(int numer_pokoju) const {
    for (const auto& pokoj : pokoje_) {
        if (pokoj.pobierzNumerPokoju() == numer_pokoju) {
            return pokoj;
        }
    }
    throw out_of_range("Nie znaleziono pokoju");
}

vector<int> SystemHotelu::wyszukajDostepnePokoje(
    const Data& od, const Data& do_daty) const {
    dniMiedzy(od, do_daty);
    vector<int> dostepne;

    //podwójna pętla, która sprawdza każdy pokój i każdą rezerwację, aby znaleźć dostępne pokoje w podanym okresie.
    for (const auto& pokoj : pokoje_) {
        bool zajety = false;
        for (const auto& rezerwacja : rezerwacje_) {
            if (rezerwacja.pobierzNumerPokoju() == pokoj.pobierzNumerPokoju() && rezerwacja.koliduje(od, do_daty)) {
                zajety = true;
                break;
            }
        }
        if (!zajety) {
            dostepne.push_back(pokoj.pobierzNumerPokoju());
        }
    }
    return dostepne;
}

int SystemHotelu::zarezerwujPokoj(int gosc_id, int numer_pokoju, const Data& od, const Data& do_daty) {
    bool gosc_istnieje = false;

    for (const auto& gosc : goscie_) {
        if (gosc.pobierzId() == gosc_id) {
            gosc_istnieje = true;
            break;
        }
    }

    if (!gosc_istnieje) {
        throw out_of_range("Nie znaleziono goscia");
    }

    const Pokoj& pokoj = znajdzPokoj(numer_pokoju);
    auto wolne_pokoje = wyszukajDostepnePokoje(od, do_daty);
    if (find(wolne_pokoje.begin(), wolne_pokoje.end(), numer_pokoju) == wolne_pokoje.end()) { //find() znajduje element w wektorze
        throw logic_error("Pokoj jest zajety w tym terminie");
    }

    int id = kolejne_id_rezerwacji_;
    rezerwacje_.emplace_back(id, gosc_id, numer_pokoju,
                             od, do_daty, time(nullptr),
                             pokoj.pobierzStawke());
    ++kolejne_id_rezerwacji_;
    return id;
}

void SystemHotelu::dodajUsluge(int rezerwacja_id, int usluga_id, int ilosc) {
    for (const auto& usluga : uslugi_) {
        if (usluga.pobierzId() == usluga_id) {
            znajdzRezerwacje(rezerwacja_id).dodajUsluge(usluga, ilosc);
            return;
        }
    }
    throw out_of_range("Nie znaleziono uslugi");
}
//Zabezpieczenie, że gość nie może dodać usługi do rezerwacji, która nie należy do niego
void SystemHotelu::dodajUslugeGoscia(int gosc_id, int rezerwacja_id, int usluga_id, int ilosc) {
    if (znajdzRezerwacje(rezerwacja_id).pobierzGoscId() != gosc_id) {
        throw logic_error("Rezerwacja nie nalezy do tego goscia");
    }
    dodajUsluge(rezerwacja_id, usluga_id, ilosc);
}

void SystemHotelu::zamelduj(int rezerwacja_id) {
    znajdzRezerwacje(rezerwacja_id).zamelduj();
}

Faktura SystemHotelu::wymelduj(int rezerwacja_id) {
    Rezerwacja& rezerwacja = znajdzRezerwacje(rezerwacja_id);
    rezerwacja.wymelduj();
    
    znajdzPokoj(rezerwacja.pobierzNumerPokoju()).ustawStatusSprzatania(StatusSprzatania::DoSprzatania);
    
    return rezerwacja.wystawFakture("FV-" + to_string(rezerwacja_id), dzisiejszaData());
}

StatusSprzatania SystemHotelu::sprawdzStatusPokoju(
    int numer_pokoju) const {
    return znajdzPokoj(numer_pokoju).pobierzStatusSprzatania();
}

void SystemHotelu::zmienStatusSprzatania(
    int numer_pokoju, StatusSprzatania status) {
    znajdzPokoj(numer_pokoju).ustawStatusSprzatania(status);
}

Statystyki SystemHotelu::pobierzStatystyki(
    const Data& od, const Data& do_daty) const {
    Statystyki statystyki;
    statystyki.oblicz(rezerwacje_, static_cast<int>(pokoje_.size()), //static_cast<int> konwertuje size_t na int
                      od, do_daty);
    return statystyki;
}

StanSystemu SystemHotelu::sprawdzStanSystemu() const {
    if (pokoje_.empty()) {
        return StanSystemu::BrakPokoi;
    }
    if (pracownicy_.empty()) {
        return StanSystemu::BrakPracownikow;
    }
    return StanSystemu::Gotowy;
}

KopiaZapasowa SystemHotelu::utworzKopieZapasowa(
    const string& sciezka) {
    int id = static_cast<int>(kopie_.size()) + 1;
    KopiaZapasowa kopia(id, time(nullptr), sciezka);

    ostringstream dane;
    dane << "Liczba gosci: " << goscie_.size() << '\n';
    dane << "Liczba pokoi: " << pokoje_.size() << '\n';
    dane << "Liczba rezerwacji: " << rezerwacje_.size() << '\n';
    dane << "Liczba uslug: " << uslugi_.size() << '\n';

    if (!kopia.zapisz(dane.str())) {
        throw runtime_error("Nie mozna zapisac kopii");
    }
    kopie_.push_back(kopia);
    return kopia;
}

//Przeciążenie funkcji anulujRezerwacje, aby umożliwić anulowanie rezerwacji zarówno przez system, jak i przez gościa
Kwota SystemHotelu::anulujRezerwacje(int rezerwacja_id, DataCzas teraz) {
    return znajdzRezerwacje(rezerwacja_id).anuluj(
        teraz, limit_anulowania_godzin_, oplata_za_pozne_anulowanie_);
}

Kwota SystemHotelu::anulujRezerwacje(int gosc_id, int rezerwacja_id, DataCzas teraz) {
    if (znajdzRezerwacje(rezerwacja_id).pobierzGoscId() != gosc_id) {
        throw logic_error("Rezerwacja nie nalezy do tego goscia");
    }
    return anulujRezerwacje(rezerwacja_id, teraz);
}

bool SystemHotelu::zweryfikujKopie(int kopia_id) const {
    for (const auto& kopia : kopie_) {
        if (kopia.pobierzId() == kopia_id) {
            return kopia.zweryfikuj();
        }
    }
    return false;
}


const vector<Gosc>& SystemHotelu::pobierzGosci() const {
    return goscie_;
}

const vector<Pokoj>& SystemHotelu::pobierzPokoje() const {
    return pokoje_;
}

const vector<Rezerwacja>& SystemHotelu::pobierzRezerwacje() const {
    return rezerwacje_;
}

const vector<UslugaDodatkowa>& SystemHotelu::pobierzUslugi() const {
    return uslugi_;
}
