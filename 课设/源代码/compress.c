#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void compress(){
	FILE *inFile,*outFile;
	char ch;
	char inFileName[50],outFileName[50];
	// long int fileLength = 0;
	 char value;
	char s[10];

	//the file length
	// printf("input the file to get length: ");
	// scanf("%s",inFileName);
	// inFile = fopen(inFileName,"r");
	// if(inFile == NULL){
	// 	printf("the file is not exit ");
	// 	exit(1);
	// }
	// ch = fgetc(inFile);
	// while(ch != EOF){
	// 	++fileLength;
	// 	ch = fgetc(inFile);
	// }	
	// printf("%ld\n",fileLength);


	printf("input the compress inFileName: ");
	scanf("%s",inFileName);
	printf("input the compress outFileName: ");
	scanf("%s",outFileName);

	inFile = fopen(inFileName,"rb");
	if(inFile == NULL){
		printf("failed to open\n");
		exit(1);
	}

	outFile = fopen(outFileName,"w");
	if(outFile == NULL){
		printf("failed to open");
		exit(1);
	}
	int bit[8]={128,64,32,16,8,4,2,1};
	int n,i,j,k=0,sum=0;
	while((ch=fgetc(inFile))!=EOF){
		// while(k!=8 && feof(inFile)){
		// 	fread(&s[k],1,1,inFile);
		// 	k++;
		// }
		s[k%8]=ch;
		k++;
		s[k%8] = '\0';
		n=strlen(s);
		// printf("%d\n",n);
		if(n+1==8){
			sum = 0;
			for(i=0 ; i<n ; i++){
				sum = sum + bit[i];
			}
			value = ( char)(sum+48);
			fputc(value,outFile);
		}
		// else if(n<8){
		// 	for(i=0 ; i<n-1 ; i++){
		// 		fputc(s[i],outFile);
		// 	}
		// }

	}
	n=strlen(s);
		for(i=0 ; i<=n ; i++){
				fputc(s[i],outFile);
			}
		
	fclose(inFile);
	fclose(outFile);
	printf("save compress coding success!");

	// int i;
	// printf("input the compress outFileName: ");
	// scanf("%s",outFileName);
	// outFile = fopen(outFileName,"w");
	// if(outFile == NULL){
	// 	printf("fail");
	// 	exit(1);
	// }
	// for(i=48 ; i<=56 ; i++){

	// 	fputc(i,outFile);
	// }
	// fclose(outFile);
	// printf("Save encoding success!\n");

}
int main(){
	compress();
	return 0;
}
