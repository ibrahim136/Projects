#include <iostream>
#include <fstream> //ifstream & ofstream
#include <vector>
#include <sstream>
#include <conio.h>
#include <random>
#include <array>
#include <tuple>
using namespace std;

class users_manager {
private:
    vector<array<string, 6>> users_data;
    vector<array<string, 6>> load_data() {
        ifstream users_file_in("users.txt");
        vector<array<string, 6>> login_data;
        string line;
        while (getline(users_file_in, line)) {
            int cnt = 0;
            string temp_username, temp_password, temp_name, temp_AQ, temp_email, temp_id;
            for (char x : line) {
                if (x == ',') {
                    cnt++;
                }
                else if (cnt == 0) {
                    temp_id += x;
                }
                else if (cnt == 1) {
                    temp_username += x;
                }
                else if (cnt == 2) {
                    temp_password += x;
                }
                else if (cnt == 3) {
                    temp_name += x;
                }
                else if (cnt == 4) {
                    temp_email += x;
                }
                else if (cnt == 5) {
                    temp_AQ += x;
                }
            }
            array<string, 6> arr{ temp_username, temp_password, temp_name,temp_AQ,temp_id,temp_email };
            login_data.push_back(arr);
        }
        users_file_in.close();
        return login_data;
    }
public:
    users_manager() {
        users_data = load_data();
    }
    void reload() {
        users_data = load_data();
    }
    vector<array<string, 6>> get_users_data() {
        return users_data;
    }

};

class user {
private:
    string name;
    string user_name;
    int id;
    string password;
    bool AQ;
    string email;
    users_manager u_m;
public:
    bool get_AQ()const {
        if (AQ) {
            return true;
        }
        else {
            return false;
        }
    }
    string get_username() const {
        return user_name;
    }
    string get_name() const {
        return name;
    }
    int get_id() const {
        return id;
    }
    string get_email() const {
        return email;
    }
    user() {
        id = 0;
        AQ = true;
    }
    bool run() {
        bool login_check = false;
        while (1) {

            array<string, 2> login_data = menu_login();
            u_m.reload();
            vector<array<string, 6>> users_data = u_m.get_users_data();

            for (array<string, 6> x : users_data) {
                if (x[0] == login_data[0] && x[1] == login_data[1]) {
                    user_name = x[0];
                    password = x[1];
                    name = x[2];
                    if (x[3] == "1") {
                        AQ = true;
                    }
                    else if (x[3] == "0") {
                        AQ = false;
                    }
                    istringstream iss(x[4]);
                    iss >> id;
                    email = x[5];
                    cout << "\033[32m\nLogin has been sucessfully\n\n\033[0m";
                    login_check = true;
                    break;
                }
            }
            if (!login_check) {
                cout << "\033[31m\nInvalid username or password\n\n\033[0m";
            }
            break;
        }
        return login_check;
    }
    array<string, 2> menu_login() {
        string login_username;
        string login_password;
        bool ignore = true;
        while (1) {
            cout << "Enter user name. (No spaces): ";

            getline(cin, login_username);
            bool is_space = false;
            for (char x : login_username) {
                if (x == ' ') {
                    is_space = true;
                    break;
                }
            }
            if (is_space) {
                cout << "\033[31m\nuser name contains a space(s)\n\n\033[0m";
                continue;
            }
            break;
        }
        cout << "Enter password: ";
        char ch;
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!login_password.empty()) {
                    cout << "\b \b";
                    login_password.pop_back();
                }
            }
            else {
                login_password += ch;
                cout << "*";
            }
        }
        cout << endl;
        return array<string, 2> {login_username, login_password};

    }


};

//Forward Declaration
class printing;
class question;
class questions_manager;

class question {
private:
    questions_manager* q_m;
    vector <array<string, 7>> questions_data;
    printing* print;
public:
    question();
    ~question() {
        delete q_m;
    }
    void answer(user& u);
    bool search_for_question(user& u, string id_q_s);
    void delete_answer(user& u);
    bool check_answered(string id_q_s);
    void delete_question(user& u);
};

