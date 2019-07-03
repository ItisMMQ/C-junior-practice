#include "pch.h"
#include "MST.h"
#include <queue>
#include <iostream>
#include <cstring>
#include <limits.h>
using std::cout;
using std::endl;

//ͼ�ĳ�ʼ������������������
Graph::Graph(int n1, int n2){
	cout << "Is it a network?" << flush;
	cin >> isNet;    //�Ƿ�����ͼ
	if (isNet == 1){
		WGraph = 1;
		digraphs=1;
		bool b;
		cout<<"Is it a balanced network?"<<flush;
		cin >> b;
		if (b == 1)
			digraphs = 0;
	}
	else{
	cout << "Is it a Weight Graph?" << flush;
	cin >> WGraph;//�Ƿ���Ȩͼ
	cout << "Is it a digraphs? " << flush;
	cin >> digraphs;//�Ƿ�����ͼ
	}
	vertex_nums = n1;
	edge_nums = n2;
	for (int i = 0; i < vertex_nums; ++i) {
		Node a;
		a.num ='a'+ i;//��������,��α�Ϊ��ĸ��
		a.val = 0; //����ֵΪ0
		vertex.push_back(a);
	}
	for (int i = 0; i < vertex_nums; ++i) { 
		vector<int> temp(vertex_nums, 0);
		edge_maze.push_back(temp);        
	}//�ڽӾ����ʼ��Ϊ0����
	char v1, v2; int w, c = 0;
	if (WGraph == 0){//��Ȩͼ
		cout << "please input the edges about the graph: vertex_1, vertex_2" << endl;
		for (int i = 0; i < edge_nums; i++){
			cin >> v1 >> v2;
			Edge temp_edge(v1, v2);
			edge.push_back(temp_edge);
			edge_maze[v1 - 'a'][v2 - 'a'] = 1;
			if (digraphs == 0)
				edge_maze[v2 - 'a'][v1 - 'a'] = 1;
		}
	}
	else if(isNet==0){
		cout << "please input the edges about the graph: vertex_1, vertex_, weight" << endl;
		for (int i = 0; i < edge_nums; i++) {
				cin >> v1 >> v2 >> w;
				Edge temp_edge(v1, v2, w);
				edge.push_back(temp_edge);
				edge_maze[v1 - 'a'][v2 - 'a'] = 1;
				if (digraphs == 0)
					edge_maze[v2 - 'a'][v1 - 'a'] = 1;
			}
	}
	else {
		cout<< "please input the edges about the graph: vertex_1, vertex_2, weight and capacity" << endl;
		for (int i = 0; i < edge_nums; i++) {
			cin >> v1 >> v2 >> w>>c;
			Edge temp_edge(v1, v2, w,c);
			edge.push_back(temp_edge);
			edge_maze[v1 - 'a'][v2 - 'a'] = 1;
			if (digraphs == 0)
				edge_maze[v2 - 'a'][v1 - 'a'] = 1;
		}
	}	
}
//�ߵĳ�ʼ������������*****Ҫ��
Graph::Graph(int n1){
	bool WGraph =0;
	cout << "Is it a Weight Graph?" << flush;
	cin >> WGraph;//�Ƿ���Ȩͼ
	cout << "Is it a digraphs? " << flush;
	cin >> digraphs;//�Ƿ�����ͼ
	vertex_nums = n1;
	edge_nums = 0;
	for (int i = 0; i < vertex_nums; ++i) {
		Node a;
		a.num = i;//��������
		a.val = 0; //����ֵΪ0
		vertex.push_back(a);
	}
	for (int i = 0; i < vertex_nums; ++i) {
		vector<int> temp(vertex_nums, 0);
		edge_maze.push_back(temp);
	}//�ڽӾ����ʼ��Ϊ0����
	bool flag=0;
	cout <<"Enter 1 to start" << flush;
	 cin >> flag;	
	if (WGraph == 0)
		cout << "please input the edges about the graph: vertex_No.1, vertex_No.2" << endl;
	else
		cout << "please input the edges about the graph: vertex_No.1, vertex_No.2, weight" << endl;
	int x, y, z=0;
	while(flag==1) {
			if (WGraph == 1) {
				cin >> x >> y >> z;
				Edge temp_edge(x, y, z);
				edge.push_back(temp_edge);
			}
			else {
				cin >> x >> y;
				Edge temp_edge(x, y);
				edge.push_back(temp_edge);
			}
			edge_maze[x][y] = 1;
			if (digraphs == 0)//���������ͼ
				edge_maze[y][x] = 1;
		flag = 0;
		cout << "Press 1 to continue: " << flush;
		cin >> flag;
	}
}
//�ߵĳ�ʼ�������ļ����룩
/************************************/
/************************************/
//����ڽӾ���
void Graph::print_edge_maze(){
	cout << endl;
	cout << "����ڽӾ���" << endl;
	cout << "   ";
	for (int i = 0; i < vertex_nums; ++i) 
		cout << char('a'+ i) << " ";	
	cout << endl;
	for (int i = 0; i < vertex_nums; i++)
	{
		cout << char('a' + i) << " ";
		for (int j = 0; j < vertex_nums; j++)
		{
			cout << edge_maze[i][j] << "  ";
		}
		cout << endl;
	}
}
//����߼�
void Graph::print_edge_vec(){
	cout << endl;
	cout << "����߱�" << endl;
	cout << "��ʼ����-->��������  ��Ȩֵ" << endl;
	for (int i = 0; i < edge_nums; i++)
	{
		cout <<"    "<< edge[i].u << "   -->   " << edge[i].v << "            " << edge[i].w << endl;
	}
}
//������ȱ���֧�ֺ���
void Graph::DFS(int v, vector<int>& nums,vector<Edge>&tEdges, int i) {
	nums[v] = i++;
	for (int j = 0; j < vertex_nums; ++j){
		if (edge_maze[v][j] == 1)
			if (nums[j] == 0) {
				Edge edge(v+'a', j+'a');
				tEdges.push_back(edge);
				DFS(j, nums, tEdges, i);
			}
	}
	return;
}
//������ȱ���
void Graph::DepthFirstSearch(){
	cout << "DepthFirstSearch()" << endl;
	vector<int> nums(vertex_nums, 0);//��Ƕ����Ƿ񱻲���
	vector<Edge> tEdges;
	int i = 1;
	for (int  v = 0; v < vertex_nums; ++v){
		if (nums[v] == 0)
			DFS(v, nums, tEdges, i);
	}
	cout << "DFS�õ���������" << endl;
	for (auto &e : tEdges)
		cout << e.u << e.v << '\t';
	cout << endl;
}
//������ȱ���
void Graph::BreadFirstSearch() {
	cout << "BreadFirstSearch()" << endl;
	vector<int>nums(vertex_nums, 0);
	queue<int> q;
	vector<Edge> tEdges;
	int i = 1;
	for (int k=0;k<vertex_nums;++k)
		while (nums[k] == 0){
			nums[k] = i++;
			q.emplace(k);
			while (!q.empty()) {
				k = q.front();
				q.pop();
				for (auto e : edge) {
					if ((e.u-'a') == k&&nums[e.v-'a'] == 0) {
						nums[e.v-'a']++;
						q.emplace(e.v-'a');
					}
					else if ((e.v - 'a')== k&&nums[e.u-'a'] == 0) {
						nums[e.u-'a']++;
						q.emplace(e.u-'a');
					}
					else continue;
					tEdges.push_back(e);
				}
			}
		}
	cout << "BFS�õ���������" << endl;
	for (auto e : tEdges)
		cout << e.u << e.v << '\t';
	cout << endl;
}
/*
��������
0 2 
0 3
0 5
2 5
3 5
1 4
3 4
1 3
*/
//���·��
void Graph::DijkstraAlgorithm(char first = 'a') {
	cout << "DijkstraAlgorithm:" << endl;
	vector<int>currDist(vertex_nums, INT_MAX);
	vector<int>toBeChecked(vertex_nums, 0);//0������δ����
	currDist[first-'a'] = 0; 
	int n1, n2;
	while ((find(toBeChecked.cbegin(), toBeChecked.cend(), 0) )!= toBeChecked.cend()) {//��ToBeChecked�л���δ����Ԫ��
		int it = find(toBeChecked.cbegin(), toBeChecked.cend(), 0) - toBeChecked.cbegin();//��һ��δ���õ��ĵ���±�
		int t = currDist[it];
		for (int i = 0; i < vertex_nums; ++i) {		
			if (toBeChecked[i] == 0&& currDist[i] <= t){//�ҵ�ToBeChecked��currDist��С�Ķ���
				t= currDist[i];			
				n1= i;
			}
			else
				continue;
		}	
		toBeChecked[n1] = 1;			
		for (auto e : edge) {                                             //�Ըö���������ڱ߼������·��
			if (e.u == (n1+97)) 
				n2 =( e.v-'a');
			else if ((digraphs==0)&&(e.v ==(n1+97)))
				n2 = (e.u-'a');
			else
				continue;				
			if (currDist[n2] > (currDist[n1] + e.w)){
					currDist[n2] = currDist[n1] + e.w;}
			}
		}
	cout << "From vertex " << first << " to  " << "  shortest path is " << endl; ;
	for (int i = 0; i < vertex_nums; ++i)		
		cout << "\t\t " << char('a'+i) << " \t\t    " << currDist[i] << endl;
	cout << endl;
}
/*
��������
a d 4
a e 1
a h 10
d h 1
e h 5
e f 3
h i 9
b f 1
b c 2
c f 3
f g 7
f i 1
g j 1
i j 2
*/
void Graph::FordAlgorithm(char src ='a') {
	cout << "FordAlgorithm:" << endl;
	vector<unsigned> currDist(vertex_nums, INT_MAX);
	currDist[src-97]= 0;
	vector<int> viaNode; viaNode.reserve(vertex_nums);
	viaNode.push_back(src-'a');
	for (int i = 0; i <vertex_nums; ++i) {
		if (i ==(src-'a'))
			continue;
		viaNode.push_back(i);
	}
	int via, dest;
	for (int i = 0; i < vertex_nums; ++i) {
		via = viaNode[i];
		for (auto e : edge) {
			if (e.u == char(via+'a')) {
				dest = e.v-'a';
				if (currDist[dest] > currDist[via] + e.w) {
					currDist[dest] = currDist[via] + e.w;
				}
			}
			if (digraphs == 1)
				continue;
			else if (e.v ==char(via + 'a')){
				dest = e.u-'a';
				if (currDist[dest] > currDist[via] + e.w)
					currDist[dest] = currDist[via] + e.w;
			}
		}	
	}
	cout << "From vertex " << src << " to  " << "  shortest path is " << endl; ;
	for (int i = 0; i < vertex_nums; ++i)
		cout << "\t\t " << char('a'+i) << "\t\t    " << currDist[i] << endl;
	cout << endl;
}
//�����

//��ͳɱ��������
