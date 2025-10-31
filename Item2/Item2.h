/* ---------------------------------------------------------------------------------------------- */
/*                             用 consts , enums 和 inlines 取代 #defines                           */
/* ---------------------------------------------------------------------------------------------- */

#include <string>

//用 compiler取代 preprocessor

#define ASPECT_RATIO 1.653  //define是预处理器的一部分，并没有被看作是C++语言的一部分，因此在调试的时候会带来很多的困难

const double AspectRatio = 1.653;   //用const取代数值类型的定义宏

// const char* const authorName = "Scott Meyers";  //指针类型的宏应该使用两个const进行限制

const std::string authorName ("Scott Meyers");  //对于字符串类型，使用std::string更加推荐，仅需一个const进行修饰

class GamePlayer
{
    enum { NumTurnsE = 5 };              //enum hack

private:
    static const int NumTurns = 5;      // 注意：这里是声明！而不是定义

    int scores[NumTurns];               // use of constant
    //...
};

//C++中要求我们虽然可以直接使用类内定义的静态变量，但这里即使你已经赋值了，但这仍然是个声明，不可以取地址
//如果需要对变量进行取地址，需要在对应的源文件中添加如下代码：
const int GamePlayer::NumTurns;

//对于一些比较老的编译器，类内给定初始值是不支持的
//还是将类内定义的类外实现分开比较好

//从某些方面来看，enum hack的行为更加贴切宏定义。
//因为宏定义的数值不可以被取地址，enum同样不可以取地址

//function-like macro
#define CALL_WITH_MAX(a, b) ((a) > (b) ? (a) : (b))

int a = 5 , b = 0;
// CALL_WITH_MAX (a++ , b); // a被递增了两次

//对于function-like形式的宏定义，推荐使用inline function代替
template<typename T>
inline T callWithMax (const T& a , const T& b)    
{                                                  
    return a > b ? a : b;                                
}