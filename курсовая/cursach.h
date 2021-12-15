// курсовая.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <map>
#include<clocale>

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
	float AiG, programmer, math, history , english;
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

//структура данных связи студентов
struct Svysstud
{
	Data data;
	Svysstud* next;
};

//структура данных группы
struct Group
{
	int counter;
	Data* _data;
};



//функции
//void DataEntery(Data *&d, int& n);
void ReadingData(map <int, Group>& grupp, int& n, string filename);
void Print(map <int, Group>& d, int &n);
void PrintStudents(map <int, Group>& d, int& n, int& gruppNum);
void Datachange(map <int, Group>& d, int& gruppNum);
void Copy(Data*& d_n, Data*& d_o, int n);// копирование всего массива
void DeletStudet(map <int, Group>& d, int& m, int& gruppNum);
void AddData(map <int, Group>& d, int& m);
void DataSorting(Data *&d, int& n);
void Savingdata(map <int, Group>& d, int n, string filename);
void PrintGroup(map <int, Group>& d);
void AddNewGroup(map <int, Group>& d, int &groupNum);
void AddToGroup(Data*& d, Data& newStudent, int& n);
void DeleteGroup(map <int, Group>& d);
void AddNewStudent(map <int, Group>& d, int& m, int& gruppNum);
// TODO: установите здесь ссылки на дополнительные заголовки, требующиеся для программы.
