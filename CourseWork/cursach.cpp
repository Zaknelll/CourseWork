// курсовая.cpp: определяет точку входа для приложения.
//

#include "cursach.h"

int _stateMenu, _stateMenu2, form;


void Menu()
{
	cout << "Выберите действие:" << endl;
	cout << "1 - Ввод данных из файла." << endl;
	cout << "2 - Вывод групп в консоль." << endl;
	cout << "3 - Новая группа." << endl;
	cout << "4 - Работа с группой." << endl;
	cout << "5 - Удаление группы." << endl;
	cout << "6 - Сохранение в файл." << endl;
	cout << "7 - Вывод данных в консоль." << endl;
	cout << "0 - Выход из программы." << endl;
	cout << "----------------" << endl;
	cout << "Ваш выбор: ";
	cin >> _stateMenu;
}


void Menu2()
{
	cout << "Выберите действие:" << endl;
	cout << "1 - Вывод списка студентов." << endl;
	cout << "2 - Добавление нового студента." << endl;
	cout << "3 - Изменение данных о студенте." << endl;
	cout << "4 - Удаление студента." << endl;
	cout << "0 - Предыдущее меню." << endl;
	cout << "----------------" << endl;
	cout << "Ваш выбор: ";
	cin >> _stateMenu2;
}


int SubMenu(map <int, Group>& grupp, int& amountofdata, int &gruppNum) {

	Menu2();


	while (_stateMenu2 != 0)
	{
		switch (_stateMenu2) {

		case 1:

			system("cls");
			

			if (amountofdata != 0)
			{

				PrintStudents(grupp, amountofdata, gruppNum);
			}

			else
				cout << "Студентов в этой группе ещё нету!" << endl;

			system("pause");
			system("cls");
			Menu2();
			break;

		case 2:

			system("cls");

				AddNewStudent(grupp, amountofdata, gruppNum);
				DataSorting(grupp.at(gruppNum)._data, grupp.at(gruppNum).counter);
			

			system("pause");
			system("cls");
			Menu2();
			break;

		case 3:

			system("cls");


			if (amountofdata != 0)
			{
				StudetnChange(grupp, gruppNum);
				DataSorting(grupp.at(gruppNum)._data, grupp.at(gruppNum).counter);
			}

			else
				cout << "Нету студентов, данные которых можно изменить!" << endl;

			system("pause");
			system("cls");
			Menu2();
			break;

		case 4:

			system("cls");

			if (amountofdata != 0)
			{
				DeletStudet(grupp, amountofdata, gruppNum);
			}

			else
				cout << "Нету студента, которого можно удалить!" << endl;

			system("pause");
			system("cls");
			Menu2();
			break;

		default:
			cout << "Неверно введён номер действия!" << endl;
			system("pause");
			system("cls");
			Menu2();
			break;
		}

	}
	return 0;
}




void ReadingData(map <int, Group> &grupp, int& n, string filename)
{
	int groupnum;
	string answer;
	ifstream reading(filename);

	while (!reading.is_open())
	{
		system("cls");
		cout << "Не удалось открыть файл!" << endl;
		cout << "Ввести файл зайново? (yes,no)" << endl << endl;

		cin >> answer;
		if (answer == "yes") {
			system("cls");
			cout << "Введите название файла: ";
			cin >> filename;
			reading.open(filename);
		}
		break;
	}

	if (reading)
	{
		reading >> n;
		Data newStudent;
		boolean invFlag = 0;

		/*d = (Data*)realloc(d, sizeof(Data) * n);*/

		for (int i = 0; i < n; i++) {

			reading >> groupnum;
			reading >> newStudent._FIO.familiy;
			reading >> newStudent._FIO.imy;
			reading >> newStudent._FIO.otchestvo;


			for (int i = 0; i < 5; i++)
			{
				reading >> newStudent._Date.marks[i];
				if (newStudent._Date.marks[i] > 6 || newStudent._Date.marks[i] <= 0) {
					cout << "Неправильные данные у студента: " << newStudent._FIO.familiy << endl;
					invFlag = 1;
				}
			}				


			reading >> newStudent._Forma.budget;


			if (newStudent._Forma.budget == 'b') {
				//бюджет
				reading >> newStudent._Stipendiy.summastipendii;
			}
			else if (newStudent._Forma.budget == 'k') {
				//контракт
				reading >> newStudent._Oplata.summaoplati;
			} else {
				cout << "Неправильные данные у студента: " << newStudent._FIO.familiy << endl;
				invFlag = 1;
			}

			if (invFlag) {
				string line;
				getline(reading, line);
				getline(reading, line);
				reading.clear();
				while (!line.empty()) {
					getline(reading, line);
					reading.clear();
				}
					
				invFlag = 0;
				newStudent = Data();
				continue;
			}

			if (grupp.find(groupnum) == grupp.end()) {
				Group g = { 1, new Data[1]{ newStudent } };
				grupp.insert(pair<int, Group>(groupnum, g));
			}
			else {
				AddToGroup(grupp.at(groupnum)._data, newStudent, grupp.at(groupnum).counter);
				grupp.at(groupnum).counter++;
			}

		}
		
			
		cout << "Данные считаны! " << endl;
	}


	reading.close();
}


