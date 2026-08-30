#include <iostream>; // cin & cout
#include <string>; // getline
using namespace std;
int main() {
	string a[9][9];
	int N;
	cin >> N;
	for (int i{ 0 }; i < N; i++)
		for (int j{ 0 }; j < N; j++)
			a[i][j] = ".";
	int di[12][3] = {
		{-2,-1,0},
		{-1,0,1},
		{0,1,2},
		{-2,-1,0},
		{-1,0,1},
		{0,1,2},
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{-2,-1,0},
		{-1,0,1},
		{0,1,2}
	};
	int dj[12][3] = {
		{0,0,0},
		{0,0,0},
		{0,0,0},
		{-2,-1,0},
		{-1,0,1},
		{0,1,2},
		{-2,-1,0},
		{-1,0,1},
		{0,1,2},
		{2,1,0},
		{1,0,-1},
		{0,-1,-2}
	};
	for (int i{ 0 }; i < N; i++) {
		for (int j{ 0 }; j < N; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	int temp_N = N;
	int games = N * N;
	bool is_x = true;
	while (games + 1) {
		if (games == 0) {
			cout << "Neither player x nor player y has won";
			break;
		}

		if (is_x) {
			cout << "Player x turn. Enter empty location (r,c): ";
			int r, c;
			cin >> r >> c;
			if (r > temp_N || c > temp_N || r < 0 || c < 0) {
				cout << "Invalid input. Try again" << endl;
				continue;
			}
			if (a[r - 1][c - 1] != ".") {
				cout << "Invalid input. Try again" << endl;
				continue;
			}
			a[--r][--c] = "x";
			for (int i{ 0 }; i < temp_N; i++) {
				for (int j{ 0 }; j < temp_N; j++)
					cout << a[i][j] << " ";
				cout << endl;
			}
			bool isis = false;
			for (int i{ 0 }; i < 12; i++) {
				bool is = false;
				int x = r + di[i][0];
				int xx = r + di[i][1];
				int xxx = r + di[i][2];
				int y = c + dj[i][0];
				int yy = c + dj[i][1];
				int yyy = c + dj[i][2];
				if (x >= 0 && xx >= 0 && xxx >= 0 && y >= 0 && yy >= 0 && yyy >= 0 && x < temp_N && xx < temp_N && xxx < temp_N && y < temp_N && yy < temp_N && yyy < temp_N) {
					if (a[x][y] == a[xx][yy] && a[xx][yy] == a[xxx][yyy]) {
						is = true;
					}
				}
				if (is) {
					cout << "Player x won";
					isis = true;
					break;
				}

			}
			if (isis)
				break;
			is_x = false;
			games--;
			continue;
		}
		if (!is_x) {
			cout << "Player o turn. Enter empty location (r,c): ";
			int r, c;
			cin >> r >> c;
			if (r > temp_N || c > temp_N || r < 0 || c < 0) {
				cout << "Invalid input. Try again" << endl;
				continue;
			}
			if (a[r - 1][c - 1] != ".") {
				cout << "Invalid input. Try again" << endl;
				continue;
			}
			a[--r][--c] = "o";
			for (int i{ 0 }; i < temp_N; i++) {
				for (int j{ 0 }; j < temp_N; j++)
					cout << a[i][j] << " ";
				cout << endl;
			}
			bool isis = false;
			for (int i{ 0 }; i < 12; i++) {
				bool is = false;
				int x = r + di[i][0];
				int xx = r + di[i][1];
				int xxx = r + di[i][2];
				int y = c + dj[i][0];
				int yy = c + dj[i][1];
				int yyy = c + dj[i][2];
				if (x >= 0 && xx >= 0 && xxx >= 0 && y >= 0 && yy >= 0 && yyy >= 0 && x < temp_N && xx < temp_N && xxx < temp_N && y < temp_N && yy < temp_N && yyy < temp_N) {
					if (a[x][y] == a[xx][yy] && a[xx][yy] == a[xxx][yyy]) {
						is = true;
					}
				}
				if (is) {
					cout << "Player o won";
					isis = true;
					break;
				}

			}
			if (isis)
				break;
			is_x = true;
			games--;
			continue;
		}


	}
}