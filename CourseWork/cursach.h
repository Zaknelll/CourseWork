// курсовая.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <map>
#include <clocale>

using namespace std;

//структура ФИО
struct FIO
{
	char familiy[50],
		imy[50],
		otchestvo[50];
};

//структура оценок студента
struct Date
{
	float marks[5];
};

//структура форма обучения
struct Forma
{
	char budget;
};

//структура оплаты обучения студента
struct Oplata
{
	int summaoplati;
};

//структура стипендии студента
struct Stipendiy
{
	int summastipendii;
};

//структура данных студента
struct Data
{
	FIO _FIO;
	Date _Date;
	Forma _Forma;
	Oplata _Oplata;
	Stipendiy _Stipendiy;
};


//структура данных группы
struct Group
{
	int counter;
	Data* _data;
};



//функции
void ReadingData(map <int, Group>& grupp, int& n, string filename);
void BinaryReadingData(map <int, Group>& grupp, int& n, string filename);
void PrintGroup(map <int, Group>& d);
void AddNewGroup(map <int, Group>& d, int& groupNum);
void PrintStudents(map <int, Group>& d, int& n, int& gruppNum);
void AddNewStudent(map <int, Group>& d, int& m, int& gruppNum);
void DataSorting(Data*& d, int& n);
void StudetnChange(map <int, Group>& d, int& gruppNum);
void DeletStudet(map <int, Group>& d, int& m, int& gruppNum);
void DeleteGroup(map <int, Group>& d);
void Savingdata(map <int, Group>& d, int n, string filename);
void BinarySavingdata(map <int, Group>& d, int n, string filename);
void PrintAllInfo(map <int, Group>& d, int &n);

void Copy(Data*& d_n, Data*& d_o, int n);
void AddToGroup(Data*& d, Data& newStudent, int& n);
// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