void BinaryReadingData(map <int, Group>& grupp, int& n, string filename) {

	int groupnum;
	string answer;
	ifstream rf(filename, ios::in | ios::binary);

	while (!rf.is_open())
	{
		system("cls");
		cout << "Не удалось открыть файл!" << endl;
		cout << "Ввести файл зайново? (yes,no)" << endl << endl;

		cin >> answer;
		if (answer == "yes") {
			system("cls");
			cout << "Введите название файла: ";
			cin >> filename;
			rf.open(filename);
		}
		break;
	}

	if (rf)
	{
		rf >> n;
		Data newStudent;
		boolean invFlag = 0;

		/*d = (Data*)realloc(d, sizeof(Data) * n);*/

		for (int i = 0; i < n; i++) {

			rf >> groupnum;
			rf >> newStudent._FIO.familiy;
			rf >> newStudent._FIO.imy;
			rf >> newStudent._FIO.otchestvo;


			for (int i = 0; i < 5; i++)
			{
				rf >> newStudent._Date.marks[i];
				if (newStudent._Date.marks[i] > 6 || newStudent._Date.marks[i] <= 0) {
					cout << "Неправильные данные у студента: " << newStudent._FIO.familiy << endl;
					invFlag = 1;
				}
			}

			rf >> newStudent._Forma.budget;


			if (newStudent._Forma.budget == 'b') {
				//бюджет
				rf >> newStudent._Stipendiy.summastipendii;
			}
			else if (newStudent._Forma.budget == 'k') {
				//контракт
				rf >> newStudent._Oplata.summaoplati;
			}
			else {
				cout << "Неправильные данные у студента: " << newStudent._FIO.familiy << endl;
				invFlag = 1;
			}

			if (invFlag) {
				string line;
				getline(rf, line);
				getline(rf, line);
				rf.clear();
				while (!line.empty()) {
					getline(rf, line);
					rf.clear();
				}

				invFlag = 0;
				newStudent = Data();
				continue;
			}

			if (grupp.find(groupnum) == grupp.end()) {
				Group g = { 1, new Data[1]{ newStudent } };
				grupp.insert(pair<int, Group>(groupnum, g));
			}
			else {
				AddToGroup(grupp.at(groupnum)._data, newStudent, grupp.at(groupnum).counter);
				grupp.at(groupnum).counter++;
			}

		}


		cout << "Данные считаны! " << endl;
	}

	rf.close();
}


void PrintAllInfo(map <int, Group>& d, int &n)
{
	map<int, Group>::iterator j;
		for (j = d.begin(); j != d.end(); j++) {

			cout << "-------------------- " << endl;

			cout << "|Номер Группы: " << j->first << "|" << endl;
			cout << "--------------------" << endl;

			if (j->second.counter == 0) {
				cout << "В этой группе ещё нет студентов!" << endl << endl;
			}
			else {
				DataSorting(j->second._data, j->second.counter);
				for (int i = 0; i < j->second.counter; i++) {

					cout << "	Данные №" << i + 1 << ":" << endl;

					cout << "	ФИО: " << j->second._data[i]._FIO.familiy << " " << j->second._data[i]._FIO.imy << " " << j->second._data[i]._FIO.otchestvo << " " << endl;

					cout << "	Оценки: " << endl << "	" << j->second._data[i]._Date.marks[0];

					for (int mark = 1; mark < 5; mark++)
					{
						cout << ", " << j->second._data[i]._Date.marks[mark];
					}

					cout << endl <<  "	Форма обучения: " << j->second._data[i]._Forma.budget << endl;


					switch (j->second._data[i]._Forma.budget) {
					case 'b':
						cout << "	Стипендия: " << j->second._data[i]._Stipendiy.summastipendii << endl;

						break;
					case 'k':
						cout << "	Оплата: " << j->second._data[i]._Oplata.summaoplati << endl;
						break;
					default:
						cout << "Неверное значение формы обучения у студента " << j->second._data[i]._FIO.familiy << " " << j->second._data[i]._FIO.imy << " " << j->second._data[i]._FIO.otchestvo << " " << endl;
						cin.get();
						system("pause");
						system("cls");
						Menu();
						break;
					}

					cout << "	____________________________ " << endl;

				}

			}
		}
}