class questions_manager {
private:
    vector<array<string, 7>> questions_data;
    vector<array<string, 7>> load_data() {
        ifstream questions_file_in("questions.txt");
        vector<array<string, 7>> questions_data;
        string line;
        while (getline(questions_file_in, line)) {
            int cnt = 0;
            string temp_id_q, temp_id_to, temp_id_from, thread, temp_AQ, temp_question, temp_answer;
            for (char x : line) {
                if (x == ',') {
                    cnt++;
                }
                else if (cnt == 0) {
                    temp_id_q += x;
                }
                else if (cnt == 1) {
                    temp_id_to += x;
                }
                else if (cnt == 2) {
                    temp_id_from += x;
                }
                else if (cnt == 3) {
                    thread += x;
                }
                else if (cnt == 4) {
                    temp_AQ += x;
                }
                else if (cnt == 5) {
                    temp_question += x;
                }
                else if (cnt == 6) {
                    temp_answer += x;
                }
            }
            array<string, 7> arr{ temp_id_q, temp_id_to, temp_id_from,thread, temp_AQ, temp_question, temp_answer };
            questions_data.push_back(arr);
        }
        questions_file_in.close();
        return questions_data;
    }
    void write_to_questions_file(vector<array<string, 7>> questions_data) {
        ofstream questions_file_out("questions.txt", ios::out | ios::trunc);
        char s{ ',' };
        for (array<string, 7> x : questions_data) {
            ostringstream oss;
            questions_file_out << x[0] + s + x[1] + s + x[2] + s + x[3] + s + x[4] + s + x[5] + s + x[6] << endl;
        }
        questions_file_out.close();
    }
    void delete_question(string id_q_s) {
        ofstream questions_file_out("questions.txt", ios::out | ios::trunc);
        char s{ ',' };
        for (array<string, 7> x : questions_data) {
            if (x[0] != id_q_s && x[3] != id_q_s) {
                ostringstream oss;
                questions_file_out << x[0] + s + x[1] + s + x[2] + s + x[3] + s + x[4] + s + x[5] + s + x[6] << endl;
            }
        }
        questions_file_out.close();
    }
public:
    questions_manager() {
        questions_data = load_data();
    }
    void reload() {
        questions_data = load_data();
    }
    vector<array<string, 7>> get_questions_data() {
        return questions_data;
    }
    void answer_question(string& id_q_s, string answer) {
        for (array<string, 7> &x : questions_data) {
            if (x[0] == id_q_s) {
                x[6] = answer;
                break;
            }
        }
        write_to_questions_file(questions_data);

    }
    friend void question::delete_question(user& u);
    friend void question::answer(user& u);
    friend void question::delete_answer(user& u);
};

