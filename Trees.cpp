// Trees.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "genThreaded.hpp"
using namespace std;

int main()
{
	int a = 0, b1 = 1, b2 = 2, c1 = 3, c2 = 4, c3 = 5, c4 =6;
	ThreadedNode<int>leaf1(c1),leaf2(c2),leaf3(c3),leaf4(c4);                  //所有叶子
	ThreadedNode<int>bch1(b1,&leaf1,&leaf2),bch2(b2,&leaf3,&leaf4);//所有树枝
	ThreadedNode<int>root(a, &bch1,&bch2);                                           //根
	ThreadedTree<int> tree;
	tree.inorder();
	system("pause");
    return 0;
}

