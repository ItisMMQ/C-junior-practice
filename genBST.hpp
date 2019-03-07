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
		preorder(root);//迭代VLR
	}
	void inorder() {
		inorder(root);//迭代LVR
	}
	void postorder() {
		postorder(root);//迭代LRV
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
	void deleteByCopying(BSTNode<T>*&);//复制删除
	void findAndDeleteByCopying(const T&);//复制删除
	void deleteByMerging(BSTNode<T>*&);//合并删除1步
	void findAndDeleteByMerging(const T&);//合并删除2步
	void iterativePreorder();//非迭代VLR
	void iterativeInorder();//非迭代LVR
	void iterativePostorder();//非迭代LRV
	void breadthFirst();//广度优先遍历
	void MorrisPreorder();
	void MorrisInorder();//转换遍历
	void MorrisPostorder();
	void balance(T*, int, int);//树的平衡
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
//迭代LVR
template<class T>
void BST<T>::inorder(BSTNode<T> *p) {
	if (p != 0) {
		inorder(p->left);
		visit(p);
		inorder(p->right);
	}
}
//迭代VLR
template<class T>
void BST<T>::preorder(BSTNode<T> *p) {
	if (p != 0) {
		visit(p);
		preorder(p->left);
		preorder(p->right);
	}
}
//迭代LRV
template<class T>
void BST<T>::postorder(BSTNode<T>* p) {
	if (p != 0) {
		postorder(p->left);
		postorder(p->right);
		visit(p);
	}
}
//插入节点
template<class T>
inline void BST<T>::insert(const T &el)
{
	BSTNode<T>* p = root, *prev = 0;
	//如果有子节点
	while (p != 0) {
		prev = p; 
		if (el < p->el)
			p = p->left;
		else
			p = p->right;
	}
	//如果没有根节点
	if (root == 0)
		root = new BSTNode<T>(el);
	else if (el < prev->el)//如果只有根节点
		prev->left = new BSTNode<T>(el);
	else prev->right = new BSTNode<T>(el);
}
//复制删除
template<class T>
inline void BST<T>::deleteByCopying(BSTNode<T>*& node)
{
	BSTNode<T>* prev, *tmp = node;
	if (node->right == 0)
		node = node->left;
	else
		if (node->left == 0)
			node = node->right;
		else {                                       //如果待删节点有左右两子树
			tmp = node->left;
			prev = node;
			while (tmp->right != 0) {   //找待删节点左子树的最右节点
				prev = tmp;
				tmp = tmp->right;
			}
			node->el = tmp->el;
			if (prev == node)
				prev->left = tmp->left;  //这里node=prev=tmp
			else
				prev->right = tmp->left;
		}
		delete tmp;
}
//合并删除1
template<class T>
inline void BST<T>::deleteByMerging(BSTNode<T>*& node)
{
	BSTNode<T> *tmp = node;
	if (node != 0) {
		if (!node->right)                     //若待删节点无右子节点
			node = node->left;             //将待删节点替换为其左子节点
		else if (node->left == 0)        //若待删节点无左子节点
			node = node->right;          //将待删节点替换为其右子节点
		else {                                     //若待删节点有左右两节点
			tmp = node->left;
			while (tmp->right != 0)     //若待删节点的左子节点有右子节点
				tmp = tmp->right;          
			tmp->right = node->right;
			tmp = node;
			node = node->left;            //原节点被其左子节点代替
		}  
		delete tmp;
	}
}
//合并删除2
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
//非迭代VLR
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
//非迭代LVR
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
//非迭代LRV
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
//广度优先遍历
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
//转换遍历
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
//树的平衡
template<class T>
inline void BST<T>::balance(T data[], int, int) {
	if (first <= last) {
		int middle = (first + last) / 2;// 个人认为：原始数据流必须是以0开头的连续数据流
		insert(data[middle]);	          //否则数组下标引用会失效
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