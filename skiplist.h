//
// Created by alu on 23-8-17.
//

#ifndef __SKIPLIST__
#define __SKIPLIST__

/*
 * TODO:
 * 1.增加文件落盘
 * 2.增加修改节点操作
*/

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

    this->forward = new Node<K,V>*[level+1];
    memset(this->forward, 0, sizeof(Node<K, V>*)*(level+1));
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
    void del(K key);
    bool search(K key);
    int getRandom();

private:
    int _maxLevel;
    int _curLevel;
    Node<K,V>* _header;


};

template<typename K, typename V>
void skipList<K, V>::del(K key) {
    if(!search(key)){
        cout << "NOT FOUND";
    }


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

        for (int i = 0; i < _curLevel; ++i) {

            //update[i]是本层跳入下层前的最后一个节点，如果在本层的下一个节点不是目标节点的话，证明节点已经全部删除
            if(update[i]->forward[i] != cur){
                break;
            }

            update[i]->forward[i] = cur->forward[i];
        }
        //删除一层为空的多余的表
        while (_curLevel > 0 && _header->forward[_curLevel] == nullptr){
            _curLevel--;
        }
        delete cur;
    }
    cout << "delete success" << endl;
    return;
}

template<typename K, typename V>
int skipList<K, V>::getRandom() {
    srand((unsigned)time(NULL));

    return rand() % _maxLevel + 1;
}

template<typename K, typename V>
skipList<K, V>::skipList(int maxLevel) {
    _maxLevel = maxLevel;
    _curLevel = 0;

    K k = 0;
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

    if(cur == nullptr || cur->getKey() != key){
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


#endif