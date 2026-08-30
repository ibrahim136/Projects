#include <iostream>; // cin & cout
#include <string>; // getline
using namespace std;
string name[100] = {}, age[100] = {}, salary[100] = {}, gender[100] = {};
int menu() {
	cout << "Enter Your choice:\n";
	cout << "1) Add new employee\n";
	cout << "2) Print all employees\n";
	cout << "3) Delete by age\n";
	cout << "4) Update Salary by name\n";
	int choice;
	cin >> choice;
	return choice;
}
void read_employee() {
	static int cnt{ 0 };
	cout << "Enter name: ";
	cin >> name[cnt];
	cout << "Enter age: ";
	cin >> age[cnt];
	cout << "Enter salary: ";
	cin >> salary[cnt];
	cout << "Enter gender (M/F): ";
	cin >> gender[cnt];
	cout << endl;
	cnt++;
}
void print_employees() {
	cout << "\n";
	for (int i{ 0 }; i < 100; i++) {
		if (name[i] == "")
			continue;
		cout << name[i] << " " << age[i] << " " << salary[i] << " " << gender[i] << endl;
	}
}
void delete_by_age() {
	cout << "Enter start and end age: ";
	string start, end;
	cin >> start >> end;
	for (int i{ 0 }; i < 100; i++)
		if (start <= age[i] && age[i] <= end)
			name[i] = "", age[i] = "", gender[i] = "", salary[i] = "";
}
void update_salary_by_name() {
	string up_name, up_salary;
	cout << "Enter the name and the salary: ";
	cin >> up_name >> up_salary;
	for (int i{ 0 }; i < 100; i++) {
		if (name[i] == "")
			continue;
		if (name[i] == up_name) {
			salary[i] = up_salary;
			break;
		}
	}
}
int main() {
	while (1) {
		int choice = menu();
		if (choice < 1 || choice >4) {
			cout << "OUT OF RANGE\n";
			continue;
		}
		if (choice == 1) {
			read_employee();
		}
		if (choice == 2) {
			print_employees();
		}
		if (choice == 3) {
			delete_by_age();
		}
		if (choice == 4) {
			update_salary_by_name();
		}
	}
}