/**
 * 顺序表(动态分配内存)
 *
 * 按索引查找:O(1);
 * 插入:最好O(1),平均n/2=O(n),最坏O(n);
 * 按值查找:最好O(1),平均(n+1)/2=O(n),最坏O(n);
 *
 * Created by 刘滔 on 2018/9/14.
 * Copyright © 2018年 刘滔. All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include "iostream"
using namespace std;

//常量定义
const int LIST_INIT_SIZE = 100;
const int LIST_INCREMENT_SIZE = 10;

//类型定义
typedef int DataType;

//动态顺序表的结构体定义
typedef struct Node{
    DataType* data;//存放数据
    int length;//顺序表当前长度
    int size;//顺序表最大容量
}*SequenceList, List;

/**
 静态顺序表的结构体定义
 typedef struct Node{
     DataType data[LIST_INIT_SIZE];//存放数据
     int length;//顺序表当前长度
 }*SequenceList, List;
 */

/**
 初始化顺序表
 
 @param list 顺序表
 */
void init(List &list){
    list.data = (DataType*)malloc(sizeof(DataType) * LIST_INIT_SIZE);
    list.size = LIST_INIT_SIZE;
    list.length = 0;
}

/**
 初始化静态顺序表
 
 void init(List &list){
     list.length = 0;
 }
 */

/**
 判断索引在顺序表中是否合法
 
 @param seqList 顺序表
 @param index 索引
 @param isInsideIndex 是否在在索引范围内
 @return true合法,fase非法
 */
bool isIndexLegal(SequenceList seqList, int index, bool isInsideIndex){
    int offs = isInsideIndex ? -1 : 0;
    return index>=0 && index <= seqList->length + offs;
}

/**
 增加顺序表容量
 
 @param seqList 顺序表
 @return true容量增加成功,fase容量增加失败
 */
bool incrementCapacity(SequenceList seqList){
    seqList->data = (DataType*)realloc(seqList->data, sizeof(DataType) * (LIST_INCREMENT_SIZE + seqList->length));
    seqList->size += LIST_INCREMENT_SIZE;
    return seqList ? true : false;
}

/**
 判断顺表是否已满
 
 @param seqList 顺序表
 @return true已满,fase未满
 */
bool isFull(SequenceList seqList){
    if(seqList->length >= seqList->size){
        return true;
    }else{
        return false;
    }
}

/**
 顺序表插入的预处理
 1.判断容量是否已满；
 2.增加容量；
 3.判断索引是否合法；
 
 @param seqList 顺序表
 @param index 索引
 @return true能插入,false不能插入
 */
bool prepareInsert(SequenceList seqList , int index){
    if(isFull(seqList)){
        bool incrementedResut =incrementCapacity(seqList);
        if(!incrementedResut){
            return false;
        }
    }
    if(!isIndexLegal(seqList, index, false)){
        return false;
    }
    return true;
}

/**
 向顺序表指定位置插入元素
 
 @param seqList 顺序表
 @param data 元素
 @param index 索引(从0开始)
 @return true插入成功,fase插入失败
 */
bool insert(SequenceList seqList, int index, DataType data){
    
    //判断数据能否插入
    if(!prepareInsert(seqList, index)){
        return false;
    }
    
    //移动元素
    for (int i = seqList->length-1; i>=index; i--) {
        seqList->data[i+1] = seqList->data[i];
    }
    
    //插入元素
    seqList->data[index] = data;
    
    //长度+1
    seqList->length++;
    
    return true;
}

/**
 向顺序表尾部追加元素

 @param seqList 线性表
 @param data 数据
 @return true插入成功,fase插入失败
 */
bool append(SequenceList seqList, DataType data){
    
    //判断数据能否插入
    if(!prepareInsert(seqList, 0)){
        return false;
    }
    
    //追加元素
    seqList->data[seqList->length] = data;
    
    //长度+1
    seqList->length++;
    
    return true;
}

/**
 删除指定索引的元素

 @param seqList 顺序表
 @param index 索引
 @return true删除成功,false删除失败
 */
bool deleteByIndex(SequenceList seqList, int index){
    
    //判断索引是否合法
    if(!isIndexLegal(seqList, index, true)){
        return false;
    }
    
    //将指定索引元素后的每个元素向索引0方向移动一个单位即可删除元素,也保证了数据逻辑连续性
    for (int i = index; i < seqList->length; i++) {
        seqList->data[i] = seqList->data[i+1];
    }
    
    //长度-1
    seqList->length--;
    
    return true;
}

/**
 根据索引查询元素

 @param index 索引
 @return 元素
 */
DataType getByIndex(SequenceList seqList, int index){
    
    //判断索引是否合法
    if(!isIndexLegal(seqList, index, true)){
        exit(1);
    }
    
    return seqList->data[index];
}

/**
 根据数据查询索引
 
 @param data 数据
 @return 索引
 */
DataType getIndexByValue(SequenceList seqList, DataType data){
    for (int i = 0; i < seqList->length; i++) {
        if(seqList->data[i] == data){
            return i;
        }
    }
    return -1;
}

/**
 遍历顺序表
 
 @param seqList 顺序表
 */
void traverse(SequenceList seqList){
    for (int i=0; i<seqList->length; i++) {
        std::cout<<seqList->data[i]<<std::endl;
    }
}

int main(int argc, const char * argv[]) {
    List list;
    init(list);
    SequenceList seqList = &list;
    insert(seqList, 0, 1);
    insert(seqList, 1, 2);
    insert(seqList, 2, 3);
    insert(seqList, 3, 4);
    insert(seqList, 4, 5);
    append(seqList, 6);
    deleteByIndex(seqList,0);
    traverse(seqList);
    std::cout<<getByIndex(seqList, 0)<<std::endl;
    std::cout<<getIndexByValue(seqList, 2)<<std::endl;
    return 0;
}


