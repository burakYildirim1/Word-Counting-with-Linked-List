#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

struct list
{
    char *word;
    int freq;
    struct list *next;
};
struct list *head=NULL;
struct list *end=NULL;

void insertBegin(char*wordTXT,int wordFreq)
{
    struct list * newNode = (struct list *)malloc(sizeof (struct list));
    newNode->freq=wordFreq;
    newNode->word = malloc(strlen(wordTXT)+1);
    strcpy(newNode->word,wordTXT);

    if(head==NULL)
    {
        head=newNode;
        end=newNode;
        end->next=NULL;
    }
    else
    {
        struct list *temp;
        temp=head;
        head=newNode;
        newNode->next=temp;
    }
}
void insertAt(char*wordTXT,int wordFreq)
{
    struct list * newNode = (struct list *)malloc(sizeof (struct list));
    newNode->freq=wordFreq;
    newNode->word = malloc(strlen(wordTXT)+1);
    strcpy(newNode->word,wordTXT);


    struct list *temp;
    struct list *temp2;
    temp=head->next;

    while(temp != NULL)
    {
        if( wordFreq > temp->freq)
        {
            temp2=temp->next;
            temp->next=newNode;
            newNode->next=temp2;

            swap(temp,newNode);
            break;
        }
        else
        {
            temp=temp->next;
        }
    }

}
void insertEnd(char*wordTXT,int wordFreq)
{
    struct list * newNode = (struct list *)malloc(sizeof (struct list));
    newNode->freq=wordFreq;
    newNode->word = malloc(strlen(wordTXT)+1);
    strcpy(newNode->word,wordTXT);

    if(head==NULL)
    {
        head=newNode;
        end=newNode;
        end->next=NULL;
    }
    else
    {
        end->next=newNode;
        end=newNode;
        end->next=NULL;
    }

}
bool searchInList(char*wordTXT)
{
    struct list *temp;
    temp=head;

    while(temp!=NULL)
    {
        if(strcmp(wordTXT,temp->word)==0)
        {
            return false;
        }
        temp=temp->next;
    }
    return true;
}
char* readFile(char *filename)
{
    char *allText = NULL;
    int textSize, read_size;

    FILE *fileTXT = fopen(filename, "r");

    fseek(fileTXT, 0, SEEK_END);
    textSize = ftell(fileTXT);

    rewind(fileTXT);

    allText = (char*) malloc(sizeof(char) * (textSize + 1) );
    fread(allText, sizeof(char), textSize, fileTXT);
    allText[textSize] = '\0';

    fclose(fileTXT);
    return allText;
}
void printList()
{
    struct list *temp;
    temp=head;

    int index=1;
    while(temp!=NULL)
    {
        printf("%d: %s: %d\n",index,temp->word,temp->freq);
        temp=temp->next;
        index++;
    }

}
int countFreq(char * AllText, char * word)
{   // https://stackoverflow.com/questions/12698836/counting-words-in-a-string-c-programming/12699260#12699260
    char *p;
    char temp[100];
    char *t = temp;
    int state, in = 1, out = 0;
    int freq = 0;

    state = out;
    for(p = AllText; *p; p++)
    {
        if(isspace(*p))
        {
            if(state == in)
            {
                *t = '\0';
                t = temp;
                if(strcmp(temp, word) == 0)
                    freq++;
            }
            state = out;
        }
        else
        {
            *t++ = *p;
            state = in;
        }
    }
    *t = '\0';
    if(strcmp(temp, word) == 0)
        freq++;
    return freq;
}
void swap(struct list *a, struct list *b)
{
    int temp = a->freq;
    a->freq = b->freq;
    b->freq = temp;

    char tempStr[50];

    strcpy(tempStr,a->word);

    strcpy(a->word,b->word);
    strcpy(b->word,tempStr);

}
int main(void)
{
    setlocale(LC_ALL, "Turkish");
    char *allText = readFile("temp.txt");
    char *tempText = malloc(strlen(allText)+1);
    strcpy(tempText,allText);

    char *word;
    char *delimeter=" \n";
    word=strtok (tempText,delimeter);
    while(word!=NULL)
    {
        int wordFreq=countFreq(allText,word);
        if( (searchInList(word)) )
        {
            if(head==NULL)
            {
                insertBegin(word,wordFreq);
//                printList();
//                printf("--------------\n");
            }
            else
            {
                if(wordFreq >= head->freq )
                {
//                    printf("insertBegin : %s : %d\n",word,wordFreq);
                    insertBegin(word,wordFreq);
//                    printList();
//                    printf("--------------\n");
                }
                else if(wordFreq <= end->freq)
                {
//                    printf("insertEnd : %s : %d\n",word,wordFreq);
                    insertEnd(word,wordFreq);
//                    printList();
//                    printf("--------------\n");
                }
                else
                {
//                    printf("insertAt : %s : %d\n",word,wordFreq);
                    insertAt(word,wordFreq);
//                    printList();
//                    printf("--------------\n");
                }
            }
        }
        word=strtok (NULL,delimeter);
    }
    printList();

    return 0;
}


