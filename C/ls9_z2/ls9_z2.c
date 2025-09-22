#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct e_queueS
{
    char *imie;
    int wiek;
    struct e_queueS *next;
} e_queue;

typedef struct queue_cS
{
    e_queue *first;
    e_queue *last;
} queue_c;

typedef queue_c* Queue;

Queue new_Queue()
{
    Queue newq = (Queue)malloc(sizeof(queue_c));
    if(newq != NULL)
    {
        newq->first = NULL;
        newq->last = NULL;
    }
    return newq;
}

int is_empty(Queue q)
{
    if(q == NULL || q->last == NULL || q->first == NULL) return 1;
    return 0;
}

int append(Queue q, char *imie, int wiek)
{
    if(q == NULL) return -2;

    e_queue* nel;
    nel = (e_queue*)malloc(sizeof(e_queue));
    if(nel == NULL) return -1;

    nel->imie = (char*)malloc(sizeof(char)*strlen(imie)+1);
    if(nel->imie == NULL) {free(nel); return -1;}

    strcpy(nel->imie, imie);
    nel->wiek = wiek;

    if(q->last == NULL) 
    {
        q->first = nel;
        q->last = nel;
    }
    else
    {
        (q->last)->next = nel;
        q->last = nel;
    }

    nel->next = NULL;

    return 0;
}

int insert_bef(Queue q, char *imie, int wiek, char *kolega)
{
    if(q == NULL) return -2;
    if(strcmp(q->first->imie, kolega) == 0)
    {
        e_queue* nel = (e_queue*)malloc(sizeof(e_queue));
        if(nel == NULL) return -1;

        nel->imie = (char*)malloc(sizeof(char)*strlen(imie)+1);
        if(nel->imie == NULL) {free(nel); return -1;}
        

        strcpy(nel->imie, imie);
        nel->wiek = wiek;
        nel->next = q->first;
        q->first = nel;

        return 0;
    }


    e_queue* ptr = q->first;

    while(ptr->next != NULL && strcmp((ptr->next)->imie, kolega) != 0) ptr = ptr->next;
    if(ptr->next == NULL) return -3;

    e_queue* nel = (e_queue*)malloc(sizeof(e_queue));
    if(nel == NULL) return -1;

    nel->imie = (char*)malloc(sizeof(char)*strlen(imie)+1);
    if(nel->imie == NULL) {free(nel); return -1;}
    

    strcpy(nel->imie, imie);
    nel->wiek = wiek;

    nel->next = ptr->next;
    ptr->next = nel;

    return 0;
}

void q_pop(Queue q)
{
    if(is_empty(q) == 1) return;

    e_queue* next = (q->first)->next;
    free((q->first)->imie);
    free(q->first);
    q->first = next;

    return;
}

void delete(Queue q)
{
    if(q == NULL) return;
    while(is_empty(q) != 0) q_pop(q);
    q->first = q->last = NULL;
}

int kick(Queue q, char *imie)
{
    if(q == NULL) return -2;
    if(strcmp(q->first->imie, imie) == 0)
    {
        //printf("git\n");
        e_queue* h = q->first->next;
        free(q->first->imie);
        free(q->first);
        q->first = h;
        return 0;
    }

    e_queue* ptr = q->first;

    while(ptr->next != NULL && strcmp((ptr->next)->imie, imie) != 0) ptr = ptr->next;
    if(ptr->next == NULL) return -3;

    e_queue* h = ptr->next;
    ptr->next = ptr->next->next;
    free(h->imie);
    free(h);

    return 0;
}

void wypisz(Queue q)
{
    if(q == NULL) return;
    e_queue *ptr = q->first;
    
    while(ptr != NULL)
    {
        fputs(ptr->imie, stdout);
        ptr = ptr->next;
    }
    printf("\n");

    return;
}


int main()
{
    char imie_bufor[1001], kolega_bufor[1001];
    int wiek_bufor, ileu, sumau=0;

    char op;
    scanf("%c", &op);

    Queue kolejka = new_Queue();

    while(op != 'Z')
    {
        switch(op)
        {
            case '+':
                //getc(stdin);
                scanf("%s%d", imie_bufor, &wiek_bufor);

                append(kolejka, imie_bufor, wiek_bufor);

                break;
            
            case '-':
                //getc(stdin);
                scanf("%s", imie_bufor);

                kick(kolejka, imie_bufor);

                break;
            
            case 'F':
                //getc(stdin);
                scanf("%s%d", imie_bufor, &wiek_bufor);
                //scanf("%d", &wiek_bufor);
                //getc(stdin);
                scanf("%s", kolega_bufor);

                insert_bef(kolejka, imie_bufor, wiek_bufor, kolega_bufor);
                
                break;
            
            case 'W':
                wypisz(kolejka);
                break;
            case 'O':
                scanf("%d", &ileu);
                sumau += ileu;
                break;
            default:
                //printf("\ndefault\n");
                break;

        }
        scanf("%c", &op);
    }

    while(sumau > 0)
    {
        if(is_empty(kolejka) == 1) return 0;
        if(kolejka->first->wiek >= 18)
        {
            printf("%s\n", kolejka->first->imie);
            sumau--;
        }
        q_pop(kolejka);
    }


    return 0;
}