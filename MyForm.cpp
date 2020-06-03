#include "stdafx.h"
#include "MyForm.h"
#include "LoadScreen.h"

// Вывод таблицы на экран (метод)
void CourseWork::MyForm::showList()
{
	// Проверка - не пуста ли таблица
	if (ML->isListEmpty())
		return;

	// Очищаем таблицу от предыдущих данных
	dataGridViewForList->DataSource = NULL;

	// Инициализируем счётчик
	int i = 1;

	DataTable ^table; //Невидимая таблица данных
	DataColumn ^column; //Столбец таблицы
	DataRow ^row; //Строка таблицы

	//Создаем таблицу данных
	table = gcnew DataTable();

	//Названия столбцов
	String^ Column1 = "№";
	String^ Column2 = "Название";
	String^ Column3 = "Жанр";
	String^ Column4 = "Страна производства";
	String^ Column5 = "Год производства";
	String^ Column6 = "Режиссёр";
	String^ Column7 = "Качество";
	String^ Column8 = "Озвучка";
	String^ Column9 = "Длительность";

	//Создание и добавление столбцов 
	column = gcnew DataColumn(Column1, Int32::typeid);
	table->Columns->Add(column);
	column = gcnew DataColumn(Column2, String::typeid);
	table->Columns->Add(column);
	column = gcnew DataColumn(Column3, String::typeid);
	table->Columns->Add(column);
	column = gcnew DataColumn(Column4, String::typeid);
	table->Columns->Add(column);
	column = gcnew DataColumn(Column5, String::typeid);
	table->Columns->Add(column);
	column = gcnew DataColumn(Column6, String::typeid);
	table->Columns->Add(column);
	column = gcnew DataColumn(Column7, String::typeid);
	table->Columns->Add(column);
	column = gcnew DataColumn(Column8, String::typeid);
	table->Columns->Add(column);
	column = gcnew DataColumn(Column9, String::typeid);
	table->Columns->Add(column);

	// Устанавливаем указатели
	head = ML->getList();
	current = head;

	while (current != NULL) {
		//Заполняем строчку таблицы
		row = table->NewRow();
		row[Column1] = i;
		row[Column2] = context.marshal_as<String^>(current->name);
		row[Column3] = context.marshal_as<String^>(current->genre);
		row[Column4] = context.marshal_as<String^>(current->country);
		row[Column5] = context.marshal_as<String^>(current->productionYear);
		row[Column6] = context.marshal_as<String^>(current->producer);
		row[Column7] = context.marshal_as<String^>(current->format);
		row[Column8] = context.marshal_as<String^>(current->sound);
		row[Column9] = context.marshal_as<String^>(current->time);

		table->Rows->Add(row);
		i++;
		current = current->link;
	}

	//Отображаем таблицу в визуальном компоненте
	dataGridViewForList->DataSource = table;

	//Устанавливаем указатель на текущий элемент в начало списка
	current = head;
}

// Обновление данных диаграммы (метод)
void CourseWork::MyForm::updateDiag()
{
	if (!ML->isListEmpty()) // Если таблица не пуста
	{
		chartFor4Request->Series[0]->Points->Clear(); // Очищаем предыдущие данные

		dataCounter dc(ML->getList()); // Создаём объект класса dataCounter и передаём ему данные о кинотеке
		dc.analyse(); // Формируем выборку

		// Передаём графическому элементу типа Chart (диаграмма) сформированные данные
		for (int i = 0; i < dc.getAmountOfStats(); ++i)
		{
			chartFor4Request->Series[0]->Points->AddY(dc.getPointAt(i));
			chartFor4Request->Series[0]->Points[i]->LegendText = context.marshal_as<String^>(dc.getStatAt(i));
		}

		// Удаляем сформированную выборку
		dc.clear();
	}
}

// Конструктор формы
CourseWork::MyForm::MyForm(MovieLibrary * list)
{
	// Инициализируем переменные и прячем графические элементы, которые не должны быть доступны пользователю, пока не введена таблица
	InitializeComponent();

	LoadScreen^ ls = gcnew LoadScreen();
	ls->ShowDialog();

	act = Action::nul;

	selectedIndex = 0;

	numberOfEl->Visible = false;
	numberOfEl->Enabled = false;
	chooseElNumber->Visible = false;
	chooseElNumber->Enabled = false;
	labelToPurpose->Visible = false;
	labelToPurpose->Enabled = false;

	dataGridViewForList->Visible = false;

	outputList->Enabled = false;
	rewriteFile->Enabled = false;

	addToList->Enabled = false;
	deleteElement->Enabled = false;
	editElement->Enabled = false;

	specialRequest1->Enabled = false;
	specialRequest2->Enabled = false;
	specialRequest3->Enabled = false;
	specialRequest4->Enabled = false;

	chartFor4Request->Series[0]->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Pie;

	ML = list;
	head = ML->getList();
	current = head;
}

// Деструктор формы
CourseWork::MyForm::~MyForm()
{
	if (components)
	{
		delete components;
	}
}

