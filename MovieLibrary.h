#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include "conio.h"
#include <fstream>

using namespace std;

struct Movie {
	string name; // Название
	string genre; // Жанр
	string country; // Страна
	string productionYear; // Год производства
	string producer; // Режиссёр
	string format; // Качество
	string sound; // Звук
	string time; // Продолжительность

	Movie* link;
};

class MovieLibrary
{
public:
	MovieLibrary();
	~MovieLibrary();

	//void showMovie(Movie*); // ###

	Movie* getList(); // Возвращает указатель на начало списка
	bool isListEmpty(); // Говорит, пуст ли список

	//void enterList(); // Ввести таблицу с клавиатуры ###
	//void showList(); // Вывести таблицу на экран ###
	int saveList(); // Сохранить таблицу в файл
	int loadList(); // Загрузить таблицу из файла
	
	void createFirstFilm(Movie); // Добавить первый элемент
	void addFilm(Movie); // Добавить фильм (в конец)
	int addFilm(Movie, int); // Добавить фильм после указанного
	int addFirstFilm(Movie); // Добавить фильм в начало
	//void addFilm(); // ###

	//int deleteFirstFilm(); // Удаляет первый фильм
	int deleteFilm(int); // Удаляет указанный фильм
	int deleteLastFilm(); // Удаляет последний фильм

	//void editFilm(string); // редактирует фильм с введённым названием

	//Movie* getInfo(string); // Возвращает информацию о фильме с введённым названием
	//Movie* getInfo(string, string); // Возвращает информацию о фильме с определёнными жанром и страной
	//Movie* getSortedList(string); // Возвращает отсортированный список определённого режиссёра
	//void diag(); // Диаграмма

private:
	string fileName;
	Movie* head;
	bool isEmpty;

	//System::Windows::Forms::MyForm^ mf;
};