void PrintStudents(map <int, Group>& d, int& n, int& gruppNum)
{

	if (d.at(gruppNum).counter != 0) {
		for (int i = 0; i < d.at(gruppNum).counter; i++) {

			cout << "Студент №" << i + 1 << ":" << endl;

			cout << "ФИО: " << d.at(gruppNum)._data[i]._FIO.familiy << " " << d.at(gruppNum)._data[i]._FIO.imy << " " << d.at(gruppNum)._data[i]._FIO.otchestvo << " " << endl;


			cout << "Оценки: " << d.at(gruppNum)._data[i]._Date.marks[0];

			for (int mark = 1; mark < 5; mark++)
			{
				cout << ", " << d.at(gruppNum)._data[i]._Date.marks[mark];
			}


			cout << endl << "Форма обучения: " << d.at(gruppNum)._data[i]._Forma.budget << endl;


			switch (d.at(gruppNum)._data[i]._Forma.budget) {
			case 'b':
				cout << "Стипендия: " << d.at(gruppNum)._data[i]._Stipendiy.summastipendii << endl;

				break;
			case 'k':
				cout << "Оплата: " << d.at(gruppNum)._data[i]._Oplata.summaoplati << endl;
				break;
			default:
				cout << "Неверное значение формы обучения у студента " << d.at(gruppNum)._data[i]._FIO.familiy << " " << d.at(gruppNum)._data[i]._FIO.imy << " " << d.at(gruppNum)._data[i]._FIO.otchestvo << " " << endl;
				cin.get();
				system("pause");
				system("cls");
				Menu();
				break;
			}

			cout << "____________________________ " << endl;

		}
	}
	else cout << "В группе нету ни одного студента! " << endl;

}


void StudetnChange(map <int, Group>& d, int& gruppNum) {

	int _n;
	cout << "Введите номер студента (от 1 до " << d.at(gruppNum).counter << "):";
	cin >> _n;
	_n--; //чтобы счёт был от 1, а не от 0
	system("cls");

	
	if (_n >= 0 && _n < d.at(gruppNum).counter) {
		cout << "Введите ФИО студента: ";
		cin >> d.at(gruppNum)._data[_n]._FIO.familiy;
		cin >> d.at(gruppNum)._data[_n]._FIO.imy;
		cin >> d.at(gruppNum)._data[_n]._FIO.otchestvo;

		cout << "Введите оценки студента за последнюю сессию: ";

		for (int i = 0; i < 5; i++)
		{
			cin >> d.at(gruppNum)._data[_n]._Date.marks[i];
			while (d.at(gruppNum)._data[_n]._Date.marks[i] > 6 || d.at(gruppNum)._data[_n]._Date.marks[i] <= 0) {
				cout << "Неправильные формат оценки" << endl;
				cin >> d.at(gruppNum)._data[_n]._Date.marks[i];
			}
		}

		cout << "Введите форму обучения студента студента: ";
		cin >> d.at(gruppNum)._data[_n]._Forma.budget;

		while (d.at(gruppNum)._data[_n]._Forma.budget != 'k' && d.at(gruppNum)._data[_n]._Forma.budget != 'b') {
			cout << "Такой формы обучения нету! " << endl;
			cout << "Введите корректную форму обучения студента (k-контракт или b-бюджет): " << endl;
			cin >> d.at(gruppNum)._data[_n]._Forma.budget;
		}

		if (d.at(gruppNum)._data[_n]._Forma.budget == 'b') {
			//бюджет
			cout << "Введите размер стипендии: ";
			cin >> d.at(gruppNum)._data[_n]._Stipendiy.summastipendii;
		}
		if (d.at(gruppNum)._data[_n]._Forma.budget == 'k') {
			//контракт
			cout << "Введите размер оплаты образования: ";

			cin >> d.at(gruppNum)._data[_n]._Oplata.summaoplati;
		}

		system("cls");

		cout << "Данные изменены! " << endl;
	}

	else cout << "Номер введён неверно!" << endl;
}


