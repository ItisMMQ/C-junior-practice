#include "pch.h"
#include <cctype>
#include "interpreter.h"
//**************************  interpreter.cpp   ***********************

//��������
std::ostream& operator<< (std::ostream& out, const IdNode& r) {
	out << r.id << " = " << r.value << std::endl;
	return out;
}
//���ʽ���
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
	return 0;  //������Է���һ����ʵ���в�����
}
//���������ֵ
void Statement::processNode(char* id, double e) {
	IdNode tmp(id, e);
	std::list<IdNode>::iterator i = find(idList.begin(), idList.end(), tmp);
	if (i != idList.end())
		i->value = e;
	else idList.push_front(tmp);
	return;
}

// readId()��ȡ����ĸ��ͷ������ĸ��������ɵ��ַ��� r
//���ҽ��������������ʽ�洢����Ϊһ���������ݣ�
// ��־��ʾ�� : var1, x, pqr123xyz, aName, etc.
void Statement::readId(char *id) {
	int i = 0;
	if (isspace(ch))
		std::cin >> ch;       //�����ո�
	if (isalpha(ch)) {       //����ĸ��ͷ
		while (isalnum(ch)) {
			id[i++] = ch;
			std::cin.get(ch); //�����ո�
		}
		id[i] = '\0';             //���Ͻ�����־
	}
	else issueError("Identifier expected");
	return;
}

double Statement::factor() {
	double var, minus = 1.0;       //������������
	static char id[200];
	std::cin >> ch;
	while (ch == '+' || ch == '-') {//��ȡ���еķ���
		if (ch == '-')
			minus *= -1.0;
		std::cin >> ch;
	}
	if (isdigit(ch) || ch == '.') {   //���ӿ�����һ������
		std::cin.putback(ch);
		std::cin >> var >> ch;
	}
	else if (ch == '(') {               //Ҳ������һ�����ű��ʽ
		var = expression();          //��ȡ���ʽ
		if (ch == ')')                     //����ƥ��
			std::cin >> ch;
		else issueError("Right paren left out");
	}
	else {
		readId(id);                       //����һ����ʶ��
		if (isspace(ch))
			std::cin >> ch;
		var = findValue(id);       //��ʶ���������ֵ
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
	readId(id);                 //��ȡ������
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
	//�������VS2017���Բ����ټ�system("pause");���������������
}