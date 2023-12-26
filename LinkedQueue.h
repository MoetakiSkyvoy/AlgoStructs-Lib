#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

// LinkedQueue.h
// Author: 严蔚敏 & 萌瀧·天遊(skyvoy@moetaki.com)

// ----- Implementation and basic operations of queues -----
// ----- 队列的实现和基本操作 -----

// Header file references
// 头文件引用
#include "stdblibal.h" // 调用本项目的基础头文件

// Predefined constants and types
// 预定义常量与类型
typedef int QElemType; // 存储数据的类型

// Storage structure representation of queues
// 队列的存储结构展示
typedef struct QNode{
	QElemType data;
	struct QNode* next;
}QNode;
typedef QNode* QueuePtr;
typedef struct LinkedQueue{
	QueuePtr front; // 队头指针
	QueuePtr rear; // 队尾指针
}LinkedQueue;

// Basic operating functions
// 基本操作函数

/**
 * Construct an empty queue.
 * 构造一个空队列。
 * 
 * @param Q LinkedQueue结构体指针
 * @return 状态结果
 */
Status InitQueue(LinkedQueue* Q){
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode)); // 从右向左赋值
	if(!(Q->front)) exit(OVERFLOW);
	
	Q->front->next = NULL; // 初始化
	
	return OK;
} // InitQueue

/**
 * Destroy a queue.
 * 销毁一个队列。
 * 
 * @param Q LinkedQueue结构体指针
 * @return 状态结果
 */
Status DestroyQueue(LinkedQueue* Q){
	while(Q->front){
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	
	return OK;
} // DestroyQueue

/**
 * Enqueue.
 * 入队操作。
 * 
 * This function inserts element e as the new tail element of Q and returns the result status.
 * 该函数插入元素e作为Q的新的队尾元素，并返回操作结果状态。
 * 
 * @param Q LinkedQueue结构体指针
 * @param e 被插入的元素
 * @return 状态结果
 */
Status EnQueue(LinkedQueue* Q, QElemType e){
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);
	p->data = e; p->next = NULL; // 将元素e封装入新结点
	
	Q->rear->next = p; Q->rear = p; // 更新队尾指针
	
	return OK;
} // EnQueue

/**
 * Check whether a queue is empty.
 * 检测某个队列是否为空。
 * 
 * @param Q LinkedQueue结构体指针
 * @return 结果
 */
Status isQueueEmpty(LinkedQueue* Q){
	return Q->front == Q->rear; // 若队列为空，返回真值
} // QueueEmpty

/**
 * DeQueue.
 * 出队操作。
 * 
 * If the queue is not empty, this function deletes the head element of Q,
 * returns its value using e, and returns the operation result status.
 * 若队列不空，该函数则删除Q的队头元素，用e返回其值，并返回操作结果状态。
 * 
 * @param Q LinkedQueue结构体指针
 * @param e 存储结果的元素的指针
 * @return 状态结果
 */
Status DeQueue(LinkedQueue* Q, QElemType* e){
	if(isQueueEmpty(Q)) return ERROR; // 失败
	
	QueuePtr p = Q->front->next;
	
	*e = p->data;
	
	Q->front->next = p->next;
	if(p == Q->rear) Q->rear = Q->front; // 若出队前只剩一个结点，防止队尾指针丢失
	free(p); // 销毁封装队头的结点
	
	return OK;
} // DeQueue

#endif
