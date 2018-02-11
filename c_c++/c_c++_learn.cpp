--------------------------------------------
compile 
g++ filename -o outname(xx.out)  // 生成可执行文件

// 执行
ubuntu *.out 文件执行. 
//   ./*.out
-------------------------------------------------------------------------------------------------------
stdint.h
intN_t, int_leastN_t, int_fastN_t表示长度为N位的整型数；
uintN_t, uint_leastN_t, uint_fastN_t表示长度为N位的无符号整型数 ；

stdint.h中的常量，定义以上各类型数的最大最小值(其中N可以为8，16，32，64)
INTN_MIN, UINTN_MIN, INTN_MAX, UINTN_MAX ;
INT_LEASEN_MIN, INT_LEASEN_MAX ;
INT_FASTN_MIN, INT_FASTN_MAX ;
-------------------------------------
stdlib.h
stdlib.h里面定义了五种类型、一些宏和通用工具函数。 
类型例如size_t、wchar_t、div_t、ldiv_t和lldiv_t； 
宏例如EXIT_FAILURE、EXIT_SUCCESS、RAND_MAX和MB_CUR_MAX等等； 
常用的函数如malloc()、calloc()、realloc()、free()、system()、atof() atoi()、atol()、rand()、srand()、exit()等等
atoi() // 字符串转整形
------------------------------------
/*
内联函数 inline , 类似宏, 
编译时会用函数体替换函数调用
*/
#include <iostream>
using namespace std;

int max(int, int, int); //函数声明，左端也可以加inline

int main( )
{
   int i=10, j=20, k=30, m;
   m = max(i, j, k);  // 编译时, 将函数的形参替换为实参, 并用函数体代码替换函数
   cout<<"max="<<m<<endl;
   return 0;
}

inline int max(int a, int b, int c) //定义max为内联函数
{
   if(b>a) a=b;
   if(c>a) a=c;
   return a;
}

-----------------------------------------------------------------------------------------------------
 :: // 域解析操作符

namespace Li{   //小李的变量声明
    int flag = 1;
}
namespace Han{   //小韩的变量声明
    bool flag = true;
}

Li::flag = 0; // use li variant
Han::flag = 1; // use han variant
------------------------------------------------------------------------------------------------------
& (reference 引用)    reference.cpp
引用就是某一变量的别名, 对引用的操作与对变量操作完全一样
类型标识符&  引用名=目标变量名
int& b; int &b;//相同
int* b; int *b;
wp(const sp<T>& other) // 引用不可修改
------------------------------------------------------------------------------
析构函数    new  delete
何时调用析构函数 : 对象脱离其作用域时(对象所在函数已经调用完毕),系统会自动执行其析构函数,释放内存

