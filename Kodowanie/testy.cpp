
#include "System_Hotelu.h"
#include "Recepcjonista.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

static int zaliczone = 0;
static int bledy = 0;

void naglowek(const string& tekst) {
    cout << "\n" << string(66, '=') << "\n";
    cout << "  " << tekst << "\n";
    cout << string(66, '=') << "\n";
}

void etap(int numer, const string& tekst) {
    cout << "\n  " << numer << ". " << tekst << "\n";
    cout << "  " << string(62, '-') << "\n";
}

void sprawdz(bool warunek, const string& opis) {
    if (warunek) {
        ++zaliczone;
    } else {
        ++bledy;
    }
    cout << "  [" << (warunek ? "OK  " : "BLAD") << "] " << opis << "\n";
}

// W tym makrze oczekujemy WYJATKU. Jego wystapienie oznacza sukces testu.
#define OCZEKUJ_BLEDU(operacja, opis)                        \
    do {                                                     \
        bool wykryto = false;                                \
        try { operacja; }                                    \
        catch (const exception&) { wykryto = true; }         \
        sprawdz(wykryto, opis);                              \
    } while (false)

bool rowne(double a, double b) {
    return fabs(a - b) < 0.001;
}

bool zawiera(const vector<int>& lista, int numer) {
    return find(lista.begin(), lista.end(), numer) != lista.end();
}

// Daty wzgledem dzisiaj: test nie przestanie dzialac po 2030 roku.
Data zaDni(int ile) {
    time_t teraz = time(nullptr);
    tm* odczyt = localtime(&teraz);
    if (!odczyt) throw runtime_error("Nie mozna pobrac daty systemowej");
    tm data = *odczyt;
    data.tm_hour = 12;
    data.tm_min = 0;
    data.tm_sec = 0;
    data.tm_mday += ile;
    data.tm_isdst = -1;
    if (mktime(&data) == static_cast<time_t>(-1)) {
        throw runtime_error("Nie mozna wyliczyc daty testowej");
    }
    return {data.tm_year + 1900, data.tm_mon + 1, data.tm_mday};
}

void pokazDate(const Data& d) {
    cout << setfill('0') << setw(2) << d.dzien << "."
         << setw(2) << d.miesiac << "." << setw(4) << d.rok
         << setfill(' ');
}

void przygotuj(SystemHotelu& hotel) {
    hotel.dodajGoscia(Gosc(1, "Jan", "Kowalski", "jan@test.pl", "123456789"));
    hotel.dodajGoscia(Gosc(2, "Anna", "Nowak", "anna@test.pl", "987654321"));
    hotel.dodajPokoj(Pokoj(101, 2, 200.0));
    hotel.dodajPokoj(Pokoj(102, 3, 150.0));
    hotel.dodajUslugeDoOferty(UslugaDodatkowa(1, "Sniadanie", 30.0, "szt"));
    hotel.dodajUslugeDoOferty(UslugaDodatkowa(2, "Parking", 20.0, "doba"));
}

string wolnePokoje(const vector<int>& pokoje) {
    if (pokoje.empty()) return "brak";
    string wynik;
    for (int numer : pokoje) {
        if (!wynik.empty()) wynik += ", ";
        wynik += to_string(numer);
    }
    return wynik;
}

// Nie nadpisujemy istniejacych plikow uzytkownika.
string sciezkaRaportu() {
    for (int n = 1; n <= 1000; ++n) {
        string nazwa = "_hotel_test_" + to_string(time(nullptr))
                     + "_" + to_string(n) + ".txt";
        ifstream plik(nazwa);
        if (!plik.good()) return nazwa;
    }
    throw runtime_error("Nie mozna znalezc wolnej nazwy raportu");
}

