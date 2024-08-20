#ifndef BIND_H
#define BIND_H

// #include <functional>
// #include <tuple>
// #include <utility>

namespace BIND {

#include <iostream>
#include <tuple>
 
using namespace std;
 
//1. 占位符定义
template<size_t idx>
struct placeholder{}; 
 
template<size_t idx>
using ph = placeholder<idx>; 
 
constexpr ph<0> _0{}; //定义一个constexpr类型的占位符对象(_0)，并用大括号初始化。
constexpr ph<1> _1{}; //定义一个constexpr类型的占位符对象(_1)
constexpr ph<2> _2;   //定义一个constexpr类型的占位符对象(_2)
constexpr ph<3> _3;   //定义占位符对象(_3)
 
//2. 参数选择：do_select_param会根据是否为占位符来选择合适的实参。
//2.2 泛化版本：arg不是占位符
template<class Args, class Params>
struct do_select_param
{
    decltype(auto) operator()(Args& arg, Params&&) //arg不是占位符，说明arg本身就是一个真正的实参，直接返回。
    {
        return arg;  //由于arg是个引用，decltype(auto)结果也是arg的引用
    }
};
 
//2.3 特化：arg为占位符情况。
template<size_t idx, class Params>
struct do_select_param<placeholder<idx>, Params> //注意Params为bind返回的绑定对象被调用时，传入其中的参数包
{
    decltype(auto) operator()(placeholder<idx>, Params&& params) //这里的params是个tuple对象。
    {
        return std::get<idx>(std::forward<Params>(params));//根据占位符取出params参数包中的实参。
    }
};
 
//2.1 根据占位符选择合适的实参
template<class Args, class Params>
decltype(auto) select_param(Args& arg, Params&& params)
{
    //注意，其中的arg是bind绑定时传入的实参，可能是实参或占位符。而params是bind返回的可调用对象被执行时传入的实参。
    //如果绑定时是占位符，会do_select_param会分派到其特化的版本，否则分派到其泛化版本。
    return do_select_param<Args, Params>{}(arg, std::move(params)); //params是副本，统一用move而不用forwared!
}
 
//3. binder类及辅助函数
//3.3 绑定对象(obj)的调用: 其中args表示传入bind函数的参数，params表示传入obj可调用对象的参数。
template<size_t... idx, class Callable, class Args, class Params>
decltype(auto) bind_invoke(std::index_sequence<idx...>, Callable& obj, Args& args, Params&& params)
{
 
    //根据args是否是占位符来选择合适的实参，并传给可调用对象obj。
    //注意：为了提高效率，参数是以move的形式（右值）被传递给obj可调动对象的。
    return std::invoke(obj, select_param(std::get<idx>(args), std::move(params))...);//C++17， invoke(func, 参数1, 参数2, ...)
}
 
//3.2 binder类（核心类）
template<class Callable, class... Args>
class binder
{
    using Seq = std::index_sequence_for<Args...>;   //等价于std::make_index_sequence<sizeof...(Args)>
                                                    //会创建类似一个index_sequence<0,1,2...>的类
    //保存bind函数的所有实参（即可调用对象及其实参）
    using args_t = std::tuple<std::decay_t<Args>...>; //注意，decay_t去掉其引用、const\volatile等特性）
    using callable_t = std::decay_t<Callable>; //可调用对象的类型（注意，decay_t去掉其引用、cv等特性）
 
    callable_t mObj; //以副本的形式保存可调用对象
    args_t mArgs; //以副本的形式保存可调用对象的所有实参。（打包放在tuple中）
public:
 
    //注意，不管是可调用对象(callableObj)，还是它的实参(args)均会根据其左右值特性，被复制或移动到Binder类中，以副本的形式保存起来。
    explicit binder(Callable&& callableObj, Args&& ... args)
                 :mObj(std::forward<Callable>(callableObj)),mArgs(std::forward<Args>(args)...)
    {
    }
 
    //Binder仿函数的调用
    template<class... Params>
    decltype(auto) operator()(Params&& ... params) //可调用对象被调用，并传入参数。
    {
        //第1个参数：升序的整数序列。第4个参数将传入的params实参转化为tuple对象。
        //注意：std::forward_as_tuple被定义成tuple<_Types&&...>(_STD forward<_Types>(_Args)...);
        //      这说明params将以引用的形式被保存在tuple中！！！
        return bind_invoke(Seq{}, mObj, mArgs, std::forward_as_tuple(std::forward<Params>(params)...));
    }
};
 
//3.1 bind辅助函数
template <class Callable, class... Args>
decltype(auto) bind(Callable&& callableObj, Args&& ... args)
{
    return binder<Callable, Args...>(std::forward<Callable>(callableObj), std::forward<Args>(args)...);
}

} // namespace

#endif