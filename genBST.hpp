#pragma once
//************************  genBST.h  **************************
//generic binary search tree

#include <queue>
#include <stack>

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

template<class T>
class Stack : public stack<T> {
public:
	T pop() {
		T tmp = top();
		stack<T>::pop();
		return tmp;
	}
};

template<class T>
class Queue : public queue<T> {
public:
	T dequeue() {
		T tmp = front();
		queue<T>::pop();
		return tmp;
	}
	void enqueue(const T& el) {
		push(el);
	}
};

template<class T>
class BSTNode {
public:
	BSTNode() {
		left = right = 0;
	}
	BSTNode(const T& e, BSTNode<T> *l = 0, BSTNode<T> *r = 0) {
		el = e; left = l; right = r;
	}
	T el;
	BSTNode<T> *left, *right;
};

template<class T>
class BST {
public:
	BST() {
		root = 0;
	}
	~BST() {
		clear();
	}
	void clear() {
		clear(root);
		root = 0;
	}
	bool isEmpty() const {
		return root == 0;
	}
	void preorder() {
		preorder(root);//����VLR
	}
	void inorder() {
		inorder(root);//����LVR
	}
	void postorder() {
		postorder(root);//����LRV
	}
	void insert(const T&);
	void recursiveInsert(const T& el) {
		recursiveInsert(root, el);
	}
	T* search(const T& el) const {
		return search(root, el);
	}
	T* recursiveSearch(const T& el) const {
		return recursiveSearch(root, el);
	}
	void deleteByCopying(BSTNode<T>*&);//����ɾ��
	void findAndDeleteByCopying(const T&);//����ɾ��
	void deleteByMerging(BSTNode<T>*&);//�ϲ�ɾ��1��
	void findAndDeleteByMerging(const T&);//�ϲ�ɾ��2��
	void iterativePreorder();//�ǵ���VLR
	void iterativeInorder();//�ǵ���LVR
	void iterativePostorder();//�ǵ���LRV
	void breadthFirst();//������ȱ���
	void MorrisPreorder();
	void MorrisInorder();//ת������
	void MorrisPostorder();
	void balance(T*, int, int);//����ƽ��
protected:
	BSTNode<T>* root;
	void clear(BSTNode<T>*);
	void recursiveInsert(BSTNode<T>*&, const T&);
	T* search(BSTNode<T>*, const T&) const;
	T* recursiveSearch(BSTNode<T>*, const T&) const;
	void preorder(BSTNode<T>*);
	void inorder(BSTNode<T>*);
	void postorder(BSTNode<T>*);
	virtual void visit(BSTNode<T>* p) {
		cout << p->el << ' ';
	}
};

