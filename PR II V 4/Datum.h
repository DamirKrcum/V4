#pragma once
#include <iostream>
#include "funkcije.h"

using namespace std;

class Datum
{
private:
	int* _dan;
	int* _mjesec;
	int* _godina;
public:
	//Z1.1 :: Dflt. ctor 
	Datum() {
		_dan = nullptr;
		_mjesec = nullptr;
		_godina = nullptr;
	}

	//Z1.2 :: User-def. ctor
	Datum(int d, int m, int g) {
		_dan = new int(d);
		_mjesec = new int(m);
		_godina = new int(g);
	}

	//Z1.3 :: Copy ctor
	Datum(const Datum& obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}

	//Z1.4 :: Move ctor
	Datum(Datum&& obj) {
		_dan = obj._dan;
		obj._dan = nullptr;
		_mjesec = obj._mjesec;
		obj._mjesec = nullptr;
		_godina = obj._godina;
		obj._godina = nullptr;
	}

	//Z1.5 :: Operator = 
	Datum& operator =(const Datum& obj) {
		if (this == &obj)
			return *this;
		delete _dan;
		delete _mjesec;
		delete _godina;
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
		return *this;
	}

	//Z1.6 :: Getteri
	int GetDan() const { return *_dan; }
	int GetMjesec() const { return *_mjesec; }
	int GetGodina() const { return *_godina; }

	//Z1.7 :: Setteri
	void SetDan(int dan) {
		delete _dan;
		_dan = new int(dan);
	}
	void SetMjesec(int mjesec) {
		delete _mjesec;
		_mjesec = new int(mjesec);
	}
	void SetGodina(int godina) {
		delete _godina;
		_godina = new int(godina);
	}
	//Z1.8 :: dtor
	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}
	friend ostream& operator << (ostream& COUT, const Datum obj);
	friend bool operator == (const Datum& d1, const Datum& d2);
	friend Datum operator + (Datum& obj, int brojDana);
	friend int datumUInt(const Datum& obj);
};

int datumUInt(const Datum& obj) {
	int temp = *obj._dan + (*obj._mjesec * 30) + (*obj._godina * 365);
	return temp;
}

//Z1.9 :: Ispisati datum
ostream& operator << (ostream& COUT, const Datum obj) {
	COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
	return COUT;
}

//Z1.10 :: Porediti dva datuma po vrijednostima atributa
bool operator == (const Datum& d1, const Datum& d2) {
	return datumUInt(d1) == datumUInt(d2);
}

bool operator != (const Datum& d1, const Datum& d2) {
	return !(d1 == d2);
}

//Z1.11 :: Kreirati novi datum kao rezultat dodavanja varijable 'brojDana' na objekat 'obj'
Datum operator + (Datum& obj, int brojDana) {
	int dan = *obj._dan, mjesec = *obj._mjesec, godina = *obj._godina;
	for (int i = 0; i < brojDana; i++) {
		if (dan + 1 <= GetBrojDanaUMjesecu(mjesec, godina))
			dan++;
		else {
			dan = 1;
			if (mjesec + 1 <= 12)
				mjesec++;
			else {
				mjesec = 1;
				godina++;
			}
		}
	}
	return Datum(dan, mjesec, godina);
}



//Z1.12 :: Provjeriti da li je 'd1' veci (noviji datum) od 'd2'
bool operator > (const Datum& d1, const Datum& d2) {
	return datumUInt(d1) > datumUInt(d2);
}

bool operator >= (const Datum& d1, const Datum& d2) {
	return d1 > d2 || d1 == d2;
}

bool operator <(const Datum& d1, const Datum& d2) {
	return d1 >= d2;
}

bool operator <=(const Datum& d1, const Datum& d2) {
	return d1 > d2;
}

//Z1.13 Izracunati razliku (u danima) izmedju objekata 'd1' i 'd2'
int operator -(Datum& d1, Datum& d2) {
	int razlika = 0;
	if (d1 == d2)
		return razlika;
	else
	{
		if (d1 > d2) {

			razlika = datumUInt(d1) - datumUInt(d2);
		}
		else {

			razlika = datumUInt(d2) - datumUInt(d1);

		}
		return razlika;
	}



}