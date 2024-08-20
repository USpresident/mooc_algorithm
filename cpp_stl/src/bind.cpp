//#include "../head/bind.h"

#include <functional>
#include <vector>
#include <iostream>
 
// 定义一个仿函数类
class Printer {
private:
    std::vector<int> m_arr {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //std::function<int(int)> m_fun;
public:
    //Printer(int , std::function<int(int)> fun) : m_fun(fun) {} // 构造函数绑定函数
    void operator()(std::function<int(int)> fun) const {
        for (auto a : m_arr) {
            fun(a);
        }
    }
};

int print(int a)
{
    int res = a * 2;
    return res;
}

// void test()
// {
//     Printer printer; // 创建仿函数实例
//     auto boundPrinter = std::bind(printer, std::bind(print, std::placeholders::_1)); // 绑定仿函数
//     boundPrinter(); // 调用绑定后的��函数
// }

void foo(int x, int y) {
    std::cout << "x + y = " << x + y << std::endl;
}
 
int main() {
    auto bound_func = std::bind(foo, 10, std::placeholders::_1);
    // 使用 decltype 获取 bound_func 的类型
    int a = 10;
    std::cout << "std::bind typename: " << typeid(std::bind(foo, 10, std::placeholders::_1)).name() << std::endl;
    return 0;
}

int addNum (int x, int y, int z)
{
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "z = " << z << std::endl;
    return (x + y + z);
}

// int main()
// {
//     auto f = std::bind(addNum, std::placeholders::_1, 555, std::placeholders::_2);

//     std:: cout << f(5, 4) << std::endl;

//     test();

//     //boundPrinter("Hello, world!"); // 使用绑定的仿函数

//     return 0;
// }

