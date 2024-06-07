#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>



struct dll {
	struct dll *prev;
	char ch[26];
	struct dll *next;
};
typedef struct dll DLL;

DLL buffer[15000];
int buffer_count = 0;

typedef struct {
	DLL *MAP[26];
} WordDictionary;

void my_strcpy(char *dest, char *src)
{
	while (*src) {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

int my_strlen(char *ch)
{
	int len =0;
	while (*ch) {
		len++;
		ch++;
	}
	return len;
}

int my_strcmp(char *str1, char *str2)
{
	while (*str1 == *str2) {
		if(*str1 == '\0')
			break;
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}



DLL *create_dll_node(char *ch)
{
	DLL *temp;
	temp = &buffer[buffer_count++];
	my_strcpy(temp->ch, ch);
	temp->next = NULL;
	temp->prev = NULL;
	return(temp);
}


WordDictionary* wordDictionaryCreate() {
	int i;
	WordDictionary *obj = NULL;
	obj = (WordDictionary *)malloc(sizeof(WordDictionary));
	for(i = 0; i < 26; i++)
		obj->MAP[i] = NULL;
	buffer_count = 0;
	return(obj);
}

void insert_in_dll(DLL **head_ref, char *ch)
{
	DLL *temp;
	if ((*head_ref) == NULL) {
		*head_ref = create_dll_node(ch);
		return;
	}

	temp = create_dll_node(ch);
	temp->next = (*head_ref);
	(*head_ref)->prev = temp;
	*head_ref = temp;
}

void wordDictionaryAddWord(WordDictionary* obj, char* word) {
	int len;
	len = my_strlen(word);
	insert_in_dll(&obj->MAP[len], word);
}

bool search(char *ori, char *word, int len)
{

	int i;
	for(i = 0; i < len; i++) {
		if (word[i] == '.')
			continue;
		if (ori[i] != word[i])
			return false;
	}
	return true;
}


bool search_in_list(DLL *root, char *word, int len)
{
	DLL *temp = root;
	bool flag = false;
	while ( temp ) {
		flag = search(temp->ch, word, len);
		if (flag)
			return true;
		temp = temp->next;
	}
	return false;
}

bool wordDictionarySearch(WordDictionary* obj, char* word) {
	int len;
	len = my_strlen(word);
	return(search_in_list(obj->MAP[len], word, len));
}

void wordDictionaryFree(WordDictionary* obj) {
	int i;
	DLL *temp, *temp1;
	for (i = 0;i < 26; i++) {
		obj->MAP[i] = NULL;
		buffer_count = 0;
	}
	free(obj);
	obj = NULL;
}
