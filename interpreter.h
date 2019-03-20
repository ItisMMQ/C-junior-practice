//**************************  interpreter.h   ***********************
#pragma once
#include <iostream>
#include <list>
#include <string.h>
#include <algorithm> // find()

//��ʶ��
class IdNode {
public:
	IdNode(const char *s = "", double e = 0) {
		id = _strdup(s);//strdup����Ϊid����ռ�
		value = e;
	}
	bool operator== (const IdNode& node) const {
		return strcmp(id, node.id) == 0;
	}
private:
	char *id;        //������
	double value;//ֵ
	friend class Statement;
	friend std::ostream& operator<< (std::ostream& out, const IdNode& r);
};
//���ʽ
class Statement {
public:
	Statement() {}
	void getStatement();
private:
	std::list<IdNode> idList;
	char  ch;                   //��ʾ����
	double factor();        //����
	double term();          //�� 
	double expression();//���ʽ
	void readId(char*);  //��ȡ
	void issueError(const char *s) {
		std::cerr << s << std::endl; 
		exit(1);
	}
	double findValue(char*);
	void  processNode(char*, double);
	friend std::ostream& operator<< (std::ostream& out, const Statement& s);
};
