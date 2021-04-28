//
// Created by blithepan on 2020/7/3.
//

#ifndef BUILD_SINGLETON_H
#define BUILD_SINGLETON_H
template <typename T>
class Singleton
{
public:
    static T& GetInstance()
    {
        static T instance;
        return instance;
    }
protected:
    Singleton() {}
    ~Singleton() {}
public:
    Singleton(Singleton const &) = delete;
    Singleton& operator=(Singleton const &) = delete;
};
#endif //BUILD_SINGLETON_H
