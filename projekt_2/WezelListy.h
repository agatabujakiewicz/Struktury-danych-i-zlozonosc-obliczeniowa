#pragma once
#include <stdio.h> 

struct WezelListy
{
public:
	WezelListy();
	int wierzcholek_docelowy;
	int waga;
	WezelListy *nastepny;
	~WezelListy();
};
