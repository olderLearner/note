#include <iostream>
#include <stdlib.h>

using namespace std;

class Box
{
	private:
				double len;
	public:
				Box(double lv=1.0):len(lv)//构造函数没有返回值
				{
						cout<<"constructor called"<<endl;
				}

				~Box()
				{
						cout<<"destructor called"<<endl;
				}
  operator bool() const {
    cout<<"operator bool"<<endl;
    return true;
  }
				void show() {
						cout<<this->len<<endl;
				}
};

void displayBox(Box& box) { // 引用传递, 不会new一个临时对象
				box.show();
}

//void displayBox(Box box) {// 形参传递,会创建一个对象复制main中的box对象,display调用完成时要析构新创建的对象
//				box.show();
//}

int main()
{
				//Box box;
				//displayBox(box);
 int a = 10;
 int b = 12;
 int c = 14;
 a > b && b < c && Box();
 //Box();
 cout<<"condition is true"<<endl;

 float v = 0.0;
 for (int i=0; i < 10; i++) {
 //v = rand() / double(RAND_MAX);
 v = rand();
 cout<< 2 * v / 2147483647 <<endl;
}
 cout << RAND_MAX <<endl;
 //std::ostringstream stream;
 //stream << "Hello"<<" fds";

}
















