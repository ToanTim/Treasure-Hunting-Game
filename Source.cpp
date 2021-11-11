#include<iostream>
#include"Class.h"
#include<string>
#include<ctime>
#include<stdlib.h>
#include<Windows.h>
#include<vector>
#include<conio.h>
#pragma warning(disable : 4996)


using namespace std;
//void draw(map& level, Player& p, Monster* m_group, MagicApple* a_group, Gem* g_group);
//if there is gem on the map then it return true then door to neext level still close

void begin(map& level, Player& p);
//random function
int rangeRandom(int min, int max) {
	int n = max - min + 1;
	int remainder = RAND_MAX % n;
	int x = 0;
	do {
		x = rand();
	} while (x >= RAND_MAX - remainder);
	return min + x % n;
}

void opent_door(map& level, Gem* g)
{
	if ((g->gem_count - 2) < g->gem_count)
	{
		int width_random = rangeRandom(2, level.width - 2);
		int heigth_random = rangeRandom(2, level.height - 2);
		if (level.character[width_random][heigth_random] != '.')
		{
			width_random = rangeRandom(2, level.width - 2);
			heigth_random = rangeRandom(2, level.height - 2);
		}

		level.character[width_random][heigth_random] = 'D';
	}

}


//clear screen without blinking
void clearScreen()
{

	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void clearBox()
{
	HANDLE hOut;
	COORD Position;
	DWORD Written;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 10;
	FillConsoleOutputCharacter(hOut, ' ', 1000000, Position, &Written);

	SetConsoleCursorPosition(hOut, Position);
}

void push_move(vector<string>& Toan, string x)
{
	Toan.push_back(x);
}

void print_move(vector<string>& Toan)
{

	for (auto it = Toan.begin(); it != Toan.end(); ++it)
	{

		cout << *it << endl;
		cout << "-------------------------------------------------" << endl;
		cout << endl;
	}
}

void end_print(map& level, Player& p, vector<string>& Toan)
{
	system("CLS");
	cout << endl;
	cout << endl;
	cout << endl;
	cout << ">>>>>>>>>>>>>>>>>>>>       Game Over           <<<<<<<<<<<<<<<<<<<<<<<<" << endl;
	cout << endl;
	cout << "*******                   Messenger from creator                       *******" << endl;
	cout << "*******Hello everyone my name is Toan Tran, I created this dungeon game*******" << endl;
	cout << "*******               Thank you for playing my Game                    *******" << endl;
	cout << ">>>> If you have any quesion or feedback, pls don't heritage and send me  <<<<" << endl;
	cout << ">>>>                     Email:toan.tran@tuni.fi                          <<<<" << endl;
	cout << ">>>>                     Your smile is my success                         <<<<" << endl;
	cout << endl;
	cout << endl;
	cout << "------------------------------------------------------------------------------------------" << endl;
	cout << ">>>>>>>>>>>Congratulation! you have successfull escaped from the " << level.getLevel() << "- level" << " <<<<<<<" << endl;
	cout << "Dungeon after " << p.getMoveCount() << " moves, with " << p.getGemCounter() << " Gem and total " << p.getPoints() << " points" << endl;
	cout << "Brief adventure history:" << endl;
	print_move(Toan);
}

void move(map& level, Player& p, MagicApple* a, Monster* m, Gem* g, vector<string>& Toan)
{
	time_t curr_time; curr_time = time(NULL); string tm = ctime(&curr_time);
	string gem = tm + ":You found a gem";
	string apple = tm + ":Ate a magic apple.";
	string monster = tm + ":Engaged and slayed a monster";

	position pos_p = p.getPosition();
	level.ok = 0;
	//player
	int actual_x_p = pos_p.x - 1;
	int actual_y_p = pos_p.y - 1;
	char moves;

	char LevelUp = 'o';
	cout << "Please select action (move with wasd or Q to escape)" << endl;
	//cin.get(move);
	moves = tolower(getch());


	while (moves != 'Q' && moves != 'q')
	{
		string level_up = tm + ">>>>Entered level " + to_string(level.getLevel()) + " caves";
		if (p.energy == 0)
		{
			moves = 'Q';
		}
		switch (moves)
		{
		case 'a':
			clearScreen();


			//p.energy = p.energy - 5;
			if (level.character[actual_x_p][actual_y_p - 1] != 'X')
			{
				p.move_counter = p.move_counter + 1;
				if (level.character[actual_x_p][actual_y_p - 1] == 'A')
				{
					Toan.push_back(apple);
					//int random = rand() % 10;
					p.energy = p.energy - 5;
					p.energy = p.energy + a[0].getEnergy();
				}
				else if (level.character[actual_x_p][actual_y_p - 1] == 'M')
				{
					Toan.push_back(monster);
					p.energy = p.energy - 5;
					p.energy = p.energy - m[0].getStrength();
				}
				else if (level.character[actual_x_p][actual_y_p - 1] == 'G')
				{
					p.gem_counter = p.gem_counter + 1;
					p.energy = p.energy - 5;
					p.point = p.point + g[0].getPoint();
					g->gem_count = g->gem_count - 1;
					Toan.push_back(gem);
					opent_door(level, g);
				}
				else if (level.character[actual_x_p][actual_y_p - 1] == '.')
				{
					p.energy = p.energy - 5;

				}
				else if (level.character[actual_x_p][actual_y_p - 1] == 'D')
				{
					/*
					level.width = level.width + level.getLevel();
					level.height = level.height + level.getLevel();
					//level.mapSet();
					//draw(level, p, m, a, g);

					map m1(level.width, level.height);
					begin(m1);
					*/
					Toan.push_back(level_up);
					system("CLS");
					moves = 'q';
					level.ok = level.ok + 1;


				}

				level.character[actual_x_p][actual_y_p] = '.';
				level.character[actual_x_p][actual_y_p - 1] = p.getSympol();
				actual_y_p = actual_y_p - 1;

				//system("CLS");
		//clearScreen();
				if (moves != 'q')
				{
					level.print(p);
					if (p.energy != 0)
					{
						cout << "Please select action (move with wasd or Q to escape)" << endl;
						moves = tolower(getch());
					}
					else
					{
						moves = 'q';
						end_print(level, p, Toan);
					}
				}

				//clearBox();


				clearBox();
			}
			else
			{
				level.print(p);
				cout << "Please select action (move with wasd or Q to escape)" << endl;
				moves = tolower(getch());
			}


			break;
		case 's':
			clearScreen();


			//minus energy everytiem move
			//p.energy=p.energy - 5;

			if (level.character[actual_x_p + 1][actual_y_p] != 'X')
			{
				p.move_counter = p.move_counter + 1;
				if (level.character[actual_x_p + 1][actual_y_p] == 'A')
				{
					Toan.push_back(apple);
					p.energy = p.energy - 5;
					p.energy = p.energy + a[0].getEnergy();

				}
				else if (level.character[actual_x_p + 1][actual_y_p] == 'M')
				{
					Toan.push_back(monster);
					p.energy = p.energy - 5;
					p.energy = p.energy - m[0].getStrength();

				}
				else if (level.character[actual_x_p + 1][actual_y_p] == 'G')
				{
					Toan.push_back(gem);
					p.gem_counter = p.gem_counter + 1;
					p.energy = p.energy - 5;
					p.point = p.point + g[0].getPoint();
					g->gem_count = g->gem_count - 1;
					opent_door(level, g);

				}
				else if (level.character[actual_x_p + 1][actual_y_p] == '.')
				{
					p.energy = p.energy - 5;

				}
				else if (level.character[actual_x_p + 1][actual_y_p] == 'D')
				{
					/*
					level.width = level.width + level.getLevel();
					level.height = level.height + level.getLevel();
					//level.mapSet();
					//draw(level, p, m, a, g);

					map m1(level.width, level.height);
					begin(m1);
					*/
					Toan.push_back(level_up);
					system("CLS");
					moves = 'q';
					level.ok = level.ok + 1;

				}
				level.character[actual_x_p][actual_y_p] = '.';
				level.character[actual_x_p + 1][actual_y_p] = p.getSympol();
				actual_x_p = actual_x_p + 1;

				//system("CLS");
			//clearScreen();
				if (moves != 'q')
				{
					level.print(p);
					if (p.energy != 0)
					{
						cout << "Please select action (move with wasd or Q to escape)" << endl;
						moves = tolower(getch());
					}
					else
					{
						moves = 'q';
						end_print(level, p, Toan);
					}
				}
			}
			else
			{
				level.print(p);
				cout << "Please select action (move with wasd or Q to escape)" << endl;
				moves = tolower(getch());
			}



			clearBox();


			break;
		case 'w':
			clearScreen();
			//move = _getch();


			//minus energy everytiem move
			//p.energy=p.energy - 5;

			if (level.character[actual_x_p - 1][actual_y_p] != 'X')
			{
				p.move_counter = p.move_counter + 1;
				if (level.character[actual_x_p - 1][actual_y_p] == 'A')
				{
					Toan.push_back(apple);
					p.energy = p.energy - 5;
					p.energy = p.energy + a[0].getEnergy();

				}
				else if (level.character[actual_x_p - 1][actual_y_p] == 'M')
				{
					Toan.push_back(monster);
					p.energy = p.energy - 5;
					p.energy = p.energy - m[0].getStrength();

				}
				else if (level.character[actual_x_p - 1][actual_y_p] == 'G')
				{
					Toan.push_back(gem);
					p.gem_counter = p.gem_counter + 1;
					p.energy = p.energy - 5;
					p.point = p.point + g[0].getPoint();
					g->gem_count = g->gem_count - 1;
					opent_door(level, g);


				}
				else if (level.character[actual_x_p - 1][actual_y_p] == '.')
				{
					p.energy = p.energy - 5;

				}

				else if (level.character[actual_x_p - 1][actual_y_p] == 'D')
				{
					/*
					level.width = level.width + level.getLevel();
					level.height = level.height + level.getLevel();
					//level.mapSet();
					//draw(level, p, m, a, g);

					map m1(level.width, level.height);
					begin(m1);
					*/
					Toan.push_back(level_up);
					system("CLS");
					moves = 'q';
					level.ok = level.ok + 1;

				}
				level.character[actual_x_p][actual_y_p] = '.';
				level.character[actual_x_p - 1][actual_y_p] = p.getSympol();
				actual_x_p = actual_x_p - 1;


				//system("CLS");
				//clearScreen();
				if (moves != 'q')
				{
					level.print(p);
					if (p.energy != 0)
					{
						cout << "Please select action (move with wasd or Q to escape)" << endl;
						moves = tolower(getch());
					}
					else
					{
						moves = 'q';
						end_print(level, p, Toan);
					}
				}

				clearBox();
			}
			else
			{
				level.print(p);
				cout << "Please select action (move with wasd or Q to escape)" << endl;
				moves = tolower(getch());
			}
			break;
		case 'd':
			clearScreen();

			//minus energy everytiem move
			//p.energy=p.energy - 5;

			//move = _getch();

			if (level.character[actual_x_p][actual_y_p + 1] != 'X')
			{
				p.move_counter = p.move_counter + 1;
				if (level.character[actual_x_p][actual_y_p + 1] == 'A')
				{
					Toan.push_back(apple);
					p.energy = p.energy - 5;
					p.energy = p.energy + a[0].getEnergy();

				}
				else if (level.character[actual_x_p][actual_y_p + 1] == 'M')
				{
					Toan.push_back(monster);
					p.energy = p.energy - 5;
					p.energy = p.energy - m[0].getStrength();

				}
				else if (level.character[actual_x_p][actual_y_p + 1] == 'G')
				{
					Toan.push_back(gem);
					p.gem_counter = p.gem_counter + 1;
					p.energy = p.energy - 5;
					p.point = p.point + g[0].getPoint();
					g->gem_count = g->gem_count - 1;
					opent_door(level, g);

				}
				else if (level.character[actual_x_p][actual_y_p + 1] == '.')
				{
					p.energy = p.energy - 5;
				}
				else if (level.character[actual_x_p][actual_y_p + 1] == 'D')
				{
					/*
					level.width = level.width + level.getLevel();
					level.height = level.height + level.getLevel();
					//level.mapSet();
					//draw(level, p, m, a, g);

					map m1(level.width, level.height);
					begin(m1);
					*/
					Toan.push_back(level_up);
					system("CLS");
					moves = 'q';
					level.ok = level.ok + 1;

				}
				level.character[actual_x_p][actual_y_p] = '.';
				level.character[actual_x_p][actual_y_p + 1] = p.getSympol();
				actual_y_p = actual_y_p + 1;

				//system("CLS");
				//clearScreen();
				if (moves != 'q')
				{
					level.print(p);
					if (p.energy != 0)
					{
						cout << "Please select action (move with wasd or Q to escape)" << endl;
						moves = tolower(getch());
					}
					else
					{
						moves = 'q';
						end_print(level, p, Toan);
					}
				}
				//clearBox();



				clearBox();
			}
			else
			{
				level.print(p);
				cout << "Please select action (move with wasd or Q to escape)" << endl;
				moves = tolower(getch());
			}
			break;
		default:
			system("CLS");

			clearScreen();
			level.print(p);
			cout << "Please select action (move with wasd or Q to escape)" << endl;
			//cin.get(move);
			moves = tolower(getch());
			system("CLS");
			break;


			break;
		}
	}

}

void setup_object(map& level, Player& p, vector<string>& Toan)
{
	level.mapSet();
	int m_size = 2 + level.getLevel();
	int a_size = 2 + level.getLevel();
	int g_size = 2 + level.getLevel();
	Monster* m_group = new Monster[m_size];
	MagicApple* a_group = new MagicApple[a_size];
	Gem* g_group = new Gem[g_size];

	//---------------------------
	position* m_po = new position[m_size];
	position* a_po = new position[a_size];
	position* g_po = new position[g_size];
	position pos_p = p.getPosition();
	//m_po[i] = m_group[i].getPosition();
	//a_po[i] = a_group[i].getPosition();
	//g_po[i] = g_group[i].getPosition();

	level.character[pos_p.x - 1][pos_p.y - 1] = p.getSympol();

	for (int i = 0; i < m_size; i++)
	{
		int random_x = rangeRandom(2, level.width - 2);
		int random_y = rangeRandom(2, level.height - 2);
		while (level.character[random_x][random_y] != '.')
		{
			random_x = rangeRandom(2, level.width - 2);
			random_y = rangeRandom(2, level.height - 2);
		}
		m_group[i] = Monster(random_x, random_y, 'M', 5);
		m_po[i] = m_group[i].getPosition();
		level.character[m_po[i].x - 1][m_po[i].y - 1] = m_group[i].getSympol();
	}




	for (int i = 0; i < a_size; i++)
	{
		int random_x = rangeRandom(2, level.width - 2);
		int random_y = rangeRandom(2, level.height - 2);

		while (level.character[random_x][random_y] != '.')
		{
			random_x = rangeRandom(2, level.width - 2);
			random_y = rangeRandom(2, level.height - 2);
		}

		a_group[i] = MagicApple(random_x, random_y, 'A', 40);
		a_po[i] = a_group[i].getPosition();
		level.character[a_po[i].x - 1][a_po[i].y - 1] = a_group[i].getSympol();
	}

	for (int i = 0; i < g_size; i++)
	{
		int random_x = rangeRandom(2, level.width - 2);
		int random_y = rangeRandom(2, level.height - 2);

		while (level.character[random_x][random_y] != '.')
		{
			random_x = rangeRandom(2, level.width - 2);
			random_y = rangeRandom(2, level.height - 2);
		}

		g_group[i] = Gem(random_x, random_y, 'G', 50);
		g_po[i] = g_group[i].getPosition();
		level.character[g_po[i].x - 1][g_po[i].y - 1] = g_group[i].getSympol();
	}
	//level.move_player(m_group, m_size, p, a_group, a_size, g_group, g_size);
	level.print(p);
	move(level, p, a_group, m_group, g_group, Toan);


	delete[] m_group;
	delete[] a_group;
	delete[] g_group;

	delete[] m_po;
	delete[] a_po;
	delete[] g_po;
}

void begin(map& level, Player& p, vector<string>& Toan)
{
	setup_object(level, p, Toan);

}

void Information()
{
	system("CLS");
	cout << "Hello, my name is Toan Tran, Game creator, nice to meet you !!" << endl;
	Sleep(2000);
	cout << "\n      I am a bachelor's degree student studying Software Engineering at Tampere University Of Applied" << endl;
	Sleep(2000);
	cout << "Currently, I am looking for opportunities to enhance deeper understanding, develop skills and knowledge" << endl;
	Sleep(2000);
	cout << "in software development.I am hard working and determined terms of work. I am open for changes and" << endl;
	Sleep(2000);
	cout << "striving to learn new things" << endl;
	Sleep(2000);
	cout << "\nyou can contact me, send feedback, ask question or just say hello to me by one of the way below " << endl;
	Sleep(1000);
	cout << "\nLinkedin: www.linkedin.com/in/toan-tran-184b94207 " << endl;
	Sleep(1000);
	cout << "\nGithub: https://github.com/Toantranle " << endl;
	Sleep(1000);
	cout << "\nMy phone number: +358 468885032" << endl;
	Sleep(2500);
	cout << "\nAre you player, teacher or job recruiter??" << endl;
	Sleep(2500);
	cout << "\nWelcome to my world ^.^" << endl;
	Sleep(2500);
	cout << "\nThis is dungeons game where you will have your own advanture, there are Gem, Apple and Monster are waiting for you" << endl;
	Sleep(2500);
	cout << "\n And of course there are a lot of subprises waiting for you during the game" << endl;
	Sleep(2500);
	cout << "\nThis is my first game, I hope you will enjoy the game and good luck" << endl;
	Sleep(2500);
	cout << "\n>>>>>>>>>>>>>>>>>>>>>>> THANK YOU VERY MUCH <<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

}

void rule()
{
	system("CLS");
	cout << "A is Magic Apple, it will help you increase your energy" << endl;
	Sleep(2000);
	cout << "\nM is Monster, it will decrease your energy" << endl;
	Sleep(2000);
	cout << "\nG is Gem, the more gem you have the more point for you" << endl;
	Sleep(2000);
	cout << "\nD is Door, where you go to next level" << endl;
	Sleep(2000);
	cout << "\nP is player, it is you on the map" << endl;
	cout << endl;
	Sleep(2000);
	cout << "\n these are rule for happy phaying: " << endl;
	Sleep(2000);
	cout << "\na move left " << endl;
	cout << "s move down " << endl;
	cout << "d move right " << endl;
	cout << "w move up " << endl;
	cout << "q for quit game " << endl;
	Sleep(2000);
	cout << "\n- Game Over when your energy = 0 " << endl;
	Sleep(2000);
	cout << "\n- there will be more gem, magic apple, monter and bigger map when you go to higher level  " << endl;
	Sleep(2000);
	cout << "\n * NOTE: you have to collect gem in order to open the door for next level" << endl;
	Sleep(2000);
}

void first()
{
	system("CLS");
	cout << "                WELCOME TO HAPPY DUNGEONS VER 1.0 ^.^                  " << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "\nIntroduction" << endl;
	cout << "\nRules" << endl;
	cout << "\nGame Begin" << endl;
}

void nothing()
{
	vector<string> Toan;
	string first_line = "Entered the first cave.";
	Toan.push_back(first_line);
	Player p1(6, 6, 'P', 0, 500);
	map m(15, 15);
	begin(m, p1, Toan);

	while (m.getOK() == 1)
	{
		Player p2(6, 6, 'P', p1.getPoints(), p1.getEnergy());
		system("CLS");
		map m1(15 + m.getLevel(), 15 + m.getLevel());
		begin(m1, p2, Toan);
	}

	end_print(m, p1, Toan);
}

void again()
{
	vector<string> Toan;
	string first_line = "Entered the first cave.";
	Toan.push_back(first_line);
	Player p1(6, 6, 'P', 0, 200);
	map m1(15, 15);
	begin(m1, p1, Toan);

	while (m1.getOK() == 1)
	{
		Player p2(6, 6, 'P', p1.getPoints(), p1.getEnergy());
		system("CLS");
		map m2(15 + m1.getLevel(), 15 + m1.getLevel());
		begin(m2, p2, Toan);
	}

	end_print(m1, p1, Toan);
}

int main()
{
	//HANDLE  hColor;
	//hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hColor,FOREGROUND_GREEN);
	//Yellow
	char process = 'b';
	char step = 'b';
	srand(static_cast<unsigned int>(time(NULL)));

	cout << "                WELCOME TO HAPPY DUNGEONS VER 1.0 ^.^                  " << endl;

	while (step == 'b')
	{
		switch (process)
		{
		case'b':
			first();
			cout << "---------------------------------------------------------" << endl;
			cout << "\nIntroduction (i), Rules(r), Game Begin(g) or you want to quit game pls enter(q)" << endl;
			process = tolower(getch());
			break;
		case'i':
			Information();
			cout << "---------------------------------------------------------" << endl;
			cout << "Go back pls enter (b) or you want to quit game pls enter(q)" << endl;
			process = tolower(getch());
			break;
		case'r':
			rule();
			cout << "---------------------------------------------------------" << endl;
			cout << "Go back pls enter (b) or you want to quit game pls enter(q)" << endl;
			process = tolower(getch());
			break;
		case'g':
			system("CLS");
			nothing();
			step = 'q';
			break;
		case'q':
			step = 'q';
			break;
			break;
		default:
			cout << "---------------------------------------------------------" << endl;
			cout << "you want to quit game pls enter(q) or Go back pls enter (b) " << endl;
			process = tolower(getch());
			break;
		}
	}
	/*vector<string> Toan;
	string first_line = "Entered the first cave.";
	Toan.push_back(first_line);
	Player p1(6, 6, 'P', 0, 200);
	map m(15, 15);
	begin(m, p1, Toan);

	while (m.getOK() == 1)
	{
		Player p2(6, 6, 'P', p1.getPoints(), p1.getEnergy());
		system("CLS");
		map m1(15 + m.getLevel(), 15 + m.getLevel());
		begin(m1, p2, Toan);
	}

	end_print(m, p1, Toan);*/





	return 0;
}
