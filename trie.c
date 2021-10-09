#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <time.h>
struct TrieNode 
{ 
    struct TrieNode *children[52]; 
    int isEndOfWord; 
    int count;
}; 
int search(struct TrieNode *root, char *key);
struct TrieNode *getNode() 
{ 
    struct TrieNode *pNode = NULL; 
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode)); 
    if (pNode) 
    { 
        int i; 
        pNode->isEndOfWord = 0; 
        for (i = 0; i < 52; i++) 
            pNode->children[i] = NULL; 
    } 
    return pNode; 
} 
void insert(struct TrieNode *root, char *key) 
{ 
    int i,len,num; 
    len = strlen(key); 
    struct TrieNode *pCrawl = root; 
  	if(search(root,key)==1)
  	{
  		for (i = 0; i < len; i++) 
		{ 
		    num = (int)(key[i]-'A'); 
		    if(num>25)
		    	num-=6;
		    pCrawl = pCrawl->children[num];
		} 
		pCrawl->count=(pCrawl->count)+1;
  		return;
  	}
    for (i = 0; i < len; i++) 
    { 
        num = (int)(key[i]-'A'); 
        if(num>25)
			num-=6;
        if (!pCrawl->children[num]) 
            pCrawl->children[num] = getNode(); 
  
        pCrawl = pCrawl->children[num]; 
        pCrawl->count=0;
    } 
    pCrawl->isEndOfWord = 1; // last node is the leaf 
} 
int search(struct TrieNode *root, char *key) 
{ 
    int i,len,num; 
    len = strlen(key);
    struct TrieNode *pCrawl = root; 
    for (i = 0; i < len; i++) 
    { 
        num = (int)(key[i]-'A'); 
        if(num>25)
			num-=6;
        if (!pCrawl->children[num]) 
            return 0;
        pCrawl = pCrawl->children[num]; 
    } 
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
} 
int haveChildren(struct TrieNode* root)
{
	for (int i = 0; i < 52; i++)
		if (root->children[i])
			return 1;	// child found

	return 0;
}
int findNum(char *str)
{
	int num=(int)(*str-'A');
	if(num>25)
		num-=6;
	return num;
}
int deletion(struct TrieNode **root, char* str)
{
	if (*root == NULL)
		return 0;
	if (*str)
	{
		if (*root != NULL && (*root)->children[findNum(str)] != NULL && deletion(&((*root)->children[findNum(str)]), str + 1) && (*root)->isEndOfWord == 0)
		{
			if (!haveChildren(*root))
			{
				free(*root);
				(*root) = NULL;
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	if (*str == '\0' && (*root)->isEndOfWord)
	{
		if (!haveChildren(*root))
		{
			free(*root); // delete current node
			(*root) = NULL;
			return 1; // delete non-leaf parent nodes
		}
		else
		{
			// mark current node as non-leaf node (DON'T DELETE IT)
			(*root)->isEndOfWord = 0;
			return 0;	   // don't delete its parent nodes
		}
	}

	return 0;
}
int preReqDel(struct TrieNode *root, char* key)
{
	int i,len,num; 
    len = strlen(key);
    if(search(root,key))
    {
    	struct TrieNode *pCrawl = root; 
		for (i = 0; i < len; i++) 
		{ 
		    num = (int)(key[i]-'A'); 
		    if(num>25)
		    	num-=6;
		    pCrawl = pCrawl->children[num]; 
		} 
		if(pCrawl->count==0)
		{
			deletion(&root,key);
		}
		else
		{
			pCrawl->count=pCrawl->count-1;
		}
		return 0;
    }
    else
    {
    	printf("Element not found in the trie.\n");
    	return 1;
    }
}
void display(struct TrieNode* root, char str[], int level) 
{ 
	int i;
    if (root->isEndOfWord)  
    { 
        str[level] = '\0'; 
        printf("%25s\t\t%5d\n",str,root->count+1);
    } 
    for (i = 0; i<52; i++)  
    { 
        if (root->children[i])  
        { 
            if(i>25)
            {
            	str[level] = i + 'A'+ 6; 
            }
            else
            {
            	str[level] = i + 'A'; 
            }
            display(root->children[i], str, level + 1); 
        } 
    } 
}
int main() 
{ 
	srand((unsigned int) getpid());
    int i,ch,flg,t,n,j,x,y,k,random;
    clock_t tt;
    char c; 
    char* jey= (char*)malloc(sizeof(char)*25);
    char output[][32] = {"Not present in trie", "Present in trie"}; 
    struct TrieNode *root = getNode(); 
    i=0;
    printf("Sample words we are going to put in the trie data structure: ");
    char key[25][25] ={
    	"swap",
		"paragraph",
		"idea",
		"revive",
		"extent",
		"barrier",
		"eject",
		"refund",
		"snow",
		"infrastructure",
		"security",
		"abortion",
		"glare",
		"railcar",
		"close",
		"cook",
		"slab",
		"provide",
		"prisoner",
		"glue",
		"permanent",
		"loud",
		"mud",
		"format",
		"behead"
    };
	for(i=0;i<25;i++)
	{
		printf("%s ",key[i]);
		insert(root, key[i]);	
	} 
	printf("\nSample Insert in trie: %6s\n", "Happy"); 
	insert(root,"Happy");
    printf("Sample Search in trie: %6s ---> %s\n", "Happy", output[search(root, "Happy")] ); 
    printf("Sample Search in trie: %6s ---> %s\n", "glare", output[search(root, "glare")] ); 
    printf("Sample Search in trie: %6s ---> %s\n", "refund", output[search(root, "refund")] ); 
    printf("Sample Search in trie: %6s ---> %s\n", "there", output[search(root, "there")] ); 
  	deletion(&root,"glare");
  	printf("Sample Delete in trie: %6s ---> %s\n", "glare", output[search(root, "glare")] );
  	flg=0;
  	while(1)
  	{
  		printf("\nChoices:\n0. Exit \t1. Insert\t2. Search\t3. Delete\t4. List of words in the trie\t5. Testing the data struct trie\nEnter your choice: ");
  		scanf("%d",&ch);
  		switch(ch){
  			case 0:
  				printf("Loop Terminated\n");
  				flg=1;
  				break;
  			case 1:
  				printf("Enter the word you wish to enter in the trie: ");
  				scanf("%s",jey);
  				insert(root,jey);
  				break;
  			case 2:
  				printf("Enter the word you wish to search in the trie: ");
  				scanf("%s",jey);
  				printf("Search in trie: %6s ---> %s\n", jey, output[search(root,jey)] ); 
  				break;
  			case 3:
  				printf("Enter the word you wish to delete in the trie: ");
  				scanf("%s",jey);
  				t=preReqDel(root,jey);
  				if(search(root,jey))
  				{
  					printf("Search in trie: %6s ---> %s\n", jey, output[search(root,jey)] );
  				}
  				else 
  				{
  					if(t==0)
  						printf("Element deleted successfully. Search in trie: %6s ---> %s\n", jey, output[search(root,jey)] );
  				}
  				break;
  			case 4:
  				printf("List of the words in the trie\n");
  				printf("\n\t\tWord/String\tNumber of occurences\n\n");
  				display(root,jey,0);
  				break;
  			case 5:
  				printf("Random words in the trie. Enter the number of words: ");
  				scanf("%d",&n);
  				// Random string for search and delete
  				random=(rand()%n);
  				char* hey= (char*)malloc(sizeof(char)*25);
  				//Start insert time
  				tt=clock();
  				for(i=0;i<n;i++)
  				{
  					x=3+(rand()%25);
  					char* dey= (char*)malloc(sizeof(char)*25);
  					for(j=0;j<x-1;j++)
  					{
  						y=65+(rand()%58);
  						if(y>90 && y<97)
  						{
  							y-=6;
  						}
  						dey[j]=(char)y;
  					}
  					dey[x]='\0';
  					insert(root,dey);
  					if(i==random)
  					{
  						for(k=0;k<x;k++)
  						{
  							hey[k]=dey[k];
  						}
  					}
  					free(dey);
  				}
  				tt=clock()-tt;
  				//End insert time
  				printf("\nTime taken taken to Insert %d elements= %f\n",n,((double)tt)/CLOCKS_PER_SEC);  				
  				printf("\nRandom element from the trie: %s\n",hey);
  				tt=clock();
  				printf("Search in trie: %6s ---> %s\n", hey, output[search(root,hey)] );
  				tt=clock()-tt;
  				printf("Time taken taken to Search = %f\n",((double)tt)/CLOCKS_PER_SEC); 
  				tt=clock();
  				deletion(&root,hey);
  				tt=clock()-tt;
  				printf("\nDeleting %s ... Search in trie: %6s ---> %s\n", hey, hey,output[search(root,hey)] );
  				printf("Time taken taken to Delete = %f\n",((double)tt)/CLOCKS_PER_SEC); 
  				break;
  			default:
  				printf("Choice not available\n");
  				break;
  		}
  		if(flg)
  			break;
  	}
    return 0; 
} 

// This code supports both upper as well as lower cases letters. Special characters are obviously not included because it's not a part of our domain of study.

// Implemented a solution for more than one occurence as well basically using a counter for each distinct key and then subtracting it for every request to delete a key without using hashmap. The last node has the info of count. With that we successfully delete a key from the trie.

// Maximum length for each word can be 25

// time complexity to insert all the elements is O(M(logN)) M is the max length of string which here plays a major role and N number of elements

// time complexity to search and delete an element is O(M) which is nevertheless constant in our analysis. Thus, it does not depend on number of elements.
