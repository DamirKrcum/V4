#pragma once
#include<iostream>
#include"Post.h"
#include "Kolekcija.h"

class Sekcija {
	char* _naziv;
	char* _kratakOpis;
	
	Kolekcija<Post*> _postovi;
public:
	//Z4.1 :: Dflt. ctor
	Sekcija() {
		_naziv = nullptr;
		_kratakOpis = nullptr;
	}

	//Z4.2 :: User-def. ctor
	Sekcija(const char* naziv, const char* kratakOpis) {
		_naziv = AlocirajIKopiraj(naziv);
		_kratakOpis = AlocirajIKopiraj(kratakOpis);		
	}

	//Z4.3 :: Copy ctor
	Sekcija(const Sekcija& obj) {
		_naziv = AlocirajIKopiraj(obj._naziv);
		_kratakOpis = AlocirajIKopiraj(obj._kratakOpis);
		_postovi = obj._postovi;
	}

	//Z4.4 :: Move ctor
	Sekcija(Sekcija&& obj) {
		_naziv = obj._naziv;
		obj._naziv = nullptr;
		_kratakOpis = obj._kratakOpis;
		obj._kratakOpis = nullptr;
		
		_postovi = obj._postovi;
		obj._postovi.UkloniSve();
	}

	//Z4.5 :: operator dodjele
	Sekcija& operator = (const Sekcija& obj) {
		if (this == &obj)
			return *this;
		delete[] _naziv;
		delete[] _kratakOpis;
		_postovi.UkloniSve();
		_naziv = AlocirajIKopiraj(obj._naziv);
		_kratakOpis = AlocirajIKopiraj(obj._kratakOpis);
		_postovi = obj._postovi;
		return *this;
	}

	//Z4.6 :: Getteri
	char* GetNaziv() const { return _naziv; }
	char* GetKratakOpis() const { return _kratakOpis; }
	Post GetPostAtI(int index) const {
		 return *_postovi[index];
	}

	//Z4.7 :: Setteri
	void SetNaziv(const char* naziv) {
		delete[] _naziv;
		_naziv = AlocirajIKopiraj(naziv);
	}
	void SetKratakOpis(const char* kratakOpis) {
		delete[] _kratakOpis;
		_kratakOpis = AlocirajIKopiraj(kratakOpis);
	}

	//Z4.8 :: operator +=  
	//Dodati novi post u niz pokazivaca
	//Onemoguciti dodavanje u slucaju da je popunjen niz pokazivaca
	bool operator +=(Post& p) {		
		_postovi += new Post(p);
		return true;
	}

	//Z4.9 :: dtor
	~Sekcija() {
		delete[] _naziv; _naziv = nullptr;
		delete[] _kratakOpis; _kratakOpis = nullptr;
	}
	friend ostream& operator << (ostream& COUT, const Sekcija& obj);
};
//Z4.10 :: Ispisati podatke o sekciji [ukljucujuci i postove]
ostream& operator << (ostream& COUT, const Sekcija& obj) {
	COUT << "Naziv: " << obj._naziv << endl;
	COUT << "Kratak opis: " << obj._kratakOpis << endl;
	COUT << "Postovi: " << endl;
	for (int i = 0; i < obj._postovi.GetBrojac(); i++)
	{
		COUT << *obj._postovi[i] << endl;
	}
	return COUT;
}

const int maxBrojSekcija = 20;