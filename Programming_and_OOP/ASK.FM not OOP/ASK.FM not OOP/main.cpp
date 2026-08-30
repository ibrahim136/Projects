#include <iostream> // cin & cout
#include <algorithm> // sort
#include <string> // getline
#include <queue> //FIFO
#include <stack> //FILO
#include <tuple> // tuple
#include <set> // set
#include <unordered_set> // unordered set
#include <map>
#include <unordered_map>
#include <numeric> //accumulate
#include <fstream> //ifstream ofstream
#include <sstream> //istringstream
#include <random>
#include <filesystem>
using namespace std;
//namespace fs = filesystem;


string menu2() {
    cout << "Menu\n";
    cout << "       1: Print Questions To Me\n";
    cout << "       2: Print Questions From Me\n";
    cout << "       3: Answer Question\n";
    cout << "       4: Delete Question\n";
    cout << "       5: Ask Question\n";
    cout << "       6: List System Users\n";
    cout << "       7: Feed\n";
    cout << "       8: Logout\n";
    cout << "       9: Delete Answer\n";
    cout << "Enter number in range 1 - 8: ";
    string choice2;
    cin >> choice2;
    return choice2;
}

string menu1() {
    cout << "Menu:\n";
    cout << "       1: Login\n";
    cout << "       2: Sign Up\n\n";
    cout << "Enter number in range 1 - 2: ";
    string choice1;
    cin >> choice1;
    return choice1;
}
void signup() {
    cout << "Enter user name. (No spaces): ";
    string username;
    cin >> username;
    ifstream test_username(username.c_str());
    if (test_username.is_open()) {
        cout << "\nusername is already taken\n\n";
        test_username.close();
        return;
    }
    test_username.close();
    cout << "Enter password: ";
    string password;
    cin >> password;
    cout << "Enter name: ";
    string name;
    cin.ignore();
    getline(cin, name);
    cout << "Enter email: ";
    string email;
    cin >> email;
    cout << "Enter ID: ";
    random_device rd; // generating random id
    mt19937 gen(rd());
    uniform_int_distribution<>distrib(1, 999);
    int randomId = distrib(gen);
    string id = to_string(randomId);
    ifstream yy("system"); // checking id if it's repeated or not
    string temp_id;
    while (yy >> temp_id) {
        yy >> temp_id;
        if (temp_id == id) {
            mt19937 gen(rd());
            uniform_int_distribution<>distrib(1, 999);
            randomId = distrib(gen);
            string id = to_string(randomId);
            yy.close();
            ifstream yy("system");
        }
    }
    yy.close();

    cout << "Allow anonymous questions? (0 or 1) : ";
    bool anonymous;
    cin >> anonymous;
    ofstream x(username.c_str());
    x << password << " " << anonymous << " " << id << " " << name << " " << email;
    x.close();

    ofstream ss(username + "_to");
    ss.close();
    ofstream s(username + "_from");
    s.close();
    ofstream y("system", ios::out | ios::app);
    y << "ID: " << id << "      Name: " << username.c_str() << endl;
    y.close();
}

bool login(string& username, string& password) {
    cout << "Enter username: ";
    cin >> username;
    ifstream x(username.c_str());
    if (x.fail()) {
        cout << "There's no such a username in the database\n";
        x.close();
        return false;
    }
    cout << "Enter Password: ";
    cin >> password;
    string cpassword;
    x >> cpassword;
    if (password != cpassword) {
        cout << "Incorrect password...\n";
        return false;
    }
    x.close();
    return true;
}

void printing_users() {
    ifstream x("system");
    string line;
    cout << endl;
    while (getline(x, line)) {
        cout << line << endl;
    }
    cout << endl;
    x.close();
}

