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
	unsigned int successor : 1;//λ��successor��ռһ��bit
	//Ϊ��ʹ�����ֽڶԶ��룬����ϵͳ�϶����һ������λ�������λ
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
//����ڵ�
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
		if (p->key > el)                   //����ǰ�ڵ�ֵ���ڴ�����ڵ�ֵ
			p = p->left;                     //ָ�����ӽڵ�
		else if (p->successor == 0)//����ǰ�ڵ�ֵС�ڴ�����ڵ�ֵ���޺��
			p = p->right;                  //ָ�����ӽڵ�
		else                                    //����ǰ�ڵ�ֵС�ڴ�����ڵ�ֵ���к�̣�����
			break;
	}
	if (prev->key > el) {              //�����ڵ�ֵ���ڴ�����ڵ�ֵ
		prev->left = newNode;     //���½ڵ�������ڵ����
		newNode->successor = 1;//�½ڵ�����1
		newNode->right = prev;   //�½ڵ������Ҷ�Ǹ��ڵ�
	}
	else if (prev->successor == 1) {//�����ڵ�ֵС�ڴ�����ڵ�ֵ���к��
		newNode->successor = 1;     //�½ڵ�����1
		prev->successor =0;               //���ڵ�����0
		newNode->right = prev->right;//�����ڵ�ԭ���ӽڵ���Ϊ�½ڵ�����ӽڵ�
		prev->right = newNode;           //���ڵ�����ӽڵ����Ϊ�²���ڵ�
	}
	else
	{
		prev->right = newNode;//���ý�successor��1��
		//prev->successor = 1;
	}
}
//����LVR
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
			//�������Լ��ӵ�
			
		}
	}
}