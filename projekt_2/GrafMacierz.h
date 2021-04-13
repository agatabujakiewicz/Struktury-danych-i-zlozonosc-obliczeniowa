#pragma once
#include "ListaSasiedztwa.h"
#include "GrafLista.h"
#include "WezelListy.h"
#include <iostream>
#include <stdio.h> 
#include <vector>
#include <string>

class GrafMacierz
{
	public:
	GrafMacierz();
	GrafMacierz(int ilosc_wierzcholkow, bool czy_skierowany); // false = nieskierowany, true = skierowany
	int V_M; //ilosc wierzcholkow
	int E_M; //ilosc krawedzi
	std::vector<std::vector<int>> Macierz;
	std::vector<std::vector<int>> MacierzWag;

	WezelListy *UtworzWezel(int wierzcholek_docelowy_, int waga_);
	void DodajKrawedz(int poczatek, int koniec, int waga, bool czy_skierowana);
	void WypiszMacierz();
	void LosujGraf(int V, float Gestosc, bool czy_skierowany);
	void ZapiszDoPliku();
	void WczytajZPliku(std::string Filename, bool czy_skierowana);

};

class MST_M : public GrafMacierz
{
	public:
		MST_M(int ilosc_wierzcholkow);
		~MST_M();
		int rozmiar;
		int waga_drzewa;
		std::vector<ListaSasiedztwa> TablicaDrzewa;
		void TworzMSTPrim(GrafMacierz Graf);
		void DodajKrawedz(Krawedz e);
		void WypiszListe();

};

class Dijkstra_M : public GrafMacierz
{
	public:
		Dijkstra_M(int ilosc_wierzcholkow);
		~Dijkstra_M();
		void SzukajSciezkiDijkstra(int poczatek, int koniec, GrafMacierz Graf);
		void WypiszSciezke();
		int stos_ptr,*dojscie,*poprzednicy, *Stos, ilosc_wierzcholkow;
		bool *QS;

};