class printing {
private:
    questions_manager q_m;
    vector<array<string, 7>> questions_data;
public:
    printing() {
        questions_data = q_m.get_questions_data();
    }
    int menu1() {
        int choice;
        while (1) {
            cout << "\033[33mMenu:\n\033[0m";
            cout << "       1: Login\n";
            cout << "       2: Signup\n";
            cout << "       3: Exit\n";
            cout << "\033[36m\n\nEnter number in range 1 - 2: \033[0m";
            string choicee;
            getline(cin, choicee);
            if (choicee.empty()) {
                cout << "\033[31m\nPlease enter a number\n\n\033[0m";
                continue;
            }
            double choiicee;
            istringstream iss(choicee);
            istringstream isss(choicee);
            iss >> choice;
            isss >> choiicee;
            if (choice > 3 || choice < 0 || iss.fail() || choice != choiicee) {
                iss.clear();
                iss.ignore(256, '\n');
                cout << "\033[31m\nInvalid Choice Number.\n\n\033[0m";
                continue;
            }
            //cin.ignore(256, '\n');
            break;
        }
        cout << "\n\n";
        return choice;
    }
    int menu2() {
        int choice;
        while (1) {
            cout << "\033[33mMenu:\n\033[0m";
            cout << "       1: Print Questions To Me\n";
            cout << "       2: Print Questions From Me\n";
            cout << "       3: Answer Question\n";
            cout << "       4: Delete Question\n";
            cout << "       5: Delete Answer\n";
            cout << "       6: Ask Question\n";
            cout << "       7: List System Users\n";
            cout << "       8: Feed\n";
            cout << "       9: Logout\n";

            cout << "\033[36m\n\nEnter number in range 1 - 8: \033[0m";
            string choicee;
            getline(cin, choicee);
            if (choicee.empty()) {
                cout << "\033[31m\nPlease enter a number\n\n\033[0m";
                continue;
            }
            double choiicee;
            istringstream iss(choicee);
            istringstream isss(choicee);
            iss >> choice;
            isss >> choiicee;

            if (choice > 9 || choice < 0 || iss.fail() || choice != choiicee) {
                cout << "\033[31m\nInvalid Choice Number.\n\n\033[0m";
                iss.clear();
                iss.ignore(256, '\n');
                continue;
            }
            //cin.ignore(256, '\n');
            break;
        }
        cout << "\n\n";
        return choice;
    }
    void print_questions_from_me(user& u) {
        q_m.reload();
        questions_data = q_m.get_questions_data();
        for (array<string, 7> x : questions_data) {
            bool thread_without_parent = true;
            if (x[2] == to_string(u.get_id()) && x[3] == "0") {
                ostringstream oss;
                oss << "Question Id (" + x[0] + ") ";
                if (x[4] == "1") {
                    oss << "AQ ";
                }
                else {
                    oss << "not AQ ";
                }
                oss << " to user id (" + x[1] + ")\n";
                oss << "Question: " << x[5] << endl;
                if (x[6].empty()) {
                    oss << "NOT Answered YET\n\n";
                }
                else {
                    oss << "Answer: " << x[6] << "\n\n";
                }
                for (array<string, 7> xx : questions_data) {
                    if (xx[3] == x[0]) {
                        oss << "        Thread:        Question Id (" + xx[0] + ") ";
                        if (xx[4] == "1") {
                            oss << "AQ ";
                        }
                        else {
                            oss << "not AQ ";
                        }
                        oss << "to user id(" + xx[1] + ")\n        Thread:        Question: " + xx[5] + "\n";
                        if (xx[6].empty()) {
                            oss << "        Thread:        NOT Answered YET\n\n";
                        }
                        else {
                            oss << "        Thread:        Answer: " << xx[6] << "\n\n";
                        }
                    }
                }
                cout << oss.str();
            }
            else if (x[2] == to_string(u.get_id())) {
                ostringstream oss;
                for (array<string, 7> xx : questions_data) {
                    if (x[3] == xx[0] && xx[2] == to_string(u.get_id())) {
                        thread_without_parent = false;
                        break;
                    }
                }
                if (thread_without_parent) {
                    oss << "\nParent Question ID (" + x[3] + ")\n";
                    oss << "Thread:        Question Id (" + x[0] + ") ";
                    if (x[4] == "1") {
                        oss << "AQ ";
                    }
                    else {
                        oss << "not AQ ";
                    }
                    oss << "to user id(" + x[1] + ")\n        Thread:        Question: " + x[5] + "\n";
                    if (x[6].empty()) {
                        oss << "        Thread:        NOT Answered YET\n\n";
                    }
                    else {
                        oss << "        Thread:        Answer: " << x[6] << "\n\n";
                    }
                }
                cout << oss.str();
            }

        }
    }
    void print_questions_to_me(user& u) {
        q_m.reload();
        questions_data = q_m.get_questions_data();
        for (array<string, 7> x : questions_data) {
            if (x[1] == to_string(u.get_id()) && x[3] == "0") {
                ostringstream oss;
                oss << "Question Id (" + x[0] + ") ";
                if (x[4] == "1") {
                    oss << "AQ \n";
                }
                else {
                    oss << " from user id (" + x[2] + ")\n";
                }

                oss << "Question: " << x[5] << endl;
                if (x[6].empty()) {
                    oss << "NOT Answered YET\n\n";
                }
                else {
                    oss << "Answer: " << x[6] << "\n\n";
                }
                for (array<string, 7> xx : questions_data) {
                    if (xx[3] == x[0]) {
                        oss << "        Thread:        Question Id (" + xx[0] + ") ";
                        if (xx[4] == "1") {
                            oss << "AQ \n";
                        }
                        else {
                            oss << " from user id (" + x[2] + ")\n";
                        }
                        oss << "        Thread:        Question: " + xx[5] + "\n";
                        if (xx[6].empty()) {
                            oss << "        Thread:        NOT Answered YET\n\n";
                        }
                        else {
                            oss << "        Thread:        Answer: " << xx[6] << "\n\n";
                        }
                    }
                }
                cout << oss.str();
            }
        }
    }
    bool print_question(string& id_q_s) {
        q_m.reload();
        questions_data = q_m.get_questions_data();
        bool answered = false;
        for (array<string, 7> x : questions_data) {
            if (x[0] == id_q_s) {
                if (x[3] == "0") {
                    ostringstream oss;
                    oss << "Question Id (" + x[0] + ") ";
                    if (x[4] == "1") {
                        oss << "AQ \n";
                    }
                    else {
                        oss << " from user id (" + x[2] + ")\n";
                    }

                    oss << "Question: " << x[5] << endl;
                    if (x[6].empty()) {
                        oss << "NOT Answered YET\n\n";
                    }
                    else {
                        answered = true;
                        oss << "Answer: " << x[6] << "\n\n";
                    }
                    cout << oss.str();
                    break;
                }
                else {
                    ostringstream oss;
                    oss << "        Thread:        Question Id (" + x[0] + ") ";
                    if (x[4] == "1") {
                        oss << "AQ \n";
                    }
                    else {
                        oss << " from user id (" + x[2] + ")\n";
                    }
                    oss << "        Thread:        Question: " + x[5] + "\n";
                    if (x[6].empty()) {
                        oss << "        Thread:        NOT Answered YET\n\n";
                    }
                    else {
                        answered = true;
                        oss << "        Thread:        Answer: " << x[6] << "\n\n";
                    }
                    cout << oss.str();
                    break;
                }
            }
        }
        return answered;
    }
    void print_all_questions() {
        q_m.reload();
        questions_data = q_m.get_questions_data();
        for (array<string, 7> x : questions_data) {
            ostringstream oss;
            if (x[3] == "0") {
                oss << "Question Id (" + x[0] + ") ";
                if (x[4] == "1") {
                    oss << "AQ ";
                }
                else {
                    oss << " from user id (" + x[2] + ") ";
                }
                oss << "to user id (" + x[1] + ")\n";
                oss << "Question: " + x[5] << endl;
                if (x[6].empty()) {
                    oss << "NOT Answered YET";
                }
                else {
                    oss << "Answer: " + x[6];
                }
            }
            else {
                oss << "Parent Question ID (" + x[3] + ")\n";
                oss << "Thread Question Id (" + x[0] + ") ";
                if (x[4] == "1") {
                    oss << "AQ ";
                }
                else {
                    oss << " from user id (" + x[2] + ") ";
                }
                oss << "to user id (" + x[1] + ")\n";
                oss << "Question: " + x[5] << endl;
                if (x[6].empty()) {
                    oss << "NOT Answered YET";
                }
                else {
                    oss << "Answer: " + x[6];
                }
            }
            cout << oss.str() << "\n\n";
        }
    }
};


