#pragma once
#include "stdafx.h"
#include <string>
#include <fstream>

using namespace std;

 // ��������� ��� �������� ������ ������ �� ��������
struct Movie 
{
	string name; // ��������
	string genre; // ����
	string country; // ������
	string productionYear; // ��� ������������
	string producer; // �������
	string format; // ��������
	string sound; // ����
	string time; // �����������������

	Movie* link; // ��������� �� ��������� ������� ������
};

 // ����� ��� ������ � ���������
 // ��������� �������� ���������� ���� ������ � ���� ���������
class MovieLibrary
{
public:
	MovieLibrary();
	~MovieLibrary();

	int setElAt(Movie, int); // ����������� ���������� �������� ���������� �������� 
	Movie* getElAt(int); // ���������� ��������� �� ��������� ������� ������
	Movie* getList(); // ���������� ��������� �� ������ ������
	bool isListEmpty(); // �������, ���� �� ������

	int saveList(); // ��������� ������ � ����
	int loadList(); // ��������� ������ �� �����
	void setFileName(string); // ���������� ��� �����
	
	void createFirstFilm(Movie); // ������� ������ ������� ������
	void addFilm(Movie); // �������� ����� (� ����� ������)
	int addFilm(Movie, int); // �������� ����� ����� ����������
	int addFirstFilm(Movie); // �������� ����� � ������ ������

	int deleteFilm(int); // ������� ��������� �����
	int deleteLastFilm(); // ������� ��������� �����
	void deleteTable(); // ������� ������� �������

	void sort(); // ������������� ������ � ���������� ������� �� �������� ������

private:
	string fileName; // ��� �����
	Movie* head; // ��������� �� ������ ������
	bool isEmpty; // ���� - ���� �� ������

	void swap(Movie*, Movie*); // �������� ��� �������� �������
};

