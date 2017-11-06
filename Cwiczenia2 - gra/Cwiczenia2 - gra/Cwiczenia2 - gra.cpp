#include "stdafx.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>

#define PRAWDOPODOBIENSTWO_ZAPADKI 0.18
#define PRAWDOPODOBIENSTWO_KATAPULTY 0.11
using namespace std;




class Pole
{
public:
	char sasiad_1;
	char sasiad_2;
	char sasiad_3;
	char typ=0; //0=podloga 1=zapadka 2=katapulta
	bool PolaczonaZ(char p)
	{
		if (p == sasiad_1 || p == sasiad_2 || p == sasiad_3)
		{
			return true;
		}
		return false;
	}
	array<char,3> &Sasiedzi()
	{
		char out[3];
		out[0] = sasiad_1;
		out[1] = sasiad_2;
		out[2] = sasiad_3;
	}
};
Pole plansza[21]; //sztuczna implementacja indeksowania od 1; plansza[0] nie jest u¿ywane

class Potwor
{
public:
	char pozycja;

	void LosujPozycje()
	{
		char random;
		
		do
		{
			random=(rand() % 20) + 1;
		} while (plansza[random].typ == 1 || plansza[random].typ == 2);

		pozycja = random;
	}

	void IdzDoGracza()
	{

	}

	
};
Potwor potwor;

class Gracz
{
private:
	char random;
public:
	char pozycja;
	char strzaly = 5; //poczatkowa ilosc strzal

	void LosujPozycje()
	{
		

		do
		{
			random = (rand() % 20) + 1;
		} while (plansza[random].typ == 1 || plansza[random].typ == 2 || potwor.pozycja==random);

		pozycja = random;
	}

	void WykonajRuch(char cel)
	{
		system("cls");
		if (plansza[pozycja].PolaczonaZ(cel))
		{
			//mozna wykonac ruch
			if (plansza[cel].typ == 1)
			{
				//gracz wszedl w zapadke
				cout << "Koniec gry, zapadka na pozycji "<<+cel<<endl;
				// KONIEC GRY
				return;
			}

			if (plansza[cel].typ == 2)
			{
				
				WykonajSkok(cel);
				return;
			}

			pozycja = cel;
			cout << "Przeszedles na pole " << +pozycja << ". \n";

			if (potwor.pozycja == cel)
			{
				//wszedles w potwora!!
				cout << "Koniec gry, trafiles na potwora na pozycji " << +cel << endl;
				return;
			}
			SprawdzNiebezpieczenstwa();
			cout << "Wchodzisz do komory nr  " << +pozycja << ". Ta komora jest polaczona tunelami z komorami " << +plansza[pozycja].sasiad_1 << ", " << +plansza[pozycja].sasiad_2 << ", " << +plansza[pozycja].sasiad_3 << endl
				<< "Wchodzisz do nastepnej komory czy strzelasz ? \n";


		
		}
		else
		{
			cout << "Nie mozesz wykonac takiego ruchu!. \n";
			cout << "Pola w poblizu: " << +plansza[pozycja].sasiad_1 << ", " << +plansza[pozycja].sasiad_2 << ", " << +plansza[pozycja].sasiad_3<<endl;
		}
	}
	void WykonajSkok(char zrodlo)
	{
		do
		{
			random = (rand() % 20) + 1;
		} while (random == zrodlo); //katapulta nie moze przemiescic w to samo miejsce

		if (plansza[random].typ == 1)
		{
			//gracz spadl w zapadke
			cout << "Koniec gry, wpadles w zapadke na pozycji "<<+random<<endl;
			// KONIEC GRY
			return;
		}

		if (plansza[random].typ == 2)
		{
			WykonajSkok(random);
			return;

		}
		pozycja = random;
		cout << "Katapulta przerzucila cie na pozycje " << +pozycja << ". \n";


		if (potwor.pozycja == random)
		{
			//wszedles w potwora!!
			cout << "Koniec gry, spadles na potwora na pozycji " << +random << endl;
			return;
		}
		SprawdzNiebezpieczenstwa();
		cout << "Wchodzisz do komory nr "<<+pozycja<<" Ta komora jest polaczona tunelami z komorami " <<+plansza[pozycja].sasiad_1 << ", " << +plansza[pozycja].sasiad_2 << ", " << +plansza[pozycja].sasiad_3 << endl
			 <<"Wchodzisz do nastepnej komory czy strzelasz ? \n";

	}