question::question() {
    q_m = new questions_manager();
    print = new printing();
    questions_data = q_m->get_questions_data();
}
void question::answer(user& u) {
    q_m->reload();
    questions_data = q_m->get_questions_data();
    cout << "Enter Question id or -1 to cancel: ";
    string id_q_s;
    getline(cin, id_q_s);
    int id_q_i;
    istringstream iss(id_q_s);
    iss >> id_q_i;
    if (id_q_s.empty() || iss.fail()) {
        cout << "\033[31m\nInvalid Input.\n\n\033[0m";
        answer(u);
        return;
    }
    if (id_q_s == "-1") {
        return;
    }
    if (search_for_question(u, id_q_s)) {
        cout << "\n\033[32mQuestion has been found\n\n\033[0m";
    }
    else {
        cout << "\n\033[31mQuestion has not been found\n\n\033[0m";
        answer(u);
        return;
    }
    if (print->print_question(id_q_s)) {
        cout << "\n\033[31mWarning: Already answered. Answer will be updated\n\n\033[0m";
    }
    string answer;
    while (true) {
        cout << "Enter answer or -1 to cancel: ";
        getline(cin, answer);
        if (answer == "-1") {
            return;
        }
        if (answer.empty()) {
            cout << "\n\033[31mAnswer can't be set to be empty\n\n\033[0m";
            continue;
        }
        bool is_comma = false;
        for (char x : answer) {
            if (x == ',') {
                cout << "\n\033[31mAnswer can't contain a comma \",\"\n\n\033[0m";
                is_comma = true;
                break;
            }
        }
        if (is_comma) {
            continue;
        }
        break;
    }
    q_m->answer_question(id_q_s, answer);
}
bool question::search_for_question(user& u, string id_q_s) {
    bool ret = false;
    q_m->reload();
    questions_data = q_m->get_questions_data();
    for (array<string, 7> x : questions_data) {
        if (x[0] == id_q_s && x[1] == to_string(u.get_id())) {
            ret = true;
            break;
        }
    }
    return ret;
}
void question::delete_answer(user& u) {
    cout << "Enter Question id or -1 to cancel: ";
    string id_q_s;
    getline(cin, id_q_s);
    int id_q_i;
    istringstream iss(id_q_s);
    iss >> id_q_i;
    if (id_q_s.empty() || iss.fail()) {
        cout << "\033[31m\nInvalid Input.\n\n\033[0m";
        delete_answer(u);
        return;
    }
    if (id_q_s == "-1") {
        return;
    }
    if (search_for_question(u, id_q_s)) {
        cout << "\n\033[32mQuestion has been found\n\n\033[0m";
    }
    else {
        cout << "\n\033[31mQuestion has not been found\n\n\033[0m";
        delete_answer(u);
        return;
    }
    if (!check_answered(id_q_s)) {
        cout << "\n\033[31mAnswer is not already answered yet\n\n\033[0m";
        return;
    }
    else {
        cout << "\n\033[32mAnswer is deleted\n\n\033[0m";
        q_m->answer_question(id_q_s, "");
    }

}
bool question::check_answered(string id_q_s) {
    bool ret = false;
    for (array<string, 7> x : questions_data) {
        if (x[0] == id_q_s) {
            if (!x[6].empty()) {
                ret = true;
            }
            break;
        }
    }
    return ret;
}
void question::delete_question(user& u) {
    q_m->reload();
    questions_data = q_m->get_questions_data();
    cout << "Enter Question id or -1 to cancel: ";
    string id_q_s;
    getline(cin, id_q_s);
    if (id_q_s.empty()) {
        cout << "\033[31m\nEmpty input.\n\n\033[0m";
        delete_question(u);
        return;
    }
    if (id_q_s == "-1") {
        return;
    }
    if (search_for_question(u, id_q_s)) {
        cout << "\n\033[32mQuestion has been found\n\n\033[0m";
    }
    else {
        cout << "\n\033[31mQuestion has not been found\n\n\033[0m";
        answer(u);
        return;
    }
    q_m->delete_question(id_q_s);
    cout << "\n\033[32mQuestion has been deleted\n\n\033[0m";

}

