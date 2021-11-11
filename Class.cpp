#include<iostream>
#include"Class.h"
#include<string>
#include<ctime>
#include<stdlib.h>
#include<Windows.h>
using namespace std;

// Class position

position::position(int x, int y)
{
	this->y = y;
	this->x = x;
}

position::position()
{
	this->y = 0;
	this->x = 0;
}

int position::getPositionX() const
{
	return x;
}

int position::getPositionY() const
{
	return y;
}

//-----------------------------------

//Class GameObject

GameObject::GameObject(int x, int y, char symbol)
{
	this->p.x = x;
	this->p.y = y;
	this->symbol = symbol;
}

GameObject::GameObject()
{
	this->p.x = 0;
	this->p.y = 0;
	this->symbol = ' ';
}


void GameObject::setPosition(int poX, int poY)
{
	position(poX, poY);
}

char GameObject::getSympol() const {
	return symbol;
}

position GameObject::getPosition()
{
	return this->p;
}

/*
int GameObject::getPosition() const
{
	return p.getPositionX();
}
*/

//------------------------------------------

//Class Gem

int Gem::gem_count = 0;

Gem::Gem(int poX, int poY, char symbol, int point) :GameObject(poX, poY, symbol)
{
	this->point = point;
	gem_count++;
}

Gem::Gem()
{
	point = 0;
}

int Gem::getPoint() const
{
	return point;
}


//--------------------------------------------------

//Class MagicApple

MagicApple::MagicApple(int poX, int poY, char symbol, int energy) :GameObject(poX, poY, symbol)
{
	this->energy = energy;
}

MagicApple::MagicApple()
{
	this->energy = 0;
}

int MagicApple::getEnergy() const

{
	return energy;
}

//---------------------------------

//Class Monster

Monster::Monster(int poX, int poY, char symbol, int strength) :GameObject(poX, poY, symbol)
{
	this->strength = strength;
}

Monster::Monster()
{
	this->strength = 0;
}

int Monster::getStrength() const
{
	return strength;
}


//-------------------------------------------------



//-------------------------------------------------------------

// class player
Player::Player()
{
	this->point = 0;

}

Player::Player(int poX, int poY, char symbol, int point, int energy) :GameObject(poX, poY, symbol)
{
	this->point = point;
	this->energy = energy;
}

int Player::getEnergy() const
{
	return energy;
}

int Player::getPoints() const
{
	return point;
}

int Player::getMoveCount() const
{
	return move_counter;
}

int Player::getGemCounter() const
{
	return gem_counter;
}

int Player::energy = 0;
int Player::point = 0;
int Player::move_counter = 0;
int Player::gem_counter = 0;

//---------------------------------------------
//Class map
int map::level = 0;
int map::ok = 0;

map::map(int width, int height)
{
	this->width = width;
	this->height = height;
	//this->level = level;
}

map::map()
{
	this->width = 0;
	this->height = 0;
	this->level = 0;
}


int map::getHeight() const
{
	return height;
}

int map::getWidth() const
{
	return width;
}

