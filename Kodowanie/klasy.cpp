// --- KLASY ---

class Osoba {
private:
    int id;
    std::string imie;
    std::string nazwisko;
};

class Gosc : public Osoba {
private:
    std::string email;
    std::string telefon;
    std::string rola;
};

class Pracownik : public Osoba {
private:
    std::string numerPracownika;
};

class Manager : public Pracownik {
public:
    std::string rola;
};

class Recepcjonista : public Pracownik {
public:
    std::string rola;
};

class Personel_Pokojowy : public Pracownik {
public:
    std::string rola;
};

class Administrator : public Pracownik {
public:
    std::string rola;
};

class Kopia_Zapasowa {
private:
    int id;
    DataCzas dataUtworzenia;
    std::string sciezkaPliku;
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
    std::string nazwa;
    Kwota cenaJednostkowa;
    std::string nazwaJednostki;
};

class Zamowiona_Usluga {
private:
    int uslugaId;
    std::string nazwa;
    Kwota cenaJednostkowa;
    int ilosc;
};

class Faktura {
private:
    std::string numer;
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
    std::vector<Zamowiona_Usluga> zamowioneUslugi;
    Kwota oplataAnulowania;
};

class SystemHotelu {
private:
    std::vector<Pracownik> pracownicy;
    std::vector<Gosc> goscie;
    std::vector<Pokoj> pokoje;
    std::vector<Rezerwacja> rezerwacje;
    std::vector<Usluga_Dodatkowa> uslugi;
    std::vector<Kopia_Zapasowa> kopie;
};
