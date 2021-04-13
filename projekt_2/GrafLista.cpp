#include "StdAfx.h"
#include "GrafLista.h"
#include "ListaSasiedztwa.h"
#include "WezelListy.h"
#include <iostream>
#include <fstream>
#include <stdio.h> 

using namespace std;

GrafLista::GrafLista()
{
}

GrafLista::~GrafLista()
{
	//cout <<"Zadzialal destruktor grafu na liscie"<<endl;
}

Krawedz::Krawedz()
{
wierzcholek_poczatkowy = 0;
wierzcholek_koncowy = 0;
waga = 0;
}

Krawedz::~Krawedz()
{
	//cout <<"Zadzialal destruktor krawedzi"<<endl;

}

Krawedz::Krawedz(int wierzcholek_poczatkowy_, int wierzcholek_koncowy_, int waga_)
{
wierzcholek_poczatkowy = wierzcholek_poczatkowy_;
wierzcholek_koncowy = wierzcholek_koncowy_;
waga = waga_;

}


GrafLista::GrafLista(int ilosc_wierzcholkow, bool czy_skierowany)
{
	V = ilosc_wierzcholkow;
	if(czy_skierowany)
	{
		TablicaSkierowana = new ListaSasiedztwa[V];
		for (int i = 0; i<V; i++)
		{
			TablicaSkierowana[i].glowa = NULL;
		}

	}
	else if(!czy_skierowany)
	{
		TablicaNieskierowana = new ListaSasiedztwa[V];
		for (int i = 0; i<V; i++)
		{
			TablicaNieskierowana[i].glowa = NULL;
		}

	}

}

WezelListy* GrafLista::UtworzWezel(int wierzcholek_docelowy_, int waga_)
{
	WezelListy *nowy = new WezelListy();
	nowy->wierzcholek_docelowy = wierzcholek_docelowy_;
	nowy->waga = waga_;
	return nowy;

}

void GrafLista::DodajKrawedz(Krawedz e, bool czy_skierowana)
{
	if (!czy_skierowana) //w przypadku grafu nieskierowanego, tworzone sa krawedzie "podwojnie skierowane"
	{					
		WezelListy *nowy = UtworzWezel(e.wierzcholek_koncowy, e.waga);
		WezelListy *nowy2 = UtworzWezel(e.wierzcholek_poczatkowy, e.waga);
		
		nowy->nastepny = TablicaNieskierowana[e.wierzcholek_poczatkowy].glowa;
		TablicaNieskierowana[e.wierzcholek_poczatkowy].glowa = nowy;
		
		nowy2->nastepny = TablicaNieskierowana[e.wierzcholek_koncowy].glowa;
		TablicaNieskierowana[e.wierzcholek_koncowy].glowa = nowy2;
	}
	
	else if (czy_skierowana)
	{
		WezelListy *nowy = UtworzWezel(e.wierzcholek_koncowy, e.waga);

		nowy->nastepny = TablicaSkierowana[e.wierzcholek_poczatkowy].glowa;
		TablicaSkierowana[e.wierzcholek_poczatkowy].glowa = nowy;

	}


}


void GrafLista::WypiszListe(bool czy_skierowana)
{
	if (!czy_skierowana)
	{
		int j = 0;
		for (int i = 0; i<V; i++)
		{
			WezelListy *temp = TablicaNieskierowana[i].glowa;
			cout <<"W: "<<i<<" ";
			j = 0;
			while (temp != NULL)
			{
				//cout <<"Krawedz o numerze: "<<j<<" ";
				cout <<"Cel: "<< temp->wierzcholek_docelowy <<" "; 
				cout <<"Waga: "<< temp->waga<<" ";
				temp = temp->nastepny;
				j++;
			} cout<<endl;
		}
	}
	else if (czy_skierowana)
	{
		int j = 0;
		for (int i = 0; i<V; i++)
		{
			WezelListy *temp = TablicaSkierowana[i].glowa;
			cout <<"W: "<<i<<" ";
			j = 0;
			while (temp != NULL)
			{
				//cout <<"Krawedz o numerze: "<<j<<" ";
				cout <<"Cel: "<< temp->wierzcholek_docelowy <<" "; 
				cout <<"Waga: "<< temp->waga<<" ";
				temp = temp->nastepny;
				j++;
			} cout<<endl;
		}
	}
}

