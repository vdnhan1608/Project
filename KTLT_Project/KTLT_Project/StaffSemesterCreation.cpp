﻿#include"StructStudent.h"
#include"Staff.h"
#include<iostream>
#include<fstream>
#include<string>
#include<io.h>
#include<fcntl.h>
#include<locale>
#include<codecvt>
#include<conio.h>
using namespace std;

/*Hàm có tác dụng ghi danh sách các khóa học nhập từ bàn phím vào file.*/
void SetUpSemester(int schoolyear,int semester, CourseInfo* pHead)
{
	// Trong main phải nhập năm học để dùng hàm.
	string str = "";
	// Trong main nhập cout << "Semester 1 is coming. Input courses in semester 1." << endl;
	// Lấy đường dẫn đến file ghi danh sách khóa học
	if (schoolyear == 1)
	{
		if (semester == 1) str = "D:\\InputProject\\SchoolYear1\\CourseSemester1.txt";
		else if (semester == 2) str = "D:\\InputProject\\SchoolYear1\\CourseSemester2.txt";
		else  str = "D:\\InputProject\\SchoolYear1\\CourseSemester3.txt";
	}
	else
		if (schoolyear == 2) {
			if (semester == 1) str = "D:\\InputProject\\SchoolYear2\\CourseSemester1.txt";
			else if (semester == 2) str = "D:\\InputProject\\SchoolYear2\\CourseSemester2.txt";
			else str = "D:\\InputProject\\SchoolYear2\\CourseSemester3.txt";
		}
		else
			if (schoolyear == 3) {
				if (semester == 1) str = "D:\\InputProject\\SchoolYear3\\CourseSemester1.txt";
				else if (semester == 2) str = "D:\\InputProject\\SchoolYear3\\CourseSemester2.txt";
				else  str = "D:\\InputProject\\SchoolYear3\\CourseSemester3.txt";
			}
			else {
				if (semester == 1) str = "D:\\InputProject\\SchoolYear4\\CourseSemester1.txt";
				else if (semester == 2) str = "D:\\InputProject\\SchoolYear4\\CourseSemester2.txt";
				else str = "D:\\InputProject\\SchoolYear4\\CourseSemester3.txt";
			}
	
	/*Tạo thông tin khóa học trong một học kì*/
	/*Setup để đọc ghi tiếng việt*/
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);

	/*Nhập thông tin khóa học và lưu vào 1 linked list*/
	wstring wstr, wtemp;
	CourseInfo*ptemp = nullptr;
	int tempI = 0;/*biến lưu thông tin số của khóa học + nút nhận của chương trình*/
	do {
		wstr = L"";
		wcout << L"Course ID: "; wcin >> tempI;
		wstr += to_wstring(tempI) + L',';
		wcout << L"Course name: "; wcin.ignore(); getline(wcin, wtemp);
		wstr += wtemp + L",";
		wcout << L"Lecturer: "; fflush(stdin); getline(wcin, wtemp);
		wstr += wtemp + L",";
		wcout << L"Number of credits: "; wcin >> tempI;
		wstr += to_wstring(tempI) + L",";
		wcout << L"Student limit: "; wcin >> tempI;
		wstr += to_wstring(tempI) + L",";
		wcout << L"Week day: "; wcin >> tempI;
		wstr += to_wstring(tempI) + L",";

		wcout << L"Session day 1 (Mon/Tue/Wed/Thu/Fri/Sat/Sun): "; wcin.ignore();getline(wcin, wtemp);
		wstr += wtemp + L",";
		wcout << L"Session time day 1 (hh:mm): "; getline(wcin, wtemp);
		wstr += wtemp + L",";
		wcout << L"Session day 2 (Mon/Tue/Wed/Thu/Fri/Sat/Sun): "; getline(wcin, wtemp);
		wstr += wtemp + L",";
		wcout << L"Session time day 2 (hh:mm):  ";fflush(stdin); getline(wcin, wtemp);
		wstr += wtemp;

		if (pHead == nullptr) {
			pHead = new CourseInfo;
			pHead->info = wstr;
			pHead->next = nullptr;
			ptemp = pHead;
		}
		else {
			ptemp->next = new CourseInfo;
			ptemp = ptemp->next;
			ptemp->info = wstr;
			ptemp->next = nullptr;
		}
		wcout << endl;
		wcout << L"Add a new course.?? 1: Yes or 0: No" << endl;
		tempI = _getch();

	} while (tempI == 49);

	
	/*Mở file với chế độ xóa hết nội dung file khi mở ra. Mục đích để tránh ghi đè lên nội dung cũ*/
	wofstream FileOut;
	FileOut.open(str);
	/*Set up để đọc chữ Tiếng Việt utf8*/
	locale loc(locale(), new codecvt_utf8<wchar_t>);
	_setmode(_fileno(stdout), _O_U16TEXT);
	FileOut.imbue(loc);

	// Đưa con trỏ file đến cuối file
	FileOut.seekp(0, ios::end);

	/*Viết nội dung khóa học vào file*/
	CourseInfo* pCur = pHead;
	while (pCur != nullptr) {
		FileOut << pCur->info << endl;
		pCur = pCur->next;
	}
	FileOut.close();
	DeleteListCourseInfo(pHead);
}

