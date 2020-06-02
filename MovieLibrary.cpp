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
	this->deleteTable();
}

// ����������� ���������� �������� ���������� �������� 
int MovieLibrary::setElAt(Movie m, int index)
{
	if (!isEmpty) // ���� ������ �� ����
	{
		Movie* current = head; // ������������� ��������� �� ������ ������
		int i = 1; // ������ �������� �������� (��������� � 1)
		while (current && i <= index) // ���� �� ��������� ����� ������ ��� �� �������� �� ������ �������
		{
			if (i == index) // ����� ��-�
			{
				// ����������� ��� ���������� ��������, link �� �������
				current->name = m.name;
				current->genre = m.genre;
				current->country = m.country;
				current->productionYear = m.productionYear;
				current->producer = m.producer;
				current->format = m.format;
				current->sound = m.sound;
				current->time = m.time;

				// �������
				return 0;
			}
			current = current->link; // ��������� � ���������� �������� ������
			i++; // �������������� �������
		}
		return 2; // ���������� ��������, ���� ������� �� ������
	}
	return 1; // ���������� ��������, ���� ������ ����
}

// ���������� ��������� �� ��������� ������� ������
Movie * MovieLibrary::getElAt(int index)
{
	if (!isEmpty) // ���� ������ �� ����
	{
		if (index == 1)
			return head; // ���������� ������ ������ (1-�� ��� ��-�)
		else
		{
			// ���� ��������� �������
			Movie* current = head;
			int i = 1;
			while (current && i <= index)
			{
				if (i == index) // �����
					return current; // ���������� ��� � �������
				current = current->link;
				i++;
			}
			return NULL; // ���������� NULL, ���� ��-� �� ������
		}
	}
	return NULL; // ��� �� ���������� NULL, ���� ������ ����
}

// ���������� ��������� �� ������ ������
Movie * MovieLibrary::getList()
{
	return head;
}

// �������, ���� �� ������
bool MovieLibrary::isListEmpty()
{
	return isEmpty; // ���������� ����
}

// ��������� ������ � ����
int MovieLibrary::saveList()
{
	if (isEmpty) // ���� ������ ����
		return 2; // ���������� ��� ������
	else
	{
		ofstream file(fileName); // ��������� ���� ��� ������

		if (!file.is_open()) // ���� �� ������� ������� ����
			return 1; // ���������� ��� ������
		else
		{
			// ���������� ������ � ����
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
					file << current->time; // ����� ���������� �������� �� ������ ������� �� ��������� ������
				else
					file << current->time << endl; // ����� ��������� - ������

				current = current->link;
			}
			file.close(); // ��������� ����
		}
	}
	return 0; // ���������� 0 ��� �������� ���������� �����
}

// ��������� ������ �� �����
int MovieLibrary::loadList()
{
	ifstream file(fileName); // ��������� ���� ��� ������

	if (!file.is_open()) // �� ������� ������� ����
	{
		// ��������� ���� � �������� �� ������
		file.close();
		return 1;
	}
	else if (file.peek() == -1 || file.peek() == 0) // ���� ����
	{
		// ��������� ����, ��������, ��� �� ����
		file.close();
		return 2;
	}
	else // ������ ����� ���������
	{
		// ���� ������ ��� ��������
		if (!(isEmpty && head == NULL))
			this->deleteTable(); // ������� ��� �� ��������� ������

		// ��������� ���� ���������
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

			if (current != NULL) // ��� ���������� ������� ���������
			{
				current->link = tmp; // ������������� link �������� ���� �� ������ ��� ���������
				current = tmp; // ������ ������ ��� ��������� ���� �������
			}
			else // ��� ���������� ������� ��������
				current = head = tmp; // ����������� ��������� �� ������� ������ � ��������� �� ������� ������� 
									  //����� ������ ��� ���������� ����
		}

		isEmpty = false; // ������������� ���� (������ ������ �� ����)

		file.close(); // ��������� ����
	}

	return 0; // ���������� ��� ��������� ���������� ������ �������
}

