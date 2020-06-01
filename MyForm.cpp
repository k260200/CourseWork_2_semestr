#include "stdafx.h"
#include "MyForm.h"

void CourseWork::MyForm::showList()
{
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

	current = head;
}

CourseWork::MyForm::MyForm(MovieLibrary * list)
{
	InitializeComponent();

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

CourseWork::MyForm::~MyForm()
{
	if (components)
	{
		delete components;
	}
}

System::Void CourseWork::MyForm::inputEl_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	head = ML->getList();

	if (act == Action::inp)
	{
		Movie m;

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

		m.name = context.marshal_as<std::string>(fName->Text);
		m.genre = context.marshal_as<std::string>(fGenre->Text);
		m.country = context.marshal_as<std::string>(fCountry->Text);
		m.productionYear = context.marshal_as<std::string>(fProdYear->Text);
		m.producer = context.marshal_as<std::string>(fProducer->Text);
		m.format = context.marshal_as<std::string>(fFormat->Text);
		m.sound = context.marshal_as<std::string>(fSound->Text);
		m.time = context.marshal_as<std::string>(fTime->Text);

		if (ML->isListEmpty())
			ML->createFirstFilm(m);
		else
			ML->addFilm(m);

		fName->Text = "Введите название";
		fGenre->Text = "Введите жанр";
		fCountry->Text = "Введите страну производства";
		fProdYear->Text = "Введите год производства";
		fProducer->Text = "Введите режиссёра";
		fFormat->Text = "Введите качество";
		fSound->Text = "Введите озвучку";
		fTime->Text = "Введите длительность";
	}
	else if (act == Action::add)
	{
		Movie m;

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

		m.name = context.marshal_as<std::string>(fName->Text);
		m.genre = context.marshal_as<std::string>(fGenre->Text);
		m.country = context.marshal_as<std::string>(fCountry->Text);
		m.productionYear = context.marshal_as<std::string>(fProdYear->Text);
		m.producer = context.marshal_as<std::string>(fProducer->Text);
		m.format = context.marshal_as<std::string>(fFormat->Text);
		m.sound = context.marshal_as<std::string>(fSound->Text);
		m.time = context.marshal_as<std::string>(fTime->Text);

		if (!chooseElNumber->Checked)
			if (!ML->isListEmpty())
			{
				ML->addFilm(m);
				MessageBox::Show("Элемент добавлен в конец списка!");
			}
			else
				MessageBox::Show("Список пуст! Прежде чем дополнять таблицу введите её с клавиатуры или загрузите из файла!");
		else
			if (!ML->isListEmpty())
			{
				if (selectedIndex > 1)
				{
					//cout << selectedIndex << endl;
					if (ML->addFilm(m, selectedIndex - 1) == 0)
						MessageBox::Show("Элемент успешно добавлен");
				}
				else if (selectedIndex == 1)
				{
					if (ML->addFirstFilm(m) == 0)
					{
						head = ML->getList();
						MessageBox::Show("Элемент успешно добавлен в начало списка");
					}
						
				}
				else
					MessageBox::Show("Сначала выберите номер элемента, после которого должна осуществляться вставка!");
			}
			else
				MessageBox::Show("Список пуст! Прежде чем дополнять таблицу введите её с клавиатуры или загрузите из файла!");

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
	else if (act == Action::del)
	{
		if (!chooseElNumber->Checked)
			if (!ML->isListEmpty())
			{
				ML->deleteLastFilm();
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
				if (selectedIndex > 0)
				{
					if (ML->deleteFilm(selectedIndex) == 0)
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

		selectedIndex = 0;
	}
	else if (act == Action::edit)
	{
		if (selectedIndex == 0)
			MessageBox::Show("Сначала выберите элемент, который хотите отредактировать");
		else
		{
			Movie m;

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

			m.name = context.marshal_as<std::string>(fName->Text);
			m.genre = context.marshal_as<std::string>(fGenre->Text);
			m.country = context.marshal_as<std::string>(fCountry->Text);
			m.productionYear = context.marshal_as<std::string>(fProdYear->Text);
			m.producer = context.marshal_as<std::string>(fProducer->Text);
			m.format = context.marshal_as<std::string>(fFormat->Text);
			m.sound = context.marshal_as<std::string>(fSound->Text);
			m.time = context.marshal_as<std::string>(fTime->Text);

			ML->setElAt(m, selectedIndex);
			MessageBox::Show("Элемент отредактирован");

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
	
	head = ML->getList();
	current = head;

	return System::Void();
}

System::Void CourseWork::MyForm::outputList_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	current = head;
	if (head == NULL)
		if (ML->isListEmpty())
		{
			MessageBox::Show("Список пуст! Прежде, чем выводить его на экран - заполните таблицу вручную или загрузите из файла.");
			return System::Void();
		}
		else
		{
			head = ML->getList();
			current = head;
		}

	this->showList();

	current = head;

	return System::Void();
}

System::Void CourseWork::MyForm::rewriteFile_Click(System::Object ^ sender, System::EventArgs ^ e)
{
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

System::Void CourseWork::MyForm::readFile_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!ML->isListEmpty())
	{
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

	this->showList();
	
	return System::Void();
}

System::Void CourseWork::MyForm::inputList_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!ML->isListEmpty())
	{
		System::Windows::Forms::DialogResult ee;

		ee = MessageBox::Show("Таблица уже введена! Если вы продолжите ввод, старые данные будут удалены - для дополнения таблицы воспользуйтесь функцией ""добавить элемент"". Продолжить?","Внимание!", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
		if (ee == System::Windows::Forms::DialogResult::Yes)
		{
			ML->deleteTable();
		}
		else
			return System::Void();
	}

	act = Action::inp;

	inputListPanel->Enabled = true;
	inputListPanel->Visible = true;

	inputEl->Text = "Ввести элемент";

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

System::Void CourseWork::MyForm::stopInputList_Click(System::Object ^ sender, System::EventArgs ^ e)
{
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
	if (!ML->isListEmpty())
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

	fName->Text = "Введите название";
	fGenre->Text = "Введите жанр";
	fCountry->Text = "Введите страну производства";
	fProdYear->Text = "Введите год производства";
	fProducer->Text = "Введите режиссёра";
	fFormat->Text = "Введите качество";
	fSound->Text = "Введите озвучку";
	fTime->Text = "Введите длительность";

	act = Action::nul;

	numberOfEl->ClearSelected();
	numberOfEl->Items->Clear();

	selectedIndex = 0;

	this->showList();

	return System::Void();
}

System::Void CourseWork::MyForm::addToList_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!ML->isListEmpty())
	{
		act = Action::add;

		chooseElNumber->Visible = true;
		chooseElNumber->Enabled = true;
		labelToPurpose->Visible = true;
		labelToPurpose->Enabled = true;

		inputListPanel->Enabled = true;
		inputListPanel->Visible = true;

		inputEl->Text = "Добавить элемент";
		labelToPurpose->Text = "для добавления";

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

System::Void CourseWork::MyForm::deleteElement_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!ML->isListEmpty())
	{
		act = Action::del;

		chooseElNumber->Visible = true;
		chooseElNumber->Enabled = true;
		labelToPurpose->Visible = true;
		labelToPurpose->Enabled = true;

		inputListPanel->Enabled = true;
		inputListPanel->Visible = true;

		inputEl->Text = "Удалить элемент";
		labelToPurpose->Text = "для удаления";

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

System::Void CourseWork::MyForm::editElement_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!ML->isListEmpty())
	{
		act = Action::edit;

		//chooseElNumber->Visible = true;
		//chooseElNumber->Enabled = true;

		numberOfEl->Visible = true;
		numberOfEl->Enabled = true;

		labelToPurpose->Visible = true;
		labelToPurpose->Enabled = true;

		inputListPanel->Enabled = true;
		inputListPanel->Visible = true;

		inputEl->Text = "Редактировать элемент";
		labelToPurpose->Text = "для изменения";

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

		fName->Enabled = false;
		fGenre->Enabled = false;
		fCountry->Enabled = false;
		fProdYear->Enabled = false;
		fProducer->Enabled = false;
		fFormat->Enabled = false;
		fSound->Enabled = false;
		fTime->Enabled = false;
	}
	else
		MessageBox::Show("Список пуст! Прежде чем удалять элементы из таблицы введите её с клавиатуры или загрузите из файла!");

	return System::Void();
}

System::Void CourseWork::MyForm::specialRequest1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	specialRequestsPanel->Enabled = true;
	specialRequestsPanel->Visible = true;

	label9->Visible = true;
	textBox1->Visible = true;

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

	label9->Text = "Введите название фильма";

	act = Action::sr1;

	return System::Void();
}

System::Void CourseWork::MyForm::specialRequest2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	specialRequestsPanel->Enabled = true;
	specialRequestsPanel->Visible = true;

	label9->Visible = true;
	textBox1->Visible = true;

	label10->Visible = true;
	textBox2->Visible = true;

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

	act = Action::sr2;

	return System::Void();
}

