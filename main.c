#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>


char fname[]={"questions.dat"};

struct question_t{
	char question[300];
	char a[50];
	char b[50];
	char c[50];
	char d[50];
	unsigned int answer;	
	unsigned int difficulty;
};


int size_of_file(){
    FILE *fp;
    int size = 0;
    struct question_t q;
    
    fp = fopen(fname,"rb");
    while(1){
        fread(&q,sizeof(q),1,fp);
        size++;
        if(feof(fp))
            break;
    };
    fclose(fp);
    
    return size - 1;
}

struct question_t rquestion_f(){
    FILE *fp;
    fp=fopen(fname,"rb");
    struct question_t q;
    int sizef = size_of_file();
    int rng = rand() % sizef;

    int j;
    for(j = 0; j <= rng;j++){
        fread(&q,sizeof(q),1,fp);
    };
    return q;
}

void add_to_arr(struct question_t **arr, struct question_t q,int *size){
    *size+=1;
    *arr = (struct question_t*)realloc(*arr, (*size)*sizeof(struct question_t));
	(*arr)[*size-1] = q;

}

int exists(struct question_t *arr, struct question_t q, int size){
	for(int i=0;i<size;i++){
		if(!strcmp(arr[i].question, q.question)) return 1;
	}
	return 0;
}

//saving random 10 questions
struct question_t *sv_10q(){
    FILE *fp;
    struct question_t *arr = (struct question_t*)malloc(sizeof(struct question_t));
    int size = 0;
    fp=fopen(fname,"rb");
    
    
    for(int i = 0; i < 10;){
        struct question_t rq = rquestion_f();   
        if(exists(arr,rq,size)) continue;
        if(i < 3){
            if(rq.difficulty == 0){
                add_to_arr(&arr,rq,&size);
                i++;
            };
        };  
        if(i >= 3 && i <= 5){
            if(rq.difficulty == 1){
                add_to_arr(&arr,rq,&size);
                i++;
            };
        };
        if(i >= 6 && i <= 9){
            if(rq.difficulty == 2){
                add_to_arr(&arr,rq,&size);
                i++;
            };
        };
    };
    fclose(fp);
    return arr;
}


void display_all(){
	FILE *fp;
	struct question_t q;
	int i=1;
	fp=fopen(fname,"rb");

	printf("\n========================================================\n\n");
	printf("\t\t All question details\n\n");
	printf("========================================================\n\n");

	printf("Question\t\t\tA\t\t\tB\t\t\tC\t\t\tD\tNUMBER\n\n");
	
	while(1){
		fread(&q,sizeof(q),1,fp);

		if(feof(fp)){
			break;
		}
		printf("%s\t\t",q.question);
		printf("%s\t\t",q.a);
		printf("%s\t\t",q.b);
		printf("%s\t\t",q.c);
		printf("%s\t\t",q.d);
		printf("%d\t\n\n",i);
		i++;
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
	printf("\nEnter difficulty (0-2):");			
	scanf("%u",&q.difficulty);

	fwrite(&q,sizeof(q),1,fp);
	fclose(fp);
	printf("\n\n");
}

void append(struct question_t *questions, int size){
	FILE *fp;
	
	fp=fopen(fname,"wb");
	for(int i=0;i<size;i++){
		fwrite(&questions[i],sizeof(questions[i]),1,fp);	
	}
	
	fclose(fp);
}


//-------------------------------------------------------------

void start_game(){
	struct question_t *questions = sv_10q(); //size=10
	int round=1;
	int ans;
	for(int i=0;i<10;i++,round++){
		printf("[---Question for round %d---]\n",round);
		printf("%s\n",questions[i].question);
		
		printf("1. %s\n", questions[i].a);
		printf("2. %s\n", questions[i].b);
		printf("3. %s\n", questions[i].c);
		printf("4. %s\n", questions[i].d);
		
		printf("\nEnter the correct answer: ");
		scanf("%d",&ans);
		if(ans != questions[i].answer){
			printf("\nYou lost the game.\nYou played for [%d] rounds\n", round);
			printf("\n\n");	
			return;
		}			
		
	}
	printf("Congratulations! You won!\n\n");
}

int main(){
	srand(time(0));
	struct question_t questions[] = {
	{"VUPROS1", "OTGOVOR1AAAAAAAAA", "ORGOVOR1B", "OTGOVOR1G", "ORGOVOR1D", 2,0},
	{"VUPROS2", "OfdasGOVOR2A", "ORGOfasVOR2B", "OTGOVOfasR2G", "ORGOVOR2D", 1,1},	
	{"VUPROS3", "OTGOVOR3A", "ORGOVOR3B", "OTGOVOR3G", "ORGOVOR3D", 4,2},
	{"VUPROS4", "OTGOVOR4A", "ORGOVOR4B", "OTGOVOR4fadsG", "ORGOVOR4D", 3,1},	
	{"VUPROSS5", "OTGOVOR5A", "ORGOVOR5B", "OTGfasOVOR5G", "ORGOVOR5D", 2,2},
	{"VUPROS6", "OTGOVOR6A", "ORGOVOR6B", "OTGOVOR6G", "ORGOVOR6D", 1,0},	
	{"VUPROS7", "OTGOVOR7A", "ORGOVOR7B", "OTGfdsOVOR7G", "ORGOVOR7D", 4,2},
	{"VUPROS8", "OTGOVOR8A", "ORGOVOR8B", "OTGOVOR8G", "ORGOVOR8D", 1,1},	
	{"VUPROS9", "OTGOVOR9A", "ORGOVOR9B", "OTGOVOR9G", "ORGOVOR9D", 2,2},
	{"VUPROS10", "OTGOVOR10A", "ORGOVOR10B", "OTGOVOR10G", "ORGOVOR10D", 3,2},	
	{"VUPROS11", "OTGOVOR11A", "ORGOVOR11B", "OTGOVOR11G", "ORGOVOR11D", 3,0},
	{"VUPROS12", "OTGOVOR12A", "ORGOVOR12B", "OTGOVOR12G", "ORGOVOR12D", 1,1},
    {"VUPROS13", "OTGOVOR13A", "ORGOVOR13B", "OTGOVOR13G", "ORGOVOR13D", 1,1},
	};
	append(questions, sizeof(questions)/sizeof(questions[0]));
	//display_all();
    
    
    while(1){
    	int o;
    	printf("1. Start game\n");
    	printf("2. Add a question\n");
    	printf("3. Display all available questions\n");
    	printf("0. Exit\n\n");
    	printf("Select option: ");    
    	scanf("%d",&o);
    	getchar();
    	printf("\n");
    	switch(o){
			case 1: start_game(); 
			break;
			
			case 2: append_ui();
			break;
			
			case 3: display_all();
			break;
						
			case 0: exit(0);
			break;
    	}
    }
    
}




