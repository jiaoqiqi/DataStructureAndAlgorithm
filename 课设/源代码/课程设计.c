#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 100000
#define M 2*N-1

typedef char * Huffmancode[N+1];

typedef struct{
        char leave;
        int weight;
        int parent,Lchild,Rchild;
       
}HTNode,HuffmanTree[M+1];

typedef struct{
        char ch;
        int count;
}Filecharcount[M+1];

int Readfile(Filecharcount fc,char member[]){
    int i=1;
    FILE *fp;
    char ch;
    char FileName[50];
    printf("Please input file name:");
    scanf("%s",FileName);
    fp = fopen(FileName,"r");
    if(fp==NULL){
       printf("文件打开失败!\n");
       exit(1);
    }
    ch = fgetc(fp);
    fc[i].ch = ch;
    fc[i].count = 0;
    int n=1,j;

    while(ch!=EOF){
       
        member[i] = ch;
        for(j=1;j<=n;j++){
            if(member[i]==fc[j].ch){
                fc[j].count++;
                break;
            }
        }       
        if(j-1==n){
            n++;
            fc[n].ch = member[i];
            fc[n].count = 1;
            j=1;
        }
        i++;
        ch = fgetc(fp);
    }
    fclose(fp);
    return n-1;
}

void CrtHuffmanCodel(HuffmanTree ht,Huffmancode hc, int n){
    char *code;
    int start,par,child,i;
    code = (char *)malloc(n*sizeof(char));
    code[n-1] = '\0';
    for(i=1;i<=n;i++){
        start = n-1;
        child=i;
        par=ht[i].parent;
        while(par!=0){
            --start;
            if(ht[par].Lchild==child)
                code[start]='0';
            else
                code[start]='1';
            child=par;
            par=ht[par].parent;
            hc[i] = (char *)malloc((n-start)*sizeof(char));
            strcpy(hc[i],&code[start]);

        }
    }
    free(code);
}

void CrtHuffmanTree(HuffmanTree ht,Filecharcount fc,int w[],int n)
{
    int m,i,s1,s2;
    m=2*n-1;
    for(i=1;i<=n;i++){
        ht[i].leave = fc[i].ch;
        w[i]=fc[i].count;
    }

    for(i=1;i<=n;i++){
        ht[i].weight=w[i];
        ht[i].Rchild=0;
        ht[i].parent = 0;
        ht[i].Lchild = 0;
    }

    for(i=n+1;i<=m;i++){
        ht[i].weight=w[i];
        ht[i].Rchild=0;
        ht[i].parent = 0;
        ht[i].Lchild = 0;
    }

    for(i=n+1;i<=m;i++){
                int o;
                s1=1;
                for(o=1;o<i;o++)
                        if(w[s1]>w[o]){
                                s1=o;
                        }
                w[s1] = 100000;
                s2 = 1;
                for(o=1;o<i;o++)
                        if(w[s2]>w[o]){
                                        s2=o;
                       }
                w[s2]=100000;
                ht[i].weight = ht[s1].weight+ht[s2].weight;
                w[i]=ht[i].weight;
                ht[i].Lchild = s1;
                ht[i].Rchild = s2;
                ht[s1].parent = i;
                ht[s2].parent = i;
        }
    printf("Encoding success!\n");
}
      
void WriteToFile(Huffmancode hc,Filecharcount fc,int n,char a[],char sh[]){
        FILE *fp;
   
        fp=fopen(sh,"w");
        if(fp==NULL)
        {
                exit(1);
        }
        int i,j,s;
        int m=0;
        for(i=1;i<=n;i++)
        {
                m=m+fc[i].count;
        }
        for(i=1;i<=m;i++)
                for(j=1;j<=n;j++)
                        if(a[i]==fc[j].ch)
                        {
                                fputs(hc[j],fp);
                                break;
                        }
        fclose(fp);
    printf("Save encoding success!\n");
}

void decode(Huffmancode hc,HuffmanTree ht,int n,char sh[]){
    FILE *fp;
        fp = fopen(sh,"r");
        if(fp==NULL)
                exit(1);
    FILE *Write;
    char sh1[50];
    printf("Please input a file to sava decoding:");
    scanf("%s",sh1);
    Write = fopen(sh1,"w");
    if(Write==NULL)
        exit(1);
        char ch;
        int i=1,j,start=1,p;
    int count=0;
        char a[1000];
        ch = fgetc(fp);
    p=2*n-1;
        while(ch!=EOF)
        {
                if(ch=='0')
            p=ht[p].Lchild;
        else
            p=ht[p].Rchild;
        if(ht[p].Lchild == 0 )
        {
            fputc(ht[p].leave,Write);
            p = 2*n-1;
        }
                ch = fgetc(fp);
        }
    
    printf("Decode success!\n");

}


void main(){
        int n;
        char member[100000];
        char FileName[50];
        Filecharcount fc;
        n = Readfile(fc,member);
        int i;
        int w[2*n];
        w[1] = 0;
        HuffmanTree ht;
        Huffmancode hc;
        CrtHuffmanTree(ht,fc,w,n);
        CrtHuffmanCodel(ht,hc,n);
        printf("Please input a file for encoding:");
        scanf("%s",FileName);
        WriteToFile(hc,fc,n,member,FileName);
        decode(hc,ht,n,FileName);       
}