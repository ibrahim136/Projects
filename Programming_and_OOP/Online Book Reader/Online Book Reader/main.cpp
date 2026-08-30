#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <random>
#include <conio.h>
#include <fstream>
#include <array>
#include <memory>
#include <cctype>
#include <chrono>
#include <format>
#include <ctime>
using namespace std;
const string yellow = "\033[33m";
const string red = "\033[31m";
const string blue = "\033[36m";
const string green = "\033[32m";
const string reset = "\033[0m";
const string clear = "\033[2J\033[H";

class admin {
private:
	string user_name, password,name,email;
public:
	admin() {};
	admin(string user_name, string password,string name,string email) : user_name(user_name), password(password),
		email(email),name(name) {}
	bool check_admin_login(string& user_name, string& password) const {
		if (user_name == this->user_name && password == this->password) {
			return true;
		}
		else {
			return false;
		}
	}
	bool check_username(string& user_name) const {
		if (user_name == this->user_name) {
			return true;
		}
		else {
			return false;
		}
	}
	const string get_name() const {
		return name;
	}
	void admin_to_user(string& user_name, string& password, string& id, string& email,string& name) const {
		user_name = this->user_name;
		name = this->name;
		password = this->password;
		email = this->email;
		id = "0";
	}
};

	

class printing {
private:
	pair<int,bool> limit_range(const int& min, const int& max) const {
		bool valid{ false };
		cout << blue + "Enter number in range " << min << "-" << max << ": " + reset;
		string choice_s;
		getline(cin, choice_s);
		istringstream iss(choice_s);
		int choice;
		iss >> choice;

		if (iss.fail()) {
			cout << red << "\nInvalid input (please input a number)\n\n" << reset;
			return make_pair(choice, valid);
		}
		if (choice < min || choice > max) {
			cout << red << "\nInvalid input range (range : " << min << "-" << max << ")\n\n" << reset;
			return make_pair(choice, valid);
		}
		cout << endl;
		valid = true;
		return make_pair(choice,valid);
	}
public:
	
	int menu1() const {
		bool valid{ false };
		int choice;
		do {
			cout << yellow << "Menu:\n" << reset;
			cout << "		1: Login\n";
			cout << "		2: Sign Up\n";
			cout << "		3: Exit\n\n";
			pair <int, bool> p{limit_range(1,3)};
			choice = p.first;
			valid = p.second;
		} while (!valid);
		return choice;
	}
	int menu2() const {
		bool valid{ false };
		int choice;
		do {
			cout << yellow << "Menu:\n" << reset;
			cout << "		1: View Profile\n";
			cout << "		2: List & Select from My Reading History\n";
			cout << "		3: List & Select from Available Books\n";
			cout << "		4: Logout\n\n";
			pair <int, bool> p{ limit_range(1,4) };
			choice = p.first;
			valid = p.second;
		} while (!valid);
		return choice;
	}
	int menu3() const {
		bool valid{ false };
		int choice;
		do {
			cout << yellow << "Menu:\n" << reset;
			cout << "		1: View Profile\n";
			cout << "		2: Add Book\n";
			cout << "		3: Logout\n\n";
			pair <int, bool> p{ limit_range(1,3) };
			choice = p.first;
			valid = p.second;
		} while (!valid);
		return choice;
	}
	int menu4(vector<string> titles) const {
		bool valid{ false };
		int choice;
		do {
			cout << yellow << "\nOur current book collection:\n" << reset;
			for (int i{ 0 }; i < titles.size();i++) {
				cout << "		" + to_string(i+1) + ": " + titles[i] << endl;
			}
			cout << "Which book to read?\n";
			pair <int, bool> p{ limit_range(1,titles.size()) };
			choice = p.first;
			valid = p.second;
		} while (!valid);
		return choice-1;
	}
	pair <int,string> menu5(int& page, vector<string>& contents) const {
		bool valid{ false };
		int choice;
		int max;
		int size = contents.size();
		int next{ 0 };
		do {
			cout << "\n\n" + yellow + "Current Page: " + to_string(page) + "/" + to_string(size) + reset;
			cout << "\n\n" + contents[page-1] << "\n\n";
			cout << yellow << "Menu:\n" << reset;
			if (page < size && page >1) {
				cout << "		1: Next Page\n";
				cout << "		2: Previous Page\n";
				cout << "		3: Stop Reading\n\n";
				max = 3;
				next = 1;
			}
			else if (page > 1 && size == page) {;
				cout << "		1: Previous Page\n";
				cout << "		2: Stop Reading\n\n";
				max = 2;
			}
			else {
				cout << "		1: Next Page\n";
				cout << "		2: Stop Reading\n\n";
				max = 2;
				next = 1;
			}
			pair <int, bool> p{ limit_range(1,max) };
			choice = p.first;
			valid = p.second;
			if (choice == max) {
				std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
				time_t now_c = std::chrono::system_clock::to_time_t(now);
				tm ltm;
				localtime_s(&ltm, &now_c);
				char buffer[80];
				strftime(buffer, sizeof(buffer), "%Y-%m-%d %I:%M:%S %p", &ltm);
				return make_pair(page,buffer);
			}
			else if (choice == next) {
				page++;
			}
			else {
				page--;
			}
			valid = p.second;
		} while (!valid || choice !=max);
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		time_t now_c = std::chrono::system_clock::to_time_t(now);
		tm ltm;
		localtime_s(&ltm, &now_c);
		char buffer[80];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %I:%M:%S %p", &ltm);
		return make_pair(page, buffer);
	}
	int menu6(vector<string> &titles,vector<int> &pages,vector<string> &times,vector<vector<string>> & contents) const {
		bool valid{ false };
		int choice;
		do {
			cout << yellow << "\nYour current books history:\n" << reset;
			for (int i{ 0 }; i < titles.size(); i++) {
				cout << "		" + to_string(i + 1) + ": " + titles[i] << ": " + to_string(pages[i])
					+ "/" + to_string(contents[i].size()) + " - " + times[i] << endl;
			}
			cout << "\nWhich session to open?\n";
			pair <int, bool> p{ limit_range(1,titles.size()) };
			choice = p.first;
			valid = p.second;
		} while (!valid);
		return choice - 1;
	}
};

