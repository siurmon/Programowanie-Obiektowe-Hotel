using namespace std;

// --- KLASY ---

class Osoba {
private:
    int id;
    string imie;
    string nazwisko;
};

class Gosc : public Osoba {
private:
    string email;
    string telefon;
    string rola;
};

class Pracownik : public Osoba {
private:
    string numerPracownika;
};

class Manager : public Pracownik {
public:
    string rola;
};

class Recepcjonista : public Pracownik {
public:
    string rola;
};

class Personel_Pokojowy : public Pracownik {
public:
    string rola;
};

class Administrator : public Pracownik {
public:
    string rola;
};

class Kopia_Zapasowa {
private:
    int id;
    DataCzas dataUtworzenia;
    string sciezkaPliku;
    StatusKopii status;
};

class Statystyki {
private:
    Data okresOd;
    Data okresDo;
    int liczbaRezerwacji;
    double oblozenieProc;
    Kwota przychodZFaktur;
};

class Usluga_Dodatkowa {
private:
    int id;
    string nazwa;
    Kwota cenaJednostkowa;
    string nazwaJednostki;
};

class Zamowiona_Usluga {
private:
    int uslugaId;
    string nazwa;
    Kwota cenaJednostkowa;
    int ilosc;
};

class Faktura {
private:
    string numer;
    int rezerwacjaId;
    Data dataWystawienia;
    Kwota kwotaPobytu;
    Kwota kwotaUslug;
    Kwota suma;
};

class Pokoj {
private:
    int numer_pokoju;
    int liczbaMiejsc;
    Kwota stawkaDobowa;
    StatusSprzatania statusSprzatania;
};

class Rezerwacja {
private:
    int id;
    int goscId;
    int pokojId;
    Data dataOd;
    Data dataDo;
    DataCzas utworzono;
    StatusRezerwacji status;
    Kwota stawkaZaDobe;
    Faktura* faktura;
    vector<Zamowiona_Usluga> zamowioneUslugi;
    Kwota oplataAnulowania;
};

class SystemHotelu {
private:
    vector<Pracownik> pracownicy;
    vector<Gosc> goscie;
    vector<Pokoj> pokoje;
    vector<Rezerwacja> rezerwacje;
    vector<Usluga_Dodatkowa> uslugi;
    vector<Kopia_Zapasowa> kopie;
};
