#include"header.h"
extern char **gs;
extern int line;
extern FILE *fd;

void macro_fun(char *s,int len)
{
	int i,n,j;
	char name[200],body[1000];
	if(strstr(s,"#define"))
	{
		for(i=len+1,n=0;s[i]!=' ';i++)
			name[n++]=s[i];
		name[n]='\0';

		for(j=i+1,n=0;s[j]!='\0';j++)
			body[n++]=s[j];
		body[n]='\0';

		replace_fun(name,body);
	}
}


void replace_fun(char *n,char *b)
{
	char *p,c=0,temp1[200];
	int len1=strlen(n),len2=strlen(b),i;
	for(i=0;i<line;i++)
	{
		p=gs[i];
		if(p=strstr(gs[i],n))
		{
			if(c==0)
			{
				c=1;
				continue;
			}
			strcpy(temp1,p+len1);
			strcpy(p,b);
			strcpy((p+len2-1),temp1);

		}
	}
	
}


//comment remove
void macro_comment_remove()
{
	int i,j;
	char t[1000];
        for(j=0;j<line;j++)
        {
                if(strstr(gs[j],"//"))
                {
                        for(i=0;gs[j][i]!='/';i++)
                                t[i]=gs[j][i];
                        t[i]='\0';
                        fputs(t,fd);
                        fputc('\n',fd);
                }
                else if(strstr(gs[j],"/*"))
                {
                        for(i=0;gs[j][i]!='/';i++)
                                t[i]=gs[j][i];
                        t[i]='\0';
                        fputs(t,fd);
                        fputc('\n',fd);
                        for(;j<line;j++)
                        {
                                fputc('\n',fd);
                                if(strstr(gs[j],"*/"))
                                      break;
                        }
                }
                else
                     fputs(gs[j],fd);
        }

}