class user;
class users_manager {
private:
	vector<array<string, 5>> users_data;
	vector<array<string, 5>> load_data() const;
public:
	users_manager() {
		users_data =load_data();
	}
	void reload() {
		users_data = load_data();
	}
	const vector<array<string, 5>> & get_users_data() const {
		return users_data;
	}
	const array<string, 5> user_format(const string& user_name, const
		string& id, const string& password, const string& name, const string& email) const {
		array<string, 5> ret = { user_name ,id ,password ,name ,email };
		return ret;
	}
};

class Authentication;
class books_manager;
class book;

class user {
private:
	string user_name, id, password, name, email;
	users_manager* u_m{nullptr};
	admin* admin_u{nullptr};
	books_manager* b_m{ nullptr };
	unique_ptr<Authentication> lsp;
	pair<bool,bool> search_for_user_and_password(string &username, string &password,admin *admin_u) {
		bool check_login{ false }, check_admin{ false };
		const vector<array<string, 5>>& users_data = u_m->get_users_data();
		if (admin_u->check_admin_login(username,password)) {
			check_login = true;
			check_admin = true;
			return make_pair(check_login, check_admin);
		}
		for (int i{ 0 }; i < users_data.size(); i++) {
				if (((users_data)[i])[0] == username && (((users_data)[i])[2] == password)) {
					check_login = true;
					email = ((users_data)[i])[4];
					name = ((users_data)[i])[3];
					id = ((users_data)[i])[1];
					return make_pair(check_login, check_admin);
			}
		}
		return make_pair(check_login, check_admin);
	}
	void print_to_users_books_history_file()const;
	pair<bool, bool> signup();
	pair<bool, bool> login();
public:
	user(const user&) = delete;
	user& operator=(const user&) = delete;
	user(users_manager& u_m, admin& admin_u,books_manager &b_m);
	pair<bool, bool> run(bool is_login) {
		pair<bool, bool> ret{ false,false };
		if (is_login) {
			ret = login();

		}
		else {
			ret = signup();
		}
		return ret;
	}
	string get_name() const {
		return name;
	}
	string get_email() const {
		return email;
	}
	string get_username() const {
		return user_name;
	}
	string get_id() const {
		return id;
	}
};

