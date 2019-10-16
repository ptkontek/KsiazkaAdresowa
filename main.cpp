#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <iterator>

using namespace std;

struct Uzytkownik {
    int idUzytkownika=0;
    string nazwa="", haslo="";
};

struct Adresat {
    int idAdresata=0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};

void wczytajUzytkownikow(vector <Uzytkownik> &uzytkownicy);
vector <Adresat> wczytajAdresatow(vector <Adresat> adresaci);

int rejestracja(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    Uzytkownik uzytkownik;
    wczytajUzytkownikow(uzytkownicy);
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    int i = 0;
    while (i < iloscUzytkownikow) {
        if ( uzytkownicy[i].nazwa == nazwa) {
            cout << "Taki uzytkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0; //wyzerowanie petli aby zaczela dzialac od poczatku
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;

    int osobaId;

    if (uzytkownicy.empty() == true) {
        osobaId = 1;
    } else {
        osobaId = uzytkownicy.back().idUzytkownika + 1;
    }
    uzytkownik.idUzytkownika = osobaId;
    uzytkownik.nazwa = nazwa;
    uzytkownik.haslo = haslo;

    uzytkownicy.push_back(uzytkownik);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    if (plik.good()) {
        plik << osobaId << "|" << nazwa << "|" << haslo << "|" << endl;

        plik.close();

        cout << "Uzytkownik zostal dodany do pliku txt." << endl;
        Sleep(1000);
    } else {
        ofstream plik( "Uzytkownicy.txt" );
        plik << osobaId << "|" << nazwa << "|" << haslo << "|" << endl;

        plik.close();

        cout << "Uzytkownik zostal dodany do pliku txt." << endl;
        Sleep(1000);
    }
    cout << iloscUzytkownikow;
    Sleep(1000);
    return iloscUzytkownikow+1;

}

int logowanie(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow) {
    Uzytkownik uzytkownik;
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    int i = 0;
    while (i < iloscUzytkownikow) {
        if ( uzytkownicy[i].nazwa == nazwa) {
            for ( int proby = 0; proby < 3; proby++) {
                cout << "Podaj haslo. Pozostalo prob: " << 3-proby << ":";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo) {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return uzytkownicy[i].idUzytkownika;
                }

            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejnym zalogowaniem.";
            Sleep(3000);
        }
        i++;
    }
    cout << "Nie ma uzytkownika o takiej nazwie." << endl;
    return 0;
}

vector <Adresat> dodajOsobeDoKsiazkiAdresowej(vector <Adresat> adresaci, int iloscOsob);
void wyszukajOsobePoImieniu(vector <Adresat> adresaci, int iloscOsob);
void wyszukajOsobePoNazwisku(vector <Adresat> adresaci, int iloscOsob);
void wyswietlWszystkichAdresatow(vector <Adresat> adresaci, int iloscOsob);
vector <Adresat> usunAdresata(vector <Adresat> adresaci, int iloscOsob);
vector <Adresat> edytujAdresata(vector <Adresat> adresaci, int iloscOsob);

int main() {
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;
    wczytajUzytkownikow(uzytkownicy);

    int idUzytkownika = 0;
    int iloscUzytkownikow = 0;
   int iloscOsob = 0;


    cout<<"Lista wszystkich uzytk"<<endl;
    for (int i=0; i<uzytkownicy.size(); i++) {
        cout << endl << endl;
        cout <<  uzytkownicy[i].idUzytkownika<< endl;
        cout <<  uzytkownicy[i].nazwa<< endl;
        cout <<  uzytkownicy[i].haslo<< endl;

    }
    getch();

    adresaci = wczytajAdresatow(adresaci);

    iloscOsob = adresaci.size();
    cout << iloscOsob <<endl;

    char wyborOpcjiMenu;
    while (true) {
        system("cls");
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl;;
        cout << "3. Zakoncz program" << endl;
        cin >> wyborOpcjiMenu;

        if (wyborOpcjiMenu == '1') {
        iloscUzytkownikow = rejestracja(uzytkownicy,iloscUzytkownikow);
        } else if (wyborOpcjiMenu == '2') {
           idUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
        } else if (wyborOpcjiMenu == '3') {
            exit(0);
        }
    }


    /*while (true) {
        system("cls");
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyszukaj osoby po imieniu" << endl;
        cout << "3. Wyszukaj osoby po nazwiskuu" << endl;
        cout << "4. Wswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> wyborOpcjiMenu;

        if (wyborOpcjiMenu == '1') {
            adresaci = dodajOsobeDoKsiazkiAdresowej(adresaci, iloscOsob);
            iloscOsob++;
        } else if (wyborOpcjiMenu == '2') {
            wyszukajOsobePoImieniu(adresaci, iloscOsob);
        } else if (wyborOpcjiMenu == '3') {
            wyszukajOsobePoNazwisku(adresaci, iloscOsob);
        } else if (wyborOpcjiMenu == '4') {
            wyswietlWszystkichAdresatow(adresaci, iloscOsob);
        } else if (wyborOpcjiMenu == '5') {
            adresaci = usunAdresata(adresaci, iloscOsob);
            iloscOsob--;
        } else if (wyborOpcjiMenu == '6') {
            adresaci = edytujAdresata(adresaci, iloscOsob);
        } else if (wyborOpcjiMenu == '9') {
            exit(0);
        }
    }*/
    return 0;
}

void wczytajUzytkownikow(vector <Uzytkownik> &uzytkownicy) {
    Uzytkownik uzytkownik;
    int iloscUzytkownikow = 0;
    string liniaWPliku;
    int nrLinii = 1;

    fstream plik;
    plik.open("Uzytkownicy.txt",ios::in);

    if (plik.good() == true) {
        while (getline(plik,liniaWPliku,'|')) {
            switch (nrLinii) {
            case 1:
                uzytkownik.idUzytkownika = atoi(liniaWPliku.c_str());
                break;
            case 2:
                uzytkownik.nazwa = liniaWPliku;
                break;
            case 3:
                uzytkownik.haslo = liniaWPliku;
                break;
            }
            if (nrLinii >= 3) {
                nrLinii = 1;
                iloscUzytkownikow++;
                uzytkownicy.push_back(uzytkownik);
            } else {
                nrLinii++;
            }
        }
        plik.close();
        cout<<"Ilosc uzytkownikow: "<<uzytkownicy.size()<<endl;

    }
}

vector <Adresat> wczytajAdresatow(vector <Adresat> adresaci) {
    Adresat adresat;
    int iloscOsob = 0;
    string liniaWPliku;
    int nrLinii = 1;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::in);

    if (plik.good() == true) {
        while (getline(plik,liniaWPliku,'|')) {
            switch (nrLinii) {
            case 1:
                adresat.idAdresata = atoi(liniaWPliku.c_str());
                break;
            case 2:
                adresat.imie = liniaWPliku;
                break;
            case 3:
                adresat.nazwisko = liniaWPliku;
                break;
            case 4:
                adresat.numerTelefonu = liniaWPliku;
                break;
            case 5:
                adresat.email = liniaWPliku;
                break;
            case 6:
                adresat.adres = liniaWPliku;
                break;
            }
            if (nrLinii >= 6) {
                nrLinii = 1;
                iloscOsob++;
                adresaci.push_back(adresat);
            } else {
                nrLinii++;
            }
        }
        plik.close();
        cout<<"Ilosc adresatow: "<<adresaci.size()<<endl;

    } else if (plik.good()==false) {
        cout<<"Brak ksiazki adresowej. Wczytaj adresata by ja stworzyc."<<endl;
    }
    return adresaci;
}

vector <Adresat> dodajOsobeDoKsiazkiAdresowej(vector <Adresat> adresaci, int iloscOsob) {
    Adresat adresat;
    string imie, nazwisko, numerTelefonu, email, adres;

    system("cls");
    cout << "Dodawanie osoby" << endl;
    cout << "Podaj imie uzytkownika: ";
    cin >> imie;
    cout << "Podaj nazwisko uzytkownika: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu uzytkownika: ";
    cin.sync(); // oprozniam bufor
    getline(cin, numerTelefonu); // wczytuje razem ze spacja
    cout << "Podaj email uzytkownika: ";
    cin >> email;
    cout << "Podaj adres uzytkownika: ";
    cin.sync();
    getline(cin, adres);

    int osobaId;

    if (adresaci.empty() == true) {
        osobaId = 1;
    } else {
        osobaId = adresaci.back().idAdresata + 1;
    }

    adresat.idAdresata = osobaId;
    adresat.imie = imie;
    adresat.nazwisko = nazwisko;
    adresat.numerTelefonu = numerTelefonu;
    adresat.email = email;
    adresat.adres = adres;

    adresaci.push_back(adresat);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good()) {
        plik << osobaId << "|" << imie << "|" << nazwisko << "|" << numerTelefonu << "|" << email << "|" << adres << "|" << endl;

        plik.close();

        cout << "Osoba zostala dodana." << endl;
        Sleep(1000);
    } else {
        cout<<"Dodaje pierwszego adresata do nowej ksiazki adresowej."<<endl;
        ofstream plik( "KsiazkaAdresowa.txt" );

        plik << osobaId << "|" << imie << "|" << nazwisko << "|" << numerTelefonu << "|" << email << "|" << adres << "|" << endl;

        plik.close();

        cout << "Osoba zostala dodana." << endl;
        Sleep(1000);
    }
    return adresaci;
}

