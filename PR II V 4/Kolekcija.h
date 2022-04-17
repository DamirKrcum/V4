#pragma once
#include <iostream>
using namespace std;
template <class T>
class Kolekcija
{
	int _size = 30;
	T* podaci = new T[_size];
	int brojac = 0;
public:
	Kolekcija(int size = 30)
	{
		_size = size;
		podaci = new T[_size];
	}
	Kolekcija(const Kolekcija& k)
	{
		_size = k._size;
		podaci = new T[_size];
		brojac = k.brojac;
		for (int i = 0; i < k.brojac; i++)
		{
			podaci[i] = k.podaci[i];
		}
	}
	Kolekcija (Kolekcija&& k) {
		_size = k._size;
		k._size = 0;
		podaci = k.podaci;
		k.podaci = nullptr;
		brojac = k.brojac;
		k.brojac = 0;
	}

	Kolekcija& operator=(const Kolekcija& k)
	{
		delete[] podaci;

		_size = k._size;
		podaci = new T[_size];
		brojac = k.brojac;
		for (int i = 0; i < k.brojac; i++)
		{
			podaci[i] = k.podaci[i];
		}
		return *this;
	}

	void Prosiri()
	{
		_size *= 2;
		T* podaciNew = new T[_size];
		for (int i = 0; i < brojac; i++)
		{
			podaciNew[i] = podaci[i];
		}
		delete[]podaci;
		podaci = podaciNew;
	}

	T& Get(int i) const
	{
		return podaci[i];
	}
	T& operator[](int i) const
	{
		return Get(i);
	}

	void Dodaj(T newV)
	{
		if (brojac == _size)
			Prosiri();
		podaci[brojac++] = newV;
	}

	void operator+=(T newV)
	{
		Dodaj(newV);
	}

	int GetBrojac() const
	{
		return brojac;
	}

	~Kolekcija()
	{
		delete[] podaci;
	}

	void UkloniSve()
	{
		brojac = 0;
	}

	friend ostream& operator<< (ostream& c, const Kolekcija<T>& k);
};


//ostream& operator<<(ostream& c, const Kolekcija& k)
//{
//	for (int i = 0; i < k.GetBrojac(); i++)
//	{
//		c << k[i] << " | ";
//	}
//	c << endl;
//	return c;
//}
template <class T>
ostream& operator<< (ostream& c, const Kolekcija<T>& k)
{
	for (int i = 0; i < k.brojac; i++)
	{
		c << k.podaci[i] << " | ";
	}
	cout << endl;
	return c;
}
