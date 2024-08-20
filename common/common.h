#ifndef COMMON_H
#define COMMON_H

class NoCopyAble {
public:
    NoCopyAble() = default;
    virtual ~NoCopyAble() = default;

    NoCopyAble(const NoCopyAble&) = delete;
    NoCopyAble& operator=(const NoCopyAble&) = delete;

    NoCopyAble(NoCopyAble&&) = delete;
    NoCopyAble& operator=(NoCopyAble&&) = delete;
};

/**
 * @brief 比较器，使用的时候要注意入参顺序；
 *        T 类型要支持比较。
 */
template<typename T>
struct CmpLess {
    bool operator()(const T &a, const T &b) const {
        return a < b;
    }
};

template<typename T>
struct CmpGreater {
    bool operator()(const T &a, const T &b) const {
        return a > b;
    }
};

#endif