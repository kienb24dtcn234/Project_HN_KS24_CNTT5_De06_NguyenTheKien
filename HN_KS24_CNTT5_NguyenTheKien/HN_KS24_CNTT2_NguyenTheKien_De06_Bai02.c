#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 200

typedef struct Node {
    char content[MAX_LEN];
    int isAction;
    struct Node* yesChild;
    struct Node* noChild;
} Node;
typedef struct Stack {
    Node* top;
} Stack;
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;
void initStack(Stack* s) {
    s->top = NULL;
}
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

void pushStack(Stack* s, const char* title) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->content, title);
    newNode->yesChild = s->top;
    s->top = newNode;
}
char* popStack(Stack* s) {
    if (s->top == NULL) return NULL;
    Node* temp = s->top;
    s->top = s->top->noChild;
    static char title[MAX_LEN];
    strcpy(title, temp->content);
    free(temp);
    return title;
}
void enqueueQueue(Queue* q, const char* title) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->content, title);
    newNode->yesChild = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->yesChild = newNode;
        q->rear = newNode;
    }
}
char* dequeueQueue(Queue* q) {
    if (q->front == NULL) return NULL;
    Node* temp = q->front;
    q->front = q->front->noChild;
    if (q->front == NULL) q->rear = NULL;
    static char title[MAX_LEN];
    strcpy(title, temp->content);
    free(temp);
    return title;
}
int isEmptyStack(Stack* s) {
    return s->top == NULL;
}
int isEmptyQueue(Queue* q) {
    return q->front == NULL;
}
void freeAll(Stack* s, Queue* q) {
    while (!isEmptyStack(s)) {
        popStack(s);
    }
    while (!isEmptyQueue(q)) {
        dequeueQueue(q);
    }
}
int main()
{
    int choice;
    do
    {
        printf("\n GAME DECISION SIMULATOR \n");
        printf("1. Bat Dau Tro Choi \n");
        printf("2. Hien Thi Cay Quyet Dinh \n");
        printf("3. Them Cau Hoi Hoac Hanh Dong \n");
        printf("4. Xoa Mot Nut Trong Cay \n");
        printf("5. Thoat\n");
        printf("Moi ban nhap lua chon : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            freeAll(&popStack,&dequeueQueue);
            printf("Thoat chuong trinh ! \n");
            break;
            default:
            printf("Lua chon khong hop le ");
        }
    }while (choice !=5);
    return 0;
}
