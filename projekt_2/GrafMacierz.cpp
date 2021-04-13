#include "StdAfx.h"
#include "GrafMacierz.h"
#include <iostream>
#include <stdio.h> 
#include <fstream>

using namespace std;

GrafMacierz::GrafMacierz()
{
	
}

GrafMacierz::GrafMacierz(int ilosc_wierzcholkow, bool czy_skierowany)
{
	V_M = ilosc_wierzcholkow;

	std::vector< std::vector<int> > matrix(V_M, std::vector<int>(V_M));
	Macierz = matrix;
	MacierzWag = matrix;
}

void GrafMacierz::WypiszMacierz()
{
   cout <<"Wyswietlam macierz sasiedztwa o wymiarach "<<V_M<<" x " <<V_M<<endl;
   cout <<endl;
	for(int j = 0; j<V_M; j++)
        {
            for(int k = 0; k<V_M; k++)
            {
                cout<<Macierz[j][k]<<" ";
            }
            cout<<endl;
        }
  cout <<endl;
	cout <<"Wyswietlam macierz wag o wymiarach "<<V_M<<" x " <<V_M<<endl;
	  cout <<endl;
	for(int j = 0; j<V_M; j++)
        {
            for(int k = 0; k<V_M; k++)
            {
                cout<<MacierzWag[j][k]<<" ";
            }
            cout<<endl;
        }

}

void GrafMacierz::DodajKrawedz(int poczatek, int koniec, int waga, bool czy_skierowana)
{
	Macierz [koniec][poczatek] = 1;
	MacierzWag [koniec][poczatek] = waga;
	
	if (!czy_skierowana)
	{
	Macierz [poczatek][koniec] = 1;
	MacierzWag [poczatek][koniec] = waga;
	}
}

void GrafMacierz::LosujGraf(int V, float Gestosc, bool czy_skierowany)
{
	
	if (!czy_skierowany) Gestosc = Gestosc/2;
	E_M = (int) (V_M*(V_M-1) * Gestosc); //ilosc maksymalnych krawedzi w grafie, przyjalem grafy bez petli
	int E_wygenerowane = 0;

	for (int i = 0; i<V-1; i++) //pierwsza petla tworzy graf, gdzie kazdy wierzcholek jest polaczony z nastepnym, a ostatni z pierwszym, taki graf musi byc spojny, zatem spojnosc jest zapewniona
		{
			//cout <<"Dodaje podstawowe krawedzie"<<endl;
			//cout <<i<<endl;
			DodajKrawedz(i, i+1, rand()%10+1, czy_skierowany);
			E_wygenerowane++;	
		}
		bool zawiera = false;
		int E_pozostale = E_M - E_wygenerowane;
		int dodano = 0;

		int w1 = 0; 
		int w2 = 0;

		for (int i = 0; i<E_pozostale; i++) //ta petla generuje losowo pozostale krawedzie, w zaleznosci od zadanej gestosci
		{	
			
			do
			{
			w1 = rand()%V_M;
			w2 = rand()%V_M;
			} while (w1 == w2);
			
				if (Macierz[w1][w2] == 1)
				{
					zawiera = true;
					E_pozostale++;
				}
		
			 
			if (!zawiera)
			{
				DodajKrawedz(w1, w2, rand()%10+1, czy_skierowany);
				//cout <<"Dodaje pozostale krawedzie, wierzcholek: "<<w1<<endl;
				//cout <<"Dodano juz: "<<dodano<<" krawedzi."<<endl;
				dodano++;
			}
			zawiera = false;
	
		}

}

WezelListy* GrafMacierz::UtworzWezel(int wierzcholek_docelowy_, int waga_)
{
	WezelListy *nowy = new WezelListy();
	nowy->wierzcholek_docelowy = wierzcholek_docelowy_;
	nowy->waga = waga_;
	return nowy;

}

void GrafMacierz::ZapiszDoPliku()
{
	ofstream plik("GrafMacierz.txt");   
	plik << E_M <<" "<<V_M<<endl;
 
		int j = 0;
		for (int i = 0; i<V_M; i++)
		{
			for (int g = 0; g<V_M; g++)
			{
				
				if (Macierz[g][i] == 1)
				{
					plik <<i<<" ";
					plik <<g<<" ";
					plik <<MacierzWag[g][i]<<endl;
				}

			}
			
	
		}


}

void GrafMacierz::WczytajZPliku(string Filename, bool czy_skierowana)
{

	ifstream plik(Filename.c_str());
	int V_temp, E_temp;
	plik >> E_temp >> V_temp;
	GrafMacierz temp(V_temp, czy_skierowana);

 
    if (!plik)
    {
        cout << "Nie mozna otworzyc pliku"<<endl;
    }
	
	else
	{
	int i = 0;
	int j = 0;
	int g,f = 0;
    while (!plik.eof())
	{
	
		while (i==j && !plik.eof())
		{
			plik >>i;
			plik >>g;
			plik >>f;
			temp.DodajKrawedz(i, g, f, czy_skierowana);
			 
		} j++;
		
	}

	Macierz = temp.Macierz;
	MacierzWag = temp.MacierzWag;
	V_M = temp.V_M;
	E_M = E_temp;
	cout <<"Zbudowano graf z pliku txt"<<endl;
	}
	plik.close();

}
