
using Rank = unsigned int;

template <typename T> struct ListNode;
template <typename T> using ListNodePos = ListNode<T>*;
template <typename T >struct ListNode
{
    T data;  ListNodePos<T> pred; ListNodePos<T> succ;  //ListNodePos是模板类型，使用模板类型必须要模板名+参数列表
    //构造函数 1.空 2.给了（一个）data，因为是一个结点的struct
    ListNode(){}; //注意构造函数没有返回类型
    ListNode(T d, ListNodePos<T>  p = nullptr, ListNodePos<T>  s =nullptr ):data(d), pred(p),succ(s){}

    //成员函数
    ListNodePos<T> insertAsPred(ListNodePos<T> &p);
    ListNodePos<T> insertAsSucc(T const &e);//不能直接用来连城list，因为单个结点前驱后继都是nullptr就不存在也无法修改pred->succ等等
    ListNodePos<T> insertAsPred(T const &e);
};

//这个函数有问题
template <typename T> 
ListNodePos<T> ListNode<T> :: insertAsPred (ListNodePos<T> &p){
pred->succ = p; p->pred = pred;
pred = p;  p->succ = this; 
return p;
}

//返回插入的结点指针
template <typename T>//定义成员模板类的函数要像定义模板函数一样
ListNodePos<T> ListNode<T> :: insertAsPred(T const &e){
ListNodePos<T> x = new ListNode(e,pred,this);
pred->succ = x; pred = x;
return x;
}

template <typename T>
ListNodePos<T> ListNode<T> :: insertAsSucc(T const &e){
ListNodePos<T> x = new ListNode(e,this,succ);
succ->pred = x; succ =x;
return x;
}