// Нажата кнопка "ввод" на специальной панели
System::Void CourseWork::MyForm::inputEl_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	head = ML->getList(); // Получаем данные

	if (act == Action::inp) // Если панель вызвана с целью ввода списка с клавиатуры
	{
		Movie m; // Временная переменная

		// Убираем лишние пробелы из текстовых окон
		String^ text = fName->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fName->Text = text;

		text = fGenre->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fGenre->Text = text;

		text = fCountry->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fCountry->Text = text;

		text = fProducer->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fProducer->Text = text;

		text = fFormat->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fFormat->Text = text;

		text = fSound->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fSound->Text = text;

		text = fTime->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fTime->Text = text;

		// Проверяем введённые пользователем данные
		if (
			fName->Text == "Введите название" || fName->Text == "" || fName->Text == " " ||
			fGenre->Text == "Введите жанр" || fGenre->Text == "" || fGenre->Text == " " ||
			fCountry->Text == "Введите страну производства" || fCountry->Text == "" || fCountry->Text == " " ||
			fProdYear->Text == "Введите год производства" || fProdYear->Text == "" || fProdYear->Text == " " ||
			fProducer->Text == "Введите режиссёра" || fProducer->Text == "" || fProducer->Text == " " ||
			fFormat->Text == "Введите качество" || fFormat->Text == "" || fFormat->Text == " " ||
			fSound->Text == "Введите озвучку" || fSound->Text == "" || fSound->Text == " " ||
			fTime->Text == "Введите длительность" || fTime->Text == "" || fTime->Text == " ")
		{
			MessageBox::Show("Заполните все поля!");
			return System::Void();
		}

		// Преобразуем типы из управляемого Text в стандартный std::string
		m.name = context.marshal_as<std::string>(fName->Text);
		m.genre = context.marshal_as<std::string>(fGenre->Text);
		m.country = context.marshal_as<std::string>(fCountry->Text);
		m.productionYear = context.marshal_as<std::string>(fProdYear->Text);
		m.producer = context.marshal_as<std::string>(fProducer->Text);
		m.format = context.marshal_as<std::string>(fFormat->Text);
		m.sound = context.marshal_as<std::string>(fSound->Text);
		m.time = context.marshal_as<std::string>(fTime->Text);

		// В зависимости от того, пуст ли список
		if (ML->isListEmpty())
			ML->createFirstFilm(m); // Создаём первый элемент
		else
			ML->addFilm(m); // Или добавляем элемент в конец

		// Выводим текст-приглашение на тексторые поля
		fName->Text = "Введите название";
		fGenre->Text = "Введите жанр";
		fCountry->Text = "Введите страну производства";
		fProdYear->Text = "Введите год производства";
		fProducer->Text = "Введите режиссёра";
		fFormat->Text = "Введите качество";
		fSound->Text = "Введите озвучку";
		fTime->Text = "Введите длительность";
	}
	else if (act == Action::add) // Если панель вызвана с целью добавить элемент в таблицу
	{
		Movie m; // Создаём временную переменную

		// Удаляем лишние проблелы
		String^ text = fName->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fName->Text = text;

		text = fGenre->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fGenre->Text = text;

		text = fCountry->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fCountry->Text = text;

		text = fProducer->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fProducer->Text = text;

		text = fFormat->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fFormat->Text = text;

		text = fSound->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fSound->Text = text;

		text = fTime->Text;
		while (text->Contains("  "))
			text = text->Replace("  ", " ");
		fTime->Text = text;

		// Проверяем введённые данные
		if (
			fName->Text == "Введите название" || fName->Text == "" || fName->Text == " " ||
			fGenre->Text == "Введите жанр" || fGenre->Text == "" || fGenre->Text == " " ||
			fCountry->Text == "Введите страну производства" || fCountry->Text == "" || fCountry->Text == " " ||
			fProdYear->Text == "Введите год производства" || fProdYear->Text == "" || fProdYear->Text == " " ||
			fProducer->Text == "Введите режиссёра" || fProducer->Text == "" || fProducer->Text == " " ||
			fFormat->Text == "Введите качество" || fFormat->Text == "" || fFormat->Text == " " ||
			fSound->Text == "Введите озвучку" || fSound->Text == "" || fSound->Text == " " ||
			fTime->Text == "Введите длительность" || fTime->Text == "" || fTime->Text == " ")
		{
			MessageBox::Show("Заполните все поля!");
			return System::Void();
		}

		// Преобразуем их
		m.name = context.marshal_as<std::string>(fName->Text);
		m.genre = context.marshal_as<std::string>(fGenre->Text);
		m.country = context.marshal_as<std::string>(fCountry->Text);
		m.productionYear = context.marshal_as<std::string>(fProdYear->Text);
		m.producer = context.marshal_as<std::string>(fProducer->Text);
		m.format = context.marshal_as<std::string>(fFormat->Text);
		m.sound = context.marshal_as<std::string>(fSound->Text);
		m.time = context.marshal_as<std::string>(fTime->Text);

		// Добавляем элемент в список
		if (!chooseElNumber->Checked) // Если пользователь не выбрал конкретное место
			if (!ML->isListEmpty()) // Добавляем в конец
			{
				ML->addFilm(m);
				MessageBox::Show("Элемент добавлен в конец списка!");
			}
			else
				MessageBox::Show("Список пуст! Прежде чем дополнять таблицу введите её с клавиатуры или загрузите из файла!");
		else
			if (!ML->isListEmpty())
			{
				if (selectedIndex > 1) // Если пользователь выбрал, после какого из элементов должен быть добавлен новый
				{
					if (ML->addFilm(m, selectedIndex - 1) == 0) // Добавляем
						MessageBox::Show("Элемент успешно добавлен");
				}
				else if (selectedIndex == 1) // Если пользователь хочет добавить элемент в начало списка
				{
					if (ML->addFirstFilm(m) == 0) // Добавляем
					{
						head = ML->getList();
						MessageBox::Show("Элемент успешно добавлен в начало списка");
					}
						
				}
				else // Если пользователь хочет добавить элемент в конкретное место (поставлена галочка в checkBox), но не указал куда
					MessageBox::Show("Сначала выберите номер элемента, после которого должна осуществляться вставка!");
			}
			else
				MessageBox::Show("Список пуст! Прежде чем дополнять таблицу введите её с клавиатуры или загрузите из файла!");

		// Заново инициализируем некоторые компоненты после изменения списка
		current = ML->getList();
		int i = 1;
		numberOfEl->ClearSelected();
		numberOfEl->Items->Clear();
		numberOfEl->BeginUpdate();
		numberOfEl->Items->Add("Добавить в начало списка");
		while (current)
		{
			numberOfEl->Items->Add(i.ToString() + ") " + context.marshal_as<String^>(current->name));
			current = current->link;
			i++;
		}
		numberOfEl->EndUpdate();

		selectedIndex = 0;

		fName->Text = "Введите название";
		fGenre->Text = "Введите жанр";
		fCountry->Text = "Введите страну производства";
		fProdYear->Text = "Введите год производства";
		fProducer->Text = "Введите режиссёра";
		fFormat->Text = "Введите качество";
		fSound->Text = "Введите озвучку";
		fTime->Text = "Введите длительность";
	}
	else if (act == Action::del) // Если панель вызвана с целью удалить элемент
	{
		if (!chooseElNumber->Checked) // Пользователь не выбрал конкретный элемент
			if (!ML->isListEmpty())
			{
				ML->deleteLastFilm(); // Удаляем последний
				MessageBox::Show("Последний элемент успешно удалён");
				head = ML->getList();
			}
			else
			{
				MessageBox::Show("Список пуст! Прежде чем дополнять таблицу введите её с клавиатуры или загрузите из файла!");
				head = NULL;
			}
		else
			if (!ML->isListEmpty())
			{
				if (selectedIndex > 0) // Пользователь выбрал элемент для удаления
				{
					if (ML->deleteFilm(selectedIndex) == 0) // Удаляем его
						MessageBox::Show("Элемент успешно удалён");
					head = ML->getList();
				}
				else
					MessageBox::Show("Сначала выберите номер элемента, который нужно удалить!");
			}
			else
			{
				MessageBox::Show("Список пуст! Прежде чем дополнять таблицу введите её с клавиатуры или загрузите из файла!");
				head = NULL;
			}

		// Обновляем данные после удаления элементов
		int i = 1;
		numberOfEl->ClearSelected();
		numberOfEl->Items->Clear();
		numberOfEl->BeginUpdate();
		while (current)
		{
			numberOfEl->Items->Add(i.ToString() + ") " + context.marshal_as<String^>(current->name));
			current = current->link;
			i++;
		}
		numberOfEl->EndUpdate();

		selectedIndex = 0;
	}
	else if (act == Action::edit) // Панель вызвана с целью отредактироваль элемент
	{
		if (selectedIndex == 0) // Просим пользователя выбрать элемент для редактирования, если он этого не сделал
			MessageBox::Show("Сначала выберите элемент, который хотите отредактировать");
		else
		{
			Movie m;

			// Убираем пробелы
			String^ text = fName->Text;
			while (text->Contains("  "))
				text = text->Replace("  ", " ");
			fName->Text = text;

			text = fGenre->Text;
			while (text->Contains("  "))
				text = text->Replace("  ", " ");
			fGenre->Text = text;

			text = fCountry->Text;
			while (text->Contains("  "))
				text = text->Replace("  ", " ");
			fCountry->Text = text;

			text = fProducer->Text;
			while (text->Contains("  "))
				text = text->Replace("  ", " ");
			fProducer->Text = text;

			text = fFormat->Text;
			while (text->Contains("  "))
				text = text->Replace("  ", " ");
			fFormat->Text = text;

			text = fSound->Text;
			while (text->Contains("  "))
				text = text->Replace("  ", " ");
			fSound->Text = text;

			text = fTime->Text;
			while (text->Contains("  "))
				text = text->Replace("  ", " ");
			fTime->Text = text;

			// Проверяем ввод
			if (
				fName->Text == "Введите название" || fName->Text == "" || fName->Text == " " ||
				fGenre->Text == "Введите жанр" || fGenre->Text == "" || fGenre->Text == " " ||
				fCountry->Text == "Введите страну производства" || fCountry->Text == "" || fCountry->Text == " " ||
				fProdYear->Text == "Введите год производства" || fProdYear->Text == "" || fProdYear->Text == " " ||
				fProducer->Text == "Введите режиссёра" || fProducer->Text == "" || fProducer->Text == " " ||
				fFormat->Text == "Введите качество" || fFormat->Text == "" || fFormat->Text == " " ||
				fSound->Text == "Введите озвучку" || fSound->Text == "" || fSound->Text == " " ||
				fTime->Text == "Введите длительность" || fTime->Text == "" || fTime->Text == " ")
			{
				MessageBox::Show("Заполните все поля!");
				return System::Void();
			}
			
			// Преобразуем данные
			m.name = context.marshal_as<std::string>(fName->Text);
			m.genre = context.marshal_as<std::string>(fGenre->Text);
			m.country = context.marshal_as<std::string>(fCountry->Text);
			m.productionYear = context.marshal_as<std::string>(fProdYear->Text);
			m.producer = context.marshal_as<std::string>(fProducer->Text);
			m.format = context.marshal_as<std::string>(fFormat->Text);
			m.sound = context.marshal_as<std::string>(fSound->Text);
			m.time = context.marshal_as<std::string>(fTime->Text);

			// Присваиваем выбранному элементу введённое значение
			ML->setElAt(m, selectedIndex);
			MessageBox::Show("Элемент отредактирован");

			// Обновляем данные
			selectedIndex = 0;

			fName->Text = "Введите название";
			fGenre->Text = "Введите жанр";
			fCountry->Text = "Введите страну производства";
			fProdYear->Text = "Введите год производства";
			fProducer->Text = "Введите режиссёра";
			fFormat->Text = "Введите качество";
			fSound->Text = "Введите озвучку";
			fTime->Text = "Введите длительность";

			current = ML->getList();
			int i = 1;
			numberOfEl->ClearSelected();
			numberOfEl->Items->Clear();
			numberOfEl->BeginUpdate();
			while (current)
			{
				numberOfEl->Items->Add(i.ToString() + ") " + context.marshal_as<String^>(current->name));
				current = current->link;
				i++;
			}
			numberOfEl->EndUpdate();

			fName->Enabled = false;
			fGenre->Enabled = false;
			fCountry->Enabled = false;
			fProdYear->Enabled = false;
			fProducer->Enabled = false;
			fFormat->Enabled = false;
			fSound->Enabled = false;
			fTime->Enabled = false;
		}
	}
	
	// Обновляем данные ещё раз
	head = ML->getList();
	current = head;
	chooseElNumber->Checked = false;
}

