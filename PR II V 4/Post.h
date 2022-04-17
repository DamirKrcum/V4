#pragma once
#include "Datum.h"
#include "funkcije.h"
using namespace std;
class Post {
	char* _postId;
	char* _korisnickoIme; //_korisnickoIme clana foruma koji je objavio post
	Datum _datumObjavljivanja;
	char* _sadrzaj;
	static int _postIdCounter;
public:
	//Z3.0 :: Vratiti staticki brojac _postIdCounter
	static int GetCounter() {
		return Post::_postIdCounter;
	}

	//Iskoristiti funkciju IntToStr za pretvaranje trenutne vrijednosti statickog atributa '_postIdCounter' u dinamicki niz karaktera
	//Povecati vrijednost '_postIdCounter'
	static char* GetNextPostId()
	{
		return IntToStr(Post::_postIdCounter++);
	}

	//Z3.1 :: Postaviti sve atribute na dflt. vrijednosti
	Post()

	{
		_postId = nullptr;
		_korisnickoIme = nullptr;
		_sadrzaj = nullptr;
	}

	//Z3.2 :: Za inicijalizaciju _postId iskoristiti staticku funkciju GetNextPostId
	Post(const char* korisnickoIme, Datum datumO, const char* sadrzaj)
		: _datumObjavljivanja(datumO)
	{
		_postId = GetNextPostId();
		_korisnickoIme = AlocirajIKopiraj(korisnickoIme);
		_sadrzaj = AlocirajIKopiraj(sadrzaj);

	}

	//Z3.3 :: Inicijalizirati '_postId' na osnovu 'obj._postId'
	Post(const Post& obj)
		: _datumObjavljivanja(obj._datumObjavljivanja)
	{
		_postId = AlocirajIKopiraj(obj._postId);
		_korisnickoIme = AlocirajIKopiraj(obj._korisnickoIme);
		_sadrzaj = AlocirajIKopiraj(obj._sadrzaj);

	}

	//Z3.4 :: Move ctor
	Post(Post&& obj)
		:_datumObjavljivanja(move(obj._datumObjavljivanja))
	{
		_postId = obj._postId;
		obj._postId = nullptr;
		_korisnickoIme = obj._korisnickoIme;
		obj._korisnickoIme = nullptr;
		_sadrzaj = obj._sadrzaj;
		obj._sadrzaj = nullptr;
	}

	//Z3.5 :: operator dodjele
	Post& operator = (const Post& obj) {
		if (this == &obj)
			return *this;
		delete[] _postId;
		delete[] _korisnickoIme;
		delete[] _sadrzaj;
		_postId = AlocirajIKopiraj(obj._postId);
		_korisnickoIme = AlocirajIKopiraj(obj._korisnickoIme);
		_sadrzaj = AlocirajIKopiraj(obj._sadrzaj);
		_datumObjavljivanja = obj._datumObjavljivanja;				//operator = klase Datum
		return *this;
	}

	//Z3.6 :: Getteri
	char* GetKorisnickoIme() const { return _korisnickoIme; }
	Datum GetDatumObjavljivanja() const { return _datumObjavljivanja; }
	char* GetSadrzaj() const { return _sadrzaj; }

	//Z3.7 :: Setteri
	//Settovati '_postId' pomocu staticke funkcije
	void SetNewPostId() {
		delete[] _postId;
		_postId = GetNextPostId();
	}

	void SetKorisnickoIme(const char* korisnickoIme) {
		delete[] _korisnickoIme;
		_korisnickoIme = AlocirajIKopiraj(korisnickoIme);
	}
	void SetDatumObjavljivanja(Datum d) {
		_datumObjavljivanja = d;
	}
	void SetSadrzaj(const char* sadrzaj) {
		delete[] _sadrzaj;
		_sadrzaj = AlocirajIKopiraj(sadrzaj);
	}

	//Z3.8 :: dtor
	~Post() {
		delete[] _postId; _postId = nullptr;
		delete[] _korisnickoIme; _korisnickoIme = nullptr;
		delete[] _sadrzaj; _sadrzaj = nullptr;
	}
	friend ostream& operator <<(ostream& COUT, const Post& p);
};
int Post::_postIdCounter = 1000; // Inicijalizacija statickog atributa

//Z3.9 :: Ispisati podatke o postu
ostream& operator <<(ostream& COUT, const Post& p) {
	COUT << "PostID: " << p._postId << endl;
	COUT << "Autor: " << p._korisnickoIme << endl;
	COUT << "Datum objave:" << p._datumObjavljivanja << endl;
	COUT << "Sadrzaj: " << p._sadrzaj << endl;
	return COUT;
}
const int maxBrojPostova = 100;