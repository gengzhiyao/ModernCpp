#include <iostream>
#include <memory>
#include <functional>
#include "SmartPointer.h"

void myCustomDel (A *a);
void DecltypeCustom (A *a);

int main ()
{
    //SetConsoleOutputCP (CP_UTF8);
    // int* i = new int (10);
    // std::shared_ptr<int> pi = std::make_shared<int> (11);
    // std::shared_ptr<A> a1 = std::make_shared<A> ("std::string");
    // std::shared_ptr<A> a2 (new A ("arguments"));
    // a2 = a1;
    // A* a3 = a2.get ();
    //!delete a3; 不要手动删除指针指针返回的裸指针，否则会报异常
    // std::weak_ptr<A> weak (a2);

    //在循环引用中，每个对象的引用计数依赖于另一个对象的释放，而另一个对象的释放又依赖于当前对象的释放，形成一个无法打破的闭环。
    // std::shared_ptr<A> loopRefa = std::make_shared<A> ();
    // std::shared_ptr<B> loopRefb = std::make_shared<B> ();
    // loopRefa->m_b = loopRefb;
    // loopRefb->m_a = loopRefa;   //B::std::weak_ptr<A> m_a;不增加引用计数
    //离开作用域之后，由于loopRefa的引用计数置零，A的对象被销毁，进一步使得shared_ptr::m_b指针成员被销毁
    //loopRefb的引用计数减至1，但是到达作用域又得减一次，基本可以看作是在极短的时间内减两次，从而引用计数归零，内存释放。

    std::shared_ptr<A> moveA1 = std::make_shared<A> ();
    std::shared_ptr<A> moveA2 = std::make_shared<A> ();
    std::shared_ptr<A> moveA3 = std::make_shared<A> ("moveA3");
    moveA1 = moveA2;
    moveA1 = moveA3;
    moveA1 = std::move (moveA2);    //执行这行触发的析构函数是由于moveA1接收一个对象，释放原本对象产生的

    //std::shared_ptr<A> invalidA = new A ("..");
    std::shared_ptr<A> validA (new A ("validA"));
    //std::move (moveA2);

    std::auto_ptr<C> autoPtrC1 (new C);
    std::auto_ptr<C> autoPtrC2 (autoPtrC1);
    if (autoPtrC1.get () == NULL)
    {
        //对于UTF8编码的文件，若终端中显示的字体是乱码，那么在windows的时间设置中，将编码方式转换为Unicode编码
        std::cout << std::string ("autoptr是空指针。") << std::endl;
    }
    C *c = autoPtrC2.release ();
    if (autoPtrC2.get()==nullptr)
    {
        std::cout << "autoPtrC2为空" << std::endl;
    }

    std::unique_ptr<A> uniqueA1 (new A ("use unique pointer"));

    std::unique_ptr<A , decltype(myCustomDel) *> (new A ("custom deleter object") , DecltypeCustom);
    decltype((myCustomDel)) fun = DecltypeCustom;//函数引用，一旦绑定就不可更改

    return 0;
}

void myCustomDel (A* a)
{
    std::cout << "执行自定义删除器" << std::endl;
    delete a;
}

void DecltypeCustom (A *a)
{
    std::cout << "执行自定义删除器:DecltypeCustom" << std::endl;
    delete a;
}