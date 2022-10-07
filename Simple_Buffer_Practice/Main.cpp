#include <iostream>
#include <string>

using namespace std;

// Your class SimpleBuffer
template <class T>
class SimpleBuffer{
	private:
		T data_;
	
	public:	
		// Implement your public members
		// SimpleBuffer(string data);
		// SimpleBuffer(int data);
		SimpleBuffer(T data);
		
		friend istream& operator >> (istream &in, SimpleBuffer<T> &buf) {
			T tmp;
			in >> tmp;
			buf.data_ += tmp;
			return in;
		}
		friend ostream& operator << (ostream &out, SimpleBuffer<T> &buf) {
			out << "Current data: " <<buf.data_;
			return out;
		}

};	// Class implementation ends

// Implement your overloaded functions

template <class T>
SimpleBuffer<T>::SimpleBuffer(T data) : data_(data) {};

// main() of your program for test
int main() {
	SimpleBuffer<string> buf_str("");
	
	for(int k = 0; k < 3; k++){
		cin >> buf_str;
		cout << buf_str << endl;
	}
	
	SimpleBuffer<int> buf_int(0);
	
	for(int k = 0; k < 5; k++){
		cin >> buf_int;
		cout << buf_int << endl;
	}
	
	return 0;
}