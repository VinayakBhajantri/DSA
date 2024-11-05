#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>

struct slide
{
    char header[100];
    char body[100];
};

struct node
{
    struct node*prev;
    struct slide data;
    struct node*next;
};
void addAftercurSlide(struct node**head,struct node**cur,struct slide*e);
void deletecurSlide(struct node**head,struct node**cur);
void readSlide(struct slide*p);
void dis(struct node*cur);

int main()
{
    struct node*head=NULL;
    struct node*cur=NULL;
    struct slide e;
    while(1)
    {
        if(kbhit())
        {
            char ch=getch();

                switch(ch)
                {
                     case 'a':
                     case 'A':readSlide(&e);
                              addAftercurSlide(&head,&cur,&e);
                              break;

                     case 'd':
                     case 'D':deletecurSlide(&head,&cur);
                              break;

                     case 's':
                     case 'S':slideShow(head);
                              break;

                     case 80:
                     case 77:movetonextSlide(&cur);
                        break;

                     case 72:
                     case 75:movetoprevSlide(&cur);
                     break;
                     case 'e':exit(0);
                }

        }
    }
}
void movetonextSlide(struct node**cur)
{
    if((*cur)->next)
    {
        *cur=(*cur)->next;
        dis(*cur);
    }
}
void movetoprevSlide(struct node**cur)
{
    if((*cur)->prev)
    {
        *cur=(*cur)->prev;
        dis(*cur);
    }
}
void slideShow(struct node*head)
{
    struct node*cur=head;
    while(cur)
    {
        dis(cur);
        delay(2);
        cur=cur->next;
    }

}
void delay(int n)
{
    int milli_seconds=1000*n;
    clock_t start=clock();
    while(clock()<start+milli_seconds);
}
void deletecurSlide(struct node**head,struct node**cur)
{
    if(*head==NULL)
    {
        printf("No slide to delete\n");
        return;
    }
    if((*head)->next==NULL)
    {
        printf("Cannot delete only slide\n");
        return;
    }
    if(*head==*cur)
    {
        *head=(*head)->next;
         (*head)->prev=NULL;
         free(*cur);
         *cur=*head;
         dis(*cur);
         return;

    }
    struct node* follow=(*cur)->prev;
    follow->next=(*cur)->next;
    if((*cur)->next)
        (*cur)->next->prev=follow;

    free(*cur);
    if(follow->next)
        *cur=follow->next;

        else
            *cur=follow;
            dis(*cur);
}
void readSlide(struct slide*p)
{
    printf("Enter header\n");
    scanf("%s",p->header);
    printf("Enter body\n");
    scanf("%s",p->body);
    }
void dis(struct node*cur)
{
    printf("Header : %s\n",(cur)->data.header);
    printf("Body : %s\n",(cur)->data.body);
}
void addAftercurSlide(struct node**head,struct node**cur,struct slide*e)
{
    struct node*p=(struct node*)malloc(sizeof(struct node));
                  if(p==NULL)
                  {
                      perror("");
                      return;
                  }
                  p->data=*e;
                  p->prev=p->next=NULL;

                  if(*head==NULL)
                  {
                      *head=p;
                      *cur=p;
                      return;
                  }
                      p->next=(*cur)->next;
                      p->prev=*cur;

                  if((*cur)->next)
                    (*cur)->next->prev=p;
                  (*cur)->next=p;
                  *cur=p;
}
