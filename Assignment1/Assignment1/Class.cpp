#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
#include "Class.h"

Form::Form(int year1, string roomNo1,  int numPupils1, string teacher1)
{
	year = year1;
	roomNo = roomNo1;
	setTeacher(teacher1);
	setNumPupils(numPupils1);
}
Form::Form(){}
int Form::getNumPupils()
{
	return numPupils;
}
void Form::setNumPupils(int num)
{
	numPupils = num;
}
string Form::getTeacher()
{
	return teacher;
}
void Form::setTeacher(string setTeacher)
{
	teacher = setTeacher;
}
void Form::addPupil(string surname1, string firstname1, char sex1, string birthDate1, 
	string addressLine1a, string addressLine2a, string postCode1, int i, char grade[])
{	
	this->child[i] = Pupil(surname1, firstname1, sex1, birthDate1, addressLine1a, addressLine2a, postCode1);
	for (int j = 0; j < MAXSUBJECTS; j++)
		this->child[i].setGrade(j, grade[j]);
	if (getNumPupils() == i)
		setNumPupils(getNumPupils() + 1);
}
void Form::removePupil(int i, Form object)
{
	for (int j = i; j < getNumPupils()-1; j++)
	{ 
		child[i] = child[j + 1];
	}
	setNumPupils(getNumPupils() - 1);
}
Pupil* Form::getFormPupils(int a)
{
	return &child[a];
}
Form::~Form(){ cout << "~Form removed\n"; };

Pupil::Pupil(string surname1, string firstname1, char sex1, string birthDate1, 
	string addressLine1a, string addressLine2a, string postCode1)
{
	surname = surname1;
	firstname = firstname1;
	sex = sex1;
	birthDate = birthDate1;
	addressLine1 = addressLine1a;
	addressLine2 = addressLine2a;
	postCode = postCode1;
}
Pupil::Pupil(){}
string Pupil::getName()
{
	return firstname+" "+surname;
}
string Pupil::getBirthDate()
{
	return birthDate;
}
char Pupil::getGrade(int i)
{
	return latestGrades[i];
}
void Pupil::setGrade(int i, char grade)
{
	latestGrades[i] = grade;
}
void Pupil::showAllGrades()
{
	for (int i = 0; i < MAXSUBJECTS; i++)
	{		
		cout << "Subject " << i + 1 << ": " << latestGrades[i] << "\n";
	}
}
string Pupil::getAddress()
{
	return addressLine1 +", "+ addressLine2+", "+postCode;
}
char Pupil::getGender()
{
	return sex;
}
Pupil::~Pupil(){/* cout << "\t~Pupil " << getName() << " has been removed\n";*/ };
//This doesnt work properly outputs for addPupil() and removePupil(), in an excessive way. 
//But doesnt output for the other function calls