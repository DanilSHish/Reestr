#include "MyForm.h"
#include <Windows.h>
#include <Windows.h>
#include <iostream>
#include <psapi.h>
#include <tchar.h>
#include <fstream>
//using namespace std;
using namespace guiv2;
[STAThread]

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    //->SetApartmentState(ApartmentState.STA);
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MyForm);
    return 0;
}