void wyszukajOsobePoImieniu(vector <Adresat> adresaci, int iloscOsob) {
    string imie="";
    cout<<"Podaj imie do wyszukania: ";
    cin >> imie;

    for (int i=0; i<=iloscOsob; i++) {
        if ( adresaci[i].imie == imie) {
            cout << endl << endl;
            cout << adresaci[i].idAdresata << endl;
            cout << adresaci[i].imie << endl;
            cout << adresaci[i].nazwisko << endl;
            cout << adresaci[i].numerTelefonu << endl;
            cout << adresaci[i].email << endl;
            cout << adresaci[i].adres << endl<<endl;
        }
    }
    getch();
}

void wyszukajOsobePoNazwisku(vector <Adresat> adresaci, int iloscOsob) {
    string nazwisko="";
    cout<<"Podaj nazwisko do wyszukania: ";
    cin >> nazwisko;

    for (int i=0; i<=iloscOsob; i++) {
        if ( adresaci[i].nazwisko == nazwisko) {
            cout << endl << endl;
            cout << adresaci[i].idAdresata << endl;
            cout << adresaci[i].imie << endl;
            cout << adresaci[i].nazwisko << endl;
            cout << adresaci[i].numerTelefonu << endl;
            cout << adresaci[i].email << endl;
            cout << adresaci[i].adres << endl<<endl;
        }
    }
    getch();
}

