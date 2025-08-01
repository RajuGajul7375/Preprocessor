#include"header.h"
FILE *fd;
int line;
char **gs;

void main(int argc,char **argv)
{
        if(argc!=2)
        {
                printf("USAGE:./a.out filename\n");
                return;
        }
        FILE *fp=fopen(argv[1],"r");
        fd=fopen("data.i","a");
        char ch;
        int c=0,c1=0;
	line=0;
        while((ch=fgetc(fp))!=EOF)
        {
                c1++;
                if(ch=='\n')
                {
			line++;
                        if(c<c1)
                                c=c1;
                        c1=0;
                }
        }
        rewind(fp);
        
	char *s=malloc(c+1);
        int len=strlen("#include");
	int len1=strlen("#define"),i;

	gs=malloc(sizeof(char *)*line);
        for(i=0;i<line;i++)
        {
                gs[i]=malloc(c+1);
                fgets(gs[i],c+1,fp);
        }
        rewind(fp);
        
	//header file include
        while(fgets(s,c+1,fp))
                header(s,len);
	rewind(fp);

	//macro replace
	while(fgets(s,c+1,fp))
		macro_fun(s,len1);
	rewind(fp);
	macro_comment_remove();

	fclose(fd);


}

void header(char *s,int len)
{
        int i,c;
        char t[20],p[200]="/usr/include/";
        if(strstr(s,"#include"))
        {
                for(i=len+1,c=0;s[i]!='>'&&s[i]!='"';i++)
                        t[c++]=s[i];
                t[c]='\0';
                strcat(p,t);
        }
        if(s[len]=='<')
        {
                path_fun(p);
        }

        else if(s[len]=='"')
        {       FILE *tp=fopen(t,"r");
                if(tp==0)
			path_fun(p);
                else
                path_fun(t);
        }


}



void path_fun(char *p)
{
        int c=0,c1=0;
        char ch;
        FILE *path=fopen(p,"r");
        while((ch=fgetc(path))!=EOF)
        {
                c1++;
                if(ch=='\n')
                {
                        if(c<c1)
                                c=c1;
                        c1=0;
                }
        }
        rewind(path);
        char *s=malloc(c+1);
	int i;

	//comment remove
        char t[10000];
        while(fgets(s,c+1,path))
	{
		if(strstr(s,"//"))
                {
                        for(i=0;s[i]!='/';i++)
                                t[i]=s[i];
                        t[i]='\0';
                        fputs(t,fd);
                        fputc('\n',fd);
                }
                else if(strstr(s,"/*"))
                {
                        for(i=0;s[i]!='/';i++)
                                t[i]=s[i];
                        t[i]='\0';
                        fputs(t,fd);
                        fputc('\n',fd);
                        while(fgets(s,c+1,path))
                        {
                                fputc('\n',fd);
                                if(strstr(s,"*/"))
                                        break;
                        }
                }
                else
                        fputs(s,fd);

	}
            
}