/*Hàm có tác dụng xóa linked list CourseInfo*/
void DeleteListCourseInfo(CourseInfo*& pHead)
{
	CourseInfo* pCur = nullptr;
	while (pHead != nullptr) {
		pCur = pHead;
		pHead = pHead->next;
		delete pCur;
	}
}

/*Hàm xóa linked list Course*/
void DeleteListCourse(Course*& pHead)
{
	Course* pCur = nullptr;
	while (pHead != nullptr)
	{
		pCur = pHead;
		pHead = pHead->next;
		delete pCur;
	}
}

/*Hàm xem danh sách các course đã nhập*/
void ViewListCourse(int schoolyear, int semester,Course*&pHead)
{
	string str = "";
	/*Lấy đường dẫn để đọc file*/
	if (schoolyear == 1)
	{
		if (semester == 1) str = "D:\\InputProject\\SchoolYear1\\CourseSemester1.txt";
		else if (semester == 2) str = "D:\\InputProject\\SchoolYear1\\CourseSemester2.txt";
		else  str = "D:\\InputProject\\SchoolYear1\\CourseSemester3.txt";
	}
	else
		if (schoolyear == 2) {
			if (semester == 1) str = "D:\\InputProject\\SchoolYear2\\CourseSemester1.txt";
			else if (semester == 2) str = "D:\\InputProject\\SchoolYear2\\CourseSemester2.txt";
			else str = "D:\\InputProject\\SchoolYear2\\CourseSemester3.txt";
		}
		else
			if (schoolyear == 3) {
				if (semester == 1) str = "D:\\InputProject\\SchoolYear3\\CourseSemester1.txt";
				else if (semester == 2) str = "D:\\InputProject\\SchoolYear3\\CourseSemester2.txt";
				else  str = "D:\\InputProject\\SchoolYear3\\CourseSemester3.txt";
			}
			else {
				if (semester == 1) str = "D:\\InputProject\\SchoolYear4\\CourseSemester1.txt";
				else if (semester == 2) str = "D:\\InputProject\\SchoolYear4\\CourseSemester2.txt";
				else str = "D:\\InputProject\\SchoolYear4\\CourseSemester3.txt";
			}

	/*Set up để đọc chữ cái Tiếng việt utf8*/
	_setmode(_fileno(stdin), _O_U16TEXT);
	locale loc(locale(), new codecvt_utf8<wchar_t>);
	wifstream FileIn;
	FileIn.imbue(loc);
	FileIn.open(str);
	if (FileIn.is_open() == false) wcout << L"Course in this semester not created." << endl;
	else {
		/*Mở hàm đọc thôi nào!!*/
		wstring wstr;
		Course * pCur = nullptr;
		getline(FileIn, wstr);
		while (!FileIn.eof()) {
			
			if (wstr == L"") break;
			if (pHead == nullptr) {
				pHead = new Course;
				SetUpInfoCourse(wstr, pHead);
				pHead->next = nullptr;
				pCur = pHead;
			}
			else
			{
				pCur->next = new Course;
				pCur = pCur->next;
				SetUpInfoCourse(wstr, pCur);
				pCur->next = nullptr;
			}
			getline(FileIn, wstr);
		}
		pCur = pHead;
		/*Setup để chuyển đổi giữa string và wstring :))*/
		wstring_convert <codecvt_utf8_utf16<wchar_t>> convert;
		;
		while (pCur != nullptr) {
			wcout << pCur->ID << L" " << pCur->Name << L" ";
			wcout << pCur->Lecturer << L" " << pCur->Credits << L" " << pCur->StudentLimit << L" " << pCur->Weekday << L" ";
			wcout<< convert.from_bytes(pCur->SessionDay1) <<L" "<< convert.from_bytes(pCur->Time1)<<L" "<< convert.from_bytes(pCur->SessionDay2)<< convert.from_bytes(pCur->Time2) << endl;
			pCur = pCur->next;
		}
		while (pHead != nullptr) {
			pCur = pHead;
			pHead = pHead->next;
			delete pCur;
		}
	}/*Phải xóa linked list Course*/
	DeleteListCourse(pHead);
	FileIn.close();
}