class Authentication {
private:
	string user_name, id, password, email, name;
	user* u{ nullptr };
	admin* admin_u{ nullptr };
	users_manager* u_m{ nullptr };
	bool is_login{ true };
	pair<bool, bool> is_comma_is_space(const string& test) const {
		bool is_comma{ test.find(',') != string::npos };
		bool is_space{ test.find(' ') != string::npos};
		return make_pair(is_comma, is_space);
	}
	tuple<bool, bool,bool> searching(string& username, string password= "") {
		bool check_login{ false }, check_admin{ false }, exists{ false };
		const vector<array<string, 5>>& users_data = u_m->get_users_data();
		if (is_login) {
			if (admin_u->check_admin_login(username, password)) {
				check_login = true;
				check_admin = true;
				admin_u->admin_to_user(user_name, this->password, id, email, name);
				return { check_login,check_admin,exists };
			}
			for (int i{ 0 }; i < users_data.size(); i++) {
				if (((users_data)[i])[0] == user_name && (((users_data)[i])[2] == password)) {
					check_login = true;
					email = ((users_data)[i])[4];
					name = ((users_data)[i])[3];
					id = ((users_data)[i])[1];
					return { check_login,check_admin,exists };
				}
			}
			return { check_login,check_admin,exists };
		}
		else {
			for (int i{ 0 }; i < users_data.size(); i++) {
				if (((users_data)[i])[0] == user_name) {
					exists = true;
					break;
				}
				if (admin_u->check_username(user_name)) {
					exists = true;
					break;
				}
			}
			return { check_login,check_admin,exists };
		}
	}
	void user_name_input() {
		while (true) {
			cout << blue + "Enter user name (No spaces): " + reset;
			getline(cin, user_name);
			if (user_name.empty()) {
				cout << red + "\nUsername can't set to be empty\n\n" + reset;
				continue;
			}
			pair <bool, bool> p = is_comma_is_space(user_name);
			bool is_comma{ false }, is_space{ p.second }, exists{ false };
			if (!is_login) {
				is_comma = p.first;
				exists = get<2>(searching(user_name));
			}
			if (is_comma && is_space) {
				cout << red + "\nUsername can't contain a space \" \" or a comma \",\"\n\n" + reset;
				continue;
			}
			if (is_comma) {
				cout << red + "\nUsername can't contain a comma \",\"\n\n" + reset;
				continue;
			}
			if (is_space) {
				cout << red + "\nUsername can't contain a space \" \"\n\n" + reset;
				continue;
			}
			if (exists) {
				cout << red + "\nUsername is already exists\n\n" + reset;
				continue;
			}
			break;
		}
		return;
	}
	void password_input() {
		while (true) {
			cout << blue + "Enter password: " + reset;
			char ch;
			password.clear();
			while ((ch = _getch()) != '\r') {
				if (ch == '\b') {
					if (!password.empty()) {
						cout << "\b \b";
						password.pop_back();
					}
				}
				else {
					password += ch;
					cout << "*";
				}
			}
			cout << endl;
			if (password.empty()) {
				cout << red + "\nPassword can't set to be empty\n\n";
				continue;
			}
			bool is_comma = false;
			if (!is_login) {
				is_comma = is_comma_is_space(password).first;
			}
			if (is_comma) {
				cout << red + "Password can't contain a comma \",\"\n\n";
				continue;
			}
			break;
		}
		return;
	}
	void email_input() {
		while (true) {
			cout << blue + "Enter email (No spaces): " + reset;
			getline(cin, email);
			pair <bool,bool> p = is_comma_is_space(email);
			bool is_comma{ p.first }, is_space{ p.second };
			if (is_comma && is_space) {
				cout << red + "\nEmail can't contain a space \" \" or a comma \",\"\n\n" + reset;
				continue;
			}
			if (is_comma) {
				cout << red + "\nEmail can't contain a comma \",\"\n\n" + reset;
				continue;
			}
			if (is_space) {
				cout << red + "\nEmail can't contain a space \" \"\n\n" + reset;
				continue;
			}
			break;
		}
		return;
	}
	void random_id() {
		vector<int> ids;
		const vector<array<string, 5>>& users_data = u_m->get_users_data();
		for (int i{ 0 }; i < users_data.size(); i++) {
			istringstream iss(((users_data)[i])[1]);
			int id;
			iss >> id;
			ids.push_back(id);
		}
		int id;
		while (true) {
			random_device rd; // generating random id
			mt19937 gen(rd());
			uniform_int_distribution<>distrib(1, 999);
			id = distrib(gen);
			vector<int>::iterator it = find(ids.begin(), ids.end(), id);
			if (it == ids.end()) {
				break;
			}
		}
		this->id = to_string(id);
		return;
	}
	void name_input() {
		while (true) {
			cout << blue + "Enter name: " + reset;
			getline(cin, name);
			if (name.empty()) {
				cout << red + "\nName can't set to be empty\n\n" + reset;
				continue;
			}
			bool is_comma{ is_comma_is_space(name).first};
			if (is_comma) {
				cout << red + "\nName can't contain a comma \",\"\n\n" + reset;
				continue;
			}
			break;
		}
		return;
	}
	pair<array<string, 5>, pair<bool, bool>> login() {
		user_name_input();
		password_input();
		tuple<bool, bool, bool> t = searching(user_name, password);
		pair <bool, bool> p_check = make_pair(get<0>(t), get<1>(t));
		array<string, 5> ret_arr = { user_name,id,password,name,email };
		return make_pair(ret_arr,p_check);
	}
	array<string, 5> signup() {
		user_name_input();
		name_input();
		password_input();
		email_input();
		random_id();
		return { user_name,id,password,name,email };
	}
public:
	Authentication(){}
	Authentication(admin &admin_u,users_manager & u_m) : admin_u(&admin_u),u_m(&u_m){}
	pair<array<string,5>,pair<bool,bool>> run(bool l) {
		this->is_login = l;
		array<string, 5> ret;
		pair<bool, bool> p_check{ false,false };
		if (l) {
			pair <array<string, 5>, pair<bool, bool>> p = login();
			ret = p.first;
			p_check = p.second;
		}
		else {
			ret = signup();
			p_check = make_pair(true, false);
		}
		return make_pair(ret, p_check);
	}
	
};