System::Void CourseWork::MyForm::specialRequest3_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	specialRequestsPanel->Enabled = true;
	specialRequestsPanel->Visible = true;

	label9->Visible = true;
	textBox1->Visible = true;

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

	act = Action::sr3;

	return System::Void();
}

System::Void CourseWork::MyForm::specialRequest4_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	//MessageBox::Show("Ба!");

	if (ML->isListEmpty())
	{
		MessageBox::Show("Сначала введите данные!");
		return System::Void();
	}

	Double a1 = 15, a2 = 20, a3 = 45, a4 = 5;

	chartFor4Request->Series[0]->Points->Clear();

	dataCounter dc(ML->getList());
	dc.analyse();

	for (int i = 0; i < dc.getAmountOfStats(); ++i)
	{
		chartFor4Request->Series[0]->Points->AddY(dc.getPointAt(i));
		chartFor4Request->Series[0]->Points[i]->LegendText = context.marshal_as<String^>(dc.getStatAt(i));
	}

	chartFor4Request->Enabled = true;
	chartFor4Request->Visible = true;

	specialRequest4->Text = "Обновить диаграмму";
	dc.clear();
	return System::Void();
}

System::Void CourseWork::MyForm::confirmButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	String^ text = textBox1->Text;
	while (text->Contains("  "))
		text = text->Replace("  ", " ");
	textBox1->Text = text;

	text = textBox2->Text;
	while (text->Contains("  "))
		text = text->Replace("  ", " ");
	textBox2->Text = text;

	if (ML->isListEmpty() == true)
	{
		MessageBox::Show("Таблица пуста! Сначала заполните её!");
		return System::Void();
	}

	if ( ( String::IsNullOrEmpty(textBox1->Text->ToString()) || textBox1->Text == " " ) ||
		act == Action::sr2 &&  ( String::IsNullOrEmpty(textBox2->Text->ToString()) || textBox2->Text == " ") )
	{
		MessageBox::Show("Введите требуемые данные!");
		return System::Void();
	}

	if (act == Action::sr1)
	{
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

			if (textBox1->Text->ToString() == row[Column2]->ToString())
				table->Rows->Add(row);	
			i++;
			current = current->link;
		}

		//Отображаем таблицу в визуальном компоненте
		dataGridViewForList->DataSource = table;

		current = head;
	}
	if (act == Action::sr2)
	{
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

			if (textBox1->Text->ToString() == row[Column3]->ToString() && textBox2->Text->ToString() == row[Column4]->ToString())
				table->Rows->Add(row);
			i++;
			current = current->link;
		}

		//Отображаем таблицу в визуальном компоненте
		dataGridViewForList->DataSource = table;

		current = head;
	}
	if (act == Action::sr3)
	{
		MovieLibrary* tmp = new MovieLibrary;
		head = ML->getList();
		current = head;

		std::string standart = context.marshal_as<std::string>(textBox1->Text);

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

		if (tmp->isListEmpty())
			MessageBox::Show("Фильмов этого режиссёра не найдено!");
		else
		{
			tmp->sort();

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

			tmp->deleteTable();
			delete tmp;
			head = ML->getList();
			current = head;
		}
	}

	specialRequestsPanel->Enabled = false;
	specialRequestsPanel->Visible = false;

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

	act = Action::nul;

	textBox1->Clear();
	textBox1->Clear();

	return System::Void();
}

