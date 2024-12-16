#include <iostream>
#include <vector>
#include <fstream>      // zapis/odczyt z pliku
#include <sstream>      // stringstream: wczytajLiczbe()
#include <cstdio>       //remove, reneme
#include <algorithm>    //transform

using namespace std;

struct Adresat {
    int id;
    string imie = "", nazwisko = "", numerTelefonu = "", adres = "", email = "";
};

string wczytajTekst() {
    string tekst = "";

    cin.sync();
    getline(cin, tekst);

    return tekst;
}

int wczytajLiczbe() {
    string wejscie = "";
    int liczba = 0;

    while(true)    {
        cin.sync();
        wejscie = wczytajTekst();
        stringstream myStream(wejscie);
        if(myStream >> liczba)
            break;
        cout << "To nie jest liczba. Wpisz ponownie!: " << endl;
    }
    return liczba;
}

char wczytajZnak() {
    string input = "";
    char inputChar = '0';

    while(true) {
        input = wczytajTekst();
        if(input.length() == 1) {
            inputChar = input[0];
            break;
        }
        cout << "To nie jest pojedynczy znak! Wpisz ponownie:" << endl;
    }
    return inputChar;
}

void wyswietlMenuGlowne() {
    system("cls");
    cout << "\t<<< KSIAZKA ADRESOWA >>>"                            << endl << endl;
    cout << "1. Dodaj adresata do ksiazki adresowej"                << endl;
    cout << "2. Wyszukaj po imieniu"                                << endl;
    cout << "3. Wyszukaj po nazwisku"                               << endl;
    cout << "4. Wyswietl wszystkich adresatow z ksiazki adresowej"  << endl;
    cout << "5. Edytuj wybranego adresata"                          << endl;
    cout << "6. Usun wybranego adresata"                            << endl;
    cout << "9. Zakoncz program"                                    << endl << endl;
}

void wczytajDaneAdresata(Adresat &daneAdresata, string tekst, int licznik) {
    switch(licznik) {
        case 1:     daneAdresata.id = stoi(tekst);         break;
        case 2:     daneAdresata.imie = tekst;             break;
        case 3:     daneAdresata.nazwisko = tekst;         break;
        case 4:     daneAdresata.numerTelefonu = tekst;    break;
        case 5:     daneAdresata.email = tekst;            break;
        case 6:     daneAdresata.adres = tekst;            break;
        default:
            cout << "Blad wczytywania. Ksiazka Adresowa zostanie zamknieta!" << endl;
            system("pause");
            exit(0);
    }
}

Adresat wczytajAdresata(string linia) {
    Adresat daneAdresata;
    char separator = '|';
    int separatorLicznik = 0;
    string przypiszTekst = "";

    for (size_t i = 0; i < linia.length(); i++) {
        if (linia[i] != separator)
            przypiszTekst.push_back(linia[i]);
        else {
            separatorLicznik++;
            wczytajDaneAdresata(daneAdresata, przypiszTekst, separatorLicznik);
            przypiszTekst.clear();
            continue;
        }
    }
    return daneAdresata;
}

void wczytajIstniejacychAdresatow(vector <Adresat> &adresaci) {
    Adresat daneAdresata;
    fstream plikZAdresatami;
    string linia = "";

    plikZAdresatami.open("List_of_Contacts.txt", ios::in);
        if (plikZAdresatami.good()) {
            while (getline(plikZAdresatami, linia)) {
                daneAdresata = wczytajAdresata(linia);
                adresaci.push_back(daneAdresata);
            }
        }
    plikZAdresatami.close();
}

bool czyPodanyAdresatJuzIstnieje(vector <Adresat> adresaci, Adresat nowyAdresat) {
    bool adresatJuzIstnieje = false;

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
        if (itr->imie == nowyAdresat.imie && itr->nazwisko == nowyAdresat.nazwisko && itr->numerTelefonu == nowyAdresat.numerTelefonu &&  itr->email == nowyAdresat.email && itr->adres == nowyAdresat.adres) {
            adresatJuzIstnieje = true;
            break;
        }
    }
    return adresatJuzIstnieje;
}

void zapiszAdresataDoPlikuTekstowego(Adresat daneAdresata) {
    fstream plikZAdresatami;
    plikZAdresatami.open("List_of_Contacts.txt", ios::out | ios::app);

    if (plikZAdresatami.good()) {
        plikZAdresatami << to_string(daneAdresata.id) << '|';
        plikZAdresatami << daneAdresata.imie << '|';
        plikZAdresatami << daneAdresata.nazwisko << '|';
        plikZAdresatami << daneAdresata.numerTelefonu << '|';
        plikZAdresatami << daneAdresata.email << '|';
        plikZAdresatami << daneAdresata.adres << '|' << endl;
        plikZAdresatami.close();

        cout << endl << "Adresat zostal dodany do ksiazki adresowej." << endl;
    } else
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
}

