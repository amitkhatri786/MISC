#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

enum {
	ENQUEUE=1,
	DEQUEUE,
	FRONT,
	REAR,
	EMPTY,
	FULL,
};


struct ll{
	struct ll *next;
	int val;
};
typedef struct ll LL;



typedef struct {
	int capacity;
	int current_count;
	LL *head;
	LL *tail;
} MyCircularQueue;


LL *get_ll_node(int val)
{
	LL *temp;
	temp = (LL *)malloc(sizeof(LL));
	temp->next = NULL;
	temp->val = val;
	return temp;
}

void insert_in_ll(MyCircularQueue *obj, LL *new_node)
{
	LL *head, *tail;
	if (!obj->tail && !obj->head) {
		obj->tail = new_node;
		obj->head = new_node;
		obj->current_count++;
		return;
	}
	tail = obj->tail;
	tail->next = new_node;
	obj->tail = new_node;
	obj->current_count++;
}

void del_from_ll(MyCircularQueue *obj)
{
	LL *temp;
	if (!obj->head)
		return;
	if (!obj->tail)
		return;

	if (obj->head == obj->tail) {
		temp = obj->head;
		obj->head = NULL;
		obj->tail = NULL;
		free(temp);
		obj->current_count--;
		return;
	}
	temp = obj->head;
	obj->head = temp->next;
	free(temp);
	temp = NULL;
	obj->current_count--;
}

MyCircularQueue* myCircularQueueCreate(int k) {
	MyCircularQueue *obj;
	obj = (MyCircularQueue *)malloc(sizeof(MyCircularQueue));
	obj->capacity = k;
	obj->head = obj->tail = NULL;
	obj->current_count = 0;
	return (obj);
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {

	LL *temp;
	if (obj->current_count == obj->capacity)
		return false;
	temp = get_ll_node(value);
	insert_in_ll(obj, temp);
	return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
	if (obj->current_count == 0)
		return false;
	del_from_ll(obj);
	return true;
}

int myCircularQueueFront(MyCircularQueue* obj) {
	if (!obj->head)
		return -1;
	return(obj->head->val);
}

int myCircularQueueRear(MyCircularQueue* obj) {
	if (!obj->tail)
		return -1;
	return(obj->tail->val);
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
	if (obj->current_count == 0)
		return true;
	return false;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
	if (obj->current_count == obj->capacity)
		return true;
	return false;
}

void myCircularQueueFree(MyCircularQueue* obj) {
	LL *temp;
	LL *temp1;
	temp = obj->head;
	while (temp) {
		temp1 = temp->next;
		free(temp);
		temp = temp1;
	}
	free(obj);
	obj = NULL;
}

int main()
{
	MyCircularQueue *obj;
	int capacity;
	int x;
	int operation;
	scanf("%d", &capacity);
	obj = myCircularQueueCreate(capacity);
	while(scanf("%d", &operation)!=EOF) {
		switch(operation) {
			case ENQUEUE:
				scanf("%d", &x);
				printf("%d\n", myCircularQueueEnQueue(obj, x));
				break;
			case DEQUEUE:
				printf("%d\n", myCircularQueueDeQueue(obj));
				break;
			case FRONT:
				printf("%d\n", myCircularQueueFront(obj));
				break;
			case REAR:
				printf("%d\n", myCircularQueueRear(obj));
				break;
			case FULL:
				printf("%d\n", myCircularQueueIsFull(obj));
				break;
			case EMPTY:
				printf("%d\n", myCircularQueueIsFull(obj));
				break;
		}

	}
	myCircularQueueFree(obj);
	return 0;
}

