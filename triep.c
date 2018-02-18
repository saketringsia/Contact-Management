#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')


struct TrieNode
{
	struct TrieNode *child[SIZE];
	bool isLast;
};
 

struct TrieNode *getnode(void)
{
	struct TrieNode *pNode;
	pNode=(struct TrieNode *)malloc(sizeof(struct TrieNode));
	if(pNode)
	{
	int i;
	pNode->isLast = false;
	for(i=0;i<SIZE;i++)
		pNode->child[i]=NULL;
	}
return pNode;
}

void insert(struct TrieNode *root,const char *key)
{
int level;
int length=strlen(key);
int index;
struct TrieNode *p=root;
	for(level=0;level<length;level++)
	{
	index=CHAR_TO_INDEX(key[level]);
		if(!p->child[index])
		p->child[index]=getnode();
	
	p=p->child[index];
}
	
	p->isLast=true;
	
}

int haveChildren(struct TrieNode *curr)
{
	for(int i=0;i<SIZE;i++)
		if(curr->child[i])
			return 1;
	return 0;
}

int deletion(struct TrieNode* *curr,char *str)
{
	if(*curr==NULL)
		return 0;
	if(*str)
	{
		if(*curr!=NULL && (*curr)->child[*str-'a'] != NULL && deletion(&((*curr)->child[*str-'a']),str+1) && (*curr)->isLast==false)
		{
			if(!haveChildren(*curr))
			{
				free(*curr);
				(*curr)=NULL;
				return 1;
			}
			else{
				return 0;
				}
		}
	}

	if(*str=='\0'&& (*curr)->isLast)
	{
		if(!haveChildren(*curr))
		{
			free(*curr);
			*curr=NULL;
			return 1;
		}
		
		else{
			(*curr)->isLast=false;
			return 0;
			}
		}
	return 0;
} 
void displayConUtil(struct TrieNode *root,struct TrieNode *curNode,char *prefix)
{
	
	if(curNode->isLast)
		printf("%s\n",prefix);
	for(char i=0;i<26;i++)
	{
		
		struct TrieNode *nextNode=curNode->child[i];
		if(nextNode!=NULL)
		{
			size_t q=strlen(prefix);
			char *q2=malloc(q+1+1);
			strcpy(q2,prefix);
			q2[q]=(char)(i+97);
			q2[q+1]='\0';
			displayConUtil(root,nextNode,q2);
			free(q2);
	}
}
}


void displayC(struct TrieNode *root,const char *str)
{

struct TrieNode *prevNode=root;
char prefix[]="";
int len=strlen(str);
int index=0;
int i;
char lastchar;
char *st2,*st1;
for(i=0;i<len;i++)
{
	size_t x=strlen(prefix);	
	st2=malloc(x+2);
	strcpy(st2,prefix);
	st2[x]=(char)str[i];
	st2[x+1]='\0';
	lastchar=st2[x];
	index=CHAR_TO_INDEX(lastchar);
	
	struct TrieNode *curNode=prevNode->child[index];
	
	if(curNode==NULL)
	{
	printf("\nNo results found for %s\n",st2);
	i++;
	strcpy(prefix,st2);
	break;
	}

	printf("\nSuggestions based on %s are\n",st2);
	displayConUtil(root,curNode,st2);
	prevNode=curNode;
	strcpy(prefix,st2);
}

for(;i<len;i++)
{
	size_t y=strlen(st2);	
	st1=malloc(y+2);
	strcpy(st1,st2);
	st1[y]=(char)str[i];
	st1[y+1]='\0';	
printf("\nNo results found for %s",st1);
free(st2);
free(st1);
}
}

int main()
{
char contacts[]="";int check=0;
struct TrieNode *root=getnode();
int i;int ch;
char query[]="";


printf("\n---------------------Welcome to your Phonebook----------------------\n");
while(1){
printf("\nSelect 1 to Create a new contact\n");
printf("\nSelect 2 to delete a  contact\n");
printf("\nSelect 3 to search for a contact\n\n");
printf("\n\nPress 4 to exit\n\n");
scanf("%d",&ch);
switch(ch)
{
case 1: printf("\nEnter the contact\n");
	scanf("%s",contacts);
	insert(root,contacts);
	break;
case 2: printf("\nEnter the contact to be deleted\n\n");
	scanf("%s",query); 
	check=deletion(&root,query);
	if(check==1)
	printf("\nContact deleted successfully\n");
	break;
case 3: printf("\nEnter the name of contact to be searched\n");
	scanf("%s",query);
	displayC(root,query);
	break;
default: exit(0);
}}
return 0;
}