/*Hàm biến chuỗi wstr thành từng phần nhỏ của struct Course*/
void SetUpInfoCourse(wstring& wstr, Course*& pHead)
{
	int length = wstr.length();
	int lc1 = 0, lc2 = 0;
	wchar_t ch = wstr[lc2];
	wstring temp = L"";
	string strtemp;
	int tempI;
	/*Setup để chuyển đổi giữa string và wstring :))*/
	wstring_convert <codecvt_utf8_utf16<wchar_t>> convert;
	// Get the ID
	while (ch != L',') { lc2++; ch = wstr[lc2]; }
	for (int j = 0;j < lc2;j++) temp += wstr[j];
	strtemp = convert.to_bytes(temp);
	tempI = atoi(strtemp.c_str());
	pHead->ID = tempI;
	lc1 = lc2; lc2++;
	ch = wstr[lc2];
	//Get the course name
	temp = L"";
	while (ch != L',') { lc2++;ch = wstr[lc2]; }
	for (int j = lc1 + 1;j < lc2;j++) temp += wstr[j];
	pHead->Name = temp;
	lc1 = lc2;
	lc2++; ch = wstr[lc2];
	// Get the course lecturer
	temp = L"";
	while (ch != L',') { lc2++; ch = wstr[lc2]; }
	for (int j = lc1 + 1;j < lc2;j++) temp += wstr[j];
	pHead->Lecturer = temp;
	lc1 = lc2;
	lc2++; ch = wstr[lc2];
	// Get the course credit
	temp = L"";
	while (ch != L',') { lc2++; ch = wstr[lc2]; }
	for (int j = lc1 + 1;j < lc2;j++) temp += wstr[j];
	strtemp = convert.to_bytes(temp);
	tempI = atoi(strtemp.c_str());
	pHead->Credits = tempI;
	lc1 = lc2;
	lc2++; ch = wstr[lc2];
	// Get the course student limit
	temp = L"";
	while (ch != L',') { lc2++; ch = wstr[lc2]; }
	for (int j = lc1 + 1;j < lc2;j++) temp += wstr[j];
	strtemp = convert.to_bytes(temp);
	tempI = atoi(strtemp.c_str());
	pHead->StudentLimit = tempI;
	lc1 = lc2;
	lc2++; ch = wstr[lc2];
	//Get the course Weekdays.
	temp = L"";
	while (ch != L',') { lc2++; ch = wstr[lc2]; }
	for (int j = lc1 + 1;j < lc2;j++) temp += wstr[j];
	strtemp = convert.to_bytes(temp);
	tempI = atoi(strtemp.c_str());
	pHead->Weekday = tempI;
	lc1 = lc2;
	lc2++; ch = wstr[lc2];
	// Get the course session day 1.
	temp = L"";
	while (ch != L',') { lc2++; ch = wstr[lc2]; }
	for (int j = lc1 + 1;j < lc2;j++) temp += wstr[j];
	strtemp = convert.to_bytes(temp);
	pHead->SessionDay1 = strtemp;
	lc1 = lc2;
	lc2++; ch = wstr[lc2];
	// Get the course session time day 1.
	temp = L"";
	while (ch != L',') { lc2++; ch = wstr[lc2]; }
	for (int j = lc1 + 1;j < lc2;j++) temp += wstr[j];
	strtemp = convert.to_bytes(temp);
	pHead->Time1 = strtemp;
	lc1 = lc2;
	lc2++; ch = wstr[lc2];
	// Get the course session day 2.
	temp = L"";
	while (ch != L',') { lc2++; ch = wstr[lc2]; }
	for (int j = lc1 + 1;j < lc2;j++) temp += wstr[j];
	strtemp = convert.to_bytes(temp);
	pHead->SessionDay2 = strtemp;
	lc1 = lc2;
	lc2++; ch = wstr[lc2];
	// Get the course session time day 2.
	temp = L"";
	for (int j = lc1 + 1;j < length;j++) temp += wstr[j];
	strtemp = convert.to_bytes(temp);
	pHead->Time2 = strtemp;
}

