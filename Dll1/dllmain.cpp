// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <psapi.h>
#include <tchar.h>
#include <fstream>
#include <string>

extern "C" __declspec(dllexport) int CreateF_WriteF_in_Reestr(const WCHAR*);
extern "C" __declspec(dllexport) int ReadF(HANDLE);

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH://присоед к процессу
    case DLL_THREAD_ATTACH:// присоед к потоку
    case DLL_THREAD_DETACH://  отсоед от потока
    case DLL_PROCESS_DETACH: // отсоед от процесса
        break;
    }
    return TRUE;
}

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383
#define CHILD_NAME_SIZE 1024

int OpenTag(HANDLE hFile, const WCHAR* TagName) {
    WriteFile(hFile, L"\n\t<", lstrlenW(L"\n\t<") * sizeof(WCHAR), NULL, NULL);
    WriteFile(hFile, TagName, lstrlenW(TagName) * sizeof(WCHAR), NULL, NULL);
    WriteFile(hFile, L">", 1 * sizeof(WCHAR), NULL, NULL);
    return 0;
}

//p
int CloseTag(HANDLE hFile, const WCHAR* TagName) {
    WriteFile(hFile, L"</", 2 * sizeof(WCHAR), NULL, NULL);
    WriteFile(hFile, TagName, lstrlenW(TagName) * sizeof(WCHAR), NULL, NULL);
    WriteFile(hFile, L">", 1 * sizeof(WCHAR), NULL, NULL);
    return 0;
}

int GetAllRegistry(HKEY parent, const int tabulation, HANDLE OutputFile) {
    HKEY curent_key;
    size_t Razmer_str;
    HKEY child_key;
    LSTATUS last_status;
    DWORD child_index = 0;
    LPWSTR child_name;  //массив юникодных сиволов
 

    int i, j = 0;
    child_name = (LPWSTR)malloc(CHILD_NAME_SIZE * sizeof(wchar_t)); // вычисление памяти

    last_status = RegOpenKeyW(parent, NULL, &curent_key);
    if (last_status != ERROR_SUCCESS) {
        free(child_name);
        return -1;
    }

    while (RegEnumKeyW(curent_key, child_index++, child_name, CHILD_NAME_SIZE) == ERROR_SUCCESS) {
        for (i = 0; i < tabulation; ++i) {
            WriteFile(OutputFile, L" ", 1 * sizeof(wchar_t), NULL, NULL); // запись пробелов, 1 (кол-во байт у строки) умножается на 2 байта sizeof
        }

        Razmer_str = wcslen(child_name);  // wcslen - подсчет байтов в строке массива child_name
  
        OpenTag(OutputFile, L"SUBSECTION");
        WriteFile(OutputFile, child_name, Razmer_str * sizeof(wchar_t), NULL, NULL); // запись основной информации (переменная child_name)
        CloseTag(OutputFile, L"SUBSECTION");
        OpenTag(OutputFile, L"KEY_VALUE");

        last_status = RegOpenKeyW(curent_key, child_name, &child_key);
        GetAllRegistry(child_key, tabulation + 1, OutputFile);
        CloseTag(OutputFile, L"KEY_VALUE");
    }

    free(child_name);
    return 0;
}

int CreateF_WriteF_in_Reestr(const WCHAR* filePath) {
    const WCHAR* all_names[] = { L"\tHKEY_CLASSES_ROOT", L"\tHKEY_CURRENT_CONFIG",
L"\tHKEY_CURRENT_USER",
L"\tHKEY_LOCAL_MACHINE",
L"\tHKEY_USERS" };

    HKEY all_classes[] = { HKEY_CLASSES_ROOT,
    HKEY_CURRENT_CONFIG,
    HKEY_CURRENT_USER,
    HKEY_LOCAL_MACHINE,
    HKEY_USERS };

    size_t Razmer_str;
    int i = 0;
    HANDLE  Reestr = (HANDLE)malloc(sizeof(HANDLE));
    //Дискриптор
    Reestr = CreateFileW(filePath,
        GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL); // создание файла

    for (int i = 0; i < 5; ++i) { // проход по ветвям реестра
        Razmer_str = wcslen(all_names[i]); // wcslen - подсчет байтов в строке i массива all_names
        OpenTag(Reestr, L"REGISTRY_BRANCH");
        OpenTag(Reestr, L"REGISTRY_BRANCH_NAME");

        WriteFile(Reestr, all_names[i], Razmer_str * sizeof(wchar_t), NULL, NULL); //запись информации i-той ветви реестра
        CloseTag(Reestr, L"REGISTRY_BRANCH_NAME");
        GetAllRegistry(all_classes[i], 1, Reestr); // функция и аргументы с 15 строки, это нужно, чтобы проходить по всем веткам реестра
        CloseTag(Reestr, L"REGISTRY_BRANCH");
    }

    CloseHandle(Reestr); // в CloseHandle передается функция открытия файла
    return 0;
}

int ReadF(HANDLE  FileProc) {

    DWORD bytes_was_readen;
    WCHAR Bufffer_for_Read;
    BOOL was_readen;
    WCHAR one_symbol;
    //const WCHAR* filePath_proverka;
    HANDLE  Proverka = (HANDLE)malloc(sizeof(HANDLE));
    
    Proverka = CreateFileW(L"D:Proverka.xml",
        GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL); // создание файла
    BOOL End_of_File = TRUE;
    was_readen = ReadFile(FileProc, &Bufffer_for_Read, 1 * sizeof(wchar_t), &bytes_was_readen, NULL);
    while (was_readen!=0x0) {

        //was_readen;
        while (End_of_File = (ReadFile(FileProc, &one_symbol, 1 * sizeof(wchar_t), &bytes_was_readen, NULL) && (one_symbol != L'h'))) {
        //while (End_of_File = (ReadFile(FileProc, &one_symbol, 1 * sizeof(wchar_t), &bytes_was_readen, NULL) && (one_symbol != L'<'))) {
            was_readen;

        }

        End_of_File = (ReadFile(FileProc, &one_symbol, 1 * sizeof(wchar_t), &bytes_was_readen, NULL));
        if (one_symbol == '/')
            continue;
        else
            WriteFile(Proverka, &one_symbol, 1 * sizeof(wchar_t), NULL, NULL);

        while (End_of_File = (ReadFile(FileProc, &one_symbol, 1 * sizeof(wchar_t), &bytes_was_readen, NULL) && (one_symbol != L'/') && (one_symbol != L'<'))) {
        //while (End_of_File = (ReadFile(FileProc, &one_symbol, 1 * sizeof(wchar_t), &bytes_was_readen, NULL) && (one_symbol != L'>'))) {
            //was_readen;
            
            //if (End_of_File = (ReadFile(FileProc, &one_symbol, 1 * sizeof(wchar_t), &bytes_was_readen, NULL) && (one_symbol != L'<'))) {

           
            WriteFile(Proverka, &one_symbol, 1 * sizeof(wchar_t), NULL, NULL);
            //}
        }
        WriteFile(Proverka, L"\n", 1 * sizeof(wchar_t), NULL, NULL);
    }




    CloseHandle(Proverka);
    return 0;
}

int Findlib(HANDLE  FileProc) {
    DWORD cbNeeded;
    DWORD cProcesses;
    unsigned int i;




    return 0;
}

