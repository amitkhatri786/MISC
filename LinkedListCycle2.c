#include<stdio.h>


struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct ListNode LL;

struct ListNode *detectCycle(struct ListNode *head) {
	LL *slow, *fast;
	int found = 0;
	slow = fast = head;
	if (head == NULL)
		return NULL;
	while (slow && fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {
			found = 1;
			break;
		}
	}

	if (found) {
		slow = head;
		while (slow != fast) {
			slow = slow->next;
			fast = fast->next;
		}
		return slow;
	}
	else {
		return NULL;
	}
}