/*Hàm chuyển struct Course sang CourseInfo. Mục đích để thuận tiện ghi và đọc file.*/
void ChangeCourseToCourseInfo(Course*& pHeadCourse, CourseInfo*& pHeadCourseInfo)
{
	if (pHeadCourse == nullptr) return;
	wstring str = L"";
	Course* pCurCourse = pHeadCourse;
	CourseInfo* pCurInfo = nullptr;
	/*Setup để chuyển đổi giữa string và wstring :))*/
	wstring_convert <codecvt_utf8_utf16<wchar_t>> convert;
	while (pCurCourse != nullptr) {
		str = L"";
		/*Ghép các thành phần lại thành 1 chuỗi*/
		str += to_wstring(pCurCourse->ID) + L',' + pCurCourse->Name + L',';
		str += pCurCourse->Lecturer + L',' + to_wstring(pCurCourse->Credits);
		str += L',' + to_wstring(pCurCourse->StudentLimit) + L',' + to_wstring(pCurCourse->Weekday)+L',';
		str+=convert.from_bytes(pCurCourse->SessionDay1)+L","+ convert.from_bytes(pCurCourse->Time1) + L",";
		str += convert.from_bytes(pCurCourse->SessionDay2) + L"," + convert.from_bytes(pCurCourse->Time2) ;
		if (pHeadCourseInfo == nullptr) {
			pHeadCourseInfo = new CourseInfo;
			pHeadCourseInfo->info = str;
			pHeadCourseInfo->next = nullptr;
			pCurInfo = pHeadCourseInfo;
		}
		else
		{
			pCurInfo->next = new CourseInfo;
			pCurInfo = pCurInfo->next;
			pCurInfo->info = str;
			pCurInfo->next = nullptr;
		}
		pCurCourse = pCurCourse->next;
	}
}

