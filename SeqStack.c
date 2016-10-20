#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct{
	int data[MAX];
	int top;
}SeqStack;

SeqStack *InitStack(){
	SeqStack *s;
	s=malloc(sizeof(SeqStack));
	s->top = -1;
	return s;
}

int EmptyStack(SeqStack *s){
	if(s->top == -1){
		return 1;
	}
	return 0;
}
int PushStack(SeqStack *s,int x){
	if(s->top == MAX-1){
		return 0;
	}
	else{
		s->top ++;
		s->data[s->top] = x;
		return 1;
	}
}

int PopStack(SeqStack *s,int *x){
	if(EmptyStack(s)){
		return 0 ;
	}
	else{
		*x = s->data[s->top];
		s->top --;
		return 1;
	}
}

int TopStack(SeqStack *s){
	if(EmptyStack(s)){
		return 0;
	}
	else{
		return s->data[s->top];
	}
}

main(){
	InitStack();
}