void Copy(Data*& d_n, Data*& d_o, int n) {

	for (int i = 0; i < n; i++) {
		d_n[i] = d_o[i];
	}
}


void DeletStudet(map <int, Group>& d, int& m, int& gruppNum) {

	int _n;
	cout << "Введите номер студента (от 1 до " << d.at(gruppNum).counter << "):";
	cin >> _n;
	_n--;
	system("cls");


	if (_n >= 0 && _n < d.at(gruppNum).counter) {

		
		Data* buf = new Data[d.at(gruppNum).counter];
		
		
		Copy (buf, d.at(gruppNum)._data, d.at(gruppNum).counter);
		
		
		--d.at(gruppNum).counter;
		int q = 0;

		
		for (int i = 0; i < d.at(gruppNum).counter; i++) {
			if (i != _n) {
				d.at(gruppNum)._data[q] = buf[i];
				++ q;
			}
		}
		m--;
		system("cls");
		delete[]buf;
		cout << "Данные удалены! " << endl;
	}

	else cout << "Номер введён неверно!" << endl;
}


void AddNewStudent(map <int, Group>& d, int& m, int& gruppNum) {



	Data* buf = new Data[d.at(gruppNum).counter + 1];

	Copy(buf, d.at(gruppNum)._data, d.at(gruppNum).counter);


	cout << "Введите ФИО студента: ";
	cin >> buf[d.at(gruppNum).counter]._FIO.familiy;
	cin >> buf[d.at(gruppNum).counter]._FIO.imy;
	cin >> buf[d.at(gruppNum).counter]._FIO.otchestvo;
	
	cout << "Введите оценки студента за последнюю сессию: ";
	
	for (int i = 0; i < 5; i++)
	{
		cin >> buf[d.at(gruppNum).counter]._Date.marks[i];
		while (buf[d.at(gruppNum).counter]._Date.marks[i] > 6 || buf[d.at(gruppNum).counter]._Date.marks[i] <= 0) {
			cout << "Неправильные формат оценки" << endl;
			cin >> buf[d.at(gruppNum).counter]._Date.marks[i];
		}
	}

	cout << "Введите форму обучения студента студента (k-контракт или b-бюджет): ";
	cin >> buf[d.at(gruppNum).counter]._Forma.budget;


	while (buf[d.at(gruppNum).counter]._Forma.budget != 'k' && buf[d.at(gruppNum).counter]._Forma.budget != 'b') {
		cout << "Такой формы обучения нету! " << endl;
		cout << "Введите корректную форму обучения студента (k-контракт или b-бюджет): " << endl;
		cin >> buf[d.at(gruppNum).counter]._Forma.budget;
	}

		if (buf[d.at(gruppNum).counter]._Forma.budget == 'b') {
			//бюджет
			cout << "Введите размер стипендии: ";
			cin >> buf[d.at(gruppNum).counter]._Stipendiy.summastipendii;
		}

		else {
			//контракт
			cout << "Введите размер оплаты образования: ";
			cin >> buf[d.at(gruppNum).counter]._Oplata.summaoplati;
		}


	delete[] d.at(gruppNum)._data;
	d.at(gruppNum)._data = buf;

	d.at(gruppNum).counter++;
	m++;

	system("cls");
	cout << "Данные добавлены! " << endl;
}


void AddToGroup(Data*& d, Data &newStudent, int &n) {

	Data* buf = new Data[n + 1];

	Copy(buf, d, n);

	buf[n] = newStudent;

	delete[] d;
	d = buf;
	//n++;
}


void AddNewGroup(map <int, Group>& d, int &groupNum) {

	
	Group g = { 0, new Data[0]};
	d.insert(pair<int, Group>(groupNum, g));
	

}


void DeleteGroup(map <int, Group>& d) {

	int groupNum;
	cout << "Введите номер группы: " << endl;
	PrintGroup(d);
	cin >> groupNum;
	
	if (d.find(groupNum) == d.end())
		cout << "Такого номера группы нету!" << endl;
	else
		d.erase(groupNum);

}


void DataSorting(Data *&d, int& n) {
	
	Data buf;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (strcmp(d[i]._FIO.familiy, d[j]._FIO.familiy) > 0) {
				buf = d[i];
				d[i] = d[j];
				d[j] = buf;
			}
		}
	}
}


