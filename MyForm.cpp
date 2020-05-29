#include "stdafx.h"
#include "MyForm.h"

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
			fName->Text == "������� ��������" || fName->Text == "" || fName->Text == " " ||
			fGenre->Text == "������� ����" || fGenre->Text == "" || fGenre->Text == " " ||
			fCountry->Text == "������� ������ ������������" || fCountry->Text == "" || fCountry->Text == " " ||
			fProdYear->Text == "������� ��� ������������" || fProdYear->Text == "" || fProdYear->Text == " " ||
			fProducer->Text == "������� ��������" || fProducer->Text == "" || fProducer->Text == " " ||
			fFormat->Text == "������� ��������" || fFormat->Text == "" || fFormat->Text == " " ||
			fSound->Text == "������� �������" || fSound->Text == "" || fSound->Text == " " ||
			fTime->Text == "������� ������������" || fTime->Text == "" || fTime->Text == " ")
		{
			MessageBox::Show("��������� ��� ����!");
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

		fName->Text = "������� ��������";
		fGenre->Text = "������� ����";
		fCountry->Text = "������� ������ ������������";
		fProdYear->Text = "������� ��� ������������";
		fProducer->Text = "������� ��������";
		fFormat->Text = "������� ��������";
		fSound->Text = "������� �������";
		fTime->Text = "������� ������������";
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
			fName->Text == "������� ��������" || fName->Text == "" || fName->Text == " " ||
			fGenre->Text == "������� ����" || fGenre->Text == "" || fGenre->Text == " " ||
			fCountry->Text == "������� ������ ������������" || fCountry->Text == "" || fCountry->Text == " " ||
			fProdYear->Text == "������� ��� ������������" || fProdYear->Text == "" || fProdYear->Text == " " ||
			fProducer->Text == "������� ��������" || fProducer->Text == "" || fProducer->Text == " " ||
			fFormat->Text == "������� ��������" || fFormat->Text == "" || fFormat->Text == " " ||
			fSound->Text == "������� �������" || fSound->Text == "" || fSound->Text == " " ||
			fTime->Text == "������� ������������" || fTime->Text == "" || fTime->Text == " ")
		{
			MessageBox::Show("��������� ��� ����!");
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
				MessageBox::Show("������� �������� � ����� ������!");
			}
			else
				MessageBox::Show("������ ����! ������ ��� ��������� ������� ������� � � ���������� ��� ��������� �� �����!");
		else
			if (!ML->isListEmpty())
			{
				if (selectedIndex > 1)
				{
					//cout << selectedIndex << endl;
					if (ML->addFilm(m, selectedIndex - 1) == 0)
						MessageBox::Show("������� ������� ��������");
				}
				else if (selectedIndex == 1)
				{
					if (ML->addFirstFilm(m) == 0)
					{
						head = ML->getList();
						MessageBox::Show("������� ������� �������� � ������ ������");
					}
						
				}
				else
					MessageBox::Show("������� �������� ����� ��������, ����� �������� ������ �������������� �������!");
			}
			else
				MessageBox::Show("������ ����! ������ ��� ��������� ������� ������� � � ���������� ��� ��������� �� �����!");

		current = ML->getList();
		int i = 1;
		numberOfEl->ClearSelected();
		numberOfEl->Items->Clear();
		numberOfEl->BeginUpdate();
		numberOfEl->Items->Add("�������� � ������ ������");
		while (current)
		{
			numberOfEl->Items->Add(i.ToString() + ") " + context.marshal_as<String^>(current->name));
			current = current->link;
			i++;
		}
		numberOfEl->EndUpdate();

		selectedIndex = 0;

		fName->Text = "������� ��������";
		fGenre->Text = "������� ����";
		fCountry->Text = "������� ������ ������������";
		fProdYear->Text = "������� ��� ������������";
		fProducer->Text = "������� ��������";
		fFormat->Text = "������� ��������";
		fSound->Text = "������� �������";
		fTime->Text = "������� ������������";
	}
	else if (act == Action::del)
	{
		if (!chooseElNumber->Checked)
			if (!ML->isListEmpty())
			{
				ML->deleteLastFilm();
				MessageBox::Show("��������� ������� ������� �����");
			}
			else
				MessageBox::Show("������ ����! ������ ��� ��������� ������� ������� � � ���������� ��� ��������� �� �����!");
		else
			if (!ML->isListEmpty())
			{
				if (selectedIndex > 0)
				{
					if (ML->deleteFilm(selectedIndex) == 0)
						MessageBox::Show("������� ������� �����");
				}
				else
					MessageBox::Show("������� �������� ����� ��������, ����� �������� ������ �������������� �������!");
			}
			else
				MessageBox::Show("������ ����! ������ ��� ��������� ������� ������� � � ���������� ��� ��������� �� �����!");

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

	}
	
	current = head;

	return System::Void();
}

