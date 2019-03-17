#include "stdafx.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

//单个变量
class Variable {
public:
	char id;          //项的因子，如x,y
	int exp;          //指数          
	Variable() { }//<vector>要用;
	Variable(char c, int i) {
		id = c; exp = i;
	}
	bool operator== (const Variable& v) const {
		return id == v.id  && exp == v.exp;
	}
	bool operator< (const Variable& v) const {//用于sort();
		return id < v.id;
	}
};
//每个项
class Term {
public:
	Term() {
		coeff = 0;
	}
	int coeff;                                                        //系数
	vector<Variable> vars;
	bool operator== (const Term&) const;
	bool operator!= (const Term& term) const {//<list>要用
		return !(*this == term);
	}
	bool operator< (const Term&) const;
	bool operator> (const Term& term) const { //<list>要用
		return *this != term && (*this < term);
	}
	int min(int n, int m) const {
		return (n < m) ? n : m;
	}
};
//完整多项式
class Polynomial{
public:
	Polynomial() {}
	Polynomial operator+ (Polynomial&);
	void error(char *s) {
		cerr << s << endl; exit(1);
	}
private:
	list<Term> terms;
	friend istream& operator>> (istream& in, Polynomial& polyn); 
	friend ostream& operator<< (ostream& out, const Polynomial& polyn); 
};
// 如果所有变量相同且对应变量的幂相同，则两项相等。
//包含一项的节点的第一个单元格将被排除在比较之外，因为它存储的是该项的系数;
bool Term::operator== (const Term& term) const {
	int i;
    int minsize= min(vars.size(), term.vars.size());
	for (i = 0; i < minsize &&vars[i] == term.vars[i];++ i)
		;
	return i == vars.size() && vars.size() == term.vars.size();
	//比较运算符优先级高于逻辑运算符
}
bool Term::operator< (const Term& term2) const {//用于sort();
	if (vars.size() == 0)
		return false;                                                      // 该项(*this)是纯数字
	else if (term2.vars.size() == 0)
		return true;                                                       // term2是纯数字
	for (int i = 0; i < min(vars.size(), term2.vars.size()); ++i)
		if (vars[i].id < term2.vars[i].id)
			return true;                                                  // *this < term2;
		else if (term2.vars[i].id < vars[i].id)
			return false;                                                // term2 > *this;
		else if (vars[i].exp < term2.vars[i].exp) 
			return true;                                                 // *this > term2;
		else if (term2.vars[i].exp < vars[i].exp)
			return false;                                               // term2 < *this;
	return ((int)vars.size() - (int)term2.vars.size() < 0) ? true : false;
}
//多项式相加
Polynomial Polynomial::operator+ (Polynomial& polyn2) {
	Polynomial result;
	list<Term>::iterator p1, p2;
	bool erased;
	for (p1 = terms.begin(); p1 != terms.end(); ++p1)
		result.terms.push_back(*p1) ;  //将p1和                  
	for (p1 = polyn2.terms.begin(); p1 != polyn2.terms.end(); ++p1)
		result.terms.push_back(*p1);   //polyn2拷到result中;
	for (p1 = result.terms.begin(); p1 != result.terms.end(); ) {
		for (p2 = p1, p2++, erased = false; p2 != result.terms.end(); ++p2)
			if (*p1 == *p2) {                  //如果两项相等
				p1->coeff += p2->coeff;  //则将它们的系数相加
				result.terms.erase(p2);     //并将p2删除
				if (p1->coeff == 0)          //若相加后系数为0
					result.terms.erase(p1);//则将p1也删除
				erased = true;                  //表示该项被删除
				break;
			}
		if (erased)                               //如果有任意项被删除
			p1 = result.terms.begin();  //重新从头搜索
		else ++p1;                              //否则，继续向后搜索
	}
	result.terms.sort();                     //捋一下顺序
	return result;
}

istream& operator>> (istream& in, Polynomial& polyn) {
	char ch, sign, coeffUsed, id;
	int exp;
	Term term;
	in >> ch;                                                           //输入
	while (true) {
		coeffUsed = 0;
		if (!isalnum(ch) && ch != ';' && ch != '-' && ch != '+')
			polyn.error("Wrong character entered.");//输入非法字符
		sign = 1;
		while (ch == '-' || ch == '+') {                       //如果输入的是符号
			if (ch == '-')
				sign *= -1;
			ch = in.get();                                            //输入一个字符
			if (isspace(ch))                                         //如果输入的是空格
				in >> ch;                                              //再输入一个字符
		}
		if (isdigit(ch)) {                                           //如果输入的是数字
			in.putback(ch);                                        //放回输入流
			in >> term.coeff;                                     //作为系数
			ch = in.get();
			term.coeff *= sign;                                  //系数前加上符号
			coeffUsed = 1;
		}
		else term.coeff = sign;                                //否则使用默认系数
		int i;
		for (i = 0; isalnum(ch); ++i) {                    //若125或132行读入的是…
			id = ch;                                                   //因子
			ch = in.get();
			if (isdigit(ch)) {                                     //指数（若有的话）
				in.putback(ch);
				in >> exp >> ch;                               //将刚刚的指数值传给exp，并再读取一个ch
			}
			else exp = 1;                                         //将因子合成项
			term.vars.push_back(Variable(id, exp));
		}
		polyn.terms.push_back(term);                //将该项加入多项式
		term.vars.resize(0);                                 //将临时变量清空以便下一个项的输入
		if (isspace(ch))
			in >> ch;
		if (ch == ';')                                            //以分号作为结束标志
			if (coeffUsed || i > 0)
				break;
			else polyn.error("Term is missing");  // e.g., 2x - ; 或只有 ';'
		else if (ch != '-' && ch != '+')                 // e.g., 2x  4y;
			polyn.error("wrong character entered");
	}
	for (list<Term>::iterator it = polyn.terms.begin(); it != polyn.terms.end(); ++it)
		if (it->vars.size() > 1)
			sort(it->vars.begin(), it->vars.end());
	return in;
}

ostream& operator<< (ostream& out, const Polynomial& polyn) {
	int afterFirstTerm = 0, i;
	for (list<Term>::const_iterator pol = polyn.terms.begin(); pol != polyn.terms.end(); ++pol) {
		out.put(' ');
		if (pol->coeff < 0)                        //如果系数小于0则打印一个负号
			out.put('-');              
		else if (afterFirstTerm)                //首项系数不写+
			out.put('+');                           
		++afterFirstTerm;
		if (abs(pol->coeff) != 1)              //如果系数不是1
			out << ' ' << abs(pol->coeff);  //打印输出系数的绝对值
		else if (pol->vars.size() == 0)     //如果该项只有一个系数
			out << " 1";                             //打印输出1
		else out.put(' ');                           //否则该项为空
		for (i = 1; i <= pol->vars.size(); ++i) {
			out << pol->vars[i - 1].id;       //输出每一项
			if (pol->vars[i - 1].exp != 1)   //和它的指数(不能为1)
				out << pol->vars[i - 1].exp;
		}
	}
	out << endl;
	return out;
}

int start() {
	Polynomial polyn1, polyn2;
	cout << "Enter two polynomials, each ended with a semicolon:\n";
	cin >> polyn1 >> polyn2;
	cout << "The result is:\n" << polyn1 + polyn2;
	return 0;
}