#pragma once

#include "stdafx.h"

#include <iostream>
#include <string>
#include "Windows.h"

#include <msclr\marshal_cppstd.h>

#include "MovieLibrary.h"

namespace CourseWork {

	using namespace std;

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public enum class Action { nul, inp, add, del, edit };

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		// Мои поля
	public:
		int selectedIndex;
		Action act;
		MovieLibrary* ML;
		Movie* current;
		Movie* head;
		msclr::interop::marshal_context context;
	public:
	private: System::Windows::Forms::Panel^  inputListPanel;
	private: System::Windows::Forms::Button^  stopInputList;
	private: System::Windows::Forms::Button^  inputList;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  addToList;
	private: System::Windows::Forms::Button^  deleteElement;
	private: System::Windows::Forms::Button^  editElement;
	private: System::Windows::Forms::Label^  labelToPurpose;
	private: System::Windows::Forms::CheckBox^  chooseElNumber;
	private: System::Windows::Forms::ListBox^  numberOfEl;

	private: System::Windows::Forms::DataGridView^  dataGridViewForList;

	public:
		MyForm(MovieLibrary* list);

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm();

	private: System::Windows::Forms::TextBox^  fName;
	protected:
	private: System::Windows::Forms::TextBox^  fGenre;
	private: System::Windows::Forms::TextBox^  fCountry;
	private: System::Windows::Forms::TextBox^  fProdYear;
	private: System::Windows::Forms::TextBox^  fProducer;
	private: System::Windows::Forms::TextBox^  fFormat;
	private: System::Windows::Forms::TextBox^  fSound;
	private: System::Windows::Forms::TextBox^  fTime;
	private: System::Windows::Forms::Button^  inputEl;
	private: System::Windows::Forms::Button^  outputList;
	private: System::Windows::Forms::Button^  rewriteFile;
	private: System::Windows::Forms::Button^  readFile;




	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->fName = (gcnew System::Windows::Forms::TextBox());
			this->fGenre = (gcnew System::Windows::Forms::TextBox());
			this->fCountry = (gcnew System::Windows::Forms::TextBox());
			this->fProdYear = (gcnew System::Windows::Forms::TextBox());
			this->fProducer = (gcnew System::Windows::Forms::TextBox());
			this->fFormat = (gcnew System::Windows::Forms::TextBox());
			this->fSound = (gcnew System::Windows::Forms::TextBox());
			this->fTime = (gcnew System::Windows::Forms::TextBox());
			this->inputEl = (gcnew System::Windows::Forms::Button());
			this->rewriteFile = (gcnew System::Windows::Forms::Button());
			this->readFile = (gcnew System::Windows::Forms::Button());
			this->dataGridViewForList = (gcnew System::Windows::Forms::DataGridView());
			this->outputList = (gcnew System::Windows::Forms::Button());
			this->inputListPanel = (gcnew System::Windows::Forms::Panel());
			this->labelToPurpose = (gcnew System::Windows::Forms::Label());
			this->chooseElNumber = (gcnew System::Windows::Forms::CheckBox());
			this->numberOfEl = (gcnew System::Windows::Forms::ListBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->stopInputList = (gcnew System::Windows::Forms::Button());
			this->inputList = (gcnew System::Windows::Forms::Button());
			this->addToList = (gcnew System::Windows::Forms::Button());
			this->deleteElement = (gcnew System::Windows::Forms::Button());
			this->editElement = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewForList))->BeginInit();
			this->inputListPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// fName
			// 
			this->fName->Location = System::Drawing::Point(172, 4);
			this->fName->Name = L"fName";
			this->fName->Size = System::Drawing::Size(361, 20);
			this->fName->TabIndex = 0;
			this->fName->Text = L"Введите название";
			this->fName->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::fName_KeyPress);
			// 
			// fGenre
			// 
			this->fGenre->Location = System::Drawing::Point(172, 30);
			this->fGenre->Name = L"fGenre";
			this->fGenre->Size = System::Drawing::Size(361, 20);
			this->fGenre->TabIndex = 1;
			this->fGenre->Text = L"Введите жанр";
			this->fGenre->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::fGenre_KeyPress);
			// 
			// fCountry
			// 
			this->fCountry->Location = System::Drawing::Point(172, 56);
			this->fCountry->Name = L"fCountry";
			this->fCountry->Size = System::Drawing::Size(361, 20);
			this->fCountry->TabIndex = 2;
			this->fCountry->Text = L"Введите страну производства";
			this->fCountry->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::fCountry_KeyPress);
			// 
			// fProdYear
			// 
			this->fProdYear->Location = System::Drawing::Point(172, 84);
			this->fProdYear->Name = L"fProdYear";
			this->fProdYear->Size = System::Drawing::Size(361, 20);
			this->fProdYear->TabIndex = 3;
			this->fProdYear->Text = L"Введите год производства";
			this->fProdYear->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::fProdYear_KeyPress);
			// 
			// fProducer
			// 
			this->fProducer->Location = System::Drawing::Point(172, 110);
			this->fProducer->Name = L"fProducer";
			this->fProducer->Size = System::Drawing::Size(361, 20);
			this->fProducer->TabIndex = 4;
			this->fProducer->Text = L"Введите режиссёра";
			this->fProducer->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::fProducer_KeyPress);
			// 
			// fFormat
			// 
			this->fFormat->Location = System::Drawing::Point(172, 136);
			this->fFormat->Name = L"fFormat";
			this->fFormat->Size = System::Drawing::Size(361, 20);
			this->fFormat->TabIndex = 5;
			this->fFormat->Text = L"Введите качество";
			this->fFormat->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::fFormat_KeyPress);
			// 
			// fSound
			// 
			this->fSound->Location = System::Drawing::Point(172, 162);
			this->fSound->Name = L"fSound";
			this->fSound->Size = System::Drawing::Size(361, 20);
			this->fSound->TabIndex = 6;
			this->fSound->Text = L"Введите озвучку";
			this->fSound->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::fSound_KeyPress);
			// 
			// fTime
			// 
			this->fTime->Location = System::Drawing::Point(172, 188);
			this->fTime->Name = L"fTime";
			this->fTime->Size = System::Drawing::Size(361, 20);
			this->fTime->TabIndex = 7;
			this->fTime->Text = L"Введите длительность";
			this->fTime->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::fTime_KeyPress);
			// 
			// inputEl
			// 
			this->inputEl->Location = System::Drawing::Point(172, 323);
			this->inputEl->Name = L"inputEl";
			this->inputEl->Size = System::Drawing::Size(168, 23);
			this->inputEl->TabIndex = 8;
			this->inputEl->Text = L"Ввести элемент";
			this->inputEl->UseVisualStyleBackColor = true;
			this->inputEl->Click += gcnew System::EventHandler(this, &MyForm::inputEl_Click);
			// 
			// rewriteFile
			// 
			this->rewriteFile->Location = System::Drawing::Point(12, 89);
			this->rewriteFile->Name = L"rewriteFile";
			this->rewriteFile->Size = System::Drawing::Size(177, 23);
			this->rewriteFile->TabIndex = 10;
			this->rewriteFile->Text = L"Сохранить таблицу в файл";
			this->rewriteFile->UseVisualStyleBackColor = true;
			this->rewriteFile->Click += gcnew System::EventHandler(this, &MyForm::rewriteFile_Click);
			// 
			// readFile
			// 
			this->readFile->Location = System::Drawing::Point(12, 37);
			this->readFile->Name = L"readFile";
			this->readFile->Size = System::Drawing::Size(177, 23);
			this->readFile->TabIndex = 11;
			this->readFile->Text = L"Загрузить таблицу из файла";
			this->readFile->UseVisualStyleBackColor = true;
			this->readFile->Click += gcnew System::EventHandler(this, &MyForm::readFile_Click);
			// 
			// dataGridViewForList
			// 
			this->dataGridViewForList->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridViewForList->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridViewForList->Location = System::Drawing::Point(254, 13);
			this->dataGridViewForList->Name = L"dataGridViewForList";
			this->dataGridViewForList->Size = System::Drawing::Size(1036, 625);
			this->dataGridViewForList->TabIndex = 12;
			// 
			// outputList
			// 
			this->outputList->Location = System::Drawing::Point(12, 63);
			this->outputList->Name = L"outputList";
			this->outputList->Size = System::Drawing::Size(177, 23);
			this->outputList->TabIndex = 13;
			this->outputList->Text = L"Вывести таблицу на экран";
			this->outputList->UseVisualStyleBackColor = true;
			this->outputList->Click += gcnew System::EventHandler(this, &MyForm::outputList_Click);
			// 
			// inputListPanel
			// 
			this->inputListPanel->Controls->Add(this->labelToPurpose);
			this->inputListPanel->Controls->Add(this->chooseElNumber);
			this->inputListPanel->Controls->Add(this->numberOfEl);
			this->inputListPanel->Controls->Add(this->label8);
			this->inputListPanel->Controls->Add(this->label7);
			this->inputListPanel->Controls->Add(this->label6);
			this->inputListPanel->Controls->Add(this->label5);
			this->inputListPanel->Controls->Add(this->label4);
			this->inputListPanel->Controls->Add(this->label3);
			this->inputListPanel->Controls->Add(this->label2);
			this->inputListPanel->Controls->Add(this->label1);
			this->inputListPanel->Controls->Add(this->stopInputList);
			this->inputListPanel->Controls->Add(this->fName);
			this->inputListPanel->Controls->Add(this->fGenre);
			this->inputListPanel->Controls->Add(this->fCountry);
			this->inputListPanel->Controls->Add(this->fProdYear);
			this->inputListPanel->Controls->Add(this->fProducer);
			this->inputListPanel->Controls->Add(this->inputEl);
			this->inputListPanel->Controls->Add(this->fFormat);
			this->inputListPanel->Controls->Add(this->fTime);
			this->inputListPanel->Controls->Add(this->fSound);
			this->inputListPanel->Enabled = false;
			this->inputListPanel->Location = System::Drawing::Point(354, 40);
			this->inputListPanel->Name = L"inputListPanel";
			this->inputListPanel->Size = System::Drawing::Size(559, 377);
			this->inputListPanel->TabIndex = 14;
			this->inputListPanel->Visible = false;
			// 
			// labelToPurpose
			// 
			this->labelToPurpose->AutoSize = true;
			this->labelToPurpose->Location = System::Drawing::Point(33, 235);
			this->labelToPurpose->Name = L"labelToPurpose";
			this->labelToPurpose->Size = System::Drawing::Size(37, 13);
			this->labelToPurpose->TabIndex = 20;
			this->labelToPurpose->Text = L"для ...";
			// 
			// chooseElNumber
			// 
			this->chooseElNumber->AutoSize = true;
			this->chooseElNumber->Location = System::Drawing::Point(9, 215);
			this->chooseElNumber->Name = L"chooseElNumber";
			this->chooseElNumber->Size = System::Drawing::Size(157, 17);
			this->chooseElNumber->TabIndex = 19;
			this->chooseElNumber->Text = L"Выбрать номер элемента";
			this->chooseElNumber->UseVisualStyleBackColor = true;
			this->chooseElNumber->CheckedChanged += gcnew System::EventHandler(this, &MyForm::chooseElNumber_CheckedChanged);
			// 
			// numberOfEl
			// 
			this->numberOfEl->FormattingEnabled = true;
			this->numberOfEl->Location = System::Drawing::Point(172, 215);
			this->numberOfEl->Name = L"numberOfEl";
			this->numberOfEl->Size = System::Drawing::Size(361, 82);
			this->numberOfEl->TabIndex = 18;
			this->numberOfEl->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::numberOfEl_SelectedIndexChanged);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(10, 191);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(123, 13);
			this->label8->TabIndex = 17;
			this->label8->Text = L"Длительность фильма";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(84, 165);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(49, 13);
			this->label7->TabIndex = 16;
			this->label7->Text = L"Озвучка";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(79, 139);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(54, 13);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Качество";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(75, 113);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(58, 13);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Режиссёр";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(34, 87);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(99, 13);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Год производства";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(16, 59);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(117, 13);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Страна производства";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(97, 33);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(36, 13);
			this->label2->TabIndex = 11;
			this->label2->Text = L"Жанр";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(33, 7);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(100, 13);
			this->label1->TabIndex = 10;
			this->label1->Text = L"Название фильма";
			// 
			// stopInputList
			// 
			this->stopInputList->Location = System::Drawing::Point(369, 323);
			this->stopInputList->Name = L"stopInputList";
			this->stopInputList->Size = System::Drawing::Size(164, 23);
			this->stopInputList->TabIndex = 9;
			this->stopInputList->Text = L"Стоп";
			this->stopInputList->UseVisualStyleBackColor = true;
			this->stopInputList->Click += gcnew System::EventHandler(this, &MyForm::stopInputList_Click);
			// 
			// inputList
			// 
			this->inputList->Location = System::Drawing::Point(12, 13);
			this->inputList->Name = L"inputList";
			this->inputList->Size = System::Drawing::Size(177, 23);
			this->inputList->TabIndex = 15;
			this->inputList->Text = L"Ввести список с клавиатуры";
			this->inputList->UseVisualStyleBackColor = true;
			this->inputList->Click += gcnew System::EventHandler(this, &MyForm::inputList_Click);
			// 
			// addToList
			// 
			this->addToList->Location = System::Drawing::Point(12, 140);
			this->addToList->Name = L"addToList";
			this->addToList->Size = System::Drawing::Size(177, 23);
			this->addToList->TabIndex = 16;
			this->addToList->Text = L"Дополнить таблицу";
			this->addToList->UseVisualStyleBackColor = true;
			this->addToList->Click += gcnew System::EventHandler(this, &MyForm::addToList_Click);
			// 
			// deleteElement
			// 
			this->deleteElement->Location = System::Drawing::Point(12, 170);
			this->deleteElement->Name = L"deleteElement";
			this->deleteElement->Size = System::Drawing::Size(177, 23);
			this->deleteElement->TabIndex = 17;
			this->deleteElement->Text = L"Удалить элемент";
			this->deleteElement->UseVisualStyleBackColor = true;
			this->deleteElement->Click += gcnew System::EventHandler(this, &MyForm::deleteElement_Click);
			// 
			// editElement
			// 
			this->editElement->Location = System::Drawing::Point(13, 200);
			this->editElement->Name = L"editElement";
			this->editElement->Size = System::Drawing::Size(176, 23);
			this->editElement->TabIndex = 18;
			this->editElement->Text = L"Удалить элемент";
			this->editElement->UseVisualStyleBackColor = true;
			this->editElement->Click += gcnew System::EventHandler(this, &MyForm::editElement_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1330, 650);
			this->Controls->Add(this->editElement);
			this->Controls->Add(this->deleteElement);
			this->Controls->Add(this->addToList);
			this->Controls->Add(this->inputList);
			this->Controls->Add(this->inputListPanel);
			this->Controls->Add(this->outputList);
			this->Controls->Add(this->dataGridViewForList);
			this->Controls->Add(this->readFile);
			this->Controls->Add(this->rewriteFile);
			this->Location = System::Drawing::Point(13, 309);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewForList))->EndInit();
			this->inputListPanel->ResumeLayout(false);
			this->inputListPanel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void fName_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void fGenre_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void fCountry_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void fProdYear_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void fProducer_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void fFormat_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void fSound_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
private: System::Void fTime_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);

private: System::Void chooseElNumber_CheckedChanged(System::Object^  sender, System::EventArgs^  e);

private: System::Void numberOfEl_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);

private: System::Void inputEl_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void outputList_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void rewriteFile_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void readFile_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void inputList_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void stopInputList_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void addToList_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void deleteElement_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void editElement_Click(System::Object^  sender, System::EventArgs^  e);
};
}