class create_new_user {
private:
    string name;
    string user_name;
    int id;
    string email;
    string password;
    bool AQ;
    users_manager u_m;
    vector <string> usernames;
    void print_to_users_file() const {
        ostringstream oss;
        string s{ ',' };
        oss << to_string(id) + s + user_name + s + password + s + name + s + email + s << AQ << endl;
        ofstream users_file_out("users.txt", ios::out | ios::app);
        users_file_out << oss.str();
        cout << endl;
        users_file_out.close();
    }
public:
    create_new_user() {
        id = 0;
        AQ = true;
    }
    void create_user() {
        u_m.reload();
        ask_user_name();
        ask_password();
        ask_name();
        ask_email();
        ask_AQ();
        id = random_id();
        print_to_users_file();
    }
    void ask_user_name() {

        usernames.clear();
        for (array<string, 6> x : u_m.get_users_data()) {
            usernames.push_back(x[0]);
        }
        while (1) {
            cout << "Enter user name. (No spaces): ";
            getline(cin, user_name);
            bool is_space = false;
            bool is_coma = false;
            bool exists = false;
            for (char x : user_name) {
                if (x == ' ') {
                    is_space = true;
                    break;
                }
                if (x == ',') {
                    is_coma = true;
                }
            }
            vector <string> ::iterator it = find(usernames.begin(), usernames.end(), user_name);
            if (it != usernames.end()) {
                cout << "\033[31m\nUser name already exists\n\n\033[0m";
                continue;
            }
            if (is_space) {
                cout << "\033[31m\nUser name contains a space(s)\n\n\033[0m";
                continue;
            }
            if (is_coma) {
                cout << "\033[31m\nUser name can't contain a coma \",\"\n\n\033[0m";
                continue;
            }
            if (user_name.empty()) {
                cout << "\033[31m\nYou can't set an empty username\n\n\033[0m";
                continue;
            }
            break;
        }

    }
    void ask_password() {

        while (1) {
            password = "";
            cout << "Enter password: ";
            char ch;
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
            bool is_coma = false;
            for (char x : password) {
                if (x == ',') {
                    is_coma = true;
                }
            }
            if (is_coma) {
                cout << "\033[31m\nYou can't set a password contains a coma \",\"\n\n\033[0m";
                continue;
            }
            if (password.empty()) {
                cout << "\033[31m\nYou can't set an empty password\n\n\033[0m";
            }
            else
                break;
        }
    }
    void ask_name() {
        while (1) {
            cout << "Enter name: ";
            getline(cin, name);
            bool is_coma = false;
            for (char x : name) {
                if (x == ',') {
                    is_coma = true;
                }
            }
            if (is_coma) {
                cout << "\033[31m\nYou can't set a name contains a coma \",\"\n\n\033[0m";
                continue;
            }
            if (name.empty()) {
                cout << "\033[31m\nYou can't set an empty name\n\n\033[0m";

            }
            else {
                break;
            }
        }
    }
    void ask_email() {
        while (1) {
            cout << "Enter email. (No spaces): ";
            getline(cin, email);
            bool is_space = false;
            bool is_coma = false;
            for (char x : email) {
                if (x == ' ') {
                    is_space = true;
                    break;
                }
            }
            for (char x : email) {
                if (x == ',') {
                    is_coma = true;
                }
            }
            if (is_coma) {
                cout << "\033[31m\nYou can't set an email contains a coma \",\"\n\n\033[0m";
                continue;
            }
            if (email.empty()) {
                cout << "\033[31m\nYou can't set an empty email\n\n\033[0m";
                continue;
            }
            if (is_space) {
                cout << "\033[31m\nEmail contains a space(s)\n\n\033[0m";
                continue;
            }

            else {
                break;
            }
        }
    }
    void ask_AQ() {
        string AQ_s;
        while (true) {
            cout << "Allow anonymous questions? (yes or no): ";
            getline(cin, AQ_s);
            if (AQ_s == "yes" || AQ_s == "Yes") {
                AQ = true;
            }
            else if (AQ_s == "no" || AQ_s == "No") {
                AQ = false;
            }
            else {
                cout << "\033[31m\nInvalid input\n\n\033[0m";
                continue;
            }
            break;
        }
    }
    int random_id() {

        vector<int> ids;
        for (array<string, 6> x : u_m.get_users_data()) {
            istringstream iss(x[4]);
            int id;
            iss >> id;
            ids.push_back(id);
        }
        int idd;
        while (true) {
            random_device rd; // generating random id
            mt19937 gen(rd());
            uniform_int_distribution<>distrib(1, 999);
            idd = distrib(gen);
            vector<int>::iterator it = find(ids.begin(), ids.end(), idd);
            if (it == ids.end()) {
                break;
            }
        }
        return idd;
    }
};

