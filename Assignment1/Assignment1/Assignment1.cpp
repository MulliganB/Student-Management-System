#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
#include "Class.h"

char getCommand(char&);
void commandSelection(char&, Form&);
void populateForm1(string, string, char, string, string, string, string, Form&);
void populateForm2(string, string, char, string, string, string, string, Form&);
void populateForm3(string, string, char, string, string, string, string, Form&);
void updateFileAdd(fstream, Form&, char);
void updateFileRemove(Form&, char);
void enterPupil(Form&, char);
void removePupil(Form&, Form&, Form&, char, int&);
void displayNumOfPupils(Form&);
void displayClassInformation(Form&);
void displayNumOfMales(Form&);
void displayNumOfFemales(Form&);
bool findSpecificPupil(Form&, Form&, Form&, int&, char&);
void displayLatestMarkForPupil(Form&, Form&, Form&, int&, char);
void displayFullAddress(Form&, Form&, Form&, int&, char);
void quit(char&);

int main()
{
	fstream pupilFile;
	char command = 0;
	string surname1;
	string firstname1;
	char sex1 = 'm';
	string birthDate1;
	string addressLine1a;
	string addressLine2a;
	string postCode1;
	int numPupils = 0;
	string roomNo;
	string teacher;
	char selection = ' ';
	Form class1;
	Form class2;
	Form class3;
	int location = 0;

	//Populating all the forms with corresponding files
	populateForm1(surname1, firstname1, sex1, birthDate1, addressLine1a, addressLine2a, postCode1, class1);
	populateForm2(surname1, firstname1, sex1, birthDate1, addressLine1a, addressLine2a, postCode1, class2);
	populateForm3(surname1, firstname1, sex1, birthDate1, addressLine1a, addressLine2a, postCode1, class3);

	do
	{
		getCommand(command);
		switch (toupper(command))
		{
		case '1': cout << "Enter the class you wish to enter the pupil into: ";
			cin >> selection;
			cout << "\n";
			switch (selection)
			{
			case '1': enterPupil(class1, selection);
				break;
			case '2': enterPupil(class2, selection);
				break;
			case '3': enterPupil(class3, selection);
				break;
			default: cout << "Invalid input\n";
			}
			break;
		case '2': removePupil(class1, class2, class3, selection, location);
				break;
		case '3':
			cout << "Enter the class you wish to know the size of: ";
			cin >> selection;
			cout << "\n";
			switch (selection)
			{
			case '1': displayNumOfPupils(class1);
				break;
			case '2': displayNumOfPupils(class2);
				break;
			case '3': displayNumOfPupils(class3);
				break;
			default: cout << "Invalid input\n";
			}
			break;
		case '4': cout << "Enter the class you wish to know the information of: ";
			cin >> selection;
			cout << "\n";
			switch (selection)
			{
			case '1': displayClassInformation(class1);
				break;
			case '2': displayClassInformation(class2);
				break;
			case '3': displayClassInformation(class3);
				break;
			default: cout << "Invalid input\n";
			}
			break;
		case '5':cout << "Enter the class you wish to know the population of: ";
			cin >> selection;
			cout << "\n";
			switch (selection)
			{
			case '1':  displayNumOfMales(class1);
				break;
			case '2': displayNumOfMales(class2);
				break;
			case '3':  displayNumOfMales(class3);
				break;
			default: cout << "Invalid input\n";
			};
			break;
		case '6': cout << "Enter the class you wish to know the population of: ";
			cin >> selection;
			cout << "\n";
			switch (selection)
			{
			case '1': displayNumOfFemales(class1);
				break;
			case '2': displayNumOfFemales(class2);
				break;
			case '3': displayNumOfFemales(class3);
				break;
			default: cout << "Invalid input\n";
			};
			break;
		case '7': findSpecificPupil(class1, class2, class3, location, selection);
			break;
		case '8': displayLatestMarkForPupil(class1, class2, class3, location, selection);
				break;
		case '9': displayFullAddress(class1, class2, class3, location, selection);
				break;
		case 'Q': quit(command);
			break;
		default: cout << "Invalid input\n\n";
			cout << "\n";
		}
	} while (toupper(command) != 'Q');
	system("pause");
	return 0;
}