// =============================================================
// SZYBKI POKAZ: jeden scenariusz, wszystkie najwazniejsze funkcje
// =============================================================
void szybkiPokaz() {
    naglowek("SZYBKI POKAZ - SYSTEM HOTELU");


    SystemHotelu hotel;
    const Data od = zaDni(10), do_daty = zaDni(13);

    etap(1, "PRZYGOTOWANIE HOTELU");
    przygotuj(hotel);
    hotel.dodajPracownika(make_unique<Recepcjonista>(10, "Ewa", "Lis", "R10"));
    cout << "  POKOJE:       101 (200.00 zl/doba), 102 (150.00 zl/doba)\n";
    cout << "  GOSCIE:       Jan (ID 1), Anna (ID 2)\n";
    cout << "  USLUGI:       Sniadanie 30.00 zl, parking 20.00 zl\n";
    cout << "  PRACOWNIK:    Ewa Lis, recepcjonista\n";
    sprawdz(hotel.sprawdzStanSystemu() == StanSystemu::Gotowy,
            "System jest gotowy do pracy");

    etap(2, "REZERWACJA I DOSTEPNOSC");
    const int id = hotel.zarezerwujPokoj(1, 101, od, do_daty);
    cout << "  REZERWACJA:   nr " << id << ", Jan, pokoj 101, termin ";
    pokazDate(od); cout << " - "; pokazDate(do_daty); cout << " (3 doby)\n";
    auto wolne = hotel.wyszukajDostepnePokoje(od, do_daty);
    cout << "  WOLNE POKOJE: " << wolnePokoje(wolne) << "\n";
    sprawdz(id == 1 && hotel.pobierzRezerwacje().size() == 1,
            "Rezerwacja zostala zapisana z ID 1");
    sprawdz(!zawiera(wolne, 101) && zawiera(wolne, 102),
            "Zajety 101 jest ukryty, pokoj 102 pozostaje wolny");

    etap(3, "KOLIZJA I TERMIN GRANICZNY");
    OCZEKUJ_BLEDU(hotel.zarezerwujPokoj(2, 101, zaDni(12), zaDni(15)),
                 "Odrzucono nakladajacy sie termin");
    const int id2 = hotel.zarezerwujPokoj(2, 101, do_daty, zaDni(15));
    cout << "  DRUGA REZERWACJA: Anna, pokoj 101 od dnia wyjazdu Jana\n";
    sprawdz(id2 == 2, "Dozwolono przyjazd kolejnego goscia w dniu wyjazdu");

    etap(4, "USLUGI I DOKLADNE KOSZTY");
    hotel.dodajUslugeGoscia(1, id, 1, 2);  // 2 x 30 = 60 zl
    hotel.dodajUsluge(id, 2, 1);          // 1 x 20 = 20 zl
    cout << "  NOCLEG:     3 x 200.00     = 600.00 zl\n";
    cout << "  SNIADANIA:  2 x  30.00     =  60.00 zl\n";
    cout << "  PARKING:    1 x  20.00     =  20.00 zl\n";
    cout << "  RAZEM:                     = "
         << hotel.pobierzRezerwacje()[0].obliczKoszt() << " zl\n";
    sprawdz(rowne(hotel.pobierzRezerwacje()[0].kosztUslug(), 80),
            "Koszt uslug wynosi dokladnie 80.00 zl");
    sprawdz(rowne(hotel.pobierzRezerwacje()[0].obliczKoszt(), 680),
            "Cena calkowita wynosi dokladnie 680.00 zl");
    OCZEKUJ_BLEDU(hotel.dodajUslugeGoscia(2, id, 1, 1),
                 "Obcy gosc nie moze dodac uslugi do rezerwacji Jana");

    etap(5, "ZAMELDOWANIE, FAKTURA I SPRZATANIE");
    hotel.zamelduj(id);
    sprawdz(hotel.pobierzRezerwacje()[0].pobierzStatus() == StatusRezerwacji::Zameldowana,
            "Gosc zostal zameldowany");
    Faktura faktura = hotel.wymelduj(id);
    cout << "  FAKTURA:    " << faktura.pobierzNumer()
         << "     DO ZAPLATY: " << faktura.suma() << " zl\n";
    sprawdz(faktura.pobierzNumer() == "FV-1" && rowne(faktura.suma(), 680),
            "Wystawiono prawidlowa fakture na 680.00 zl");
    sprawdz(hotel.pobierzRezerwacje()[0].pobierzStatus() == StatusRezerwacji::Wymeldowana,
            "Status rezerwacji: Wymeldowana");
    sprawdz(hotel.sprawdzStatusPokoju(101) == StatusSprzatania::DoSprzatania,
            "Po wyjezdzie pokoj wymaga sprzatania");
    hotel.zmienStatusSprzatania(101, StatusSprzatania::Czysty);
    sprawdz(hotel.sprawdzStatusPokoju(101) == StatusSprzatania::Czysty,
            "Personel oznaczyl pokoj jako czysty");

    etap(6, "ANULOWANIE - W TERMINIE I ZA POZNO");
    const Data a = zaDni(16), b = zaDni(18);
    int id3 = hotel.zarezerwujPokoj(2, 102, a, b);
    Kwota bezOplaty = hotel.anulujRezerwacje(2, id3, dataNaCzas(a) - 48 * 3600);
    const Data c = zaDni(20), d = zaDni(22);
    int id4 = hotel.zarezerwujPokoj(2, 102, c, d);
    Kwota poTerminie = hotel.anulujRezerwacje(2, id4, dataNaCzas(c) - 12 * 3600);
    cout << "  48 godzin przed przyjazdem: " << bezOplaty << " zl\n";
    cout << "  12 godzin przed przyjazdem: " << poTerminie << " zl\n";
    sprawdz(rowne(bezOplaty, 0), "Bezplatne anulowanie - 0.00 zl");
    sprawdz(rowne(poTerminie, 100), "Pozne anulowanie - 100.00 zl");
    sprawdz(zawiera(hotel.wyszukajDostepnePokoje(a, b), 102),
            "Anulowana rezerwacja zwolnila pokoj 102");

    etap(7, "STATYSTYKI I RAPORT");
    const Data raportOd = zaDni(-1), raportDo = zaDni(25);
    Statystyki stat = hotel.pobierzStatystyki(raportOd, raportDo);
    const double oczekiwaneOblozenie = 100.0 * 5 / (2 * dniMiedzy(raportOd, raportDo));
    cout << "  REZERWACJE:  " << stat.pobierzLiczbeRezerwacji() << " (bez anulowanych)\n";
    cout << "  OBLOZENIE:   " << stat.pobierzOblozenie() << " %\n";
    cout << "  PRZYCHOD:    " << stat.pobierzPrzychod() << " zl\n";
    sprawdz(stat.pobierzLiczbeRezerwacji() == 2,
            "Statystyki obejmuja dwie nieanulowane rezerwacje");
    sprawdz(rowne(stat.pobierzOblozenie(), oczekiwaneOblozenie),
            "Oblozenie wyliczono poprawnie z pieciu pokojodob");
    sprawdz(rowne(stat.pobierzPrzychod(), 680),
            "Przychod obejmuje fakture na 680.00 zl");

    const string sciezka = sciezkaRaportu();
    KopiaZapasowa kopia = hotel.utworzKopieZapasowa(sciezka);
    sprawdz(hotel.zweryfikujKopie(kopia.pobierzId()),
            "Zapisano plik raportu i mozna go odczytac");
    std::remove(sciezka.c_str());
    cout << "  Raport zawiera liczniki obiektow (to NIE jest pelny backup).\n";
}

