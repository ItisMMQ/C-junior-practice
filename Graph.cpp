// Graph.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
//#include "DFS.h"
#include "MST.h"

using namespace std;

int main()
{
	///*
	//CreateGraph();
	//std::cout << "result for bfs:" << std::endl;
	//bfs(0);
	//memset(visited, 0, sizeof(visited));
	//std::cout << "result for dfs(Recursion):" << std::endl;
//	dfs(0);
	//std::cout << std::endl;
	//memset(visited, 0, sizeof(visited));
	//std::cout << "result for nodfs(Recursion):" << std::endl;
	//dfs_noRecursion(0);
	//*/
	/*vector<string> chkBlood(string father, string mother);
	string f = "B", m = "A";
	vector<string> res;
	res=chkBlood(f, m);
	for (auto &r : res)
		cout << r << '\t';*/
	Graph g(10,14);
	g.print_edge_maze();
    g.print_edge_vec();
	g.DepthFirstSearch();
	g.BreadFirstSearch();
	g.DijkstraAlgorithm('d');
	g.FordAlgorithm('d');
	cout << endl;
	system("pause");
	return 0;
}

int findAppearance(string A, int lena, string B, int lenb) {
	// write code here
	for (int i = 0; i < lena; ++i) {
		if (A.compare(i, lenb, B)==0)
			return i;	
	}
	return -1;
}

vector<string> chkBlood(string father, string mother) {
	// write code here
	vector<string> res; 
	int lenf = father.size(), lenm = mother.size();
	int f = father.compare("A");
	int m = mother.compare("A");
	switch (f) {
	case 0: {//A型血
		res.push_back("A");
		if (mother == "AB") {
			res.push_back("AB");
			res.push_back("B");
			break;
		}
		else if (mother == "B")
		{
			res.push_back("AB");
			res.push_back("B");
		}
		res.push_back("O");
		break;
	}
	case 1: {//AB型血
		res.push_back("A");
		res.push_back("B");
		if (m == 1)
			res.push_back("AB");
		break;
	}
	case -1:{//O型或B型血
		if (father == "B")
		{
			res.push_back("B");
			if (mother=="A") {
				res.push_back("A");
				res.push_back("AB");
				res.push_back("O");
				break;
			}
			else if (mother=="AB") {
				res.push_back("A");
				res.push_back("AB");
				break;
			}
			else
				res.push_back("O");
		}
		else{
			if (mother == "A") {
				res.push_back("A");
			}
			else	if (mother == "AB") {				
					res.push_back("A");				
					res.push_back("B");
			}
			else	if (mother == "B")			
						res.push_back("B");
			res.push_back("O");
			break;
		}
	}
	}
	std::sort(res.begin(), res.end());		
	return res;
}