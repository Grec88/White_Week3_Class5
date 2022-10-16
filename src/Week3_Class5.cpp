//============================================================================
// Name        : Week3_Class5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string> &names, int year) {
	string name;  // изначально имя неизвестно

	// перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
	for (const auto& [key, value] : names) {
		// если очередной год не больше данного, обновляем имя
		if (key <= year) {
			name = value;
		} else {
			// иначе пора остановиться, так как эта запись и все последующие относятся к будущему
			break;
		}
	}

	return name;
}

vector<string> FindSetByYear(const map<int, string> &names, int year) {
	vector<string> chrono;  // изначально имя неизвестно

	// перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
	for (const auto& [key, value] : names) {
		if (key <= year) {
			chrono.push_back(value);
		} else {
			// иначе пора остановиться, так как эта запись и все последующие относятся к будущему
			break;
		}
	}
	reverse(chrono.begin(), chrono.end());
	//unique(chrono.begin(), chrono.end());
	return chrono;
}

string GetString(const vector<string> &a) {
	string chrono = "";
	if (a.empty() == 0) {
		for (size_t i = 0; i < a.size(); ++i) {
			if (a.size() > 1) {
				if (i < a.size() - 1) {
					chrono += (a[i] + ", ");
				} else {
					chrono += a[i];
				}
			}
			if (a.size() == 1) {
				chrono += a[i];
			}
		}
	}
	return chrono;
}

class Person {
public:

	Person(const string &new_name, const string &new_surname,
			const int &birth_year) {
		name = new_name;
		surname = new_surname;
		year = birth_year;
		first_names[birth_year] = new_name;
		last_names[birth_year] = new_surname;
	}

	void ChangeFirstName(int year, const string &first_name) {
		first_names[year] = first_name;
	}
	void ChangeLastName(int year, const string &last_name) {
		last_names[year] = last_name;
	}

	string GetFullName(int new_year) const {
		if (year > new_year) {
			return "No person";
		}
		// получаем имя и фамилию по состоянию на год year
		const string first_name = FindNameByYear(first_names, new_year);
		const string last_name = FindNameByYear(last_names, new_year);

		// если и имя, и фамилия неизвестны
		if (first_name.empty() && last_name.empty() && name.empty()
				&& surname.empty()) {
			return "Incognito";

			// если неизвестно только имя
		}
		if (first_name.empty() && last_name.empty() && name.empty() == 0
				&& surname.empty() == 0) {
			return name + " " + surname;

			// если неизвестно только имя
		} else if (first_name.empty()) {
			return last_name + " with unknown first name";

			// если неизвестна только фамилия
		} else if (last_name.empty()) {
			return first_name + " with unknown last name";

			// если известны и имя, и фамилия
		} else {
			return first_name + " " + last_name;
		}
	}

