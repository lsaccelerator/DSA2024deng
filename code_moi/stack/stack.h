#include "..\vector\vector.h" 
template <typename T> class Stack: public Vector<T> { //Stack是Vector的派生类，public继承，因此继承Vector的protected和public成员
public: 
   using Vector<T>::operator[];
   void push ( T const& e ) { this->insert ( e ); } 
   T pop() { return this->remove ( this->size() - 1 ); } 
   T& top() { return ( *this ) [this->size() - 1]; } 
   // Stack ( Rank c = DEFAULT_CAPACITY, Rank s = 0, T v = 0 )
   // { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } 
};
//2.25遗留问题：为了初始化必须有派生类自己的构造函数，但是重复写两遍总觉得不太对劲，还有就是参数到底是怎么传的，
//为什么基类的参数名也要写上