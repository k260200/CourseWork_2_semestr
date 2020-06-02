#pragma once
#include "stdafx.h"
#include <string>
#include <fstream>

using namespace std;

 // Структура для описания одного фильма из кинотеки
struct Movie 
{
	string name; // Название
	string genre; // Жанр
	string country; // Страна
	string productionYear; // Год производства
	string producer; // Режиссёр
	string format; // Качество
	string sound; // Звук
	string time; // Продолжительность

	Movie* link; // Указатель на следующий элемент списка
};

 // Класс для работы с кинотекой
 // Реализует основной функционал базы данных в этой программе
class MovieLibrary
{
public:
	MovieLibrary();
	~MovieLibrary();

	int setElAt(Movie, int); // Присваивает указанному элементу переданное значение 
	Movie* getElAt(int); // Возвращает указатель на указанный элемент списка
	Movie* getList(); // Возвращает указатель на начало списка
	bool isListEmpty(); // Говорит, пуст ли список

	int saveList(); // Сохранить список в файл
	int loadList(); // Загрузить список из файла
	void setFileName(string); // Установить имя файла
	
	void createFirstFilm(Movie); // Создать первый элемент списка
	void addFilm(Movie); // Добавить фильм (в конец списка)
	int addFilm(Movie, int); // Добавить фильм после указанного
	int addFirstFilm(Movie); // Добавить фильм в начало списка

	int deleteFilm(int); // Удаляет указанный фильм
	int deleteLastFilm(); // Удаляет последний фильм
	void deleteTable(); // Удаляет таблицу целиком

	void sort(); // Отсортировать список в алфавитном порядке по названию фильма

private:
	string fileName; // Имя файла
	Movie* head; // Указатель на начало списка
	bool isEmpty; // Флаг - пуст ли список

	void swap(Movie*, Movie*); // Поменять два элемента местами
};