// =============================================================
// DOKLADNIEJSZE TESTY: oddzielne, niezalezne scenariusze
// =============================================================
void testDane() {
    SystemHotelu hotel;
    przygotuj(hotel);
    sprawdz(hotel.pobierzGosci().size() == 2, "Dodano dokladnie dwoch gosci");
    sprawdz(hotel.pobierzPokoje().size() == 2, "Dodano dokladnie dwa pokoje");
    sprawdz(hotel.pobierzUslugi().size() == 2, "Dodano dwie uslugi do oferty");
    OCZEKUJ_BLEDU(hotel.dodajGoscia(Gosc(1, "Nowy", "Gosc", "a@b.pl", "111111111")),
                 "Zablokowano zduplikowane ID goscia");
    OCZEKUJ_BLEDU(hotel.dodajPokoj(Pokoj(101, 3, 90)),
                 "Zablokowano zduplikowany numer pokoju");
    OCZEKUJ_BLEDU(hotel.dodajUslugeDoOferty(UslugaDodatkowa(1, "Inna", 5, "szt")),
                 "Zablokowano zduplikowane ID uslugi");
}

void testRezerwacja() {
    SystemHotelu hotel;
    przygotuj(hotel);
    Data a = zaDni(10), b = zaDni(13);
    sprawdz(hotel.wyszukajDostepnePokoje(a, b).size() == 2,
            "Przed rezerwacja oba pokoje sa wolne");
    int id = hotel.zarezerwujPokoj(1, 101, a, b);
    sprawdz(id == 1, "Pierwsza rezerwacja ma ID 1");
    sprawdz(hotel.pobierzRezerwacje().size() == 1 &&
            hotel.pobierzRezerwacje()[0].pobierzGoscId() == 1,
            "Zapisano rezerwacje na wlasciwego goscia");
    auto wolne = hotel.wyszukajDostepnePokoje(a, b);
    sprawdz(wolne.size() == 1 && zawiera(wolne, 102),
            "Po rezerwacji wolny pozostaje tylko pokoj 102");
}

