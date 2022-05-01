/*circular-linked-list*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    struct Node *llink;
    struct Node *rlink;
} listNode;

int initialize(listNode **h);
int freeList(listNode *h);
void printList(listNode *h);
int invertList(listNode *h);

int insertFirst(listNode *h, int key);
int insertNode(listNode *h, int key);
int insertLast(listNode *h, int key);

int deleteFirst(listNode *h);
int deleteNode(listNode *h, int key);
int deleteLast(listNode *h);


int main()
{
    char command;
    int key;
    listNode *headnode = NULL;

    printf("\n[----- [Annotations by JinYeongKim] [2019038030] -----]\n");

    do
    {
        printf("----------------------------------------------------------------\n");
        printf("                  Doubly Circular Linked List                   \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'z':
        case 'Z':
            initialize(&headnode);
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

//노드에 메모리를 할당하는 함수
int initialize(listNode **h)
{

    /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
    if (*h != NULL)
        freeList(*h);

    /* headNode에 대한 메모리를 할당하여 리턴 */
    *h = (listNode *)malloc(sizeof(listNode));
    (*h)->rlink = *h;
    (*h)->llink = *h;
    (*h)->key = -9999;
    return 1;
}

//노드에 할당된 메모리를 반환하는 함수
int freeList(listNode *h)
{
    //만약 헤드노드밖에 없다면
    if (h->rlink == h)
    {
        free(h);    //헤드노드 메모리 반환
        return 1;
    }

    //각 노드를 참조하기 위한 p와 prev 노드
    listNode *p = h->rlink;
    listNode *prev = NULL;

    //p노드가 한바퀴 다 돌 때까지 실행
    while (p != NULL && p != h)
    {
        prev = p;
        p = p->rlink;
        free(prev); //노드 메모리 반환
    }
    free(h);    //헤드노드 메모리 반환
    return 0;
}

void printList(listNode *h)
{
    int i = 0;
    listNode *p;

    printf("\n---PRINT\n");

    if (h == NULL)
    {
        printf("Nothing to print....\n");
        return;
    }

    p = h->rlink;

    while (p != NULL && p != h)
    {
        printf("[ [%d]=%d ] ", i, p->key);
        p = p->rlink;
        i++;
    }
    printf("  items = %d\n", i);

    /* print addresses */
    printf("\n---checking addresses of links\n");
    printf("-------------------------------\n");
    printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

    i = 0;
    p = h->rlink;
    while (p != NULL && p != h)
    {
        printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
        p = p->rlink;
        i++;
    }
}

//마지막 노드 - 삽입할 노드 - 헤드노드
int insertLast(listNode *h, int key)
{
    //만약 헤드노드가 없으면
    if (h == NULL)
        return -1;  //initialize가 안 된 것이므로 함수 종료 (노드 삽입 불가)

    //삽입할 노드 메모리 할당
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;
    node->rlink = NULL;
    node->llink = NULL;

    //만약 헤드노드밖에 없다면 첫 노드로 삽입
    if (h->rlink == h)
    {
        h->rlink = node;
        h->llink = node;
        node->rlink = h;
        node->llink = h;
        /*원형 연결 리스트이므로 헤드노드 다음에 삽입할 노드, 그 다음에 다시 헤드노드이다*/
    }
    //만약 헤드노드 이외의 노드가 있다면 헤드노드 바로 앞에다 삽입하고 연결시킨다
    else
    {
        h->llink->rlink = node;
        node->llink = h->llink;
        h->llink = node;
        node->rlink = h;
    }

    return 1;
}

//노드 - (마지막 노드) - 헤드노드
int deleteLast(listNode *h)
{
    //만약 헤드노드만 있거나 혹은 헤드노드도 없다면 삭제할 노드가 없다.
    if (h->llink == h || h == NULL)
    {
        printf("nothing to delete.\n");
        return 1;
    }

    listNode *nodetoremove = h->llink;  //마지막 노드 참조

    //마지막 노드 앞에 있던 노드가 헤드노드와 연결되게 정리
    nodetoremove->llink->rlink = h;
    h->llink = nodetoremove->llink;

    free(nodetoremove); //마지막 노드 메모리 반환

    return 1;
}

