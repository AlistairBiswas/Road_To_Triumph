#include "Input.h"
#include "Book.h"
#include "FileUtils.h"
#include "Menu.h"

extern int screenWidth, screenHeight;
extern double screenPosX, screenPosY;
extern int mousePosX, mousePosY;
extern int mouseMode;
extern bool typeMode;

extern Book book[5];
extern Book supplementary;
extern bool specialState;

extern char alphabet[];
extern char str[30];
extern char str2[30];
extern int len;
extern int menu;
extern int charLength;

void iMouseMove(int mx, int my)
{
}

void iPassiveMouse(int mx, int my)
{
	if ((mx >= screenPosX && mx + 17 <= screenWidth) && (my - 31 >= screenPosY && my <= screenHeight))
	{
		mousePosX = mx;
		mousePosY = my;
	}
	if (menu == MAIN_MENU)
	{
		if (((mx >= 675 && mx <= 846) && (my >= 506 && my <= 547)) || 
		    ((mx >= 670 && mx <= 847) && (my >= 422 && my <= 463)) ||
			((mx >= 676 && mx <= 844) && (my >= 334 && my <= 379)) || 
			((mx >= 670 && mx <= 848) && (my >= 254 && my <= 297)) || 
			((mx >= 709 && mx <= 812) && (my >= 170 && my <= 212)) || 
			((mx >= 725 && mx <= 791) && (my >= 86 && my <= 128)))
			mouseMode = CLICKABLE;
		else
			mouseMode = NON_CLICKABLE;
	}
	else if (menu == PAUSE_MENU)
	{
		if (((mx >= 653 && mx <= 825) && (my >= 453 && my <= 507)) || 
		    ((mx >= 653 && mx <= 825) && (my >= 383 && my <= 437)) ||
			((mx >= 653 && mx <= 825) && (my >= 311 && my <= 366)) || 
			((mx >= 653 && mx <= 825) && (my >= 240 && my <= 294)) || 
			((mx >= 653 && mx <= 825) && (my >= 168 && my <= 223)) || 
			((mx >= 653 && mx <= 825) && (my >= 96 && my <= 151)))
			mouseMode = CLICKABLE;
		else
			mouseMode = NON_CLICKABLE;
	}
	else if (menu == GAME_OVER)
	{
		if ((mx >= 112 && mx <= 409) && (my >= 404 && my <= 464))
			mouseMode = CLICKABLE;
		else
			mouseMode = NON_CLICKABLE;
	}
	else if (menu == CREDITS)
	{
		if (((mx >= 136 && mx <= 348) && (my >= 136 && my <= 151)) || 
			((mx >= 420 && mx <= 602) && (my >= 136 && my <= 152)) || 
			((mx >= 701 && mx <= 832) && (my >= 136 && my <= 153)))
			mouseMode = CLICKABLE;
		else
			mouseMode = NON_CLICKABLE;
	}
}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (menu == INTRO)
		{
			menu = MAIN_MENU;
		}
		else if (menu == MAIN_MENU)
		{
			if ((mx >= 675 && mx <= 846) && (my >= 506 && my <= 547))
			{
				initDeclare();
				menu = GAME;
			}
			else if ((mx >= 670 && mx <= 847) && (my >= 422 && my <= 463))
			{
				load();
				menu = GAME;
				iResumeTimer(0);
				iResumeTimer(1);
				iResumeTimer(2);
				iResumeTimer(3);
				iResumeTimer(4);
				iResumeTimer(5);
				iResumeTimer(6);
			}
			else if ((mx >= 676 && mx <= 844) && (my >= 334 && my <= 379))
			{
				loadScore();
				menu = SCORE_BOARD;
			}
			else if ((mx >= 670 && mx <= 848) && (my >= 254 && my <= 297))
			{
				menu = INSTRUCTIONS;
			}
			else if ((mx >= 709 && mx <= 812) && (my >= 170 && my <= 212))
			{
				menu = CREDITS;
			}
			else if ((mx >= 725 && mx <= 791) && (my >= 86 && my <= 128))
			{
				exit(0);
			}
		}
		else if (menu == GAME)
		{
			if ((mx >= 930 && mx <= 1012) && (my >= 554 && my <= 590))
			{
				iPauseTimer(0);
				iPauseTimer(1);
				iPauseTimer(2);
				iPauseTimer(3);
				iPauseTimer(4);
				iPauseTimer(5);
				iPauseTimer(6);
				menu = PAUSE_MENU;
			}
			if (!book[0].count && !book[1].count && !book[2].count && !book[3].count && !book[4].count)
			{
				menu = GAME_OVER;
			}
		}
		else if (menu == PAUSE_MENU)
		{
			if ((mx >= 653 && mx <= 825) && (my >= 453 && my <= 507))
			{
				menu = GAME;
				iResumeTimer(0);
				iResumeTimer(1);
				iResumeTimer(2);
				iResumeTimer(3);
				iResumeTimer(4);
				iResumeTimer(5);
				iResumeTimer(6);
			}
			else if ((mx >= 653 && mx <= 825) && (my >= 383 && my <= 437))
			{
				initDeclare();
				menu = GAME;
				iResumeTimer(0);
				iResumeTimer(1);
				iResumeTimer(2);
				iResumeTimer(3);
				iResumeTimer(4);
				iResumeTimer(5);
				iResumeTimer(6);
			}
			else if ((mx >= 653 && mx <= 825) && (my >= 311 && my <= 366))
			{
				save();
			}			
			else if ((mx >= 653 && mx <= 825) && (my >= 240 && my <= 294))
			{
				load();
				menu = GAME;
				iResumeTimer(0);
				iResumeTimer(1);
				iResumeTimer(2);
				iResumeTimer(3);
				iResumeTimer(4);
				iResumeTimer(5);
				iResumeTimer(6);
			}			
			else if ((mx >= 653 && mx <= 825) && (my >= 168 && my <= 223))
				menu = MAIN_MENU;
			else if ((mx >= 653 && mx <= 825) && (my >= 96 && my <= 151))
				exit(0);
		}
		else if (menu == GAME_OVER)
		{
			if ((mx >= 112 && mx <= 409) && (my >= 404 && my <= 464) && !typeMode)
				typeMode = true;
			else
				typeMode = false;
		}
		else if (menu == CERTIFICATE)
		{
			menu = SCORE_BOARD;
		}
		else if (menu == SCORE_BOARD)
		{
			if ((mx >= 810 && mx <= 928) && (my >= 524 && my <= 563))
				menu = MAIN_MENU;
		}
		else if (menu == INSTRUCTIONS)
		{
			if ((mx >= 41 && mx <= 144) && (my >= 468 && my <= 539))
				menu = MAIN_MENU;
		}
		else if (menu == CREDITS)
		{
			if ((mx >= 136 && mx <= 348) && (my >= 136 && my <= 151))
				system("START https://www.github.com/SyedMashruk");
			else if ((mx >= 420 && mx <= 602) && (my >= 136 && my <= 152))
				system("START https://www.github.com/rafi99-bat");
			else if ((mx >= 701 && mx <= 832) && (my >= 136 && my <= 153))
				system("START https://www.github.com/alistairrr");
			else if ((mx >= 25 && mx <= 149) && (my >= 540 && my <= 589))
				menu = MAIN_MENU;
		}
	}
	if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

