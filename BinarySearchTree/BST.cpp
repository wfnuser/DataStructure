/************************
author: wfnuser 2016/12/01 www.element14.site
title: Binary Search Tree
For DS
************************/

#include<iostream>
#include<cstdlib>
#include<cstdio>

using namespace std;

template <class T>
class BTree
{
    private:
        struct Node {
            T data;
            Node *left;
            Node *right;
            Node() : data(NULL), left(NULL), right(NULL) {}
            Node(T key) : data(key), left(NULL), right(NULL) {}
            Node(T key, Node *lt, Node *rt) : data(key), left(lt), right(rt){}
        };
        
    public:
        Node *root;
        BTree(Node *t = NULL):root(t) {};
        ~BTree() {};
        void insert(const T &key);
        void inOrder();
        void makeEmpty();
        void remove(const T &key);
        void removeBelow(const T &key);

    private:
        void insert(const T &key, Node *&t);
        void inOrder(Node *t) const;
        void makeEmpty(Node *&t);
        void remove(const T &key, Node *&t);
        void removeBelow(const T &key, Node *&t);
};

template <class T>
void BTree<T>::removeBelow(const T &key, Node *&t)
{
    if (t == NULL) return;
    if (t->data > key) removeBelow(key, t->left);
    else if (t->data == key) {
        makeEmpty(t->left);
    } else {
        Node *tmp = t;
        makeEmpty(t->left);
        t = t->right;
        delete tmp;
        removeBelow(key, t);
    }
}
template <class T>
void BTree<T>::removeBelow(const T &key) 
{
    return removeBelow(key,root);
}

template <class T>
void BTree<T>::remove(const T &key, Node *&t)
{
    if (t == NULL) return;
    if (t->data > key) remove(key, t->left);
    else if (t->data < key) remove(key, t->right);
    else if (t->left != NULL && t->right != NULL) {
        Node *tmp = t->right;
        while (tmp->left != NULL) tmp = tmp->left;
        t->data = tmp->data;
        remove(t->data,t->right);
    } else {
        Node *tmp = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete tmp;
    }
}
template <class T>
void BTree<T>::remove(const T &key) 
{
    return remove(key,root);
}

template <class T>
void BTree<T>::inOrder(Node *t) const
{
    if (t != NULL) {
        inOrder(t->left);
        cout<< t->data << " " ;
        inOrder(t->right);
    }
}
template <class T>
void BTree<T>::inOrder() 
{
    inOrder(root);
}

template <class T>
void BTree<T>::insert(const T &key, Node *&t)
{
  if (t == NULL) {t = new Node(key);}
  else {
    if (key < t->data) insert(key, t->left);
    else if (key > t->data) insert(key, t->right);
    else if (key == t->data) return;
  }
}
template <class T>
void BTree<T>::insert(const T &key) 
{
    return insert(key, root);
}

template <class T>
void BTree<T>::makeEmpty()
{
  makeEmpty(root);
}
template <class T>
void BTree<T>::makeEmpty(Node *&t)
{
  if (t->left != NULL) makeEmpty(t->left);
  if (t->right != NULL) makeEmpty(t->right);
  delete t;
}

int main()
{
    BTree<int> hmx;

    int a[10]={4,7,12,0,19,8,1,30,5,6};
    for (int i = 0; i < 10; i++) {
        hmx.insert(a[i]);
    }
    hmx.removeBelow(12);
    
    hmx.inOrder();
}

