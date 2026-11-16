#include "System_Hotelu.h"
#include "Administrator.h"
#include "Manager.h"
#include "Personel_pokojowy.h"
#include "Recepcjonista.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <string>

using namespace std;

int main() {
    SystemHotelu hotel;
    int rola = 0;
    cout << fixed << setprecision(2);
    cin.exceptions(ios::failbit | ios::badbit); // Włączanie wyjątków dla błędów wejścia/wyjścia.

    cout << "SYSTEM HOTELU\n";

    while (true) {
        try {
            if (rola == 0) {
                cout << "\n=== WYBIERZ ROLE ===\n"
                     << "1. Gosc\n"
                     << "2. Recepcjonista\n"
                     << "3. Manager\n"
                     << "4. Personel pokojowy\n"
                     << "5. Administrator\n"
                     << "0. Koniec\nWybor: ";
                cin >> rola;
                if (rola == 0) {
                    break;
                }
                if (rola < 1 || rola > 5) {
                    cout << "Nie ma takiej roli.\n";
                    rola = 0;
                }
                continue;
            }

            if (rola == 1) {
                cout << "\n=== GOSC ===\n"
                     << "1. Lista pokoi\n"
                     << "2. Lista uslug\n"
                     << "3. Zarejestruj sie\n"
                     << "4. Sprawdz wolne pokoje\n"
                     << "5. Zarezerwuj pokoj\n"
                     << "6. Moje rezerwacje\n"
                     << "7. Anuluj rezerwacje\n"
                     << "8. Dodaj usluge do mojej rezerwacji\n";
            } else if (rola == 2) {
                cout << "\n=== RECEPCJONISTA ===\n"
                     << "1. Lista gosci\n"
                     << "2. Dodaj goscia\n"
                     << "3. Lista rezerwacji\n"
                     << "4. Zarezerwuj pokoj\n"
                     << "5. Dodaj usluge do rezerwacji\n"
                     << "6. Zameldowanie\n"
                     << "7. Wymeldowanie i faktura\n"
                     << "8. Anulowanie rezerwacji\n";
            } else if (rola == 3) {
                cout << "\n=== MANAGER ===\n"
                     << "1. Lista pokoi\n"
                     << "2. Dodaj pokoj\n"
                     << "3. Lista uslug\n"
                     << "4. Dodaj usluge do oferty\n"
                     << "5. Lista rezerwacji\n"
                     << "6. Statystyki\n"
                     << "7. Dodaj pracownika\n";
            } else if (rola == 4) {
                cout << "\n=== PERSONEL POKOJOWY ===\n"
                     << "1. Lista pokoi\n"
                     << "2. Pokoje wymagajace sprzatania\n"
                     << "3. Zmien status sprzatania\n";
            } else {
                cout << "\n=== ADMINISTRATOR ===\n"
                     << "1. Stan systemu\n"
                     << "2. Dodaj pracownika\n"
                     << "3. Utworz kopie (tylko liczniki)\n"
                     << "4. Sprawdz plik kopii\n";
            }
            cout << "0. Powrot\nWybor: ";
            int wybor;
            cin >> wybor;
            if (wybor == 0) {
                rola = 0;
                continue;
            }

            // Np. 101 = rola 1 (gosc), opcja 1 (lista pokoi).
            switch (rola * 100 + wybor) {
                case 101: case 301: case 401:
                    cout << "Status sprzatania: 0 czysty, 1 do sprzatania, "
                         << "2 w trakcie.\n";
                    for (const Pokoj& pokoj : hotel.pobierzPokoje()) {
                        cout << "Pokoj " << pokoj.pobierzNumerPokoju()
                             << ", miejsc: " << pokoj.pobierzLiczbeMiejsc()
                             << ", cena: " << pokoj.pobierzStawke()
                             << " zl, status "
                             << static_cast<int>(
                                    pokoj.pobierzStatusSprzatania()) << "\n";
                    }
                    break;

                case 102: case 303:
                    for (const UslugaDodatkowa& usluga : hotel.pobierzUslugi()) {
                        cout << usluga.pobierzId() << ". "
                             << usluga.pobierzNazwe() << " - "
                             << usluga.pobierzCene() << " zl/"
                             << usluga.pobierzJednostke() << "\n";
                    }
                    break;

                case 103: case 202: {
                    int id;
                    string imie, nazwisko, email, telefon;
                    cout << "ID: "; cin >> id;
                    cout << "Imie: "; getline(cin >> ws, imie);
                    cout << "Nazwisko: "; getline(cin >> ws, nazwisko);
                    cout << "Email: "; getline(cin >> ws, email);
                    cout << "Telefon: "; cin >> telefon;
                    hotel.dodajGoscia(Gosc(id, imie, nazwisko, email, telefon));
                    cout << "Dodano goscia.\n";
                    break;
                }

                case 104: {
                    Data od{}, do_daty{};
                    cout << "Przyjazd (rok miesiac dzien): ";
                    cin >> od.rok >> od.miesiac >> od.dzien;
                    cout << "Wyjazd (rok miesiac dzien): ";
                    cin >> do_daty.rok >> do_daty.miesiac >> do_daty.dzien;
                    cout << "Wolne pokoje: ";
                    for (int numer : hotel.wyszukajDostepnePokoje(
                             od, do_daty)) {
                        cout << numer << " ";
                    }
                    cout << "\n";
                    break;
                }

                case 105: case 204: {
                    int gosc_id, numer;
                    Data od{}, do_daty{};
                    cout << "ID goscia i numer pokoju: ";
                    cin >> gosc_id >> numer;
                    cout << "Przyjazd (rok miesiac dzien): ";
                    cin >> od.rok >> od.miesiac >> od.dzien;
                    cout << "Wyjazd (rok miesiac dzien): ";
                    cin >> do_daty.rok >> do_daty.miesiac >> do_daty.dzien;
                    int id = hotel.zarezerwujPokoj(gosc_id, numer, od, do_daty);
                    cout << "Numer rezerwacji: " << id << "\n";
                    break;
                }

                case 106: {
                    int gosc_id;
                    cout << "Twoje ID: "; cin >> gosc_id;
                    for (const Rezerwacja& r : hotel.pobierzRezerwacje()) {
                        if (r.pobierzGoscId() == gosc_id) {
                            cout << "Rezerwacja " << r.pobierzId()
                                 << ", pokoj " << r.pobierzNumerPokoju()
                                 << ", status "
                                 << static_cast<int>(r.pobierzStatus()) << "\n";
                        }
                    }
                    break;
                }

                case 107: {
                    int gosc_id, id;
                    cout << "ID goscia i rezerwacji: ";
                    cin >> gosc_id >> id;
                    cout << "Oplata: " << hotel.anulujRezerwacje(
                        gosc_id, id, time(nullptr)) << " zl\n";
                    break;
                }

                case 108: {
                    int gosc_id, rezerwacja_id, usluga_id, ilosc;
                    cout << "Twoje ID: "; cin >> gosc_id;
                    cout << "ID rezerwacji, ID uslugi, ilosc: ";
                    cin >> rezerwacja_id >> usluga_id >> ilosc;
                    hotel.dodajUslugeGoscia(
                        gosc_id, rezerwacja_id, usluga_id, ilosc);
                    cout << "Dodano usluge do Twojej rezerwacji.\n";
                    break;
                }

                case 201:
                    for (const Gosc& gosc : hotel.pobierzGosci()) {
                        cout << gosc.pobierzId() << ". "
                             << gosc.pobierzImie() << " "
                             << gosc.pobierzNazwisko() << "\n";
                    }
                    break;

                case 203: case 305:
                    cout << "Status rezerwacji: 0 zarezerwowana, "
                         << "1 zameldowana, 2 wymeldowana, 3 anulowana.\n";
                    for (const Rezerwacja& r : hotel.pobierzRezerwacje()) {
                        Data od = r.pobierzDataOd();
                        Data do_daty = r.pobierzDataDo();
                        cout << "Rezerwacja " << r.pobierzId()
                             << ", gosc " << r.pobierzGoscId()
                             << ", pokoj " << r.pobierzNumerPokoju()
                             << ", " << od.rok << "-" << od.miesiac << "-"
                             << od.dzien << " do " << do_daty.rok << "-"
                             << do_daty.miesiac << "-" << do_daty.dzien
                             << ", status "
                             << static_cast<int>(r.pobierzStatus()) << "\n";
                    }
                    break;

                case 205: {
                    int rezerwacja_id, usluga_id, ilosc;
                    cout << "ID rezerwacji, ID uslugi, ilosc: ";
                    cin >> rezerwacja_id >> usluga_id >> ilosc;
                    hotel.dodajUsluge(rezerwacja_id, usluga_id, ilosc);
                    cout << "Dodano usluge.\n";
                    break;
                }

                case 206: {
                    int id;
                    cout << "ID rezerwacji: "; cin >> id;
                    hotel.zamelduj(id);
                    cout << "Zameldowano.\n";
                    break;
                }

                case 207: {
                    int id;
                    cout << "ID rezerwacji: "; cin >> id;
                    Faktura faktura = hotel.wymelduj(id);
                    cout << "Faktura " << faktura.pobierzNumer()
                         << ", do zaplaty: " << faktura.suma() << " zl\n";
                    break;
                }

                case 208: {
                    int id;
                    cout << "ID rezerwacji: "; cin >> id;
                    cout << "Oplata: " << hotel.anulujRezerwacje(
                        id, time(nullptr)) << " zl\n";
                    break;
                }

                case 302: {
                    int numer, miejsca;
                    Kwota cena;
                    cout << "Numer pokoju, miejsca, cena: ";
                    cin >> numer >> miejsca >> cena;
                    hotel.dodajPokoj(Pokoj(numer, miejsca, cena));
                    cout << "Dodano pokoj.\n";
                    break;
                }

                case 304: {
                    int id;
                    string nazwa, jednostka;
                    Kwota cena;
                    cout << "ID uslugi: "; cin >> id;
                    cout << "Nazwa: "; getline(cin >> ws, nazwa);
                    cout << "Cena: "; cin >> cena;
                    cout << "Jednostka: "; getline(cin >> ws, jednostka);
                    hotel.dodajUslugeDoOferty(
                        UslugaDodatkowa(id, nazwa, cena, jednostka));
                    cout << "Dodano usluge.\n";
                    break;
                }

                case 306: {
                    Data od{}, do_daty{};
                    cout << "Poczatek (rok miesiac dzien): ";
                    cin >> od.rok >> od.miesiac >> od.dzien;
                    cout << "Koniec (rok miesiac dzien): ";
                    cin >> do_daty.rok >> do_daty.miesiac >> do_daty.dzien;
                    Statystyki s = hotel.pobierzStatystyki(od, do_daty);
                    cout << "Rezerwacje: " << s.pobierzLiczbeRezerwacji()
                         << ", oblozenie: " << s.pobierzOblozenie()
                         << "%, przychod: " << s.pobierzPrzychod() << " zl\n";
                    break;
                }

                case 307: case 502: {
                    int typ, id;
                    string imie, nazwisko, numer;
                    cout << "Typ: 1 recepcjonista, 2 manager, "
                         << "3 sprzataczka, 4 administrator: ";
                    cin >> typ;
                    if (typ < 1 || typ > 4) {
                        cout << "Nieprawidlowy typ.\n";
                        break;
                    }
                    cout << "ID: "; cin >> id;
                    cout << "Imie: "; getline(cin >> ws, imie);
                    cout << "Nazwisko: "; getline(cin >> ws, nazwisko);
                    cout << "Numer pracownika: "; cin >> numer;
                    if (typ == 1) {
                        hotel.dodajPracownika(make_unique<Recepcjonista>(
                            id, imie, nazwisko, numer));
                    } else if (typ == 2) {
                        hotel.dodajPracownika(make_unique<Manager>(
                            id, imie, nazwisko, numer));
                    } else if (typ == 3) {
                        hotel.dodajPracownika(make_unique<PersonelPokojowy>(
                            id, imie, nazwisko, numer));
                    } else {
                        hotel.dodajPracownika(make_unique<Administrator>(
                            id, imie, nazwisko, numer));
                    }
                    cout << "Dodano pracownika.\n";
                    break;
                }

                case 402:
                    for (const Pokoj& pokoj : hotel.pobierzPokoje()) {
                        if (pokoj.pobierzStatusSprzatania() !=
                            StatusSprzatania::Czysty) {
                            cout << "Pokoj " << pokoj.pobierzNumerPokoju()
                                 << ", status " << static_cast<int>(
                                    pokoj.pobierzStatusSprzatania()) << "\n";
                        }
                    }
                    break;

                case 403: {
                    int numer, status;
                    cout << "Numer pokoju: "; cin >> numer;
                    cout << "0 czysty, 1 do sprzatania, 2 w trakcie: ";
                    cin >> status;
                    if (status < 0 || status > 2) {
                        cout << "Nieprawidlowy status.\n";
                        break;
                    }
                    hotel.zmienStatusSprzatania(
                        numer, static_cast<StatusSprzatania>(status));
                    cout << "Zmieniono status.\n";
                    break;
                }

                case 501: {
                    StanSystemu stan = hotel.sprawdzStanSystemu();
                    if (stan == StanSystemu::Gotowy) {
                        cout << "System gotowy.\n";
                    } else if (stan == StanSystemu::BrakPokoi) {
                        cout << "Brak pokoi.\n";
                    } else {
                        cout << "Brak pracownikow.\n";
                    }
                    break;
                }

                case 503: {
                    string sciezka;
                    cout << "Plik kopii (np. kopia.txt): ";
                    getline(cin >> ws, sciezka);
                    KopiaZapasowa kopia = hotel.utworzKopieZapasowa(sciezka);
                    cout << "Zapisano raport, ID " << kopia.pobierzId()
                         << ". To nie jest pelna kopia danych.\n";
                    break;
                }

                case 504: {
                    int id;
                    cout << "ID kopii: "; cin >> id;
                    cout << (hotel.zweryfikujKopie(id)
                        ? "Plik dostepny.\n" : "Brak pliku.\n");
                    break;
                }

                default:
                    cout << "Nie ma takiej opcji.\n";
            }
        } catch (const ios_base::failure&) {
            if (cin.eof()) {
                cout << "\nKoniec wprowadzania danych.\n";
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Niepoprawne dane. Sprobuj ponownie.\n";
        } catch (const exception& blad) {
            cout << "Blad: " << blad.what() << "\n";
        }
    }
    return 0;
}