形参为对象的传递问题   object.cpp
displayBox(Box box) {    // 形参传递

displayBox(Box& box) {    // 引用传递

-----------------------------------------------------------------------------------------
int i;
size_t size = sizeof(i);//sizeof 操作得到变量i的类型的大小

------------------------------------
  
  格式控制符
  %c : 输出一个字符 c character
  %s : 输出字符串   s string
  %d : 输出10进制
  %hd  short int
  %ld  long int
  %u   unsigned
  %o : 输出8进制
  %x : 输出16进制
  %f : float
  %lf  double

---------------------------------------
初始化结构体
typedef struct person
{
   char name;
   int age;
}person_t;

1: 
person_t p = {0};
person_t *p = malloc(sizeof(person_t));

结构体数组
person ps[10];
----------------------------------------
std::make_shared<SLCANProto>(this);   // 构造对象

// placeholders 占位符
namespace placeholders {
  extern /* unspecified */ _1;
  extern /* unspecified */ _2;
  extern /* unspecified */ _3;
  // ...
}

---------------------------------------
c++ 
map
map<uint32_t, HandlerFuc> mRxMsgHandlers.
        auto it = mRxMsgHandlers.find(msg.canFrame->can_id); // 根据id查找value
        if (it != mRxMsgHandlers.end()) { // 存在
            it->second(msg); // 调用value 的函数
        }


emplace() emplace_back()  :  insert()  push_back() 
emplace(): 直接将参数传给对象的构造器, 在容器中构造一个对象, 从而实现0拷贝,(底层机制: 调用placement new , 即布局new 运算符来实现的)
eg: 
class MyClass(T1 val1, T2 val2);
container.emplace(container.end(), val1, val2)  // 在容器末尾直接构造一个对象.
container.insert(container.end(), MyClass (val1, val2)) // 先构造一个对象, 然后拷贝到容器末尾
emplace_back() 与 push_back() 类似
如果对象已经存在,则效率差不多.
emplace_back和push_back都是向容器内添加数据.
对于在容器中添加类的对象时, 相比于push_back,emplace_back可以避免额外类的复制和移动操作.
"emplace_back avoids the extra copy or move operation required when using push_back."


 mProtos.emplace(toInt(gemulatorProto->getProtoType()), gemulatorProto);// insert

vector
mDevices.push_back(std::make_shared<CANBoxDevice>(hal, this));// 存值

--------------------------------------------------------
    static constexpr int CANID_CANBOX_LED_2 = 0x13;

常量表达式必须在编译期间计算出它的值并且 它的值不可以被改变。
在C++11中，我们可以通过声明constexpr让编译器确定一个变量是不是常量表达式，声明为constexpr的变量是const类型的变量，它必须由常量表达式来初始化。例如：
constexpr int mf = 20; // 常量表达式
constexpr int limit = mf + 1; // 常量表达式
constexpr int sz = size(); // 如果size()是常量表达式则编译通过，否则报错

---------------------------------------------------------
5.产生一定范围随机数的通用表示公式
stdlib.h
要取得[a,b)的随机整数，使用(rand() % (b-a))+ a; 
要取得[a,b]的随机整数，使用(rand() % (b-a+1))+ a; 
要取得(a,b]的随机整数，使用(rand() % (b-a))+ a + 1; 
通用公式:a + rand() % n；其中的a是起始值，n是整数的范围。 
要取得a到b之间的随机整数，另一种表示：a + (int)b * rand() / (RAND_MAX + 1)。 
要取得0～1之间的浮点数，可以使用rand() / double(RAND_MAX)。

---------------------------------------------------------
ostringstream istringstream getline()
sstream.h
类似sprintf, 
ostringstream stream;
stream << "data data";
ostringstream是C++的一个字符集操作模板类，定义在sstream.h头文件中。ostringstream类通常用于执行C风格的串流的输出操作，格式化字符串，避免申请大量的缓冲区，替代sprintf
ios_base <-- ios <-- ostream <-- ostringstream
二、ostringstream的基本使用
ostringstream的构造函数形式：
explicit ostringstream ( openmode which = ios_base::out );
explicit ostringstream ( const string & str, openmode which = ios_base::out );
 
有时候，我们需要格式化一个字符串，但通常并不知道需要多大的缓冲区。为了保险常常申请大量的缓冲区以防止缓冲区过小造成字符串无法全部存储。这时我们可以考虑使用ostringstream类，该类能够根据内容自动分配内存，并且其对内存的管理也是相当的到位。取得std::ostringstream里的内容可以通过str()和str(string&)成员函数。

三、注意事项
std::ostringstream::str()返回的是临时对象，不能对其直接操作。
例如会有如下误用：
const char *  pBuffer  =  oss.str().c_str();
注意pBuffer指向的内存已被析构！！
#include <string>  
#include <iostream>  
using namespace std;  
  
void main()  
{  
    ostringstream ostr1; // 构造方式1  
    ostringstream ostr2("abc"); // 构造方式2  
  
/*---------------------------------------------------------------------------- 
*** 方法str()将缓冲区的内容复制到一个string对象中，并返回 
----------------------------------------------------------------------------*/  
    ostr1 << "ostr1 " << 2012 << endl; // 格式化，此处endl也将格式化进ostr1中  
    cout << ostr1.str();   
  
/*---------------------------------------------------------------------------- 
*** 建议：在用put()方法时，先查看当前put pointer的值，防止误写 
----------------------------------------------------------------------------*/  
    long curPos = ostr2.tellp(); //返回当前插入的索引位置(即put pointer的值)，从0开始   
    cout << "curPos = " << curPos << endl;  
  
    ostr2.seekp(2); // 手动设置put pointer的值  
    ostr2.put('g');     // 在put pointer的位置上写入'g'，并将put pointer指向下一个字符位置  
    cout << ostr2.str() << endl;  
      
  
/*---------------------------------------------------------------------------- 
*** 重复使用同一个ostringstream对象时，建议： 
*** 1：调用clear()清除当前错误控制状态，其原型为 void clear (iostate state=goodbit); 
*** 2：调用str("")将缓冲区清零，清除脏数据 
----------------------------------------------------------------------------*/  
    ostr2.clear();  
    ostr2.str("");  
  
    cout << ostr2.str() << endl;  
    ostr2.str("_def");  
    cout << ostr2.str() << endl;  
    ostr2 << "gggghh";    // 覆盖原有的数据，并自动增加缓冲区  
    cout << ostr2.str() << endl;
    ostr2.str("");   // 若不加这句则运行时错误，因为_df所用空间小于gggghh，导致读取脏数据
    ostr2.str("_df");  
    cout << ostr2.str() << endl;

    // 输出随机内存值，危险
    const char* buf = ostr2.str().c_str();  
    cout << buf << endl;

    // 正确输出_df
    string ss = ostr2.str();
    const char *buffer = ss.c_str();
    cout << buffer << endl;
}

getline();
#include <string>
istream& getline(istream &in, string &line, char delim);

in是一个输入流，如cin、ifstream等。line是将输入流中的字符串放到这个string中，delim是结束字符，默认情况下是‘\n’
所以，我们可以使用getline从文件中逐行读取到string中，然后将该行和istringstream绑定，逐个字符串处理。
例如，txt文件中每行的内容为：
int main(int argc, char* argv[])  
{  
    std::string line;  
    std::string word;  
    std::ifstream fin("test.txt");  
      
    while (getline(fin, line))  
    {  
        std::istringstream stream(line);  
        while (stream >> word)  
            std::cout << word << "\n";  
    }  
    getchar();  
    return 0;  
} 	

---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------
---------------------------------------------------------




