// Нажата кнопка "Вывести таблицу на экран"
System::Void CourseWork::MyForm::outputList_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	current = head;
	if (head == NULL) // Если табица не пуста
		if (ML->isListEmpty())
		{
			MessageBox::Show("Список пуст! Прежде, чем выводить его на экран - заполните таблицу вручную или загрузите из файла.");
			return System::Void();
		}
		else
		{
			// Получаем данные о кинотеке
			head = ML->getList();
			current = head;
		}

	// Выводим её на экран
	this->showList();

	// обновляем данные
	current = head;

	return System::Void();
}

// Нажата кнопка "Сохранить таблицу в файл"
System::Void CourseWork::MyForm::rewriteFile_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	System::Windows::Forms::DialogResult ee;

	// Спрашиваем - хочет ли пользователь выбрать конкретное место, чтобы сохранить таблицу
	ee = MessageBox::Show("Сохранить таблицу в новом файле? (по умолчанию будет перезаписан указанный ранее файл или файл database.txt)", "Внимание!", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
	if (ee == System::Windows::Forms::DialogResult::Yes) // Если да
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			string newNameOfFile = context.marshal_as<std::string>(saveFileDialog1->FileName);
			if (newNameOfFile.empty())
			{
				MessageBox::Show("Введите название файла!");
				return System::Void();
			}
			else
				ML->setFileName(newNameOfFile); // Обновляем название файла
		}
			
	// Сохраняем таблицу в файл
	switch (ML->saveList())
	{
	case 0:
		MessageBox::Show("Файл уcпешно перезаписан.");
		break;
	case 1:
		MessageBox::Show("Не удалось открыть файл!");
		break;
	case 2:
		MessageBox::Show("Список пуст! Прежде чем перезаписывать файл введите таблицу вручную или загрузите из файла.");
		break;
	}

	return System::Void();
}

