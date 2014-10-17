//
// File: StackLinearList.h
//
// Stack implemented with linear list.
//
// 2014-10-14, Shining Yang <y.s.n@live.com>
//
#pragma once

#if 0
��Stack��Ч�ʡ�
��T��һ���ڲ���������ʱ����ջ�Ĺ��캯�������������ĸ����Ծ�ΪO(1)���������û�
�Զ������ʱ�����캯�������������ĸ����Ծ�ΪO(MaxStackSize)������ÿ����ջ�����ĸ�
���Ծ�ΪO(1)��ע��ͨ����LinearList����Stack��һ����������˱���������һ����Ҳʹ��
��Ŀɿ��Եõ��ܴ���ߣ���ΪLinearList�������Բ�����Ϊ����ȷ�ġ�Ȼ�������ҵ��ǣ���
���д�ļ򻯴���������Ч�ʵ���ʧ�����磬Ϊ�����ջ�����һ��Ԫ�أ�����Ҫȷ����ջ��
����length()��Ȼ����ú���Insert()��Insert�������ȱ����жϲ�������Ƿ��Խ�磬Ȼ����Ҫ
����һ��forѭ���Ŀ�����ִ��0��Ԫ�ص��ƶ���Ϊ����������Ŀ��������԰�Stack�����һ��
���࣬�����������ࡣ
��һ��Ǳ�ڵ�������������StackҲ���ܵ�LinearList�����������Ƶ�Ӱ�졣���磬����Ϊ
��������ΪT�ĳ�Ա��������� << �� == ����Ϊǰ�����ڶ����Ա���� << �����أ��������ڶ�
LinearList::Search�����ء�
#endif

#include "../03_LinearList/LinearList.h"
#include "../Utility/Exception.h"
using namespace DSCPP::Utils;

namespace DSCPP { namespace Stack {

template<typename T>
class Stack : private CLinearList<T> {
public:
    enum {
        DEFAULT_STACK_SIZE = 20
    };

    Stack(int c = DEFAULT_STACK_SIZE);
    ~Stack();

protected:
    Stack(const Stack<T>& s);
    Stack<T>& operator=(const Stack<T>& s);

public:
    bool IsEmpty();
    bool IsFull();
    Stack<T>& Push(const T& e);
    Stack<T>& Pop(T& e);
    T Top() const;
};

template<typename T>
DSCPP::Stack::Stack<T>::Stack(int c) : CLinearList<T>(c)
{
}

template<typename T>
DSCPP::Stack::Stack<T>::~Stack()
{
}

template<typename T>
bool Stack<T>::IsEmpty()
{
    return CLinearList<T>::IsEmpty();
}

template<typename T>
bool Stack<T>::IsFull()
{
    return GetMaxSize() == Length();
}

template<typename T>
Stack<T>& Stack<T>::Push(const T& e)
{
    Insert(Length(), e);
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::Pop(T& e)
{
    Delete(Length() - 1, e);
    return *this;
}

template<typename T>
T Stack<T>::Top() const
{
    if (IsEmpty()) {
        throw new OutOfBounds();
    }

    T x;
    Find(Length() - 1, x);
    return x;
}

//==============================================================================
//= Stack2
//= not derived from linear list
//==============================================================================
template<typename T>
class Stack2 {
public:
    enum {
        DEFAULT_STACK_SIZE = 20
    };

    Stack2(int c = DEFAULT_STACK_SIZE) : capacity(c), top(-1) {
        elements = new T[c];
    }

    ~Stack2() {
        delete[] elements;
    }

protected:
    Stack2(const Stack2<T>& s);
    Stack2<T>& operator=(const Stack2<T>& s);

public:
    bool IsEmpty() const {
        return top < 0;
    }

    bool IsFull() const {
        return top >= capacity - 1;
    }

    Stack2<T>& Push(const T& x) {
        if (IsFull()) {
            throw new OutOfBounds();
        }

        elements[++top] = x;
        return *this;
    }

    Stack2<T>& Pop(T& x) {
        if (IsEmpty()) {
            throw new OutOfBounds();
        }

        x = elements[top--];
        return *this;
    }

    T Top() const {
        if (IsEmpty()) {
            throw new OutOfBounds();
        }

        return elements[top];
    }

private:
    int capacity;
    int top;
    T* elements;
};

}}