void iKeyboard(unsigned char key)
{
	if (menu == INTRO)
	{
		menu = MAIN_MENU;
	}
	else if (menu == GAME)
	{
		if (key == 'a')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'b')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'c')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'd')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'e')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'f')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'g')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'h')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'i')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'j')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'k')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'l')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'm')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'n')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'o')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'p')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'q')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'r')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 's')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 't')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'u')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'v')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'w')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'x')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'y')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == 'z')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == ',')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == ';')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == '=')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == '!')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == '&')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == '*')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == '#')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == '%')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == '(')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == ')')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == '{')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == '}')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		else if (key == '-')
		{
			if (alphabet[supplementary.index] == key && (supplementary.posY >= -supplementary.size && supplementary.posY - 40 <= screenHeight))
			{
				supplementary.count--;
				int min = lowestScore(book);
				for (int i = 0; i < 5; i++)
				{
					if (book[i].score == min)
					{
						if (book[i].score <= 97)
						{
							book[i].score += supplementary.score;
							break;
						}
					}
				}
				supplementary.posY = -300;
				supplementary.index = rand() % charLength;
				specialState = false;
			}
			else if (alphabet[book[0].index] == key && (book[0].posY >= -book[0].size && book[0].posY - 40 <= screenHeight))
			{
				book[0].posX = 313;
				book[0].bookUpdate();
				book[0].index = rand() % (charLength / 5);
			}
			else if (alphabet[book[1].index] == key && (book[1].posY >= -book[1].size && book[1].posY - 40 <= screenHeight))
			{
				book[1].posX = 455;
				book[1].bookUpdate();
				book[1].index = (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[2].index] == key && (book[2].posY >= -book[2].size && book[2].posY - 40 <= screenHeight))
			{
				book[2].posX = 597;
				book[2].bookUpdate();
				book[2].index = 2 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[3].index] == key && (book[3].posY >= -book[3].size && book[3].posY - 40 <= screenHeight))
			{
				book[3].posX = 739;
				book[3].bookUpdate();
				book[3].index = 3 * (charLength / 5) + rand() % (charLength / 5);
			}
			else if (alphabet[book[4].index] == key && (book[4].posY >= -book[4].size && book[4].posY - 40 <= screenHeight))
			{
				book[4].posX = 881;
				book[4].bookUpdate();
				book[4].index = 4 * (charLength / 5) + rand() % (charLength / 5);
			}
		}
		if (key == 27)
		{
			iPauseTimer(0);
			iPauseTimer(1);
			iPauseTimer(2);
			iPauseTimer(3);
			iPauseTimer(4);
			iPauseTimer(5);
			iPauseTimer(6);
			menu = PAUSE_MENU;
		}
	}
	else if (menu == INSTRUCTIONS)
	{
	}
	else if (menu == PAUSE_MENU)
	{
		if (key == 27)
		{
			menu = GAME;
			iResumeTimer(0);
			iResumeTimer(1);
			iResumeTimer(2);
			iResumeTimer(3);
			iResumeTimer(4);
			iResumeTimer(5);
			iResumeTimer(6);
		}
	}
	else if (menu == GAME_OVER)
	{
		if (typeMode)
		{
			if (key == '\r')
			{
				saveScore();
				typeMode = false;
				for(int i = 0; i < len; i++)
					str2[i] = 0;
				len = 0;
				if (book[0].score >= 80 && book[1].score >= 80 && book[2].score >= 80 && book[3].score >= 80 && book[4].score >= 80)
					menu = CERTIFICATE;
				else
					menu = SCORE_BOARD;
			}
			else if(key == '\b')
			{
				if(len!=0)
					len--;
				str2[len] = 0;
			}
			else
			{
				str2[len] = key;
				len++;
			}
		}
		else
		{
			if (len > 0)
			{
				if (key == '\r')
					menu = SCORE_BOARD;
			}
		}
	}
	else if (menu == CERTIFICATE)
	{
		menu = SCORE_BOARD;
	}
	else if (menu == CREDITS)
	{
		if (key == '\b')
		{
			menu = MAIN_MENU;
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if(key == GLUT_KEY_END)
	{
		
	}
	if(key == GLUT_KEY_LEFT)
	{

	}
	if(key == GLUT_KEY_RIGHT)
	{

	}
	if(key == GLUT_KEY_UP)
	{

	}
	if(key == GLUT_KEY_DOWN)
	{

	}
}