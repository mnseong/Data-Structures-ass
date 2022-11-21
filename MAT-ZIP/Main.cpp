// Add any additional header files freely
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

// Returns menu serving time of each menu
int getMenuTime(char menu){
	switch(menu){
		case 'A': return 1;
		case 'B': return 2;
		case 'C': return 3;
		case 'D': return 4;
		case 'E': return 5;
		case 'F': return 7;
		case 'G': return 10;
		case 'H': return 12;
		case 'I': return 14;
		case 'J': return 15;
	}
}

int n;
vector<pair<int, int>> v;
vector<int> check(32);
int flag, cnt;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int date;
		char menu;
		cin >> date >> menu;
		v.push_back(make_pair(date, getMenuTime(menu)));
	}
	sort(v.begin(), v.end(), greater<>());
	while (!v.empty()) {
		cnt++;
		for (int i = v.size()-1; i >= 0; i--) {
			if (v[i].first >= flag) {
				pair<int, int> minDate = v[i];
				int beginDate = minDate.first;
				int endDate = beginDate + minDate.second - 1;
				for (int i = beginDate; i < endDate + 1; i++) {
					if (check[i] == 0) {
						check[i]++;
					}
				}
				flag = endDate + 1;
				v.erase(v.begin() + i);
			}
		}
		for (int i = 0; i < check.size(); i++) {
			if (check[i] == 1) {
				check[i]--;
			}
		}
		flag = 0;
	}
	cout << cnt;
	return 0;
}