/*Hàm thêm các khóa học vào file danh sách khóa học*/
void AddCourseSemester(int schoolyear, int semester, CourseInfo* pHead)
{
	string str = "";
	// Trong main nhập cout << "Semester 1 is coming. Input courses in semester 1." << endl;
	// Lấy đường dẫn đến file ghi danh sách khóa học
	if (schoolyear == 1)
	{
		if (semester == 1) str = "D:\\InputProject\\SchoolYear1\\CourseSemester1.txt";
		else if (semester == 2) str = "D:\\InputProject\\SchoolYear1\\CourseSemester2.txt";
		else  str = "D:\\InputProject\\SchoolYear1\\CourseSemester3.txt";
	}
	else
		if (schoolyear == 2) {
			if (semester == 1) str = "D:\\InputProject\\SchoolYear2\\CourseSemester1.txt";
			else if (semester == 2) str = "D:\\InputProject\\SchoolYear2\\CourseSemester2.txt";
			else str = "D:\\InputProject\\SchoolYear2\\CourseSemester3.txt";
		}
		else
			if (schoolyear == 3) {
				if (semester == 1) str = "D:\\InputProject\\SchoolYear3\\CourseSemester1.txt";
				else if (semester == 2) str = "D:\\InputProject\\SchoolYear3\\CourseSemester2.txt";
				else  str = "D:\\InputProject\\SchoolYear3\\CourseSemester3.txt";
			}
			else {
				if (semester == 1) str = "D:\\InputProject\\SchoolYear4\\CourseSemester1.txt";
				else if (semester == 2) str = "D:\\InputProject\\SchoolYear4\\CourseSemester2.txt";
				else str = "D:\\InputProject\\SchoolYear4\\CourseSemester3.txt";
			}
	wfstream FileOut;
	// Set up để đọc được chữ Tiếng Viết utf8
	FileOut.open(str, ios::out | ios::in);
	locale loc(locale(), new codecvt_utf8<wchar_t>);
	_setmode(_fileno(stdout), _O_U16TEXT);
	FileOut.imbue(loc);

	// Đưa con trỏ file đến cuối file
	FileOut.seekp(0, ios::end);

	// Ghi tiếp các khóa học vào bên dưới.
	CourseInfo* pCur = pHead;
	while (pCur != nullptr) {
		FileOut << pCur->info << endl;
		pCur = pCur->next;
	}
	FileOut.close();

}