bool insert_line(string file_name, int line_number_to_insert_after, string inserting_line) {
    vector <string> lines;
    string line;
    ifstream file(file_name.c_str());
    if (!file.is_open()) {
        cout << "Error opening file for reading: " << file_name << endl;
        file.close();
        return false;
    }
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    int index = line_number_to_insert_after;
    if (index < 0) {
        index = 0;
    }
    if (index > lines.size()) {
        index = lines.size();
    }
    lines.insert(lines.begin() + index, inserting_line);
    ofstream fil(file_name, ios::out | ios::trunc);
    if (!fil.is_open()) {
        cout << "Error opening file for writing: " << file_name << endl;
        fil.close();
        return false;
    }
    for (string l : lines) {
        fil << l << endl;
    }
    fil.close();
    return true;
}

void ask_question(string username, string id) {
    cout << "Enter User id or -1 to cancel: ";
    string id_to;
    cin >> id_to;
    if (id_to == "-1") {
        return;
    }
    bool check1{ true };
    ifstream file("system");
    string username_to;
    string temp_id;
    while (file >> temp_id) {
        file >> temp_id;
        if (temp_id == id_to) {
            file >> username_to;
            file >> username_to;
            check1 = false;
            break;
        }
    }
    file.close();

    if (check1) {
        cout << "\nThere's no such an id in the data base\n\n";
        return;
    }
    else if (id == id_to) {
        cout << "\nYou can't ask yourself\n\n";
        return;
    }
    ifstream xx(username_to.c_str());
    bool check2{ false };
    for (int i{ 0 }; i < 2; i++) {
        string x;
        xx >> x;
        if (x == "1") {
            check2 = true;
        }
    }
    xx.close();
    bool check3;
    if (check2) {
        cout << "Note: Anonymous questions are allowed for this user\n";
        while (true) {
            cout << "Do you want to ask anonymous question ? (y/n): ";
            string answer;
            cin >> answer;
            if (answer == "y") {
                check3 = true;
                break;
            }
            else if (answer == "n") {
                check3 = false;
                break;
            }
            else {
                cout << "incorrect answer\n";
            }
        }
    }
    else {
        cout << "Note: Anonymous questions are not allowed for this user\n";
        check3 = false;
    }
    cout << "For thread question: Enter Question id or -1 for new question or -2 to cancel: ";
    string Question_id, id_q;
    cin >> Question_id;
    if (Question_id == "-1") {
        random_device rdd;
        mt19937 gen(rdd());
        uniform_int_distribution<>distrib(1, 999);
        int randomIdd = distrib(gen);
        id_q = to_string(randomIdd);
        cout << "Enter question text: ";
        string text;
        cin.ignore();
        getline(cin, text);
        ofstream xx(username + "_to", ios::out | ios::app);
        ofstream uu(username_to + "_from", ios::out | ios::app);
        string id_q_temp;
        ifstream hhh("Questions_id");
        bool check4{ false };
        if (hhh >> id_q_temp) {
            check4 = true;
        }
        hhh.close();
        ofstream qq("Questions_id", ios::out | ios::app);
        if (check4) {
            qq << " ";
        }
        qq.close();
        ifstream hh("Questions_id");

        while (hh >> id_q_temp) {
            if (id_q_temp == id_q) {
                mt19937 gen(rdd());
                uniform_int_distribution<>distrib(1, 999);
                int randomIdd = distrib(gen);
                id_q = to_string(randomIdd);
                hh.close();
                ifstream hh("Questions_id");
            }
        }
        hh.close();
        ofstream koko("Questions_id", ios::out | ios::app);
        koko << id_q;
        koko << " " << username << " " << id;
        koko.close();
        ifstream jojo(username + "_to");
        ifstream jo(username_to + "_from");
        string doo;
        if (jojo >> doo) {
            xx << endl;
        }
        if (jo >> doo) {
            uu << endl;
        }
        xx << "Question Id (" << id_q << ") ";
        if (!check3) {
            xx << "!AQ";
        }
        else {
            xx << " AQ";
        }
        xx << " to user id(" << id_to << ")        Question: " << text << endl;
        xx.close();
        uu << "Question Id (" << id_q << ") ";
        if (!check3) {
            uu << "from user id (" << id << ")";
        }
        uu << "        Question: " << text << endl;
        uu.close();
    }
    else if (Question_id == "-2") {
        return;
    }
    else {
        ifstream pop(username_to + "_from");
        string temp;
        bool check1 = false;
        int x{ 0 };
        int cnt{ 0 };
        string line;
        bool check_last = true;
        while (getline(pop, line)) {
            if (line.empty()) {
                cnt++;
                continue;
            }
            istringstream iss(line);
            string word;
            for (int i{ 0 }; i < 3; i++) {
                iss >> word;
            }
            if (word == "(" + Question_id + ")") {
                check1 = true;
                while (getline(pop, line)) {
                    cnt++;
                    istringstream isss(line);
                    isss >> word;
                    if (word == "Question") {
                        check_last = false;
                        x = cnt;
                        break;
                    }
                }
                break;

            }
            cnt++;

        }



        pop.close();
        if (!check1) {
            cout << "\nThere's no question with such an id in the data base of this user\n\n";
            return;
        }
        cout << "Enter question text: ";
        random_device rdd;
        mt19937 gen(rdd());
        uniform_int_distribution<>distrib(1, 999);
        int randomIdd = distrib(gen);
        id_q = to_string(randomIdd);
        string id_q_temp;
        ifstream hhh("Questions_id");
        bool check4{ false };
        if (hhh >> id_q_temp) {
            check4 = true;
        }
        hhh.close();
        ofstream qq("Questions_id", ios::out | ios::app);
        if (check4) {
            qq << " ";
        }
        qq.close();
        ifstream hh("Questions_id");

        while (hh >> id_q_temp) {
            if (id_q_temp == id_q) {
                mt19937 gen(rdd());
                uniform_int_distribution<>distrib(1, 999);
                int randomIdd = distrib(gen);
                id_q = to_string(randomIdd);
                hh.close();
                ifstream hh("Questions_id");
            }
        }
        hh.close();
        ofstream koko("Questions_id", ios::out | ios::app);
        koko << id_q;
        koko << " " << username << " " << id;
        koko.close();
        string text, tempp;
        cin.ignore();
        getline(cin, text);
        string textt = text;
        tempp = "        Thread: Question Id (" + id_q + ") ";
        if (!check3) {
            tempp += "from user id (" + id + ")";
        }
        text = tempp + "        Question: " + text + "\n";
        if (check_last) {
            ofstream t(username_to + "_from", ios::out | ios::app);
            text = "\n" + text;
            t << text;
        }
        else {
            insert_line(username_to + "_from", x, text);
        }

        ifstream popp(username + "_to");
        check1 = true;
        cnt = 0;
        check_last = true;
        while (getline(popp, line)) {
            if (line.empty()) {
                cnt++;
                continue;
            }
            istringstream iss(line);
            string word;
            for (int i{ 0 }; i < 3; i++) {
                iss >> word;
            }
            if (word == "(" + Question_id + ")") {
                check1 = false;
                while (getline(popp, line)) {
                    cnt++;
                    istringstream isss(line);
                    isss >> word;
                    if (word == "Question") {
                        check_last = false;
                        x = cnt;
                        break;
                    }
                }
                break;

            }
            cnt++;

        }
        popp.close();
        ofstream ppopp(username + "_to", ios::out | ios::app);
        tempp = "        Thread: Question Id (" + id_q + ") ";
        if (!check3) {
            tempp += "!AQ";
        }
        else {
            tempp += "AQ";
        }
        textt = tempp + "        Question: " + textt + "\n";
        if (!check1) {
            if (check_last) {
                ofstream dod(username + "_to", ios::out | ios::app);
                dod << endl << textt;
            }
            else {
                insert_line(username + "_to", x, textt);
            }
        }
        else {
            ppopp << endl << endl << endl << textt;
            ppopp.close();
        }
    }

}