class book {
private:
	string ISBN, title, author_name, nop;
	vector<string> contents;
public:
	book(string &ISBN,string &title,string &author_name,string &nop,vector<string> &contents): 
		ISBN(ISBN), title(title), author_name(author_name), nop(nop),contents(contents){ }
	string get_ISBN() const {
		return ISBN;
	}
	string get_title() const {
		return title;
	}
	vector<string> get_content()const {
		return contents;
	}
};

class books_manager {
private:
	vector <book> books;
	void load_books() {
		books.clear();
		ifstream books_file_in("books.txt");
		if (books_file_in.fail()) {
			cout << red << "Failed to access books file";
			return;
		}
		string line;
		while (getline(books_file_in, line)) {
			string ISBN, title, author_name, nop;
			vector<string> contents;
			string content;
			int cnt = 0;
			for (char x : line) {
				if (x == ',' && cnt >= 4) {
					contents.push_back(content);
					content.clear();
					cnt++;
					continue;
				}
				if (x == ',') {
					cnt++;
					continue;
				}
				if (cnt == 0) {
					ISBN += x;
				}
				else if (cnt == 1) {
					title += x;
				}
				else if (cnt == 2) {
					author_name += x;
				}
				else if (cnt == 3) {
					nop += x;
				}
				else if (cnt >= 4) {
					content += x;
				}
			}
			contents.push_back(content);
			books.push_back(book(ISBN, title, author_name, nop, contents));
			ISBN.clear();
			title.clear();
			author_name.clear();
			nop.clear();
			contents.clear();
		}
	}
public:
	books_manager() {
		load_books();
	}
	void reload() {
		load_books();
	}
	const vector<book>& get_books() const {
		return books;
	}
};

