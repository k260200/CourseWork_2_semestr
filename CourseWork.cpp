// ����� ����� ����������

#include "stdafx.h"
#include <iostream>

#include "MyForm.h" // ���������� ����� ��� ������ � �����������

using namespace System;
using namespace System::Windows::Forms;
using namespace CourseWork;

[STAThread]
int main(cli::array < String^> ^ args)
{
	// ������ ��������
	MovieLibrary ml;

	// ������ ���������
	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm(&ml));

	return 0;
}
