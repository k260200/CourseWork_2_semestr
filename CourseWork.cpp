//#include "stdafx.h"
//
//using namespace System;
//
//int main(array<System::String ^> ^args)
//{
//    return 0;
//}


#include "stdafx.h"
#include <iostream>
#include "MyForm.h"

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup");

using namespace System;
using namespace System::Windows::Forms;
using namespace CourseWork;

[STAThread]
//int main(array<System::String ^> ^args)
int main(cli::array < String^> ^ args)
{
	MovieLibrary ml;
	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm(&ml));

	return 0;
}
