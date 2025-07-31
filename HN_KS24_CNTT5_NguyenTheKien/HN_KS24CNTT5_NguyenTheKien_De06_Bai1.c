#include <stdio.h>
#include  <string.h>
#include <stdlib.h>

#define MAX_LEN 100

typedef struct Node {
    char bookTitle[MAX_LEN];
    struct Node* next;
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
    strcpy(newNode->bookTitle, title);
    newNode->next = s->top;
    s->top = newNode;
}
char* popStack(Stack* s) {
    if (s->top == NULL) return NULL;
    Node* temp = s->top;
    s->top = s->top->next;
    static char title[MAX_LEN];
    strcpy(title, temp->bookTitle);
    free(temp);
    return title;
}
void enqueueQueue(Queue* q, const char* title) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->bookTitle, title);
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}
char* dequeueQueue(Queue* q) {
    if (q->front == NULL) return NULL;
    Node* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    static char title[MAX_LEN];
    strcpy(title, temp->bookTitle);
    free(temp);
    return title;
}
int isEmptyStack(Stack* s) {
    return s->top == NULL;
}
int isEmptyQueue(Queue* q) {
    return q->front == NULL;
}
void openNewBook(Stack* bookStack) {
    char title[MAX_LEN];
    printf("Nhap ten sach moi: ");
    getchar();
    fgets(title, MAX_LEN, stdin);
    title[strcspn(title, "\n")] = '\0'; // Xóa ký tự newline
    pushStack(bookStack, title);
    printf("Da mo sach: %s\n", title);
}

void closeCurrentBook(Stack* bookStack, Queue* closedBooks) {
    if (isEmptyStack(bookStack)) {
        printf("Khong co sach dang mo\n");
        return;
    }
    char* title = popStack(bookStack);
    enqueueQueue(closedBooks, title);
    printf("Da dong sach: %s\n", title);
}
void viewMostRecentBook(Stack* bookStack) {
    if (isEmptyStack(bookStack)) {
        printf("Khong co sach dang mo\n");
        return;
    }
    printf("Sach dang doc gan day: %s\n", bookStack->top->bookTitle);
}
void viewAccessHistory(Queue* closedBooks) {
    printf("Lich su dong sach:\n");
    Node* current = closedBooks->front;
    while (current != NULL) {
        printf("%s\n", current->bookTitle);
        current = current->next;
    }
}
void restoreBook(Stack* bookStack, Queue* closedBooks) {
    if (isEmptyQueue(closedBooks)) {
        printf("Lich su dong sach trong\n");
        return;
    }
    char* title = dequeueQueue(closedBooks);
    pushStack(bookStack, title);
    printf("Phuc hoi sach: %s\n", title);
}

void freeAll(Stack* s, Queue* q) {
    while (!isEmptyStack(s)) {
        popStack(s);
    }
    while (!isEmptyQueue(q)) {
        dequeueQueue(q);
    }
}

int main ()
{
    Stack bookStack;
    Queue closedBooks;
    initStack(&bookStack);
    initQueue(&closedBooks);
    int choice;
    do
    {
        printf(" \n E-BOOK READER MANAGER \n");
        printf("1. Mo Sach Moi \n");
        printf("2. Dong Sach Hien Tai \n");
        printf("3. Xem Sach Dang Doc Gan Nhat \n");
        printf("4. Lich Su Dong Sach \n");
        printf("5. Khoi Phuc Sach \n");
        printf("6. Hien Thi Cac Sach Dang Mo \n");
        printf("7. Thoat \n");
        printf("Moi ban nhap lua chon: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            openNewBook(&bookStack);
            break;
        case 2:
            closeCurrentBook(&bookStack, &closedBooks);
            break;
        case 3:
            viewMostRecentBook(&bookStack);
            break;
        case 4:
            viewAccessHistory(&closedBooks);
            break;
        case 5:
            restoreBook(&bookStack, &closedBooks);
            break;
        case 6:
            break;
        case 7:
            printf("Thoat chuong trinh ! \n");
            freeAll(&bookStack, &closedBooks);
            break;
        default:
            printf("Lua chon khong hop le ");
        }
    }while (choice !=7);
    return 0;
}
