#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці

using namespace std;

struct Room
{
	int size;
	string surname1;
	string initials1;
	string surname2;
	string initials2;
};

void Create(Room* p);
void Print(Room* p);
void Add(Room* p);
void Remove(Room* p);
void Edit(Room* p);
void Search(Room* p);
void SaveToFile(Room* p, const int N, const char* filename);
void LoadFromFile(Room*& p, int& N, const char* filename);

int main()

{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N = 15;

	Room* p = new Room[N];

	int menuItem;
	char filename[100];

	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - створити новий готель" << endl;
		cout << " [2] - вивід данних на екран" << endl;
		cout << " [3] - додати нового гостя" << endl;
		cout << " [4] - видалити гостя" << endl;
		cout << " [5] - редагувати гостя" << endl;
		cout << " [6] - знайти гостя" << endl;
		cout << " [7] - завантаження данних у файл" << endl;
		cout << " [8] - зчитування данних з файлу" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;

		switch (menuItem)
		{
		case 1:
			Create(p);
			break;
		case 2:
			Print(p);
			break;
		case 3:
			Add(p);
			break;
		case 4:
			Remove(p);
			break;
		case 5:
			Edit(p);
			break;
		case 6:
			Search(p);
			break;
		case 7:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			SaveToFile(p, N, filename);
			break;
		case 8:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			LoadFromFile(p, N, filename);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	system("pause");
	return 0;
}

void Create(Room* p)
{
	for (int i = 0; i < 10; i++)
	{
		p[i].size = 2;
		p[i].surname1 = "";
		p[i].initials1 = "";
		p[i].surname2 = "";
		p[i].initials2 = "";
	}
	for (int i = 10; i < 15; i++)
	{
		p[i].size = 1;
		p[i].surname1 = "";
		p[i].initials1 = "";
		p[i].surname2 = "";
		p[i].initials2 = "";
	}
}

void Print(Room* p)
{
	cout << "============================================================================================================================"
		<< endl;
	cout << "| №  |   Розмір   | Фамілія |      Ініціали      | Фамілія | Ініціали |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < 15; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " ";
		switch (p[i].size)
		{
		case 1:
			cout << "| " << setw(10) << fixed << right << "Одномісний" << " |";
			cout << setw(12) << fixed << right << p[i].surname1 << " |";
			cout << setw(14) << fixed << right << p[i].initials1 << " |";
			cout << setw(19) << fixed << "|";
			cout << setw(14) << fixed << "|" << endl;
			break;
		case 2:
			cout << "| " << setw(10) << fixed << right << "Двомісний" << " |";
			cout << setw(12) << fixed << right << p[i].surname1 << " |";
			cout << setw(14) << fixed << right << p[i].initials1 << " |";
			cout << setw(18) << fixed << right << p[i].surname2 << "|";
			cout << setw(13) << fixed << right << p[i].initials2 << "|" << endl;
			break;
		}
	}
	cout << "============================================================================================================================"
		<< endl;
	cout << endl;
}

void Add(Room* p)
{
	int nb;
	cout << "Введіть номер кімнати: "; cin >> nb;

	if (nb > 15 || nb < 1)
	{
		cout << "Недопустиме значення";
	}
	else if (p[nb - 1].surname1 != "" && p[nb - 1].surname2 != "")
	{
		cout << "В цій кімнаті вже знаходяться " << p[nb - 1].surname1 << " " << p[nb - 1].initials1 <<
									   " та " << p[nb - 1].surname2 << " " << p[nb - 1].initials2 << ", тому місць вже не має.";
	}
	else if (p[nb - 1].surname1 != "" && p[nb - 1].size == 1)
	{
		cout << "В цій кімнаті вже знаходиться " << p[nb - 1].surname1 << " " << p[nb - 1].initials1 << ", тому місць вже не має.";
	}
	else if (p[nb - 1].surname1 != "" && p[nb - 1].surname2 == "" && p[nb - 1].size == 2)
	{
		cout << "В цій кімнаті знаходиться " << p[nb - 1].surname1 << " " << p[nb - 1].initials1 << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
		cout << "Введіть, будь ласка, фамілію гостя: "; getline(cin, p[nb - 1].surname2);
		cout << "Введіть, будь ласка, ініціали гостя: "; getline(cin, p[nb - 1].initials2);
	}
	else if (p[nb - 1].surname1 == "")
	{
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
		cout << "Введіть, будь ласка, фамілію гостя: "; getline(cin, p[nb - 1].surname1);
		cout << "Введіть, будь ласка, ініціали гостя: "; getline(cin, p[nb - 1].initials1);
	}
}