void Savingdata(map <int, Group>& d, int n, string filename) {

	ofstream record(filename, ios::out);
	string answer;
	
	while (!record.is_open())
	{
		system("cls");
		cout << "Не удалось открыть файл!" << endl;
		cout << "Ввести файл зайново? (yes,no)" << endl << endl;

		cin >> answer;
		if (answer == "yes") {
			system("cls");
			cout << "Введите название файла: ";
			cin >> filename;
			record.open(filename);
		}
		break;
	}


	if (record)
	{
		record << n << endl;

		for (map<int, Group>::iterator j = d.begin(); j != d.end(); j++) {


			for (int i = 0; i < j->second.counter; i++) {

				record << j->first << endl;
				record << j->second._data[i]._FIO.familiy << endl;
				record << j->second._data[i]._FIO.imy << endl;
				record << j->second._data[i]._FIO.otchestvo << endl;

				for (int mark = 0; mark < 5; mark++)
				{
					record << j->second._data[i]._Date.marks[mark] << endl;

				}

				record << j->second._data[i]._Forma.budget << endl;


				if (i < n - 1) {
					if (j->second._data[i]._Forma.budget == 'b') {
						record << j->second._data[i]._Stipendiy.summastipendii << endl << endl;;
					}

					else {
						record << j->second._data[i]._Oplata.summaoplati << endl << endl;
					}
				}
				else {
					if (j->second._data[i]._Forma.budget == 'b') {
						record << j->second._data[i]._Stipendiy.summastipendii;
					}

					else {
						record << j->second._data[i]._Oplata.summaoplati;
					}
				}
			}
		}
		cout << "Данные записаны! " << endl;
	}

	else
		cout << "Ошибка открытия файла!" << endl;

	record.close();
}


void BinarySavingdata(map <int, Group>& d, int n, string filename) {

	ofstream record(filename, ios::out | ios::binary);
	string answer;

	while (!record.is_open())
	{
		system("cls");
		cout << "Не удалось открыть файл!" << endl;
		cout << "Ввести файл зайново? (yes,no)" << endl << endl;

		cin >> answer;
		if (answer == "yes") {
			system("cls");
			cout << "Введите название файла: ";
			cin >> filename;
			record.open(filename);
		}
		break;
	}


	if (record)
	{
		record << n << endl;

		for (map<int, Group>::iterator j = d.begin(); j != d.end(); j++) {


			for (int i = 0; i < j->second.counter; i++) {

				record << j->first << endl;
				record << j->second._data[i]._FIO.familiy << endl;
				record << j->second._data[i]._FIO.imy << endl;
				record << j->second._data[i]._FIO.otchestvo << endl;

				for (int mark = 0; mark < 5; mark++)
				{
					record << j->second._data[i]._Date.marks[mark] << endl;

				}

				record << j->second._data[i]._Forma.budget << endl;


				if (i < n - 1) {
					if (j->second._data[i]._Forma.budget == 'b') {
						record << j->second._data[i]._Stipendiy.summastipendii << endl << endl;;
					}

					else {
						record << j->second._data[i]._Oplata.summaoplati << endl << endl;
					}
				}
				else {
					if (j->second._data[i]._Forma.budget == 'b') {
						record << j->second._data[i]._Stipendiy.summastipendii;
					}

					else {
						record << j->second._data[i]._Oplata.summaoplati;
					}
				}
			}
		}
		cout << "Данные записаны! " << endl;
	}

	else
		cout << "Ошибка открытия файла!" << endl;

	record.close();

}


void PrintGroup(map <int, Group>& d) {

	map<int, Group>::iterator j;
	for (j = d.begin(); j != d.end(); j++) {
		cout << "Номер Группы: " << j->first << "(" << j->second.counter << ")" << endl;
	}
	
}





