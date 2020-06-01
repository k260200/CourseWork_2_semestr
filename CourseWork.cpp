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

//#include "dataCounter.h"

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup");

using namespace System;
using namespace System::Windows::Forms;
using namespace CourseWork;

[STAThread]
//int main(array<System::String ^> ^args)
int main(cli::array < String^> ^ args)
{
	MovieLibrary ml;
	//ml.loadList();
	//dataCounter dc(ml.getList());
	//dc.analyse();
	//for (int i = 0; i < dc.getAmountOfStats(); ++i)
	//	std::cout << dc.getStatAt(i) << " - " << dc.getPointAt(i) << std::endl;
	Application::EnableVisualStyles();
	Application::Run(gcnew MyForm(&ml));

	//system("pause");
	return 0;
}