class add_book {
private:
	string ISBN, title, author_name, nop;
	vector<string> contents;
	books_manager* b_m{ nullptr };
	void ISBN_input() {
		while (true) {
			cout << blue + "Enter ISBN(International Standard Book Number) formed of 13 numbers: " + reset;
			ISBN.clear();
			getline(cin, ISBN);
			if (ISBN.empty()) {
				cout << red + "\n\nISBN can't be set to be empty\n\n" + reset;
				continue;
			}
			bool non_int{ false };
			for (char x : ISBN) {
				if (!isdigit(static_cast<unsigned char>(x))) {
					non_int = true;
					break;
				}
			}
			if (non_int) {
				cout << red+  "\n\nPlease enter 13 numbers without anything else\n\n" + reset;
				continue;
			}
			if (ISBN.size() != 13) {
				cout << red + "\n\nYou have entered " + to_string(ISBN.size()) + " numbers\n";
				cout << "Please enter 13 numbers without anything else\n\n" + reset;
				continue;
			}
			const vector<book> books = b_m->get_books();
			vector <string> ISBNs;
			for (book x : books) {
				ISBNs.push_back(x.get_ISBN());
			}
			vector <string> ::iterator it = find(ISBNs.begin(), ISBNs.end(),ISBN);
			if (it != ISBNs.end()) {
				cout << red + "\n\nISBN already exists\n\n" + reset;
				continue;
			}
			break;
		}
	}
	bool is_comma(const string& test) const {
		bool is_comma{ test.find(',') != string::npos };
		return is_comma;
	}
	void title_input() {
		while (true) {
			cout << blue + "Enter Title: " + reset;
			title.clear();
			getline(cin, title);
			if (title.empty()) {
				cout << red + "\n\nTitle can't be set to be empty\n\n" + reset;
				continue;
			}
			if (is_comma(title)) {
				cout << red + "\n\nTitle can't contain a comma\n\n" + reset;
				continue;
			}
			break;
		}
	}
	void author_name_input() {
		while (true) {
			cout << blue + "Enter Author Name: " + reset;
			author_name.clear();
			getline(cin, author_name);
			if (author_name.empty()) {
				cout << red + "\n\nAuthor name can't be set to be empty\n\n" + reset;
				continue;
			}
			if (is_comma(author_name)) {
				cout << red + "\n\nAuthor name can't contain a comma\n\n" + reset;
				continue;
			}
			break;
		}
	}
	void nop_input() {
		while (true) {
			cout << blue + "Enter number of pages: " + reset;
			nop.clear();
			getline(cin, nop);
			if (nop.empty()) {
				cout << red + "\n\nNumber of pages can't be set to be empty\n\n" + reset;
				continue;
			}
			int temp;
			istringstream iss_temp(nop);
			iss_temp >> temp;
			if (iss_temp.fail()) {
				cout << red + "\n\nPlease enter number of pages without anything else\n\n" + reset;
				continue;
			}
			if (temp < 0) {
				cout << red + "\n\nPlease enter a positive number for the number of pages\n\n" + reset;
				continue;
			}
			break;
		}
	}
	void content_input() {
		contents.clear();
		int nop_int;
		istringstream iss_temp(nop);
		iss_temp >> nop_int;
		for (int i{ 1 }; i <= nop_int; i++ ) {
			cout << blue + "Enter page # " + to_string(i) + ":" + reset;
			string temp;
			getline(cin, temp);
			if (temp.empty()) {
				cout << red + "\n\nPage can't be empty\n\n" + reset;
				i--;
				continue;
			}
			if (is_comma(temp)) {
				cout << red + "\n\nPage can't contain a comma\n\n" + reset;
				i--;
				continue;
			}
			contents.push_back(temp);
		}
	}
	void print_to_books_file()const {
		ostringstream oss;
		char s{ ',' };
		oss << ISBN + s + title + s + author_name + s + nop;
		for (int i{ 0 }; i < contents.size(); i++) {
			oss << s + contents[i];
		}
		oss << endl;
		ofstream books_file_out("books.txt", ios::out | ios::app);
		if (books_file_out.fail()) {
			cout << red << "Failed to access books file";
			return;
		}
		books_file_out << oss.str();
		cout << endl;
		books_file_out.close();
		return;
	}
	void print_to_books_history_file()const {
		ostringstream oss;
		oss << "," + ISBN + ",0,0";
		ifstream books_history_file_in("books_history.txt");
		vector<string> lines;
		string line;
		while (getline(books_history_file_in, line)) {
			line += oss.str();
			lines.push_back(line);
		}
		books_history_file_in.close();
		ofstream books_history_file_out("books_history.txt", ios::out | ios::trunc);
		if (books_history_file_out.fail()) {
			cout << red << "Failed to access users file";
			return;
		}
		for (string line : lines) {
			books_history_file_out << line << endl;
		}
		cout << endl;
		books_history_file_out.close();
		return;
	}
public:
	add_book(books_manager& b_m) : b_m(&b_m) {};
	void run(const user& u) {
		if (u.get_id() != "0") {
			cout << red << "\n\nACCESS DENIED: You do not have permission to add books.\n\n" << reset;
			return;
		}
		else {
			cout << green << "\n\nAdmin access verified. You can add a new book.\n\n" << reset;
		}
		ISBN_input();
		title_input();
		author_name_input();
		nop_input();
		content_input();
		print_to_books_file();
		print_to_books_history_file();
	}
};