void printing_questions_from_me(string username) {
    ifstream x(username + "_to");
    string line;
    cout << endl;
    while (getline(x, line)) {
        cout << line << endl;
    }
    cout << endl;
    x.close();
}
void printing_questions_from_others(string username) {
    ifstream x(username + "_from");
    string line;
    cout << endl;
    while (getline(x, line)) {
        cout << line << endl;
    }
    cout << endl;
    x.close();
}

void print_two_lines(string username, int xx, bool check3) {
    string line;
    ifstream x(username + "_from");
    for (int i{ 1 }; i < xx; i++) {
        getline(x, line);
    }
    if (check3) {
        getline(x, line);
        cout << line << endl;
        getline(x, line);
        cout << line << endl;
    }
    else {
        getline(x, line);
        cout << line << endl;
    }
    x.close();
}

void delete_line(string username, int xx) {
    vector <string> lines;
    string line;
    ifstream x(username);
    for (int i{ 1 }; i <= xx; i++) {
        getline(x, line);
        lines.push_back(line);
    }
    getline(x, line);
    while (getline(x, line)) {
        lines.push_back(line);
    }
    x.close();
    ofstream xxx(username, ios::out | ios::trunc);
    for (string l : lines) {
        xxx << l << endl;
    }
    xxx.close();

}
void delete_lines(string file, int start, int end) {
    vector <string> lines;
    string line;
    ifstream x(file);
    for (int i{ 1 }; i < start; i++) {
        getline(x, line);
        lines.push_back(line);
    }
    for (int i{ start }; i < end; i++) {
        getline(x, line);
    }
    while (getline(x, line)) {
        lines.push_back(line);
    }
    x.close();
    ofstream xxx(file, ios::out | ios::trunc);
    for (string l : lines) {
        xxx << l << endl;
    }
    xxx.close();
}

