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

// Присваивает указанному элементу переданное значение 
int MovieLibrary::setElAt(Movie m, int index)
{
	if (!isEmpty) // Если список не пуст
	{
		Movie* current = head; // Устанавливаем указатель на начало списка
		int i = 1; // Индекс текущего элемента (нумерация с 1)
		while (current && i <= index) // Пока не достигнем конца списка или не наткнёмся на нужный элемент
		{
			if (i == index) // Нашли эл-т
			{
				// Присваиваем ему переданное значение, link не трогаем
				current->name = m.name;
				current->genre = m.genre;
				current->country = m.country;
				current->productionYear = m.productionYear;
				current->producer = m.producer;
				current->format = m.format;
				current->sound = m.sound;
				current->time = m.time;

				// Выходим
				return 0;
			}
			current = current->link; // Переходим к следующему элементу списка
			i++; // Инкрементируем счётчик
		}
		return 2; // Возвращаем значение, если элемент не найден
	}
	return 1; // Возвращаем значение, если список пуст
}

// Возвращает указатель на указанный элемент списка
Movie * MovieLibrary::getElAt(int index)
{
	if (!isEmpty) // Если список не пуст
	{
		if (index == 1)
			return head; // Возвращаем начало списка (1-ый его эл-т)
		else
		{
			// Ищем указанный элемент
			Movie* current = head;
			int i = 1;
			while (current && i <= index)
			{
				if (i == index) // Нашли
					return current; // Возвращаем его и выходим
				current = current->link;
				i++;
			}
			return NULL; // Возвращаем NULL, если эл-т не найден
		}
	}
	return NULL; // Так же возвращаем NULL, если список пуст
}

// Возвращает указатель на начало списка
Movie * MovieLibrary::getList()
{
	return head;
}

// Говорит, пуст ли список
bool MovieLibrary::isListEmpty()
{
	return isEmpty; // Возвращаем флаг
}

// Сохранить список в файл
int MovieLibrary::saveList()
{
	if (isEmpty) // Если список пуст
		return 2; // Возвращаем код ошибки
	else
	{
		ofstream file(fileName); // Открываем файл для записи

		if (!file.is_open()) // Если не удалось открыть файл
			return 1; // Возвращаем код ошибки
		else
		{
			// Записываем список в файл
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
					file << current->time; // После последнего элемента не делаем перенос на следующую строку
				else
					file << current->time << endl; // После остальных - делаем

				current = current->link;
			}
			file.close(); // Закрываем файл
		}
	}
	return 0; // Возвращаем 0 при успешной перезаписи файла
}

// Загрузить список из файла
int MovieLibrary::loadList()
{
	ifstream file(fileName); // Открываем файл для чтения

	if (!file.is_open()) // Не удалось открыть файл
	{
		// Закрываем файл и сообщаем об ошибке
		file.close();
		return 1;
	}
	else if (file.peek() == -1 || file.peek() == 0) // Файл пуст
	{
		// Закрываем файл, сообщаем, что он пуст
		file.close();
		return 2;
	}
	else // Данные можно считывать
	{
		// Если список уже заполнен
		if (!(isEmpty && head == NULL))
			this->deleteTable(); // Удаляем его во избежание утечек

		// Считываем файл построчко
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

			if (current != NULL) // При считывании обычных элементов
			{
				current->link = tmp; // Устанавливаем link текущего узла на только что считанный
				current = tmp; // Делаем только что считанный узел текущим
			}
			else // При считывании первого элемента
				current = head = tmp; // Присваиваем указателю на началов списка и указателю на текущий элемент 
									  //адрес только что считанного узла
		}

		isEmpty = false; // Устанавливаем флаг (список больше не пуст)

		file.close(); // Закрываем файл
	}

	return 0; // Возвращаем код успешного завершения работы функции
}

// Установить имя файла (по умолчанию это database.txt)
void MovieLibrary::setFileName(string newFileName)
{
	fileName = newFileName;
}

// Создать первый элемент списка
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

// Добавить фильм (в конец списка)
void MovieLibrary::addFilm(Movie m)
{
	if (!isEmpty) // Если список не пуст
	{
		Movie* current = head;
		Movie* tmp = NULL;
		while (current->link) // Проходим до конца списка
		{
			current = current->link;
		}
		// Выделяем память под новый элемент и инициализируем его
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

		// Устанавливаем link текущего элемента на новосозданный узел
		current->link = tmp;
	}
}

// Добавить фильм после указанного
int MovieLibrary::addFilm(Movie m, int indexToAddAfter)
{
	if (isEmpty) // Если список пуст
		return 1; // Возвращаем код ошибки
	else
	{
		int i = 1; // Устанавливаем счётчик на 1
		bool found = false; // Устанавливаем флаг в false
		Movie* current = head; // Устанавливаем указатель на начало списка
		while (current && !found) // Пока не конец списка или пока не найден элемент
		{
			if (i == indexToAddAfter) // Номер элемента совпал с искомым
			{
				// Выделяем память под новый узел списка
				Movie* tmp = new Movie;
				tmp->link = current->link; // Устанавливаем link новосозданного узла на эл-т, следующий за текущим
				current->link = tmp; // Устанавливаем link текущего узла на новосозданный эл-т
				
				// Инициализируем новосозданный эл-т переданным значением
				tmp->name = m.name;
				tmp->genre = m.genre;
				tmp->country = m.country;
				tmp->productionYear = m.productionYear;
				tmp->producer = m.producer;
				tmp->format = m.format;
				tmp->sound = m.sound;
				tmp->time = m.time;

				// Устанавливаем флаг в true для выхода из цикла
				found = true;
			}
			i++; // Увеличиваем счётчик
			current = current->link; // Переходим к следующему элементу
		}
		if (!found) // Если элемент так и не был найден
			return 2; // Возвращаем код ошибки
	}

	return 0; // Сообщаем об успешном завершении функции
}