System::Void CourseWork::MyForm::outputList_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	current = head;
	int i = 1;
	if (head == NULL)
		if (ML->isListEmpty())
		{
			MessageBox::Show("������ ����! ������, ��� �������� ��� �� ����� - ��������� ������� ������� ��� ��������� �� �����.");
			return System::Void();
		}
		else
		{
			head = ML->getList();
			current = head;
		}

	dataGridViewForList->DataSource = NULL;

	DataTable ^table; //��������� ������� ������
	DataColumn ^column; //������� �������
	DataRow ^row; //������ �������

	//������� ������� ������
	table = gcnew DataTable();

	//�������� ��������
	String^ Column1 = "�";
	String^ Column2 = "��������";
	String^ Column3 = "����";
	String^ Column4 = "������ ������������";
	String^ Column5 = "��� ������������";
	String^ Column6 = "�������";
	String^ Column7 = "��������";
	String^ Column8 = "�������";
	String^ Column9 = "������������";

	//�������� � ���������� �������� 
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


	while(current != NULL) {
		//��������� ������� �������
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

	//���������� ������� � ���������� ����������
	dataGridViewForList->DataSource = table;

	current = head;

	return System::Void();
}

System::Void CourseWork::MyForm::rewriteFile_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	switch (ML->saveList())
	{
	case 0:
		MessageBox::Show("���� �c����� �����������.");
		break;
	case 1:
		MessageBox::Show("�� ������� ������� ����!");
		break;
	case 2:
		MessageBox::Show("������ ����! ������ ��� �������������� ���� ������� ������� ������� ��� ��������� �� �����.");
		break;
	}

	return System::Void();
}

System::Void CourseWork::MyForm::readFile_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!ML->isListEmpty())
	{
		System::Windows::Forms::DialogResult ee;

		ee = MessageBox::Show("������� ��� �������, ��� ����������� ��� ������������� ������� �� �����. ����������?", "��������!", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
		if (ee == System::Windows::Forms::DialogResult::No)
			return System::Void();
	}
	switch (ML->loadList())
	{
	case 0: 
		head = ML->getList();
		current = head;
		MessageBox::Show("������ �� ����� ������� ���������.");
		//MyForm::outputList_Click(this, &MyForm::inputList_Click);
		//outputList_Click(this, this->outputList_Click);
		break;
	case 1:
		MessageBox::Show("�� ������� ������� ����!");
		break;
	case 2:
		MessageBox::Show("���� ����!");
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
	}
	
	return System::Void();
}

System::Void CourseWork::MyForm::inputList_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!ML->isListEmpty())
	{
		System::Windows::Forms::DialogResult ee;

		ee = MessageBox::Show("������� ��� �������! ���� �� ���������� ����, ������ ������ ����� ������� - ��� ���������� ������� �������������� �������� ""�������� �������"". ����������?","��������!", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
		if (ee == System::Windows::Forms::DialogResult::Yes)
		{
			ML->~MovieLibrary();
		}
		else
			return System::Void();
	}

	act = Action::inp;

	inputListPanel->Enabled = true;
	inputListPanel->Visible = true;

	inputEl->Text = "������ �������";

	dataGridViewForList->Visible = false;

	inputList->Enabled = false;
	outputList->Enabled = false;
	readFile->Enabled = false;
	rewriteFile->Enabled = false;

	addToList->Enabled = false;
	deleteElement->Enabled = false;
	editElement->Enabled = false;

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

	act = Action::nul;

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

		inputEl->Text = "�������� �������";
		labelToPurpose->Text = "��� ����������";

		dataGridViewForList->Visible = false;

		inputList->Enabled = false;
		outputList->Enabled = false;
		readFile->Enabled = false;
		rewriteFile->Enabled = false;

		addToList->Enabled = false;
		deleteElement->Enabled = false;
		editElement->Enabled = false;
	}
	else
		MessageBox::Show("������ ����! ������ ��� ������� �������� �� ������� ������� � � ���������� ��� ��������� �� �����!");

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

		inputEl->Text = "������� �������";
		labelToPurpose->Text = "��� ��������";

		dataGridViewForList->Visible = false;

		inputList->Enabled = false;
		outputList->Enabled = false;
		readFile->Enabled = false;
		rewriteFile->Enabled = false;

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
		MessageBox::Show("������ ����! ������ ��� ��������� ������� ������� � � ���������� ��� ��������� �� �����!");

	return System::Void();
}

System::Void CourseWork::MyForm::editElement_Click(System::Object ^ sender, System::EventArgs ^ e)
{
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
			numberOfEl->Items->Add("�������� � ������ ������");
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

	return System::Void();
}