System::Void CourseWork::MyForm::cancelButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	specialRequestsPanel->Enabled = false;
	specialRequestsPanel->Visible = false;

	specialRequestsPanel->Enabled = false;
	specialRequestsPanel->Visible = false;

	label9->Visible = false;
	textBox1->Visible = false;

	label10->Visible = false;
	textBox2->Visible = false;

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

	textBox1->Clear();
	textBox1->Clear();

	act = Action::nul;

	return System::Void();
}

System::Void CourseWork::MyForm::exitButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	System::Windows::Forms::DialogResult ee;

	ee = MessageBox::Show("Выйти из программы?", "Внимание!", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
	if (ee == System::Windows::Forms::DialogResult::Yes)
	{
		exit(0);
	}
	return System::Void();
}

System::Void CourseWork::MyForm::fName_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' && c != ':' && c != '.' && c != ',' && c != '-' && c != '!' && c != '?' && !Char::IsLetter(c) && !Char::IsControl(c) && ! Char::IsDigit(c))
		e->Handled = true;

	return System::Void();
}

System::Void CourseWork::MyForm::fGenre_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' && c != '.' && c != ',' && c != '-' && !Char::IsLetter(c) && !Char::IsControl(c))
		e->Handled = true;

	return System::Void();
}

System::Void CourseWork::MyForm::fCountry_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' &&  c != '.' && c != ',' && c != '-' && !Char::IsLetter(c) && !Char::IsControl(c))
		e->Handled = true;

	return System::Void();
}

