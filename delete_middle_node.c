#include<stdio.h>
#include<stdlib.h>



struct ListNode {
	int val;
	struct ListNode *next;
};

typedef struct ListNode LIST;
#if 1
struct ListNode* removeElements(struct ListNode* head, int val) {
	LIST *prev;
	LIST *temp1; 
	LIST *temp = head;
	prev = temp;
	while (temp) {
		if (temp->val == val) {
			if (temp == head){
				temp1 = head->next;
				free(head);
				head = temp1;
				temp = temp1;
			} else {
				temp1 = temp->next;
				prev->next = temp->next;
				free(temp);
				temp = temp1;
			}
		} else {
			prev = temp;
			temp = temp->next;
		}
	}
	return head;
}

void print_node(LIST *head)
{
	LIST *temp = head;
	while(temp) {
		printf("temp->val = %d\n", temp->val);
		temp = temp->next;
	}
}
struct ListNode* deleteMiddle(struct ListNode* head) {
	LIST *prev;
	LIST *slow, *fast;
	slow = fast = head;
	if (head == NULL)
		return NULL;
	if (head->next == NULL)
		return NULL;

	while(slow && fast->next) {
		prev = slow;
		slow = slow->next;
		fast = fast->next->next;
	}
	prev->next = slow->next;
	free(slow);
	return head;
}
#endif

int main()
{
	LIST *head = NULL;
	head = (LIST *)malloc(sizeof(LIST));
	head->val = 1;
	head->next = (LIST *)malloc(sizeof(LIST));
	head->next->val = 2;
	head->next->next = (LIST *)malloc(sizeof(LIST));
	head->next->next->val = 6;
	head->next->next->next = (LIST *)malloc(sizeof(LIST));;
	head->next->next->next->val = 3;
	head->next->next->next->next = (LIST *)malloc(sizeof(LIST));
	head->next->next->next->next->val = 4;

	head->next->next->next->next->next = (LIST *)malloc(sizeof(LIST));
	head->next->next->next->next->next->val = 5;
	head->next->next->next->next->next->next = (LIST *)malloc(sizeof(LIST));
	head->next->next->next->next->next->next->val = 6;
	head->next->next->next->next->next->next->next = NULL;
	print_node(head);
	printf("AFTER\n");
	head = removeElements(head, 6);
	print_node(head);
	return 0;
}