char getCommand(char& command)
{
	cout << "1. Enter pupil.\n"
		<< "2. Remove pupil.\n"
		<< "3. Find no. of pupils in given class.\n"
		<< "4. Display teacher's name + class list for given class.\n"
		<< "5. Find no. of boys in a given class.\n"
		<< "6. Find no. of girls in a given class.\n"
		<< "7. Find specified pupil (given name + DoB).\n"
		<< "8. Find latest mark for given pupil in given subject.\n"
		<< "9. Display full address for given pupil.\n"
		<< "10. Quit (press q to quit).\n\n";
	cout << "Enter number of the command you require: ";
	cin >> command;
	cout << "\n";
	return command;
}
void populateForm1(string surname1, string firstname1, char sex1,
	string birthDate1, string addressLine1a, string addressLine2a, string postCode1, Form& class1)
{
	string gender;
	string letter;
	fstream pupilFile;
	string roomNo;
	string teacher;
	char grade[MAXSUBJECTS];
	int year;
	int numPupils;

	pupilFile.open("Pupil.txt", ios::in);
	if (!pupilFile.fail())
	{
		pupilFile >> year;
		pupilFile.ignore();
		pupilFile >> numPupils;
		pupilFile.ignore();
		getline(pupilFile, roomNo);
		getline(pupilFile, teacher);
		class1.setTeacher(teacher);
		class1.setNumPupils(numPupils);
		for (int j = 0; j < class1.getNumPupils(); j++)
		{
			getline(pupilFile, surname1);
			getline(pupilFile, firstname1);
			getline(pupilFile, gender);
			if (gender == "m" || gender == "M")
			{
				sex1 = 'M';
			}
			else
			{
				sex1 = 'F';
			}
			getline(pupilFile, birthDate1);
			getline(pupilFile, addressLine1a);
			getline(pupilFile, addressLine2a);
			getline(pupilFile, postCode1);
			for (int i = 0; i < MAXSUBJECTS; i++)
			{
				pupilFile.get(grade[i]);
				pupilFile.ignore();
			}
			class1.addPupil(surname1, firstname1, sex1, birthDate1, addressLine1a, addressLine2a, postCode1, j, grade);
		}
	}
	else
		cout << "File failed to open";
	pupilFile.close();
}
void populateForm2(string surname1, string firstname1, char sex1, 
	string birthDate1, string addressLine1a, string addressLine2a, string postCode1, Form& class2)
{
	string gender;
	string letter;
	fstream pupilFile;
	string roomNo;
	string teacher;
	char grade[MAXSUBJECTS];
	int year;
	int numPupils;

	pupilFile.open("Pupil2.txt", ios::in);
	if (!pupilFile.fail())
	{
		pupilFile >> year;
		pupilFile.ignore();
		pupilFile >> numPupils;
		pupilFile.ignore();
		getline(pupilFile, roomNo);
		getline(pupilFile, teacher);
		class2.setTeacher(teacher);
		class2.setNumPupils(numPupils);
		for (int j = 0; j < class2.getNumPupils(); j++)
		{
			getline(pupilFile, surname1);
			getline(pupilFile, firstname1);
			getline(pupilFile, gender);
			if (gender == "m" || gender == "M")
			{
				sex1 = 'M';
			}
			else
			{
				sex1 = 'F';
			}
			getline(pupilFile, birthDate1);
			getline(pupilFile, addressLine1a);
			getline(pupilFile, addressLine2a);
			getline(pupilFile, postCode1);
			for (int i = 0; i < MAXSUBJECTS; i++)
			{
				pupilFile.get(grade[i]);
				pupilFile.ignore();
			}
			class2.addPupil(surname1, firstname1, sex1, birthDate1, addressLine1a, addressLine2a, postCode1, j, grade);
		}
	}
	else
		cout << "File failed to open";
	pupilFile.close();
}
void populateForm3(string surname1, string firstname1, char sex1, 
	string birthDate1, string addressLine1a, string addressLine2a, string postCode1, Form& class3)
{
	string gender;
	string letter;
	fstream pupilFile;
	string roomNo;
	string teacher;
	char grade[MAXSUBJECTS];
	int year;
	int numPupils;

	pupilFile.open("Pupil3.txt", ios::in);
	if (!pupilFile.fail())
	{
		pupilFile >> year;
		pupilFile.ignore();
		pupilFile >> numPupils;
		pupilFile.ignore();
		getline(pupilFile, roomNo);
		getline(pupilFile, teacher);
		class3.setTeacher(teacher);
		class3.setNumPupils(numPupils);
		for (int j = 0; j < class3.getNumPupils(); j++)
		{
			getline(pupilFile, surname1);
			getline(pupilFile, firstname1);
			getline(pupilFile, gender);
			if (gender == "m" || gender == "M")
			{
				sex1 = 'M';
			}
			else
			{
				sex1 = 'F';
			}
			getline(pupilFile, birthDate1);
			getline(pupilFile, addressLine1a);
			getline(pupilFile, addressLine2a);
			getline(pupilFile, postCode1);
			for (int i = 0; i < MAXSUBJECTS; i++)
			{
				pupilFile.get(grade[i]);
				pupilFile.ignore();
			}
			class3.addPupil(surname1, firstname1, sex1, birthDate1, addressLine1a, addressLine2a, postCode1, j, grade);
		}
	}
	else
		cout << "File failed to open";
	pupilFile.close();
}
void updateFileAdd(Form& object, char grade[], char selection)
{
	fstream pupilFile;
	int classNumber;
	string roomNumber;
	string teacher;
	string gender;

	if (selection == '1')
	{
		pupilFile.open("Pupil.txt", ios::in);
		pupilFile >> classNumber;
		pupilFile.ignore();
		pupilFile.ignore();
		pupilFile.ignore();
		getline(pupilFile, roomNumber);
		getline(pupilFile, teacher);
		pupilFile.close();
		pupilFile.open("Pupil.txt", ios::out);
		pupilFile << classNumber << endl;
		pupilFile << object.getNumPupils() << endl;
		pupilFile << roomNumber << endl;
		pupilFile << teacher << endl;
		pupilFile.close();
		for (int i = 0; i < object.getNumPupils(); i++)
		{
			pupilFile.open("Pupil.txt", ios::app);
			size_t position = (object.getFormPupils(i)->getName()).find(" ");
			pupilFile << (object.getFormPupils(i)->getName()).substr(position + 1) << endl;
			pupilFile << (object.getFormPupils(i)->getName()).substr(0, position) << endl;
			pupilFile << object.getFormPupils(i)->getGender() << endl;
			pupilFile << object.getFormPupils(i)->getBirthDate() << endl;
			size_t position2 = (object.getFormPupils(i)->getAddress()).find(',');
			size_t position3 = (object.getFormPupils(i)->getAddress()).find_last_of(',');
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(0, position2) << endl;
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(position2 + 2,(position3 - 1)-(position2 + 1)) 
						<< endl;
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(position3 + 2) << endl;
			for (int j = 0; j < MAXSUBJECTS; j++)
			{
				pupilFile << object.getFormPupils(i)->getGrade(j) << endl;

			}
			pupilFile.close();
		}


	}
	if (selection == '2')
	{
		pupilFile.open("Pupil2.txt", ios::in);
		pupilFile >> classNumber;
		pupilFile.ignore();
		pupilFile.ignore();
		pupilFile.ignore();
		getline(pupilFile, roomNumber);
		getline(pupilFile, teacher);
		pupilFile.close();
		pupilFile.open("Pupil2.txt", ios::out);
		pupilFile << classNumber << endl;
		pupilFile << object.getNumPupils() << endl;
		pupilFile << roomNumber << endl;
		pupilFile << teacher << endl;
		pupilFile.close();
		for (int i = 0; i < object.getNumPupils(); i++)
		{
			pupilFile.open("Pupil2.txt", ios::app);
			size_t position = (object.getFormPupils(i)->getName()).find(" ");
			pupilFile << (object.getFormPupils(i)->getName()).substr(position + 1) << endl;
			pupilFile << (object.getFormPupils(i)->getName()).substr(0, position) << endl;
			pupilFile << object.getFormPupils(i)->getGender() << endl;
			pupilFile << object.getFormPupils(i)->getBirthDate() << endl;
			size_t position2 = (object.getFormPupils(i)->getAddress()).find(',');
			size_t position3 = (object.getFormPupils(i)->getAddress()).find_last_of(',');
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(0, position2) << endl;
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(position2 + 2,(position3 - 1)-(position2 + 1)) 
						<< endl;
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(position3 + 2) << endl;
			for (int j = 0; j < MAXSUBJECTS; j++)
			{
				pupilFile << object.getFormPupils(i)->getGrade(j) << endl;

			}
			pupilFile.close();
		}
	}
	if (selection == '3')
	{
		pupilFile.open("Pupil3.txt", ios::in);
		pupilFile >> classNumber;
		pupilFile.ignore();
		pupilFile.ignore();
		pupilFile.ignore();
		getline(pupilFile, roomNumber);
		getline(pupilFile, teacher);
		pupilFile.close();
		pupilFile.open("Pupil3.txt", ios::out);
		pupilFile << classNumber << endl;
		pupilFile << object.getNumPupils() << endl;
		pupilFile << roomNumber << endl;
		pupilFile << teacher << endl;
		pupilFile.close();
		for (int i = 0; i < object.getNumPupils(); i++)
		{
			pupilFile.open("Pupil3.txt", ios::app);
			size_t position = (object.getFormPupils(i)->getName()).find(" ");
			pupilFile << (object.getFormPupils(i)->getName()).substr(position + 1) << endl;
			pupilFile << (object.getFormPupils(i)->getName()).substr(0, position) << endl;
			pupilFile << object.getFormPupils(i)->getGender() << endl;
			pupilFile << object.getFormPupils(i)->getBirthDate() << endl;
			size_t position2 = (object.getFormPupils(i)->getAddress()).find(',');
			size_t position3 = (object.getFormPupils(i)->getAddress()).find_last_of(',');
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(0, position2) << endl;
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(position2 + 2,(position3 - 1)-(position2 + 1))
						<< endl;
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(position3 + 2) << endl;
			for (int j = 0; j < MAXSUBJECTS; j++)
			{
				pupilFile << object.getFormPupils(i)->getGrade(j) << endl;

			}
			pupilFile.close();
		}
	}
}
void updateFileRemove(Form& object, char selection)
{
	fstream pupilFile;
	int classNumber;
	string roomNumber;
	string teacher;
	string gender;

	if (selection == '1')
	{
		pupilFile.open("Pupil.txt", ios::in);
		pupilFile >> classNumber;
		pupilFile.ignore();
		pupilFile.ignore();
		pupilFile.ignore();
		getline(pupilFile, roomNumber);
		getline(pupilFile, teacher);
		pupilFile.close();
		pupilFile.open("Pupil.txt", ios::out);
		pupilFile << classNumber << endl;
		pupilFile << object.getNumPupils() << endl;
		pupilFile << roomNumber << endl;
		pupilFile << teacher << endl;
		pupilFile.close();
		for (int i = 0; i < object.getNumPupils(); i++)
		{
			pupilFile.open("Pupil.txt", ios::app);
			size_t position = (object.getFormPupils(i)->getName()).find(" ");
			pupilFile << (object.getFormPupils(i)->getName()).substr(position + 1) << endl;
			pupilFile << (object.getFormPupils(i)->getName()).substr(0, position) << endl;
			pupilFile << object.getFormPupils(i)->getGender() << endl;
			pupilFile << object.getFormPupils(i)->getBirthDate() << endl;
			size_t position2 = (object.getFormPupils(i)->getAddress()).find(',');
			size_t position3 = (object.getFormPupils(i)->getAddress()).find_last_of(',');
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(0, position2) << endl;
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(position2 + 2, (position3 - 1) - (position2 + 1))
					<< endl;
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(position3 + 2) << endl;
			for (int j = 0; j < MAXSUBJECTS; j++)
			{
				pupilFile << object.getFormPupils(i)->getGrade(j) << endl;
			}
			pupilFile.close();
		}
	}
	if (selection == '2')
	{
		pupilFile.open("Pupil2.txt", ios::in);
		pupilFile >> classNumber;
		pupilFile.ignore();
		pupilFile.ignore();
		pupilFile.ignore();
		getline(pupilFile, roomNumber);
		getline(pupilFile, teacher);
		pupilFile.close();
		pupilFile.open("Pupil2.txt", ios::out);
		pupilFile << classNumber << endl;
		pupilFile << object.getNumPupils() << endl;
		pupilFile << roomNumber << endl;
		pupilFile << teacher << endl;
		pupilFile.close();
		for (int i = 0; i < object.getNumPupils(); i++)
		{
			pupilFile.open("Pupil2.txt", ios::app);
			size_t position = (object.getFormPupils(i)->getName()).find(" ");
			pupilFile << (object.getFormPupils(i)->getName()).substr(position + 1) << endl;
			pupilFile << (object.getFormPupils(i)->getName()).substr(0, position) << endl;
			pupilFile << object.getFormPupils(i)->getGender() << endl;
			pupilFile << object.getFormPupils(i)->getBirthDate() << endl;
			size_t position2 = (object.getFormPupils(i)->getAddress()).find(',');
			size_t position3 = (object.getFormPupils(i)->getAddress()).find_last_of(',');
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(0, position2) << endl;
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(position2 + 2, (position3 - 1) - (position2 + 1))
					<< endl;
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(position3 + 2) << endl;
			for (int j = 0; j < MAXSUBJECTS; j++)
			{
				pupilFile << object.getFormPupils(i)->getGrade(j) << endl;
			}
			pupilFile.close();
		}
	}
	if (selection == '3')
	{
		pupilFile.open("Pupil3.txt", ios::in);
		pupilFile >> classNumber;
		pupilFile.ignore();
		pupilFile.ignore();
		pupilFile.ignore();
		getline(pupilFile, roomNumber);
		getline(pupilFile, teacher);
		pupilFile.close();
		pupilFile.open("Pupil3.txt", ios::out);
		pupilFile << classNumber << endl;
		pupilFile << object.getNumPupils() << endl;
		pupilFile << roomNumber << endl;
		pupilFile << teacher << endl;
		pupilFile.close();
		for (int i = 0; i < object.getNumPupils(); i++)
		{
			pupilFile.open("Pupil3.txt", ios::app);
			size_t position = (object.getFormPupils(i)->getName()).find(" ");
			pupilFile << (object.getFormPupils(i)->getName()).substr(position + 1) << endl;
			pupilFile << (object.getFormPupils(i)->getName()).substr(0, position) << endl;
			pupilFile << object.getFormPupils(i)->getGender() << endl;
			pupilFile << object.getFormPupils(i)->getBirthDate() << endl;
			size_t position2 = (object.getFormPupils(i)->getAddress()).find(',');
			size_t position3 = (object.getFormPupils(i)->getAddress()).find_last_of(',');
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(0, position2) << endl;
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(position2 + 2, (position3 - 1) - (position2 + 1))
					<< endl;
			pupilFile << (object.getFormPupils(i)->getAddress()).substr(position3 + 2) << endl;
			for (int j = 0; j < MAXSUBJECTS; j++)
			{
				pupilFile << object.getFormPupils(i)->getGrade(j) << endl;
			}
			pupilFile.close();
		}
	}
}
void enterPupil(Form& object, char selection)
{
	string surname1;
	string firstname1;
	char sex1 = 'm';
	string birthDate1;
	string addressLine1a;
	string addressLine2a;
	string postCode1;
	char grade[MAXSUBJECTS] = { 'a', 'b', 'c', 'd', 'e' };
	int i = object.getNumPupils();

	cout << "Enter the first name of the pupil: ";
	cin.ignore();
	getline(cin, firstname1);
	cout << "\n";
	cout << "Enter the surname of the pupil: ";
	getline(cin, surname1);
	cout << "\n";
	cout << "Enter the gender of the pupil(m or f): ";
	cin >> sex1;
	cout << "\n";
	cout << "Enter the date of birth of the pupil(dd/mm/yy): ";
	cin.ignore();
	getline(cin, birthDate1);
	cout << "\n";
	cout << "Enter the first address line of the pupil: ";
	getline(cin, addressLine1a);
	cout << "\n";
	cout << "Enter the second address line  of the pupil: ";
	getline(cin, addressLine2a);
	cout << "\n";
	cout << "Enter the postcode of the pupil: ";
	getline(cin, postCode1);
	cout << "\n";
	for (int j = 0; j < MAXSUBJECTS; j++)
	{
		cout << "Enter Grade for subject " << j + 1 << ": ";
		cin >> grade[j];
		cout << "\n";
	}
	object.addPupil(surname1, firstname1, sex1, birthDate1, addressLine1a, addressLine2a, postCode1, i, grade);
	updateFileAdd(object, grade, selection);
}
void removePupil(Form& class1, Form& class2, Form& class3, char selection, int& location)
{
	if (findSpecificPupil(class1, class2, class3, location, selection))
	{
		switch (selection)
		{
		case '1': class1.removePupil(location, class1);
			cout << "Pupil has been removed";
			cout << "\n";
			updateFileRemove(class1, selection);
			break;
		case '2': class2.removePupil(location, class2);
			cout << "Pupil has been removed";
			cout << "\n";
			updateFileRemove(class2, selection);
			break;
		case '3':class3.removePupil(location, class3);
			cout << "Pupil has been removed";
			cout << "\n";
			updateFileRemove(class3, selection);
			break;
		}
	}
	cout << "\n\n";
}
void displayNumOfPupils(Form& object)
{
	if (object.getNumPupils() == 1)
	{
		cout << "There is " << object.getNumPupils() << " pupil in this class\n\n";
		cout << "\n";
	}
	else
	{
		cout << "There are " << object.getNumPupils() << " pupils in this class\n\n";
		cout << "\n\n";
	}
}
void displayClassInformation(Form& object)
{
	cout << "The teacher is " << object.getTeacher() << "\n\n";
	cout << "Pupil list" << ": \n";
	for (int i = 0; i < object.getNumPupils(); i++)
	{
		cout << object.getFormPupils(i)->getName() << "\n";
	}
	cout << "\n\n";
}
void displayNumOfMales(Form& object)
{
	int counter = 0;

	for (int i = 0; i < object.getNumPupils(); i++)
	{
		if ((object.getFormPupils(i)->getGender()) == 'm' || (object.getFormPupils(i)->getGender()) == 'M')
			counter += 1;
	}
	if (counter == 1)
	{
		cout << "There is " << counter << " male in this class\n";
	}
	else
	{
		cout << "There are " << counter << " males in this class\n";
	}
	cout << "\n\n";
}
void displayNumOfFemales(Form& object)
{
	int counter = 0;

	for (int i = 0; i < object.getNumPupils(); i++)
	{
		if ((object.getFormPupils(i)->getGender()) == 'f' || (object.getFormPupils(i)->getGender()) == 'F')
			counter += 1;
	}
	if (counter == 1)
	{
		cout << "There is " << counter << " female in this class\n";
	}
	else
	{
		cout << "There are " << counter << " females in this class\n";
	}
	cout << "\n\n";
}
bool findSpecificPupil(Form& class1, Form& class2, Form& class3, 
	int& location, char& selection)
{
	string name;
	string name1;
	string DoB;
	bool found = false;

	cout << "Enter the name of the pupil: ";
	cin.ignore();
	getline(cin, name);
	cout << "\n";
	cout << "Enter the date of birth of that pupil: ";
	getline(cin, DoB);
	cin.ignore();
	cout << "\n";
	for (int i = 0; i < class1.getNumPupils(); i++)
	{
		name1 = class1.getFormPupils(i)->getName();
		if ((name == name1) && (DoB == class1.getFormPupils(i)->getBirthDate()))
		{
			cout << name1 << " has been found\n";
			found = true;
			location = i;
			selection = '1';
		}
	}
	if (!found)
	{
		for (int i = 0; i < class2.getNumPupils(); i++)
		{
			name1 = class2.getFormPupils(i)->getName();
			if ((name == name1) && (DoB == class2.getFormPupils(i)->getBirthDate()))
			{
				cout << name1 << " has been found\n";
				found = true;
				location = i;
				selection = '2';
			}
		}
	}
	if (!found)
	{
		for (int i = 0; i < class3.getNumPupils(); i++)
		{
			name1 = class3.getFormPupils(i)->getName();
			if ((name == name1) && (DoB == class3.getFormPupils(i)->getBirthDate()))
			{
				cout << name1 << " has been found\n";
				found = true;
				location = i;
				selection = '3';
			}
		}
	}
	if (!found)
		cout << "\nPupil not found\n";
	cout << "\n\n";
	return found;
}
void displayLatestMarkForPupil(Form& class1, Form& class2, Form& class3, 
	 int& location, char selection)
{
	char grade = ' ';
	int i = 0;
	if (findSpecificPupil(class1, class2, class3, location, selection))
	{
		switch (selection)
		{
		case '1': cout << "Enter the subject you wish to know the grade of: ";
			cin >> i;
			cout << "The grade for subject " << i << " are: ";
			cout << class1.getFormPupils(location)->getGrade(i);
			cout << "\n\n";
			break;
		case '2': cout << "Enter the subject you wish to know the grade of: ";
			cin >> i;
			cout << "The grade for subject " << i << " are: ";
			cout << class2.getFormPupils(location)->getGrade(i);
			cout << "\n\n";
			break;
		case '3': cout << "Enter the subject you wish to know the grade of: ";
			cin >> i;
			cout << "The grade for subject " << i << " are: ";
			cout << class3.getFormPupils(location)->getGrade(i);
			cout << "\n\n";
			break;
		}
	}
}
void displayFullAddress(Form& class1, Form& class2, Form& class3, 
	 int& location, char selection)
{
	if (findSpecificPupil(class1, class2, class3, location, selection))
	{
		switch (selection)
		{
		case '1': cout << "The address of is: ";
			cout << class1.getFormPupils(location)->getAddress() << "\n\n";
			break;
		case '2': cout << "The address of is: ";
			cout << class2.getFormPupils(location)->getAddress() << "\n\n";
			break;
		case '3': cout << "The address of is: ";
			cout << class3.getFormPupils(location)->getAddress() << "\n\n";
			break;
		}
	}
}
void quit(char& command)
{
	char input;
	cout << "Do you wish to Exit? Y or N: ";
	cin >> input;
	if (toupper(input) == 'Y')
		command = 'q';
	else
		command = ' ';
	cout << "\n\n";
}