// Нажата кнопка "Загрузить таблицу из файла"
System::Void CourseWork::MyForm::readFile_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Хочет ли пользователь выбрать файл, откуда будут загружены данные?
	System::Windows::Forms::DialogResult ee;
	ee = MessageBox::Show("Загрузить таблицу из нового файла? (по умолчанию таблица будет загружена из указанного ранее файла или из файла database.txt)", "Внимание!", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
	if (ee == System::Windows::Forms::DialogResult::Yes) // Да
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			string newNameOfFile = context.marshal_as<std::string>(openFileDialog1->FileName);
			if (newNameOfFile.empty())
			{
				MessageBox::Show("Введите название файла!");
				return System::Void();
			}
			else
				ML->setFileName(newNameOfFile); // Изменяем имя файла для чтения
		}

	// Считываем данные из файла
	if (!ML->isListEmpty())
	{
		// Предупреждаем, что текущая таблица удалится
		System::Windows::Forms::DialogResult ee;
		ee = MessageBox::Show("Таблица уже введена, при продолжении она перезапишется данными из файла. Продолжить?", "Внимание!", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
		if (ee == System::Windows::Forms::DialogResult::No)
			return System::Void();
	}
	switch (ML->loadList())
	{
	case 0: 
		head = ML->getList();
		current = head;
		MessageBox::Show("Данные из файла успешно загружены.");
		break;
	case 1:
		MessageBox::Show("Не удалось открыть файл!");
		break;
	case 2:
		MessageBox::Show("Файл пуст!");
		break;
	}
	
	if (!ML->isListEmpty())
	{
		// Если после загрузки таблица не пуста - показываем другие кнопки
		outputList->Enabled = true;
		rewriteFile->Enabled = true;
		addToList->Enabled = true;
		deleteElement->Enabled = true;
		editElement->Enabled = true;
		dataGridViewForList->Visible = true;

		specialRequest1->Enabled = true;
		specialRequest2->Enabled = true;
		specialRequest3->Enabled = true;
		specialRequest4->Enabled = true;
	}

	// Вывоб таблицы на экран и обновление диаграммы
	this->showList();
	this->updateDiag();
	
	return System::Void();
}

// Пользователь запрашивает ввод данных с клавиатуры
System::Void CourseWork::MyForm::inputList_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!ML->isListEmpty())
	{
		//Предупреждаем, что текущая таблица удалится
		System::Windows::Forms::DialogResult ee;
		ee = MessageBox::Show("Таблица уже введена! Если вы продолжите ввод, старые данные будут удалены - для дополнения таблицы воспользуйтесь функцией ""добавить элемент"". Продолжить?","Внимание!", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
		if (ee == System::Windows::Forms::DialogResult::Yes)
		{
			ML->deleteTable();
		}
		else
			return System::Void();
	}

	// Устанавливаем режим ввода с клавиатуры
	act = Action::inp;

	// Выводим на форму нужные для ввода элементы
	inputListPanel->Enabled = true;
	inputListPanel->Visible = true;

	inputEl->Text = "Добавить элемент";

	// Скрываем другие графические элементы
	dataGridViewForList->Visible = false;

	inputList->Enabled = false;
	outputList->Enabled = false;
	readFile->Enabled = false;
	rewriteFile->Enabled = false;

	addToList->Enabled = false;
	deleteElement->Enabled = false;
	editElement->Enabled = false;

	specialRequest1->Enabled = false;
	specialRequest2->Enabled = false;
	specialRequest3->Enabled = false;
	specialRequest4->Enabled = false;

	return System::Void();
}

// Нажата кнопка "назад" на специальной панели
System::Void CourseWork::MyForm::stopInputList_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Прячем элементы формы
	inputListPanel->Enabled = false;
	inputListPanel->Visible = false;

	chooseElNumber->Visible = false;
	chooseElNumber->Enabled = false;
	labelToPurpose->Visible = false;
	labelToPurpose->Enabled = false;

	chooseElNumber->Checked = false;

	numberOfEl->Visible = false;
	numberOfEl->Enabled = false;

	inputList->Enabled = true;
	readFile->Enabled = true;
	if (!ML->isListEmpty()) // Если Таблица заполнена - показываем кнопки для взаимодействия с таблицей и саму таблицу
	{
		dataGridViewForList->Visible = true;

		outputList->Enabled = true;
		rewriteFile->Enabled = true;
		addToList->Enabled = true;
		deleteElement->Enabled = true;
		editElement->Enabled = true;

		specialRequest1->Enabled = true;
		specialRequest2->Enabled = true;
		specialRequest3->Enabled = true;
		specialRequest4->Enabled = true;
	}

	// Включаем другие элементы формы (они находятся на специальных панелях и всё равно невидимы)
	// Однако некоторые функции могли их спрятать - нужно вывести их, чтобы сделать возможной работу других функций
	fName->Enabled = true;
	fGenre->Enabled = true;
	fCountry->Enabled = true;
	fProdYear->Enabled = true;
	fProducer->Enabled = true;
	fFormat->Enabled = true;
	fSound->Enabled = true;
	fTime->Enabled = true;

	fName->Visible = true;
	fGenre->Visible = true;
	fCountry->Visible = true;
	fProdYear->Visible = true;
	fProducer->Visible = true;
	fFormat->Visible = true;
	fSound->Visible = true;
	fTime->Visible = true;

	label1->Visible = true;
	label2->Visible = true;
	label3->Visible = true;
	label4->Visible = true;
	label5->Visible = true;
	label6->Visible = true;
	label7->Visible = true;
	label8->Visible = true;

	// Устанавливаем режим ожидания команды
	act = Action::nul;

	// Обновляем данные
	fName->Text = "Введите название";
	fGenre->Text = "Введите жанр";
	fCountry->Text = "Введите страну производства";
	fProdYear->Text = "Введите год производства";
	fProducer->Text = "Введите режиссёра";
	fFormat->Text = "Введите качество";
	fSound->Text = "Введите озвучку";
	fTime->Text = "Введите длительность";

	

	numberOfEl->ClearSelected();
	numberOfEl->Items->Clear();

	selectedIndex = 0;

	// Выводим на экран таблицу и обновляем данные для диаграммы
	this->showList();
	this->updateDiag();

	return System::Void();
}

// Пользователь запрашивает дополнение таблицы
System::Void CourseWork::MyForm::addToList_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!ML->isListEmpty())
	{
		// Устанавливаем соответствующий режим
		act = Action::add;

		// Показываем нужные элементы формы
		chooseElNumber->Visible = true;
		chooseElNumber->Enabled = true;
		labelToPurpose->Visible = true;
		labelToPurpose->Enabled = true;

		inputListPanel->Enabled = true;
		inputListPanel->Visible = true;

		inputEl->Text = "Добавить элемент";
		labelToPurpose->Text = "для добавления";

		// Скрываем другие элементы формы
		dataGridViewForList->Visible = false;

		inputList->Enabled = false;
		outputList->Enabled = false;
		readFile->Enabled = false;
		rewriteFile->Enabled = false;

		addToList->Enabled = false;
		deleteElement->Enabled = false;
		editElement->Enabled = false;

		specialRequest1->Enabled = false;
		specialRequest2->Enabled = false;
		specialRequest3->Enabled = false;
		specialRequest4->Enabled = false;
	}
	else
		MessageBox::Show("Список пуст! Прежде чем удалять элементы из таблицы введите её с клавиатуры или загрузите из файла!");

	return System::Void();
}

