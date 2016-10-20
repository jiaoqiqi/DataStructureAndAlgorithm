#include <stdio.h>
#include <stdlib.h>

typedef struct Polyomial
{
    float coef;         
    int expn;           
    struct Polyomial *next;
} Polyomial, *Polyn;

Polyn CreatePloy()
{
    Polyomial *head, *rear, *s;
    float c;
    int e, t;
    char d, f;
    head = (Polyomial *)malloc(sizeof(Polyomial));      
    head->next = NULL;
    rear = head;
    scanf("%d",&t);
    getchar();
    while (t--) {
        getchar();
        scanf("%f,%d",&c,&e);
        getchar();
        s = (Polyomial *)malloc(sizeof(Polyomial));
        s->coef = c;
        s->expn = e;
        rear->next = s;
        rear = s;
    }
    rear->next = NULL;
    return head;
}

void PrintPolyn(Polyn P)
{
    Polyn q = P->next;
    int flag = 1;
    if (!q) {
        putchar('0');
        printf("\n");
        return;
    }
    while (q) {
        if (q->coef>0 && flag != 1) {
            putchar('+');
        }
        if (q->coef != 1 && q->coef != -1) {
            printf("%g",q->coef);
            if (q->expn == 1) {
                putchar('X');
            } else if (q->expn) {
                printf("X^%d",q->expn);
            }
        } else {
            if (q->coef == 1) {
                if (!q->expn) {
                    putchar('1');
                } else if (q->expn == 1) {
                    putchar('X');
                } else {
                    printf("X^%d",q->expn);
                }
            }
			if (q->coef == -1) {
                if (!q->expn) {
                    printf("-1");
                } else if (q->expn == 1) {
                    printf("-X");
                } else {
                    printf("-X^%d",q->expn);
                }
            }
        }
        q = q->next;
        flag++;
    }
    printf("\n");
}

Polyn MultiPolyn(Polyn pa,Polyn pb)
{

    Polyn qa = pa->next;
    Polyn headc, pc, qb, qc;
    pc = (Polyn)malloc(sizeof(struct Polyomial));
    pc->next = NULL;
    headc = pc;
    while (qa != NULL) {
        qb = pb->next;
		while (qb != NULL) {
		    qc = (Polyn)malloc(sizeof(struct Polyomial));
		    qc->coef = qa->coef * qb->coef;
		    qc->expn = qa->expn + qb->expn;
            pc->next = qc;
            pc = qc;
            qb = qb->next;
		}
        qa = qa->next;
    }
    pc->next = NULL;
    return headc;
}

void UnitePoly(Polyomial *h)
{
	Polyomial *pa, *pb, *qa, *qb, *temp;
	qa = h;
	pa = qa->next;

	while(pa != NULL) {
		pb = pa->next;
		qb = pa;
		while(pb != NULL) {
			if(pa->expn == pb->expn) {
				pa->coef = pa->coef + pb->coef;
				if(pa->coef == 0) {
					temp = pb;
					qb->next = pb->next;
					free(temp);
					temp=pa;
					qa->next = pa->next;
					pa = qa;
					free(temp);
					break;
				} else {
					temp=pb;
					qb->next = pb->next;
					pb = pb->next;
					free(temp);
				}
			} else {
				qb = pb;
				pb = pb->next;
			}
		}
		qa = pa;
		pa = pa->next;
	}
}

void Insort(Polyomial *h)
{
	Polyomial *s, *p;
	int t, m;
	for (p=h->next; p!=NULL; p=p->next) {    
		for(s=h->next; s->next!=NULL; s=s->next) {
			if(s->expn > s->next->expn) {
				t = s->expn;
				m = s->coef;
				s->coef = s->next->coef;
				s->expn = s->next->expn;
				s->next->coef = m;
				s->next->expn = t;
			}
		}
	}
}

int main(int argc, char *argv[])
{
    Polyomial *a, *b, *h;

    a = CreatePloy();
    b = CreatePloy();
    h = MultiPolyn(a,b);
    UnitePoly(h);
	Insort(h);
    PrintPolyn(h);

    return 0;
}