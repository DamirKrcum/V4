#include <iostream>
#include "Datum.h"
#include "funkcije.h"
#include "clan.h"
#include "Post.h"
#include "Sekcija.h"
#include "Forum.h"
using namespace std;

void Zadatak1() {
	int broj = 56511;
	cout << "Pretvaranje broja (56511) u str] : " << endl;
	char* stringBroj = IntToStr(broj);
	cout << stringBroj << endl;
	delete[] stringBroj;
	stringBroj = nullptr;
	cout << "Sve prijestupne godine izmedju [1900-2021]: " << endl;
	for (size_t i = 1900; i <= 2021; i++)
		if (PrijestupnaGodina(i))
			cout << i << ", ";
	cout << endl;
	Datum starWarsDay; //dflt. ctor
	starWarsDay.SetDan(4);
	starWarsDay.SetMjesec(5);
	starWarsDay.SetGodina(2021);
	cout << "Star Wars day: " << starWarsDay << endl; // operator <<

	Datum worldUfoDay(starWarsDay.GetDan() - 3, starWarsDay.GetMjesec() + 2, starWarsDay.GetGodina()); //user-def. ctor
	cout << "World Ufo day: " << worldUfoDay << endl;

	Datum laborDay(starWarsDay); //copy ctor
	laborDay.SetDan(1);
	cout << "Labor day (BiH): " << laborDay << endl;

	Datum victoryDay(move(laborDay)); //Move ctor
	victoryDay.SetDan(9);
	cout << "Victory day (BiH): " << victoryDay << endl;

	Datum juneSolstice(21, 6, 2021), juneSolstice_copy;
	juneSolstice_copy = juneSolstice;
	cout << "June Solstice (BiH): " << juneSolstice << endl;
	cout << "Dealokacija ..." << endl;

	Datum datumi[] = { Datum(1,2,2021), Datum(31,12, 2020), Datum(31, 12, 2021) };
	cout << "Razlika u danima: --->" << endl;
	cout << "Razlika izmedju: " << datumi[0] << " i " << datumi[1] << " je " << datumi[0] - datumi[1] << endl; // operator -
	cout << "Razlika izmedju: " << datumi[0] << " i " << datumi[2] << " je " << datumi[0] - datumi[2] << endl; // operator -
	cout << "Razlika izmedju: " << datumi[1] << " i " << datumi[2] << " je " << datumi[1] - datumi[2] << endl; // operator -

	//Testiranje operatora +
	Datum someDatum(5, 5, 2025);
	cout << "Test datum: " << someDatum << endl;
	cout << someDatum << " + 30 dana  = " << someDatum + 30 << endl; // operator +
	cout << "Dealokacija..." << endl;
}

void Zadatak2() {

	Clan almightyBruce;
	almightyBruce.SetKorisnickoIme("almightyBruce");
	almightyBruce.SetDatumRegistracije(Datum(1, 1, 2021));
	almightyBruce.SetSpol(0);
	almightyBruce.SetSpol(1);
	almightyBruce.SetLozinka("its'Goooood");
	cout << almightyBruce << endl;

	Clan crazyMage("CrazyMage", "PA$$w0rd", Datum(3, 12, 2019), 1);
	Clan copyCrazyMage(crazyMage);
	cout << copyCrazyMage << endl;

	Clan azermyth("Azermyth", "azerpass", Datum(1, 4, 2020), 1);
	Clan noviAzer(move(azermyth));
	cout << noviAzer << endl;
	cout << "Testiranje operatora '==' " << endl;
	cout << (crazyMage == copyCrazyMage ? "Isti clan!" : "Razlici clanovi!") << endl;

	Clan aceVentura;
	aceVentura = noviAzer;
	aceVentura.SetKorisnickoIme("8Ventura");
	cout << aceVentura << endl;
	cout << "Dealokacija..." << endl;
}
void Zadatak3() {
	Post p1;
	p1.SetNewPostId();
	p1.SetKorisnickoIme("Neo");
	p1.SetDatumObjavljivanja(Datum(5, 5, 2021));
	p1.SetSadrzaj("Izasao sam iz matrice. Osjecaj je prelijep...");
	cout << p1 << endl;

	Post p2("Trinity", Datum(5, 5, 2021), " Kolega @Neo, you don't say.");
	Post copyp2(p2);
	cout << copyp2 << endl;

	Post p3("Ementaler", Datum(6, 5, 2021), "Pozdrav ljudi. Ovdje Igor sa Hcl-a...");
	Post pr3new(move(p3));
	cout << pr3new << endl;

	Post p4;
	p4 = pr3new;
	p4.SetNewPostId();
	p4.SetKorisnickoIme("Agent Smith");
	p4.SetSadrzaj("Dragi kolega @Neo, pripremite se da vas dealociram.");
	cout << p4 << endl;
	cout << "Dealokacija..." << endl;
}

