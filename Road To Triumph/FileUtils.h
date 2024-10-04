#ifndef FILEUTILS_H
#define FILEUTILS_H

struct Info 
{
	char name[30];
	double cgpa;
	int totalMarks;

	Info();
	~Info();
};

void saveScore();
void loadScore();
void save();
void load();

#endif