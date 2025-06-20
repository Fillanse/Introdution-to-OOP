#include <iostream>
using namespace std;

class String
{
public:
	String() : _size(0), _capacity(10) {
		_str = new char[_capacity];
		_str[0] = '\0';
	}
	String(const char* str) {
		_size = strlen(str);
		_capacity = _size + 1;
		_str = new char[_capacity];
		assign(str);
	}
	String(const String& other) {
		*this = other;
	}
	~String() { delete[] _str; }

	String& operator=(const String& other) {
		if (this != &other) {
			delete[] _str;
			_size = other._size;
			_capacity = other._capacity;
			_str = new char[_capacity];
			for (int i = 0; i < _size; i++) {
				_str[i] = other[i];
			}
			_str[_size] = '\0';
		}
		return *this;
	}
	String& operator=(const char* str) {
		assign(str);
		return *this;
	}
	char& operator[](int index) {
		return _str[index];
	}
	const char& operator[](int index) const {
		return _str[index];
	}

	String& append(const char* str) {
		size_t len = strlen(str);
		if (_size + len + 1 > _capacity) {
			reserve(_size + len + 1);
		}
		for (int i = 0; i < len; i++) {
			_str[_size + i] = str[i];
		}
		_size += len;
		_str[_size] = '\0';
		return *this;
	}

	size_t get_size() const { return _size; }
	size_t get_capacity() const { return _capacity; }
	char* data() { return _str; }
	const char* data() const { return _str; }
private:
	void assign(const char* str) {
		size_t len = strlen(str);
		reserve(len + 1);
		for (int i = 0; i <= len; i++) {
			_str[i] = str[i];
		}
		_size = len;
	}
	void reserve(size_t capacity) {
		if (capacity > _capacity) {
			char* new_str = new char[capacity];
			for (int i = 0; i < _capacity; i++) {
				new_str[i] = _str[i];
			}
			delete[] _str;
			_str = new_str;
			_capacity = capacity;
		}
	}
	char* _str;
	size_t _size;
	size_t _capacity;
};
String operator+(const String& left, const String& right) {
	String temp(left);
	temp.append(right.data());
	return temp;
}
ostream& operator<<(ostream& os, const String& str) {
	for (int i = 0; i < str.get_size(); i++) {
		os << str[i];
	}
	return os;
}

int main()
{
	String str1 = "Hello";
	String str2 = "World";
	cout << str1;
	cout << str2;
	String str3 = str1 + str2;
	cout << str3 << endl;
}