/*Hàm cập nhật thông tin của khóa học*/
void UpdateCourse(int schoolyear, int semester, int k, Course*& pHead)
{
	string str = "";
	// Lấy đường dẫn đến chỗ file ghi danh sách course.
	if (schoolyear == 1)
	{
		if (semester == 1) str = "D:\\InputProject\\SchoolYear1\\CourseSemester1.txt";
		else if (semester == 2) str = "D:\\InputProject\\SchoolYear1\\CourseSemester2.txt";
		else  str = "D:\\InputProject\\SchoolYear1\\CourseSemester3.txt";
	}
	else
		if (schoolyear == 2) {
			if (semester == 1) str = "D:\\InputProject\\SchoolYear2\\CourseSemester1.txt";
			else if (semester == 2) str = "D:\\InputProject\\SchoolYear2\\CourseSemester2.txt";
			else str = "D:\\InputProject\\SchoolYear2\\CourseSemester3.txt";
		}
		else
			if (schoolyear == 3) {
				if (semester == 1) str = "D:\\InputProject\\SchoolYear3\\CourseSemester1.txt";
				else if (semester == 2) str = "D:\\InputProject\\SchoolYear3\\CourseSemester2.txt";
				else  str = "D:\\InputProject\\SchoolYear3\\CourseSemester3.txt";
			}
			else {
				if (semester == 1) str = "D:\\InputProject\\SchoolYear4\\CourseSemester1.txt";
				else if (semester == 2) str = "D:\\InputProject\\SchoolYear4\\CourseSemester2.txt";
				else str = "D:\\InputProject\\SchoolYear4\\CourseSemester3.txt";
			}
	// Set up để lấy chữ cái Tiếng Việt utf8
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	wstring_convert <codecvt_utf8_utf16<wchar_t>> convert;
	locale loc(locale(), new codecvt_utf8<wchar_t>);


	// Xác định course cần phải Update.
	Course* pCur = pHead;
	int i = 1;
	while (i < k) { i++; pCur = pCur->next; }

	// Trong main phải cout<< Hỏi course nào để update rồi dùng hàm.

	// Staff update.
	int button;

	// Update Course ID.
	wcout << "Course ID: " << pCur->ID << " Update: Type Y/N (Yes or No)";
	button = _getch();
	// Kiểm tra nút nhận có gõ đúng hay không.
	while (button != 89 && button != 78 && button != 110 && button != 121) button = _getch();
	wcout << endl;
	/*Update course ID*/
	if (button == 121 || button == 89) {
		wcout << "New Course ID: ";
		wcin >> pCur->ID;
	}
	/*Update Course Name*/
	wcout << "Course Name: " << pCur->Name << " Update: Type Y/N (Yes or No)";
	button = _getch();

	// Kiểm tra nút nhận có gõ đúng hay không.
	while (button != 89 && button != 78 && button != 110 && button != 121) button = _getch();
	wcout << endl;
	if (button == 121 || button == 89) {
		wcout << "New Course Name: ";
		getline(wcin, pCur->Name);
	}

	/*Update Course Lecturer*/
	wcout << "Course Lecture: " << pCur->Lecturer << " Update: Type Y/N (Yes or No)";
	button = _getch();
	// Kiểm tra nút nhận có gõ đúng hay không.
	while (button != 89 && button != 78 && button != 110 && button != 121) button = _getch();
	wcout << endl;
	if (button == 121 || button == 89) {
		wcout << "New Course Lecturer: ";
		getline(wcin, pCur->Lecturer);
	}

	/*Update Course Credits*/
	wcout << "Course Credits: " << pCur->Credits << " Update: Type Y/N (Yes or No)";
	button = _getch();
	// Kiểm tra nút nhận có gõ đúng hay không.
	while (button != 89 && button != 78 && button != 110 && button != 121) button = _getch();
	wcout << endl;
	if (button == 121 || button == 89) {
		wcout << "New Course Credits: ";
		wcin >> pCur->Credits;
	}

	/*Update Course Student Limits*/
	wcout << "Course Student Limits: " << pCur->StudentLimit << " Update: Type Y/N (Yes or No)";
	button = _getch();
	// Kiểm tra nút nhận có gõ đúng hay không.
	while (button != 89 && button != 78 && button != 110 && button != 121) button = _getch();
	wcout << endl;
	if (button == 121 || button == 89) {
		wcout << "New Course Student Limit: ";
		wcin >> pCur->StudentLimit;
	}

	/*Update Course Weekday*/
	wcout << "Course Weekday: " << pCur->Weekday << " Update: Type Y/N (Yes or No)";
	button = _getch();
	// Kiểm tra nút nhận có gõ đúng hay không.
	while (button != 89 && button != 78 && button != 110 && button != 121) button = _getch();
	wcout << endl;
	if (button == 121 || button == 89) {
		wcout << "New Course Weekday: ";
		wcin >> pCur->Weekday;
	}

	wstring wtemp;

	/*Update Course Session Day 1*/
	wcout << "Course Session Day 1: " << convert.from_bytes(pCur->SessionDay1) << " Update: Type Y/N (Yes or No)";
	button = _getch();
	// Kiểm tra nút nhận có gõ đúng hay không.
	while (button != 89 && button != 78 && button != 110 && button != 121) button = _getch();
	wcout << endl;
	
	if (button == 121 || button == 89) {
		wcout << "New Course Session: ";
		getline(wcin, wtemp);
		pCur->SessionDay1 = convert.to_bytes(wtemp);
	}

	/*Update Course Session Time 1*/
	wcout << "Course Session Time Day 1: " << convert.from_bytes(pCur->Time1) << " Update: Type Y/N (Yes or No)";
	button = _getch();
	// Kiểm tra nút nhận có gõ đúng hay không.
	while (button != 89 && button != 78 && button != 110 && button != 121) button = _getch();
	wcout << endl;
	if (button == 121 || button == 89) {
		wcout << "New Course Session: ";
		getline(wcin, wtemp);
		pCur->Time1 = convert.to_bytes(wtemp);
	}

	/*Update Course Session Day 1*/
	wcout << "Course Session Day 2: " << convert.from_bytes(pCur->SessionDay2) << " Update: Type Y/N (Yes or No)";
	button = _getch();
	// Kiểm tra nút nhận có gõ đúng hay không.
	while (button != 89 && button != 78 && button != 110 && button != 121) button = _getch();
	wcout << endl;
	if (button == 121 || button == 89) {
		wcout << "New Course Session: ";
		getline(wcin, wtemp);
		pCur->SessionDay2 = convert.to_bytes(wtemp);
	}

	/*Update Course Session Time Day 1*/
	wcout << "Course Session Time Day 2: " << convert.from_bytes(pCur->Time2) << " Update: Type Y/N (Yes or No)";
	button = _getch();
	// Kiểm tra nút nhận có gõ đúng hay không.
	while (button != 89 && button != 78 && button != 110 && button != 121) button = _getch();
	wcout << endl;
	if (button == 121 || button == 89) {
		wcout << "New Course Session: ";
		getline(wcin, wtemp);
		pCur->Time2 = convert.to_bytes(wtemp);
	}

	wcout << "Update successfully." << endl;

	// Ghi vào lại file danh sách các khóa học.
	CourseInfo* pCourseInfo = nullptr;
	ChangeCourseToCourseInfo(pHead, pCourseInfo);
	SetUpSemester(schoolyear, semester, pCourseInfo);
	/*Hàm này có thể sửa lại cho tốt hơn vì mỗi lần update là mỗi lần ghi lại vào file mệt*/
	/*Hàm chưa kiểm tra*/ /*Successfully*/
}

