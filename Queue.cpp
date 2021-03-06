// Queue.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
//#include <deque>
#include <queue>
#include <list>
#include <functional>
#include <algorithm>

using namespace::std;

int main()
{
	//P121,program4-6
	/*queue<int> q1;
	queue<int, list<int>>q2;
	q1.push(1); q1.push(2); q1.push(3);
	q2.push(4); q2.push(5); q2.push(6);
	q1.push(q2.back());
	while (!q1.empty()) {
		cout << q1.front() << ' ';
		q1.pop();
	}
	cout << '\n';
	while (!q2.empty()) {
		cout << q2.front() << ' ';
		q2.pop();
	}*/
	//P122,program4-7
	/*priority_queue<int> pq1;
	priority_queue<int, vector<int>,greater<int>> pq2;
	pq1.push(3); pq1.push(1); pq1.push(2);
	pq2.push(3); pq2.push(1); pq2.push(2);
	int a[] = { 4,6,5 };
	priority_queue<int> pq3(a, a + 3);
	while (!pq1.empty()) {
		cout << pq1.top() << ' ';
			pq1.pop();
	}
	cout << '\n';
	while (!pq2.empty()) {
		cout << pq2.top() << ' ';
		pq2.pop();
	}
	cout << '\n';
	while (!pq3.empty()) {
		cout << pq3.top() << ' ';
		pq3.pop();
	}*/
	//P125,Program4-8
	deque<int> dq1;
	dq1.push_front(1);
	dq1.push_front(2);
	dq1.push_back(3);
	dq1.push_back(4);                                               //dq1={2,1,3,4};
	deque<int> dq2(dq1.begin() + 1, dq1.end() - 1);//dq2={1,3};
	dq1[1] = 5;                                                          //dq1={2,5,3,4};
	dq1.erase(dq1.begin());                                       //dq1={5,3,4};
	dq1.insert(dq1.end() - 1, 2, 6);                            //dq1={5,3,6,6,4};
	sort(dq1.begin(), dq1.end());                              //dq1={3,4,5,6,6};
	deque<int> dq3;
	dq3.resize(dq1.size() + dq2.size());
	merge(dq1.begin(), dq1.end(), dq2.begin(), dq2.end(), dq3.begin());
	for (auto &d : dq3)                                             //dq13={1,3,3,4,5,6,6};
		cout << d << '\t';
	system("pause");
	return 0;
}
