#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include "addressbook.pb.h"
using namespace std;

tutorial::AddressBook address_book;
tutorial::Person john;


TCHAR szName[] = TEXT("comunicationInstructor-Simbox");
#define BUF_SIZE 10000

int _tmain(int argc, _TCHAR* argv[])
{
	_tprintf(TEXT("READER C++\n"));
	_tprintf(TEXT("Memory-Mapped file example. Press any key to read new data, Esc to exit\n"));

	HANDLE hMapFile;
	char* pBuf;

	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS, // read/write access
		FALSE, // do not inherit the name
		szName); // name of mapping object

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not open file mapping object %s (error %d).\n"), szName, GetLastError());
		_getch();
		return 1;
	}

	char ch;
	do // repeat until escape is pressed
	{
		pBuf = (char*)MapViewOfFile(hMapFile, // handle to map object
			FILE_MAP_ALL_ACCESS, // read/write permission
			0,
			0,
			BUF_SIZE);
		if (pBuf == NULL)
		{
			_tprintf(TEXT("Could not map view of file (%d).\n"), GetLastError());
			CloseHandle(hMapFile);
			_getch();
			return 1;
		}

		// Read strings from the buffer
		//char *currentBuf = &pBuf[0];

		string currentBuf(pBuf);
		
		
		_tprintf(TEXT("\nData in MMF:\n"));
		/*do
		{*/
			// C# BinaryWriter writes the string by prefixing to the string a single byte or
			// word that contains the length of that string.
			// This method first writes the length of the string as a UTF-7 encoded unsigned
			// integer, and then writes that many characters to the stream by using the
			// BinaryWriter instance's current encoding.
			int strLen = currentBuf[0]; // read length of the string
			//int len1 = (sizeof(currentBuf) / sizeof(currentBuf[0]));
			//int len2 = std::strlen((const char*)currentBuf);
			//int len3 = sizeof(currentBuf);

			/*unsigned char *str = (unsigned char*)currentBuf;
										 
			std::string myString(reinterpret_cast<char*>(str));


			char *str1 = new char[strLen + 1];
			for (int i = 0; i<strLen; i++)
				str1[i] = currentBuf[i];
			
			str1[strLen] = 0;*/
			

			//string myString();

			//address_book.ParseFromArray(currentBuf, strLen);
			address_book.ParseFromString(currentBuf);			

			for (int i = 0; i < address_book.people_size(); i++) {
				const tutorial::Person& person = address_book.people(i);
				
				cout << "Person ID: " << person.id() << endl;
				cout << "Name: " << person.name() << endl;	
				

				if (person.email() != "")
				{
					cout << "Email " << person.email() << endl;
				}

				if (person.has_email())
				{
					cout << "Email " << person.email() << endl;
				}				

				for (int j = 0; j < person.phones_size(); j++) {
					const tutorial::Person::PhoneNumber& phone_number = person.phones(j);

					switch (phone_number.type()) {
					case tutorial::Person::MOBILE:
						cout << "Mobile phone #: ";
						break;
					case tutorial::Person::HOME:
						cout << "Home phone #: ";
						break;
					case tutorial::Person::WORK:
						cout << "Work phone #: ";
						break;
					}
					cout << phone_number.number() << endl;
				}
			}

			

			/*_tprintf(TEXT("%s\n"), str);
			delete[] str;*/
			//currentBuf = &currentBuf[strLen];
		//} while (currentBuf[0] != 0);

		UnmapViewOfFile(pBuf);

		ch = _getch();

	} while (ch != 27); // repeat until escape is pressed

	CloseHandle(hMapFile);

	return 0;
}