class reading_books {
private:
	books_manager* b_m{ nullptr };
	printing print;
	user* u{ nullptr };

	pair<int,string> searching_for_history(string ISBN) const {
		ifstream books_history_file_in("books_history.txt");
		if (books_history_file_in.fail()) {
			cout << red + "Can't access books_history.txt file";
			return make_pair(0,"");
		}
		string user_name = u->get_username();
		string line;
		while (getline(books_history_file_in, line)) {
			int cnt{ 0 };
			string temp_user_name;
			string history_page;
			string temp_ISBN;
			string time;
			for (char x : line) {
				if (cnt == 1 && temp_user_name!= user_name) {
					break;
				}
				if (cnt > 1 && cnt % 3 == 0) {
					if (temp_ISBN == ISBN) {
						int page_history_ret;
						istringstream iss(history_page);
						iss >> page_history_ret;
						return make_pair(page_history_ret, time);
					}
					else {
						history_page.clear();
						temp_ISBN.clear();
						time.clear();
					}
				}
				if (x == ',') {
					cnt++;
					continue;
				}
				if (cnt == 0) {
					temp_user_name += x;
				}
				else if (cnt > 0 && cnt % 3 == 1) {
					temp_ISBN += x;
				}
				else if (cnt > 0 && cnt % 3 == 2) {
					history_page += x;
				}
				else if (cnt > 0 && cnt % 3 == 0) {
					time += x;
				}
			}
		}

	}

	vector<pair<array<string,2>,int>> get_ISBN_page_time () const {
		vector<pair<array<string, 2>, int>> ret;
		ifstream books_history_file_in("books_history.txt");
		if (books_history_file_in.fail()) {
			cout << red + "Can't access books_history.txt file";
			return {};
		}
		string user_name = u->get_username();
		string line;
		while (getline(books_history_file_in, line)) {
			int cnt{ 0 };
			string temp_user_name;
			string history_page;
			string temp_ISBN;
			string time;
			bool add_check{false};
			bool break_check{ false };
			for (char x : line) {
				if (cnt == 1 && temp_user_name != user_name) {
					break;
				}
				if (x == ',') {
					if (cnt > 1 && cnt % 3 == 0) {
						break_check = true;
						if (history_page != "0" && history_page != "1") {
							int page_history_ret;
							istringstream iss(history_page);
							iss >> page_history_ret;
							ret.push_back(make_pair(array<string, 2>{temp_ISBN, time}, page_history_ret));
							history_page.clear();
							temp_ISBN.clear();
							time.clear();
						}
					}
					cnt++;
					continue;
				}
				if (cnt == 0) {
					temp_user_name += x;
				}
				else if (cnt > 0 && cnt % 3 == 1) {
					temp_ISBN += x;
				}
				else if (cnt > 0 && cnt % 3 == 2) {
					history_page += x;
				}
				else if (cnt > 0 && cnt % 3 == 0) {
					time += x;
				}

			}
			if (history_page != "0" && history_page != "1" && temp_user_name == user_name) {
				int page_history_ret;
				istringstream iss(history_page);
				iss >> page_history_ret;
				ret.push_back(make_pair(array<string, 2>{temp_ISBN, time}, page_history_ret));
				history_page.clear();
				temp_ISBN.clear();
				time.clear();
			}
			if (break_check) {
				break;
			}
		}
		return ret;
	}