class create_new_question {
private:
    int id_q{ 0 }, id_to{ 0 }, id_from{ 0 }, thread{ 0 };
    string Question{ "" }, Answer{ "" };
    bool AQ_u{ false }, AQ_q{ false };
    users_manager u_m;
    questions_manager q_m;
    user u;
    vector<array<string, 6>> users_data = u_m.get_users_data();
    vector<array<string, 7>> questions_data = q_m.get_questions_data();

public:
    create_new_question() {}
    void run(user const& uu) {
        u = uu;
        id_from = u.get_id();
        int choice = menu1();
        if (choice == 5) {
            return;
        }
        int indexx = index(choice);
        string user_to_info = print_enter(indexx);
        if (check_myself(u, user_to_info, indexx)) {
            run(u);
            return;
        }
        if (search_for_user(user_to_info, indexx)) {
            run(u);
            return;
        }
        id_q = random_id();
        if (!question()) {
            return;
        }
        print_to_questions_file();
    }
    int menu1() {
        int choice;
        while (true) {
            cout << "Send to user by: \n";
            cout << "        1: Username\n";
            cout << "        2: Name\n";
            cout << "        3: User ID\n";
            cout << "        4: Email\n";
            cout << "        5: cancel\n";
            cout << "\033[36m\n\nEnter number in range 1 - 4: \033[0m";
            string choicee;
            getline(cin, choicee);
            if (choicee.empty()) {
                cout << "\033[31m\nPlease enter a number\n\n\033[0m";
                continue;
            }
            double choiicee;
            istringstream iss(choicee);
            istringstream isss(choicee);
            iss >> choice;
            isss >> choiicee;
            if (choice > 5 || choice < 0 || iss.fail() || choice != choiicee) {
                iss.clear();
                iss.ignore(256, '\n');
                cout << "\033[31m\nInvalid Choice Number.\n\n\033[0m";
                continue;
            }

            break;
        }
        cout << "\n\n";
        return choice;
    }
    int index(int const& choice) {
        if (choice == 1) {
            return 0;
        }
        else if (choice == 2) {
            return 2;
        }
        else if (choice == 3) {
            return 4;
        }
        else {
            return 5;
        }
    }
    string print_enter(int& indexx) {
        string temp;
        while (true) {
            if (indexx == 0) {
                cout << "Enter username of the user that you want to send to: ";
            }
            else if (indexx == 2) {
                cout << "Enter name of the user that you want to send to: ";
            }
            else if (indexx == 4) {
                cout << "Enter id of the user that you want to send to: ";
            }
            else if (indexx == 5) {
                cout << "Enter email of the user that you want to send to: ";
            }


            getline(cin, temp);
            if (temp.empty()) {
                cout << "\033[31m\nYou can't send to an empty user\n\n\033[0m";
                continue;
            }
            bool is_space = false, is_coma = false;
            if (indexx == 0) {
                for (char x : temp) {
                    if (x == ' ') {
                        is_space = true;
                    }
                    if (x == ',') {
                        is_coma = true;
                    }
                }
            }
            if (is_space) {
                cout << "\033[31m\nUser name contains a space(s)\n\n\033[0m";
                continue;
            }
            if (is_coma) {
                cout << "\033[31m\nUser name contains a coma \",\"\n\n\033[0m";
                continue;
            }
            break;
        }
        return temp;
    }
    bool check_myself(user& u, string& user_to_info, int& indexx) {
        bool check = false;
        if (indexx == 0 && (u.get_username() == user_to_info)) {
            cout << "\033[31m\nYou can't send to yourself\n\n\033[0m";
            check = true;
        }
        else if (indexx == 2 && (u.get_name() == user_to_info)) {
            cout << "\033[31m\nYou can't send to yourself\n\n\033[0m";
            check = true;
        }
        else if (indexx == 4 && (to_string(u.get_id()) == user_to_info)) {
            cout << "\033[31m\nYou can't send to yourself\n\n\033[0m";
            check = true;
        }
        else if (indexx == 5 && (u.get_email() == user_to_info)) {
            cout << "\033[31m\nYou can't send to yourself\n\n\033[0m";
            check = true;
        }
        return check;
    }
    bool search_for_user(string user_to_info, int indexx) {
        for (array<string, 6> x : users_data) {
            if (x[indexx] == user_to_info) {
                cout << "\033[32m\nUser has been found\n\n\033[0m";
                istringstream iss(x[4]);
                iss >> id_to;
                if (x[3] == "0") {
                    AQ_u = false;
                }
                else {
                    AQ_u = true;
                }
                return false;
            }
        }
        cout << "\033[31m\nUser not found\n\n\033[0m";
        return true;
    }
    int random_id() {

        vector<int> id_q_s;
        for (array<string, 7> x : questions_data) {
            istringstream iss(x[0]);
            int id;
            iss >> id;
            id_q_s.push_back(id);
        }
        int idd;
        while (true) {
            random_device rd; // generating random id
            mt19937 gen(rd());
            uniform_int_distribution<>distrib(1, 999);
            idd = distrib(gen);
            vector<int>::iterator it = find(id_q_s.begin(), id_q_s.end(), idd);
            if (it == id_q_s.end()) {
                break;
            }
        }
        return idd;
    }
    bool question() {

        cout << "\033[36mNote: Anonymous questions are";
        if (!AQ_u) {
            cout << "\033[31m not";
            AQ_q = AQ_u;
        }
        cout << "\033[36m allowed for this user\n\n\033[0m";
        string AQ_s;
        if (AQ_u) {
            while (true) {
                cout << "Ask anonymous questions? (yes or no): ";
                getline(cin, AQ_s);
                if (AQ_s == "yes" || AQ_s == "Yes") {
                    AQ_q = true;
                }
                else if (AQ_s == "no" || AQ_s == "No") {
                    AQ_q = false;
                }
                else {
                    cout << "\033[31m\nInvalid input\n\n\033[0m";
                    continue;
                }
                break;
            }
        }
        while (true) {
            cout << "For thread question: Enter Question id or -1 for new question or -2 to cancel: ";
            string temp;
            getline(cin, temp);
            if (temp.empty()) {
                cout << "\033[31m\nEmpty input, Tryagain...\n\n\033[0m";
                continue;
            }
            if (temp == "-1") {
                thread = 0;
                break;
            }
            if (temp == "-2") {
                return false;
            }
            else {
                int temp_intt;
                istringstream iiss(temp);
                iiss >> temp_intt;
                if (temp_intt < 1 || temp_intt > 999) {
                    cout << "\033[31m\nInvalid Question id (Question id in range of: 1-999)\n\n\033[0m";
                    continue;
                }
                else if (iiss.fail()) {
                    cout << "\033[31m\nInvalid Question id input\n\n\033[0m";
                    continue;
                }
                else {
                    istringstream isss(temp);
                    isss >> thread;

                    if (get<0>(search_question(temp_intt))) {
                        if (get<2>(search_question(temp_intt))) {
                            if (get<1>(search_question(temp_intt))) {
                                break;
                            }
                            else {
                                cout << "\033[31m\nQuestion is already a thread question\n\n\033[0m";
                                continue;
                            }
                        }
                        else {
                            cout << "\033[31m\nQuestion id is not in the user's database.\n\n\033[0m";
                            continue;
                        }
                    }
                    else {
                        cout << "\033[31m\nQuestion id is not found\n\n\033[0m";
                        continue;
                    }
                }
            }
            return true;
        }
        while (true) {
            cout << "Enter question text: ";
            string temp_question;
            getline(cin, temp_question);
            if (temp_question.empty()) {
                cout << "\033[31m\nQuestion can't set to be empty\n\n\033[0m";
                continue;
            }
            bool is_coma = false;
            for (char x : temp_question) {
                if (x == ',') {
                    is_coma = true;
                }
            }
            if (is_coma) {
                cout << "\033[31m\nQuestion can't contain a coma \",\"\n\n\033[0m";
                continue;
            }
            Question = temp_question;
            break;
        }
    }
    tuple<bool, bool, bool> search_question(int& id_q_temp) {
        vector<pair <int, int>> id_q_s2;
        for (array<string, 7> x : questions_data) {
            istringstream iss(x[0]);
            int id;
            iss >> id;
            int thread;
            istringstream isss(x[3]);
            isss >> thread;
            id_q_s2.push_back(make_pair(id, thread));
        }
        vector <int> id_q_s1;
        for (array<string, 7> x : questions_data) {
            istringstream iss(x[0]);
            int id;
            iss >> id;
            id_q_s1.push_back(id);
        }
        vector<pair <int, int>> id_q_s3;
        for (array<string, 7> x : questions_data) {
            istringstream iss(x[0]);
            int id;
            iss >> id;
            int user_to_idd;
            istringstream isss(x[1]);
            isss >> user_to_idd;
            id_q_s3.push_back(make_pair(id, user_to_idd));
        }
        pair <int, int> p = make_pair(id_q_temp, 0);
        vector <int> ::iterator it1 = find(id_q_s1.begin(), id_q_s1.end(), id_q_temp);
        vector <pair <int, int>> ::iterator it2 = find(id_q_s2.begin(), id_q_s2.end(), p);
        p = make_pair(id_q_temp, id_to);
        vector <pair <int, int>> ::iterator it3 = find(id_q_s3.begin(), id_q_s3.end(), p);
        tuple <bool, bool, bool> ret = make_tuple(true, true, true);
        if (it2 == id_q_s2.end()) {
            get<1>(ret) = false;
        }
        if (it1 == id_q_s1.end()) {
            get<0>(ret) = false;
        }
        if (it3 == id_q_s3.end()) {
            get<2>(ret) = false;
        }
        return ret;
    }
    void print_to_questions_file() const {
        ostringstream oss;
        string s{ ',' };
        oss << to_string(id_q) + s + to_string(id_to) + s + to_string(id_from) + s +
            to_string(thread) + s << AQ_q << s + Question + s + Answer << endl;
        ofstream questions_file_out("questions.txt", ios::out | ios::app);
        questions_file_out << oss.str();
        cout << endl;
        questions_file_out.close();
    }
};