void wyswietlWszystkichAdresatow(vector <Adresat> adresaci, int iloscOsob) {

    cout<<"Lista wszystkich adresatow"<<endl;
    for (int i=0; i<iloscOsob; i++) {
        cout << endl << endl;
        cout << adresaci[i].idAdresata << endl;
        cout << adresaci[i].imie << endl;
        cout << adresaci[i].nazwisko << endl;
        cout << adresaci[i].numerTelefonu << endl;
        cout << adresaci[i].email << endl;
        cout << adresaci[i].adres << endl<<endl;
    }
    getch();
}

vector <Adresat> usunAdresata(vector <Adresat> adresaci, int iloscOsob) {
    int nrID;
    cout << "Podaj nr ID adresata do usuniecia: ";
    cin >> nrID;
    bool czyIstniejeAdresat = false;

    for (vector<Adresat>::iterator itr=adresaci.begin(); itr!=adresaci.end()+1; ++itr) {
        if (itr->idAdresata == nrID) {
            czyIstniejeAdresat = true;
            adresaci.erase(itr);
            cout<<"Usunieto adresata o nr ID = " <<nrID<<endl;
            fstream plik;
            plik.open("KsiazkaAdresowa.txt",ios::out | ios::trunc );
            plik.clear();
            plik.flush();

            for (vector<Adresat> ::iterator itr=adresaci.begin(); itr!=adresaci.end(); ++itr) {
                if (plik.good()) {
                    plik << itr->idAdresata << "|" << itr->imie << "|" << itr->nazwisko << "|" << itr->numerTelefonu << "|" << itr->email << "|" << itr->adres << "|" << endl;
                }
            }
            plik.close();
        }
    }
    if (czyIstniejeAdresat == false)
        cout << "Nie znaleziono adresata o numerze id: " << nrID << " w ksiazce adresowej" << endl;
    getch();
    Sleep(1000);

    return adresaci;
}

vector <Adresat> edytujAdresata(vector <Adresat> adresaci, int iloscOsob) {
    int nrID;
    cout << "Podaj nr ID adresata do edycji: ";
    cin >> nrID;
    cout<< "Wybierz dane do edycji: ";
    Sleep(1000);
    char wybor;

    system("cls");
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Numer telefonu" << endl;
    cout << "4. E-mail" << endl;
    cout << "5. Adres" << endl;
    cout << "6. Powrot do menu" << endl;
    cin >> wybor;
    string zmiana;

    for (vector<Adresat> ::iterator itr=adresaci.begin(); itr!=adresaci.end()+1; ++itr) {
        if (itr->idAdresata == nrID) {
            if (wybor == '1') {
                cout << "Podaj nowe imie: ";
                cin >>zmiana;
                itr->imie=zmiana;

            } else if (wybor == '2') {
                cout << "Podaj nowe nazwisko: ";
                cin >>zmiana;
                itr->nazwisko=zmiana;


            } else if (wybor == '3') {
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                getline(cin, zmiana);
                itr->numerTelefonu=zmiana;


            } else if (wybor == '4') {
                cout << "Podaj nowy e-mail: ";
                cin >>zmiana;
                itr->email=zmiana;

            } else if (wybor == '5') {
                cout << "Podaj nowy adres: ";
                cin.sync();
                getline(cin, zmiana);
                itr->adres=zmiana;

            } else if (wybor == '6') {
                exit(0);
            }
        }
    }

    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::out | ios::trunc );
    plik.clear();
    plik.flush();

    for (vector<Adresat> ::iterator itr=adresaci.begin(); itr!=adresaci.end(); ++itr) {
        if (plik.good()) {
            plik << itr->idAdresata << "|" << itr->imie << "|" << itr->nazwisko << "|" << itr->numerTelefonu << "|" << itr->email << "|" << itr->adres << "|" << endl;
        }
    }
    plik.close();
    Sleep(1000);
    return adresaci;
}
