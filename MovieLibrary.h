#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include "conio.h"
#include <fstream>

using namespace std;

struct Movie {
	string name; // ��������
	string genre; // ����
	string country; // ������
	string productionYear; // ��� ������������
	string producer; // �������
	string format; // ��������
	string sound; // ����
	string time; // �����������������

	Movie* link;
};

class MovieLibrary
{
public:
	MovieLibrary();
	~MovieLibrary();

	//void showMovie(Movie*); // ###

	Movie* getList(); // ���������� ��������� �� ������ ������
	bool isListEmpty(); // �������, ���� �� ������

	//void enterList(); // ������ ������� � ���������� ###
	//void showList(); // ������� ������� �� ����� ###
	int saveList(); // ��������� ������� � ����
	int loadList(); // ��������� ������� �� �����
	
	void createFirstFilm(Movie); // �������� ������ �������
	void addFilm(Movie); // �������� ����� (� �����)
	int addFilm(Movie, int); // �������� ����� ����� ����������
	int addFirstFilm(Movie); // �������� ����� � ������
	//void addFilm(); // ###

	//int deleteFirstFilm(); // ������� ������ �����
	int deleteFilm(int); // ������� ��������� �����
	int deleteLastFilm(); // ������� ��������� �����

	//void editFilm(string); // ����������� ����� � �������� ���������

	//Movie* getInfo(string); // ���������� ���������� � ������ � �������� ���������
	//Movie* getInfo(string, string); // ���������� ���������� � ������ � ������������ ������ � �������
	//Movie* getSortedList(string); // ���������� ��������������� ������ ������������ ��������
	//void diag(); // ���������

private:
	string fileName;
	Movie* head;
	bool isEmpty;

	//System::Windows::Forms::MyForm^ mf;
};

