#include <iostream>; // cin & cout
#include <string>; // getline
using namespace std;

string a[20][5];
int s[20][5]{ 0 };
void menu() {
	cout << "Enter your choice:\n";
	cout << "1) Add new patient\n";
	cout << "2) Print all patients\n";
	cout << "3) Get next patient\n";
	cout << "4) Exit\n";
}

void add(int x, string y, int z) {
	x--;
	int cnt{ 0 };
	for (int i{ 0 }; i < 5; i++) {
		if (a[x][i] != "")
			cnt++;
	}
	if (cnt == 5) {
		cout << "Sorry we can't add more patients for this specialization\n\n";
		return;
	}
	if (z) {
		int temp_i;
		for (int i{ 0 }; i < 5; i++) {
			if (a[x][i] == "") {
				temp_i = i;
				break;
			}
		}
		for (int i{ temp_i }; i >= 0; i--) {
			if (i == 0) {
				a[x][i] = y;
				s[x][i] = z;
			}
			else {
				a[x][i] = a[x][i - 1];
				s[x][i] = s[x][i - 1];
			}
		}
	}
	else {
		int temp_i;
		for (int i{ 4 }; i >= 0; i--) {
			if (a[x][i] == "") {
				temp_i = i;
				break;
			}
		}
		for (int i{ temp_i }; i < 5; i++) {
			if (i == 4) {
				a[x][i] = y;
				s[x][i] = z;
			}
			else {
				a[x][i] = a[x][i + 1];
				s[x][i] = s[x][i + 1];
			}
		}
	}
}

void print() {
	cout << "\n";
	for (int i{ 0 }; i < 20; i++) {
		int cnt{ 0 };
		for (int j{ 0 }; j < 5; j++) {
			if (a[i][j] != "")
				cnt++;
		}
		if (cnt != 0) {
			cout << "There are " << cnt << " patient(s) in specialization " << i + 1 << endl;
			for (int j{ 0 }; j < 5; j++) {
				if (a[i][j] != "") {
					cout << a[i][j] << " ";
					if (s[i][j])
						cout << "urgent\n";
					else
						cout << "regular\n";
				}
			}
			cout << "\n\n";
		}
	}
	cout << "\n\n";
}

void next(int x) {
	for (int i = 0; i < 5; i++) {
		if (a[x][i] == "") {
			if (i == 4)
				cout << "No patients at the moment. Have rest, Dr\n\n";
			continue;
		}
		else {
			cout << a[x][i] << " please go with the Dr\n\n";
			a[x][i] = "";
			break;
		}

	}
}

int main() {
	while (1) {
		menu();
		int c{};
		cin >> c;
		if (c < 1 || c>4) {
			cout << "Invalid choice (you must choice from 1 to 4)\n\n";
			continue;
		}
		if (c == 4)
			break;
		if (c == 1) {
			cout << "Enter specialization, name, & status: ";
			int x, z;
			string y;
			cin >> x >> y >> z;
			add(x, y, z);
			cout << endl;
		}
		else if (c == 2) {
			print();
		}
		else if (c == 3) {
			cout << "Enter specialization: ";
			int x;
			cin >> x;
			x--;
			next(x);
		}



	}

}