class user_interface {
private:
    users_manager u_m;
    user u;
    vector<array<string, 6>> users_data = u_m.get_users_data();
    printing print;
    question q;
public:
    user_interface() {}
    bool run(int const& choice) {

        if (choice == 1) {
            print.print_questions_to_me(u);
            return false;
        }
        else if (choice == 2) {
            print.print_questions_from_me(u);
            return false;
        }
        else if (choice == 3) {
            q.answer(u);
            return false;
        }
        else if (choice == 4) {
            q.delete_question(u);
            return false;
        }
        else if (choice == 5) {
            q.delete_answer(u);
            return false;
        }
        else if (choice == 6) {
            create_new_question q_new;
            q_new.run(u);
            return false;
        }
        else if (choice == 7) {
            cout << "\n\n";
            u_m.reload();
            for (array<string, 6> x : users_data) {
                cout << "ID: " << x[4] << "\nName: " << x[2] <<
                    "\nUser name: " << x[0] << "\nEmail: " << x[5] << "\n\n\n";
            }
            return false;
        }
        else if (choice == 8) {
            print.print_all_questions();
            return false;
        }
        else {
            return true;
        }

    }
    void user(user const& u) {
        this->u = u;
    }
};

class system_ask_fm {
private:
    printing print;
    create_new_user new_u;
    user u;
    user_interface u_i;
public:
    system_ask_fm() {
    }
    void run() {
        bool exit = login_or_sign_up();
        if (exit) {
            return;
        }
        user_interface();
        run();
    }
    bool login_or_sign_up() {
        int choice1 = print.menu1();
        if (choice1 == 2) {
            new_u.create_user();
            login_or_sign_up();
            return false;
        }
        else if (choice1 == 1) {
            if (!u.run()) {
                login_or_sign_up();
            }
            return false;
        }
        else if (choice1 == 3) {
            return true;
        }
    }
    void user_interface() {
        u_i.user(u);
        int choice2 = print.menu2();
        bool end = u_i.run(choice2);
        cout << "\n\n";
        if (end == true) {
            return;
        }
        user_interface();
    }
};

int main() {
    system_ask_fm s;
    s.run();
    return 0;
}
