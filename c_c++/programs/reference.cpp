#include <iostream>
using namespace std;
void fun1(int b)
{
   b=1;
}

void fun2(int &b)
{
  b=2;
}
void fun3(int *b)
{
  *b=3;
}
void swap(int& x,int& y);

int main()
{
  int a = 0;
  fun1(a);
cout <<"fun1 a= "<<a<<endl;
  fun2(a);
cout <<"fun2 a= "<<a<<endl;
  fun3(&a);
cout <<"fun3 a= "<<a<<endl;
  
  int m = 100;
  int n = 200;
  cout<<"before swap m="<<m<<endl;
  cout<<"before swap n="<<n<<endl;
  swap(m,n);
  cout<<"after swap m="<<m<<endl;
  cout<<"after swap n="<<n<<endl;
  return 0;
}

void swap(int& x,/*const*/ int& y) // const 引用不可修改
{
  int temp;
  temp=x;
  x=y;
  y=temp;
  return;
}

