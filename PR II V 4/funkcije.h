#pragma once
#include <iostream>
using namespace std;

//Z0.1
char* AlocirajIKopiraj(const char* tekst) {
	if (tekst == nullptr)
		return nullptr;
	int vel = strlen(tekst) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, tekst);
	return temp;
}

int Min(int broj1, int broj2) { return (broj1 <= broj2) ? broj1 : broj2; }
int Max(int broj1, int broj2) { return (broj1 >= broj2) ? broj1 : broj2; }

//Z0.2 :: Vratiti broj znamenki za dati broj
int IzracunajBrojZnamenki(int broj) {
	int temp = 0;
	while (broj != 0)
	{
		broj = broj / 10;
		temp++;
	}
	return temp;
}

//Z0.3 :: Pretvoriti (int) u (char*). Obezbijediti da je 'broj' u opsegu [INT_MIN, INT_MAX]
char* IntToStr(int broj) {
	broj = Min(broj, INT_MAX);
	broj = Max(broj, INT_MIN);
	int vel = IzracunajBrojZnamenki(broj) + 1;
	char* temp = new char[vel];
	_itoa_s(broj, temp, vel, 10);
	return temp;
}

bool PrijestupnaGodina(int godina) {
	return (((godina % 4 == 0) && (godina % 100 != 0)) ||
		(godina % 400 == 0));
}

//Z0.4 :: Vratiti broj dana za dati mjesec (Voditi racuna o prijestupnim godinama)
int GetBrojDanaUMjesecu(int mjesec, int godina) {
	switch (mjesec) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 2:
		return PrijestupnaGodina(godina) ? 29 : 28;
	default:
		return 30;
	}
}

