#include "ListNode.h"

template <typename T> class List{
private:
    int _size; ListNodePos<T> header, trailer;
protected:
    void init();
    int clear();
    List<T> copyNodes (ListNodePos<T> p,Rank n); //从一个指针p极其后继共n个结点通过复制*构造*一个新list
public:
//构造函数
    List(){init();};
    List(ListNodePos<T> p,Rank n){copyNodes(p,n);};
    List(List<T> const &l){copyNodes(l->header->succ,l._size);};
//析构函数 
    ~List();
//成员函数：只读接口
    ListNodePos<T> find(T const &e, Rank n, ListNodePos<T> p ) const;
    ListNodePos<T> search(T const &e, Rank n, ListNodePos<T> p) const;
    ListNodePos<T> operator[] (Rank r) const;
//成员函数：可写接口
    ListNodePos<T> insertAsLast (T e);
    T remove(ListNodePos<T> p);
    int deduplicate();
    int uniquify();
    ListNodePos<T> insertA(ListNodePos<T> p, T const &e);
};

template <typename T> 
void List<T>::init(){
    header = new ListNode<T>; //正好new返回的是指针
    trailer = new ListNode<T>;
    header->succ = trailer; header->pred = nullptr;
    trailer ->pred = header; trailer->succ = nullptr;
    _size = 0;
}

template<typename T>
List<T> List<T>::copyNodes (ListNodePos<T> p,Rank n){
    init();
    while (n--){insertAsLast(p->data); p = p->succ;}
}

//返回插入的结点指针
template <typename T>
ListNodePos<T> List<T>::insertAsLast (T e){
    _size++;
    return trailer->insertAsPred(e);
}

//删除p结点并返回其值
template<typename T>
T List<T>::remove(ListNodePos<T> p){
        T e = p->data;
        p->pred->succ = p->succ;
        p->succ->pred = p->pred;
        delete p; _size--;
        return e;
    }

//删除所有结点(不含header和trailer)，返回size
//底层上只能沿着链依次访问删除，因为不是连续存放的
template <typename T>
int List<T>::clear(){
    int a = _size;
    while(_size--){remove(header->succ);}
    return a;
}

//依次删除含header和trailer的所有结点
template <typename T>
List<T>::~List(){
    clear();
    delete header, trailer;
}

//查找p的n个前驱中的值e并返回指针
template <typename T>
ListNodePos<T> List<T>::find (T const &e, Rank n, ListNodePos<T> p ) const {
    while (n--){
        if (e==((p=p->pred)->data))return p;//注意看括号
    }
    return nullptr;
}

//最朴素的去重
template <typename T>
int List<T>::deduplicate(){
    if (_size<2) return 0; //只有0或1个元素则不用删
    int oldSize = _size;
    ListNodePos<T> p = header; Rank n=0; 
    //发现重复保留第一个，删后面的
    // while(trailer!=p){
    //     if (find(p->data,n,p)) {p = p->succ; remove(p->pred)};
    //     else {p=p->succ; n++; }
    //     }
    //发现重复保留最后一个，删前面的
    while (trailer!=(p=p-> succ)){
        ListNodePos<T> q = find(p->data,n,p);
        p? remove(p): n++;
    }
    return oldSize-_size;
}

//有序列表去重
template <typename T> 
int List<T>::uniquify(){
    if (_size<2) return 0; 
    int oldSize = _size;
    ListNodePos <T> p=header->succ,q = p->succ;
    while (trailer!=  p){
        while (q->data==p->data){q=q->succ;delete q->pred;_size--;}
        q->pred = p; p->succ=q;
        p = q; q=p->succ;
    }
    return _size-oldSize;
}

//有序列表(假设递增)查找，可以提前结束可以失败，返回最终位置
template <typename T>
ListNodePos<T> List<T>::search(T const &e, Rank n, ListNodePos<T> p) const{
    while (n-- && header!= (p=p->pred)){
        if (e>= p->data) return p;
    }
    return nullptr;
}

//插入作为前驱
template <typename T>
ListNodePos<T> List<T>::insertA(ListNodePos<T> p, T const &e){
ListNodePos<T> q = new ListNode<T>(e,p->pred,p);
p->pred->succ=q;p->pred = q;
_size++;
return q;
}

//0<=r<_size
template <typename T>
ListNodePos<T> List<T>:: operator[] (Rank r) const{
ListNodePos<T> p = header->succ;
while (r--){p = p->succ;}
return p;
}