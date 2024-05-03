#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <conio.h>
#include <time.h>

using namespace std;

char cezar_szyfr(char r, int stala)
{
    int i;
    char s;
    if ((int(r) < 65) || (int(r) > 122))
    {
        return r;
    }
    if ((int(r) > 90) && (int(r) < 97))
    {
        return r;
    }
    if ((int(r)) > 64 && (int(r) < 91))
    {
        i = (((int(r)) + stala) % 90);
        if (i == 0)
        {
            i = 90;
        }
        if (i < 65 && i != 0)
        {
            i += 64;
        }
    }
    if (int(r) > 96 && int(r) < 123)
    {
        i = (((int(r)) + stala) % 122);
        if (i == 0)
        {
            i = 122;
        }
        if (i < 97 && i != 0)
        {
            i += 96;
        }
    }
    s = char(i);
    return s;
}

char cezar_de_szyfr(char r, int stala)
{

    int i;
    char s;
    if ((int(r) < 65) || (int(r) > 122))
    {
        return r;
    }
    if ((int(r) > 90) && (int(r) < 97))
    {
        return r;
    }
    if ((int(r)) > 64 && (int(r) < 91))
    {
        i = (((int(r)) - stala) % 90);
        if (i == 0)
        {
            i = 90;
        }
        if (i < 65 && i != 0)
        {
            i += 26;
        }
    }
    if (int(r) > 96 && int(r) < 123)
    {
        i = (((int(r)) - stala) % 122);
        if (i == 0)
        {
            i = 122;
        }
        if (i < 97 && i != 0)
        {
            i += 26;
        }
    }
    s = char(i);
    return s;
}

char vigenere_szyfr(char r, char stala)
{
    if((int(r) > 96 && int(r) < 123))
    {
        int klucz = (int(r)-97 + int(stala)-97) % 26;
        return cezar_szyfr(97, klucz);
    }
    if((int(r)) > 64 && (int(r) < 91))
    {
        int klucz = (int(r)-65 + int(stala)-65) % 26;
        return cezar_szyfr(65, klucz);
    }

}

char vigenere_de_szyfr(char r, char stala)
{
    if((int(r) > 96 && int(r) < 123))
    {
        int klucz =(int(stala)-97);
        return cezar_de_szyfr(r, klucz);
    }
    if((int(r)) > 64 && (int(r) < 91))
    {
        int klucz =(int(stala)-65);
        return cezar_de_szyfr(r, klucz);
    }
}


int main()
{
    const int k = 3;
    int stronakoncowa = k;
    int metoda_szyfrowania;
    int ktoryplik = 0;
    string szyfr_czy_deszyfr;
    char nazwa_pliku_do_odczytania[80], nazwa_pliku_do_zapisania[80];
    fstream plik_do_wczytywania;
    fstream plik_do_zapisu;
    int licznik = 0;
    string* tablica = new string[licznik];
    srand(time(NULL));
    cout << "wybierz metode szyfrowania: 1-szyfr cezara 2-szyfr vigenere " << endl;
    cin >> metoda_szyfrowania;
    system("cls");
    cout << "wybierz dzialanie programu (s - szyfrowanie, d - deszyfrowanie)" << endl;
    cin >> szyfr_czy_deszyfr;
    system("cls");
    cout << "podaj nazwe pliku do wczytania" << endl;
    cin >> nazwa_pliku_do_odczytania;
    system("cls");
    cout << "podaj nazwe pliku do zapisania" << endl;
    cin >> nazwa_pliku_do_zapisania;
    system("cls");

    plik_do_wczytywania.open(nazwa_pliku_do_odczytania, ios::in);
    plik_do_zapisu.open(nazwa_pliku_do_zapisania, ios::out);

    if (plik_do_wczytywania.good() == false)
    {
        cout << "taki plik nie istnieje.";
        exit(0);
    }
    int klucz;
    int licz_slowo=0;
    string slowo;
    if (metoda_szyfrowania==1)
    {
        cout << "podaj klucz szyfrowania (liczba)" << endl;
        cin >> klucz;
    }
    if (metoda_szyfrowania==2)
    {
        cout << "podaj klucz szyfrowania (slowo)" << endl;
        cin >> slowo;
    }

    system("cls");

    string linia;
    string tekstjawny;
    char znak;
    bool warunek = false;
    while (getline(plik_do_wczytywania, linia)) {
        for (int i = 0; i < linia.length(); i++) {
            if (szyfr_czy_deszyfr == "s")
            {
                if (metoda_szyfrowania == 1)
                    znak = cezar_szyfr(linia[i], klucz);
                else if (metoda_szyfrowania == 2)
                    if ((int(linia[i])>64 && int(linia[i])<91) || (int(linia[i])>96 && int(linia[i])<123))
                    {
                        tekstjawny[i]=linia[i];
                        linia[i]=slowo[licz_slowo];
                        licz_slowo+=1;
                        if(licz_slowo==slowo.length())
                        {
                            licz_slowo=0;
                        }
                        znak = vigenere_szyfr(tekstjawny[i],linia[i]);
                    }
                    else
                    {
                        znak=linia[i];
                    }
                plik_do_zapisu << znak;
            }
            if (szyfr_czy_deszyfr == "d")
            {
                if (metoda_szyfrowania == 1)
                    znak = cezar_de_szyfr(linia[i], klucz);
                else if (metoda_szyfrowania == 2)
                    if ((int(linia[i])>64 && int(linia[i])<91) || (int(linia[i])>96 && int(linia[i])<123))
                    {
                        tekstjawny[i]=linia[i];
                        linia[i]=slowo[licz_slowo];
                        licz_slowo+=1;
                        if(licz_slowo==slowo.length())
                        {
                            licz_slowo=0;
                        }
                        znak = vigenere_de_szyfr(tekstjawny[i],linia[i]);
                    }
                    else
                    {
                        znak=linia[i];
                    }
                plik_do_zapisu << znak;
            }
        }
        plik_do_zapisu << endl;
    }

    plik_do_wczytywania.close();
    plik_do_zapisu.close();

    plik_do_zapisu.open(nazwa_pliku_do_zapisania, ios::in);


    int aktualna_strona = 0;
    int ostatnia_strona = 0;
    int rozmiar_strony = 5;
    int poprzedniplik = 0;
    do
    {
        cout <<"ktory plik chcesz otworzyc? 1-poczatkowy, 2-koncowy 3-wyjdz"<<endl;
        cin>>ktoryplik;
        system("cls");
        if (poprzedniplik == ktoryplik)
        {
            aktualna_strona = ostatnia_strona;
        }

        if (plik_do_wczytywania.is_open())
        {
            plik_do_wczytywania.close();
        }

        if (ktoryplik==1)
        {
            plik_do_wczytywania.open(nazwa_pliku_do_odczytania, ios::in);
        }

        if (ktoryplik==2)
        {
            plik_do_wczytywania.open(nazwa_pliku_do_zapisania, ios::in);
        }

        if (ktoryplik==3) {
            break;
        }

        plik_do_wczytywania.seekg(aktualna_strona);

        for (int i = 0; i < rozmiar_strony; i++)
        {
            getline(plik_do_wczytywania, linia);
            cout << linia << endl;
        }
        ostatnia_strona = plik_do_wczytywania.tellg();

        if (plik_do_wczytywania.eof())
        {
            cout << "plik sie skonczyl" << endl;
        }
        linia=" ";
        poprzedniplik = ktoryplik;
    }
    while(warunek==false);

    plik_do_zapisu.close();

    return 0;
}
