#include <Windows.h>
#include "String.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n------------------------------------\n"

#define DEBUG



//#define CONSTRUCTORS_CHECK
#define OPERATOR_PLUS
//#define ISTREAM_OPERATOR
//#define PERFORMANCE_TEST
//#define CALLING_CONSTRUCTORS

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	String str1(5);	//explicit-конструктор нельзя вызвать оператором '=', но всегда можно вызвать при помощи круглых скобок
	str1.info();
	cout << str1 << endl;

	String str2 = "Hello";
	str2 = str2;
	cout << str2 << endl;

	String str3 = str2;		//CopyConstructor
	cout << str3 << endl;

	String str4;
	str4 = str3;
	cout << str4 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATOR_PLUS
	String str1 = "Hello";
	String str2 = "World";
	cout << delimiter << endl;
	String str3;
	str3 = str1 + str2;
	cout << delimiter << endl;
	cout << str3 << endl;
	cout << delimiter << endl;
	String str4 = str3;
	cout << str4 << endl;
	cout << delimiter << endl;
	//MoveSemantic
#endif // OPERATOR_PLUS

#ifdef ISTREAM_OPERATOR
	String str;
	cout << "Введите строку: ";
	SetConsoleCP(1251);
	//cin >> str;
	//cin.getline(str.get_str(), str.get_size());
	getline(cin, str);
	SetConsoleCP(866);
	cout << str << endl;
#endif // ISTREAM_OPERATOR

#ifdef PERFORMANCE_TEST
	String text = R"(When a return statement contains an expression of non-primitive type, its execution copies the expression result into the return slot of the calling function. The compiler invokes the copy or move constructor of the returned type. Then, as the function is exited, destructors for function-local variables are called, which includes any variables named in the expression.
		The C++ standard allows(but doesn't require) the compiler to optionally construct the returned object directly in the return slot of the calling function. This construction skips (or elides) the copy or move constructor executed as part of the return statement. Unlike most other optimizations, this transformation is allowed to have an observable effect on the program's output.Namely, the copy or move constructor and associated destructor are called one less time.The standard still requires that the named returned variable has a defined copy or move constructor, even if the compiler elides the constructor in all cases.
			In versions before Visual Studio 2022 version 17.4, when optimizations are disabled(such as under / Od or in functions marked #pragma optimize("", off)) the compiler only performs mandatory copy and move elision.Under / O2, the older compilers perform optional copy or move elision on return of a named variable in an optimized function when all of these conditions are met : it has no loops or exception handling, it doesn't return multiple symbols with overlapping lifetimes, the type's copy or move constructor doesn't have default arguments.
			Visual Studio 2022 version 17.4 increases the number of places where the compiler does optional copy or move elisions under / Zc : nrvo, whether enabled explicitly, or automatically by using the / O2, / permissive - , or /std : c++20 or later options.Under / Zc : nrvo, the compiler performs optional copy or move elision on return of a named variable for any function when : it has no loops or exception handling(as before); it returns the variable from a loop; it has exception handling; the returned type's copy or move constructor has default arguments. Optional copy or move elisions are never done when /Zc:nrvo- is applied, or when the function returns multiple symbols with overlapping lifetimes, or for a throw of a named variable.)";
	cout << text.get_size() << endl;

	const int SIZE = 100000;
	String arr[SIZE]{};
	String get_text(const String & other);
	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = get_text(text);
	}
	cout << "DONE" << endl;
#endif // PERFORMANCE_TEST

#ifdef CALLING_CONSTRUCTORS
	String str1;		//Default constructor
	str1.info();

	String str2(8);		//Single-argument constructor ('int') 8 - размер строки в Байтах;
	str2.info();

	String str3 = "Hello";	//Single-argumentconstructor ('const char*');
	str3.info();
	cout << typeid("Hello").name() << endl;

	String str4();		//(Default constrcutor) Здесь НЕ вызывается никакой конструктор,
	//и не создается никакой объект, здесь происходит объявление функции str4(),
	//которая ничего НЕ принимает, и озвращает объект типа 'String'.
//Пустые () НЕ делают явный вызов Default-конструктора.
//str4.

//Если нужно явно вызвать DefaultConstructor, это можно сделать {}
	String str5(8);		//Создается строка длиной 8 Байт
	String str6{ 8 };	//Создается строка длиной 8 Байт, т.е., {} вызывают конструктор.
	String str7{};		//Явный вызов конструктора по умолчанию
	//		!!!		{} СЛЕДУЕТ ИСПОЛЬЗОВАТЬ С ОСТОРОЖНОСТЬЮ		!!!

	String str9 = str3;	//CopyConstructor
	str9.info();
#endif // CALLING_CONSTRUCTORS

}

String get_text(const String& other)
{
	String local = other;
	return local;
}

/*
---------------------------------
C++11 MoveSemantic:
MoveConstructor - Конструктор переноса;
MoveAssignment  - Переносящий оператор присваивания;
Move-методы принимают r-value reference: Class&&
CopyConstructor,CopyAssignment - DeepCopy		(Побитовое копирование);
MoveConstrcutor,MoveAssignment - ShallowCopy	(Поверхностное копирование);
---------------------------------
*/