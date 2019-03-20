#include "pch.h"
#include <cctype>
#include "interpreter.h"
//**************************  interpreter.cpp   ***********************

//语句输出？
std::ostream& operator<< (std::ostream& out, const IdNode& r) {
	out << r.id << " = " << r.value << std::endl;
	return out;
}
//表达式输出
std::ostream& operator<< (std::ostream& out, const Statement& s) {
	std::list<IdNode>::const_iterator i = s.idList.begin();
	for (; i != s.idList.end(); ++i)
		out << *i;
	out << std::endl;
	return out;
}

double Statement::findValue(char *id) {
	IdNode tmp(id);
	std::list<IdNode>::iterator i = find(idList.begin(), idList.end(), tmp);
	if (i != idList.end())
		return i->value;
	else issueError("Unknown variable");
	return 0;  //这句是以防万一，其实运行不到它
}
//保存变量的值
void Statement::processNode(char* id, double e) {
	IdNode tmp(id, e);
	std::list<IdNode>::iterator i = find(idList.begin(), idList.end(), tmp);
	if (i != idList.end())
		i->value = e;
	else idList.push_front(tmp);
	return;
}

// readId()读取由字母开头，以字母和数字组成的字符串 r
//并且将它们以数组的形式存储并作为一个参数传递，
// 标志符示例 : var1, x, pqr123xyz, aName, etc.
void Statement::readId(char *id) {
	int i = 0;
	if (isspace(ch))
		std::cin >> ch;       //跳过空格
	if (isalpha(ch)) {       //以字母开头
		while (isalnum(ch)) {
			id[i++] = ch;
			std::cin.get(ch); //保留空格
		}
		id[i] = '\0';             //加上结束标志
	}
	else issueError("Identifier expected");
	return;
}

double Statement::factor() {
	double var, minus = 1.0;       //变量，正负号
	static char id[200];
	std::cin >> ch;
	while (ch == '+' || ch == '-') {//读取所有的符号
		if (ch == '-')
			minus *= -1.0;
		std::cin >> ch;
	}
	if (isdigit(ch) || ch == '.') {   //因子可能是一个数字
		std::cin.putback(ch);
		std::cin >> var >> ch;
	}
	else if (ch == '(') {               //也可能是一个括号表达式
		var = expression();          //读取表达式
		if (ch == ')')                     //括号匹配
			std::cin >> ch;
		else issueError("Right paren left out");
	}
	else {
		readId(id);                       //或是一个标识符
		if (isspace(ch))
			std::cin >> ch;
		var = findValue(id);       //标识符所代表的值
	}
	return minus * var;           
}

double Statement::term() {
	double f = factor();
	while (true) {
		switch (ch) {
		case '*': f *= factor(); break;
		case '/': f /= factor(); break;
		default: return f;
		}
	}
}

double Statement::expression() {
	double t = term();
	while (true) {
		switch (ch) {
		case '+': t += term(); break;
		case '-': t -= term(); break;
		default: return t;
		}
	}
}

void Statement::getStatement() {
	char id[20], command[20];
	double e;
	std::cout << "Enter a statement: ";
	std::cin >> ch;
	readId(id);                 //读取变量名
	strcpy(command, id);//strcpy(dst,src);
	for (int i = 0; i < strlen(command);++ i)
		command[i] = toupper(command[i]);
	if (strcmp(command, "STATUS") == 0)
		std::cout << *this;
	else if (strcmp(command, "PRINT") == 0) {
		readId(id);
		std::cout << id << " = " << findValue(id) << std::endl;
	}
	else if (strcmp(command, "END") == 0)
		exit(0);
	else {
		if (isspace(ch))
			std::cin >> ch;
		if (ch == '=') {
			e = expression();
			if (ch != ';')
				issueError("There are some extras in the statement");
			else processNode(id, e);
		}
		else issueError("'=' is missing");
	}
}

#include <iostream>
#include <string>

using namespace std;

int main()
{
	Statement statement;
	cout << "The program processes statements of the following format:\n"
		<< "\t<id> = <expt>;\n\tprint <id>\n\tstatus\n\tend\n\n";
	while (1)
		statement.getStatement();
	std::cout << "Hello World!\n";
	//升级后的VS2017可以不用再加system("pause");来保持输出窗口了
}