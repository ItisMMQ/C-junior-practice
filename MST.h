#pragma once

#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

//边集
class Edge{
	friend bool operator<(const Edge& E1, const Edge& E2){
		return E1.w < E2.w;
	}
	friend bool operator>(const Edge& E1, const Edge& E2){
		return E1.w > E2.w;
	}
public:
	Edge():Edge(0,0,0){}
	Edge(char a,char b,int c,int d):u(a),v(b),w(c),cap(d){}
	Edge(char a,char b, int c) :Edge(a,b,c,0){}
	Edge(char a, char b) :Edge(a,b,0,0) {}
	char u;    //起始顶点
	char v;    //终止顶点
	int w;      //边的权值，如代价
	int cap;   //容量
};

//顶点集
class Node{
public:
	char num;// 顶点编号
	int val;     // 顶点值
	Node() :num(0), val(' ') {}
	Node(char a):Node(a,0){}
	Node(char a, int b) :num(a),val(b) {}
};

//图
class Graph{
private:
	int vertex_nums;                            //顶点数
	int edge_nums;                               //边数Ss
	vector<Node> vertex;                    //顶点表，强制设为编号从0开始
	vector<Edge> edge;                       //边表
	vector<vector<int>> edge_maze;  //邻接矩阵，存储各个顶点连接关系
	bool WGraph;                                //有权图？
	bool digraphs;                                //有向图？
	bool isNet;                                      //网络图？
public:
	Graph(int n1);                                //顶点数
	Graph(int n1, int n2);                     //顶点数，边数
	void DFS(int v, vector<int>& nums, vector<Edge>&, int i);
	void DepthFirstSearch();                //深度优先遍历
	void BreadFirstSearch();                //广度优先遍历
	void DijkstraAlgorithm(char first);//最短路径--D算法
	void FordAlgorithm(char first);     //最短路径--F算法
	void print_edge_maze();                //打印邻接矩阵
	void print_edge_vec();                   //打印边表
};
