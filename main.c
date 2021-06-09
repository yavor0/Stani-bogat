#include<stdio.h>
#include<stdlib.h>
#include <string.h>

char fname[]={"questions.dat"};

struct question_t{
	char question[200];
	char a[30];
	char b[30];
	char c[30];
	char d[30];
	unsigned int difficulty;
	unsigned int answer;	
};

void append(){
	FILE *fp;
	struct question_t q;
	
	fp=fopen(fname,"ab");

	printf("\nEnter question:");
	fgets(q.question, sizeof(q.question),stdin);
	q.question[strlen(q.question)-1] = '\0';
	
	printf("\nEnter answer a:");
	fgets(q.a, sizeof(q.a),stdin);
	q.a[strlen(q.a)-1] = '\0';

	printf("\nEnter answer b:");
	fgets(q.b, sizeof(q.b),stdin);
	q.b[strlen(q.b)-1] = '\0';

	printf("\nEnter answer c:");
	fgets(q.c, sizeof(q.c),stdin);
	q.c[strlen(q.c)-1] = '\0';
	
	printf("\nEnter answer d:");
	fgets(q.d, sizeof(q.d),stdin);
	q.d[strlen(q.d)-1] = '\0';
	
	printf("\nEnter correct answer (1-4):");			
	scanf("%u",&q.answer);
	// todo: if diff != (1-3)
	printf("\nEnter difficulty (1-3):");			
	scanf("%u",&q.difficulty);

	fwrite(&q,sizeof(q),1,fp);
	fclose(fp);
}

void display()
{
	FILE *fp;
	struct question_t q;

	fp=fopen(fname,"rb");

	printf("\n========================================================\n\n");
	printf("\t\t All question details\n\n");
	printf("========================================================\n\n");

	printf("Question\tA\tB\tC\tD\n\n");

	while(1){
		fread(&q,sizeof(q),1,fp);

		if(feof(fp)){
			break;
		}
		printf("%s\t",q.question);
		printf("%s\t",q.a);
		printf("%s\t",q.b);
		printf("%s\t",q.c);
		printf("%s\t\n\n",q.d);

	}
	printf("========================================================\n\n");
	fclose(fp);
}

int main(){
	append();
	display();
}


