void answer_question(string username) {
    cout << "Enter Question id or -1 to cancel: ";
    string question_id;
    cin >> question_id;
    if (question_id == "-1") {
        return;
    }
    else {
        bool check1{ true }, check2{ false }, check3{ false }, check4{ true }; //check1 for existance of question // check 2 for thread // check 3 if answered of not // check 4 for AQ questions
        ifstream x(username + "_from");
        string temp, line;
        int xx, cnt{ 1 };
        string username_to, id_to;

        while (getline(x, line)) {
            if (line.empty()) {
                cnt++;
                continue;
            }
            istringstream iss(line);
            iss >> temp;
            if (temp == "Question") {
                iss >> temp;
                iss >> temp;
                if (temp == "(" + question_id + ")") {
                    check1 = false;
                    xx = cnt;
                    iss >> id_to;
                    if (id_to == "from") {
                        iss >> id_to;
                        iss >> id_to;
                        iss >> id_to;
                        getline(x, line);
                        istringstream isss(line);
                        isss >> temp;
                        if (temp == "Answer:") {
                            check3 = true;
                        }

                    }
                    else {
                        getline(x, line);
                        istringstream isss(line);
                        isss >> temp;
                        if (temp == "Answer:") {
                            check3 = true;
                        }
                        check4 = false;
                    }
                }
            }
            else if (temp == "Thread:") {
                iss >> temp;
                iss >> temp;
                iss >> temp;
                if (temp == "(" + question_id + ")") {
                    check1 = false;
                    check2 = true;
                    xx = cnt;
                    iss >> id_to;
                    if (id_to == "from") {
                        iss >> id_to;
                        iss >> id_to;
                        iss >> id_to;
                        getline(x, line);
                        istringstream isss(line);
                        isss >> temp;
                        isss >> temp;
                        if (temp == "Answer:") {
                            check3 = true;
                        }

                    }
                    else {
                        getline(x, line);
                        istringstream isss(line);
                        isss >> temp;
                        isss >> temp;
                        if (temp == "Answer:") {
                            check3 = true;
                        }
                        check4 = false;
                        ifstream ff("Questions_id");

                    }
                }
            }

            cnt++;

        }
        x.close();
        if (check1) {
            cout << "There's no question for you with such an id in the data base\n";
            return;
        }

        if (check4) {
            ifstream y("system");
            while (y >> temp) {
                y >> temp;
                if ("(" + temp + ")" == id_to) {
                    id_to = temp;
                    y >> temp;
                    y >> username_to;
                }
                getline(y, line);
            }
            y.close();
        }
        else {
            ifstream y("Questions_id");
            while (y >> temp) {
                if (temp == question_id) {
                    y >> username_to;
                    break;
                }
            }
            y.close();
        }
        print_two_lines(username, xx, check3);
        cout << "\n\n";
        if (check3) {
            cout << "Warning: Already answered. Answer will be updated\n";
        }
        cout << "Enter answer: ";
        string text, tempp{ "" };
        cin.ignore();
        getline(cin, text);
        if (check3) {
            delete_line(username + "_from", xx);
        }
        if (check2) {
            tempp = "        Thread:";
        }
        text = tempp + "        Answer: " + text;
        insert_line(username + "_from", xx, text);



        ifstream f(username_to + "_to");
        cnt = 1;

        while (getline(f, line)) {
            if (line.empty()) {
                cnt++;
                continue;
            }
            istringstream iis(line);
            iis >> temp;
            if (temp == "Question") {
                iis >> temp;
                iis >> temp;
                if (temp == "(" + question_id + ")") {
                    xx = cnt;
                }
            }
            else if (temp == "Thread:") {
                iis >> temp;
                iis >> temp;
                iis >> temp;
                if (temp == "(" + question_id + ")") {
                    xx = cnt;
                }
            }
            cnt++;
        }
        cout << endl << xx << endl;
        f.close();
        if (check3) {
            delete_line(username_to + "_to", xx);
        }
        insert_line(username_to + "_to", xx, text);

    }
}

