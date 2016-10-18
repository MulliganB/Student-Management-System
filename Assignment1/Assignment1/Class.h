#include "stdafx.h"
#include <string>
#define MAXPUPIL 15
#define MAXSUBJECTS 5
using namespace std;

class Pupil
{
private:
	string surname;
	string firstname;
	char sex;
	string birthDate;
	string addressLine1;
	string addressLine2;
	string postCode;
	char latestGrades[MAXSUBJECTS];
public:
	Pupil(string, string, char, string, string, string, string);
	Pupil();
	string getName();
	string getBirthDate();
	char getGrade(int);
	void setGrade(int, char);
	void showAllGrades();
	string getAddress();
	char getGender();
	~Pupil();
	
};

class Form
{
private:
	int year;
	int numPupils;
	string roomNo;
	string teacher;
	Pupil child[MAXPUPIL];
public:
	Form(int, string, int, string);
	Form();
	int getNumPupils();
	void setNumPupils(int);
	string getTeacher();
	void setTeacher(string);
	void addPupil(string, string, char, string, string, string, string, int, char[]);
	void removePupil(int, Form);
	Pupil* getFormPupils(int);
	~Form();
};