void Remove(Room* p)
{
	int nb;
	int menu = 0;
	cout << "Введіть номер кімнати: "; cin >> nb;

	if (nb > 15 || nb < 1)
	{
		cout << "Недопустиме значення";
	}
	else if (p[nb - 1].surname1 != "" && p[nb - 1].surname2 != "")
	{
		cout << "В цій кімнаті знаходяться " << p[nb - 1].surname1 << " " << p[nb - 1].initials1 <<
									   " та " << p[nb - 1].surname2 << " " << p[nb - 1].initials2 <<endl;
		cout << "Виберіть дію:" << endl;
		cout << " [1] - видалити гостя: " << p[nb - 1].surname1 << " " << p[nb - 1].initials1 << endl;
		cout << " [2] - видалити гостя: " << p[nb - 1].surname2 << " " << p[nb - 1].initials2 << endl;
		cout << " [0] - повернутися до головного меню" << endl << endl;
		cout << "Введіть значення: "; cin >> menu;
		switch (menu)
		{
		case 1:
			p[nb - 1].surname1 = "";
			p[nb - 1].initials1 = "";
			break;
		case 2:
			p[nb - 1].surname2 = "";
			p[nb - 1].initials2 = "";
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	}
	else if (p[nb - 1].surname1 != "")
	{
		cout << "В цій кімнаті знаходиться " << p[nb - 1].surname1 << " " << p[nb - 1].initials1 << endl;
		cout << "Виберіть дію:" << endl;
		cout << " [1] - видалити гостя: " << p[nb - 1].surname1 << " " << p[nb - 1].initials1 << endl;
		cout << " [0] - повернутися до головного меню" << endl << endl;
		cout << "Введіть значення: "; cin >> menu;
		switch (menu)
		{
		case 1:
			p[nb - 1].surname1 = "";
			p[nb - 1].initials1 = "";
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	}
	else if (p[nb - 1].surname1 == "")
	{
		cout << "В цій кімнаті ніхто не знаходиться.";
	}
}

void Edit(Room* p)
{
	int nb;
	int menu = 0;
	cout << "Введіть номер кімнати: "; cin >> nb;

	if (nb > 15 || nb < 1)
	{
		cout << "Недопустиме значення";
	}
	else if (p[nb - 1].surname1 != "" && p[nb - 1].surname2 != "")
	{
		cout << "В цій кімнаті знаходяться " << p[nb - 1].surname1 << " " << p[nb - 1].initials1 <<
			" та " << p[nb - 1].surname2 << " " << p[nb - 1].initials2 << endl;
		cout << "Виберіть дію:" << endl;
		cout << " [1] - редагувати гостя: " << p[nb - 1].surname1 << " " << p[nb - 1].initials1 << endl;
		cout << " [2] - редагувати гостя: " << p[nb - 1].surname2 << " " << p[nb - 1].initials2 << endl;
		cout << " [0] - повернутися до головного меню" << endl << endl;
		cout << "Введіть значення: "; cin >> menu;
		switch (menu)
		{
		case 1:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << "Введіть, будь ласка, фамілію гостя: "; getline(cin, p[nb - 1].surname1);
			cout << "Введіть, будь ласка, ініціали гостя: "; getline(cin, p[nb - 1].initials1);
			break;
		case 2:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << "Введіть, будь ласка, фамілію гостя: "; getline(cin, p[nb - 1].surname2);
			cout << "Введіть, будь ласка, ініціали гостя: "; getline(cin, p[nb - 1].initials2);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	}
	else if (p[nb - 1].surname1 != "")
	{
		cout << "В цій кімнаті знаходиться " << p[nb - 1].surname1 << " " << p[nb - 1].initials1 << endl;
		cout << "Виберіть дію:" << endl;
		cout << " [1] - редагувати гостя: " << p[nb - 1].surname1 << " " << p[nb - 1].initials1 << endl;
		cout << " [0] - повернутися до головного меню" << endl << endl;
		cout << "Введіть значення: "; cin >> menu;
		switch (menu)
		{
		case 1:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << "Введіть, будь ласка, фамілію гостя: "; getline(cin, p[nb - 1].surname2);
			cout << "Введіть, будь ласка, ініціали гостя: "; getline(cin, p[nb - 1].initials2);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	}
	else if (p[nb - 1].surname1 == "")
	{
		cout << "В цій кімнаті ніхто не знаходиться." << endl;
		cout << "Виберіть дію: " << endl;
		cout << " [1] - додати гостя" << endl;
		cout << " [0] - повернутися до головного меню" << endl << endl;
		cout << "Введіть значення: "; cin >> menu;
		switch (menu)
		{
		case 1:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << "Введіть, будь ласка, фамілію гостя: "; getline(cin, p[nb - 1].surname1);
			cout << "Введіть, будь ласка, ініціали гостя: "; getline(cin, p[nb - 1].initials1);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	}
}

void Search(Room* p)
{
	int nb = 0;
	string surname;
	int room = 0;
	string initials;

	cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
	cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
	cout << "Введіть, будь ласка, прізвище гостя: "; getline(cin, surname); cout << endl;
	for (int i = 0; i < 15; i++)
	{
		if (p[i].surname1 == surname)
		{
			nb++;
			room = i;
		}
		if (p[i].surname2 == surname)
		{
			nb++;
			room = i;
		}
	}

	if (nb == 0)
		cout << "Такого мешканця немає.";
	else if (nb == 1)
		cout << p[room].surname1 << p[room].surname2 << " " << p[room].initials1 << p[room].initials2 << " знаходиться в кімнаті під номером " << room + 1 << endl;
	else if (nb > 1)
	{
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
		cout << "Введіть, будь ласка, ініціали гостя: "; getline(cin, initials);
		for (int i = 0; i < 15; i++)
		{
			if (p[i].surname1 == surname && p[i].initials1 == initials)
			{
				room = i;
			}
			if (p[i].surname2 == surname && p[i].initials1 == initials)
			{
				room = i;
			}
		}
		cout << p[room].surname1 << p[room].surname2 << p[room].initials1 << p[room].initials2 <<
			" знаходиться в кімнаті під номером " << room + 1 << endl;
	}
}

void SaveToFile(Room* p, const int N, const char* filename)
{
	ofstream fout(filename, ios::binary); // відкрили бінарний файл запису
	fout.write((char*)&N, sizeof(N)); // записали кількість елементів
	for (int i = 0; i < N; i++)
		fout.write((char*)&p[i], sizeof(Room)); // записали елементи масиву
	fout.close(); // закрили файл
}

void LoadFromFile(Room*& p, int& N, const char* filename)
{
	delete[] p; // знищили попередні дані
	ifstream fin(filename, ios::binary); // відкрили бінарний файл зчитування
	fin.read((char*)&N, sizeof(N)); // прочитали кількість елементів
	p = new Room[N]; // створили динамічний масив
	for (int i = 0; i < N; i++)
		fin.read((char*)&p[i], sizeof(Room)); // прочитали елементи масиву
	fin.close(); // закрили файл
}
