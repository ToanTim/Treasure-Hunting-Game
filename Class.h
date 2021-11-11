#pragma once


int rangeRandom(int min, int max);
void clearScreen();
class position {
private:

public:
	int x;
	int y;
	position(int x, int y);
	position();
	int getPositionX() const;
	int getPositionY() const;
};

class GameObject {
private:

	char symbol;

public:
	position p;
	GameObject(int x, int y, char symbol);
	GameObject();
	virtual void setPosition(int x, int y);
	position getPosition();
	virtual char getSympol() const;
	//virtual ~GameObject();

};

class Gem :public GameObject
{
private:


public:
	int point;
	static int gem_count;
	Gem(int poX, int poY, char symbol, int point);
	Gem();
	int getPoint() const;
	//void setPosition(int x, int y);
	//position getPosition();


};

class MagicApple :public GameObject
{
private:
	int energy;
public:
	MagicApple(int poX, int poY, char symbol, int energy);
	MagicApple();
	int getEnergy() const;

};


class Monster :public GameObject
{
private:
	int strength;
public:
	Monster(int poX, int poY, char symbol, int strength);
	Monster();
	//void setPosition(int x, int y);
	//int getPositionX();
	int getStrength() const;
};

class Player :public GameObject
{
private:

public:
	static int move_counter;
	static int gem_counter;
	static int point;
	static int energy;

	Player(int poX, int poY, char symbol, int point, int energy);
	Player();
	//void setPosition(int x, int y);
	//int getPositionX();
	int getPoints() const;
	int getEnergy() const;
	int getMoveCount() const;
	int getGemCounter() const;
	//int getEnergy() const;

};

class map :public GameObject, position
{
private:
	static int level;

public:
	static int ok;
	int height;
	int width;
	char** character;
	map(int width, int height);
	map();
	//void random();
	//void move_player(Monster* m, int m_size, Player& p, MagicApple* a, int a_size, Gem* g, int g_size);
	int getHeight() const;
	int getWidth() const;
	void mapSet();
	void print(Player& p);
	int getLevel() const;
	int getOK() const;
	~map();
};


