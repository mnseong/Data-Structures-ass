#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n, m, year = 1;
vector<vector<int>> field;
vector<vector<bool>> isVisited;
vector<pair<int, int>> meltList;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void inputData() {
	cin >> n >> m;
	field.resize(n, vector<int> (m, 0));
	isVisited.resize(n, vector<bool> (m, false));
	
	string tmp;
	for (int i = 0; i < n; i++) {
		cin >> tmp;
		for (int j = 0; j < m; j++) {
			field[i][j] = tmp[j] - '0';
		}
	}
}

// Debugging
void showCurState() {
	cout << "현재 필드 상태" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << field[i][j];
		}
		cout << endl;
	}
	cout << "현재 방문 상태" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << isVisited[i][j];
		}
		cout << endl;
	}
	cout << "다음에 녹일 것" << endl;
	for (int i = 0; i < meltList.size(); i++) {
		cout << meltList[i].first << meltList[i].second << endl;
	}
}

void bfs() {
	queue<pair<int, int>> q;
	q.push(make_pair(0, 0));
	isVisited[0][0] = true;
	
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			
			if (nx>=0&&ny>=0&&nx<n&&ny<m) {
				if (!field[nx][ny] && !isVisited[nx][ny]) {
					q.push(make_pair(nx, ny));
					isVisited[nx][ny] = 1;
				} else if (field[nx][ny] && !isVisited[nx][ny]) {
					meltList.push_back(make_pair(nx, ny));
				}
			}
		}
	}
}

void init() {
	fill(isVisited.begin(), isVisited.end(), vector<bool> (m, false));
	meltList.clear();
}

bool success() {
	bool result = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (field[i][j]) result = false;
		}
	}
	return result;
}

int main(void){
	inputData();
	
	for ( ; ;year++) {
		bfs();
		for (int i = 0; i < meltList.size(); i++) {
			int x = meltList[i].first;
			int y = meltList[i].second;
			field[x][y] = 0;
		}
		if (success()) break;
		init();
	}
	
	cout << year << endl;
	
	return 0;
}

