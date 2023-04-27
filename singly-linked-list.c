/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science
 *  at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node // 연결 리스트의 노드를 정의하였다.
{
    int key;           // 리스트에 저장된 값이다.
    struct Node *link; // 다음 리스트의 주소를 가리키는 포인터이다.
} listNode;

typedef struct Head // 연결 리스트의 헤드노드를 정의하였다.
{
    struct Node *first; // 헤드노드이므로, 값을 가지지 않고 주소만 가리킨다.
} headNode;

/* 함수 리스트 */
headNode *initialize(headNode *h); // 연결 리스트 초기화
int freeList(headNode *h);         // 연결 리스트 해제

int insertFirst(headNode *h, int key); // 연결 리스트 맨앞에 삽입
int insertNode(headNode *h, int key);  // 연결 리스트 중간에 삽입
int insertLast(headNode *h, int key);  // 연결 리스트 마지막에 삽입

int deleteFirst(headNode *h);         // 연결 리스트 맨앞을 삭제
int deleteNode(headNode *h, int key); // 연결 리스트 중 값이 key인 노드 삭제
int deleteLast(headNode *h);          // 연결 리스트 마지막을 삭제
int invertList(headNode *h);          // 리스트 역순으로 만들기

void printList(headNode *h); // 리스트 출력하기

int main()
{
    char command;              // 어떤 명령어를 실행할지 결정하는 변수이다.
    int key;                   // 삽입할 값을 결정하는 변수이다.
    headNode *headnode = NULL; // 실제 값이 저장되는 헤드노드이다.

    do
    {
        printf("\n\n[----- [hyaejun-mun] [2019015035] -----]\n");
        printf("----------------------------------------------------------------\n");
        printf("                     Singly Linked List                         \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = "); // 값을 입력받는다.
        scanf(" %c", &command);

        switch (command) // 그 값에 따라 다른 명령어를 실행한다.
        {
        case 'z':
        case 'Z':
            headnode = initialize(headnode);
            break;
        case 'p':
        case 'P':
            printList(headnode);
            break;
        case 'i':
        case 'I':
            printf("Your Key = ");
            scanf("%d", &key);
            insertNode(headnode, key);
            break;
        case 'd':
        case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteNode(headnode, key);
            break;
        case 'n':
        case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            insertLast(headnode, key);
            break;
        case 'e':
        case 'E':
            deleteLast(headnode);
            break;
        case 'f':
        case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            insertFirst(headnode, key);
            break;
        case 't':
        case 'T':
            deleteFirst(headnode);
            break;
        case 'r':
        case 'R':
            invertList(headnode);
            break;
        case 'q':
        case 'Q':
            freeList(headnode);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

headNode *initialize(headNode *h)
{

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (h != NULL)
        freeList(h);

    /* headNode에 대한 메모리를 할ㄷ랑하여 리턴 */
    headNode *temp = (headNode *)malloc(sizeof(headNode));
    temp->first = NULL;
    return temp;
}

int freeList(headNode *h)
{
    /* h와 연결된 listNode 메모리 해제
     * headNode도 해제해 주어야 함.
     */
    listNode *p = h->first;

    listNode *prev = NULL;
    while (p != NULL)
    {
        prev = p;
        p = p->link;
        free(prev);
    }
    free(h);
    return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode *h, int key)
{
    // 멤버로 받은 값을 원소로 가지는 노드를 생성한다.
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key; // 값을 삽입하고,

    node->link = h->first; // 만든 노드가 1번째 노드를 가리키게 한 뒤,
    h->first = node;       // 헤드노드가 만든 노드를 가리키게 한다.
                           // 이렇게 하면, 헤드노드 -> 만든노드 -> 1번째 노드 순이 된다.
    return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode *h, int key)
{
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;
    node->link = NULL;

    if (h->first == NULL) // 아직 비어있을 경우
    {
        h->first = node; // 헤드 뒤에 삽입한다.
        return 0;
    }
    // 리스트가 비어있지 않을 경우
    listNode *n = h->first;    // 리스트 원소와 key를 비교하기 위한 것이다.
    listNode *back = h->first; // n의 바로 뒤를 가리켜서, 삽입할 위치를 잊지 않게 한다.
    while (n != NULL)          // n이 NULL이 아닐 동안(리스트의 끝이 아닌 동안)
    {
        if (n->key >= key) // 성립할 때
        {
            if (h->first == n) // 첫 번째 원소이면(back 불필요)
            {
                h->first = node; // 첫 번째 원소 앞에 삽입(listFirst와 동일함.)
                node->link = n;
            }
            else // 첫째 원소가 아니면
            {
                node->link = n; // 그 위치 앞에 삽입
                back->link = node;
            }
            return 0; // 그리고 바로 끝내 준다.
        }
        back = n;    // back이 뒤를 가리키게 하고,
        n = n->link; // n은 한 노드 나아감.
    }
    back->link = node; // 다 끝나도 성립하는 것이 없을 경우, 맨 마지막에 삽입함.
    return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode *h, int key)
{
    // 멤버로 받은 값을 원소로 가지는 노드를 생성한다.
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;
    node->link = NULL;

    if (h->first == NULL) // 리스트가 비어 있으면
    {                     // 첫 번째 노드로 삽입하고 종료한다.
        h->first = node;
        return 0;
    }

    listNode *n = h->first;
    while (n->link != NULL) // n이 가리키는 노드가 NULL이 아닐 때까지
    {                       // (n이 마지막이 될 때까지)
        n = n->link;        // n은 순차적 이동
    }
    n->link = node; // 끝에 덧붙임

    return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode *h)
{
    if (h->first == NULL) // 리스트가 비어있는지 판별한다.
    {
        printf("\nlist is blank.\n");
        return 0;
    }
    // 지울 노드의 주소를 기억하는 변수를 동적 생성한다.
    listNode *n = (listNode *)malloc(sizeof(listNode));

    n = h->first;       // 지울 노드(첫번째 노드)를 가리킨다.
    h->first = n->link; // 지울 노드를 제거한다.
    free(n);            // 제거되었으므로, 동적 할당 해제해 준다.

    return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode *h, int key)
{
    if (h->first == NULL) // 리스트가 비어있는지 판별한다.
    {
        printf("\nlist is blank.\n");
        return 0;
    }
    return 0;
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode *h)
{

    return 0;
}

/**
 * 리스트의 링크를 역순으로 재배치
 */
int invertList(headNode *h)
{

    return 0;
}

void printList(headNode *h)
{
    int i = 0;
    listNode *p;

    printf("\n---PRINT\n");

    if (h == NULL)
    {
        printf("Nothing to print....\n");
        return;
    }

    p = h->first;

    while (p != NULL)
    {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->link;
        i++;
    }

    printf("  items = %d\n", i);
}