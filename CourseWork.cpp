// Точка входа приложения

#include "stdafx.h"
#include <iostream>

#include "MyForm.h" // Подключаем класс для работы с интерфейсом

using namespace System;
using namespace System::Windows::Forms;
using namespace CourseWork;

[STAThread]
int main(cli::array < String^> ^ args)
{
	// Создаём кинотеку
	MovieLibrary ml;

	// Создаём интерфейс
	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm(&ml));

	return 0;
}
