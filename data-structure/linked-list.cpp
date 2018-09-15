/**
 * 双向循环链表(动态分配内存)
 *
 * Created by 刘滔 on 2018/9/15.
 * Copyright © 2018年 刘滔. All rights reserved.
 */
#include <iostream>
#include <stdio.h>
using namespace std;

//类型定义
typedef int DataType;

//链表结点结构体定义
typedef struct Node{
    DataType data;//存放数据(头结点则)
    struct Node* prior;//前驱结点
    struct Node* next;//后继结点
}*PNode, Node;

/**
 初始化链表
 
                head指针
    ******************************
    *         |         |        *
 ****  prior  |   data  |  next  ****
 *  *         |         |        *  *
 *  ******************************  *
 *                ^  ^              *
 ******************  ****************

 @param headNode 头结点
 */
void init(Node &headNode){
    headNode.next = &headNode;
    headNode.prior = &headNode;
    headNode.data = 0;
}

/**
 判断索引在链表中是否合法
 
 @param headNode 头结点
 @param index 索引
 @return true合法,fase非法
 */
bool isIndexLegal(PNode headNode, int index){
    return index>=1 && index <= headNode->data+1;
}

/**
 创建结点

 @param data 结点数据
 @return 新结点
 */
PNode createNode(DataType data){
    PNode newNode = (PNode)malloc(sizeof(Node));
    if(!newNode){
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    return newNode;
}

/**
 在链表尾部追加新结点

 @param headNode 头结点
 @param data 数据
 */
void append(PNode headNode, DataType data){
    
    //创建结点
    PNode newNode = createNode(data);
    
    //1.将新结点连接到尾结点
    newNode->prior = headNode->prior;
    //2.新结点连接到头结点
    newNode->next = headNode;
    //3.尾结点连接到新结点
    headNode->prior->next = newNode;
    //4.头结点连接到尾结点
    headNode->prior = newNode;
    
    //长度+1
    headNode->data++;
}

/**
 插入元素
 
 @param headNode 头结点
 @param index 插入位置(从1开始)
 @param data 数据
 */
void insert(PNode headNode, int index, DataType data){
    
    //判断插入位置是否合法
    if(!isIndexLegal(headNode, index)){
        exit(-1);
    }
    
    //创建结点
    PNode newNode = createNode(data);
    
    //找到目标位置结点的前一个结点
    PNode temp = headNode;
    int count = 0;
    while (temp->next != NULL && count != index-1) {
        count++;
        temp = temp->next;
    }
    
    //1.新结点连接到目标位置结点
    newNode->next = temp->next;
    //2.新结点连接到目标结点的前一结点
    newNode->prior = temp;
    //3.目标位置结点连接到新结点
    temp->next->prior = newNode;
    //3.目标位置结点的前一个结点连接到新结点
    temp->next = newNode;
    
    headNode->data++;
    
}

/**
 遍历顺序表
 
 @param headNode 头结点
 */
void traverse(PNode headNode){
    PNode temp = headNode;
    while (temp->next != headNode) {
        temp = temp->next;
        std::cout<<temp->data<<std::endl;
    }
}

int main(int argc, const char * argv[]) {
    Node node;
    init(node);
    PNode headNode = &node;
    append(headNode, 1);
    append(headNode, 2);
    append(headNode, 3);
    insert(headNode, 4, 0);
    traverse(headNode);
    return 0;
}
