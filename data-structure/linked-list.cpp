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
 判断索引在顺序表中是否合法
 
 @param headNode 头结点
 @param index 索引
 @param isInsideIndex 是否在在索引范围内
 @return true合法,fase非法
 */
bool isIndexLegal(PNode headNode, int index, bool isInsideIndex){
    int offs = isInsideIndex ? 0 : 1;
    return index>=-1 && index < headNode->data + offs;
}

/**
 根据数据查找结点
 
 @param headNode 头结点
 @param data 数据
 @return 结点
 */
PNode findByValue(PNode headNode, DataType data){
    PNode temp = headNode->next;
    while (temp != headNode && temp->data != data) {
        temp = temp->next;
    }
    return temp->data == data ? temp : NULL;
}

/**
 根据索引查找结点

 @param headNode 头结点
 @param index 索引([-1,length])
 @return 结点
 */
PNode findByIndex(PNode headNode, int index){
    
    //判断索引是否合法
    if(!isIndexLegal(headNode, index, true)){
        return NULL;
    }
    
    //顺序查找
    PNode temp = headNode;
    int count = -1;
    while (count < index) {
        count++;
        temp = temp->next;
    }
    return temp;
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
    
    //查找操作结点(指定索引的前一个结点)
    PNode operationNode = findByIndex(headNode, index-1);
    if(!operationNode){
        exit(EXIT_FAILURE);
    }
    
    //创建结点
    PNode newNode = createNode(data);
    //1.新结点连接到目标位置结点
    newNode->next = operationNode->next;
    //2.新结点连接到目标结点的前一结点
    newNode->prior = operationNode;
    //3.目标位置结点连接到新结点
    operationNode->next->prior = newNode;
    //4.目标位置结点的前一个结点连接到新结点
    operationNode->next = newNode;
    
    //长度+1
    headNode->data++;
    
}

/**
 通过指定索引删除

 @param headNode 头结点
 @param index 索引
 */
void deleteByIndex(PNode headNode, int index){
    
    //查找操作结点(指定索引的前一个结点)
    PNode operationNode = findByIndex(headNode, index-1);
    if(!operationNode){
        exit(EXIT_FAILURE);
    }
    //查找待删除结点的后一个结点
    PNode deletedNextNode = operationNode->next->next;
    
    //释放待删除结点的内存空间(物理删除)
    PNode deletedNode = operationNode->next;
    free(deletedNode);
    
    //操作结点连接待删除结点的后一个结点
    operationNode->next = deletedNextNode;
    deletedNextNode->prior = operationNode;
    
    //长度-1
    headNode->data--;
}

/**
 通过指定数据删除
 
 @param headNode 头结点
 @param data 数据
 */
void deleteByValue(PNode headNode, DataType data){
    
    //查找待删除结点
    PNode deletedNode = findByValue(headNode, data);
    if(!deletedNode){
        exit(EXIT_FAILURE);
    }
    
    //获取操作结点(指定索引的前一个结点)
    PNode operationNode = deletedNode->prior;
    if(!operationNode){
        exit(EXIT_FAILURE);
    }
    
    //查找待删除结点的后一个结点
    PNode deletedNextNode = deletedNode->next;
    
    //释放待删除结点的内存空间(物理删除)
    free(deletedNode);
    
    //操作结点连接待删除结点的后一个结点
    operationNode->next = deletedNextNode;
    deletedNextNode->prior = operationNode;
    
    //长度-1
    headNode->data--;
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
    insert(headNode, 0, 0);
    insert(headNode, 1, 6);
    deleteByIndex(headNode, 0);
    deleteByValue(headNode, 2);
    traverse(headNode);
    return 0;
}
