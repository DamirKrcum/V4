#pragma once
#include "Datum.h"
#include "funkcije.h"
using namespace std;

class Clan {
	const int _clanId;
	char _korisnickoIme[30];
	char _lozinka[20];
	Datum* _datumRegistracije;
	bool* _spol;
	static int _clanIdCounter;
public:
	//Z2.0 :: Vratiti vrijednost statickog atributa _clanIdCounter
	static int GetCounter() {
		return _clanIdCounter;
	}

	//Z2.1 :: Dflt. ctor  [Postaviti _clanId na vrijednost statickog brojaca. Zatim, uvecati brojac]
	Clan()
		: _clanId(_clanIdCounter++)
	{
		strcpy_s(_korisnickoIme, 30, "");
		strcpy_s(_lozinka, 20, "");
		_datumRegistracije = nullptr;
		_spol = nullptr;
	}

	//Z2.2 :: User-def. ctor [Postaviti _clanId na vrijednost statickog brojaca. Zatim, uvecati brojac]
	Clan(const char* korisnickoIme, const char* lozinka, Datum datumReg, bool spol)
		: _clanId(_clanIdCounter++)
	{
		strcpy_s(_korisnickoIme, 30, korisnickoIme);
		strcpy_s(_lozinka, 20, lozinka);
		_datumRegistracije = new Datum(datumReg);
		_spol = new bool(spol);
	}

	//Z2.3 :: Copy ctor [kopirati obj._clanId u _clanId]
	Clan(const Clan& obj)
		:_clanId(obj._clanId)
	{
		strcpy_s(_korisnickoIme, 30, obj._korisnickoIme);
		strcpy_s(_lozinka, 20, obj._lozinka);
		_datumRegistracije = new Datum;
		*_datumRegistracije = *obj._datumRegistracije;
		_spol = new bool(obj._spol);
	}

	//Z2.4 :: Move ctor [kopirati obj._clanId u _clanId]
	Clan(Clan&& obj)
		: _clanId(obj._clanId)
	{
		strcpy_s(_korisnickoIme, 30, obj._korisnickoIme);
		strcpy_s(obj._korisnickoIme, 30, "");
		strcpy_s(_lozinka, 20, obj._lozinka);
		strcpy_s(obj._lozinka, 20, "");
		_spol = obj._spol;
		obj._spol = nullptr;
		_datumRegistracije = obj._datumRegistracije;
		obj._datumRegistracije = nullptr;
	}

	//Z2.5 :: operator dodjele
	Clan& operator = (const Clan& obj)
	{
		if (this == &obj)
			return *this;
		delete _datumRegistracije;
		delete _spol;
		strcpy_s(_korisnickoIme, 30, obj._korisnickoIme);
		strcpy_s(_lozinka, 20, obj._lozinka);
		_datumRegistracije = new Datum;
		*_datumRegistracije = *obj._datumRegistracije;			//provjeriti radi li operator = od klase datum
		_spol = new bool(obj._spol);
		return *this;
	}

	//Z2.6 :: Getteri
	const char* GetKorisnickoIme() const { return _korisnickoIme; }
	const char* GetLozinka() const { return _lozinka; }
	Datum GetDatumPrijave() const { return *_datumRegistracije; }
	bool GetSpol() const { return *_spol; }

	//Z2.7 :: Setteri
	void SetKorisnickoIme(const char* korisnickoIme) {
		strcpy_s(_korisnickoIme, 30, korisnickoIme);
	}
	void SetLozinka(const char* lozinka) {
		strcpy_s(_lozinka, 20, lozinka);
	}
	void SetDatumRegistracije(Datum datumRegistracije) {
		if (_datumRegistracije == nullptr)
			_datumRegistracije = new Datum;
		_datumRegistracije->SetDan(datumRegistracije.GetDan());
		_datumRegistracije->SetMjesec(datumRegistracije.GetMjesec());
		_datumRegistracije->SetGodina(datumRegistracije.GetGodina());
	}
	void SetSpol(bool spol) {
		if (_spol == nullptr)
			_spol = new bool;
		*_spol = spol;
	}

	//Z2.8 :: dtor
	~Clan() {
		delete _datumRegistracije;
		_datumRegistracije = nullptr;
		delete _spol;
		_spol = nullptr;
	}
	friend ostream& operator <<(ostream& COUT, const Clan& clan);
};
int Clan::_clanIdCounter = 1; // Inicijalizacija statickog atributa

//Z2.9 :: Ispisati podatke o clanu
ostream& operator <<(ostream& COUT, const Clan& clan) {
	COUT << "ID: " << clan._clanId << endl;
	COUT << "Username: " << clan._korisnickoIme << endl;
	COUT << "Datum registracije: " << *clan._datumRegistracije << endl;
	COUT << "Spol: " << (*clan._spol ? "Muski" : "Zenski") << endl;
	return COUT;
}

//Z2.10 :: operator == [Porediti clanove 'c1' i 'c2' po korisnickom imenu]
bool operator ==(const Clan& c1, const Clan& c2) {
	if (strcmp(c1.GetKorisnickoIme(), c2.GetKorisnickoIme()) == 0)
		return true;
	return false;
}