// Пользователь запрашивает удаление элементов таблицы
System::Void CourseWork::MyForm::deleteElement_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!ML->isListEmpty())
	{
		// Устанавливаем режим удаления
		act = Action::del;

		// Выводим на форму нужные элементы
		chooseElNumber->Visible = true;
		chooseElNumber->Enabled = true;
		labelToPurpose->Visible = true;
		labelToPurpose->Enabled = true;

		inputListPanel->Enabled = true;
		inputListPanel->Visible = true;

		inputEl->Text = "Удалить элемент";
		labelToPurpose->Text = "для удаления";

		// Другие элементы прячем
		dataGridViewForList->Visible = false;

		inputList->Enabled = false;
		outputList->Enabled = false;
		readFile->Enabled = false;
		rewriteFile->Enabled = false;

		addToList->Enabled = false;
		deleteElement->Enabled = false;
		editElement->Enabled = false;

		specialRequest1->Enabled = false;
		specialRequest2->Enabled = false;
		specialRequest3->Enabled = false;
		specialRequest4->Enabled = false;

		fName->Enabled = false;
		fGenre->Enabled = false;
		fCountry->Enabled = false;
		fProdYear->Enabled = false;
		fProducer->Enabled = false;
		fFormat->Enabled = false;
		fSound->Enabled = false;
		fTime->Enabled = false;

		fName->Visible = false;
		fGenre->Visible = false;
		fCountry->Visible = false;
		fProdYear->Visible = false;
		fProducer->Visible = false;
		fFormat->Visible = false;
		fSound->Visible = false;
		fTime->Visible = false;

		label1->Visible = false;
		label2->Visible = false;
		label3->Visible = false;
		label4->Visible = false;
		label5->Visible = false;
		label6->Visible = false;
		label7->Visible = false;
		label8->Visible = false;
	}
	else
		MessageBox::Show("Список пуст! Прежде чем удалять элементы таблицы введите её с клавиатуры или загрузите из файла!");

	return System::Void();
}

// Пользователь запрашивает редактирование элементов таблицы
System::Void CourseWork::MyForm::editElement_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!ML->isListEmpty())
	{
		// Устанавливаем режим редактирования
		act = Action::edit;

		// Показываем нужные элементы формы
		numberOfEl->Visible = true;
		numberOfEl->Enabled = true;

		labelToPurpose->Visible = true;
		labelToPurpose->Enabled = true;

		inputListPanel->Enabled = true;
		inputListPanel->Visible = true;

		inputEl->Text = "Редактировать элемент";
		labelToPurpose->Text = "Выберите элемент \nдля изменения";

		dataGridViewForList->Visible = false;

		// Прячем не нужные элементы формы
		inputList->Enabled = false;
		outputList->Enabled = false;
		readFile->Enabled = false;
		rewriteFile->Enabled = false;

		specialRequest1->Enabled = false;
		specialRequest2->Enabled = false;
		specialRequest3->Enabled = false;
		specialRequest4->Enabled = false;

		addToList->Enabled = false;
		deleteElement->Enabled = false;
		editElement->Enabled = false;

		fName->Enabled = false;
		fGenre->Enabled = false;
		fCountry->Enabled = false;
		fProdYear->Enabled = false;
		fProducer->Enabled = false;
		fFormat->Enabled = false;
		fSound->Enabled = false;
		fTime->Enabled = false;

		// Заполняем listBox данными из кинотеки, чтобы пользователь мог выбрать элемент для редактирования
		// Здесь это нужно делать, так как в отличии от запросов на дополнение, удаление и ввод здесь нет checkBox'а
		// Именно в его обработчике изменения состояния обычно заполняется этот элемент
		current = ML->getList();
		int i = 1;
		numberOfEl->BeginUpdate();
		while (current)
		{
			numberOfEl->Items->Add(i.ToString() + ") " + context.marshal_as<String^>(current->name));
			current = current->link;
			i++;
		}
		numberOfEl->EndUpdate();
	}
	else
		MessageBox::Show("Список пуст! Прежде чем удалять элементы из таблицы введите её с клавиатуры или загрузите из файла!");

	return System::Void();
}

// Пользователь запрашивает вывод данных по названию фильма
System::Void CourseWork::MyForm::specialRequest1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Выводим на форму требуемые графические элементы
	specialRequestsPanel->Enabled = true;
	specialRequestsPanel->Visible = true;

	label9->Visible = true;
	textBox1->Visible = true;

	label10->Visible = false;
	textBox2->Visible = false;

	// Не нужные элементы прячем
	dataGridViewForList->Visible = false;

	inputList->Enabled = false;
	outputList->Enabled = false;
	readFile->Enabled = false;
	rewriteFile->Enabled = false;

	specialRequest1->Enabled = false;
	specialRequest2->Enabled = false;
	specialRequest3->Enabled = false;
	specialRequest4->Enabled = false;

	addToList->Enabled = false;
	deleteElement->Enabled = false;
	editElement->Enabled = false;

	label9->Text = "Введите название фильма";

	// Устанавливаем режим выполнения индивидуального запроса 1
	act = Action::sr1;

	return System::Void();
}

// Пользователь запрашивает вывод фильмов определённого жанра и страны
System::Void CourseWork::MyForm::specialRequest2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Выводим нужные графические элементы
	specialRequestsPanel->Enabled = true;
	specialRequestsPanel->Visible = true;

	label9->Visible = true;
	textBox1->Visible = true;

	label10->Visible = true;
	textBox2->Visible = true;

	// Не нужные прячем
	dataGridViewForList->Visible = false;

	inputList->Enabled = false;
	outputList->Enabled = false;
	readFile->Enabled = false;
	rewriteFile->Enabled = false;

	specialRequest1->Enabled = false;
	specialRequest2->Enabled = false;
	specialRequest3->Enabled = false;
	specialRequest4->Enabled = false;

	addToList->Enabled = false;
	deleteElement->Enabled = false;
	editElement->Enabled = false;

	label9->Text = "Укажите жанр фильма";
	label10->Text = "Введите страну производства фильма";

	// Устанавливаем соответствующий режим
	act = Action::sr2;

	return System::Void();
}

// Пользователь запрашивает вывод фильмов определённого режиссёра в алфавитном порядке
System::Void CourseWork::MyForm::specialRequest3_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Выводим нужные элементы на форму
	specialRequestsPanel->Enabled = true;
	specialRequestsPanel->Visible = true;

	label9->Visible = true;
	textBox1->Visible = true;

	// Другие элементы прячем
	label10->Visible = false;
	textBox2->Visible = false;

	dataGridViewForList->Visible = false;

	inputList->Enabled = false;
	outputList->Enabled = false;
	readFile->Enabled = false;
	rewriteFile->Enabled = false;

	specialRequest1->Enabled = false;
	specialRequest2->Enabled = false;
	specialRequest3->Enabled = false;
	specialRequest4->Enabled = false;

	addToList->Enabled = false;
	deleteElement->Enabled = false;
	editElement->Enabled = false;

	label9->Text = "Укажите режиссёра";

	// Устанавливаем режим выполнения индивидуального запроса номер 3
	act = Action::sr3;

	return System::Void();
}

