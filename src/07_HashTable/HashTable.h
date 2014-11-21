//
// File: HashTable.h
// Hash table implemented as linear open addressing using an auxiliary flag array.
// Shining Yang <y.s.n@live.com>, 2014-11-21
//
#pragma once

#include <iostream>
#include "..\Utility\Exception.h"
using namespace std;
using namespace DSCPP::Utils;

namespace DSCPP { namespace Hash {

template<typename E, typename K>
class HashTable {
public:
    HashTable(int nBuckets = 16);
    virtual ~HashTable();

    bool Search(const K& k, E& e) const;
    HashTable<E, K>& Insert(const E& e);
    HashTable<E, K>& Delete(const K& k, E& e);
    
    template<typename E, typename K>
    friend ostream& operator<<(ostream& os, const HashTable<E, K>& obj);

protected:
    int _SearchHelper(const K& k) const;

private:
    bool* empty;
    E* elements;
    int divisor;
};

template<typename E, typename K>
HashTable<E, K>::HashTable(int nBuckets /*= 16*/)
{
    divisor = nBuckets;
    empty = new bool[nBuckets];
    elements = new E[nBuckets];
    for (int i = 0; i < nBuckets; i++) {
        empty[i] = true;
    }
}

template<typename E, typename K>
HashTable<E, K>::~HashTable()
{
    delete[] empty;
    delete[] elements;
}

template<typename E, typename K>
bool HashTable<E, K>::Search(const K& k, E& e) const
{
    int n = _SearchHelper(k);
    if (empty[n] || elements[n] != k) {
        return false;
    }

    e = elements[n];
    return true;
}

template<typename E, typename K>
HashTable<E, K>& HashTable<E, K>::Insert(const E& e)
{
    K k = e; // make a conversion
    int n = _SearchHelper(k);
    if (empty[n]) {
        elements[n] = e;
        empty[n] = false;
    } else {
        if (elements[n] == k) {
            throw new ItemAlreadyExisted();
        } else {
            throw new OutOfRange();
        }
    }
    return *this;
}

template<typename E, typename K>
HashTable<E, K>& HashTable<E, K>::Delete(const K& k, E& e)
{
    return *this;
}

// ����n ��Ͱ��
// 1) �����йؼ���ֵΪk ��Ԫ�أ�empty[n]Ϊfalse ��elements[n] �Ĺؼ���ֵΪk��
// 2) ����û�йؼ���ֵΪk ��Ԫ�أ�empty[n]Ϊtrue����ɰѹؼ���ֵΪk ��Ԫ�ز��뵽n ��Ͱ�У�
// 3) ����û�йؼ���ֵΪk ��Ԫ�أ�empty[n]Ϊfalse��empty[n]�Ĺؼ���ֵ������k���ұ�������
template<typename E, typename K>
int HashTable<E, K>::_SearchHelper(const K& k) const
{
    int i = k % divisor;
    int n = i;
    do {
        if (empty[n] || elements[n] == k) {
            return n;
        }
        n = (n + 1) % divisor;
    } while (n != i);

    return n;
}

template<typename E, typename K>
ostream& operator<<(ostream& os, const HashTable<E, K>& obj)
{
    for (int i = 0; i < obj.divisor; i++) {
        if (obj.empty[i]) {
            os << "*";
        } else {
            os << obj.elements[i];
        }
        os << " ";
    }
    return os;
}

}}