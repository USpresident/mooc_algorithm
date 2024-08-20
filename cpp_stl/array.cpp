#include <array>
#include <iostream>

// namespace std{
//     template <typename T, size_t N>
//     class array;
// }

void printArray(const std::array<int, 10> &arr, bool flag)
{
    if (arr.empty()) {
        return;
    }

    for (auto e : arr) {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    if (!flag) {
        return;
    }

    std::cout << "iterator :" << std::endl;

    for (auto it = std::begin(arr); it != std::end(arr); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 因为入参加const arr，不能用 iterator, reverse_iterator
    for (std::array<int, 10>::const_iterator it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for (std::array<int, 10>::const_iterator it = arr.cbegin(); it != arr.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for (std::array<int, 10>::const_reverse_iterator it = arr.rbegin(); it != arr.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for (std::array<int, 10>::const_reverse_iterator it = arr.crbegin(); it != arr.crend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::array<int, 10> arr{1, 2, 3}; // 初始化1,2,3,0...
    printArray(arr, false);

    std::cout << arr.size() << ", " << arr.max_size() << std::endl; // 10, 10

    arr.fill(1); // 所有元素更新为1
    printArray(arr, false);

    for (int i = 0; i < 10; i++) {
        arr[i] = i + 1; // 依次赋值1,2,3,...,10
    }
    printArray(arr, true);

    // <array> 头文件中还重载了 get() 全局函数，该重载函数的功能是访问容器中指定下标的元素，并返回该元素的引用
    std::cout << arr[2] << ", " << arr.at(4) << ", " << std::get<3>(arr) << std::endl;

    std::cout << arr.front() << ", " << arr.back() << ", " << std::endl; // 引用
    std::cout << arr.data() << ", " << *arr.data() << std::endl; // 首元素指针

    // ---------------------------------------
    std::array<int, 10> arr2 = arr; // 长度一样
    printArray(arr2, false);

    for (int i = 0; i < 10; i++) {
        arr2[i] *= arr2[i]; // 依次赋值1,2,3,...,10
    }

    std::cout << "before swap:" << std::endl;
    printArray(arr, false);
    printArray(arr2, false);

    arr.swap(arr2); // 交换 array1 和 array2 容器中的所有元素，但前提是它们具有相同的长度和类型
    std::cout << "after swap:" << std::endl;
    printArray(arr, false);
    printArray(arr2, false);

    return 0;
}