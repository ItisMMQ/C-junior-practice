//标准库模板排序
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> // greater<>

class Person {
public:
	Person(char *n = "", int a = 0) {
		name = _strdup(n);
		age = a;
	}
	bool operator==(const Person& p) const {
		return strcmp(name, p.name) == 0; // && age == p.age;
	}
	bool operator<(const Person& p) const {
		return strcmp(name, p.name) < 0;
	}
private:
	char *name;
	int age;
	friend std::ostream& operator<< (std::ostream& out, const Person& p) {
		out << "(" << p.name << "," << p.age << ")";
		return out;
	}
};

bool f1(int n) {return n < 5;}

template<typename T>
void printVector(char *s, const std::vector<T>& v) {
	std::cout << s << " = (";
	if (v.size() == 0) {
		std::cout << ")\n";
		return;
	}
	typename std::vector<T>::const_iterator it;
	for (it = v.begin(); it != v.end() - 1; ++it)
		std::cout << *it << ',';
	std::cout << *it << ")\n";
}

//多项式相加

