/**
 * 顺序表
 * Created by 刘滔 on 2018/9/14.
 * Copyright © 2018年 刘滔. All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include "iostream"
using namespace std;

//常量定义
const int LIST_INIT_SIZE = 1;
const int LIST_INCREMENT_SIZE = 1;

//类型定义
typedef int DataType;

//结构体定义
typedef struct Node{
    DataType* data;//存放数据
    int length;//顺序表当前长度
    int size;//顺序表最大容量
}*SequenceList, Node;

/**
 初始化顺序表
 
 @return 顺序表
 */
SequenceList init(){
    SequenceList list = (SequenceList)malloc(sizeof(Node));
    list->data = (DataType*)malloc(sizeof(DataType) * LIST_INIT_SIZE);
    list->size = LIST_INIT_SIZE;
    list->length = 0;
    return list;
}

/**
 判断顺表是否已满
 
 @param list 顺序表
 @return true已满,fase未满
 */
bool isFull(SequenceList &list){
    if(list->length >= list->size){
        return true;
    }else{
        return false;
    }
}

/**
 增加顺序表容量
 
 @param list 顺序表
 @return true容量增加成功,fase容量增加失败
 */
bool incrementCapacity(SequenceList &list){
    list->data = (DataType*)realloc(list->data, sizeof(DataType) * (LIST_INCREMENT_SIZE + list->length));
    list->size += LIST_INCREMENT_SIZE;
    return list ? true : false;
}

/**
 判断索引在顺序表中是否合法
 
 @param list 顺序表
 @param index 索引
 @return true合法,fase非法
 */
bool isIndexLegal(SequenceList &list, int index){
    return index>=0 && index <= list->length;
}

/**
 顺序表插入的预处理
 1.判断容量是否已满；
 2.增加容量；
 3.判断索引是否合法；
 
 @param list 顺序表
 @param index 索引
 @return true能插入,false不能插入
 */
bool prepareInsert(SequenceList &list , int index){
    if(isFull(list)){
        bool incrementedResut =incrementCapacity(list);
        if(!incrementedResut){
            return false;
        }
    }
    if(!isIndexLegal(list, index)){
        return false;
    }
    return true;
}

/**
 向顺序表指定位置插入元素
 
 @param list 顺序表
 @param data 元素
 @param index 索引(从0开始)
 @return true插入成功,fase插入失败
 */
bool insertToIndex(SequenceList &list, int index, DataType data){
    
    //判断数据能否插入
    if(!prepareInsert(list, index)){
        return false;
    }
    
    //移动元素
    for (int i = list->length-1; i>=index; i--) {
        list->data[i+1] = list->data[i];
    }
    
    //插入元素
    list->data[index] = data;
    
    //长度+1
    list->length++;
    
    return true;
}

/**
 遍历顺序表
 
 @param list 顺序表
 */
void traverse(SequenceList &list){
    for (int i=0; i<list->length; i++) {
        std::cout<<list->data[i]<<std::endl;
    }
}

int main(int argc, const char * argv[]) {
    SequenceList list =  init();;
    insertToIndex(list, 0, 1);
    insertToIndex(list, 1, 2);
    insertToIndex(list, 2, 3);
    insertToIndex(list, 3, 4);
    insertToIndex(list, 4, 5);
    traverse(list);
    return 0;
}


