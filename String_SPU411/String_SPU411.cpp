#include <iostream>
using namespace std;

class Str
{
public:
	explicit Str(int size) : size(80) {
		this->size = size;
		this->str = new char[size] {};
	}
	Str(const char* str) {
		while (str[size++]);
		this->str = new char[size] {};
		for (int i = 0; str[i]; i++) this->str[i] = str[i];
	}
	Str(const Str& other) {
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; str[i]; i++) this->str[i] = str[i];
	}
	~Str() {
		if (this != nullptr) {
			delete[] str;
			this->str = nullptr;
			size = 0;

		}
	};
	Str& operator=(Str& other) {
		if (this != &other) {
			delete[] str;
			this->size = other.size;
			this->str = new char[size] {};
			for (int i = 0; str[i]; i++) this->str[i] = str[i];
		}
		return *this;
	}
	int get_size() const {
		return size;
	}
	const char* get_str() const {
		return this->str;
	}
private:
	int size;
	char* str;
};
ostream& operator<<(ostream& os, const Str& str) {
	return os << str.get_str();
}

int main()
{
	Str A = "Hello";
	cout << A << endl;
	Str B = A;
	cout << B << endl;
}