	void print_to_books_history(string& ISBN, int& page,string &buffer) const {
		ifstream books_history_file_in("books_history.txt");
		if (books_history_file_in.fail()) {
			cout << red + "Can't access books_history.txt file";
			return;
		}
		vector <string> new_lines;
		string user_name = u->get_username();
		string line;
		while (getline(books_history_file_in, line)) {
			int cnt{ 0 };
			string temp_user_name;
			string history_page;
			string temp_ISBN;
			string time;
			string temp_line;
			bool user_once{ true };

			for (char x : line) {
				if (cnt == 1 && temp_user_name != user_name) {
					temp_line = line;
					break;
				}
				if (cnt == 1 && temp_user_name == user_name && user_once) {
					temp_line += user_name;
					user_once = false;
				}
				if (x == ',') {
					cnt++;
					if (cnt > 1 && cnt % 3 == 1) {
						temp_line += ",";
						if (temp_ISBN == ISBN) {
							temp_line += temp_ISBN + "," + to_string(page) + "," + buffer;
						}
						else {
							temp_line += temp_ISBN + "," + history_page + "," + time;
						}
						temp_ISBN.clear();
						history_page.clear();
						time.clear();
					}
					continue;
				}
				if (cnt == 0) {
					temp_user_name += x;
				}
				else if (cnt > 0 && cnt % 3 == 1) {
					temp_ISBN += x;
				}
				else if (cnt > 0 && cnt % 3 == 2) {
					history_page += x;
				}
				else if (cnt > 0 && cnt % 3 == 0) {
					time += x;
				}
			}
			if (temp_line != line) {
				temp_line += ",";
				if (temp_ISBN == ISBN) {
					temp_line += temp_ISBN + "," + to_string(page) + "," + buffer;
				}
				else {
					temp_line += temp_ISBN + "," + history_page + "," + time;
				}
			}
			new_lines.push_back(temp_line);
		}
		books_history_file_in.close();
		ofstream books_history_file_out("books_history.txt", ios::out | ios::trunc);
		if (books_history_file_out.fail()) {
			cout << red + "Can't access books_history.txt file";
			return;
		}
		for (string x : new_lines) {
			books_history_file_out << x << endl;
		}
	}
	
public:
	reading_books(books_manager & b_m,user &u) : b_m(&b_m),u(&u){}
	void run_available() {
		const vector<book> books = b_m->get_books();
		vector <string> titles;
		if (books.size() == 0) {
			cout << red + "There's no books in the data base" + reset;
			return;
		}
		for (book x : books) {
			titles.push_back(x.get_title());
		}
		int choice = print.menu4(titles);
		vector<string> contents = books[choice].get_content();
		string ISBN = books[choice].get_ISBN();
		pair p = searching_for_history(ISBN);
		int page_history = p.first;
		if (page_history == 0) {
			page_history = 1;
		}
		pair pp = print.menu5(page_history, contents);
		int new_page_history = pp.first;
		string buffer = pp.second;
		print_to_books_history(ISBN,new_page_history,buffer);
	}
	void run_history() {
		vector<pair<array<string, 2>, int>> history_books = get_ISBN_page_time();
		vector<string> ISBNs;
		vector<string> times;
		vector<int> pages_history;
		for (pair<array<string, 2>, int> x : history_books) {
			ISBNs.push_back(x.first[0]);
			times.push_back(x.first[1]);
			pages_history.push_back(x.second);
		}
		vector<book> books = b_m->get_books();
		vector<book> books_history;
		for (book x : books) {
			vector<string> ::iterator it = find(ISBNs.begin(), ISBNs.end(), x.get_ISBN());
			if (it != ISBNs.end()) {
				books_history.push_back(x);
			}
		}
		vector<string> titles;
		vector <vector<string>> contents;
		for (book x : books_history) {
			titles.push_back(x.get_title());
			contents.push_back(x.get_content());
		}
		int choice = print.menu6(titles, pages_history, times, contents);
		pair p = print.menu5(pages_history[choice], contents[choice]);
		int new_page_history = p.first;
		string buffer = p.second;
		print_to_books_history(ISBNs[choice], new_page_history, buffer);
	}
};

vector<array<string, 5>> users_manager::load_data() const {
	ifstream users_file_in("users.txt");
	string line;
	vector<array<string, 5>> users_data;
	while (getline(users_file_in, line)) {
		string user_name, id, password, name, email;
		int cnt{ 0 };
		for (char x : line) {
			if (x == ',') {
				cnt++;
				continue;
			}
			if (cnt == 0) {
				user_name += x;
				continue;
			}
			else if (cnt == 1) {
				id += x;
				continue;
			}
			else if (cnt == 2) {
				password += x;
			}
			else if (cnt == 3) {
				name += x;
			}
			else if (cnt == 4) {
				email += x;
			}
			else {
				break;
			}
		}
		users_data.push_back(user_format(user_name,id,password,name,email));
	}
	return users_data;
}