void testKolizje() {
    SystemHotelu hotel;
    przygotuj(hotel);
    int id1 = hotel.zarezerwujPokoj(1, 101, zaDni(10), zaDni(13));
    OCZEKUJ_BLEDU(hotel.zarezerwujPokoj(2, 101, zaDni(12), zaDni(15)),
                 "Blokada nakladajacych sie terminow");
    int id2 = hotel.zarezerwujPokoj(2, 101, zaDni(13), zaDni(15));
    sprawdz(id1 == 1 && id2 == 2,
            "Nowy pobyt moze zaczac sie w dniu poprzedniego wyjazdu");
    int id3 = hotel.zarezerwujPokoj(2, 102, zaDni(10), zaDni(13));
    sprawdz(id3 == 3, "Inny pokoj moze miec rezerwacje w tym samym czasie");
}

void testUslugi() {
    SystemHotelu hotel;
    przygotuj(hotel);
    int id = hotel.zarezerwujPokoj(1, 101, zaDni(10), zaDni(13));
    hotel.dodajUslugeGoscia(1, id, 1, 2);
    hotel.dodajUsluge(id, 2, 1);
    sprawdz(rowne(hotel.pobierzRezerwacje()[0].kosztUslug(), 80),
            "Suma uslug = 2 x 30 + 1 x 20 = 80.00 zl");
    sprawdz(rowne(hotel.pobierzRezerwacje()[0].obliczKoszt(), 680),
            "Cala rezerwacja = 3 x 200 + 80 = 680.00 zl");
    OCZEKUJ_BLEDU(hotel.dodajUslugeGoscia(2, id, 1, 1),
                 "Obcy gosc nie moze dodac uslugi");
    OCZEKUJ_BLEDU(hotel.dodajUsluge(id, 99, 1),
                 "Nieznana usluga powoduje blad");
    OCZEKUJ_BLEDU(hotel.dodajUsluge(id, 1, 0),
                 "Nie mozna zamowic zera sztuk");
    sprawdz(rowne(hotel.pobierzRezerwacje()[0].obliczKoszt(), 680),
            "Nieudane operacje nie zmienily kosztu");
}

void testMeldowanie() {
    SystemHotelu hotel;
    przygotuj(hotel);
    int id = hotel.zarezerwujPokoj(1, 101, zaDni(10), zaDni(13));
    OCZEKUJ_BLEDU(hotel.wymelduj(id),
                 "Nie mozna wymeldowac przed zameldowaniem");
    hotel.dodajUsluge(id, 1, 2);
    hotel.zamelduj(id);
    sprawdz(hotel.pobierzRezerwacje()[0].pobierzStatus() == StatusRezerwacji::Zameldowana,
            "Zameldowanie ustawia prawidlowy status");
    OCZEKUJ_BLEDU(hotel.zamelduj(id), "Powtorne zameldowanie jest blokowane");
    Faktura f = hotel.wymelduj(id);
    sprawdz(f.pobierzNumer() == "FV-1" && rowne(f.suma(), 660),
            "Faktura: FV-1 i dokladna kwota 660.00 zl");
    sprawdz(hotel.pobierzRezerwacje()[0].pobierzStatus() == StatusRezerwacji::Wymeldowana,
            "Wymeldowanie ustawia prawidlowy status");
    sprawdz(hotel.sprawdzStatusPokoju(101) == StatusSprzatania::DoSprzatania,
            "Po wymeldowaniu pokoj wymaga sprzatania");
    auto faktura = hotel.pobierzRezerwacje()[0].pobierzFakture();
    sprawdz(faktura.has_value() && rowne(faktura->suma(), 660),
            "Faktura zostaje zapisana w rezerwacji");
    OCZEKUJ_BLEDU(hotel.wymelduj(id), "Powtorne wymeldowanie jest blokowane");
    OCZEKUJ_BLEDU(hotel.dodajUsluge(id, 1, 1),
                 "Po wymeldowaniu nie mozna dodac uslugi");
}

