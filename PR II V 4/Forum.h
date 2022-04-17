#pragma once
#include"Sekcija.h"
#include"clan.h"
class Forum {
	char* _naziv;
	int _trenutnoSekcija;
	Sekcija _sekcije[maxBrojSekcija];
	int _maxClanova;
	Clan* _clanovi;
	int _trenutnoClanova;
public:
	//Z5.1 :: Dflt. ctor
	Forum() {
		_naziv = nullptr;
		_trenutnoSekcija = 0;
		_maxClanova = 0;
		_clanovi = nullptr;
		_trenutnoClanova = 0;

	}

	//Z5.2 :: User-def. ctor
	Forum(const char* naziv, int maxClanova) {
		_naziv = AlocirajIKopiraj(naziv);
		_maxClanova = maxClanova;
		_trenutnoSekcija = 0;
		_clanovi = new Clan[_maxClanova];
		_trenutnoClanova = 0;
	}

	//Z5.3 :: Copy ctor
	Forum(const Forum& obj) {
		_naziv = AlocirajIKopiraj(obj._naziv);
		_trenutnoSekcija = obj._trenutnoSekcija;
		for (int i = 0; i < _trenutnoSekcija; i++)
		{
			_sekcije[i] = obj._sekcije[i];
		}
		_maxClanova = obj._maxClanova;
		_trenutnoClanova = obj._trenutnoClanova;
		_clanovi = new Clan[_maxClanova];
		for (int i = 0; i < _trenutnoClanova; i++)
		{
			_clanovi[i] = obj._clanovi[i];
		}
	}

	//Z5.4 :: Move ctor
	Forum(Forum&& obj) {
		_naziv = obj._naziv;
		obj._naziv = nullptr;
		_trenutnoSekcija = obj._trenutnoSekcija;
		for (int i = 0; i < _trenutnoSekcija; i++)
		{
			_sekcije[i] = obj._sekcije[i];
		}
		_maxClanova = obj._maxClanova;
		_trenutnoClanova = obj._trenutnoClanova;
		_clanovi = obj._clanovi;
		

		obj._maxClanova = 0;
		obj._trenutnoClanova = 0;
		obj._clanovi = nullptr;

	}

	//Z5.5 :: Getteri
	int GetTrenutnoSekcija() const { return _trenutnoSekcija; }
	Sekcija GetSekcijaAtI(int index) const { return _sekcije[index]; }
	int GetBrojClanova() const { return _trenutnoClanova; }
	int MaxBrojClanova() const { return _maxClanova; }
	Clan GetClanAtI(int index) const { return _clanovi[index]; }

	//Z5.6 :: Setteri
	void SetNaziv(const char* naziv) {
		delete[] _naziv;
		_naziv = AlocirajIKopiraj(naziv);
	}

	//Z5.7 :: Setter za _maxClanova
	/*
		Osigurati da je (noviMaxBrojClanova> _maxBrojClanova)
		Kreirati novi niz velicine (noviMaxBrojClanova)
		Kopirati sadrzaj iz starog niza u novi niz
	*/
	void SetMaxClanova(int noviMaxBrojClanova) {
		if (noviMaxBrojClanova <= _maxClanova)
			_maxClanova += noviMaxBrojClanova;
		Clan* temp = _clanovi;
		_clanovi = new Clan[_maxClanova];
		for (int i = 0; i < _trenutnoClanova; i++)
		{
			_clanovi[i] = temp[i];
		}
		delete[] temp; temp = nullptr;
	}

	//Z5.8 Operator += (dodavanje nove sekcije)
	bool operator += (const Sekcija sekcija) {
		if (_trenutnoSekcija == maxBrojSekcija)
			return false;
		_sekcije[_trenutnoSekcija++] = sekcija;
		return true;
	}

	//Z5.9 :: operator += (dodavanje novog clana)
	//Ukoliko brojac dosegne vrijednost '_maxClanova', uraditi prosirivanje niza za 10 koristenjem metode 'SetMaxClanova'
	void operator += (const Clan clan) {
		if (_maxClanova == _trenutnoClanova)
			SetMaxClanova(10);
		_clanovi[_trenutnoClanova++] = clan;
	}

	//Z5.10 :: dtor
	~Forum() {
		delete[] _naziv; _naziv = nullptr;
		delete[] _clanovi; _clanovi = nullptr;
	}
	friend ostream& operator <<(ostream& COUT, const Forum& f);
};
//Z5.11 :: Ispisati podatke o forumu, ispisati sekcije [zajedno sa postovima] te korisnicka imena forumasa [clanova]
ostream& operator <<(ostream& COUT, const Forum& f) {
	COUT << "Naziv foruma: " << f._naziv << endl;
	COUT << "Trenutno sekcija: " << f._trenutnoSekcija << endl;
	COUT << "Sekcije: " << endl;
	for (int i = 0; i < f.GetTrenutnoSekcija(); i++)
	{
		COUT << f._sekcije[i] << endl;
	}
	COUT << "Trenutno clanova: " << f._trenutnoClanova << endl;
	
	return COUT;
}