void delete_answer(string username) {
    cout << "Enter Question id or -1 to cancel: ";
    string question_id;
    cin >> question_id;
    if (question_id == "-1") {
        return;
    }
    else {
        ifstream f(username + "_from");
        bool check1{ true }, check2{ false }, check3{ false };
        string line, temp, id_from;
        int x, cnt{ 1 };
        while (getline(f, line)) {
            if (line.empty()) {
                cnt++;
                continue;
            }
            istringstream is(line);
            is >> temp;
            if (temp == "Question") {
                is >> temp;
                is >> temp;
                if (temp == "(" + question_id + ")") {
                    check1 = false;
                    x = cnt;
                    is >> temp;
                    if (temp == "from") {
                        check3 = true;
                        is >> temp;
                        is >> temp;
                        is >> id_from;
                    }
                    getline(f, line);
                    istringstream iss(line);
                    iss >> temp;
                    if (temp == "Answer:") {
                        check2 = true;
                    }
                }
            }
            else if (temp == "Thread:") {
                is >> temp;
                if (temp == "Question") {
                    is >> temp;
                    is >> temp;
                    if (temp == "(" + question_id + ")") {
                        check1 = false;
                        x = cnt;
                        is >> temp;
                        if (temp == "from") {
                            check3 = true;
                            is >> temp;
                            is >> temp;
                            is >> id_from;
                        }
                        getline(f, line);
                        istringstream iss(line);
                        iss >> temp;
                        iss >> temp;
                        if (temp == "Answer:") {
                            check2 = true;
                        }
                    }
                }
            }
            cnt++;
        }
        f.close();
        if (check1) {
            cout << "\nThere's no question with this id in the data base\n\n";
            return;
        }
        if (!check2) {
            cout << "\nThe Question is not answered yet\n\n";
            return;
        }
        delete_line(username + "_from", x);


        string username_from;
        if (check3) {
            ifstream ff("system");
            while (ff >> temp) {
                ff >> temp;
                if (id_from == "(" + temp + ")") {
                    ff >> temp;
                    ff >> username_from;
                }
            }
            ff.close();
        }
        else {
            ifstream ff("Questions_id");
            while (ff >> temp) {
                if (temp == question_id) {
                    ff >> username_from;
                    break;
                }
            }
            ff.close();
        }

        cnt = 1;
        ifstream fff(username_from + "_to");
        while (getline(fff, line)) {
            if (line.empty()) {
                cnt++;
                continue;
            }
            istringstream iis(line);
            iis >> temp;
            if (temp == "Question") {
                iis >> temp;
                iis >> temp;
                if (temp == "(" + question_id + ")") {
                    x = cnt;

                }
            }
            else if (temp == "Thread:") {
                iis >> temp;
                if (temp == "Question") {
                    iis >> temp;
                    iis >> temp;
                    if (temp == "(" + question_id + ")") {
                        ;
                        x = cnt;
                    }
                }
            }
            cnt++;
        }
        delete_line(username_from + "_to", x);

    }
}