// Пользователь запрашивает вывод диаграммы на экран (количество фильмов каждой страны-производителя)
System::Void CourseWork::MyForm::specialRequest4_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (ML->isListEmpty())
	{
		MessageBox::Show("Сначала введите данные!");
		return System::Void();
	}

	// Выводим на форму диаграммы
	if (specialRequest4->Text == "Диаграмма процентного соотношения стран - производителей фильмов")
	{
		chartFor4Request->Enabled = true;
		chartFor4Request->Visible = true;

		specialRequest4->Text = "Скрыть диаграмму";
	}
	else
	{
		chartFor4Request->Enabled = false;
		chartFor4Request->Visible = false;

		specialRequest4->Text = "Диаграмма процентного соотношения стран - производителей фильмов";
	}
	

	// Обновляем диаграмму
	this->updateDiag();
	
	return System::Void();
}

// Нажате кнопка подтверждения на специальной панели для индивидуальных запросов
System::Void CourseWork::MyForm::confirmButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Очищаем текстовые поля от лишних пробелов
	String^ text = textBox1->Text;
	while (text->Contains("  "))
		text = text->Replace("  ", " ");
	textBox1->Text = text;

	text = textBox2->Text;
	while (text->Contains("  "))
		text = text->Replace("  ", " ");
	textBox2->Text = text;

	// Следим, чтобы таблица не была пуста
	if (ML->isListEmpty() == true)
	{
		MessageBox::Show("Таблица пуста! Сначала заполните её!");
		return System::Void();
	}

	// Следим, чтобы пользователь ввёл все необходимые данные
	if ( ( String::IsNullOrEmpty(textBox1->Text->ToString()) || textBox1->Text == " " ) ||
		act == Action::sr2 &&  ( String::IsNullOrEmpty(textBox2->Text->ToString()) || textBox2->Text == " ") )
	{
		MessageBox::Show("Введите требуемые данные!");
		return System::Void();
	}
	// В зависимости от запроса выполняем различные действия
	if (act == Action::sr1) // Вывод на экран информации о фильме по названию
	{
		// Работа функции аналогична работе метода showList()

		head = ML->getList();
		current = head;

		if (ML->isListEmpty())
			return;

		dataGridViewForList->DataSource = NULL;

		int i = 1;

		DataTable ^table; //Невидимая таблица данных
		DataColumn ^column; //Столбец таблицы
		DataRow ^row; //Строка таблицы

		//Создаем таблицу данных
		table = gcnew DataTable();

		//Названия столбцов
		String^ Column1 = "№";
		String^ Column2 = "Название";
		String^ Column3 = "Жанр";
		String^ Column4 = "Страна производства";
		String^ Column5 = "Год производства";
		String^ Column6 = "Режиссёр";
		String^ Column7 = "Качество";
		String^ Column8 = "Озвучка";
		String^ Column9 = "Длительность";

		//Создание и добавление столбцов 
		column = gcnew DataColumn(Column1, Int32::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column2, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column3, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column4, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column5, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column6, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column7, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column8, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column9, String::typeid);
		table->Columns->Add(column);

		while (current != NULL) {
			//Заполняем строчку таблицы
			row = table->NewRow();
			row[Column1] = i;
			row[Column2] = context.marshal_as<String^>(current->name);
			row[Column3] = context.marshal_as<String^>(current->genre);
			row[Column4] = context.marshal_as<String^>(current->country);
			row[Column5] = context.marshal_as<String^>(current->productionYear);
			row[Column6] = context.marshal_as<String^>(current->producer);
			row[Column7] = context.marshal_as<String^>(current->format);
			row[Column8] = context.marshal_as<String^>(current->sound);
			row[Column9] = context.marshal_as<String^>(current->time);

			// Единственное отличие - в таблицу добавляются лишь те элементы, где название фильма совпадает в введённым пользователем
			if (textBox1->Text->ToString() == row[Column2]->ToString())
				table->Rows->Add(row);	
			i++;
			current = current->link;
		}

		//Отображаем таблицу в визуальном компоненте
		dataGridViewForList->DataSource = table;

		current = head;
	}
	if (act == Action::sr2) // Вывод на экран фильмов определённого жанра и страны
	{
		// Работа данной функции аналогична работе предыдущей

		head = ML->getList();
		current = head;

		if (ML->isListEmpty())
			return;

		dataGridViewForList->DataSource = NULL;

		int i = 1;

		DataTable ^table; //Невидимая таблица данных
		DataColumn ^column; //Столбец таблицы
		DataRow ^row; //Строка таблицы

		//Создаем таблицу данных
		table = gcnew DataTable();

		//Названия столбцов
		String^ Column1 = "№";
		String^ Column2 = "Название";
		String^ Column3 = "Жанр";
		String^ Column4 = "Страна производства";
		String^ Column5 = "Год производства";
		String^ Column6 = "Режиссёр";
		String^ Column7 = "Качество";
		String^ Column8 = "Озвучка";
		String^ Column9 = "Длительность";

		//Создание и добавление столбцов 
		column = gcnew DataColumn(Column1, Int32::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column2, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column3, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column4, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column5, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column6, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column7, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column8, String::typeid);
		table->Columns->Add(column);
		column = gcnew DataColumn(Column9, String::typeid);
		table->Columns->Add(column);

		while (current != NULL) {
			//Заполняем строчку таблицы
			row = table->NewRow();
			row[Column1] = i;
			row[Column2] = context.marshal_as<String^>(current->name);
			row[Column3] = context.marshal_as<String^>(current->genre);
			row[Column4] = context.marshal_as<String^>(current->country);
			row[Column5] = context.marshal_as<String^>(current->productionYear);
			row[Column6] = context.marshal_as<String^>(current->producer);
			row[Column7] = context.marshal_as<String^>(current->format);
			row[Column8] = context.marshal_as<String^>(current->sound);
			row[Column9] = context.marshal_as<String^>(current->time);

			// Единственное отличие - более строгое условие - должны совпасть и страна и жанр
			if (textBox1->Text->ToString() == row[Column3]->ToString() && textBox2->Text->ToString() == row[Column4]->ToString())
				table->Rows->Add(row);
			i++;
			current = current->link;
		}

		//Отображаем таблицу в визуальном компоненте
		dataGridViewForList->DataSource = table;

		current = head;
	}
	if (act == Action::sr3) // Вывод на экран фильмов определённого режиссёра в алфавитном порядке
	{
		// Создаём новую временную кинотеку
		MovieLibrary* tmp = new MovieLibrary;
		head = ML->getList();
		current = head;

		std::string standart = context.marshal_as<std::string>(textBox1->Text);

		// Добавляем туда элементы с требуемым именем режиссёра
		while (current)
		{
			if (current->producer == standart)
			{
				if (tmp->isListEmpty())
					tmp->createFirstFilm(*current);
				else
					tmp->addFilm(*current);
			}

			current = current->link;
		}

		// Выводим резальтат на экран
		if (tmp->isListEmpty())
			MessageBox::Show("Фильмов этого режиссёра не найдено!");
		else
		{
			// Сортируем временный список
			tmp->sort();

			// Далее функция работает идентично предыдущим
			dataGridViewForList->DataSource = NULL;

			int i = 1;

			DataTable ^table; //Невидимая таблица данных
			DataColumn ^column; //Столбец таблицы
			DataRow ^row; //Строка таблицы

			//Создаем таблицу данных
			table = gcnew DataTable();

			//Названия столбцов
			String^ Column1 = "№";
			String^ Column2 = "Название";
			String^ Column3 = "Жанр";
			String^ Column4 = "Страна производства";
			String^ Column5 = "Год производства";
			String^ Column6 = "Режиссёр";
			String^ Column7 = "Качество";
			String^ Column8 = "Озвучка";
			String^ Column9 = "Длительность";

			//Создание и добавление столбцов 
			column = gcnew DataColumn(Column1, Int32::typeid);
			table->Columns->Add(column);
			column = gcnew DataColumn(Column2, String::typeid);
			table->Columns->Add(column);
			column = gcnew DataColumn(Column3, String::typeid);
			table->Columns->Add(column);
			column = gcnew DataColumn(Column4, String::typeid);
			table->Columns->Add(column);
			column = gcnew DataColumn(Column5, String::typeid);
			table->Columns->Add(column);
			column = gcnew DataColumn(Column6, String::typeid);
			table->Columns->Add(column);
			column = gcnew DataColumn(Column7, String::typeid);
			table->Columns->Add(column);
			column = gcnew DataColumn(Column8, String::typeid);
			table->Columns->Add(column);
			column = gcnew DataColumn(Column9, String::typeid);
			table->Columns->Add(column);

			head = tmp->getList();
			current = head;

			while (current != NULL) {
				//Заполняем строчку таблицы
				row = table->NewRow();
				row[Column1] = i;
				row[Column2] = context.marshal_as<String^>(current->name);
				row[Column3] = context.marshal_as<String^>(current->genre);
				row[Column4] = context.marshal_as<String^>(current->country);
				row[Column5] = context.marshal_as<String^>(current->productionYear);
				row[Column6] = context.marshal_as<String^>(current->producer);
				row[Column7] = context.marshal_as<String^>(current->format);
				row[Column8] = context.marshal_as<String^>(current->sound);
				row[Column9] = context.marshal_as<String^>(current->time);

				table->Rows->Add(row);
				i++;
				current = current->link;
			}

			//Отображаем таблицу в визуальном компоненте
			dataGridViewForList->DataSource = table;

			// Удаляем временный список
			tmp->deleteTable();
			delete tmp;
			head = ML->getList();
			current = head;
		}
	}

	// После выполнения любого из запросов прячем связанные с ним элементы панели для индивидуальных запросов
	specialRequestsPanel->Enabled = false;
	specialRequestsPanel->Visible = false;

	// Так же выводим на форму прочие элементы
	dataGridViewForList->Visible = true;

	inputList->Enabled = true;
	outputList->Enabled = true;
	readFile->Enabled = true;
	rewriteFile->Enabled = true;

	specialRequest1->Enabled = true;
	specialRequest2->Enabled = true;
	specialRequest3->Enabled = true;
	specialRequest4->Enabled = true;

	addToList->Enabled = true;
	deleteElement->Enabled = true;
	editElement->Enabled = true;
	 
	// Переходим вв режим ожидания команд
	act = Action::nul;

	// Очищаем текстовые поля
	textBox1->Clear();
	textBox2->Clear();

	return System::Void();
}

