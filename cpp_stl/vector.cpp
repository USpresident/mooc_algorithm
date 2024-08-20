#include <vector>
#include <iostream>

void printArray(const std::vector<int> &vec, bool flag)
{
    for (const auto &element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    std::cout << "capacity: " << vec.capacity() << ", size: " << vec.size() << ", " << vec.max_size() <<  std::endl;

    if (!flag) {
        return;
    }
}

int main(int argc, char *argv[])
{
    // std::vector<int> vec;
    // vec.reserve(3);
    // std::cout << "capacity: " << vec.capacity() << ", size: " << vec.size() << ", " << vec.max_size() <<  std::endl;
    // vec.push_back(10);
    // vec.push_back(20);
    // vec.push_back(30);
    // vec.push_back(40);
    // printArray(vec, true);

    std::vector<int> vec = {1};
    printArray(vec, true);
    std::cout << "capacity: " << vec.capacity() << ", size: " << vec.size() << ", " << vec.max_size() <<  std::endl;

    vec.emplace(vec.begin(), 44);
    vec.emplace(vec.end(), 4);
    printArray(vec, true);
    
    vec.reserve(8);
    std::cout << "capacity: " << vec.capacity() << ", size: " << vec.size() << ", " << vec.max_size() <<  std::endl;
    vec.shrink_to_fit();
    std::cout << "capacity: " << vec.capacity() << ", size: " << vec.size() << ", " << vec.max_size() <<  std::endl;
    vec.resize(6);
    printArray(vec, true);
    vec.resize(9, 2);
    printArray(vec, true);
    
    std::vector<int> temp(4, 5);
    vec.assign(temp.begin(), temp.end());
    printArray(vec, true);

    int arr[3] {66, 77, 99};
    vec.assign(std::begin(arr), std::end(arr));
    printArray(vec, true);

    vec.insert(vec.end(), arr, arr + 3);
    printArray(vec, true);

    vec.insert(vec.begin(), arr, arr + 2);
    printArray(vec, true);

    std::swap(temp, vec);
    printArray(vec, true);
    vec.swap(temp);
    printArray(vec, true);

    vec.clear();
    printArray(vec, true);

    return 0;
}


// begin()	返回指向容器中第一个元素的迭代器。
// end()	返回指向容器最后一个元素所在位置后一个位置的迭代器，通常和 begin() 结合使用。
// rbegin()	返回指向最后一个元素的迭代器。
// rend()	返回指向第一个元素所在位置前一个位置的迭代器。
// cbegin()	和 begin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
// cend()	和 end() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
// crbegin()	和 rbegin() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
// crend()	和 rend() 功能相同，只不过在其基础上，增加了 const 属性，不能用于修改元素。
// size()	返回实际元素个数。
// max_size()	返回元素个数的最大值。这通常是一个很大的值，一般是 232-1，所以我们很少会用到这个函数。
// resize()	改变实际元素的个数。
// capacity()	返回当前容量。
// empty()	判断容器中是否有元素，若无元素，则返回 true；反之，返回 false。
// reserve()	增加容器的容量。
// shrink _to_fit()	将内存减少到等于当前元素实际所使用的大小。
// operator[ ]	重载了 [ ] 运算符，可以向访问数组中元素那样，通过下标即可访问甚至修改 vector 容器中的元素。
// at()	使用经过边界检查的索引访问元素。
// front()	返回第一个元素的引用。
// back()	返回最后一个元素的引用。
// data()	返回指向容器中第一个元素的指针。
// assign()	用新元素替换原有内容。
// push_back()	在序列的尾部添加一个元素。
// pop_back()	移出序列尾部的元素。
// insert()	在指定的位置插入一个或多个元素。
// erase()	移出一个元素或一段元素。
// clear()	移出所有的元素，容器大小变为 0。
// swap()	交换两个容器的所有元素。
// emplace()	在指定的位置直接生成一个元素。
// emplace_back()	在序列尾部生成一个元素。