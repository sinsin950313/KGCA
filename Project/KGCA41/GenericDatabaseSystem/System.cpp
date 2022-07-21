#include "System.h"
#include <Windows.h>
#include <conio.h>
#include "IOManager.h"
#include "FileManager.h"

System::System(const char* path)
{
	FileManager::GetInstance().Open(path);
	Load();
}

void System::Run()
{
	Print();
	fflush(stdin);
	char order = _getch();
	system("cls");
	Transaction(order);
}

void System::Transaction(char order)
{
	InstructionManual();

	char c;
	switch (order)
	{
	case 'h': case 'H':
		Left();
		break;
	case 'j': case 'J':
		Down();
		break;
	case 'k': case 'K':
		Up();
		break;
	case 'l': case 'L':
		Right();
		break;
	case 'c': case 'C':
		if ((c = _getch()) == 'd' || c == 'D')
		{
			CreateData();
		}
		else if (c == 's' || c == 'S')
		{
			CreateField();
		}
		break;
	case 'd': case 'D':
		if ((c = _getch()) == 'd' || c == 'D')
		{
			DeleteData();
		}
		else if (c == 's' || c == 'S')
		{
			DeleteField();
		}
		break;
	case 'e': case 'E':
		Update();
		break;
	case 's': case 'S':
		Save();
		break;
	case 'q': case 'Q':
		Quit();
		break;
	default:
		break;
	}
}

void System::Load()
{
	Buffer schemaBuffer;
	FileManager::GetInstance().Read(schemaBuffer);
	_schema.Set(schemaBuffer);

	Buffer buffer;
	while (FileManager::GetInstance().Read(buffer))
	{
		//_datas.PushBack(DataFactory::GetInstance().CreateData(&_schema, buffer));
		CreateData(buffer);
		buffer.Clear();
	}
}

void System::Up()
{
	--_dataIndex;
	_dataIndex = max(0, _dataIndex);
}

void System::Down()
{
	++_dataIndex;
	_dataIndex = min(_dataCount, _dataIndex);
}

void System::Left()
{
	--_schemaIndex;
	_schemaIndex = max(0, _schemaIndex);
}

void System::Right()
{
	++_schemaIndex;
	_schemaIndex = min(_schemaCount, _schemaIndex);
}

void System::CreateData()
{
	cout << "Create Data" << endl;

	_datas.PushBack(DataFactory::GetInstance().CreateData(&_schema, ));
	++_dataIndex;
}

void System::CreateField()
{
	cout << "Create Schema" << endl;

	++_schemaIndex;
}

void System::Read()
{
	cout << "Read" << endl;
}

void System::Update()
{
	cout << "Update" << endl;
}

void System::DeleteData()
{
	cout << "Delete Data" << endl;

	--_dataIndex;
	_dataIndex = max(0, _dataIndex);
}

void System::DeleteField()
{
	cout << "Delete Schema" << endl;

	--_schemaIndex;
	_schemaIndex = max(0, _schemaIndex);
}

void System::Save()
{
	cout << "Save" << endl;
}

void System::Print()
{
	// print Data template
	InstructionManual();
}

void System::InstructionManual()
{
	//https://stackoverflow.com/a/23370070/8106257
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	char str1[] = "Left : h, Down : j, Up : k, Right : l";
	COORD cur;
	cur.X = columns - sizeof(str1);
	cur.Y = rows - 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	cout << str1;

	char str2[] = "Create Data : cd, Create Schema : cs, Delete Data : dd, Delete Schema : ds, Edit : e, Save : s, Quit : q";
	cur.X = columns - sizeof(str2);
	cur.Y = rows - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	cout << str2;

	cur.X = 0;
	cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void System::Quit()
{
	exit(0);
}
