#include <stdlib.h>
#include <stdio.h>

typedef struct listElement
{
    int val;
    struct listElement* next;
} listel;

listel* newList()
{
    listel* p = (listel*)malloc(sizeof(listel));
    if(p == NULL) return NULL;
    p->val = 0;
    p->next = NULL;

    return p;
}

void addEl(listel* list, int val)
{
    while(list->next != NULL) list = list->next;
    listel* newEl = newList();
    if(newEl == NULL) return;

    newEl->next = NULL;
    newEl->val = val;
    list->next = newEl;
}

listel* create_proc(listel* list, listel* (*function)(listel*))
{
    listel* listNew = newList();
    if(listNew == NULL) return NULL;

    while(list->next != NULL)
    {
        addEl(listNew, function(list->next)->val);
        list = list->next;
    }
    return listNew;
}

listel* create_imp(listel* list, listel* (*function)(listel*))
{
    listel* listNew = newList();
    if(listNew == NULL) return NULL;

    listel* cursor = listNew;
    while(list->next != NULL)
    {
        cursor->next = function(list->next);
        cursor = cursor->next;
        list = list->next;
    }
    return listNew;
}

void write(listel* list)
{
    while(list->next != NULL)
    {
        printf("%d ", list->next->val);
        list = list->next;
    }
    printf("\n");
}

listel* fun(listel* el)
{
    listel* newEl = newList();
    if(newEl == NULL) return NULL;

    newEl->val = 2*(el->val)*(el->val);
    newEl->next = NULL;

    return newEl;
}

int main()
{
    listel* list = newList();

    for(int i=1; i<=10; i++) addEl(list, i);
    // list: 1 2 3 4 5 6 7 8 9 10

    listel* listA = create_imp(list, fun);
    listel* listB = create_proc(list, fun);

    write(list);
    write(listA);
    write(listB);

    return 0;
}