	string GetFullNameWithHistory(int new_year) const {
		if (year > new_year) {
			return "No person";
		}
		// получаем имя и фамилию по состоянию на год year
		const string first_name = FindNameByYear(first_names, new_year);
		const string last_name = FindNameByYear(last_names, new_year);
		vector<string> ch1 = FindSetByYear(first_names, new_year);
		vector<string> ch2 = FindSetByYear(last_names, new_year);
		for (size_t i = 1; i < ch1.size(); i++) {
			if (ch1[i - 1] == ch1[i]) {
				ch1.erase(ch1.begin() + i);
			}
		}
		for (size_t i = 1; i < ch2.size(); i++) {
			if (ch2[i - 1] == ch2[i]) {
				ch2.erase(ch2.begin() + i);
			}
		}
		if (count(ch1.begin(), ch1.end(), first_name) == ch1.size()) {
			for (int i = 0; i < ch1.size(); i++) {
				ch1.erase(find(ch1.begin(), ch1.end(), first_name));
			}
		}
		if (count(ch2.begin(), ch2.end(), last_name) == ch2.size()) {
			for (int i = 0; i < ch2.size(); i++) {
				ch2.erase(find(ch2.begin(), ch2.end(), last_name));
			}
		}
		if (count(ch1.begin(), ch1.end(), first_name) >= 1) {
			ch1.erase(find(ch1.begin(), ch1.end(), first_name));
		}
		if (count(ch2.begin(), ch2.end(), last_name) >= 1) {
			ch2.erase(find(ch2.begin(), ch2.end(), last_name));
		}
		if (count(ch2.begin(), ch2.end(), last_name) == 1 && ch2.size() == 1) {
			ch2.erase(find(ch2.begin(), ch2.end(), last_name));
		}
		if (count(ch1.begin(), ch1.end(), first_name) == 1 && ch1.size() == 1) {
			ch1.erase(find(ch1.begin(), ch1.end(), first_name));
		}
		const string chrono1 = GetString(ch1);
		const string chrono2 = GetString(ch2);
		// если и имя, и фамилия неизвестны
		if (first_name.empty() && last_name.empty() && name.empty() == 0
				&& surname.empty() == 0) {
			return name + " " + surname;

			// если неизвестно только имя
		} else if (first_name.empty() && chrono2 != "") {
			return last_name + " (" + chrono2 + ") " + "with unknown first name";

			// если неизвестна только фамилия
		} else if (first_name.empty() && chrono2 == "") {
			return last_name + " with unknown first name";

			// если неизвестна только фамилия
		} else if (last_name.empty() && chrono1 != "") {
			return first_name + " (" + chrono1 + ") " + "with unknown last name";

			// если известны и имя, и фамилия
		} else if (last_name.empty() && chrono1 == "") {
			return first_name + " with unknown last name";

			// если известны и имя, и фамилия
		} else if (chrono1 != "" && chrono2 != "") {
			return first_name + " (" + chrono1 + ") " + last_name + " ("
					+ chrono2 + ")";
		} else if (chrono1 != "" && chrono2 == "") {
			return first_name + " (" + chrono1 + ") " + last_name;
		} else if (chrono1 == "" && chrono2 != "") {
			return first_name + " " + last_name + " (" + chrono2 + ")";
		} else if (chrono1 == "" && chrono2 == "") {
			return first_name + " " + last_name;
		}
	}

private:
	map<int, string> first_names;
	map<int, string> last_names;
	string name;
	string surname;
	int year;
};
/*#include <algorithm>
 #include <map>
 #include <vector>
 #include <string>

 using namespace std;

 vector<string> FindNamesHistory(const map<int, string>& names_by_year,
 int year) {
 vector<string> names;
 // перебираем всю историю в хронологическом порядке
 for (const auto& item : names_by_year) {
 // если очередное имя не относится к будущему и отличается от предыдущего,
 if (item.first <= year && (names.empty() || names.back() != item.second)) {
 // добавляем его в историю
 names.push_back(item.second);
 }
 }
 return names;
 }

 string BuildJoinedName(vector<string> names) {
 // нет истории — имя неизвестно
 if (names.empty()) {
 return "";
 }
 // меняем прямой хронологический порядок на обратный
 reverse(begin(names), end(names));

 // начинаем строить полное имя с самого последнего
 string joined_name = names[0];

 // перебираем все последующие имена
 for (int i = 1; i < names.size(); ++i) {
 if (i == 1) {
 // если это первое «историческое» имя, отделяем его от последнего скобкой
 joined_name += " (";
 } else {
 // если это не первое имя, отделяем от предыдущего запятой
 joined_name += ", ";
 }
 // и добавляем очередное имя
 joined_name += names[i];
 }

 // если в истории было больше одного имени, мы открывали скобку — закроем её
 if (names.size() > 1) {
 joined_name += ")";
 }
 // имя со всей историей готово
 return joined_name;
 }

 // см. решение предыдущей задачи
 string BuildFullName(const string& first_name, const string& last_name) {
 if (first_name.empty() && last_name.empty()) {
 return "Incognito";
 } else if (first_name.empty()) {
 return last_name + " with unknown first name";
 } else if (last_name.empty()) {
 return first_name + " with unknown last name";
 } else {
 return first_name + " " + last_name;
 }
 }

 class Person {
 public:
 void ChangeFirstName(int year, const string& first_name) {
 first_names[year] = first_name;
 }
 void ChangeLastName(int year, const string& last_name) {
 last_names[year] = last_name;
 }

 string GetFullName(int year) {
 // найдём историю изменений имени и фамилии
 // в данном случае это излишне, так как нам достаточно узнать последние имя и фамилию, но почему бы не использовать готовые функции?
 const vector<string> first_names_history = FindFirstNamesHistory(year);
 const vector<string> last_names_history = FindLastNamesHistory(year);

 // подготовим данные для функции BuildFullName: возьмём последние имя и фамилию или оставим их пустыми, если они неизвестны
 string first_name;
 string last_name;
 if (!first_names_history.empty()) {
 first_name = first_names_history.back();
 }
 if (!last_names_history.empty()) {
 last_name = last_names_history.back();
 }
 return BuildFullName(first_name, last_name);
 }

 string GetFullNameWithHistory(int year) {
 // получим полное имя со всей историей
 const string first_name = BuildJoinedName(FindFirstNamesHistory(year));
 // получим полную фамилию со всей историей
 const string last_name = BuildJoinedName(FindLastNamesHistory(year));
 // объединим их с помощью готовой функции
 return BuildFullName(first_name, last_name);
 }

 private:
 vector<string> FindFirstNamesHistory(int year) {
 return FindNamesHistory(first_names, year);
 }
 vector<string> FindLastNamesHistory(int year) {
 return FindNamesHistory(last_names, year);
 }

 map<int, string> first_names;
 map<int, string> last_names;
 };*/

int main() {
	Person person("Polina", "Sergeeva", 1960);
	for (int year : { 1959, 1960 }) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1965, "Appolinaria");
	person.ChangeLastName(1967, "Ivanova");
	for (int year : { 1965, 1967 }) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	return 0;
}