int main()
{

	setlocale(LC_ALL, "");

	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
    Menu();

	map <int, Group> grupp;
	string answer, tmp;
	int _actions, counter,
		amountofdata = 0;
	string fileName;

	Data *d = (Data*)malloc(sizeof(Data) * amountofdata);
	

	while (_stateMenu != 0)
	{
		switch (_stateMenu)
		{
		case 1:

			system("cls");
			cout << "Ввод данных из бинарного файли или из текстогово? (bin, txt)" << endl;
			cin >> tmp;
			system("cls");

			if (tmp == "bin") {

				cout << "Введите название файла: ";
				cin >> fileName;

				BinaryReadingData(grupp, amountofdata, fileName);

				for (map<int, Group>::iterator j = grupp.begin(); j != grupp.end(); j++) {

					DataSorting(j->second._data, j->second.counter);
				}
			}

			else {
			//ввод из файла
			cout << "Введите название файла: ";
			cin >> fileName;

			ReadingData(grupp, amountofdata, fileName);

			for (map<int, Group>::iterator j = grupp.begin(); j != grupp.end(); j++) {

				DataSorting(j->second._data, j->second.counter);
				}
			}

			system("pause");
			system("cls");
			Menu();
			break;

		case 2:

			system("cls");

			if (!grupp.empty())
			{
				PrintGroup(grupp);
			}
			else
				cout << "Ещё нету ни одной группы!" << endl;


			system("pause");
			system("cls");
			Menu();
			break;

		case 3:

			system("cls");

				int groupNum;
				cout << "Введите номер новой группы: " << endl;
				cin >> groupNum;

				if (groupNum > 0 && groupNum < 10000) {
					AddNewGroup(grupp, groupNum);
					cout << "Новая группа была создана! " << endl;
				}


				while (groupNum < 0 || groupNum > 10000) {
					cout << "Номер группы введён некорректно!" << endl;
					cout << "Ввести заново? (yes,no)" << endl << endl;

					cin >> answer;
					if (answer == "yes") {
						system("cls");
						cout << "Введите номер новой группы: " << endl;
						cin >> groupNum;
						if (groupNum > 0 && groupNum < 10000) {
							AddNewGroup(grupp, groupNum);
							cout << "Новая группа была создана! " << endl;
						}						
					}
					else goto ExitMenu;
				}
					
			system("pause");
			system("cls");
			Menu();
			break;


		case 4:
			int gruppNum;
			

			system("cls");
			cout << "Введите номер группы" << endl;
			PrintGroup(grupp);
			cin >> gruppNum;
			system("cls");

			if (!grupp.empty())
			{
				SubMenu(grupp, amountofdata, gruppNum);
			}

					while (grupp.find(gruppNum) == grupp.end()) {

						cout << "Такой группы нету!" << endl;
						cout << "Создаём новую группу? (yes,no)" << endl << endl;
						
						cin >> answer;

						if (answer == "yes") {

							if (gruppNum > 0 && gruppNum < 10000) {
								AddNewGroup(grupp, gruppNum);
								cout << "Новая группа была создана! " << endl;
								system("cls");
								SubMenu(grupp, amountofdata, gruppNum);
							}


							while (gruppNum < 0 || gruppNum > 10000) {
								system("cls");
								cout << "Номер группы введён некорректно!" << endl;
								cout << "Ввести заново? (yes,no)" << endl << endl;

								cin >> answer;
								if (answer == "yes") {
									system("cls");
									cout << "Введите номер новой группы: " << endl;
									cin >> gruppNum;
									if (gruppNum > 0 && gruppNum < 10000) {
										AddNewGroup(grupp, gruppNum);
										cout << "Новая группа была создана! " << endl;
									}
									system("cls");

								}
							}
						}
						
						else {
							goto ExitMenu;
						}					
					}



					
				ExitMenu:
					system("pause");
					system("cls");
					Menu();
					break;

				
			
		case 5:

			system("cls");

			if (!grupp.empty())
			{
				DeleteGroup(grupp);
			}
			else
				cout << "Данные пусты!" << endl;


			system("pause");
			system("cls");
			Menu();
			break;


		case 6:

			system("cls");
			cout << "Ввод данных из бинарного файли или из текстогово? (bin, txt)" << endl;
			cin >> tmp;

			if (tmp == "bin") {
				system("cls");
				cout << "Введите название файла: ";
				cin >> fileName;
				BinarySavingdata(grupp, amountofdata, fileName);
			}

			else {

				system("cls");
				cout << "Введите название файла: ";
				cin >> fileName;
				Savingdata(grupp, amountofdata, fileName);
			}



			system("pause");
			system("cls");
			Menu();
			break;


		case 7:

			system("cls");

			if (!grupp.empty())
			{
				PrintAllInfo(grupp, amountofdata);
			}

			else
				cout << "Группы не найдены!" << endl;

			system("pause");
			system("cls");
			Menu();
			break;

		default:
			cout << "Неверно введён номер действия!" << endl;
			system("pause");
			system("cls");
			Menu();
			break;

		}

	}
    return 0;
}