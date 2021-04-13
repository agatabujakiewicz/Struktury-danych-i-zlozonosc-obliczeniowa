#pragma once
#include "ListaSasiedztwa.h"
#include "WezelListy.h"
#include <iostream>
#include <stdio.h> 
#include <vector>
#include <string>

class GrafLista
{
public:
	GrafLista();
	~GrafLista();
	GrafLista(int ilosc_wierzcholkow, bool czy_skierowany); // false = nieskierowany, true = skierowany
	int V; //ilosc wierzcholkow
	int E; //ilosc krawedzi
	ListaSasiedztwa *TablicaSkierowana;
	ListaSasiedztwa *TablicaNieskierowana;
	WezelListy *UtworzWezel(int wierzcholek_docelowy_, int waga_);
	void DodajKrawedz (struct Krawedz e, bool czy_skierowana);
	void WypiszListe(bool czy_skierowana);
	void LosujGraf(int V, float Gestosc, bool czy_skierowany);
	void ZapiszDoPliku(bool czy_skierowana);
	void ZapiszDoPliku(std::string, bool czy_skierowana);
	void WczytajZPliku(bool czy_skierowana);

};

struct Krawedz
{
public:
	Krawedz(int wierzcholek_poczatkowy, int wierzcholek_koncowy, int waga);
	Krawedz();
	~Krawedz();
	Krawedz(int n);
	int wierzcholek_poczatkowy;
	int wierzcholek_koncowy;
	int waga;

};

class Kolejka
{
  private:
    Krawedz *kopiec;
    int pozycja_w_kopcu;
  public:
    Kolejka(int n);
    ~Kolejka();
    Krawedz poczatek();
    void odloz(Krawedz e);
    void sciagnij();
};

class MST : public GrafLista
{
	public:
		MST (int ilosc_wierzcholkow);
		~MST();
		int rozmiar;
		int waga_drzewa;
		std::vector<ListaSasiedztwa> TablicaDrzewa;
		void DodajKrawedz(Krawedz e);
		void TworzMSTPrim(GrafLista Graf);
		void WypiszListe();
		WezelListy* ZwrocPoczatekListySasiadow(int n);

};

class Dijkstra : GrafLista
{
	public:
		Dijkstra(int ilosc_wierzcholkow);
		~Dijkstra();
		void SzukajSciezkiDijkstra(int poczatek, int koniec, GrafLista Graf);
		void WypiszSciezke();
		int stos_ptr, *dojscie, *poprzednicy, *Stos, ilosc_wierzcholkow;
		bool *QS;


};