user::user(users_manager& u_m, admin& admin_u,books_manager &b_m) : u_m(&u_m), admin_u(&admin_u), lsp (make_unique<Authentication>(admin_u, u_m)),b_m(&b_m) {}
void user::print_to_users_books_history_file()const {
	ostringstream oss_u;
	char s{ ',' };
	oss_u << user_name + s + id + s + password + s + name + s + email;
	ostringstream oss_b;
	oss_b << user_name;
	for (book x : this->b_m->get_books()) {
		oss_b << s +  x.get_ISBN() +",0,0" ;
	}
	ofstream users_file_out("users.txt", ios::out | ios::app);
	ofstream books_history_file_out("books_history.txt", ios::out | ios::app);
	if (users_file_out.fail()) {
		cout << red << "Failed to access users file" + reset;
		return;
	}
	if (books_history_file_out.fail()) {
		cout << red << "Failed to access books history file"+reset;
		return;
	}
	oss_u << endl;
	oss_b << endl;
	users_file_out << oss_u.str();
	books_history_file_out << oss_b.str();
	cout << endl;
	users_file_out.close();
	books_history_file_out.close();
	return;
}
pair<bool,bool> user::signup() {
	pair <array<string, 5>, pair<bool, bool>> p = lsp->run(false);
	array<string, 5> user_data = p.first;
	pair<bool, bool> p_check = p.second;
	user_name = user_data[0];
	id = user_data[1];
	password = user_data[2];
	name = user_data[3];
	email = user_data[4];
	print_to_users_books_history_file();
	cout << green + "User Has been added sucessfully\n\n" + reset;
	return p_check;
}
pair<bool, bool> user::login() {
	pair <array<string, 5>, pair<bool, bool>> p = lsp->run(true);
	array<string, 5> user_data = p.first;
	pair<bool, bool> p_check = p.second;
	if (p_check.first) {
		user_name = user_data[0];
		id = user_data[1];
		password = user_data[2];
		name = user_data[3];
		email = user_data[4];
	}
	else {
		cout << red + "\n\nInvalid username or password... Please tryagain\n\n" + reset;
	}

	return p_check;
}

class online_book_reader_system {
private:
	printing print;
	admin admin_u;
	users_manager u_m;
	books_manager b_m;
	user u;
	add_book add_b;
	reading_books b_r;
	void view_profile() {
		cout << yellow + "\n\nName: " + reset + u.get_name();
		cout << yellow + "\n\nEmail: " + reset + u.get_email();
		cout << yellow + "\n\nUser name: " + reset + u.get_username() + "\n\n\n";
	}
public:
	online_book_reader_system() :admin_u("admin", "1234", "Admin Mohamed Admin", "admin@gmail.com"),u_m(),b_m(),add_b(b_m), u(u_m, admin_u,b_m),b_r(b_m,u) {}
	void run() {
		while (true) {
			cout << clear;
			u_m.reload();
			b_m.reload();
			pair <bool, bool> checker = login_or_sign_up();
			bool is_admin = checker.first;
			bool exit = checker.second;
			if (exit) {
				break;
			}
			if (is_admin) {
				admin_interface();
			}
			else {
				user_interface();
			}
		}
	}
	pair <bool, bool> login_or_sign_up(){
		pair <bool, bool> checker;
		bool exit{ false };
		while (true) {
			int choice = print.menu1();
			if (choice == 1) {
				checker = u.run(true);
				if (checker.first) {
					break;
				}
			}
			else if (choice == 2) {
				checker = u.run(false);
				break;
			}
			else {
				exit = true;
				break;
			}
		}
		return make_pair(checker.second,exit);
	}
	void user_interface() {
		while(true){
			cout << yellow + "\n\nHello " + u.get_name() + " | User View" + reset + "\n\n";
			int choice = print.menu2();
			if (choice == 1) {
				view_profile();
			}
			else if (choice == 2) {
				b_r.run_history();
			}
			else if (choice == 3) {
				b_r.run_available();
			}
			else {
				break;
			}
		}
	}

	void admin_interface() {
		while (true) {
			cout << yellow + "\n\nHello " + admin_u.get_name() + " | Admin View" + reset + "\n\n";
			int choice = print.menu3();
			if (choice == 1) {
				view_profile();
			}
			else if (choice == 2) {
				add_b.run(u);
			}

			else {
				break;
			}
		}
	}

};

int main() {
	online_book_reader_system sys;
	sys.run();
}