#include <iostream> // cin & cout
#include <algorithm> // sort
#include <string> // getline
using namespace std;

const int maxy{ 100 };

struct books_system {
	string book_name;
	int book_id, quantity, borrowed{ 0 };
	void add() {
		cout << "Enter book info: id & name & total quantitiy: ";
		cin >> book_id >> book_name >> quantity;
		borrowed = 0;
	}
	void print() {
		cout << "id = " << book_id << " name = " << book_name
			<< " total quantity " << quantity << " total borrowed "
			<< borrowed << endl;
	}
	void search(string search) {
		int l_book = book_name.length();
		int l_search = search.length();
		if (l_book < l_search)
			return;
		bool status{ true };
		for (int i{ 0 }; i < l_search; i++) {
			if (book_name[i] != search[i]) {
				status = false;
				break;
			}
		}
		if (status) {
			cout << book_name << endl;
		}

	}
};
bool compare_id(books_system a, books_system b) {
	return a.book_id < b.book_id;
}
bool compare_name(books_system a, books_system b) {
	return a.book_name < b.book_name;
}
struct users_system {
	string user_name;
	int user_id, books_borrowed[maxy];
	void add() {
		cout << "Enter user name & national id: ";
		cin >> user_name >> user_id;
	}
};
struct lib {
	books_system books[maxy];
	users_system users[maxy];
	int len_b{ 0 }, len_u{ 0 }, len_borr[maxy]{ 0 };
	int menu() {
		cout << "Library Menu\n";
		cout << "1) add book\n";
		cout << "2) search books by prefix\n";
		cout << "3) print who borrowed book by name\n";
		cout << "4) print library by id\n";
		cout << "5) print library by name\n";
		cout << "6) add user\n";
		cout << "7) user borrow book\n";
		cout << "8) user return book\n";
		cout << "9) print users\n";
		cout << "10) Exit\n\n";
		cout << "Enter your menu choice [1 - 10]: ";
		int choice;
		cin >> choice;
		if (choice < 1 || choice >10) {
			cout << "Invalid choice, please enter a value from 1 to 10 inclusive\n";
			return -1;
		}
		return choice;
	}
	void run() {
		while (true) {
			int choice = menu();
			if (choice == 1) {
				books[len_b++].add();
			}
			else if (choice == 2) {
				cout << "Enter book name prefix: ";
				string search;
				cin >> search;
				for (int i{ 0 }; i < len_b; i++) {
					books[i].search(search);
				}
			}
			else if (choice == 3) {
				who();
			}
			else if (choice == 4) {
				sort(books, books + len_b, compare_id);
				for (int i{ 0 }; i < len_b; i++) {
					books[i].print();
				}
			}
			else if (choice == 5) {
				sort(books, books + len_b, compare_name);
				for (int i{ 0 }; i < len_b; i++) {
					books[i].print();
				}
			}
			else if (choice == 6) {
				users[len_u++].add();
			}
			else if (choice == 7) {
				user_borrow();
			}
			else if (choice == 8) {
				user_return();
			}
			else if (choice == 9) {
				user_print();
			}
			else if (choice == 10) {
				break;
			}
		}
	}
	void who() {
		cout << "Enter book name: ";
		string bookk_name;
		cin >> bookk_name;
		int book_index = get_book(bookk_name);
		for (int i{ 0 }; i < len_u; i++) {
			for (int j{ 0 }; j < len_borr[i]; j++) {
				if (users[i].books_borrowed[j] == books[book_index].book_id) {
					cout << users[i].user_name << endl;
					break;
				}
			}
		}
	}
	void user_borrow() {
		cout << "Enter user name and book name: ";
		string userr_name, bookk_name;
		int index{ 0 };
		cin >> userr_name >> bookk_name;
		bool status = true;
		for (int i{ 0 }; i < len_b; i++) {
			if (books[i].book_name == bookk_name) {
				if (books[i].borrowed < books[i].quantity) {
					books[i].borrowed++;
					index = i;
					status = false;
				}
				else {
					cout << "All the " << books[i].book_name << " have been borrowed\n";
					status = false;
					index = i;
					return;
				}
			}
		}
		if (status) {
			cout << "There's no book with this name\n";
			return;
		}
		status = true;
		for (int i{ 0 }; i < len_u; i++) {
			if (users[i].user_name == userr_name) {
				users[i].books_borrowed[len_borr[i]] = books[index].book_id;
				len_borr[i]++;
				status = false;
				return;
			}
		}
		if (status) {
			cout << "There's no user with this name\n";
			books[index].borrowed--;
			return;
		}
	}
	void user_return() {
		cout << "Enter user name and book name: ";
		string userr_name, bookk_name;
		cin >> userr_name >> bookk_name;
		int user_index = get_user(userr_name);
		int book_index = get_book(bookk_name);
		if (user_index != -1) {
			if (book_index != -1) {
				for (int i{ 0 }; i < len_borr[user_index]; i++) {
					if (users[user_index].books_borrowed[i] == books[book_index].book_id) {
						users[user_index].books_borrowed[i] = 0;
						books[book_index].borrowed--;
					}
				}
			}
			else {
				cout << "There's no book with this name";
			}
		}
		else {
			cout << "There's no user with this name";
		}
	}
	int get_book(string bookk_name) {
		int book_index;
		for (int i{ 0 }; i < len_b; i++) {
			if (books[i].book_name == bookk_name) {
				book_index = i;
				return book_index;
			}
		}
		return -1;
	}
	int get_user(string userr_name) {
		int user_index;
		for (int i{ 0 }; i < len_u; i++) {
			if (users[i].user_name == userr_name) {
				user_index = i;
				return user_index;
			}
		}
		return -1;
	}
	void user_print() {
		for (int i{ 0 }; i < len_u; i++) {
			cout << "user " << users[i].user_name << " id " << users[i].user_id;
			cout << " borrowed books ids: ";
			for (int j{ 0 }; j < len_borr[i]; j++) {
				if (users[i].books_borrowed[j] != 0) {
					cout << users[i].books_borrowed[j] << " ";
				}
			}
			cout << endl;
		}
		cout << endl;
	}
};

int main() {
	lib libr;
	libr.run();
}