// Нажата кнопка отмены на специальной панели для индивидуальных запросов
System::Void CourseWork::MyForm::cancelButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Прячем элементы формы
	specialRequestsPanel->Enabled = false;
	specialRequestsPanel->Visible = false;

	specialRequestsPanel->Enabled = false;
	specialRequestsPanel->Visible = false;

	label9->Visible = false;
	textBox1->Visible = false;

	label10->Visible = false;
	textBox2->Visible = false;

	// Выводим на экран другие элементы формы
	dataGridViewForList->Visible = true;

	inputList->Enabled = true;
	outputList->Enabled = true;
	readFile->Enabled = true;
	rewriteFile->Enabled = true;

	specialRequest1->Enabled = true;
	specialRequest2->Enabled = true;
	specialRequest3->Enabled = true;
	specialRequest4->Enabled = true;

	addToList->Enabled = true;
	deleteElement->Enabled = true;
	editElement->Enabled = true;

	// Очищаем текстовые поля
	textBox1->Clear();
	textBox2->Clear();

	// Переходим в режим ожидания команд
	act = Action::nul;

	return System::Void();
}

// Нажата кнопка выхода
System::Void CourseWork::MyForm::exitButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Запрашиваем подтверждение
	System::Windows::Forms::DialogResult ee;
	ee = MessageBox::Show("Выйти из программы?", "Внимание!", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
	if (ee == System::Windows::Forms::DialogResult::Yes)
	{
		// Закрываем форму
		this->Close();
	}
	return System::Void();
}

// Нажата кнопка "Справка"
System::Void CourseWork::MyForm::helpButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	// Выводим подсказки на экран
	MessageBox::Show("Эта программа разработана для курсовой работы на тему Разработка приложения с использованием динамических структур данных \nпо курсу Основы Алгоритмизации и ООП \nВариант №4 - домашняя кинотека\nВыполнил - студент группы 940, Башев К.С.");
	return System::Void();
}

// Обработчики нажатий клавиш в текстовых полях, для фильтрации запрещённых символов
	// Поле названия фильма
System::Void CourseWork::MyForm::fName_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	static int wrongClick = 1;
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' && c != ':' && c != '.' && c != ',' && c != '-' && c != '!' && c != '?' && !Char::IsLetter(c) && !Char::IsControl(c) && !Char::IsDigit(c))
	{
		e->Handled = true;
		wrongClick++;
		if (wrongClick % 5 == 1)
			MessageBox::Show("Недопустимые символы! Разрешены только буквы, цифры и знаки препинания.");
	}

	return System::Void();
}

	// Поле жанр
System::Void CourseWork::MyForm::fGenre_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	static int wrongClick = 1;
	Char c = e->KeyChar;
	if (c != 8 && c != ' '  && c != '-' && !Char::IsLetter(c) && !Char::IsControl(c))
	{
		e->Handled = true;
		wrongClick++;
		if (wrongClick % 5 == 1)
			MessageBox::Show("Недопустимые символы! Разрешены только буквы и тире.");
	}

	return System::Void();
}

	// Поле страна-производитель
System::Void CourseWork::MyForm::fCountry_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	static int wrongClick = 1;
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' && c != '-' && !Char::IsLetter(c) && !Char::IsControl(c))
	{
		e->Handled = true;
		wrongClick++;
		if (wrongClick % 5 == 1)
			MessageBox::Show("Недопустимые символы! Разрешены только буквы и тире.");
	}

	return System::Void();
}

	// Поле год производства
