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
	for (auto iter = _schema.CreateIterator(); iter != _schema.End(); ++iter)
	{
		++_schemaCount;
	}

	Buffer buffer;
	while (FileManager::GetInstance().Read(buffer))
	{
		_datas.PushBack(DataFactory::GetInstance().CreateData(&_schema, buffer));
		buffer.Clear();
		++_dataCount;
	}
}

void System::Up()
{
	cout << "Up" << endl;
	--_dataIndex;
	_dataIndex = max(0, _dataIndex);
}

void System::Down()
{
	cout << "Down" << endl;
	++_dataIndex;
	_dataIndex = min(_dataCount, _dataIndex);
}

void System::Left()
{
	cout << "Left" << endl;
	--_schemaIndex;
	_schemaIndex = max(0, _schemaIndex);
}

void System::Right()
{
	cout << "Right" << endl;
	++_schemaIndex;
	_schemaIndex = min(_schemaCount, _schemaIndex);
}

void System::CreateData()
{
	Buffer tmp;
	static char instruction[] = "Fill Data";
	tmp.Push(instruction, sizeof(instruction));
	IOManager::GetInstance().Write(tmp, stdout);

	if (_schemaCount != 0)
	{
		_datas.PushBack(DataFactory::GetInstance().CreateData(&_schema));
		++_dataIndex;
	}
}

void System::CreateField()
{
	Buffer typeTmp;
	static char typeInstruction[] = "Choose Schema Type - String : s, Interger : i, Float : f";
	typeTmp.Push(typeInstruction, sizeof(typeInstruction));
	IOManager::GetInstance().Write(typeTmp, stdout);
	Buffer typeBuffer;
	IOManager::GetInstance().Read(typeBuffer, stdin, 1);

	// need to fflush?
	Buffer nameTmp;
	static char nameInstruction[] = "Write Schema Name : ";
	nameTmp.Push(nameInstruction, sizeof(nameInstruction));
	IOManager::GetInstance().Write(nameTmp, stdout);
	Buffer nameBuffer;
	IOManager::GetInstance().Read(nameBuffer, stdin);

	char type = *typeBuffer.GetBuffer();
	const char* name = nameBuffer.GetString();
	_schema.Add(Schema::ToType(type), name);

	++_schemaIndex;
}

void System::Read()
{
	cout << "Read" << endl;
}

void System::Update()
{
	auto schemaIter = _schema.CreateIterator();
	for (int i = 0; i < _schemaCount; ++i)
	{
		++schemaIter;
	}
	Buffer name = schemaIter.Get().GetName();

	auto dataIter = _datas.Begin();
	for (int i = 0; i < _dataCount; ++i)
	{
		++dataIter;
	}
	char instruction[] = "Write data";
	Buffer instructionBuffer;
	instructionBuffer.Push(instruction, sizeof(instruction));
	IOManager::GetInstance().Write(instructionBuffer, stdout);

	Buffer data;
	IOManager::GetInstance().Read(data);

	dataIter.Get()->Update(name, data);
}

void System::DeleteData()
{
	auto iter = _datas.Begin();
	for (int i = 0; i < _dataCount; ++i)
	{
		++iter;
	}
	_datas.Erase(iter);

	--_dataIndex;
	_dataIndex = max(0, _dataIndex);
}

void System::DeleteField()
{
	auto iter = _schema.CreateIterator();
	for (int i = 0; i < _schemaCount; ++i)
	{
		++iter;
	}
	_schema.Erase(iter);
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
