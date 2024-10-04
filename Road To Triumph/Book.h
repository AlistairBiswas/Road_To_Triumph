#ifndef BUBBLE_H
#define BUBBLE_H

#define MAX_SCORE 50

typedef struct Book Book;

struct Book
{
	double posX, posY;
	int size;
	double speed;
	int index;
	int score;
	int count;
	double GPA;

	Book();
	Book(double posX, double speed, int index);
	~Book();

	void bookUpdate();
	void GPAcount();
};

unsigned int iLoadImage(char filename[]);
void initDeclare();
int lowestScore(Book book[]);
void bookImageLoad();
void book0Move();
void book1Move();
void book2Move();
void book3Move();
void book4Move();
void supplementaryMove();
void speedup();

#endif