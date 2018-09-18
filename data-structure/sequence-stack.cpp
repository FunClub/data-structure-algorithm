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
 初始化栈
 
 @param stack 栈
 */
void init(Stack &stack){
    int initMemorySize = sizeof(DataType) * STACK_INIT_SIZE;
    stack.top = (DataType*)malloc(initMemorySize);
    stack.base = stack.top;
    stack.size = STACK_INIT_SIZE;
}

/**
 增加顺序栈容量
 
 @param seqStack 顺序栈
 @return true容量增加成功,fase容量增加失败
 */
bool incrementCapacity(SequenceStack seqStack){
    int newMemorySize= (seqStack->size + STACK_INCREMENT_SIZE) * sizeof(DataType);
    DataType* newMemory = (DataType*)realloc(seqStack->base, newMemorySize);
    if(newMemory){
        seqStack->base = newMemory;
        seqStack->top = seqStack->base+seqStack->size;
        seqStack->size += STACK_INCREMENT_SIZE;
        std::cout<<"内存分配成功"<<std::endl;
        return true;
    }else{
        std::cout<<"内存分配失败"<<std::endl;
        exit(EOVERFLOW);
    }
}

/**
 判断顺序栈是否已满
 
 【注意】
 |相同类型的指针相减|=间隔元素的个数
 例如：已知变量A==B为int*类型
 有：A-B==0;A++,A-B==1,B-A==-1;
 
 @param seqStack 顺序栈
 @return true已满,fase未满
 */
bool isFull(SequenceStack seqStack){
    if(seqStack->top - seqStack->base >= seqStack->size){
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
    *seqStack->top++ = data;
    std::cout<<"剩余容量="<<seqStack->size-(seqStack->top-seqStack->base)<<std::endl;
}

/**
 遍历栈
 
 @param seqStack 顺序栈
 */
void traverse(SequenceStack seqStack){
    while (seqStack->top != seqStack->base) {
        std::cout<<*--seqStack->top<<std::endl;
    }
}

int main(int argc, const char * argv[]) {
    Stack stack;
    init(stack);
    SequenceStack seqStack = &stack;
    push(seqStack, 1);
    push(seqStack, 2);
    push(seqStack, 3);
    traverse(seqStack);
    return 0;
}