void Zadatak4() {
	Sekcija letNaMars("Let na mars, all about...", "Neki opis...");
	Post p1("bad_karma13", Datum(2, 3, 2020), "Ispucao je losu srecu na Cybertrucku.. Ovo uspijeva 100%");
	Post p2("monkey_see_monkey_do", Datum(3, 3, 2020), "Kad ono uzlijece Elon sa svojima? xD");
	Post p3("cerealKillerHoho", Datum(3, 3, 2020), "Teraformiranje Marsa ce se pokazati kao prevelik zalogaj za nasu generaciju...");
	Post p4("dr_Michio_Kaku", Datum(3, 3, 2020), "Ovo je prvi korak u kolonizaciji Suncevog sistema...");
	letNaMars += p1;
	letNaMars += p2;
	letNaMars += p3;
	Sekcija mars2(letNaMars);
	mars2 += p4;

	Sekcija mars3(move(mars2));
	Post p5("superSonic", Datum(3, 3, 2020), "Zelimo novo gostovanje g.Muska kod Joe Rogena!");
	mars3 += p5;
	Sekcija mars4;
	mars4 = mars3;
	cout << mars4 << endl;
	cout << "Dealokacija..." << endl;
}

void Zadatak5() {
	 Forum nebula("Nebula:: forum o fizici i metafizici", 10);
	 Clan arwen_dor("arwenix", "L0trI$L1fe", Datum(11, 1, 2021), 0);
	 Clan thomasAnderson("neo", "one", Datum(12, 1, 2021), 1);
	 Clan rickC_137("rickestRick", "wabalubadubdub", Datum(3, 3, 2021), 1);
	
	 //Dodavanje clanova preko operatora +=
	 nebula += arwen_dor;
	 nebula += thomasAnderson;
	 nebula += rickC_137;
	 //
	 Sekcija newAge("New Age", "Sta predstavlja New Age?");
	 Post p1("arwenix", Datum(3, 3, 2020), "Postoji niz proturijecnih definicija o novom fenomenu ...");
	 Post p2("neo", Datum(4, 3, 2020), "Nova religija? Ili ipak samo nova paradigma? ...");
	 Post p3("rickestRick", Datum(5, 3, 2020), "Ovisi od konteksta u kojem se pojavljuje");
	 newAge += p1; // dodavanje posta
	 newAge += p2; // dodavanje posta
	 newAge += p3; // dodavanje posta
	 //
	 Sekcija telepatija("Telepatija i telekineza", "Parapsiholoski fenomeni");
	 Post p4("arwenix", Datum(6, 3, 2020), "Na ovom podrucju najvise se proslavio Uri Geller ...");
	 Post p5("neo", Datum(7, 3, 2020), "Medju poznatije slucajeve ubraja se i Nina Kulagina...");
	 telepatija += p4; // dodavanje posta
	 telepatija += p5; // dodavanje posta
	 //
	 nebula += newAge; // dodavanje sekcije
	 nebula += telepatija; // dodavanje sekcije
	 //
	 Forum copy_of_nebula(nebula);
	 Forum nebula_prime(move(copy_of_nebula));
	 cout << nebula_prime;
	 cout << "Dealokacija..." << endl;
}

int Menu() {
	int nastaviDalje = 1;
	while (nastaviDalje == 1) {
		int izbor = 0;
		do {
			system("cls");
			cout << "::Zadaci::" << endl;
			cout << "(1) Zadatak 1" << endl;
			cout << "(2) Zadatak 2" << endl;
			cout << "(3) Zadatak 3" << endl;
			cout << "(4) Zadatak 4" << endl;
			cout << "(5) Zadatak 5" << endl;
			cout << "Unesite odgovarajuci broj zadatka za testiranje: -->: ";
			cin >> izbor;
			cout << endl;
		} while (izbor < 1 || izbor > 5);
		switch (izbor) {
		case 1: Zadatak1(); cout << "Zadatak 1. Done." << endl; break;
		case 2: Zadatak2(); cout << "Zadatak 2. Done." << endl; break;
		case 3: Zadatak3(); cout << "Zadatak 3. Done." << endl; break;
		case 4: Zadatak4(); cout << "Zadatak 4. Done." << endl; break;
		case 5: Zadatak5(); cout << "Zadatak 5. Done." << endl; break;
		default:break;
		}
		do {
			cout << "DA LI ZELITE NASTAVITI DALJE? (1/0): ";
			cin >> nastaviDalje;
		} while (nastaviDalje != 0 && nastaviDalje != 1);
	}
	return 0;
}

int main() {
	Menu();
	return 0;
}