// ���������� ��� ����� (�� ��������� ��� database.txt)
void MovieLibrary::setFileName(string newFileName)
{
	fileName = newFileName;
}

// ������� ������ ������� ������
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

// �������� ����� (� ����� ������)
void MovieLibrary::addFilm(Movie m)
{
	if (!isEmpty) // ���� ������ �� ����
	{
		Movie* current = head;
		Movie* tmp = NULL;
		while (current->link) // �������� �� ����� ������
		{
			current = current->link;
		}
		// �������� ������ ��� ����� ������� � �������������� ���
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

		// ������������� link �������� �������� �� ������������� ����
		current->link = tmp;
	}
}

// �������� ����� ����� ����������
int MovieLibrary::addFilm(Movie m, int indexToAddAfter)
{
	if (isEmpty) // ���� ������ ����
		return 1; // ���������� ��� ������
	else
	{
		int i = 1; // ������������� ������� �� 1
		bool found = false; // ������������� ���� � false
		Movie* current = head; // ������������� ��������� �� ������ ������
		while (current && !found) // ���� �� ����� ������ ��� ���� �� ������ �������
		{
			if (i == indexToAddAfter) // ����� �������� ������ � �������
			{
				// �������� ������ ��� ����� ���� ������
				Movie* tmp = new Movie;
				tmp->link = current->link; // ������������� link �������������� ���� �� ��-�, ��������� �� �������
				current->link = tmp; // ������������� link �������� ���� �� ������������� ��-�
				
				// �������������� ������������� ��-� ���������� ���������
				tmp->name = m.name;
				tmp->genre = m.genre;
				tmp->country = m.country;
				tmp->productionYear = m.productionYear;
				tmp->producer = m.producer;
				tmp->format = m.format;
				tmp->sound = m.sound;
				tmp->time = m.time;

				// ������������� ���� � true ��� ������ �� �����
				found = true;
			}
			i++; // ����������� �������
			current = current->link; // ��������� � ���������� ��������
		}
		if (!found) // ���� ������� ��� � �� ��� ������
			return 2; // ���������� ��� ������
	}

	return 0; // �������� �� �������� ���������� �������
}

// �������� ����� � ������ ������
int MovieLibrary::addFirstFilm(Movie m)
{
	if (isEmpty)
		return 1; // ��������, ��� ������ ����
	else
	{
		// �������� ������ ��� ����� ��-�
		Movie* tmp = new Movie;
		tmp->link = head; // ������������� ��� link �� ������ ������
		head = tmp; // ������� � ��������� �� ������ ������ ����� ������ ��-��
		
		// �������������� ���� ��-� ���������� ���������
		tmp->name = m.name;
		tmp->genre = m.genre;
		tmp->country = m.country;
		tmp->productionYear = m.productionYear;
		tmp->producer = m.producer;
		tmp->format = m.format;
		tmp->sound = m.sound;
		tmp->time = m.time;
	}

	return 0; // ��������, ��� ������� ���������� �������
}

// ������� ��������� �����
int MovieLibrary::deleteFilm(int indexToDelete)
{
	if (isEmpty)
	{
		return 1; // ���������� 1, ���� ������ ����
	}
	else if (head->link == NULL && indexToDelete == 1) // ���� � ������� ������� ���� �������
		this->deleteTable(); // ������� ������ �������
	else
	{
		int index = 1; // ������������� �������
		if (indexToDelete == 1) // ���� ����� ������� ������ ��-� � �� �� ������������ � ������
		{
			Movie* toDelete = head; // ���������� ����� ������ ������
			head = head->link; // ���������� ��������� �� ������ ������ �� ��������� �������
			delete toDelete; // ������� ������� �������
			toDelete = NULL;
			return 0; // ������� ������� ����������
		}
		// ���� �� ������� ����� �� ������ ��-�
		index++;
		Movie* current = head; // ������������� ��������� �� ������ ������
		Movie* toDelete = NULL;
		Movie* previous = NULL;
		while (current->link) // ���� �� ����� �� �������������� ��������
		{
			toDelete = current->link; // ��������� ����� ���������� �� ������� ��-��
			if (index == indexToDelete) // ���� ������ ��-�, ������� ��������� �������
			{
				current->link = toDelete->link; // ������������� link �������� ��-�� �� ��������� �� ���, ������� ����� �������
				delete toDelete; // ������� ��������� �� ������� ��-�
				toDelete = NULL;
				return 0; // ������� ������� ����������
			}
			else // ���� ��-� ��� �������� ��� �� ������
			{
				index++; // ����������� �������
				previous = current; // ��������� ����� �������� ��������
				current = current->link; // �������� � ���������� �������� ������
			}
		}
		// ����� �� �������������� ��-��
		if (index == indexToDelete) // ����� ������� ��� �������� - �� ���������
		{
			previous->link = NULL; // ������������� link ������� ����� ������� ���� �� NULL
			delete current; // ������� ������� �������
			current = NULL;
			return 0; // ������� ������� ����������
		}
	}
}

