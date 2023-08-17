//
// Created by alu on 23-8-17.
//

#include <iostream>
#include <cstring>

using std::cout, std::endl;

template <typename K, typename V>
class Node{
public:
    Node(K key, V val, int level);
    ~Node();
    inline K getKey() const { return _key; }
    inline V getVal() const { return _val; }
    int _listLevel;
    Node** forward;

private:
    K _key;
    V _val;


};

template <typename K, typename V>
Node<K,V>::Node(K key, V val, int level) {
    this->_key = key;
    this->_val = val;
    this->_listLevel = level;
}


template <typename K, typename V>
Node<K,V>::~Node(){
    delete[] forward;
}

template <typename K, typename V>
class skipList{
public:
    skipList(int maxLevel);

    void insret(K key, V val);
    void del(V val);
    bool search(K key);
    int getRandom();

private:
    int _maxLevel;
    int _curLevel;
    Node<K,V>* _header;


};

template<typename K, typename V>
int skipList<K, V>::getRandom() {
    srand((unsigned)time(NULL));

    return rand() % _maxLevel + 1;
}

template<typename K, typename V>
skipList<K, V>::skipList(int maxLevel) {
    _maxLevel = maxLevel;
    _curLevel = 0;

    K k;
    V v;
    _header = new Node<K,V>(k,v,_maxLevel);
}

template<typename K, typename V>
void skipList<K, V>::insret(K key, V val) {
    Node<K,V>* cur = _header;
    Node<K,V>* update[this->_maxLevel + 1];
    memset(update, 0, sizeof(Node<K,V>*) * (this->_maxLevel+1));
    for(int level = _curLevel; level >= 0; level--){
        while (cur->forward[level] != nullptr && cur->forward[level]->getKey() < key){
            cur = cur->forward[level];
        }
        update[level] = cur;
    }

    cur = cur->forward[0];
    if(cur != nullptr && cur->getKey() == key){
        cout << "key is exist!" << endl;
    }

    if(cur != nullptr && cur->getKey() != key){
        int randomLevel = getRandom();
        //如果增加层数，需要更新update数组
        if(randomLevel > _curLevel){
            for(int level = _curLevel + 1; level < randomLevel + 1; level++){
                update[level] = _header;
            }
            _curLevel = randomLevel;
        }

        //插入新节点
        Node<K,V>* insertNode = new Node<K,V>(key, val, randomLevel);
        for(int level = 0; level < _curLevel; level++){
            insertNode->forward[level] = update[level]->forward[level];
            update[level]->forward[level] = insertNode;
        }

        cout << "Successfully insert node!!" << endl;

        return;
    }
}


template <typename K, typename V>
bool skipList<K, V>::search(K key) {

    Node<K,V>* cur = _header;

    // 找到Key相同的元素的前置节点
    for(int level = _curLevel; level >= 0; level--){
        while (cur->forward[level] != nullptr && cur->forward[level]->getKey() < key){
            cur = cur->forward[level];
        }
    }

    //让cur指向查找元素节点的最底层，也就是原始链表
    cur = cur->forward[0];

    //检查是否该节点就是要找的节点
    if(cur && cur->getKey() == key){
        cout << "Found Key!" << endl;
        cout << "Key: " << cur->getKey() << " Value: " << cur->getVal() << endl;
        return true;
    }

    cout << "NOT FOUND!" << endl;
    return false;
}
