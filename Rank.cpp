// Rank.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "effesort.hpp"
#include "STL_sort.hpp"


using namespace std;
int main()
{ 
	/*int arr[] = { 3,4,7,8,6,5,10 };
	heapsort(arr, 7);
	for (auto &a:arr)
		cout << a << '\n';*/
	/*long arr2[] = { 12,654,1234,74,134,67,769,134,6,6789 };
	radixsort2(arr2, 9);
	for (auto &a : arr2)
		cout << a << '\n';
	cout << '\n';*/
	long arr3[] = { 23,64,1246,658,1000,347,582,14,8634,87,31 ,674};
	for (auto &a : arr3)
		cout << a << '\t';
	cout << '\n';
	bitRadixsort(arr3, 11,16);
	for (auto &a : arr3)
		cout << a << '\t';
	//标准模板库排序
	/*int a[] = { 1,4,3,6,7,2,5 }, i;
	vector<int> v1(a, a + 7), v2(a, a + 7), v3(6, 9), v4(6, 9);
	vector<int>::iterator i1, i2, i3, i4;
	partial_sort(v1.begin(), v1.begin() + 3, v1.end());
	printVector("v1", v1);                    // v1 = (1,2,3,6,7,4,5)
	partial_sort(v2.begin() + 1, v2.begin() + 4, v2.end(), greater<int>());
	printVector("v2", v2);                    // v2 = (1,7,6,5,3,2,4)
	i3 = partial_sort_copy(v2.begin(), v2.begin() + 4, v3.begin(), v3.end());
	printVector("v3", v3);                    // v3 = (1,5,6,7,9,9)
	cout << *(i3 - 1) << ' ' << *i3 << endl;   // 7 9
	i4 = partial_sort_copy(v1.begin(), v1.begin() + 4, v4.begin(), v4.end(), greater<int>());
	printVector("v4", v4);                    // v4 = (6,3,2,1,9,9)
	cout << *(i4 - 1) << ' ' << *i4 << endl;   // 1 9
	i1 = partition(v1.begin(), v1.end(), f1);
	printVector("v1", v1);                    // v1 = (1,2,3,4,7,6,5)
	cout << *(i1 - 1) << ' ' << *i1 << endl;   // 4 7
	i2 = partition(v2.begin(), v2.end(), bind2nd(less<int>(), 5));
	printVector("v2", v2);                    // v2 = (1,4,2,3,5,6,7)
	cout << *(i2 - 1) << ' ' << *i2 << endl;   // 3 5
	sort(v1.begin(), v1.end());
	printVector("v1", v1);                    // v1 = (1,2,3,4,5,6,7)
	sort(v1.begin(), v1.end(), greater<int>());
	printVector("v1", v1);                    // v1 = (7,6,5,4,3,2,1)
	vector<Person> pv1, pv2;
	for (i = 0; i < 20; i++) {
		pv1.push_back(Person("Josie", 60 - i));
		pv2.push_back(Person("Josie", 60 - i));
	}
	printVector("pv1", pv1);       // pv2 = ((Josie,60) ... (Josie,41))
	sort(pv1.begin(), pv1.end());
	printVector("pv1", pv1);       // pv1 = ((Josie,41) ... (Josie,60))
	printVector("pv2", pv2);       // pv2 = ((Josie,60) ... (Josie,41))
	stable_sort(pv2.begin(), pv2.end());
	printVector("pv2", pv2);       // pv2 = ((Josie,60) ... (Josie,41))

	vector<int> heap1, heap2, heap3(a, a + 7), heap4(a, a + 7);
	for (i = 1; i <= 7; i++) {
		heap1.push_back(i);
		push_heap(heap1.begin(), heap1.end());
		printVector("heap1", heap1);
	}
	// heap1 = (1)
	// heap1 = (2,1)
	// heap1 = (3,1,2)
	// heap1 = (4,3,2,1)
	// heap1 = (5,4,2,1,3)
	// heap1 = (6,4,5,1,3,2)
	// heap1 = (7,4,6,1,3,2,5)
	sort_heap(heap1.begin(), heap1.end()); // heap1 = (1,2,3,4,5,6,7)
	printVector("heap1", heap1);
	for (i = 1; i <= 7; i++) {
		heap2.push_back(i);
		push_heap(heap2.begin(), heap2.end(), greater<int>());
		printVector("heap2", heap2);
	}
	// heap2 = (1)
	// heap2 = (1,2)
	// heap2 = (1,2,3)
	// heap2 = (1,2,3,4)
	// heap2 = (1,2,3,4,5)
	// heap2 = (1,2,3,4,5,6)
	// heap2 = (1,2,3,4,5,6,7)
	sort_heap(heap2.begin(), heap2.end(), greater<int>());
	printVector("heap2", heap2);           // heap2 = (7,6,5,4,3,2,1)
	make_heap(heap3.begin(), heap3.end());
	printVector("heap3", heap3);           // heap3 = (7,6,5,1,4,2,3)
	sort_heap(heap3.begin(), heap3.end());
	printVector("heap3", heap3);           // heap3 = (1,2,3,4,5,6,7)
	make_heap(heap4.begin(), heap4.end(), greater<int>());
	printVector("heap4", heap4);           // heap4 = (1,4,2,6,7,3,5)
	sort_heap(heap4.begin(), heap4.end(), greater<int>());
	printVector("heap4", heap4);	          // heap4 = (7,6,5,4,3,2,1)
	*/
	//多项式相加
	//Polynomial polyn1, polyn2;
	//cout << "Enter two polynomials, each ended with a semicolon:\n";
	//cin >> polyn1 >> polyn2;
	//cout << "The result is:\n" << polyn1 + polyn2;
	cout << endl;
	int start();
	start();
	system("pause");
	return 0;
}

int foo(int a, int b){
	if (b == 0) { cout << "a= " << a << " b= " << b << endl; return 0; }
	if (b % 2 == 0) { cout << "a= " << a << " b%2= " << b << endl; return foo(a + a, b / 2); }
	cout << "a= " << a << endl;
	return foo(a + a, b / 2) + a;
	}