void dodajAdresata(vector <Adresat> &adresaci) {
    Adresat daneAdresata;
    string numerIdAdresataString = "";
    string daneAdresataTekst = "";

    system("cls");
    cout << "\t<<< DODAJ ADRESATA >>>" << endl << endl;

    if (adresaci.empty())
        daneAdresata.id = 1;
    else
        daneAdresata.id = adresaci.back().id + 1;

    cout << endl << "Numer ID adresata:\t\t" << daneAdresata.id << endl;

    cout << "Podaj imie:\t\t\t";
    daneAdresata.imie = wczytajTekst();

    cout << "Podaj nazwisko:\t\t\t";
    daneAdresata.nazwisko = wczytajTekst();

    cout << "Podaj numer telefonu:\t\t";
    daneAdresata.numerTelefonu = wczytajTekst();

    cout << "Podaj adres email:\t\t";
    daneAdresata.email = wczytajTekst();

    cout << "Podaj adres zamieszkania:\t";
    daneAdresata.adres = wczytajTekst();


    if (czyPodanyAdresatJuzIstnieje(adresaci, daneAdresata)) {
        cout << endl << "Podany adresat juz istnieje!" << endl;
    } else {
        adresaci.push_back(daneAdresata);
        zapiszAdresataDoPlikuTekstowego(daneAdresata);
    }
    system("pause");
}

void wyswietlDaneAdresata(vector <Adresat> :: iterator itr) {
    cout << endl;
    cout << "Numer ID:\t\t"         << itr->id                                  << endl;
    cout << "Imie i Nazwisko:\t"    << itr->imie << " " << itr->nazwisko        << endl;
    cout << "nr. telefonu:\t\t"     << itr->numerTelefonu                       << endl;
    cout << "Email:\t\t\t"          << itr->email                               << endl;
    cout << "Adres:\t\t\t"          << itr->adres                               << endl << endl;
}

string ignorujWilkoscLiter(string slowo) {

    transform(slowo.begin(), slowo.end(), slowo.begin(), :: toupper);
    return slowo;
}

void wyszukajPoImieniu(vector <Adresat> adresaci) {
    bool znalezionyAdresat = false;
    string imieDoWyszukania = "";

    system("cls");
    if (!adresaci.empty()) {
        cout << "\t<<< WYSZUKAJ PO IMIENIU >>>" << endl << endl;
        cout << "Wprowadz imie:\t\t";
        imieDoWyszukania = wczytajTekst();

        for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (ignorujWilkoscLiter(itr->imie) == ignorujWilkoscLiter(imieDoWyszukania)) {
                wyswietlDaneAdresata(itr);
                znalezionyAdresat = true;
            }
        }
        if (znalezionyAdresat == false)
            cout << endl << "Nie znaleziono adresata o podanym imieniu!" << endl;
    } else {
        cout << "Ksiazka Adresowa jest pusta!" << endl;
    }
    system("pause");
}

void wyszukajPoNazwisku(vector <Adresat> adresaci) {
    bool znalezionyAdresat = false;
    string nazwiskoDoWyszukania = "";

    system("cls");
    if (!adresaci.empty()) {
        cout << "\t<<< WYSZUKAJ PO NAZWISKU >>>" << endl << endl;
        cout << "Wprowadz nazwisko:\t\t";
        nazwiskoDoWyszukania = wczytajTekst();

        for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr->nazwisko == nazwiskoDoWyszukania) {
                wyswietlDaneAdresata(itr);
                znalezionyAdresat = true;
            }
        }
        if (znalezionyAdresat == false)
            cout << endl << "Nie znaleziono adresata o podanym nazwisku!" << endl;
    } else {
        cout << "Ksiazka Adresowa jest pusta!" << endl;
    }
    system("pause");
}

void wyswietlWszystkichAdresatow(vector <Adresat> adresaci) {
    system("cls");
    if (!adresaci.empty()) {
        cout << "\t<<< WSZYSCY ADRESACI >>>" << endl << endl;
        cout << "Liczba Adresatow: " << adresaci.size() << endl;

        for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
            wyswietlDaneAdresata(itr);
    } else {
        cout << "Brak kontaktow do wyswietlenia. Ksiazka adresowa jest pusta!" << endl;
    }
    system("pause");
}

void zastapPlikTekstowy() {
    char nazwaPrzedZmiana[] = "Updated_List_of_Contacts.txt";
    char nazwaPoZmianie[] = "List_of_Contacts.txt";

    if (remove("List_of_Contacts.txt") == 0 && rename(nazwaPrzedZmiana, nazwaPoZmianie) == 0)
        return;
    else
        cout << "Blad podczas nadpisywania pliku tekstowego." << endl;
}

void zaktualizujPlikTekstowy(vector <Adresat> adresaci) {
    fstream zaktualizowanyPlik;
    string daneAdresata = "";

    zaktualizowanyPlik.open("Updated_List_of_Contacts.txt", ios::out);
    if (zaktualizowanyPlik.good()) {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            daneAdresata += to_string(itr->id) + '|';
            daneAdresata += itr->imie + '|';
            daneAdresata += itr->nazwisko + '|';
            daneAdresata += itr->numerTelefonu + '|';
            daneAdresata += itr->email + '|';
            daneAdresata += itr->adres + '|';

            zaktualizowanyPlik << daneAdresata << endl;
            daneAdresata.clear();
        }
        zaktualizowanyPlik.close();
    }
    zastapPlikTekstowy();
}