void map::mapSet()
{

	level++;
	int height = getHeight();
	int width = getWidth();
	int nothing;
	//-------------------------------------------------------
	/*
	int m_size = 2 + getLevel();
	int a_size = 2 + getLevel();
	int g_size = 2 + getLevel();
	Monster* m_group = new Monster[m_size];
	MagicApple* a_group = new MagicApple[a_size];
	Gem* g_group = new Gem[g_size];


	for (int i = 0; i < m_size; i++)
	{
		int random_x = rangeRandom(2, width - 2);
		int random_y = rangeRandom(2, height - 2);
		m_group[i] = Monster(random_x, random_y, 'M', 5);
	}


	for (int i = 0; i < a_size; i++)
	{
		int random_x = rangeRandom(2, width - 2);
		int random_y = rangeRandom(2, height - 2);


		a_group[i] = MagicApple(random_x, random_y, 'A', 10);
	}

	for (int i = 0; i < g_size; i++)
	{
		int random_x = rangeRandom(2, width - 2);
		int random_y = rangeRandom(2, height - 2);


		g_group[i] = Gem(random_x, random_y, 'G', 5);
	}

	//------------------------------------------------------

	position* m_po = new position[m_size];
	position* a_po = new position[a_size];
	position* g_po = new position[g_size];
	for (int i = 0; i < a_size; i++)
	{
		m_po[i] = m_group[i].getPosition();
		a_po[i] = a_group[i].getPosition();
		g_po[i] = g_group[i].getPosition();

	}


	for (int i = 0; i < a_size; i++)
	{
		character[m_po[i].x - 1][m_po[i].y - 1] = m_group[i].getSympol();
		character[a_po[i].x - 1][a_po[i].y - 1] = a_group[i].getSympol();
		character[g_po[i].x - 1][g_po[i].y - 1] = g_group[i].getSympol();
	}



	//-----------------------------------------------------
	*/
	if (width < height)
	{
		nothing = width;
		width = height;
		height = nothing;
	}

	int different = width - height;
	character = new char* [width];
	for (int a = 0; a < width; a++)
	{
		character[a] = new char[height];
	}



	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i == 0 || i == (height + different - 1))
			{
				character[i][j] = 'X';
			}
			else if (j == 0 || j == (width - different - 1))
			{
				character[i][j] = 'X';
			}
			else
			{

				//int random = rand() % 8;
				if (i % 2 == 0 && j % 2 == 0)
				{
					character[i][j] = 'X';
				}
				else
				{
					character[i][j] = '.';
				}

			}
		}
	}
	/*
	for (int i = 0; i < a_size; i++)
	{
		character[m_po[i].x - 1][m_po[i].y - 1] = m_group[i].getSympol();
		character[a_po[i].x - 1][a_po[i].y - 1] = a_group[i].getSympol();
		character[g_po[i].x - 1][g_po[i].y - 1] = g_group[i].getSympol();
	}
	/*
	//----------------------------------
	delete[] m_group;
	delete[] a_group;
	delete[] g_group;
	//----------------------------------
	delete[] m_po;
	delete[] a_po;
	delete[] g_po;
	*/


}

int map::getLevel() const
{
	return level;
}

int map::getOK() const
{
	return ok;
}
//void map::move_player(Monster* m, int m_size, Player& p, MagicApple* a, int a_size, Gem* g, int g_size)
//{
//
//	position* m_po = new position[m_size];
//	position* a_po = new position[a_size];
//	position* g_po = new position[g_size];
//	for (int i = 0; i < a_size; i++)
//	{
//		m_po[i] = m[i].getPosition();
//		a_po[i] = a[i].getPosition();
//		g_po[i] = g[i].getPosition();
//
//	}
//
//	position pos_p = p.getPosition();
//
//	for (int i = 0; i < a_size; i++)
//	{
//		character[a_po[i].x - 1][a_po[i].y - 1] = a[i].getSympol();
//	}
//
//	for (int i = 0; i < m_size; i++)
//	{
//		character[m_po[i].x - 1][m_po[i].y - 1] = m[i].getSympol();
//	}
//
//	for (int i = 0; i < g_size; i++)
//	{
//		character[g_po[i].x - 1][g_po[i].y - 1] = g[i].getSympol();
//	}
//
//	character[pos_p.x - 1][pos_p.y - 1] = p.getSympol();
//
//	delete[] m_po;
//	delete[] a_po;
//	delete[] g_po;
//}


//player p for print enery and point
void map::print(Player& p)
{
	if (p.getEnergy() > 0)
	{
		Gem* g;
		cout << g->gem_count << endl;
		cout << "Level : " << level << ": player energy : " << p.getEnergy() << " ;points: " << p.getPoints() << endl;
		int nothing;
		if (width < height)
		{
			nothing = width;
			width = height;
			height = nothing;
		}

		cout << "map " << to_string(width) << "*" << to_string(height) << endl;
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				cout << character[i][j];
			}
			cout << endl;
		}
	}
	else if (p.getEnergy() == 0)
	{
		system("CLS");
		cout << endl;
		cout << endl;
		cout << endl;

	}

}

map::~map()
{
	for (int i = 0; i < width; i++)
		delete[] character[i];

	delete[] character;

}