// ������� ��������� �����
int MovieLibrary::deleteLastFilm()
{
	if (isEmpty)
		return 1; // �������, ��� ������ ����
	else if (head->link == NULL) // ���� ��������� ������� - ������������ � ������
		this->deleteTable(); // ������� ���� ������
	else // ���� ���� ��� �������� ������ ����
	{
		// �������� ���������� ����� ��� �������� ���������� �������� �� ������� deleteFilm()
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

// ������� ������ �������
void MovieLibrary::deleteTable()
{
	if (!isEmpty && head != NULL) // ���� ������ �� ����
	{
		Movie* current = head; // ������������� ��������� �� ������ ������
		Movie* toDelete = current; // ���������� ������� ��� �������� ��� �������
		while (current) // ���� �� ����� ������
		{
			current = current->link; // ��������� � ���������� ��������
			delete toDelete; // ������� ����������
			toDelete = current; // ���������� ������� ��� �������� ��� �������
		}
		head = NULL; // ����������� ��������� �� ������ ������ �������� NULL
		isEmpty = true; // ������������� ���� � true (������ ����)
	}
}

// ������������� ������ � ���������� ������� �� �������� ������
void MovieLibrary::sort()
{
	Movie* current = head;
	if (head == NULL || isEmpty)
		return; // ���� ������ ���� - ��������� ������ �������
	else
	{
		bool isSorted = false; // ���� (�������������) = false
		while (!isSorted) // ���� �� �������������
		{
			isSorted = true; // �������, ��� ������ ������������
			current = head; // ������������� ��������� �� ������ ������
			while (current->link) // ���� �� ����� ������
			{
				if (current->name > current->link->name) // ���� �������� ����� �������� �������
				{
					// ������ �� �������
					swap(current, current->link);
					isSorted = false; // ������������� ���� (�������������) � false
				}
				current = current->link; // ��������� � ���������� ��������
			}
		}
	}
}

// �������� ��� �������� ������� (���������, ��� ����������)
void MovieLibrary::swap(Movie *m1, Movie *m2)
{
	// ���� �� ���� �� ���������� ���������� �� ������ NULL
	if (m1 != NULL && m2 != NULL)
	{
		// ������ ���� ���� ��������� ������� (���, ����� link)
		Movie *t = new Movie;
		t->name = m1->name;
		t->genre = m1->genre;
		t->country = m1->country;
		t->productionYear = m1->productionYear;
		t->producer = m1->producer;
		t->format = m1->format;
		t->sound = m1->sound;
		t->time = m1->time;

		m1->name = m2->name;
		m1->genre = m2->genre;
		m1->country = m2->country;
		m1->productionYear = m2->productionYear;
		m1->producer = m2->producer;
		m1->format = m2->format;
		m1->sound = m2->sound;
		m1->time = m2->time;

		m2->name = t->name;
		m2->genre = t->genre;
		m2->country = t->country;
		m2->productionYear = t->productionYear;
		m2->producer = t->producer;
		m2->format = t->format;
		m2->sound = t->sound;
		m2->time = t->time;
	}
	else // ���� ������� ���� ���� ������ ���������
		return; // �������
}