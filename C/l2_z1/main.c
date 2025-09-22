#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int k=2;
int p;
int ch;
char m[6]={'a','e','i','o','u'};
char M[6]={'A','E','I','O','U'};

int main()
{
    while ((ch = getchar()) != EOF)
    {
        p=-1;
        if(ch=='a')
        {
            p=0;
        }
        else if(ch=='e')
        {
            p=1;
        }
        else if(ch=='i')
        {
            p=2;
        }
        else if(ch=='o')
        {
            p=3;
        }
        else if(ch=='u')
        {
            p=4;
        }
        else if(ch=='A')
        {
            p=0;
        }
        else if(ch=='E')
        {
            p=1;
        }
        else if(ch=='I')
        {
            p=2;
        }
        else if(ch=='O')
        {
            p=3;
        }
        else if(ch=='U')
        {
            p=4;
        }
        if(p != -1)
        {
            p+=k;
            p%=5;
            if(ch<'a') printf("%c",M[p]);
            else printf("%c",m[p]);
            // putchar(m[p]);
        }
        else printf("%c",ch);
    }

    return 0;
}
