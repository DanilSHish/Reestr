#pragma once
#include "MyForm.h"
#include <fstream>
#include <Windows.h>
#include <psapi.h>
#include <tchar.h>
#include <vcclr.h>

typedef int(WINAPI *fCreate) (const WCHAR*);
typedef int(WINAPI* fRead) (HANDLE);

namespace guiv2 {

	using namespace System;
	//using namespace System::a
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:




	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button3;




	private: System::ComponentModel::IContainer^ components;


	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(35, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(195, 43);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Сохранение информации о реестре";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(35, 182);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(195, 29);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Получение имен библиотек";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 91);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(249, 20);
			this->textBox1->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(62, 75);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(128, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Путь сохранения файла";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(108, 127);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 4;
			this->button3->Text = L"button3";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(273, 223);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}


#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (textBox1->Text != "") {


			HMODULE lib = 0;
			lib = LoadLibrary(L"Dll1.dll");

			if (lib == 0) {
				MessageBox::Show("Библиотека Dll1.dll не найдена!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				Close();
			}
			fCreate CreateF_WriteF_in_Reestr;
			CreateF_WriteF_in_Reestr = (fCreate)GetProcAddress(lib, "CreateF_WriteF_in_Reestr");
			if (CreateF_WriteF_in_Reestr == NULL) {
				MessageBox::Show("Функция не найдена!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				Close();
			}
			/*
			SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;
			saveFileDialog1->Filter = "(*.xml)|*.xml";
			saveFileDialog1->ShowDialog();
			textBox1->Text = saveFileDialog1->FileName;//////////////////////////////////////////////////////////////////////////////////////////////////////////////
			String^ path = saveFileDialog1->FileName;
			//MessageBox::Show("Пожалуйста подожите", "Важно ", MessageBoxButtons::OK, MessageBoxIcon::Information);
		*/

			String^ path = (textBox1->Text);
			int STR_LEN = path->Length;
			WCHAR* WideStr = (WCHAR*)malloc((path->Length + 1) * sizeof(WCHAR));
			array<WCHAR>^ Wpath = gcnew array<WCHAR>(STR_LEN);
			path->CopyTo(0, Wpath, 0, path->Length);
			for (unsigned int i = 0; i < Wpath->Length; ++i) {
				WideStr[i] = Wpath[i];
			}
			WideStr[path->Length] = 0x0;
			if (WideStr == NULL) {
				MessageBox::Show("WideStr = 0", "Ошибка ", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			//textBox1->Text(WideStr);
			//textBox1->Text(WideStr);
			CreateF_WriteF_in_Reestr(WideStr);
		}
		else 
		MessageBox::Show("Выберите путь сохраннения файла", "Ошибка ", MessageBoxButtons::OK, MessageBoxIcon::Error);
		
	}

	//MessageBox::Show("WideStr = 0", "Ошибка ", MessageBoxButtons::OK, MessageBoxIcon::Error);

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	HANDLE XML;
	WCHAR Bufffer_for_Read;
	HMODULE lib = 0;
	lib = LoadLibrary(L"Dll1.dll");

	if (lib == 0) {
		MessageBox::Show("Библиотека Dll1.dll не найдена!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		Close();
	}
	fRead ReadF;
	ReadF = (fRead)GetProcAddress(lib, "ReadF");
	if (ReadF == NULL) {
		MessageBox::Show("Функция ReadFile не найдена!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		Close();
	}
	OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
	openFileDialog1->Filter = "XML | *.xml";
	openFileDialog1->ShowDialog();
	String^ path = openFileDialog1->FileName;

	int STR_LEN = path->Length;
	WCHAR* WideStr = (WCHAR*)malloc((path->Length + 1) * sizeof(WCHAR));
	array<WCHAR>^ Wpath = gcnew array<WCHAR>(STR_LEN);
	path->CopyTo(0, Wpath, 0, path->Length);
	for (unsigned int i = 0; i < Wpath->Length; ++i) {
		WideStr[i] = Wpath[i];
	}
	WideStr[path->Length] = 0x0;
	if (WideStr == NULL) {
		MessageBox::Show("WideStr = 0", "Ошибка ", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	/*
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		MessageBox::Show("Файл открыт", "Отлично", MessageBoxButtons::OK, MessageBoxIcon::Information);
		Close();
	}*/


	XML = CreateFileW(WideStr,
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL); 
	ReadF(XML);

}

private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;
	saveFileDialog1->Filter = "(*.xml)|*.xml";
	saveFileDialog1->ShowDialog();
	textBox1->Text = saveFileDialog1->FileName;//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//String^ path = saveFileDialog1->FileName;
}
};
}