void testAnulowanie() {
    SystemHotelu hotel;
    przygotuj(hotel);
    Data a = zaDni(10), b = zaDni(13);
    int id1 = hotel.zarezerwujPokoj(1, 101, a, b);
    int id2 = hotel.zarezerwujPokoj(2, 102, a, b);
    time_t start = dataNaCzas(a);
    OCZEKUJ_BLEDU(hotel.anulujRezerwacje(1, id2, start - 12 * 3600),
                 "Obcy gosc nie moze anulowac cudzej rezerwacji");
    Kwota wczesnie = hotel.anulujRezerwacje(1, id1, start - 48 * 3600);
    Kwota pozno = hotel.anulujRezerwacje(2, id2, start - 12 * 3600);
    sprawdz(rowne(wczesnie, 0), "48 h przed przyjazdem: oplata 0.00 zl");
    sprawdz(rowne(pozno, 100), "12 h przed przyjazdem: oplata 100.00 zl");
    OCZEKUJ_BLEDU(hotel.anulujRezerwacje(1, id1, start - 48 * 3600),
                 "Nie mozna anulowac drugi raz");
    sprawdz(hotel.wyszukajDostepnePokoje(a, b).size() == 2,
            "Obie anulowane rezerwacje zwolnily pokoje");
    int id3 = hotel.zarezerwujPokoj(1, 101, a, b);
    Kwota rowno = hotel.anulujRezerwacje(id3, start - 24 * 3600);
    sprawdz(rowne(rowno, 0), "Dokladnie 24 h przed przyjazdem: bez oplaty");
}

void testStatystyki() {
    SystemHotelu hotel;
    przygotuj(hotel);
    int id = hotel.zarezerwujPokoj(1, 101, zaDni(10), zaDni(13));
    hotel.dodajUsluge(id, 1, 2);
    hotel.zamelduj(id);
    hotel.wymelduj(id); // Faktura jest wystawiana z DZISIEJSZA data.
    int anulowana = hotel.zarezerwujPokoj(2, 102, zaDni(10), zaDni(13));
    hotel.anulujRezerwacje(anulowana, dataNaCzas(zaDni(10)) - 48 * 3600);
    Data a = zaDni(-1), b = zaDni(20); // Zawiera dzisiejsza fakture i pobyt.
    Statystyki s = hotel.pobierzStatystyki(a, b);
    double oczekiwane = 100.0 * 3 / (2 * dniMiedzy(a, b));
    sprawdz(s.pobierzLiczbeRezerwacji() == 1,
            "Statystyki pomijaja anulowane rezerwacje");
    sprawdz(rowne(s.pobierzOblozenie(), oczekiwane),
            "Oblozenie ma dokladna, oczekiwana wartosc");
    sprawdz(rowne(s.pobierzPrzychod(), 660),
            "Przychod z faktury wynosi dokladnie 660.00 zl");
}

void testSprzatanie() {
    SystemHotelu hotel;
    przygotuj(hotel);
    sprawdz(hotel.sprawdzStatusPokoju(101) == StatusSprzatania::Czysty,
            "Poczatkowo pokoj jest czysty");
    hotel.zmienStatusSprzatania(101, StatusSprzatania::DoSprzatania);
    sprawdz(hotel.sprawdzStatusPokoju(101) == StatusSprzatania::DoSprzatania,
            "Zgloszono pokoj do sprzatania");
    hotel.zmienStatusSprzatania(101, StatusSprzatania::WTrakcie);
    sprawdz(hotel.sprawdzStatusPokoju(101) == StatusSprzatania::WTrakcie,
            "Sprzatanie jest w trakcie");
    hotel.zmienStatusSprzatania(101, StatusSprzatania::Czysty);
    sprawdz(hotel.sprawdzStatusPokoju(101) == StatusSprzatania::Czysty,
            "Sprzatanie zakonczone");
    OCZEKUJ_BLEDU(hotel.sprawdzStatusPokoju(999),
                 "Nie mozna odczytac nieistniejacego pokoju");
}

