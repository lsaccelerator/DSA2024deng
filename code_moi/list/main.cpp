#include"list.h"
#include <iostream>
using namespace std;
int main(){
  int a[] = {1,99,2,3,4,4,4,5,5,6};
  //使用模板时必须指定T的实际类型
  //ListNodePos<int> p =  new ListNode<int> {111};
  List<int> L{};
  for (int i=0;i<10;i++){L.insertAsLast(a[i]);}
  //List<int> D{};
  //L.uniquify();
  cout << 3<<endl;
}