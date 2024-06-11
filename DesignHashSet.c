#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct {
	bool map[1000001];
} MyHashSet;


MyHashSet* myHashSetCreate() {
	MyHashSet *obj;
	obj = (MyHashSet *)malloc(1* sizeof(MyHashSet));
    //obj->map[0]= false;
    memset(obj->map, 0, 1000001);
	return obj;
}

void myHashSetAdd(MyHashSet* obj, int key) {
	obj->map[key] = true;
}

void myHashSetRemove(MyHashSet* obj, int key) {
	obj->map[key] = false;
}

bool myHashSetContains(MyHashSet* obj, int key) {
	if (!obj->map[key])
		return false;
	return true; 
}

void myHashSetFree(MyHashSet* obj) {
	free(obj);
}

/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);

 * myHashSetRemove(obj, key);

 * bool param_3 = myHashSetContains(obj, key);

 * myHashSetFree(obj);
 */
