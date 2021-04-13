#include "StdAfx.h"
#include "GrafLista.h"
#include "GrafMacierz.h"
#include "ListaSasiedztwa.h"
#include "WezelListy.h"
#include <iostream>
#include <stdio.h> 

using namespace std;

MST::MST(int ilosc_wierzcholkow)
{
	V = ilosc_wierzcholkow;

	TablicaDrzewa.resize(V);
	for (int i = 0; i<V; i++)
	{
		TablicaDrzewa[i].glowa = NULL;
	}

	waga_drzewa = 0;
	rozmiar = V - 1;	

}

MST::~MST()
{

}

MST_M::~MST_M()
{

}

MST_M::MST_M(int ilosc_wierzcholkow)
{
	V_M = ilosc_wierzcholkow;

	TablicaDrzewa.resize(V_M);
	for (int i = 0; i<V_M; i++)
	{
		TablicaDrzewa[i].glowa = NULL;
	}

	waga_drzewa = 0;
	rozmiar = V_M - 1;

}

void MST::DodajKrawedz(Krawedz e)
{
	waga_drzewa+=e.waga;
	WezelListy *nowy = UtworzWezel(e.wierzcholek_koncowy, e.waga);
	WezelListy *nowy2 = UtworzWezel(e.wierzcholek_poczatkowy, e.waga);

	nowy->nastepny = TablicaDrzewa[e.wierzcholek_poczatkowy].glowa;
	TablicaDrzewa[e.wierzcholek_poczatkowy].glowa = nowy;

	nowy2->nastepny = TablicaDrzewa[e.wierzcholek_koncowy].glowa;
	TablicaDrzewa[e.wierzcholek_koncowy].glowa = nowy2;

}

void MST_M::DodajKrawedz(Krawedz e)
{
	waga_drzewa+=e.waga;
	WezelListy *nowy = UtworzWezel(e.wierzcholek_koncowy, e.waga);
	WezelListy *nowy2 = UtworzWezel(e.wierzcholek_poczatkowy, e.waga);

	nowy->nastepny = TablicaDrzewa[e.wierzcholek_poczatkowy].glowa;
	TablicaDrzewa[e.wierzcholek_poczatkowy].glowa = nowy;

	nowy2->nastepny = TablicaDrzewa[e.wierzcholek_koncowy].glowa;
	TablicaDrzewa[e.wierzcholek_koncowy].glowa = nowy2;


}

void MST::TworzMSTPrim(GrafLista Graf)
{

	int V = Graf.V; 
	int E = V*V;
	waga_drzewa = 0;
	int* odwiedzone;
	odwiedzone = new int[V];
	for(int i = 0; i < V; i++)
	{
		odwiedzone[i] = 0;
	}

	WezelListy* temp;
	int v = 0;
	odwiedzone[v] = 1;
	Kolejka kolejka(E);
	Krawedz e;
	for(int i = 1; i < V; i++)          
	{
		for(temp = Graf.TablicaNieskierowana[v].glowa; temp; temp = temp->nastepny) 
			if(odwiedzone[temp->wierzcholek_docelowy] == 0)         
			{
				e.wierzcholek_poczatkowy = v;
				e.wierzcholek_koncowy = temp->wierzcholek_docelowy;
				e.waga = temp->waga;
				kolejka.odloz(e);               
			}
			
			do
			{
				e = kolejka.poczatek();              
				kolejka.sciagnij();
			} while(odwiedzone[e.wierzcholek_koncowy] == 1);     
			DodajKrawedz(e);                 
			odwiedzone[e.wierzcholek_koncowy] = 1;        
			v = e.wierzcholek_koncowy;
		
	}
	delete odwiedzone;
}

void MST_M::TworzMSTPrim(GrafMacierz Graf)
{

	int V = Graf.V_M; 
	int E = V*V;
	int* odwiedzone;
	waga_drzewa = 0;
	odwiedzone = new int[V];
	for(int i = 0; i < V; i++)
	{
		odwiedzone[i] = 0;
	}

	int v = 0;
	odwiedzone[v] = 1;
	Kolejka kolejka(E);
	Krawedz e;
	for(int i = 1; i < V; i++)          
	{
		for(int u = 0; u < V; u++) 
			if(Graf.Macierz[v][u] == 1 && odwiedzone[u] == 0)         
			{ //cout <<"wszedl w ifa"<<endl;
				e.wierzcholek_poczatkowy = v;
				e.wierzcholek_koncowy = u;
				e.waga = Graf.MacierzWag[u][v];
				kolejka.odloz(e);               
			}
			
			do
			{
				e = kolejka.poczatek();              
				kolejka.sciagnij();
				//cout <<"jestem we while"<<endl;
			} while(odwiedzone[e.wierzcholek_koncowy] == 1);     
			DodajKrawedz(e);                 
			odwiedzone[e.wierzcholek_koncowy] = 1;        
			v = e.wierzcholek_koncowy;
		
	}

	delete odwiedzone;
}


void MST::WypiszListe()
{
	WezelListy *temp;
	for (int i = 0; i<=rozmiar; i++)
	{
		cout <<"Numer wierzcholka: "<<i<<" to "<<endl;
		temp = TablicaDrzewa[i].glowa;
		while (temp != NULL)
		{
			cout <<"Cel: " <<temp->wierzcholek_docelowy<<" Waga: "<<temp->waga<<" "<<endl;
			temp = temp->nastepny;
		}
		
	}
	cout <<"Waga MST to: "<<waga_drzewa<<endl;

}

void MST_M::WypiszListe()
{
	WezelListy *temp;
	for (int i = 0; i<=rozmiar; i++)
	{
		cout <<"Numer wierzcholka: "<<i<<" to "<<endl;
		temp = TablicaDrzewa[i].glowa;
		while (temp != NULL)
		{
			cout <<"Cel: " <<temp->wierzcholek_docelowy<<" Waga: "<<temp->waga<<" "<<endl;
			temp = temp->nastepny;
		}
		
	}
	cout <<"Waga MST to: "<<waga_drzewa<<endl;

}

Kolejka::Kolejka(int n)
{
	kopiec = new Krawedz[n];            
	pozycja_w_kopcu = 0;                       
}


Kolejka::~Kolejka()
{
	delete [] kopiec;
}


Krawedz Kolejka::poczatek()
{
	return kopiec[0];
}


void Kolejka::odloz(Krawedz e)
{
	int i,j;

	i = pozycja_w_kopcu++;                
	j = (i - 1) >> 1;              

	while(i && (kopiec[j].waga > e.waga))
	{
		kopiec[i] = kopiec[j];
		i = j;
		j = (i - 1) >> 1;
	}

	kopiec[i] = e;                    
}


void Kolejka::sciagnij()
{
	int i,j;
	Krawedz e;

	if(pozycja_w_kopcu)
	{
		e = kopiec[--pozycja_w_kopcu];

		i = 0;
		j = 1;

		while(j < pozycja_w_kopcu)
		{
			if((j + 1 < pozycja_w_kopcu) && (kopiec[j + 1].waga < kopiec[j].waga)) j++;
			if(e.waga <= kopiec[j].waga) break;
			kopiec[i] = kopiec[j];
			i = j;
			j = (j << 1) + 1;
		}

		kopiec[i] = e;
	}
}

