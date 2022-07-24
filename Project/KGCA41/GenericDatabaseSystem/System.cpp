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
	cur.X = 1 + (1 + _schemaIndex) * GetNameLength() + (_schemaIndex * 2) + _schemaIndex;
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
	_schemaIndex = min(_schemaCount - 1 - _deletedSchema, _schemaIndex);
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

	for (auto iter = _datas.Begin(); iter != _datas.End(); ++iter)
	{
		iter.Get()->NewSchema(type);
	}
}

void System::Update()
{
	if (_dataCount)
	{
		auto schemaIter = _schema.CreateIterator();
		int tmpIndexCounter = 0;
		while (tmpIndexCounter < _schemaIndex)
		{
			if (schemaIter.Get().IsAlive())
			{
				++tmpIndexCounter;
			}
			++schemaIter;
		}
		while (!schemaIter.Get().IsAlive())
		{
			++schemaIter;
		}
		Buffer name;
		name.Push(schemaIter.Get().GetName(), GetNameLength());

		auto dataIter = _datas.Begin();
		for (int i = 0; i < _dataIndex; ++i)
		{
			++dataIter;
		}

		system("cls");
		PrintSchema();
		if (_dataCount)
		{
			int tmpDataIndex = 0;
			for (auto iter = _datas.Begin(); iter != _datas.End(); ++iter)
			{
				int tmpSchemaIndex = 0;
				cout << "*";
				auto dataLinkedList = iter.Get()->GetDatas();
				auto tmpSchemaIter = _schema.CreateIterator();
				for (auto dataIter = dataLinkedList.Begin(); dataIter != dataLinkedList.End(); ++dataIter)
				{
					if (tmpSchemaIter.Get().IsAlive())
					{
						if (tmpSchemaIndex == _schemaIndex && tmpDataIndex == _dataIndex)
						{
							cout << " " << setw(GetNameLength()) << "Edit Here" << " *";
						}
						else
						{
							cout << " " << setw(GetNameLength()) << dataIter.Get().GetString() << " *";
						}
						++tmpSchemaIndex;
					}
					++tmpSchemaIter;
				}
				cout << endl;
				++tmpDataIndex;
			}
		}

		Buffer data;
		IOManager::GetInstance().Read(data);

		dataIter.Get()->Update(name, data);
	}
}

void System::DeleteData()
{
	if (_dataCount)
	{
		auto iter = _datas.Begin();
		for (int i = 0; i < _dataIndex; ++i)
		{
			++iter;
		}
		_datas.Erase(iter);

		--_dataCount;
		_dataCount = max(0, _dataCount);
	}
}

void System::DeleteField()
{
	if (_schemaCount)
	{
		auto schemaIter = _schema.CreateIterator();
		int tmpIndexCounter = 0;
		while (tmpIndexCounter < _schemaIndex)
		{
			if (schemaIter.Get().IsAlive())
			{
				++tmpIndexCounter;
			}
			++schemaIter;
		}
		while (!schemaIter.Get().IsAlive())
		{
			++schemaIter;
		}
		_schema.Erase(schemaIter);

		++_deletedSchema;
		_deletedSchema = min(_schemaCount, _deletedSchema);
	_schemaIndex = min(_schemaCount - 1 - _deletedSchema, _schemaIndex);
	}
}

void System::Save()
{
	FileManager::GetInstance().Reopen();

	Buffer schemaBuffer = _schema.GetSchema();
	char newline = '\n';
	schemaBuffer.Push(&newline, 1);
	FileManager::GetInstance().Write(schemaBuffer);

	for (auto iter = _datas.Begin(); iter != _datas.End(); ++iter)
	{
		Buffer dataBuffer = iter.Get()->Serialize(true);
		dataBuffer.Push(&newline, 1);
		FileManager::GetInstance().Write(dataBuffer);
	}
}

void System::PrintSchema()
{
	auto schemaIter = _schema.CreateIterator();
	if (_schemaCount - _deletedSchema)
	{
		cout << "*";	//frame
		for (int i = 0; i < _schemaCount; ++i)
		{
			if (schemaIter.Get().IsAlive())
			{
				cout << "*";	//space
				for (int i = 0; i < GetNameLength(); ++i)
				{
					cout << "*";	//field
				}
				cout << "*";	//space
				cout << "*";	//frame
			}
			++schemaIter;
		}
		cout << endl;

		cout << "*";
		for (auto iter = _schema.CreateIterator(); iter != _schema.End(); ++iter)
		{
			if (iter.Get().IsAlive())
			{
				cout << " " << setw(GetNameLength()) << iter.Get().GetName() << " *";
			}
		}
		cout << endl;

		schemaIter = _schema.CreateIterator();
		cout << "*";	//frame
		for (int i = 0; i < _schemaCount; ++i)
		{
			if (schemaIter.Get().IsAlive())
			{
				cout << "*";	//space
				for (int i = 0; i < GetNameLength(); ++i)
				{
					cout << "*";	//field
				}
				cout << "*";	//space
				cout << "*";	//frame
			}
			++schemaIter;
		}
		cout << endl;
	}
	else
	{
		system("cls");
		Buffer instruction;
		char instructionStr[] = "Create Schema First";
		instruction.Push(instructionStr, sizeof(instructionStr));
		IOManager::GetInstance().Write(instruction, stdout);
	}
}

void System::PrintData()
{
	if (_schemaCount - _deletedSchema)
	{
		for (auto iter = _datas.Begin(); iter != _datas.End(); ++iter)
		{
			cout << "*";

			auto schemaIter = _schema.CreateIterator();
			auto dataLinkedList = iter.Get()->GetDatas();
			for (auto dataIter = dataLinkedList.Begin(); dataIter != dataLinkedList.End(); ++dataIter)
			{
				if (schemaIter.Get().IsAlive())
				{
					cout << " " << setw(GetNameLength()) << dataIter.Get().GetString() << " *";
				}
				++schemaIter;
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

	system("cls");
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
