#include "stdafx.h"
#include "dataCounter.h"

// Конструктор, принимающий указатель на список фильмов, по которому должна составляться выборка
dataCounter::dataCounter(Movie* hd)
{
	head = hd;
	amountOfStats = 0;
	all = 0;
}

dataCounter::~dataCounter()
{
	this->clear();
}

// Обработка данных, составление выборки
int dataCounter::analyse()
{
	all = 0;
	if(head == NULL)
		return 1; // Выходим, если кинотека пуста
	else
	{
		Movie* current = head; // Устанавливаем указатель на начало кинотеки
		while (current) // Пока не конец кинотеки
		{
			int add = -1;
			if (amountOfStats == 0) // Добавляем первую страну в выборку
			{
				stats.push_back(current->country);
				points.push_back(1);
				amountOfStats++;
				all++;
			}
			else // Выполняем проверку для последующих эл-тов
			{
				add = thereIsSameStat(current->country); // Встречалась ли эта страна
				if (add != -1) // Да
					points.at(add)++; // Увеличиваем счётчик фильмов этой страны
				else // Нет
				{
					stats.push_back(current->country); // Добавляем страну в выборку
					points.push_back(1);
					amountOfStats++;
					all++;
				}
			}

			current = current->link; // Устанавливаем указатель на следующий элемент
		}
	}

	return 0;
}

// Удаление выборки
void dataCounter::clear()
{
	stats.clear();
	points.clear();
	amountOfStats = 0;
}

// Получить количество стран-производителей в выборке
int dataCounter::getAmountOfStats()
{
	return stats.size();
}

// Получить название определённой страны-производителя из выборки
string dataCounter::getStatAt(int index)
{
	return stats.at(index);
}

// Получить количество фильмов, произведённых в указанной стране
int dataCounter::getPointAt(int index)
{
	return points.at(index);
}

// Служебная функция для проверки уникальности указанной страны
int dataCounter::thereIsSameStat(string st)
{
	for (int i = 0; i < stats.size(); i++)
		if (stats.at(i) == st)
			return i;
	return -1;
}
