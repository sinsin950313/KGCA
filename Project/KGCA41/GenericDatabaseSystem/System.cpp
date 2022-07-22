#include "System.h"
#include <Windows.h>
#include <conio.h>
#include "IOManager.h"
#include "FileManager.h"
#include <iomanip>

System::System(const char* path)
{
	FileManager::GetInstance().Open(path);
	Read();
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

void System::Read()
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

void System::MoveCarret()
{
	COORD cur;
	cur.X = (1 + _schemaIndex) * GetNameLength();
	cur.Y = 3 + _dataIndex;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

void System::Up()
{
	--_dataIndex;
	_dataIndex = max(0, _dataIndex);
}

void System::Down()
{
	++_dataIndex;
	_dataIndex = min(_dataCount - 1, _dataIndex);
}

void System::Left()
{
	--_schemaIndex;
	_schemaIndex = max(0, _schemaIndex);
}

void System::Right()
{
	++_schemaIndex;
	_schemaIndex = min(_schemaCount - 1, _schemaIndex);
}

void System::CreateData()
{
	system("cls");
	if (_schemaCount != 0)
	{
		_datas.PushBack(DataFactory::GetInstance().CreateData(&_schema));
		++_dataCount;
	}
}

void System::CreateField()
{
	system("cls");
	Buffer typeTmp;
	static char typeInstruction[] = "Choose Schema Type - String : s, Interger : i, Float : f";
	typeTmp.Push(typeInstruction, sizeof(typeInstruction));
	IOManager::GetInstance().Write(typeTmp, stdout);
	Buffer typeBuffer;
	IOManager::GetInstance().Read(typeBuffer, stdin, 1);

	Buffer nameTmp;
	static char nameInstruction[] = "Write Schema Name : ";
	nameTmp.Push(nameInstruction, sizeof(nameInstruction));
	IOManager::GetInstance().Write(nameTmp, stdout);
	Buffer nameBuffer;
	char c;
	while ((c = fgetc(stdin)) == '\n');
	nameBuffer.Push(&c, 1);
	IOManager::GetInstance().Read(nameBuffer, stdin);

	char type = *typeBuffer.GetBuffer();
	const char* name = nameBuffer.GetString();
	_schema.Add(Schema::ToType(type), name);

	++_schemaCount;
}

void System::Update()
{
	//need to check
	auto schemaIter = _schema.CreateIterator();
	for (int i = 0; i < _schemaCount; ++i)
	{
		++schemaIter;
	}
	Buffer name;
	name.Push(schemaIter.Get().GetName(), GetNameLength());

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
	//need to check
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
	//need to check
	auto iter = _schema.CreateIterator();
	for (int i = 0; i < _schemaCount; ++i)
	{
		++iter;
	}
	_schema.Erase(iter);
}

void System::Save()
{
	Buffer schemaBuffer = _schema.GetSchema();
	char newline = '\n';
	schemaBuffer.Push(&newline, 1);
	FileManager::GetInstance().Write(schemaBuffer);

	for (auto iter = _datas.Begin(); iter != _datas.End(); ++iter)
	{
		Buffer dataBuffer = iter.Get()->Serialize();
		dataBuffer.Push(&newline, 1);
		FileManager::GetInstance().Write(dataBuffer);
	}
}

void System::PrintSchema()
{
	if (_schemaCount)
	{
		cout << "*";	//frame
		for (int i = 0; i < _schemaCount; ++i)
		{
			cout << "*";	//space
			for (int i = 0; i < GetNameLength(); ++i)
			{
				cout << "*";	//field
			}
			cout << "*";	//space
			cout << "*";	//frame
		}
		cout << endl;

		cout << "*";
		for (auto iter = _schema.CreateIterator(); iter != _schema.End(); ++iter)
		{
			cout << " " << setw(GetNameLength()) << iter.Get().GetName() << " *";
		}
		cout << endl;

		cout << "*";	//frame
		for (int i = 0; i < _schemaCount; ++i)
		{
			cout << "*";	//space
			for (int i = 0; i < GetNameLength(); ++i)
			{
				cout << "*";	//field
			}
			cout << "*";	//space
			cout << "*";	//frame
		}
		cout << endl;
	}
}

void System::PrintData()
{
	if (_dataCount)
	{
		for (auto iter = _datas.Begin(); iter != _datas.End(); ++iter)
		{
			cout << "*";
			auto dataLinkedList = iter.Get()->GetDatas();
			for (auto dataIter = dataLinkedList.Begin(); dataIter != dataLinkedList.End(); ++dataIter)
			{
				cout << " " << setw(GetNameLength()) << dataIter.Get().GetString() << " *";
			}
			cout << endl;
		}
	}
}

void System::Print()
{
	COORD cur;
	cur.X = 0;
	cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	PrintSchema();
	PrintData();
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

	MoveCarret();
}

void System::Quit()
{
	system("cls");
	exit(0);
}