/*Hàm xóa 1 khóa học, rồi cập nhật lại trong file mới*/
void DeleteACourse(int schoolyear, int semester, int k, Course*& pHead)
{
	/*Có cần xác định đường dẫn không. Vì sau đó sẽ setup lại semester. Chắc có*/
	/*Trong hàm main cần phải xác định là course thứ mấy cần phải xóa*/

	/*Xác định course cần xóa*/
	if (pHead == nullptr) return;
	Course* pCur = pHead;
	int i = 1;
	/* Trường hợp xóa course đầu tiên*/
	if (k == 1) {
		pCur = pHead;
		pHead = pHead->next;
		delete pCur;
	}
	/*Trường hợp xóa course ở sau cái đầu.*/
	else {
		pCur = pHead;
		while (i < k - 1) {
			i++;pCur = pCur->next;
		}
		Course* ptemp = pCur->next;
		pCur->next = ptemp->next;
		delete ptemp;
	}

	wcout << "Delete Course no." << k << " successfully!" << endl;
	/*Update và view ra cho staff*/
	CourseInfo* pCourseInfo = nullptr;
	ChangeCourseToCourseInfo(pHead, pCourseInfo);
	SetUpSemester(schoolyear, semester, pCourseInfo);
	// View danh sách mới cho staff.
	wcout << "Here the new course semester." << endl;
	Course* pCourse = nullptr;
	ViewListCourse(schoolyear, semester, pCourse);
	/*Xóa danh sách course info*/
	DeleteListCourseInfo(pCourseInfo);
	DeleteListCourse(pCourse);
	/*Kiểm tra hàm có hoạt động không*/ /*Thành công luôn.*/
}

void SetUpCourse(Course& pHead) {
	
}
/*Cần tạo ngày bắt đầu và ngày cuối cùng của thời gian đăng kí học phần.*/