void testStan() {
    SystemHotelu pusty;
    sprawdz(pusty.sprawdzStanSystemu() == StanSystemu::BrakPokoi,
            "Pusty hotel: BrakPokoi");
    SystemHotelu hotel;
    przygotuj(hotel);
    sprawdz(hotel.sprawdzStanSystemu() == StanSystemu::BrakPracownikow,
            "Hotel bez personelu: BrakPracownikow");
    hotel.dodajPracownika(make_unique<Recepcjonista>(10, "Ewa", "Lis", "R10"));
    sprawdz(hotel.sprawdzStanSystemu() == StanSystemu::Gotowy,
            "Po dodaniu pracownika: Gotowy");
    OCZEKUJ_BLEDU(hotel.dodajPracownika(make_unique<Recepcjonista>(10, "Inna", "Osoba", "R11")),
                 "Nie mozna dodac pracownika z powtorzonym ID");
}

void testKopia() {
    SystemHotelu hotel;
    przygotuj(hotel);
    const string sciezka = sciezkaRaportu();
    KopiaZapasowa kopia = hotel.utworzKopieZapasowa(sciezka);
    sprawdz(kopia.pobierzStatus() == StatusKopii::Zapisana,
            "Operacja zapisu ma status Zapisana");
    sprawdz(hotel.zweryfikujKopie(kopia.pobierzId()),
            "Zapisany plik jest dostepny");
    ifstream plik(sciezka);
    string tekst((istreambuf_iterator<char>(plik)), istreambuf_iterator<char>());
    sprawdz(tekst.find("Liczba gosci: 2") != string::npos &&
            tekst.find("Liczba pokoi: 2") != string::npos &&
            tekst.find("Liczba uslug: 2") != string::npos,
            "Raport zawiera prawidlowe liczniki obiektow");
    plik.close();
    int usunieto = std::remove(sciezka.c_str());
    sprawdz(usunieto == 0, "Usunieto tymczasowy plik testowy");
    sprawdz(!hotel.zweryfikujKopie(kopia.pobierzId()),
            "Po usunieciu plik nie przechodzi weryfikacji");
}

void testWalidacja() {
    OCZEKUJ_BLEDU(SystemHotelu(-1, 100),
                 "Ujemny limit anulowania jest odrzucany");
    OCZEKUJ_BLEDU(SystemHotelu(24, -20),
                 "Ujemna oplata anulowania jest odrzucana");
    OCZEKUJ_BLEDU(UslugaDodatkowa(-1, "Usluga", 10, "szt"),
                 "Ujemne ID uslugi jest odrzucane");
    SystemHotelu hotel;
    przygotuj(hotel);
    OCZEKUJ_BLEDU(hotel.zarezerwujPokoj(99, 101, zaDni(10), zaDni(13)),
                 "Nieznany gosc jest odrzucany");
    OCZEKUJ_BLEDU(hotel.zarezerwujPokoj(1, 999, zaDni(10), zaDni(13)),
                 "Nieznany pokoj jest odrzucany");
    OCZEKUJ_BLEDU(hotel.zarezerwujPokoj(1, 101, zaDni(13), zaDni(10)),
                 "Data wyjazdu przed przyjazdem jest odrzucana");
    OCZEKUJ_BLEDU(hotel.wyszukajDostepnePokoje(Data{2031, 2, 30}, Data{2031, 3, 2}),
                 "Nieistniejaca data kalendarzowa jest odrzucana");
}

void testFaktura() {
    SystemHotelu hotel;
    przygotuj(hotel);
    int id = hotel.zarezerwujPokoj(1, 101, zaDni(10), zaDni(13));
    hotel.zamelduj(id);
    Faktura pierwsza = hotel.wymelduj(id);
    auto zapisana = hotel.pobierzRezerwacje()[0].pobierzFakture();
    sprawdz(zapisana.has_value(), "Po wymeldowaniu istnieje faktura");
    sprawdz(pierwsza.pobierzNumer() == "FV-1" && rowne(pierwsza.suma(), 600),
            "Faktura bez uslug opiewa na 600.00 zl");
    // Przez getter otrzymujemy const Rezerwacja&, wiec sprawdzamy zachowany obiekt.
    sprawdz(zapisana.has_value() && zapisana->pobierzNumer() == pierwsza.pobierzNumer(),
            "Faktura zostaje przypisana do odpowiedniej rezerwacji");
}

