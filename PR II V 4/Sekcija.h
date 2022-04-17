#pragma once
#include<iostream>
#include"Post.h"

class Sekcija {
	char* _naziv;
	char* _kratakOpis;
	int _trenutnoPostova;
	Post* _postovi[maxBrojPostova] = { nullptr };
public:
	//Z4.1 :: Dflt. ctor
	Sekcija() {
		_naziv = nullptr;
		_kratakOpis = nullptr;
		_trenutnoPostova = 0;

	}

	//Z4.2 :: User-def. ctor
	Sekcija(const char* naziv, const char* kratakOpis) {
		_naziv = AlocirajIKopiraj(naziv);
		_kratakOpis = AlocirajIKopiraj(kratakOpis);
		_trenutnoPostova = 0;

	}

	//Z4.3 :: Copy ctor
	Sekcija(const Sekcija& obj) {
		_naziv = AlocirajIKopiraj(obj._naziv);
		_kratakOpis = AlocirajIKopiraj(obj._kratakOpis);
		_trenutnoPostova = obj._trenutnoPostova;
		for (int i = 0; i < _trenutnoPostova; i++)
		{
			_postovi[i] = new Post(*obj._postovi[i]);
		}
	}

	//Z4.4 :: Move ctor
	Sekcija(Sekcija&& obj) {
		_naziv = obj._naziv;
		obj._naziv = nullptr;
		_kratakOpis = obj._kratakOpis;
		obj._kratakOpis = nullptr;
		_trenutnoPostova = obj._trenutnoPostova;
		for (int i = 0; i < _trenutnoPostova; i++)
		{
			_postovi[i] = obj._postovi[i];
			obj._postovi[i] = nullptr;
		}
		obj._trenutnoPostova = 0;

	}

	//Z4.5 :: operator dodjele
	Sekcija& operator = (const Sekcija& obj) {
		if (this == &obj)
			return *this;
		delete[] _naziv;
		delete[] _kratakOpis;
		for (int i = 0; i < _trenutnoPostova; i++)
		{
			delete _postovi[i];
			_postovi[i] = nullptr;
		}
		_naziv = AlocirajIKopiraj(obj._naziv);
		_kratakOpis = AlocirajIKopiraj(obj._kratakOpis);
		_trenutnoPostova = obj._trenutnoPostova;
		for (int i = 0; i < _trenutnoPostova; i++)
		{
			_postovi[i] = new Post(*obj._postovi[i]);
		}
		return *this;
	}

	//Z4.6 :: Getteri
	char* GetNaziv() const { return _naziv; }
	char* GetKratakOpis() const { return _kratakOpis; }
	Post GetPostAtI(int index) const {
		index = Min(index, _trenutnoPostova + 1);
		index = Max(index, 0);
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
		if (_trenutnoPostova == maxBrojPostova)
			return false;
		_postovi[_trenutnoPostova++] = new Post(p);
		return true;
	}

	//Z4.9 :: dtor
	~Sekcija() {
		delete[] _naziv; _naziv = nullptr;
		delete[] _kratakOpis; _kratakOpis = nullptr;
		for (int i = 0; i < _trenutnoPostova; i++)
		{
			delete _postovi[i];
			_postovi[i] = nullptr;
		}
	}
	friend ostream& operator << (ostream& COUT, const Sekcija& obj);
};
//Z4.10 :: Ispisati podatke o sekciji [ukljucujuci i postove]
ostream& operator << (ostream& COUT, const Sekcija& obj) {
	COUT << "Naziv: " << obj._naziv << endl;
	COUT << "Kratak opis: " << obj._kratakOpis << endl;
	COUT << "Postovi: " << endl;
	for (int i = 0; i < obj._trenutnoPostova; i++)
	{
		COUT << *obj._postovi[i] << endl;
	}
	return COUT;
}

const int maxBrojSekcija = 20;