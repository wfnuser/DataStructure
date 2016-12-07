//100*100的稀疏矩阵的元素值的范围为1~1000之间的整型数。试利用随机函数按1%的非0元素的概率生成这个矩阵，每个非0元素以一个三元素组表示（行号、列号、
//元素值），并将矩阵存入闭散列表中。并检验最后生成的非0元素的个数是否为1%
#include <iostream>
#include <stdlib.h>     //srand, rand
#include <time.h>   //time
using namespace std;
void matrix();
template <class T>
class hashTable
{
public:
  //virtual bool find(const T&x) const = 0;
  virtual bool insert (const T&x) = 0;
  //virtual bool remove(const T&x) = 0;
  int (*key)(const T&x);
  static int defaultKey(const int &k) {return k;}
};

template <class T>
class closeHashTable:public hashTable<T>
{
private:
  struct node
  {
    T data;
    int state;
    node() {state = 0;}
  };
  node *array;
  int size;
  int (*key)(const T&x);
  static int defaultKey(const T &k) {return k;}
public:
  closeHashTable (int length = 101, int (*f)(const T&x) = defaultKey);
  ~closeHashTable() {delete []array;}
 // virtual bool find(const T&x) const = 0;
  bool insert (const T&x);
 // virtual bool remove(const T&x) = 0;
  //virtual rehash() = 0;
};

template <class T>
closeHashTable<T>::closeHashTable (int length, int (*f)(const T&x)) //f is a pointer pointing to a function with one parameter x of type T
{
  size = length;
  array = new node[size];
  key = f;   // the function that turns key into index
}

template <class T>
bool closeHashTable<T>::insert(const T&x)
{
  int initPos, pos;
  initPos = pos = key(x) % size;
  do{
    if (array[pos].state != 1) //place available
    {
      array[pos].data = x;
      array[pos].state = 1;
      return true;
    }
    if (array[pos].state == 1 && array[pos].data == x) return true; //already exist
    //operator == must be overloaded to operate data == x
    pos = (pos + 1) % size;  //move to the next place
  } while (pos != initPos);
  return false;
}

template <class Type>
class matrix_entry// : public closeHashTable<T>
{
  friend int Get_key(const matrix_entry<Type> &entry);
  friend bool operator ==(const matrix_entry &a, const matrix_entry &b)
  {
    if (a.x == b.x && a.y == b.y && a.dataValue == b.dataValue) return 1;
    else return 0;
  }
public:
  int x, y;
private:
  Type dataValue;

public:
  matrix_entry(int r = 0, int c = 0, Type value = NULL):x(r), y(c), dataValue(value){}
};

template<class Type>
int Get_key(const matrix_entry<Type> &entry){return 100*entry.x+entry.y;}

void matrix()
{
  int elem[100][100];
  typedef matrix_entry<int> matrix_elements;

  closeHashTable < matrix_elements > mat(131, Get_key); //length should be a prime number bigger than 100
  int row(0), column, keyValue;
  srand (time(NULL));
  while(row < 100)
  {
    keyValue = 1000*rand();
    if (keyValue == 0) continue;
    column = 100*rand();
    matrix_elements element(row, column, keyValue);
    mat.insert(element);
    row++;
  }
}

int main()
{
  matrix();
  return 0;
}
