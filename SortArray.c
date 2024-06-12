#include<stdio.h>
#include<stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int map[201] = {0};
int middle = 100;

struct list {
	struct list *next;
	int num;
};
typedef struct list LL;
LL *freq_map[101]= {NULL};
LL buffer[1000];
int buffer_count=0;
LL *get_list_node(int num)
{
	LL *temp;
	temp = &buffer[buffer_count++];
	temp->num = num;
	temp->next = NULL;
	return temp;
}

void insert_in_sorted_order(LL **head_ref, int num)
{
	LL *new_node = get_list_node(num);
	LL *temp,*prev;
	if (*head_ref == NULL) {
		*head_ref = new_node;
		return;
	}
	if (num >= (*head_ref)->num) {
		new_node->next = *head_ref;
		*head_ref = new_node;
		return;
	}


	temp = *head_ref;
	while (temp && temp->num > num) {
		prev = temp;
		temp = temp->next;
	}
	prev->next = new_node;
	new_node->next = temp;
}
void init()
{
    int i;
    for(i=0;i<201;i++)
        map[i] = 0;
    for(i=0;i<101;i++)
        freq_map[i] = NULL;
    buffer_count = 0;

}

int* frequencySort(int* nums, int numsSize, int* returnSize)
{
	int i;
	int x = 0;
	LL *temp;
    int *result;
    printf("numsSize %d returnSize = %d\n", numsSize, *returnSize);
    init();
	result = (int *)malloc(numsSize*sizeof(int));
	for (i = 0; i < numsSize; i++)
		map[nums[i]+middle]++;
	for (i = 0; i < numsSize; i++) {
		insert_in_sorted_order(&freq_map[map[nums[i]+middle]], nums[i]);
	}
	for(i=0;i<101;i++) {
		if(freq_map[i]) {
			temp = freq_map[i];
			while(temp) {
				//printf("%d\n", temp->num);
				result[x] = temp->num;
                x++;
                //returnSize++;
				temp = temp->next;
			}
		}
	}
    for(i=0;i<numsSize;i++)
    printf("%d\n", result[i]);
    *returnSize = numsSize;
	return result;
}
