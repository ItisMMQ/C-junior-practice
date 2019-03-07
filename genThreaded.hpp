#pragma once
//******************genThreaded.h******************//
// Generic binary search threaded tree

#ifndef  THREADED_TREE 
#define THREADED_TREE

template<class T>
class ThreadedNode {
public:
	ThreadedNode() {
		left = right = 0;
	}
	ThreadedNode(const T& el, ThreadedNode *l = 0, ThreadedNode *r = 0) {
		key = el; left = l; right = r; successor = 0;
	}
	T key;
	ThreadedNode *left, *right;
	unsigned int successor : 1;//位域，successor仅占一个bit
	//为了使机器字节对对齐，操作系统肯定会给一个比特位填充额外的位
};

template<class T>
class ThreadedTree {
public:
	ThreadedTree() {
		root = 0;
	}
	void clear() {
		clear(root); root = 0;
	}
	~ThreadedTree() {
		clear();
	}
	void virtual visit(ThreadedNode<T>* p) {
		cout << p->key << " ";
	}
	void preorder();
	void inorder();
	void postorder();
	void insert(const T&);
protected:
	ThreadedNode<T>* root;
	void clear(ThreadedNode<T>*);
};
#endif // ! THREADED_TREE 
//插入节点
template<class T>
inline void ThreadedTree<T>::insert(const T &el)
{
	ThreadedNode<T>*p, *prev = 0, *newNode;
	newNode = new ThreadedNode<T>(el);
	if (root == 0) {
		root = newNode;
		return;
	}
	p = root;
	while (p != 0) {
		prev = p;
		if (p->key > el)                   //若当前节点值大于带插入节点值
			p = p->left;                     //指向左子节点
		else if (p->successor == 0)//若当前节点值小于带插入节点值且无后继
			p = p->right;                  //指向右子节点
		else                                    //若当前节点值小于带插入节点值且有后继，跳出
			break;
	}
	if (prev->key > el) {              //若根节点值大于带插入节点值
		prev->left = newNode;     //将新节点插至根节点左侧
		newNode->successor = 1;//新节点后继置1
		newNode->right = prev;   //新节点的右子叶是根节点
	}
	else if (prev->successor == 1) {//若根节点值小于带插入节点值且有后继
		newNode->successor = 1;     //新节点后继置1
		prev->successor =0;               //根节点后继置0
		newNode->right = prev->right;//将根节点原右子节点作为新节点的右子节点
		prev->right = newNode;           //根节点的右子节点更新为新插入节点
	}
	else
	{
		prev->right = newNode;//不用将successor置1吗
		//prev->successor = 1;
	}
}
//线索LVR
template<class T>
void ThreadedTree<T>::inorder() {
	ThreadedNode<T>*prev, *p = root;
	if (p != 0) {
		while (p->left != 0)
			p = p->left;
		while (p != 0) {
			cout<<*p.el;//visit(p);
			prev = p;
			p = p->right;
			if (p != 0 && prev->successor == 0)
				while (p->left != 0)
					p = p->left;
			//以下是自己加的
			
		}
	}
}