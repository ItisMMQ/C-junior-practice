#include "stdafx.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

//��������
class Variable {
public:
	char id;          //������ӣ���x,y
	int exp;          //ָ��          
	Variable() { }//<vector>Ҫ��;
	Variable(char c, int i) {
		id = c; exp = i;
	}
	bool operator== (const Variable& v) const {
		return id == v.id  && exp == v.exp;
	}
	bool operator< (const Variable& v) const {//����sort();
		return id < v.id;
	}
};
//ÿ����
class Term {
public:
	Term() {
		coeff = 0;
	}
	int coeff;                                                        //ϵ��
	vector<Variable> vars;
	bool operator== (const Term&) const;
	bool operator!= (const Term& term) const {//<list>Ҫ��
		return !(*this == term);
	}
	bool operator< (const Term&) const;
	bool operator> (const Term& term) const { //<list>Ҫ��
		return *this != term && (*this < term);
	}
	int min(int n, int m) const {
		return (n < m) ? n : m;
	}
};
//��������ʽ
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
// ������б�����ͬ�Ҷ�Ӧ����������ͬ����������ȡ�
//����һ��Ľڵ�ĵ�һ����Ԫ�񽫱��ų��ڱȽ�֮�⣬��Ϊ���洢���Ǹ����ϵ��;
bool Term::operator== (const Term& term) const {
	int i;
    int minsize= min(vars.size(), term.vars.size());
	for (i = 0; i < minsize &&vars[i] == term.vars[i];++ i)
		;
	return i == vars.size() && vars.size() == term.vars.size();
	//�Ƚ���������ȼ������߼������
}
bool Term::operator< (const Term& term2) const {//����sort();
	if (vars.size() == 0)
		return false;                                                      // ����(*this)�Ǵ�����
	else if (term2.vars.size() == 0)
		return true;                                                       // term2�Ǵ�����
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
//����ʽ���
Polynomial Polynomial::operator+ (Polynomial& polyn2) {
	Polynomial result;
	list<Term>::iterator p1, p2;
	bool erased;
	for (p1 = terms.begin(); p1 != terms.end(); ++p1)
		result.terms.push_back(*p1) ;  //��p1��                  
	for (p1 = polyn2.terms.begin(); p1 != polyn2.terms.end(); ++p1)
		result.terms.push_back(*p1);   //polyn2����result��;
	for (p1 = result.terms.begin(); p1 != result.terms.end(); ) {
		for (p2 = p1, p2++, erased = false; p2 != result.terms.end(); ++p2)
			if (*p1 == *p2) {                  //����������
				p1->coeff += p2->coeff;  //�����ǵ�ϵ�����
				result.terms.erase(p2);     //����p2ɾ��
				if (p1->coeff == 0)          //����Ӻ�ϵ��Ϊ0
					result.terms.erase(p1);//��p1Ҳɾ��
				erased = true;                  //��ʾ���ɾ��
				break;
			}
		if (erased)                               //����������ɾ��
			p1 = result.terms.begin();  //���´�ͷ����
		else ++p1;                              //���򣬼����������
	}
	result.terms.sort();                     //��һ��˳��
	return result;
}

istream& operator>> (istream& in, Polynomial& polyn) {
	char ch, sign, coeffUsed, id;
	int exp;
	Term term;
	in >> ch;                                                           //����
	while (true) {
		coeffUsed = 0;
		if (!isalnum(ch) && ch != ';' && ch != '-' && ch != '+')
			polyn.error("Wrong character entered.");//����Ƿ��ַ�
		sign = 1;
		while (ch == '-' || ch == '+') {                       //���������Ƿ���
			if (ch == '-')
				sign *= -1;
			ch = in.get();                                            //����һ���ַ�
			if (isspace(ch))                                         //���������ǿո�
				in >> ch;                                              //������һ���ַ�
		}
		if (isdigit(ch)) {                                           //��������������
			in.putback(ch);                                        //�Ż�������
			in >> term.coeff;                                     //��Ϊϵ��
			ch = in.get();
			term.coeff *= sign;                                  //ϵ��ǰ���Ϸ���
			coeffUsed = 1;
		}
		else term.coeff = sign;                                //����ʹ��Ĭ��ϵ��
		int i;
		for (i = 0; isalnum(ch); ++i) {                    //��125��132�ж�����ǡ�
			id = ch;                                                   //����
			ch = in.get();
			if (isdigit(ch)) {                                     //ָ�������еĻ���
				in.putback(ch);
				in >> exp >> ch;                               //���ոյ�ָ��ֵ����exp�����ٶ�ȡһ��ch
			}
			else exp = 1;                                         //�����Ӻϳ���
			term.vars.push_back(Variable(id, exp));
		}
		polyn.terms.push_back(term);                //������������ʽ
		term.vars.resize(0);                                 //����ʱ��������Ա���һ���������
		if (isspace(ch))
			in >> ch;
		if (ch == ';')                                            //�Էֺ���Ϊ������־
			if (coeffUsed || i > 0)
				break;
			else polyn.error("Term is missing");  // e.g., 2x - ; ��ֻ�� ';'
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
		if (pol->coeff < 0)                        //���ϵ��С��0���ӡһ������
			out.put('-');              
		else if (afterFirstTerm)                //����ϵ����д+
			out.put('+');                           
		++afterFirstTerm;
		if (abs(pol->coeff) != 1)              //���ϵ������1
			out << ' ' << abs(pol->coeff);  //��ӡ���ϵ���ľ���ֵ
		else if (pol->vars.size() == 0)     //�������ֻ��һ��ϵ��
			out << " 1";                             //��ӡ���1
		else out.put(' ');                           //�������Ϊ��
		for (i = 1; i <= pol->vars.size(); ++i) {
			out << pol->vars[i - 1].id;       //���ÿһ��
			if (pol->vars[i - 1].exp != 1)   //������ָ��(����Ϊ1)
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