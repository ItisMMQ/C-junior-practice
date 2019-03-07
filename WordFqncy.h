//****************************  genSplay.h  ****************************
//                     generic splaying tree class

#ifndef SPLAYING
#define SPLAYING

template<class T> class SplayTree;

template<class T>
class SplayingNode {
public:
	SplayingNode() {
		left = right = parent = 0;
	}
	SplayingNode(const T& el, SplayingNode *l = 0, SplayingNode *r = 0,
		SplayingNode *p = 0) {
		info = el; left = l; right = r; parent = p;
	}
	T info;                                               //当前节点
	SplayingNode *left, *right, *parent;//左、右子节点，前驱
};

template<class T>
class SplayTree {
public:
	SplayTree() { root = 0; }
	void inorder() { inorder(root); }
	T* search(const T&);
	void insert(const T&);
protected:
	SplayingNode<T> *root;
	void rotateR(SplayingNode<T>*);//右旋
	void rotateL(SplayingNode<T>*);//左旋
	void continueRotation(SplayingNode<T>* gr, SplayingNode<T>* par,
		SplayingNode<T>* ch, SplayingNode<T>* desc);
	void semisplay(SplayingNode<T>*);//半张开
	void inorder(SplayingNode<T>*);
	void virtual visit(SplayingNode<T>*) {   }
};

template<class T>
void SplayTree<T>::continueRotation(SplayingNode<T>* gr, SplayingNode<T>* par,
	SplayingNode<T>* ch, SplayingNode<T>* desc) {
	if (gr != 0) {                   //若有太爷
		if (gr->right == ch->parent)
			gr->right = ch;
		else gr->left = ch;
	}
	else root = ch;
	if (desc != 0)                  //若有曾孙
		desc->parent = par;
	par->parent = ch;          //都要运行
	ch->parent = gr;
}

template<class T>
void SplayTree<T>::rotateR(SplayingNode<T>* p) {
	p->parent->left = p->right;
	p->right = p->parent;
	continueRotation(p->parent->parent, p->right, p, p->right->left);
}

template<class T>
void SplayTree<T>::rotateL(SplayingNode<T>* p) {
	p->parent->right = p->left;
	p->left = p->parent;
	continueRotation(p->parent->parent, p->left, p, p->left->right);
}
//半张开
template<class T>
void SplayTree<T>::semisplay(SplayingNode<T>* p) {
	while (p != root) {
		if (p->parent->parent == 0)                                //若gar是根
			if (p->parent->left == p)                                 //若p是左子树
				rotateR(p);                                                   //右旋
			else rotateL(p);                                                //否则左旋
		else
			if (p->parent->left == p)                                  //若p是左子树		
				if (p->parent->parent->left == p->parent) {//且同构			
					rotateR(p->parent);                                  //则par右旋（半张开）			
					p = p->parent;
				}
				else {	                                                          //异构则全张开		
					rotateR(p); // rotate p and its parent;			
					rotateL(p); // rotate p and its new parent;		
				}
			else                                                                     //若p是右子树	
				if (p->parent->parent->right == p->parent) {//且同构					
					rotateL(p->parent);	                                   //则par左旋（半张开）			
					p = p->parent;
				}
				else {				                                               //异构则全张开		
					rotateL(p); // rotate p and its parent;				
					rotateR(p); // rotate p and its new parent;			
				}
				if (root == 0)// update the root;				
					root = p;
	}
}

template<class T>
T* SplayTree<T>::search(const T& el) {
	SplayingNode<T> *p = root;
	while (p != 0)
		if (p->info == el) {        // if el is in the tree,
			semisplay(p);            // move it upward;
			return &p->info;
		}
		else if (el < p->info)
			p = p->left;
		else p = p->right;
		return 0;
}

template<class T>
void SplayTree<T>::insert(const T& el) {
	SplayingNode<T> *p = root, *prev = 0, *newNode;
	while (p != 0) {  // find a place for inserting a new node;
		prev = p;
		if (el < p->info)
			p = p->left;
		else p = p->right;
	}
	if ((newNode = new SplayingNode<T>(el, 0, 0, prev)) == 0) {
		cerr << "No room for new nodes\n";
		exit(1);
	}
	if (root == 0)    // the tree is empty;
		root = newNode;
	else if (el < prev->info)
		prev->left = newNode;
	else prev->right = newNode;
}

template<class T>
void SplayTree<T>::inorder(SplayingNode<T> *p) {
	if (p != 0) {
		inorder(p->left);
		visit(p);
		inorder(p->right);
	}
}

#endif