void delete_question(string username) {
    vector <string> q_ids;
    cout << "Enter Question id or -1 to cancel: ";
    string question_id;
    cin >> question_id;
    if (question_id == "-1") {
        return;
    }
    bool check1 = true;
    ifstream f(username + "_from");
    string line, temp;
    int start, end{ 0 }, cnt{ 0 };
    while (getline(f, line)) {
        if (line.empty()) {
            cnt++;
            continue;
        }
        istringstream is(line);
        is >> temp;
        if (temp == "Question") {
            is >> temp;
            is >> temp;
            if (temp == "(" + question_id + ")") {
                check1 = false;
                start = cnt;
                q_ids.push_back("(" + question_id + ")");
                while (getline(f, line)) {
                    cnt++;
                    if (line.empty()) {
                        continue;
                    }
                    istringstream iss(line);
                    iss >> temp;

                    if (temp == "Thread:") {
                        iss >> temp;
                        if (temp == "Question") {
                            iss >> temp;
                            iss >> temp;
                            q_ids.push_back(temp);
                        }
                    }
                    else if (temp == "Question") {
                        end = cnt;
                        break;
                    }
                }
                if (end == 0) {
                    cnt += 2;
                    end = cnt;
                }
                end = cnt;

            }
        }
        else if (temp == "Thread:") {
            is >> temp;
            if (temp == "Question") {
                is >> temp;
                is >> temp;
                if (temp == "(" + question_id + ")") {
                    check1 = false;
                    start = cnt;
                    q_ids.push_back("(" + question_id + ")");
                    while (getline(f, line)) {
                        cnt++;
                        if (line.empty()) {
                            continue;
                        }
                        istringstream iss(line);
                        iss >> temp;
                        if (temp == "Thread:") {
                            iss >> temp;
                            if (temp == "Question") {
                                end = cnt;
                                break;
                            }
                        }
                        else if (temp == "Question") {
                            end = cnt;
                            break;
                        }

                    }
                    end = cnt;
                }
            }
        }
        cnt++;
    }
    f.close();

    if (check1) {
        cout << "\nThere's no Question with such an id in the data base\n\n";
        return;
    }
    if (start == end) {
        end += 2;
    }
    cout << start << " " << end << "\n\n";
    delete_lines(username + "_from", start, end);


    /*for (string x : q_ids) {
        cout << x << " ";
    }*/


    for (string x : q_ids) {
        string username_from;
        int startt, endd{ 0 };
        cnt = 0;
        string linee, tempp;
        bool check1{ true };
        ifstream ff("Questions_id");
        while (ff >> tempp) {
            if (x == "(" + tempp + ")") {
                ff >> username_from;
                break;
            }
        }
        ff.close();


        ifstream fff(username_from + "_to");
        while (getline(fff, linee)) {
            if (linee.empty()) {
                cnt++;
                continue;
            }
            istringstream iis(linee);
            iis >> tempp;
            if (tempp == "Question") {
                iis >> tempp;
                iis >> tempp;
                if (tempp == x) {
                    check1 = false;
                    startt = cnt;
                    while (getline(fff, linee)) {
                        cnt++;
                        if (linee.empty()) {
                            continue;
                        }
                        istringstream iiss(linee);
                        iiss >> tempp;
                        if (tempp == "Question") {
                            endd = cnt;
                            break;
                        }
                    }
                    if (endd == 0) {
                        cnt += 2;
                        endd = cnt;
                    }
                    endd = cnt;

                }
            }
            else if (tempp == "Thread:") {
                iis >> tempp;
                if (tempp == "Question") {
                    iis >> tempp;
                    iis >> tempp;
                    if (tempp == x) {
                        check1 = false;
                        startt = cnt;
                        while (getline(fff, linee)) {
                            cnt++;
                            if (linee.empty()) {
                                continue;
                            }
                            istringstream iiss(linee);
                            iiss >> tempp;
                            if (tempp == "Thread:") {
                                iiss >> tempp;
                                if (tempp == "Question") {
                                    endd = cnt;
                                    break;
                                }
                            }
                            else if (tempp == "Question") {
                                endd = cnt;
                                break;
                            }

                        }
                        endd = cnt;
                    }
                }
            }
            cnt++;
        }
        fff.close();
        if (check1) {
            continue;
        }
        if (startt == endd) {
            endd += 2;
        }
        cout << startt << " " << endd << "\n\n";
        delete_lines(username_from + "_to", startt, endd);

    }


}