void GrafLista::LosujGraf(int V, float Gestosc, bool czy_skierowany)
{
	
	GrafLista temp(V, czy_skierowany);
	if (!czy_skierowany) Gestosc = Gestosc / 2;
	temp.E = (int) (V*(V-1) * Gestosc); //ilosc maksymalnych krawedzi w grafie, przyjalem grafy bez petli
	int E_wygenerowane = 0;

	for (int i = 0; i<V; i++) //pierwsza petla tworzy graf, gdzie kazdy wierzcholek jest polaczony z nastepnym, a ostatni z pierwszym, taki graf musi byc spojny, zatem spojnosc jest zapewniona
		{
			//cout <<"Dodaje podstawowe krawedzie"<<endl;
			E_wygenerowane++;
			if (i == V-1) 
			{	
				Krawedz e(i, 0, rand()%10+1);
				temp.DodajKrawedz(e, czy_skierowany); 
				break;
			}
			Krawedz e(i, i+1, rand()%10+1);
			temp.DodajKrawedz(e, czy_skierowany);
				
		}
		bool zawiera = false;
		int E_pozostale = temp.E - E_wygenerowane;
		int dodano = 0;

		for (int i = 0; i<E_pozostale; i++) //ta petla generuje losowo pozostale krawedzie, w zaleznosci od zadanej gestosci
		{	
			int w1 = 0; 
			int w2 = 0;
			do
			{
			w1 = rand()%V;
			w2 = rand()%V;
			//cout << "Jestem w petli" << endl;
			} while (w1 == w2);
			
			WezelListy *temp2;
			if (czy_skierowany)
			temp2 = temp.TablicaSkierowana[w1].glowa;
			if (!czy_skierowany)
			temp2 = temp.TablicaNieskierowana[w1].glowa;

			for(temp2; temp2; temp2 = temp2->nastepny)
			{
				if (temp2->wierzcholek_docelowy == w2)
				{
					zawiera = true;
					E_pozostale++;
				}
				if (temp2->nastepny == NULL)
				{
					break;
				}
			} 
			if (!zawiera)
			{
				Krawedz e(w1, w2, 11+rand()%10+1);
				temp.DodajKrawedz(e, czy_skierowany);
				//cout <<"Dodaje pozostale krawedzie, wierzcholek: "<<w1<<endl;
				//cout <<"Dodano juz: "<<dodano<<" krawedzi."<<endl;
				dodano++;
			}
			zawiera = false;
	
		}
	if (!czy_skierowany)
		TablicaNieskierowana = temp.TablicaNieskierowana;
	if (czy_skierowany)
		TablicaSkierowana = temp.TablicaSkierowana;
	E = temp.E;
}

void GrafLista::ZapiszDoPliku(bool czy_skierowana)
{
	ofstream plik("GrafLista.txt");   
	plik << E <<" "<<V<<endl;
	WezelListy *temp;
		int j = 0;
		for (int i = 0; i<V; i++)
		{
			if (!czy_skierowana) temp = TablicaNieskierowana[i].glowa;
			if (czy_skierowana) temp = TablicaSkierowana[i].glowa;
			j = 0;
			while (temp != NULL)
			{
				//cout <<"Krawedz o numerze: "<<j<<" ";
				plik <<i<<" ";
				plik <<temp->wierzcholek_docelowy <<" "; 
				plik << temp->waga<<endl;
				temp = temp->nastepny;
				j++;
			} 
		}


}

void GrafLista::ZapiszDoPliku(string Filename, bool czy_skierowana)
{
	ofstream plik(Filename.c_str());
	plik << E << " " << V << endl;

	WezelListy *temp;
	int j = 0;
	for (int i = 0; i<V; i++)
	{
		if (!czy_skierowana) temp = TablicaNieskierowana[i].glowa;
		if (czy_skierowana) temp = TablicaSkierowana[i].glowa;

		
		j = 0;
		while (temp != NULL)
		{
			//cout <<"Krawedz o numerze: "<<j<<" ";
			plik << i << " ";
			plik << temp->wierzcholek_docelowy << " ";
			plik << temp->waga << endl;
			temp = temp->nastepny;
			j++;
		}
	}


}

void GrafLista::WczytajZPliku(bool czy_skierowana)
{

	ifstream plik("GrafLista.txt");
	int V_temp, E_temp;
	plik >> E_temp >> V_temp;
	GrafLista temp(V_temp, czy_skierowana);
	
 
    if (!plik)
    {
        cout << "Nie mozna otworzyc pliku"<<endl;
    }
	else
	{
	int i = 0;
	int j = 0;
	int test = 0;
	Krawedz e;
    while (!plik.eof())
	{
	
		while (i==j && !plik.eof())
		{
			plik >>i;
			e.wierzcholek_poczatkowy = i;
			plik >>e.wierzcholek_koncowy;
			plik >>e.waga;
			temp.DodajKrawedz(e, czy_skierowana);
			 
		} j++;
		
	}

	if (!czy_skierowana) TablicaNieskierowana = temp.TablicaNieskierowana;
	if (czy_skierowana) TablicaSkierowana = temp.TablicaSkierowana;
	V = temp.V;
	E = E_temp;
	cout <<"Zbudowano graf z pliku txt"<<endl;
	}
	plik.close();

}