System::Void CourseWork::MyForm::fProdYear_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	Char c = e->KeyChar;
	if (c != 8 && !Char::IsDigit(c) && !Char::IsControl(c))
		e->Handled = true;

	return System::Void();
}

System::Void CourseWork::MyForm::fProducer_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' && c != '.' && c != ',' && c != '-'  && !Char::IsLetter(c) && !Char::IsControl(c))
		e->Handled = true;

	return System::Void();
}

System::Void CourseWork::MyForm::fFormat_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' && c != ':' && c != '.' && c != ',' && c != '-' && !Char::IsLetter(c) && !Char::IsControl(c) && !Char::IsDigit(c))
		e->Handled = true;

	return System::Void();
}

System::Void CourseWork::MyForm::fSound_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' && c != ':' && c != '.' && c != ',' && c != '-' && !Char::IsLetter(c) && !Char::IsControl(c) && !Char::IsDigit(c))
		e->Handled = true;

	return System::Void();
}

System::Void CourseWork::MyForm::fTime_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' && c != ':' && c != '.' && c != ',' && !Char::IsLetter(c) && !Char::IsControl(c) && !Char::IsDigit(c))
		e->Handled = true;

	return System::Void();
}

System::Void CourseWork::MyForm::textBox1_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	Char c = e->KeyChar;
	
	if (act == Action::sr1)
		if (c != 8 && c != ' ' && c != ':' && c != '.' && c != ',' && c != '-' && c != '!' && c != '?' && !Char::IsLetter(c) && !Char::IsControl(c) && !Char::IsDigit(c))
			e->Handled = true;
	else if (act == Action::sr2 || act == Action::sr3)
		if (c != 8 && c != ' ' && c != '.' && c != ',' && c != '-' && !Char::IsLetter(c) && !Char::IsControl(c))
			e->Handled = true;

	return System::Void();
}

System::Void CourseWork::MyForm::textBox2_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	Char c = e->KeyChar;
	if (c != 8 && c != ' ' &&  c != '.' && c != ',' && c != '-' && !Char::IsLetter(c) && !Char::IsControl(c))
		e->Handled = true;

	return System::Void();
}

System::Void CourseWork::MyForm::chooseElNumber_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	numberOfEl->ClearSelected();
	numberOfEl->Items->Clear();

	if (chooseElNumber->Checked)
	{
		numberOfEl->Visible = true;
		numberOfEl->Enabled = true;

		current = ML->getList();
		int i = 1;
		numberOfEl->BeginUpdate();
		if(act == Action::add)
			numberOfEl->Items->Add("Добавить в начало списка");
		while (current)
		{
			numberOfEl->Items->Add(i.ToString() + ") " + context.marshal_as<String^>(current->name));
			current = current->link;
			i++;
		}
		numberOfEl->EndUpdate();
	}
	else
	{
		numberOfEl->Visible = false;
		numberOfEl->Enabled = false;
	}

	return System::Void();
}

System::Void CourseWork::MyForm::numberOfEl_SelectedIndexChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	selectedIndex = numberOfEl->SelectedIndex + 1;

	if (act == Action::edit)
	{
		fName->Enabled = true;
		fGenre->Enabled = true;
		fCountry->Enabled = true;
		fProdYear->Enabled = true;
		fProducer->Enabled = true;
		fFormat->Enabled = true;
		fSound->Enabled = true;
		fTime->Enabled = true;

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