//헤드노드 - 삽입할 노드 - 노드
int insertFirst(listNode *h, int key)
{
    //만약 헤드노드가 없다면 함수 종료(삽입 불가)
    if (h==NULL)
        return -1;

    //삽입할 노드 메모리 할당
    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;
    node->rlink = NULL;
    node->llink = NULL;

    //더블 포인팅 가능하게 연결
    node->rlink = h->rlink;
    h->rlink->llink = node;
    node->llink = h;
    h->rlink = node;

    return 1;
}

//헤드노드 - (첫번째 노드) - 두번째 노드
int deleteFirst(listNode *h)
{
    //헤드노드만 있거나 혹은 헤드노드도 없을 때 삭제할 노드가 없다.
    if (h == NULL || h->rlink == h)
    {
        printf("nothing to delete.\n");
        return 0;
    }

    listNode *nodetoremove = h->rlink;  //첫번째 노드 참조

    //헤드노드 - 두번째 노드 처럼 되게끔 포인팅 설정
    nodetoremove->rlink->llink = h; //nodetoremove->rlink는 두번째 노드를 뜻함
    h->rlink = nodetoremove->rlink;

    free(nodetoremove); //첫번째 노드 메모리 반환

    return 1;
}

//리스트를 역순으로 배치하는 함수
int invertList(listNode *h)
{
    //만약 헤드노드만 있거나 혹은 헤드노드도 없을 때
    if (h->rlink == h || h == NULL)
    {
        printf("nothing to invert...\n");
        return 0;
    }

    //
    listNode *n = h->rlink;
    listNode *trail = h;
    listNode *middle = h;

    /* 최종 바뀔 링크 유지 */
    h->llink = h->rlink;

    //한 바퀴 돌 때까지 n을 이동시켜서 rlink와 llink 포인팅 서로 변경
    while (n != NULL && n != h)
    {
        trail = middle;
        middle = n;
        n = n->rlink;
        middle->rlink = trail;
        middle->llink = n;
    }

    h->rlink = middle;  //마지막 노드 = middle

    return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode *h, int key)
{
    //헤드노드가 없을 때 삽입 불가
    if (h == NULL)
        return -1;

    listNode *node = (listNode *)malloc(sizeof(listNode));
    node->key = key;
    node->llink = node->rlink = NULL;

    //헤드노드밖에 없을 때 첫번째 자리에 삽입
    if (h->rlink == h)
    {
        insertFirst(h, key);
        return 1;
    }

    listNode *n = h->rlink;

    /* key를 기준으로 삽입할 위치를 찾는다 */
    while (n != NULL && n != h)
    {
        //삽입하려는 노드의 키값보다 더 큰 키값을 갖는 노드가 있을 때
        if (n->key >= key)
        {
            /* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
            if (n == h->rlink)
            {
                insertFirst(h, key);
            }
            else
            { /* 중간이거나 마지막인 경우 node - n */
                node->rlink = n;
                node->llink = n->llink;
                n->llink->rlink = node;
                n->llink = node;
            }
            return 0;
        }

        n = n->rlink;   //노드 이동
    }

    /* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
    insertLast(h, key);
    return 0;
}

//원하는 노드 삭제
int deleteNode(listNode *h, int key)
{
    //헤드노드밖에 없거나 혹은 헤드노드도 없을 때
    if (h->rlink == h || h == NULL)
    {
        printf("nothing to delete.\n");
        return 0;
    }

    //
    listNode *n = h->rlink;

    while (n != NULL && n != h)
    {
        //삭제하고자 하는 노드를 찾았을 때
        if (n->key == key)
        {
            if (n == h->rlink)
            { /* 첫 노드째 노드 인경우 */
                deleteFirst(h);
            }
            else if (n->rlink == h)
            { /* 마지막 노드인 경우 */
                deleteLast(h);
            }
            else
            { /* 중간인 경우 */
                n->llink->rlink = n->rlink;
                n->rlink->llink = n->llink;
                free(n);
            }
            return 0;
        }

        n = n->rlink;   //노드 이동
    }

    /* 찾지 못한 경우 */
    printf("cannot find the node for key = %d\n", key);
    return 0;
}
