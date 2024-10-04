#ifndef RENDER_H
#define RENDER_H

#include <glut.h>

void iShowBMP2(int x, int y, char filename[], int ignoreColor);
void iShowBMP(int x, int y, char filename[]);
unsigned int iLoadImage(char filename[]);
void iShowImage(int x, int y, int width, int height, unsigned int texture);
void iText(GLdouble x, GLdouble y, char *str, void* font = GLUT_BITMAP_8_BY_13);
void iLine(double x1, double y1, double x2, double y2);
void iFilledRectangle(double left, double bottom, double dx, double dy);
void iSetColor(double r, double g, double b);
void iClear();
void scoring();
void showResult();
void showCertificate();
void showScoreBoard();
void showCursor();
void bookRender();
void iDraw();

#endif