void feed(string username) {
    ifstream f(username + "_from");
    string line1, line2;
    string temp1, temp3;

    while (getline(f, line1)) {
        vector <string> temp2;
        if (line1.empty()) {
            continue;
        }
        istringstream is(line1);
        is >> temp1;
        if (temp1 == "Question") {
            is >> temp3;
            is >> temp3;
            getline(f, line2);
            istringstream iss(line2);
            iss >> temp1;
            if (temp1 == "Answer") {
                cout << line1 << endl << line2 << endl << endl;
            }

        }
        else if (temp1 == "Thread:") {
            is >> temp1;
            if (temp1 == "Question") {
                getline(f, line2);
                istringstream iss(line2);
                iss >> temp1;
                iss >> temp1;
                if (temp1 == "Answer:") {
                    istringstream iis(line1);
                    iis >> temp1;
                    while (iis >> temp1) {
                        temp2.push_back(temp1);
                    }
                    line1 = "";
                    for (string x : temp2) {
                        line1 += x;
                        line1 += " ";
                    }
                    cout << "Thread Parent Question ID " << temp3 << " " << line1 << endl << line2 << endl << endl;
                }
            }
        }
    }
}

int main() {
    while (true) {
        string choice1 = menu1();
        if (choice1 == "1") {
            string username, password;
            bool checking = login(username, password);
            ifstream x(username.c_str());
            string id;
            for (int i{ 0 }; i < 3; i++) {
                x >> id;
            }
            x.close();
            if (checking) {
                while (true) {
                    string choice2 = menu2();
                    if (choice2 == "1") {
                        printing_questions_from_others(username);
                    }
                    else if (choice2 == "2") {
                        printing_questions_from_me(username);
                    }
                    else if (choice2 == "3") {
                        answer_question(username);
                    }
                    else if (choice2 == "4") {
                        delete_question(username);
                    }
                    else if (choice2 == "5") {
                        ask_question(username, id);
                    }
                    else if (choice2 == "6") {
                        printing_users();
                    }
                    else if (choice2 == "7") {
                        feed(username);
                    }
                    else if (choice2 == "8") {
                        break;
                    }
                    else if (choice2 == "9") {
                        delete_answer(username);
                    }
                    else
                        cout << "\nIncorrect choice... Please tryagain\n\n";
                }
            }
        }
        else if (choice1 == "2") {
            signup();
        }
        else {
            cout << "\nIncorrect choice... Please tryagain\n\n";
        }
    }
}