System::Void CourseWork::MyForm::fProdYear_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	static int wrongClick = 1;
	Char c = e->KeyChar;
	if (c != 8 && !Char::IsDigit(c) && !Char::IsControl(c))
	{
		e->Handled = true;
		wrongClick++;
		if (wrongClick % 5 == 1)
			MessageBox::Show("Недопустимые символы! Разрешены только цифры.");
	}

	return System::Void();
}

	// Поле режиссёр
System::Void CourseWork::MyForm::fProducer_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	static int wrongClick = 1;
	Char c = e->KeyChar;
	if (c != 8 && c != ' '  && c != '-'  && !Char::IsLetter(c) && !Char::IsControl(c))
	{
		e->Handled = true;
		wrongClick++;
		if (wrongClick % 5 == 1)
			MessageBox::Show("Недопустимые символы! Разрешены только буквы и тире.");
	}

	return System::Void();
}

	// Поле качество
System::Void CourseWork::MyForm::fFormat_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	static int wrongClick = 1;
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' && c != ':' && c != '.' && c != ',' && c != '-' && !Char::IsLetter(c) && !Char::IsControl(c) && !Char::IsDigit(c))
	{
		e->Handled = true;
		wrongClick++;
		if (wrongClick % 5 == 1)
			MessageBox::Show("Недопустимые символы! Разрешены только буквы, цифры и знаки препинания.");
	}

	return System::Void();
}

	// Поле звук
System::Void CourseWork::MyForm::fSound_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	static int wrongClick = 1;
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' && c != ':' && c != '.' && c != ',' && c != '-' && !Char::IsLetter(c) && !Char::IsControl(c) && !Char::IsDigit(c))
	{
		e->Handled = true;
		wrongClick++;
		if (wrongClick % 5 == 1)
			MessageBox::Show("Недопустимые символы! Разрешены только буквы, цифры и знаки препинания.");
	}

	return System::Void();
}

	// Поле длительность
System::Void CourseWork::MyForm::fTime_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	static int wrongClick = 1;
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' && c != ':' && c != '.' && c != ',' && !Char::IsLetter(c) && !Char::IsControl(c) && !Char::IsDigit(c))
	{
		e->Handled = true;
		wrongClick++;
		if (wrongClick % 5 == 1)
			MessageBox::Show("Недопустимые символы! Разрешены только буквы, цифры и знаки препинания.");
	}

	return System::Void();
}

	// Поле 1 для индивидуальных запросов
System::Void CourseWork::MyForm::textBox1_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	static int wrongClick = 1;
	Char c = e->KeyChar;
	
	// Здесь в зависимости от запросов стоят разные фильтры, соответствующие фильтрам других текстовых полей
	if (act == Action::sr1)
	{
		if (c != 8 && c != ' ' && c != ':' && c != '.' && c != ',' && c != '-' && c != '!' && c != '?' && !Char::IsLetter(c) && !Char::IsControl(c) && !Char::IsDigit(c))
		{
			e->Handled = true;
			wrongClick++;
			if (wrongClick % 5 == 1)
				MessageBox::Show("Недопустимые символы! Разрешены только буквы, цифры и знаки препинания.");
		}
	}
	else if (act == Action::sr2 || act == Action::sr3)
	{
		if (c != 8 && c != ' '  && c != '-' && !Char::IsLetter(c) && !Char::IsControl(c))
		{
			e->Handled = true;
			wrongClick++;
			if (wrongClick % 5 == 1)
				MessageBox::Show("Недопустимые символы! Разрешены только буквы и тире.");
		}
	}
		

	return System::Void();
}

	// Поле 2 для индивидуальных запросов
System::Void CourseWork::MyForm::textBox2_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	static int wrongClick = 1;
	Char c = e->KeyChar;
	// Поле два открывается при выполнении лишь одного запроса - поэтому его фильтр соответствует фильтру страны-производителя
	if (c != 8 && c != ' '  && c != '-' && !Char::IsLetter(c) && !Char::IsControl(c))
	{
		e->Handled = true;
		wrongClick++;
		if (wrongClick % 5 == 1)
			MessageBox::Show("Недопустимые символы! Разрешены только буквы и тире.");
	}

	return System::Void();
}

	// Поставлена или убрана галочка в checkBox - пользователь хочет выбрать элемент для удаления/редактирования/дополнения или наоборот скрыть listBox
System::Void CourseWork::MyForm::chooseElNumber_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	// Стираем старое выделение в listBox
	numberOfEl->ClearSelected();
	numberOfEl->Items->Clear();

	// Пользователь хочет выбрать конкретный элемент (checkBox установлен в true)
	if (chooseElNumber->Checked)
	{
		// Делаем listBox видиммым
		numberOfEl->Visible = true;
		numberOfEl->Enabled = true;

		// Заполняем его
		current = ML->getList();
		int i = 1;
		numberOfEl->BeginUpdate();
		if(act == Action::add) // При режиме добавления записываем первым элементом значение для добавления в начало списка
			numberOfEl->Items->Add("Добавить в начало списка");
		while (current)
		{
			numberOfEl->Items->Add(i.ToString() + ") " + context.marshal_as<String^>(current->name));
			current = current->link;
			i++;
		}
		numberOfEl->EndUpdate();
	}
	else // Если пользователь наоборот хочет скрыть listBox
	{
		// Прячем его
		numberOfEl->Visible = false;
		numberOfEl->Enabled = false;
	}

	return System::Void();
}

	// Изменён выбранный элемент в listBox
System::Void CourseWork::MyForm::numberOfEl_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	// Инициализируем специальную переменную для хранения номера выбранного элемента
	selectedIndex = numberOfEl->SelectedIndex + 1;

	// В зависимости от режима работы выводим на форму некоторые данные и элементы
	if (act == Action::edit)
	{
		// Даём доступ к текстовым полям, требуемым для редактирования
		fName->Enabled = true;
		fGenre->Enabled = true;
		fCountry->Enabled = true;
		fProdYear->Enabled = true;
		fProducer->Enabled = true;
		fFormat->Enabled = true;
		fSound->Enabled = true;
		fTime->Enabled = true;

		// Выводим на эти поля информацию о выбранном для редактировния элементе
		Movie* m = ML->getElAt(selectedIndex);
		if (m != NULL)
		{
			fName->Text = context.marshal_as<String^>(m->name);
			fGenre->Text = context.marshal_as<String^>(m->genre);
			fCountry->Text = context.marshal_as<String^>(m->country);
			fProdYear->Text = context.marshal_as<String^>(m->productionYear);
			fProducer->Text = context.marshal_as<String^>(m->producer);
			fFormat->Text = context.marshal_as<String^>(m->format);
			fSound->Text = context.marshal_as<String^>(m->sound);
			fTime->Text = context.marshal_as<String^>(m->time);
		}
	}

	return System::Void();
}
