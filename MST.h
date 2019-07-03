#pragma once

#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>

using namespace std;

//�߼�
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
	char u;    //��ʼ����
	char v;    //��ֹ����
	int w;      //�ߵ�Ȩֵ�������
	int cap;   //����
};

//���㼯
class Node{
public:
	char num;// ������
	int val;     // ����ֵ
	Node() :num(0), val(' ') {}
	Node(char a):Node(a,0){}
	Node(char a, int b) :num(a),val(b) {}
};

//ͼ
class Graph{
private:
	int vertex_nums;                            //������
	int edge_nums;                               //����Ss
	vector<Node> vertex;                    //�����ǿ����Ϊ��Ŵ�0��ʼ
	vector<Edge> edge;                       //�߱�
	vector<vector<int>> edge_maze;  //�ڽӾ��󣬴洢�����������ӹ�ϵ
	bool WGraph;                                //��Ȩͼ��
	bool digraphs;                                //����ͼ��
	bool isNet;                                      //����ͼ��
public:
	Graph(int n1);                                //������
	Graph(int n1, int n2);                     //������������
	void DFS(int v, vector<int>& nums, vector<Edge>&, int i);
	void DepthFirstSearch();                //������ȱ���
	void BreadFirstSearch();                //������ȱ���
	void DijkstraAlgorithm(char first);//���·��--D�㷨
	void FordAlgorithm(char first);     //���·��--F�㷨
	void print_edge_maze();                //��ӡ�ڽӾ���
	void print_edge_vec();                   //��ӡ�߱�
};
