#include "Book.h"
#include "Menu.h"
#include "Render.h"
#include "FileUtils.h"

#include <stdio.h>
#include <time.h>
#include <string.h>

extern int screenWidth;
extern int screenHeight;
extern double screenPosX;
extern double screenPosY;
extern int mousePosX, mousePosY;
extern int mouseMode;
extern bool typeMode;
extern int max;

extern Book book[5];
extern Book supplementary;
extern bool specialState;
extern Info info[5];

extern int book0, book1, book2, book3, book4, notes;
extern int score;
extern char alphabet[];
extern char playerName[30];
extern char str[30];
extern char str2[30];
extern char buffer[2];
extern int len;
extern int menu;
extern int charLength;

void scoring()
{
	iSetColor(0, 0, 0);
	sprintf(str, "%d", book[0].score);
	iText(80, 483, str, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(str, "%d", book[1].score);
	iText(80, 453, str, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(str, "%d", book[2].score);
	iText(80, 424, str, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(str, "%d", book[3].score);
	iText(80, 395, str, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(str, "%d", book[4].score);
	iText(80, 367, str, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(str, "%d", book[0].count);
	iText(80, 216, str, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(str, "%d", book[1].count);
	iText(80, 186, str, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(str, "%d", book[2].count);
	iText(80, 156, str, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(str, "%d", book[3].count);
	iText(80, 126, str, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(str, "%d", book[4].count);
	iText(80, 96, str, GLUT_BITMAP_TIMES_ROMAN_24);
}

void showResult()
{
	iShowBMP(screenPosX, screenPosY, "res/images/result.bmp");
	book[0].GPAcount();
	book[1].GPAcount();
	book[2].GPAcount();
	book[3].GPAcount();
	book[4].GPAcount();
	iSetColor(0, 0, 0);
	sprintf(str, "%.2lf", (book[0].GPA + book[1].GPA + book[2].GPA + book[3].GPA + book[4].GPA) / 5);
	iText(617, 420, str, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(str, "%d / 100", book[0].score);
	iText(675, 292, str, GLUT_BITMAP_HELVETICA_18);
	sprintf(str, "%d / 100", book[1].score);
	iText(675, 246, str, GLUT_BITMAP_HELVETICA_18);
	sprintf(str, "%d / 100", book[2].score);
	iText(675, 200, str, GLUT_BITMAP_HELVETICA_18);
	sprintf(str, "%d / 100", book[3].score);
	iText(675, 153, str, GLUT_BITMAP_HELVETICA_18);
	sprintf(str, "%d / 100", book[4].score);
	iText(675, 110, str, GLUT_BITMAP_HELVETICA_18);
	sprintf(str, "%d / 500", (book[0].score + book[1].score + book[2].score + book[3].score + book[4].score));
	iText(675, 50, str, GLUT_BITMAP_HELVETICA_18);
	int failed = iLoadImage("res/images/fail.png");
	if (book[0].score < 40)
		iShowImage(860, 285, 80, 29, failed);
	if (book[1].score < 40)
		iShowImage(860, 240, 80, 29, failed);
	if (book[2].score < 40)
		iShowImage(860, 193, 80, 29, failed);
	if (book[3].score < 40)
		iShowImage(860, 147, 80, 29, failed);
	if (book[4].score < 40)
		iShowImage(860, 100, 80, 29, failed);
	if (typeMode)
	{
		strcpy(playerName, str2);
		strcpy(str, str2);
		strcat(str, "|");
		iText(135, 421, str, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else
	{
		if (len == 0)
		{
			iSetColor(150, 150, 150);
			iText(135, 422, "Enter Your Name", GLUT_BITMAP_HELVETICA_18);
		}
		else
		{
			iSetColor(0, 0, 0);
			iText(135, 421, playerName, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
}

void showCertificate()
{
	iShowBMP(screenPosX, screenPosY, "res/images/certificate.bmp");
	iSetColor(0, 0, 0);
	strcpy(str, playerName);
	strupr(str);
	iText(405, 300, str, GLUT_BITMAP_TIMES_ROMAN_24);
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(str, "%02d", tm.tm_mday);
	iText(213, 118, str, GLUT_BITMAP_HELVETICA_18);
	sprintf(str, "%02d", tm.tm_mon + 1);
	iText(254, 118, str, GLUT_BITMAP_HELVETICA_18);
	sprintf(str, "%d", tm.tm_year + 1900);
	iText(296, 118, str, GLUT_BITMAP_HELVETICA_18);
	iSetColor(131, 139, 56);
	iText(435, 56, "Press any key to continue", GLUT_BITMAP_HELVETICA_12);
}

void showScoreBoard()
{
	iShowBMP(screenPosX, screenPosY, "res/images/score-board.bmp");
	iSetColor(0, 0, 0);
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(str, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	iText(780, 460, str, GLUT_BITMAP_HELVETICA_12);

	iText(186, 324, info[0].name, GLUT_BITMAP_HELVETICA_18);
	iText(186, 296, info[1].name, GLUT_BITMAP_HELVETICA_18);
	iText(186, 268, info[2].name, GLUT_BITMAP_HELVETICA_18);
	iText(186, 241, info[3].name, GLUT_BITMAP_HELVETICA_18);
	iText(186, 212, info[4].name, GLUT_BITMAP_HELVETICA_18);

	sprintf(str, "%.3lf", info[0].cgpa);
	iText(645, 324, str, GLUT_BITMAP_HELVETICA_18);
	sprintf(str, "%.3lf", info[1].cgpa);
	iText(645, 296, str, GLUT_BITMAP_HELVETICA_18);
	sprintf(str, "%.3lf", info[2].cgpa);
	iText(645, 268, str, GLUT_BITMAP_HELVETICA_18);
	sprintf(str, "%.3lf", info[3].cgpa);
	iText(645, 241, str, GLUT_BITMAP_HELVETICA_18);
	sprintf(str, "%.3lf", info[4].cgpa);
	iText(645, 212, str, GLUT_BITMAP_HELVETICA_18);
}

void showCursor()
{
	glutSetCursor(GLUT_CURSOR_NONE);
	iShowImage(mousePosX, mousePosY - 31, 30, 30, iLoadImage("res/images/cursor.png"));
}

void bookRender()
{
	bookImageLoad();
	if (book[0].count)
	{
		iShowImage(book[0].posX - 35, book[0].posY - 40, 80, 84, book0);
		iSetColor(0, 0, 0);
		sprintf(buffer, "%c", alphabet[book[0].index]);
		iText(book[0].posX - 10, book[0].posY - 8, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if (book[1].count)
	{
		iShowImage(book[1].posX - 35, book[1].posY - 40, 80, 84, book1);
		iSetColor(0, 0, 0);
		sprintf(buffer, "%c", alphabet[book[1].index]);
		iText(book[1].posX - 10, book[1].posY - 8, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if (book[2].count)
	{
		iShowImage(book[2].posX - 35, book[2].posY - 40, 80, 84, book2);
		iSetColor(0, 0, 0);
		sprintf(buffer, "%c", alphabet[book[2].index]);
		iText(book[2].posX - 10, book[2].posY - 8, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if (book[3].count)
	{
		iShowImage(book[3].posX - 35, book[3].posY - 40, 80, 84, book3);
		iSetColor(0, 0, 0);
		sprintf(buffer, "%c", alphabet[book[3].index]);
		iText(book[3].posX - 10, book[3].posY - 8, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if (book[4].count)
	{
		iShowImage(book[4].posX - 35, book[4].posY - 40, 80, 84, book4);
		iSetColor(0, 0, 0);
		sprintf(buffer, "%c", alphabet[book[4].index]);
		iText(book[4].posX - 10, book[4].posY - 10, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if (supplementary.count && specialState)
	{
		iShowImage(supplementary.posX - 35, supplementary.posY - 40, 80, 84, notes);
		iSetColor(0, 0, 0);
		sprintf(buffer, "%c", alphabet[supplementary.index]);
		iText(supplementary.posX - 10, supplementary.posY - 10, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void iDraw()
{
	iClear();
	if (menu == INTRO)
	{
		iShowBMP(screenPosX, screenPosY, "res/images/intro.bmp");
		showCursor();
	}
	if (menu == MAIN_MENU)
	{
		iShowBMP(screenPosX, screenPosY, "res/images/menu.bmp");
		if (mouseMode == CLICKABLE)
		{
			iSetColor(99, 98, 98);
			if ((mousePosX >= 675 && mousePosX <= 846) && (mousePosY >= 506 && mousePosY <= 547))
				iLine(675, 509, 847, 509);
			else if ((mousePosX >= 670 && mousePosX <= 847) && (mousePosY >= 422 && mousePosY <= 463))
				iLine(672, 426, 846, 426);
			else if ((mousePosX >= 676 && mousePosX <= 844) && (mousePosY >= 334 && mousePosY <= 379))
				iLine(677, 340, 844, 340);
			else if ((mousePosX >= 670 && mousePosX <= 848) && (mousePosY >= 254 && mousePosY <= 297))
				iLine(671, 258, 847, 258);
			else if ((mousePosX >= 709 && mousePosX <= 812) && (mousePosY >= 170 && mousePosY <= 212))
				iLine(709, 172, 812, 172);
			else if ((mousePosX >= 725 && mousePosX <= 791) && (mousePosY >= 86 && mousePosY <= 128))
				iLine(724, 88, 791, 88);
		}
		showCursor();
	}
	if (menu == GAME)
	{
		iShowBMP(screenPosX, screenPosY, "res/images/game.bmp");
		bookRender();
		scoring();
		if (!book[0].count && !book[1].count && !book[2].count && !book[3].count && !book[4].count)
		{
			iShowBMP(screenPosX, screenPosY, "res/images/image.bmp");
			iShowImage(337, 260, 350, 110, iLoadImage("res/images/gameover.png"));
			iSetColor(0, 0, 0);
			iText(468, 265, "Click to continue", GLUT_BITMAP_HELVETICA_12);
		}
		showCursor();
	}
	if (menu == PAUSE_MENU)
	{
		iShowBMP(screenPosX, screenPosY, "res/images/PauseMenu(255).bmp");
		if (mouseMode == CLICKABLE)
		{
			iSetColor(0, 0, 0);
			if ((mousePosX >= 653 && mousePosX <= 825) && (mousePosY >= 453 && mousePosY <= 507))
				iLine(688, 467, 790, 467);
			else if ((mousePosX >= 653 && mousePosX <= 825) && (mousePosY >= 383 && mousePosY <= 437))
				iLine(684, 397, 788, 397);
			else if ((mousePosX >= 653 && mousePosX <= 825) && (mousePosY >= 311 && mousePosY <= 366))
				iLine(706, 324, 772, 324);
			else if ((mousePosX >= 653 && mousePosX <= 825) && (mousePosY >= 240 && mousePosY <= 294))
				iLine(700, 253, 775, 253);
			else if ((mousePosX >= 653 && mousePosX <= 825) && (mousePosY >= 168 && mousePosY <= 223))
				iLine(662, 183, 816, 183);
			else if ((mousePosX >= 653 && mousePosX <= 825) && (mousePosY >= 96 && mousePosY <= 151))
				iLine(710, 107, 764, 107);
		}
		showCursor();
	}
	if (menu == GAME_OVER)
	{
		showResult();
		if (mouseMode == CLICKABLE)
			glutSetCursor(GLUT_CURSOR_TEXT);
		else
			showCursor();
	}
	if (menu == CERTIFICATE)
	{
		showCertificate();
		showCursor();
	}
	if (menu == SCORE_BOARD)
	{
		showScoreBoard();
		showCursor();
	}
	if (menu == INSTRUCTIONS)
	{
		iShowBMP(screenPosX, screenPosY, "res/images/Handbook.bmp");
		showCursor();
	}
	if (menu == CREDITS)
	{
		iShowBMP(screenPosX, screenPosY, "res/images/Credit.bmp");
		if (mouseMode == CLICKABLE)
		{
			iSetColor(255, 255, 255);
			if ((mousePosX >= 136 && mousePosX <= 348) && (mousePosY >= 136 && mousePosY <= 151))
				iLine(138, 134, 348, 134);
			else if ((mousePosX >= 420 && mousePosX <= 602) && (mousePosY >= 136 && mousePosY <= 152))
				iLine(422, 134, 602, 134);
			else if ((mousePosX >= 701 && mousePosX <= 832) && (mousePosY >= 136 && mousePosY <= 153))
				iLine(702, 136, 834, 136);
		}
		showCursor();
	}
}