	void Strzel(char p1, char p2)
	{
		if (strzaly <= 0)
		{
			cout << "Nie masz czym strzelac! :(" << endl;
			return;
		}
		if (p1 == p2 || p1 == pozycja || p2 == pozycja)
		{
			cout << "Strzala nie moze poleciec w ten sposob!" << endl;
			return;
		}
		if (plansza[p1].PolaczonaZ(pozycja) && plansza[p2].PolaczonaZ(p1))
		{
			//mozna strzelic w ten sposob
			strzaly--;

			if (potwor.pozycja == p1 || potwor.pozycja == p2)
			{
				//WYGRANA GRA!!!
				cout << "Zabiles potwora, brawo!" << endl;
				
			}
			else
			{
				cout << "Oddales strzal, ale nic z teog nie wyniklo..." << endl;
			}
			return;
		
		}
		else
		{
			cout << "Strzala nie moze poleciec w ten sposob!" << endl;
			return;
		}
	}

	void SprawdzNiebezpieczenstwa()
	{
		SprawdzNiebezpieczenstwo(plansza[pozycja].sasiad_1);
		SprawdzNiebezpieczenstwo(plansza[pozycja].sasiad_2);
		SprawdzNiebezpieczenstwo(plansza[pozycja].sasiad_3);
		
	}
	void SprawdzNiebezpieczenstwo(char p)
	{
		if (potwor.pozycja == p)
		{
			cout << "Czuje potwora...\n";
		}
		if (plansza[p].typ == 1)
		{
			cout << "Czuje przeciag...\n";
		}
		if (plansza[p].typ == 2)
		{
			cout << "Czuje katapulte...\n";
		}
	}

	
};
Gracz gracz;


void Wypelnij_Plansze()
{
	plansza[1].sasiad_1 = 6;
	plansza[1].sasiad_2 = 5;
	plansza[1].sasiad_3 = 2;

	plansza[2].sasiad_1 = 3;
	plansza[2].sasiad_2 = 8;
	plansza[2].sasiad_3 = 1;

	plansza[3].sasiad_1 = 2;
	plansza[3].sasiad_2 = 10;
	plansza[3].sasiad_3 = 4;

	plansza[4].sasiad_1 = 12;
	plansza[4].sasiad_2 = 3;
	plansza[4].sasiad_3 = 5;

	plansza[5].sasiad_1 = 1;
	plansza[5].sasiad_2 = 4;
	plansza[5].sasiad_3 = 14;

	plansza[6].sasiad_1 = 1;
	plansza[6].sasiad_2 = 7;
	plansza[6].sasiad_3 = 15;

	plansza[7].sasiad_1 = 6;
	plansza[7].sasiad_2 = 8;
	plansza[7].sasiad_3 = 17;

	plansza[8].sasiad_1 = 9;
	plansza[8].sasiad_2 = 7;
	plansza[8].sasiad_3 = 2;

	plansza[9].sasiad_1 = 10;
	plansza[9].sasiad_2 = 8;
	plansza[9].sasiad_3 = 18;

	plansza[10].sasiad_1 = 11;
	plansza[10].sasiad_2 = 9;
	plansza[10].sasiad_3 = 3;

	plansza[11].sasiad_1 = 19;
	plansza[11].sasiad_2 = 10;
	plansza[11].sasiad_3 = 12;

	plansza[12].sasiad_1 = 13;
	plansza[12].sasiad_2 = 11;
	plansza[12].sasiad_3 = 4;

	plansza[13].sasiad_1 = 12;
	plansza[13].sasiad_2 = 14;
	plansza[13].sasiad_3 = 20;

	plansza[14].sasiad_1 = 5;
	plansza[14].sasiad_2 = 13;
	plansza[14].sasiad_3 = 15;

	plansza[15].sasiad_1 = 6;
	plansza[15].sasiad_2 = 13;
	plansza[15].sasiad_3 = 14;

	plansza[16].sasiad_1 = 17;
	plansza[16].sasiad_2 = 20;
	plansza[16].sasiad_3 = 15;

	plansza[17].sasiad_1 = 7;
	plansza[17].sasiad_2 = 18;
	plansza[17].sasiad_3 = 16;

	plansza[18].sasiad_1 = 9;
	plansza[18].sasiad_2 = 17;
	plansza[18].sasiad_3 = 19;

	plansza[19].sasiad_1 = 11;
	plansza[19].sasiad_2 = 18;
	plansza[19].sasiad_3 = 20;

	plansza[20].sasiad_1 = 16;
	plansza[20].sasiad_2 = 19;
	plansza[20].sasiad_3 = 13;

	double random;
	//generacja jaskin
	for (char i = 1; i <= 21; i++)
	{
		random = ((double)rand() / (RAND_MAX));
		if (random < PRAWDOPODOBIENSTWO_ZAPADKI)
		{
			plansza[i].typ = 1;
		}
	}

	//generacja katapult
	for (char i = 1; i <= 21; i++)
	{
		random = ((double)rand() / (RAND_MAX));
		if (random < PRAWDOPODOBIENSTWO_KATAPULTY)
		{
			plansza[i].typ = 2;
		}
	}
}



