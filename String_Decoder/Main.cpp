#include <iostream>
#include <string>
#include <stack>

using namespace std;

stack<string> str_stack;
stack<int> int_stack;

string repetition(string s, int n) {
	string res;
	for (int i = 0; i < n; i++) {
		res += s;
	}
	return res;
}

string invalid_n = "GHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?@#$%^&*";
string heximal = "ABCDEF";

class StringDecoder{
	private:
		string data_;
	// Implement your class here
	public:
		StringDecoder();
		string decoding(string s);
		void setData(string s);
		friend istream& operator >> (istream &in, StringDecoder &sd) {
			string tmp;
			in >> tmp;
			sd.setData(sd.decoding(tmp));
			return in;
		}
		friend ostream& operator << (ostream &out, StringDecoder &sd) {
			out << sd.data_;
			return out;
		}
};

// Implement your class here
StringDecoder::StringDecoder() {};

string StringDecoder::decoding(string s) {
	string current;
	int decimal;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '{') {
			if (invalid_n.find(s[i-1]) != string::npos) {
				current = "ERROR: Invalid input";
				break;
			} else if ('A' <= s[i-1] && s[i-1] <= 'F') {
				decimal = 10 + heximal.find(s[i-1]);
			} else if (isdigit(s[i-1])) {
				decimal = s[i-1] - 48;
			}
			str_stack.push(current);
			int_stack.push(decimal);
			current = "";
			decimal = 0;
		} else if (s[i] == '}') {
			string prev_str = str_stack.top();
			int num = int_stack.top();
			str_stack.pop();
			int_stack.pop();
			current = repetition(current, num);
			current.insert(0, prev_str);
		} else if (s[i+1] != '{') {
			current += s[i];
		}
	}
	return current;
};

void StringDecoder::setData(string s) {
	data_ = s;
}
int main(){
	StringDecoder sd;
	
	// Note:
	// encoded input strings are read from an input file using operator>>
	// your class may store a decoded string in data_ to print it using operator<<
	while(cin >> sd){
		cout << sd << endl;
	}
	
	return 0;
}