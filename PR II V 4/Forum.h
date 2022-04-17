#pragma once
#include"Sekcija.h"
#include"clan.h"
#include"Kolekcija.h"
class Forum {
	char* _naziv;
	
	Kolekcija<Sekcija> _sekcije;
	
	Kolekcija<Clan> _clanovi;
public:
	//Z5.1 :: Dflt. ctor
	Forum() {
		_naziv = nullptr;
		
	}

	//Z5.2 :: User-def. ctor
	Forum(const char* naziv, int maxClanova) {
		_naziv = AlocirajIKopiraj(naziv);
		
	}

	//Z5.3 :: Copy ctor
	Forum(const Forum& obj) {
		_naziv = AlocirajIKopiraj(obj._naziv);
		_sekcije = obj._sekcije;		
		_clanovi = obj._clanovi;
		

	}

	//Z5.4 :: Move ctor
	Forum(Forum&& obj) {
		_naziv = obj._naziv;
		obj._naziv = nullptr;		
		_sekcije = obj._sekcije;
		obj._sekcije.UkloniSve();		
		_clanovi = obj._clanovi;
		obj._clanovi.UkloniSve();
	}

	//Z5.5 :: Getteri
	int GetTrenutnoSekcija() const { return _sekcije.GetBrojac(); }
	Sekcija GetSekcijaAtI(int index) const { return _sekcije[index]; }
	int GetBrojClanova() const { return _clanovi.GetBrojac(); }
	
	Clan GetClanAtI(int index) const { return _clanovi[index]; }

	//Z5.6 :: Setteri
	void SetNaziv(const char* naziv) {
		delete[] _naziv;
		_naziv = AlocirajIKopiraj(naziv);
	}

	//Z5.7 :: Setter za _maxClanova
	

	//Z5.8 Operator += (dodavanje nove sekcije)
	bool operator += (const Sekcija sekcija) {
		
		_sekcije += sekcija;
		return true;
	}

	//Z5.9 :: operator += (dodavanje novog clana)
	//Ukoliko brojac dosegne vrijednost '_maxClanova', uraditi prosirivanje niza za 10 koristenjem metode 'SetMaxClanova'
	void operator += (const Clan clan) {		
		_clanovi += clan;
	}

	//Z5.10 :: dtor
	~Forum() {
		delete[] _naziv; _naziv = nullptr;		
		_clanovi.UkloniSve();
	}
	friend ostream& operator <<(ostream& COUT, const Forum& f);
};
//Z5.11 :: Ispisati podatke o forumu, ispisati sekcije [zajedno sa postovima] te korisnicka imena forumasa [clanova]
ostream& operator <<(ostream& COUT, const Forum& f) {
	COUT << "Naziv foruma: " << f._naziv << endl;
	COUT << "Trenutno sekcija: " << f._sekcije.GetBrojac() << endl;
	COUT << "Sekcije: " << endl;
	for (int i = 0; i < f.GetTrenutnoSekcija(); i++)
	{
		COUT << f._sekcije[i] << endl;
	}
	COUT << "Trenutno clanova: " << f._clanovi.GetBrojac() << endl;

	return COUT;
}