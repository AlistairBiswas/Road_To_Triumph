#ifndef INPUT_H
#define INPUT_H

#include "Book.h"

#include <Windows.h>
#include <ctype.h>
#include <time.h>

#define GLUT_LEFT_BUTTON		0
#define GLUT_MIDDLE_BUTTON		1
#define GLUT_RIGHT_BUTTON		2

#define GLUT_DOWN				0
#define GLUT_UP					1

#define GLUT_KEY_F1				1
#define GLUT_KEY_F2				2
#define GLUT_KEY_F3				3
#define GLUT_KEY_F4				4
#define GLUT_KEY_F5				5
#define GLUT_KEY_F6				6
#define GLUT_KEY_F7				7
#define GLUT_KEY_F8				8
#define GLUT_KEY_F9				9
#define GLUT_KEY_F10			10
#define GLUT_KEY_F11			11
#define GLUT_KEY_F12			12

#define GLUT_KEY_LEFT			100
#define GLUT_KEY_UP				101
#define GLUT_KEY_RIGHT			102
#define GLUT_KEY_DOWN			103
#define GLUT_KEY_PAGE_UP		104
#define GLUT_KEY_PAGE_DOWN		105
#define GLUT_KEY_HOME			106
#define GLUT_KEY_END			107
#define GLUT_KEY_INSERT			108

int iSetTimer(int msec, void (*f)(void));
void iPauseTimer(int index);
void iResumeTimer(int index);
void initDeclare();
int lowestScore(Book book[]);

#endif