void ShowDebug()
{
	cout << "==============DEBUG===========\n";
	cout << "Katapulty sa na polach: ";
	for (char i = 1;i <= 21;i++)
	{
		if (plansza[i].typ == 2)
			cout << +i << ", ";
	}
	cout << "\n";

	cout << "Zapadki sa na polach: ";
	for (char i = 1;i <= 21;i++)
	{
		if (plansza[i].typ == 1)
			cout << +i << ", ";
	}
	cout << "\n";

	cout << "Pozycja potwora: " << +potwor.pozycja<<"\n";

	cout << "Pozycja gracza: " << +gracz.pozycja << "\n";
	cout << "Graczowi pozostalo " <<+gracz.strzaly << " strzal.\n";
}

char main()
{
	srand(time(NULL));
	string input;

	Wypelnij_Plansze();
	potwor.LosujPozycje(); //musi byc wywolane przed gracz.LosujPozycje !!!
	gracz.LosujPozycje();
	

	do
	{
		cin >> input;
		if (input == "d")
		{
			system("CLS");
			ShowDebug();
		}
		if (input[0] == 'm') //ruch gracza
		{
			char cel;
			input.erase(0, 1);
			try
			{ 
				cel = stoi(input);
			}
			catch(invalid_argument)
			{
				cout << "Blad w skladni polecenia!!!"<<endl;
				continue;
			}

			gracz.WykonajRuch(cel);
			
		}

		if (input[0] == 's') //strzal gracza
		{
			input.erase(0, 1);
			char out[3] = { 0 };
			
			size_t pos = 0;
			string token;
			try
			{
				pos = input.find("-");
				token = input.substr(0, pos);	
				out[0] = stoi(token);
				input.erase(0, pos + 1);

				pos = input.find("-");
				token = input.substr(0, pos);
				out[1] = stoi(token);
				input.erase(0, pos + 1);

				out[2] = stoi(input);
			}
			catch (invalid_argument)
			{
				cout << "Blad w skladni polecenia!!!"<< endl;
				continue;
			}

			if(out[0]==gracz.pozycja)
				gracz.Strzel(out[1], out[2]);
			else
			{
				cout << "Strzal powinien sie zaczynac od Twojej pozycji!" << endl;
				continue;
			}

			
		}

	} while (true);


    return 0;
}

