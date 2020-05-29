#include "stdafx.h"
#include "MovieLibrary.h"
#include "Windows.h"

MovieLibrary::MovieLibrary()
{
	setlocale(0, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	fileName = "database.txt";
	head = NULL;
	isEmpty = true;
}

MovieLibrary::~MovieLibrary()
{
	Movie* current = head;
	Movie* toDelete = current;
	while (current)
	{
		current = current->link;
		delete toDelete;
		toDelete = current;
	}
	head = NULL;
	isEmpty = true;
}

//void MovieLibrary::showMovie(Movie *m)
//{
//	cout << "�������� - " << m->name << endl;
//	cout << "���� - " <<m->genre << endl;
//	cout << "������ - " << m->country << endl;
//	cout << "��� ������������ - " << m->productionYear << endl;
//	cout << "������� - " << m->producer << endl;
//	cout << "�������� - " << m->format << endl;
//	cout << "���� - " << m->sound << endl;
//	cout << "����� - " << m->time << endl;
//}

Movie * MovieLibrary::getList()
{
	return head;
}

bool MovieLibrary::isListEmpty()
{
	return isEmpty;
}

//void MovieLibrary::enterList()
//{
//	int i = 1;
//	Movie* tmp = NULL;
//	Movie* current = head;
//	char stop = 0;
//	do
//	{
//		tmp = new Movie;
//
//		cout << endl << "������� " << i << " �������:" << endl;
//
//		cout << "��������: "; cin >> tmp->name;
//		cout << "����: "; cin >> tmp->genre;
//		cout << "������: "; cin >> tmp->country;
//		cout << "��� ������������: "; cin >> tmp->productionYear;
//		cout << "�������: "; cin >> tmp->producer;
//		cout << "��������: "; cin >> tmp->format;
//		cout << "����: "; cin >> tmp->sound;
//		cout << "�����: "; cin >> tmp->time;
//		tmp->link = NULL;
//
//		if (current != NULL)
//		{
//			current->link = tmp;
//			current = tmp;
//		}
//		else
//			current = head = tmp;
//			
//		i++;
//
//		cout << "����������? (y/n)";
//		stop = _getch();
//	} while (stop != 'n');
//
//	isEmpty = false;
//	cout << endl;
//}

//void MovieLibrary::showList()
//{
//	if (isEmpty)
//		cout << "������ ����! " << endl;
//	else
//	{
//		int i = 1;
//		Movie* current = head;
//		while (current)
//		{
//			cout << i << ": " << endl;
//			showMovie(current);
//			/*cout << "�������� - " << current->name << endl;
//			cout << "���� - " << current->genre << endl;
//			cout << "������ - " << current->country << endl;
//			cout << "��� ������������ - " << current->productionYear << endl;
//			cout << "������� - " << current->producer << endl;
//			cout << "�������� - " << current->format << endl;
//			cout << "���� - " << current->sound << endl;
//			cout << "����� - " << current->time << endl;*/
//
//			i++;
//			current = current->link;
//		}
//	}
//}

int MovieLibrary::saveList()
{
	if (isEmpty)
		return 2;
	else
	{
		ofstream file(fileName);

		if (!file.is_open())
			return 1;
		else
		{
			Movie* current = head;
			while (current)
			{
				file << current->name << endl;
				file << current->genre << endl;
				file << current->country << endl;
				file << current->productionYear << endl;
				file << current->producer << endl;
				file << current->format << endl;
				file << current->sound << endl;
				if (current->link == NULL)
					file << current->time;
				else
					file << current->time << endl;

				current = current->link;
			}
			file.close();
		}
	}
	return 0;
}

int MovieLibrary::loadList()
{
	ifstream file(fileName);

	if (!file.is_open())
	{
		return 1;
	}
	else if (file.peek() == -1 || file.peek() == 0)
	{
		return 2;
	}
	else
	{
		if (!(isEmpty && head == NULL))
			this->~MovieLibrary();

		Movie* tmp = NULL;
		Movie* current = head;
		while (!file.eof())
		{
			tmp = new Movie;

			getline(file, tmp->name);
			getline(file, tmp->genre);
			getline(file, tmp->country);
			getline(file, tmp->productionYear);
			getline(file, tmp->producer);
			getline(file, tmp->format);
			getline(file, tmp->sound);
			getline(file, tmp->time);
			
			tmp->link = NULL;

			if (current != NULL)
			{
				current->link = tmp;
				current = tmp;
			}
			else
				current = head = tmp;
		}

		isEmpty = false;

		file.close();
	}

	return 0;
}

void MovieLibrary::createFirstFilm(Movie m)
{
	head = new Movie;
	head->name = m.name;
	head->genre = m.genre;
	head->country = m.country;
	head->productionYear = m.productionYear;
	head->producer = m.producer;
	head->format = m.format;
	head->sound = m.sound;
	head->time = m.time;
	head->link = NULL;
	isEmpty = false;
}

void MovieLibrary::addFilm(Movie m)
{
	if (!isEmpty)
	{
		Movie* current = head;
		Movie* tmp = NULL;
		while (current->link)
		{
			current = current->link;
		}
		tmp = new Movie;
		tmp->name = m.name;
		tmp->genre = m.genre;
		tmp->country = m.country;
		tmp->productionYear = m.productionYear;
		tmp->producer = m.producer;
		tmp->format = m.format;
		tmp->sound = m.sound;
		tmp->time = m.time;
		tmp->link = NULL;
		
		tmp->link = NULL;

		current->link = tmp;
	}
}

int MovieLibrary::addFilm(Movie m, int indexToAddAfter)
{
	if (isEmpty)
		return 1;
	else
	{
		int i = 1;
		bool found = false;
		Movie* current = head;
		while (current && !found)
		{
			if (i == indexToAddAfter)
			{
				Movie* tmp = new Movie;
				tmp->link = current->link;
				current->link = tmp;

				tmp->name = m.name;
				tmp->genre = m.genre;
				tmp->country = m.country;
				tmp->productionYear = m.productionYear;
				tmp->producer = m.producer;
				tmp->format = m.format;
				tmp->sound = m.sound;
				tmp->time = m.time;

				found = true;
			}
			i++;
			current = current->link;
		}
		if (!found)
			return 2;
	}

	return 0;
}

int MovieLibrary::addFirstFilm(Movie m)
{
	if (isEmpty)
		return 1;
	else
	{
		Movie* tmp = new Movie;
		tmp->link = head;
		head = tmp;

		tmp->name = m.name;
		tmp->genre = m.genre;
		tmp->country = m.country;
		tmp->productionYear = m.productionYear;
		tmp->producer = m.producer;
		tmp->format = m.format;
		tmp->sound = m.sound;
		tmp->time = m.time;
	}

	return 0;
}

//void MovieLibrary::addFilm()
//{
//	if (isEmpty)
//		cout << "������ ����!" << endl;
//	else
//	{
//		Movie* current = head;
//		Movie* tmp = NULL;
//		while (current->link)
//		{
//			current = current->link;
//		}
//		tmp = new Movie;
//
//		cout << "��������: "; cin >> tmp->name;
//		cout << "����: "; cin >> tmp->genre;
//		cout << "������: "; cin >> tmp->country;
//		cout << "��� ������������: "; cin >> tmp->productionYear;
//		cout << "�������: "; cin >> tmp->producer;
//		cout << "��������: "; cin >> tmp->format;
//		cout << "����: "; cin >> tmp->sound;
//		cout << "�����: "; cin >> tmp->time;
//		tmp->link = NULL;
//
//		current->link = tmp;
//	}
//}

int MovieLibrary::deleteFilm(int indexToDelete)
{
	if (isEmpty)
	{
		return 1;
	}	
	else
	{
		int index = 1;
		if (indexToDelete == 1)
		{
			Movie* toDelete = head;
			head = head->link;
			delete toDelete;
			toDelete = NULL;
			return 0;
		}
		Movie* current = head;
		Movie* toDelete = NULL;
		Movie* previous = NULL;
		while (current->link)
		{
			toDelete = current->link;
			if (index == indexToDelete)
			{
				current->link = toDelete->link;
				delete toDelete;
				toDelete = NULL;
				return 0;
			}
			else
			{
				index++;
				previous = current;
				current = current->link;
			}
		}
		if (index == indexToDelete)
		{
			previous->link = NULL;
			delete current;
			current = NULL;
			return 0;
		}
	}
}

int MovieLibrary::deleteLastFilm()
{
	if (isEmpty)
		return 1;
	else
	{
		Movie* current = head;
		Movie* toDelete = NULL;
		Movie* previous = NULL;

		while (current->link)
		{
			toDelete = current->link;
			previous = current;
			current = current->link;
		}
		previous->link = NULL;
		delete current;
		current = NULL;
		return 0;
	}
}
