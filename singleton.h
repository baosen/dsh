#ifndef DSHELL_SINGLETON_H
#define DSHELL_SINGLETON_H

template<class T>
class Singleton<T> {
public:
    static Singleton<T>& get_instance() {
        static Singleton<T> s;
        return s;
    }
private:
    Singleton();
    T single_object;
};

#endif DSHELL_SINGLETON_H
