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
	unsigned int answer;	
	unsigned int difficulty;
};

struct question_t *sv_10q(struct question_t *arr[10]){
    FILE *fp;
    
    struct question_t *q;

    fp=fopen(fname,"rb");
    
    for(int i = 0; i < 10 ; i++){
        
        fread(&q,sizeof(q),1,fp);
        arr[i] = q;
        //printf("%s",arr[i]->question);
    };
    
    fclose(fp);
    
    return *arr;
    
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

void append_ui(){
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
	printf("\nEnter difficulty (1-10):");			
	scanf("%u",&q.difficulty);

	fwrite(&q,sizeof(q),1,fp);
	fclose(fp);
}
void append(struct question_t *questions, int size){
	FILE *fp;
	
	fp=fopen(fname,"wb");
	for(int i=0;i<size;i++){
		fwrite(&questions[i],sizeof(questions[i]),1,fp);	
	}
	
	fclose(fp);
}




int main(){
	struct question_t questions[] = {
	{"VUPROS1", "OTGOVOR1A", "ORGOVOR1B", "OTGOVOR1G", "ORGOVOR1D", 2,9},
	{"VUPROS2", "OTGOVOR2A", "ORGOVOR2B", "OTGOVOR2G", "ORGOVOR2D", 1,2},	
	{"VUPROS3", "OTGOVOR3A", "ORGOVOR3B", "OTGOVOR3G", "ORGOVOR3D", 4,1},
	{"VUPROS4", "OTGOVOR4A", "ORGOVOR4B", "OTGOVOR4G", "ORGOVOR4D", 3,4},	
	{"VUPROS5", "OTGOVOR5A", "ORGOVOR5B", "OTGOVOR5G", "ORGOVOR5D", 2,10},
	{"VUPROS6", "OTGOVOR6A", "ORGOVOR6B", "OTGOVOR6G", "ORGOVOR6D", 1,6},	
	{"VUPROS7", "OTGOVOR7A", "ORGOVOR7B", "OTGOVOR7G", "ORGOVOR7D", 4,3},
	{"VUPROS8", "OTGOVOR8A", "ORGOVOR8B", "OTGOVOR8G", "ORGOVOR8D", 1,7},	
	{"VUPROS9", "OTGOVOR9A", "ORGOVOR9B", "OTGOVOR9G", "ORGOVOR9D", 2,8},
	{"VUPROS10", "OTGOVOR10A", "ORGOVOR10B", "OTGOVOR10G", "ORGOVOR10D", 3,5},	
	{"VUPROS11", "OTGOVOR11A", "ORGOVOR11B", "OTGOVOR11G", "ORGOVOR11D", 3,3},
	{"VUPROS12", "OTGOVOR12A", "ORGOVOR12B", "OTGOVOR12G", "ORGOVOR12D", 1,10},	
	};
	append(questions, sizeof(questions)/sizeof(questions[0]));
	display();
}









