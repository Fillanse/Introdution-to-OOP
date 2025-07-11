#include"String.h"
/// ----------------------------------------------------------------- ///

/////////////////////////////////////////////////////////////////////////
/////////		����������� ������ - Class definition			/////////

int String::get_size()const
{
	return size;
}
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}

//				Constructors:
//�������� ����� 'explicit' ����� ������������ ������ ������ ������
String::String(int size) :size(size), str(new char[this->size] {})
{
	cout << "DefaultConstructor:\t" << this << endl;
}
//		:: - Scope operator (�������� ���������� ���������)
String::String(const char str[]) : String(strlen(str) + 1)
{
	for (int i = 0; str[i]; i++)this->str[i] = str[i];
	cout << "Constructor:\t\t" << this << endl;
}
String::String(const String& other) : String(other.str)
{
	cout << "CopyConstructor:\t" << this << endl;
}
String::String(String&& other) : size(other.size), str(other.str)
{
	other.size = 0;
	other.str = nullptr;	//�������� ������ �� �������� ������������.
	cout << "MoveConstructor:\t" << this << endl;
}
String::~String()
{
	delete[] str;
	this->str = nullptr;
	this->size = 0;
#ifdef DEBUG
	cout << "Destructor:\t\t" << this << endl;
#endif // DEBUG
}

//				Operators:
String& String::operator=(const String& other)
//type
{
	if (this == &other)return *this;
	delete[] this->str;
	this->size = other.size;
	this->str = new char[size] {};
	for (int i = 0; i < size; i++)this->str[i] = other.str[i];
#ifdef DEBUG
	cout << "CopyAssignment:\t\t" << this << endl;
#endif // DEBUG
	return *this;
}
String& String::operator=(String&& other)
{
	if (this == &other)return *this;
	delete[] this->str;
	this->size = other.size;
	this->str = other.str;
	other.size = 0;
	other.str = nullptr;
#ifdef DEBUG
	cout << "MoveAssignment:\t\t" << this << endl;
#endif // DEBUG

	return *this;
}
String& String::operator+=(const String& other)
{
	return *this = *this + other;
}
char String::operator[](int i)const
{
	return str[i];
}
char& String::operator[](int i)
{
	return str[i];
}

//				Methods:
void String::info()const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);	//Default constructor
	for (int i = 0; left.get_str()[i]; i++)
		//result.get_str()[i] = left.get_str()[i];
		result[i] = left[i];
	for (int i = 0; right.get_str()[i]; i++)
		//result.get_str()[left.get_size() - 1 + i] = right.get_str()[i];
		result[left.get_size() - 1 + i] = right[i];
	cout << "Operator+" << endl;
	return result;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}
std::istream& operator>>(std::istream& cin, String& obj)
{
	const int SIZE = 1024;	//������ ������ - 1kB
	char buffer[SIZE] = {};
	cin >> buffer;
	obj = buffer;
	return cin;
}
std::istream& getline(std::istream& cin, String& obj)
{
	cin.getline(obj.get_str(), obj.get_size());
	return cin;
}

/////////	����� ����������� ������ - Class definition	end		/////////
/////////////////////////////////////////////////////////////////////////