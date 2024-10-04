#include "Menu.h"
#include "Book.h"

#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int book0, book1, book2, book3, book4, notes;
extern int menu;
extern int screenWidth;
extern int screenHeight;
extern int charLength;
extern int max;
extern bool specialState;

Book::Book()
{
}

Book::Book(double posX, double speed, int index)
{
	this->posX = posX;
	posY = -size - rand() % 300;
	size = 85;
	this->speed = speed;
	this->index = index;
	score = 0;
	count = MAX_SCORE + 1;
	GPA = 0.00;
}

Book::~Book()
{
}

void Book::bookUpdate()
{
	if (score <= 98)
		score += 2;
	if (count != 0)
		count--;
	posY = -size - rand() % 300;
}

void Book::GPAcount()
{
	if (score >= 80)
		GPA = 4.00;
	else if (score < 80 && score >= 75)
		GPA = 3.75;
	else if (score < 75 && score >= 70)
		GPA = 3.50;
	else if (score < 70 && score >= 65)
		GPA = 3.25;
	else if (score < 65 && score >= 60)
		GPA = 3.00;
	else if (score < 60 && score >= 55)
		GPA = 2.75;
	else if (score < 55 && score >= 50)
		GPA = 2.50;
	else if (score < 50 && score >= 45)
		GPA = 2.25;
	else if (score < 45 && score >= 40)
		GPA = 2.00;
	else
		GPA = 0.00;
}

extern Book book[5];
extern Book supplementary;

void initDeclare()
{
	book[0] = Book(313, 1, rand() % (charLength / 5));
	book[1] = Book(455, 1, (charLength / 5) + rand() % (charLength / 5));
	book[2] = Book(597, 1, 2 * (charLength / 5) + rand() % (charLength / 5));
	book[3] = Book(739, 1, 3 * (charLength / 5) + rand() % (charLength / 5));
	book[4] = Book(881, 1, 4 * (charLength / 5) + rand() % (charLength / 5));
	supplementary.posX = 171 + rand() % 853;
	supplementary.posY = -300;
	supplementary.speed = 3;
	supplementary.index = rand() % charLength;
	supplementary.count = 40;
	supplementary.score = 4;
}

int lowestScore(Book book[])
{
	int min = book[0].score;
	for(int i = 0; i < 5; i++){
		if(book[i].score < min){
			min = book[i].score;
		}
	}
	return min;
}

void bookImageLoad()
{
	book0 = iLoadImage("res/images/red.png");
	book1 = iLoadImage("res/images/blue.png");
	book2 = iLoadImage("res/images/green.png");
	book3 = iLoadImage("res/images/yellow.png");
	book4 = iLoadImage("res/images/violet.png");
	notes = iLoadImage("res/images/notes1.png");
}

void book0Move()
{	
	if (menu == GAME)
	{
		if (book[0].posY - 40 > screenHeight)
		{
			if (book[0].count)
			{
				book[0].count--;
				book[0].posX = 313;
				book[0].posY = -book[0].size - rand() % 300;
				book[0].index = rand() % (charLength / 5);
			}
		}
		else if (book[0].posY - 40 <= screenHeight)
		{
			book[0].posY += book[0].speed;
		}
	}
}

void book1Move()
{
	if (menu == GAME)
	{
		if (book[1].posY - 40 > screenHeight)
		{
			if (book[1].count)
			{
				book[1].count--;
				book[1].posX = 455;
				book[1].posY = -book[1].size - rand() % 300;
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (book[1].posY - 40 <= screenHeight)
		{
			book[1].posY += book[1].speed;
		}
	}
}

void book2Move()
{
	if (menu == GAME)
	{
		if (book[2].posY - 40 > screenHeight)
		{
			if (book[2].count)
			{
				book[2].count--;
				book[2].posX = 597;
				book[2].posY = -book[2].size - rand() % 300;
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (book[2].posY - 40 <= screenHeight)
		{
			book[2].posY += book[2].speed;
		}
	}
}

void book3Move()
{
	if (menu == GAME)
	{
		if (book[3].posY - 40 > screenHeight)
		{
			if (book[3].count)
			{
				book[3].count--;
				book[3].posX = 739;
				book[3].posY = -book[3].size - rand() % 300;
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (book[3].posY - 40 <= screenHeight)
		{
			book[3].posY += book[3].speed;
		}
	}
}

void book4Move()
{
	if (menu == GAME)
	{
		if (book[4].posY - 40 > screenHeight)
		{
			if (book[4].count)
			{
				book[4].count--;
				book[4].posX = 881;
				book[4].posY = -book[4].size - rand() % 300;
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (book[4].posY - 40 <= screenHeight)
		{
			book[4].posY += book[4].speed;
		}
	}
}

void supplementaryMove()
{	
	if (menu == GAME)
	{
		for (int i = 0; i < 5; i++)
		{
			if ((book[i].score == 20 || book[i].score == 40 || book[i].score == 60) && book[i].score > max)
			{
				specialState = true;
				max = book[i].score;
			}
		}
		if (specialState)
		{
			if (!book[0].count && !book[1].count && !book[2].count && !book[3].count && !book[4].count)
			{
				supplementary.count = 0;
			}
			if (supplementary.posY - 40 > screenHeight)
			{
				if (supplementary.count)
				{
					specialState = false;
					supplementary.count--;
					supplementary.posX = 171 + rand() % 853;
					supplementary.posY = -300;
					supplementary.index = rand() % charLength;
				}
			}
			else if (supplementary.posY - 40 <= screenHeight)
			{
				supplementary.posY += supplementary.speed;
			}
		}
	}
}

void speedup()
{
	if (book[0].score <= 40)
		book[0].speed += 0.25;
	else if (book[0].score > 40 && book[0].score <= 60)
		book[0].speed += 0.5;
	else
		book[0].speed += 0.75;

	if (book[1].score <= 40)
		book[1].speed += 0.25;
	else if (book[1].score > 40 && book[1].score <= 60)
		book[1].speed += 0.5;
	else
		book[1].speed += 0.75;

	if (book[2].score <= 40)
		book[2].speed += 0.25;
	else if (book[2].score > 40 && book[2].score <= 60)
		book[2].speed += 0.5;
	else
		book[2].speed += 0.75;

	if (book[3].score <= 40)
		book[3].speed += 0.25;
	else if (book[3].score > 40 && book[3].score <= 60)
		book[3].speed += 0.5;
	else
		book[3].speed += 0.75;

	if (book[4].score <= 40)
		book[4].speed += 0.25;
	else if (book[4].score > 40 && book[4].score <= 60)
		book[4].speed += 0.5;
	else
		book[4].speed += 0.75;
}