void wykonajTest(int nr) {
    static const char* nazwy[] = {
        "", "Dodawanie danych i duplikaty", "Tworzenie rezerwacji i dostepnosc",
        "Kolizje i terminy graniczne", "Uslugi i dokladne koszty",
        "Zameldowanie, wymeldowanie i faktura", "Anulowanie - 48 h / 24 h / 12 h",
        "Statystyki - dokladne wyniki", "Statusy sprzatania",
        "Gotowosc systemu i pracownicy", "Raport plikowy",
        "Walidacja niepoprawnych danych", "Zachowanie faktury"
    };
    if (nr < 1 || nr > 12) {
        cout << "Nie ma takiego testu.\n";
        return;
    }
    etap(nr, nazwy[nr]);
    try {
        switch (nr) {
            case 1: testDane(); break;
            case 2: testRezerwacja(); break;
            case 3: testKolizje(); break;
            case 4: testUslugi(); break;
            case 5: testMeldowanie(); break;
            case 6: testAnulowanie(); break;
            case 7: testStatystyki(); break;
            case 8: testSprzatanie(); break;
            case 9: testStan(); break;
            case 10: testKopia(); break;
            case 11: testWalidacja(); break;
            case 12: testFaktura(); break;
        }
    } catch (const exception& e) {
        sprawdz(false, string("Nieoczekiwany wyjatek: ") + e.what());
    } catch (...) {
        sprawdz(false, "Nieznany nieoczekiwany wyjatek");
    }
}

void podsumowanie() {
    cout << "\n" << string(66, '=') << "\n";
    cout << "  WYNIK: " << zaliczone << " / " << (zaliczone + bledy)
         << " sprawdzen zaliczonych";
    if (bledy == 0) cout << "   [SUKCES]";
    else cout << "   [BLEDY: " << bledy << "]";
    cout << "\n" << string(66, '=') << "\n";
}

void resetuj() {
    zaliczone = 0;
    bledy = 0;
}

int pokazDemo() {
    resetuj();
    try {
        szybkiPokaz();
    } catch (const exception& e) {
        sprawdz(false, string("Demonstracja przerwana: ") + e.what());
    }
    podsumowanie();
    return bledy == 0 ? 0 : 1;
}

int wszystkieTesty() {
    resetuj();
    naglowek("PELNY ZESTAW TESTOW - 12 SCENARIUSZY");
    for (int i = 1; i <= 12; ++i) wykonajTest(i);
    podsumowanie();
    return bledy == 0 ? 0 : 1;
}

int menu() {
    while (true) {
        naglowek("MENU TESTOW - SYSTEM HOTELU");
        cout << "  1. SZYBKI POKAZ\n";
        cout << "  2. Wszystkie testy automatyczne\n";
        cout << "  3. Pojedynczy test (1-12)\n";
        cout << "  0. Wyjscie\n";
        cout << "  Wybor: ";
        int wybor;
        if (!(cin >> wybor)) {
            if (cin.eof()) return bledy == 0 ? 0 : 1;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Niepoprawny wybor.\n";
            continue;
        }
        if (wybor == 0) return bledy == 0 ? 0 : 1;
        if (wybor == 1) pokazDemo();
        else if (wybor == 2) wszystkieTesty();
        else if (wybor == 3) {
            cout << "  Numer testu (1-12): ";
            int nr;
            if (!(cin >> nr)) {
                if (cin.eof()) return bledy == 0 ? 0 : 1;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  Niepoprawny numer.\n";
                continue;
            }
            resetuj();
            wykonajTest(nr);
            podsumowanie();
        } else cout << "  Nie ma takiej opcji.\n";
    }
}

int main(int argc, char* argv[]) {
    cout << fixed << setprecision(2);
    if (argc <= 1) return menu();
    string opcja = argv[1];
    if (opcja == "--demo") return pokazDemo();
    if (opcja == "--all") return wszystkieTesty();
    if (opcja == "--menu") return menu();
    if (opcja == "--test" && argc >= 3) {
        int nr = 0;
        try { nr = stoi(argv[2]); }
        catch (const exception&) {
            cout << "Niepoprawny numer testu.\n";
            return 2;
        }
        if (nr < 1 || nr > 12) {
            cout << "Numer testu musi byc od 1 do 12.\n";
            return 2;
        }
        resetuj();
        naglowek("POJEDYNCZY TEST");
        wykonajTest(nr);
        podsumowanie();
        return bledy == 0 ? 0 : 1;
    }
    cout << "Uzycie: testy.exe --demo | --all | --menu | --test N\n";
    return 2;
}
