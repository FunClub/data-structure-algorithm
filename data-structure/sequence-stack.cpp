/**
 * 顺序栈
 *
 * Created by 刘滔 on 2018/9/17.
 * Copyright © 2018年 刘滔. All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include "iostream"
using namespace std;

//常量定义
const int STACK_INIT_SIZE = 1;
const int STACK_INCREMENT_SIZE = 1;

//类型定义
typedef int DataType;

//栈的结构体定义
typedef struct Node{
    DataType* top;//栈顶指针
    DataType* base;//栈底指针
    int size;//栈最大容量
}*SequenceStack, Stack;

/**
 静态顺序表的结构体定义
 typedef struct Node{
 DataType data[LIST_INIT_SIZE];//存放数据
 int length;//顺序表当前长度
 }*SequenceList, List;
 */

/**
 初始化栈
 
 @param stack 栈
 */
void init(Stack &stack){
    int size = sizeof(Stack) * STACK_INIT_SIZE;
    stack.top = (DataType*)malloc(size);
    stack.base = stack.top;
    stack.size = size;
    //std::cout<<"初始化成功剩余容量="<<stack.size-(stack.top - stack.base)*sizeof(DataType)<<"，base="<<stack.base<<"，size="<<size<<std::endl;
}

/**
 初始化静态顺序表
 
 void init(List &list){
 list.length = 0;
 }
 */

/**
 增加顺序栈容量
 
 @param seqStack 顺序栈
 @return true容量增加成功,fase容量增加失败
 */
bool incrementCapacity(SequenceStack seqStack){
    int size = sizeof(DataType) * STACK_INCREMENT_SIZE + seqStack->size;
    DataType* newData = (DataType*)realloc(seqStack->top, size);
    if(newData){
        seqStack->top = newData;
        seqStack->size = size;
        std::cout<<"增加容量成功剩余容量="<<seqStack->size-(seqStack->top - seqStack->base)*sizeof(DataType)<<",top="<<seqStack->top<<"，base="<<seqStack->base<<"，size="<<seqStack->size<<std::endl;
       
        return true;
    }else{
        exit(EOVERFLOW);
    }
}

/**
 判断顺序栈是否已满
 
 @param seqStack 顺序栈
 @return true已满,fase未满
 */
bool isFull(SequenceStack seqStack){
    std::cout<<"剩余容量="<<seqStack->size-(seqStack->top - seqStack->base)*sizeof(DataType)<<",top="<<seqStack->top<<"，base="<<seqStack->base<<"，size="<<seqStack->size<<std::endl;
    if(seqStack->size-(seqStack->top - seqStack->base)*sizeof(DataType)==0){
        return true;
    }else{
        return false;
    }
}

/**
 入栈的预处理

 @param seqStack 顺序栈
 @return true能插入,false不能插入
 */
bool preparePush(SequenceStack seqStack){
    
    // 判断容量是否已满；
    if(isFull(seqStack)){
        
        // 增加容量；
        bool incrementedResut =incrementCapacity(seqStack);
        
        if(!incrementedResut){
            return false;
        }
    }
    return true;
}

/**
 入栈
 
 @param seqStack 顺序栈
 @param data 元素
 */
void push(SequenceStack seqStack, DataType data){
    
    //判断数据能否入栈
    if(!preparePush(seqStack)){
        exit(EXIT_SUCCESS);
    }
    
    //入栈
    *++seqStack->top = data;
    
}

void pop(SequenceStack seqStack){
    while (seqStack->top != seqStack->base) {
        std::cout<<*seqStack->top--<<std::endl;
    }
}



int main(int argc, const char * argv[]) {
    Stack stack;
    init(stack);
    SequenceStack seqStack = &stack;
    std::cout<<"size="<<seqStack->size<<std::endl;
    std::cout<<"base="<<seqStack->base<<std::endl;
    std::cout<<"top="<<seqStack->top<<std::endl;
    stack.top++;
    std::cout<<"top="<<seqStack->top<<std::endl;
    return 0;
}



