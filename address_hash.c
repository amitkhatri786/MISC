#include<stdio.h>
#include<stdlib.h>

#define HASH_SIZE	5381

struct list {
	struct Node *r_node;
	struct Node *new_node;
	struct list *next;
};
typedef struct list LIST;
LIST list_buffer[100000];
int list_buffer_count = 0;

LIST *hash_map[HASH_SIZE + 1] = {0};
/*
struct Node {
	int x;
	struct Node *next;
	struct Node *random;
};*/
typedef struct Node RANDOM_LIST;
RANDOM_LIST random_list_buffer[100000];
int random_list_buffer_count = 0;


LIST *create_list_node(RANDOM_LIST *p, RANDOM_LIST *new_head)
{
	LIST *node;
	node = &list_buffer[list_buffer_count];
	node->r_node = p;
	node->new_node = new_head;
	node->next = NULL;
	list_buffer_count++;
	return(node);
}

RANDOM_LIST *create_random_list_node(int x)
{
	RANDOM_LIST *node;
	node = &random_list_buffer[random_list_buffer_count];
	node->val = x;
	node->next = NULL;
	node->random = NULL;
	random_list_buffer_count++;
	return(node);
}

void insert_in_list(LIST **head, LIST *new_node)
{
	if (!head) {
		*head = new_node;
		return;
	}

	new_node->next = *head;
	*head = new_node;

}

void insert_in_hash_map(RANDOM_LIST *node, RANDOM_LIST *new_head)
{
	unsigned int address = (int )node;
	LIST *new_node;
#if 1
	printf("%s-%d --> %d\n", __func__, __LINE__, address%HASH_SIZE);
#endif
	new_node = create_list_node(node, new_head);
	insert_in_list(&hash_map[address%HASH_SIZE], new_node);

}

RANDOM_LIST *search_in_hash_map(RANDOM_LIST *node)
{
	LIST *temp;
	unsigned int hash = (int ) node;
	hash = hash%HASH_SIZE;
	temp = hash_map[hash];
#if 1
	printf("%s-%d --> %d\n", __func__, __LINE__, hash);
#endif
	while (temp) {
		if (temp->r_node == node)
			return temp->new_node;
	
		temp = temp->next;
	}
	return NULL;
}

RANDOM_LIST  *copyRandomList(RANDOM_LIST *head)
{
	RANDOM_LIST *temp = head;
	RANDOM_LIST *new_temp, *prev = NULL;
	RANDOM_LIST *new_head;
	RANDOM_LIST *x, *y;
	int address;

    if(!head)
        return NULL;
	new_temp = create_random_list_node(temp->val);
	insert_in_hash_map(temp, new_temp);
	new_head = new_temp;
	while (temp->next) {
#ifdef DEBUG
		printf("%s-%d\n", __func__, __LINE__);
#endif
		new_temp->next = create_random_list_node(temp->next->val);
		temp = temp->next;
		insert_in_hash_map(temp, new_temp->next);
		new_temp = new_temp->next;
	}
	//prev->next = NULL;
	new_temp = new_head;
	while(new_temp) {
		printf("new_temp->val = %d\n", new_temp->val);
		new_temp = new_temp->next;
	}
	temp = head;
	new_temp = new_head;
	while (temp) {
		x = search_in_hash_map(temp);
		y = search_in_hash_map(temp->random);
        if (x) {
            printf("x->val= %d\n", x->val);
            if (y)
                printf("y->val= %d\n", y->val);
		    x->random = y;
        }
		temp = temp->next;
	}
	return(new_head);
}