// Добавить фильм в начало списка
int MovieLibrary::addFirstFilm(Movie m)
{
	if (isEmpty)
		return 1; // Сообщаем, что список пуст
	else
	{
		// Выделяем памято под новый эл-т
		Movie* tmp = new Movie;
		tmp->link = head; // Устанавливаем его link на начало списка
		head = tmp; // Передаём в указатель на начало списка адрес нового эл-та
		
		// Инициализируем этот эл-т переданным значением
		tmp->name = m.name;
		tmp->genre = m.genre;
		tmp->country = m.country;
		tmp->productionYear = m.productionYear;
		tmp->producer = m.producer;
		tmp->format = m.format;
		tmp->sound = m.sound;
		tmp->time = m.time;
	}

	return 0; // Сообщаем, что функция отработала успешно
}

// Удаляет указанный фильм
int MovieLibrary::deleteFilm(int indexToDelete)
{
	if (isEmpty)
	{
		return 1; // Возвращаем 1, если список пуст
	}
	else if (head->link == NULL && indexToDelete == 1) // Если в таблице остался один элемент
		this->deleteTable(); // Удаляем список целиком
	else
	{
		int index = 1; // Устанавливаем счётчик
		if (indexToDelete == 1) // Если нужно удалить первый эл-т и он не единственный в списке
		{
			Movie* toDelete = head; // Запоминаем адрес начала списка
			head = head->link; // Перемещаем указатель на начало списка на следующий элемент
			delete toDelete; // Удаляем прошлый элемент
			toDelete = NULL;
			return 0; // Функция успешно отработала
		}
		// Если же удалить нужно не первый эл-т
		index++;
		Movie* current = head; // Устанавливаем указатель на начало списка
		Movie* toDelete = NULL;
		Movie* previous = NULL;
		while (current->link) // Пока не дойдём до предпоследнего элемента
		{
			toDelete = current->link; // Сохраняем адрес следующего за текущим эл-та
			if (index == indexToDelete) // Если найден эл-т, который требуется удалить
			{
				current->link = toDelete->link; // Устанавливаем link текущего эл-та на следующий за тем, который хотим удалить
				delete toDelete; // Удаляем следующий за текущим эл-т
				toDelete = NULL;
				return 0; // Функция успешно отработала
			}
			else // Если эл-т для удаления ещё не найден
			{
				index++; // Увеличиваем счётчик
				previous = current; // Сохраняем адрес текущего элемента
				current = current->link; // Переходи к следующему элементу списка
			}
		}
		// Дошли до предпоследнего эл-та
		if (index == indexToDelete) // нашли элемент для удаления - он последний
		{
			previous->link = NULL; // Устанавливаем link идущего перед текущим узла на NULL
			delete current; // Удаляем текущий элемент
			current = NULL;
			return 0; // Функция успешно отработала
		}
	}
}

// Удаляет последний фильм
int MovieLibrary::deleteLastFilm()
{
	if (isEmpty)
		return 1; // Говорим, что список пуст
	else if (head->link == NULL) // Если последний элемент - единственный в списке
		this->deleteTable(); // Удаляем весь список
	else // Если есть ещё элементы помимо него
	{
		// Работает аналогично блоку для удаления последнего элемента из функции deleteFilm()
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

// Удаляет список целиком
void MovieLibrary::deleteTable()
{
	if (!isEmpty && head != NULL) // Если список не пуст
	{
		Movie* current = head; // Устанавливаем указатель на начало списка
		Movie* toDelete = current; // Запоминаем элемент для удаления как текущий
		while (current) // Пока не конец списка
		{
			current = current->link; // Переходим к следующему элементу
			delete toDelete; // Удаляем предыдущий
			toDelete = current; // Запоминаем элемент для удаления как текущий
		}
		head = NULL; // Присваиваем указателю на начало списка значение NULL
		isEmpty = true; // Устанавливаем флаг в true (список пуст)
	}
}

// Отсортировать список в алфавитном порядке по названию фильма
void MovieLibrary::sort()
{
	Movie* current = head;
	if (head == NULL || isEmpty)
		return; // Если список пуст - завершаем работу функции
	else
	{
		bool isSorted = false; // Флаг (отсортировано) = false
		while (!isSorted) // Пока не отсортировано
		{
			isSorted = true; // Считаем, что список отсортирован
			current = head; // Устанавливаем указатель на начало списка
			while (current->link) // Пока не конец списка
			{
				if (current->name > current->link->name) // Если элементы нужно поменять местами
				{
					// Меняем их местами
					swap(current, current->link);
					isSorted = false; // Устанавливаем флаг (отсортировано) в false
				}
				current = current->link; // Переходим к следующему элементу
			}
		}
	}
}

// Поменять два элемента местами (служебная, для сортировки)
void MovieLibrary::swap(Movie *m1, Movie *m2)
{
	// Если ни один из переданных указателей не хранит NULL
	if (m1 != NULL && m2 != NULL)
	{
		// Меняем поля этих элементов местави (все, кроме link)
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
	else // Если передан хоть один пустой указатель
		return; // Выходим
}