int wybierzMenuEdycji() {
    int wyborUzytkownika = 0;

    cout << endl << endl << "Wybierz dane do edycji:\t" << endl;
    cout << "1 - Imie"                      << endl;
    cout << "2 - Nazwisko"                  << endl;
    cout << "3 - Numer Telefonu"            << endl;
    cout << "4 - Email"                     << endl;
    cout << "5 - Adres"                     << endl;
    cout << "6 - Powrot do Menu Glownego"   << endl;

    cout << endl << "Twoj wybor: ";
    wyborUzytkownika = wczytajLiczbe();

    while (wyborUzytkownika < 1 || wyborUzytkownika > 6) {
        cout << endl << "Niepoprawny wybor! Sprobuj ponownie." << endl;
        cout << "Twoj wybor: ";
        wyborUzytkownika = wczytajLiczbe();
    }
    return wyborUzytkownika;
}

void edytujWybranegoAdresata(vector <Adresat> &adresaci) {
    bool czyIstniejeAdresat = false;
    int numerId = 0;
    int wyborUzytkownika = 0;

    if (!adresaci.empty()) {
        system("cls");
        cout << "\t<<< EDYTUJ ADRESATA >>>" << endl << endl;
        cout << "Wprowadz numer ID adresata do edycji:\t";
        numerId = wczytajLiczbe();

        for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr->id == numerId) {
                czyIstniejeAdresat = true;
                cout << endl << "Wybrany adresat:";
                wyswietlDaneAdresata(itr);
                wyborUzytkownika = wybierzMenuEdycji();
                if (wyborUzytkownika == 6) {
                    return;
                } else {
                    system("cls");
                    cout << endl << "Wprowadz zmiane:\t";
                    switch (wyborUzytkownika) {
                        case 1: itr->imie = wczytajTekst();            break;
                        case 2: itr->nazwisko = wczytajTekst();        break;
                        case 3: itr->numerTelefonu = wczytajTekst();   break;
                        case 4: itr->email = wczytajTekst();           break;
                        case 5: itr->adres = wczytajTekst();           break;
                    }
                    zaktualizujPlikTekstowy(adresaci);
                    cout << endl << "Zapisano zmiany!" << endl;
                    break;
                }
            }
        }
        if (!czyIstniejeAdresat)
            cout << endl << "Nie znaleziono adresata o takim numerze ID!" << endl;
    } else
        cout << endl << "Ksiazka Adresowa jest pusta!" << endl << endl;

    system("pause");
}

void usunWybranegoAdresata(vector <Adresat> &adresaci) {
    bool adresatZnaleziony = false;
    bool zakonczPetle = false;
    char znak;
    int numerId = 0;

    if (!adresaci.empty()) {
        system("cls");
        cout << "\t<<< USUN ADRESATA >>>" << endl << endl;
        cout << "Wprowadz numer ID adresata do usuniecia:\t";
        numerId = wczytajLiczbe();

        for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr->id == numerId) {
                adresatZnaleziony = true;
                cout << endl << "Wybrany adresat:";
                wyswietlDaneAdresata(itr);
                cout << "Czy napewno chcesz usunac wybranego Adresata?(t/n): ";

                while (zakonczPetle == false) {
                    znak = wczytajZnak();
                    if (znak == 't') {
                        adresaci.erase(itr);
                        cout << endl << "Adresat zostal usuniety!" << endl;
                        zaktualizujPlikTekstowy(adresaci);
                        zakonczPetle = true;
                    } else if (znak == 'n') {
                        cout << endl << "Wybrany adresat NIE zostal usuniety!" << endl;
                        zakonczPetle = true;
                    } else
                        cout << endl << "Wpisz t lub n!" << endl;
                }
                if (zakonczPetle == true)
                    break;
            }
        }
        if (!adresatZnaleziony)
            cout << endl << "Nie znaleziono adresata o takim numerze ID!" << endl;
    } else
        cout << endl << "Ksiazka Adresowa jest pusta!" << endl << endl;

    system("pause");
}

int main() {
    vector <Adresat> adresaci;
    wczytajIstniejacychAdresatow(adresaci);

    while (1) {
        wyswietlMenuGlowne();

        int wyborUzytkownika = 0;
        cout << "Wybierz jedna z opcji:\t";
        wyborUzytkownika = wczytajLiczbe();

        switch (wyborUzytkownika) {
        case 1:   dodajAdresata(adresaci);                      break;
        case 2:   wyszukajPoImieniu(adresaci);                  break;
        case 3:   wyszukajPoNazwisku(adresaci);                 break;
        case 4:   wyswietlWszystkichAdresatow(adresaci);        break;
        case 5:   edytujWybranegoAdresata(adresaci);            break;
        case 6:   usunWybranegoAdresata(adresaci);              break;
        case 9:   exit(0);
        default:  cout << "Nieprawidlowy wybor! Sprobuj ponownie." << endl;
                  system("pause");
        }

    }
    return 0;
}
