//**************************  interpreter.h   ***********************
#pragma once
#include <iostream>
#include <list>
#include <string.h>
#include <algorithm> // find()

//标识符
class IdNode {
public:
	IdNode(const char *s = "", double e = 0) {
		id = _strdup(s);//strdup可以为id分配空间
		value = e;
	}
	bool operator== (const IdNode& node) const {
		return strcmp(id, node.id) == 0;
	}
private:
	char *id;        //变量名
	double value;//值
	friend class Statement;
	friend std::ostream& operator<< (std::ostream& out, const IdNode& r);
};
//表达式
class Statement {
public:
	Statement() {}
	void getStatement();
private:
	std::list<IdNode> idList;
	char  ch;                   //表示符？
	double factor();        //因子
	double term();          //项 
	double expression();//表达式
	void readId(char*);  //读取
	void issueError(const char *s) {
		std::cerr << s << std::endl; 
		exit(1);
	}
	double findValue(char*);
	void  processNode(char*, double);
	friend std::ostream& operator<< (std::ostream& out, const Statement& s);
};
