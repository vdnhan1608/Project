#include"StructStudent.h"
#include"Student.h"
#include<iostream>
#include<fstream>
#include<string>
#include<io.h>
#include<fcntl.h>
#include<locale>
#include<codecvt>
using namespace std;

void Input(string path, wstring& str, Student*& pHead)
{
	wifstream FileIn;
	FileIn.open(path);
	const locale utf8_locale(locale(), new codecvt_utf8<wchar_t>());
	_setmode(_fileno(stdin), _O_U16TEXT);
	if (FileIn.is_open() == false) cout << "FileIn cannot be opened." << endl; else cout << "FileIn can be opened" << endl;
	FileIn.imbue(utf8_locale);
	getline(FileIn, str);
	Student* pCur = nullptr;
	getline(FileIn, str);
	while (!FileIn.eof() && str != L"") {

		if (pHead == nullptr)
		{
			pHead = new Student;
			SetUp(str, pHead);
			pHead->pNext = nullptr;
			pCur = pHead;
		}
		else {
			pCur->pNext = new Student;
			pCur = pCur->pNext;
			SetUp(str, pCur);
			pCur->pNext = nullptr;
		}
		getline(FileIn, str);
	}
	FileIn.close();
}


void SetUp(wstring str, Student*& pHead)
{
	int lc1 = 1, lc2 = 0, i = 2;
	wstring temp = L"";
	string tempInt = "";
	string tempString = "";
	wchar_t ch = str[i];
	// Get Student ID
	while (ch != ',') { i++; ch = str[i]; }
	lc2 = i;
	for (i = lc1 + 1; i < lc2; i++) tempInt += str[i];
	int x = atoi(tempInt.c_str());
	pHead->ID = x;

	// Get First Name
	lc1 = lc2;
	i = lc2 + 1;
	ch = str[i];
	while (ch != ',') { i++; ch = str[i]; }
	lc2 = i;
	for (i = lc1 + 1; i < lc2; i++) temp += str[i];
	pHead->First_Name = temp;

	//Get Last Name
	lc1 = lc2;
	i = lc2 + 1;
	ch = str[i];
	while (ch != ',') { i++; ch = str[i]; }
	lc2 = i;
	temp = L"";
	for (i = lc1 + 1; i < lc2; i++) temp += str[i];
	pHead->Last_Name = temp;

	//Get gender
	lc1 = lc2;
	i = lc2 + 1;
	ch = str[i];
	while (ch != ',') { i++; ch = str[i]; }
	lc2 = i;
	tempString = "";
	for (i = lc1 + 1; i < lc2; i++) tempString += str[i];
	if (tempString == "Male")
		pHead->Gender = 1; else pHead->Gender = 0;

	//Get Date of Birth
	lc1 = lc2;
	i = lc2 + 1;
	ch = str[i];
	while (ch != ',') { i++; ch = str[i]; }
	lc2 = i;
	tempString = "";
	for (i = lc1 + 1; i < lc2; i++) tempString += str[i];
	pHead->DateOfBirth = tempString;

	//Get Social ID
	lc1 = lc2;
	i = lc2 + 1;
	ch = str[i];
	while (ch != ',') { i++; ch = str[i]; }
	lc2 = i;
	tempInt = "";
	for (i = lc1 + 1; i < lc2; i++) tempInt += str[i];
	x = atoi(tempInt.c_str());
	pHead->Social_ID = x;

	//Get username
	lc1 = lc2;
	i = lc2 + 1;
	ch = str[i];
	while (ch != ',') { i++; ch = str[i]; }
	lc2 = i;
	tempString = "";
	for (i = lc1 + 1; i < lc2; i++) tempString += str[i];
	pHead->username = tempString;

	//Get password
	lc1 = lc2;
	i = lc2 + 1;
	ch = str[i];
	while (ch != ',') { i++; ch = str[i]; }
	lc2 = i;
	tempString = "";
	for (i = lc1 + 1; i < lc2; i++) tempString += str[i];
	pHead->password = tempString;

	//Get Class
	lc1 = lc2;
	i = lc2 + 1;
	ch = str[i];
	while (ch != ',') { i++; ch = str[i]; }
	lc2 = i;
	tempString = "";
	for (i = lc1 + 1; i < lc2; i++) tempString += str[i];
	pHead->Class = tempString;

	//Get SchoolYear
	lc1 = lc2;
	i = lc2 + 1;
	ch = str[i];
	tempInt = "";
	tempInt += ch;
	x = atoi(tempInt.c_str());
	pHead->SchoolYear = x;
}

void login(Student* pHead) {
	string un;
	string pass;
	cout << "Insert your username, please!  " << endl;
	cin >> un;
	cout << "Insert your password, please! " << endl;
	cin >> pass;
	Student* pCur = pHead;
	while (pCur->pNext != nullptr) {
		if (un == pCur->username && pass == pCur->password) {
			cout << "Login successfully !" << endl;
			return;
		}
		pCur = pCur->pNext;
	}
	cout << "Invalid login, please try again !" << endl;
}