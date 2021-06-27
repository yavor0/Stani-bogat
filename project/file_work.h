#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>

//#include "./question.h"
char fname[]={"questions.dat"};




extern int size_of_file(){
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


extern struct question_t rquestion_f(){
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

extern void add_to_arr(struct question_t **arr, struct question_t q,int *size){
    *size+=1;
    *arr = (struct question_t*)realloc(*arr, (*size)*sizeof(struct question_t));
	(*arr)[*size-1] = q;

}

extern int exists(struct question_t *arr, struct question_t q, int size){
	for(int i=0;i<size;i++){
		if(!strcmp(arr[i].question, q.question)) return 1;
	}
	return 0;
}

//saving random 10 questions
extern struct question_t *sv_10q(){
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


extern void display_all(){
    FILE *fp;
    struct question_t q;
    int i=1;
    fp=fopen(fname,"rb");

    printf("\n========================================================\n\n");
    printf("\t\t All question details\n\n");
    printf("========================================================\n\n");


    
    while(1){
        fread(&q,sizeof(q),1,fp);

        if(feof(fp)){
            break;
        }
        printf("[---Question %d---]\n",i);
        printf("%s\n",q.question);
        printf("1. %s\n", q.a);
        printf("2. %s\n", q.b);
        printf("3. %s\n", q.c);
        printf("4. %s\n\n", q.d);
        i++;
    }
    printf("========================================================\n\n");
    fclose(fp);
}

extern void append_ui(){ // dobavq vupros ot terminala
	FILE *fp;
	struct question_t q;
	
	fp=fopen(fname,"ab"); // append to binary

	printf("\nEnter question:");
	fgets(q.question, sizeof(q.question),stdin); // chetem string ot terminala
	q.question[strlen(q.question)-1] = '\0'; // maha new lina ot stringa
	
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

extern void append(struct question_t *questions, int size){
	FILE *fp;
	
	fp=fopen(fname,"wb");
	for(int i=0;i<size;i++){
		fwrite(&questions[i],sizeof(questions[i]),1,fp);	
	}
	
	fclose(fp);
}

extern int count_qs(){ // vrushta kolko vuprosa ima vuv faila
    FILE *fp;
    struct question_t q;
    int i=0;
    fp=fopen(fname,"rb");
    
    while(1){
        fread(&q,sizeof(q),1,fp);
        if(feof(fp)){
            break;
        }
        i++;
    }
    fclose(fp);
    return i;	
}
//------------------------------------------------------------

extern void edit_q(){ 
/*
todo: put question input in a function; add an option for flexible editing (ex. only the question without the answers)
*/
	FILE *fp,*fp1; //ptr za failove
	
	struct question_t q; // structura za noviq vupros
	int num,found=0;

	fp=fopen(fname,"rb"); // original file
	fp1=fopen("temp.dat","wb"); // tmp file za zapametqvane na noviq vupros
	
	display_all(); // displayvame vsichki vuprosi
	
	printf("\nEnter the number of the question you want to modify: ");
	scanf("%d",&num); // chetem nomera na vuprosa, koito iskame da editnem
	getchar();

	for(int i = 1; i <= count_qs(); i++){
		fread(&q,sizeof(q),1,fp); // chetem vuprosite ot original file

		if(feof(fp)){ // ako sme stignali kraq na faila breakvame
			break;
		}
		if(i==num){
			found=1; // indikirame che sme namerili vuprosa
			printf("\nEnter question:");
			fgets(q.question, sizeof(q.question),stdin);
			q.question[strlen(q.question)-1] = '\0';
			
			printf("\nEnter answer a:");
			fgets(q.a, sizeof(q.a),stdin);
			q.a[strlen(q.a)-1] = '\0'; // premahva new lina ot fgets

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

			printf("\nEnter difficulty (0-2):");			
			scanf("%u",&q.difficulty);
			fwrite(&q,sizeof(q),1,fp1);
		}
		else{
			fwrite(&q,sizeof(q),1,fp1); // zapisvame vuprosa v noviq file 
		}
	}
	fclose(fp);
	fclose(fp1);
//-----
	if(found==0){
		printf("Sorry no question found\n\n");
	}
	else{
		fp=fopen(fname,"wb"); // oroginalen file otvarqme v mode write binary
		fp1=fopen("temp.dat","rb"); // tmp file otvarqme v mode read binary
		while(1){
			fread(&q,sizeof(q),1,fp1); // chetem ot tmp file
			if(feof(fp1)){ // ako sme stignali kraq na faila breakvame
				break;
			}
			fwrite(&q,sizeof(q),1,fp); // pishem v originalniq file ot tmp file
		}

	}
	fclose(fp);
	fclose(fp1);
}