template<class T>
T* BST<T>::search(BSTNode<T>* p, const T& el) const {
	while (p != 0)
		if (el == p->el)
			return &p->el;
		else if (el < p->el)
			p = p->left;
		else p = p->right;
		return 0;
}
//����LVR
template<class T>
void BST<T>::inorder(BSTNode<T> *p) {
	if (p != 0) {
		inorder(p->left);
		visit(p);
		inorder(p->right);
	}
}
//����VLR
template<class T>
void BST<T>::preorder(BSTNode<T> *p) {
	if (p != 0) {
		visit(p);
		preorder(p->left);
		preorder(p->right);
	}
}
//����LRV
template<class T>
void BST<T>::postorder(BSTNode<T>* p) {
	if (p != 0) {
		postorder(p->left);
		postorder(p->right);
		visit(p);
	}
}
//����ڵ�
template<class T>
inline void BST<T>::insert(const T &el)
{
	BSTNode<T>* p = root, *prev = 0;
	//������ӽڵ�
	while (p != 0) {
		prev = p; 
		if (el < p->el)
			p = p->left;
		else
			p = p->right;
	}
	//���û�и��ڵ�
	if (root == 0)
		root = new BSTNode<T>(el);
	else if (el < prev->el)//���ֻ�и��ڵ�
		prev->left = new BSTNode<T>(el);
	else prev->right = new BSTNode<T>(el);
}
//����ɾ��
template<class T>
inline void BST<T>::deleteByCopying(BSTNode<T>*& node)
{
	BSTNode<T>* prev, *tmp = node;
	if (node->right == 0)
		node = node->left;
	else
		if (node->left == 0)
			node = node->right;
		else {                                       //�����ɾ�ڵ�������������
			tmp = node->left;
			prev = node;
			while (tmp->right != 0) {   //�Ҵ�ɾ�ڵ������������ҽڵ�
				prev = tmp;
				tmp = tmp->right;
			}
			node->el = tmp->el;
			if (prev == node)
				prev->left = tmp->left;  //����node=prev=tmp
			else
				prev->right = tmp->left;
		}
		delete tmp;
}
//�ϲ�ɾ��1
template<class T>
inline void BST<T>::deleteByMerging(BSTNode<T>*& node)
{
	BSTNode<T> *tmp = node;
	if (node != 0) {
		if (!node->right)                     //����ɾ�ڵ������ӽڵ�
			node = node->left;             //����ɾ�ڵ��滻Ϊ�����ӽڵ�
		else if (node->left == 0)        //����ɾ�ڵ������ӽڵ�
			node = node->right;          //����ɾ�ڵ��滻Ϊ�����ӽڵ�
		else {                                     //����ɾ�ڵ����������ڵ�
			tmp = node->left;
			while (tmp->right != 0)     //����ɾ�ڵ�����ӽڵ������ӽڵ�
				tmp = tmp->right;          
			tmp->right = node->right;
			tmp = node;
			node = node->left;            //ԭ�ڵ㱻�����ӽڵ����
		}  
		delete tmp;
	}
}
//�ϲ�ɾ��2
template<class T>
inline void BST<T>::findAndDeleteByMerging(const T &te)
{
	BSTNode<T> *node = root, *prev = 0;
	while (node != 0) {
		if (node->el != te)
			break;
		prev = node;
		if (node->el < te)
			node = node->right;
		else node = node->left;
	}
	if (node != 0 && node->el == te)
		if (node == root)
			deleteByMerging(root);
		else 
			if (prev->left == node)
				deleteByMerging(prev->left);
			else 
				deleteByMerging(prev->right);
	else
		if (root != 0)
		cout << "el" << te << "is not in the tree\n";
		else
		cout << "the tree is empty\n";
}
//�ǵ���VLR
template<class T>
void BST<T>::iterativePreorder() {
	Stack<BSTNode<T>*> travStack;
	BSTNode<T> *p = root;
	if (p != 0) {
		travStack.push(p);
		while (!travStack.empty()) {
			p = travStack.pop();
			visit(p);
			if (p->right != 0)
				travStack.push(p->right);
			if (p->left != 0)             // left child pushed after right
				travStack.push(p->left); // to be on the top of the stack;
		}
	}
}
//�ǵ���LVR
template<class T>
void BST<T>::iterativeInorder() {
	Stack<BSTNode<T>*> travStack;
	BSTNode<T> *p = root;
	while (p != 0) {
		while (p != 0) {                         //stack the right child (if any)
			if (p->right)             
				travStack.push(p->right); //and the node itself when going
			travStack.push(p);
			p = p->left;                           // to the left
		}
		p = travStack.pop();                  //pop a node with no left child 
		while (!travStack.empty() && p->right == 0) { 
			visit(p);                                 //visit it,and all node with no right child
			p = travStack.pop();
		}
		visit(p);                                     //visit also the first node with a right child (if any)
		if (!travStack.empty())              
			p = travStack.pop();
		else p = 0;
	}
}
//�ǵ���LRV
template<class T>
void BST<T>::iterativePostorder() {
	Stack<BSTNode<T>*> travStack;
	BSTNode<T>* p = root, *q = root;
	while (p != 0) {
		for (; p->left != 0; p = p->left)
			travStack.push(p);
		while (p->right == 0 || p->right == q) {
			visit(p);
			q = p;
			if (travStack.empty())
				return;
			p = travStack.pop();
		}
		travStack.push(p);
		p = p->right;
	}
}
//������ȱ���
template<class T>
void BST<T>::breadthFirst() {
	Queue<BSTNode<T>*> queue;
	BSTNode<T> *p = root;
	if (p != 0) {
		queue.enqueue(p);
		while (!queue.empty()) {
			p = queue.dequeue();
			visit(p);
			if (p->left != 0)
				queue.enqueue(p->left);
			if (p->right != 0)
				queue.enqueue(p->right);
		}
	}
}
//ת������
template<class T>
inline void BST<T>::MorrisInorder()
{
	BSTNode<T>* p = root, *tmp;
	while(p!=0)
		if (p->left == 0) {
			visit(p);
			p = p->right;
		}
		else {
			tmp = p->left;
			while (tmp->right != 0 && tmp->right != p)
				tmp = tmp->right;
			if (tmp->right == 0) {
				tmp->right = p; 
				p = p->left;
			}
			else {
				visit(p);
				tmp->right = 0;
				p = p->right;
			}
		}
}
//����ƽ��
template<class T>
inline void BST<T>::balance(T data[], int, int) {
	if (first <= last) {
		int middle = (first + last) / 2;// ������Ϊ��ԭʼ��������������0��ͷ������������
		insert(data[middle]);	          //���������±����û�ʧЧ
		balance(data, first, --middle);
		balance(data, ++middle, last);
	}
}


template<class T>
void moveDown(T data[], int first, int last) {
	int largest = 2 * first + 1;
	while (largest <= last) {
		if (largest < last&&data[largest] < data[largest + 1])
			++largest;
		if (data[first] < data[largest]) {
			swap(data[first], data[largest]);
			first = largest;
			largest = 2 * first + 1;
		}
		else largest = last + 1;
	}
}
#endif