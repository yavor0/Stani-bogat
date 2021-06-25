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
int fifty_arr[3];

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

int count_qs(){
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

void edit_q(){ 
/*
todo: put question input in a function; add an option for flexible editing (ex. only the question without the answers)
*/
	FILE *fp,*fp1;
	
	struct question_t q;
	int num,found=0;

	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");
	
	display_all();
	
	printf("\nEnter the nmber of the question you want to modify:");
	scanf("%d",&num);
	getchar();

	for(int i = 1; i <= count_qs(); i++){
		fread(&q,sizeof(q),1,fp);

		if(feof(fp)){
			break;
		}
		if(i==num){
			found=1;
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

			printf("\nEnter difficulty (0-2):");			
			scanf("%u",&q.difficulty);
			fwrite(&q,sizeof(q),1,fp1);
		}
		else{
			fwrite(&q,sizeof(q),1,fp1);
		}
	}
	fclose(fp);
	fclose(fp1);

	if(found==0){
		printf("Sorry no question found\n\n");
	}
	else{
		fp=fopen(fname,"wb");
		fp1=fopen("temp.dat","rb");
		while(1){
			fread(&q,sizeof(q),1,fp1);
			if(feof(fp1)){
				break;
			}
			fwrite(&q,sizeof(q),1,fp);
		}

	}
	fclose(fp);
	fclose(fp1);
}

//-----------------------Jokers----------------------------
char *number_to_answer(struct question_t *q,int ans){
    switch(ans){
        case 0: return q->a; 
        case 1: return q->b;
        case 2: return q->c;
        case 3: return q->d;
    }
    return "\0";// to remove the waring
}
//-----------------------------------------------------------------------
void print_q(struct question_t q,int ans1, int ans2 ){
    printf("%s\n",q.question);
    for(int i = 0; i < 4;i++){
        if(i==ans1){
            printf("%d. %s\n",i+1,number_to_answer(&q,ans1));
            continue;
        }
        if(i==ans2){
            printf("%d. %s\n",i+1,number_to_answer(&q,ans2));
            continue;
        }
        
        printf("%d.\n",i+1);
        
    }
}

void fiftyfifty(struct question_t q){
    int rngf=0;
    int rngs=0;
    
    do{
    rngf = rand() % 4;
    rngs = rand() % 4;
    }while(!(rngf != rngs && (q.answer == rngf+1 || q.answer == rngs+1)));
    fifty_arr[0] = rngf+1;
    fifty_arr[1] = rngs+1;
    
    printf("\n------%d,%d----\n", rngf+1,rngs+1);
    print_q(q,rngf,rngs);
    
}

void print_available_jokers(int Fiftyfifty,int CallFriend,int Help){
    printf("-----Choose Joker-----\n");
    printf("1. 50/50 = %d\n",Fiftyfifty);
    printf("2. Phone-a-Friend = %d\n",CallFriend);
    printf("3. Ask the Audience = %d\n",Help);	
}

void callfriend(struct question_t q, int flag_fifty){
    int probability = rand() % 101;
    int ans;

    
	if(q.difficulty == 0 && probability <= 80){
		ans = q.answer;	
		printf("Your friend says {%d} is the correct answer.\n", ans);
		return;
	}
	if(q.difficulty == 1 && probability <= 60){
		ans = q.answer;
		printf("Your friend says {%d} is the correct answer.\n", ans);
		return;	
	}
	if(q.difficulty == 2 && probability <= 30){
		ans = q.answer;
		printf("Your friend says {%d} is the correct answer.\n", ans);
		return;	
	}
	
    if(flag_fifty){
		if(q.answer == fifty_arr[0]){
			ans = fifty_arr[1];
		}
		else{
			ans = fifty_arr[0];
		}
    }
    else{
		do{
			ans = rand() % 4;
		}while(ans != q.answer);
	}
	printf("Your friend says {%d} is the correct answer.\n", ans);
	
}

void jokers(struct question_t q , int *Fiftyfifty,int *CallFriend,int *Help, int *flag_fifty) {
	int choise;
    print_available_jokers(*Fiftyfifty, *CallFriend, *Help);
    printf("\nEnter the joker: ");
    scanf("%d",&choise);
    
    if(*Fiftyfifty == 1 && choise == 1){
        fiftyfifty(q);
        *flag_fifty = 1;
        *Fiftyfifty = 0;
        return;
    };
    if(*CallFriend == 1 && choise == 2){
        callfriend(q, *flag_fifty);
        *CallFriend = 0;
        return;
    };
    if(*Help == 1 && choise == 3){
        //help();
        *Help = 0;
        return;
    };
    printf("This joker is used!\n");
}

//-------------------------------------------------------------

void start_game(){
	struct question_t *questions = sv_10q(); //size=10
	int round=1;
	int ans;
    
    int Fiftyfifty = 1;
    int CallFriend = 1;
    int Help = 1;

    int flag_fifty = 0;
    
	for(int i=0;i<10;i++,round++){
		printf("[---Question for round %d---]\n",round);
    	print_available_jokers(Fiftyfifty, CallFriend, Help);
        printf("\n");
		printf("%s\n",questions[i].question);
		
		printf("1. %s\n", questions[i].a);
		printf("2. %s\n", questions[i].b);
		printf("3. %s\n", questions[i].c);
		printf("4. %s\n", questions[i].d);

        
        a:
		printf("5. Use Jokers\n");
		printf("\nEnter your option: ");
		scanf("%d",&ans);
        if(ans == 5){
			jokers(questions[i], &Fiftyfifty, &CallFriend, &Help, &flag_fifty);
        	goto a;
            
        }
		if(ans != questions[i].answer){
			printf("\nYou lost the game.\nYou played for [%d] rounds\n", round);
			printf("\n\n");	
			return;
		}
		flag_fifty=0;			
		
	}
	printf("Congratulations! You won!\n\n");
}

int main(){
	srand(time(0));
	struct question_t questions[] = {
	{"A person with well-developed abdominal muscles is said to have a what?", "One-pack", "Six pack", "12-pack", "Family-pack", 2,0},
	{"What sort of animal is Walt Disney's Dumbo?", "Elephant", "Deer", "Donkey", "Lion", 1,1},	
	{"Compiled by Benjamin Franklin in 1737, The Drinker's Dictionary  included all but which of these synonyms for drunkenness?", "Nimptopsical", "Buzzey", "Staggerish", "Pifflicated", 4,2},
	{" What do egals usually eat?", "Fruit", "Meat", "Worms", "Leaves", 3,1},	
	{"In the children’s book series, where is Paddington Bear originally from?", " Iceland", "Peru", "India", "Canada", 2,2},
	{"What animal is the tallest?", "Giraff", "Lion", "Horse", "Cat", 1,0},	
	{"What letter must appear on the beginning of the registration number of all non-military aircraft in the US?", "A", "U", "L", "N", 4,2},
	{"What first lady was a ninth-generation descendant of Pocahontas?", "Edith Wilson", "Helen Taft", "Bess Truman", "Mamie Eisenhower", 1,1},	
	{"The US icon Uncle Sam was based on Samuel Wilson who worked during the War of 1812 as a what?", "Mail deliverer", "Meat inspector", "Historian", "Weapons mechanic", 2,2},
	{"Khrushchev's famous 1960 shoe-banging outburst at the UN was in response to a delegate from what nation?", "Austria", "The Philippines", "Turkey", "Spain", 3,2},	
	{"Where did Scotch whisky originate?", "Belgium", "Spain", "Ireland", "Wales", 3,0},
	{"When was Henry VIII born?", " 28th June 1491", "4th July 1478", "6th January 1490", "12th February 1468", 2,1},
	{"The song God Bless America was originally written for what 1918 musical?", "Oh Lady! Lady!!", "Watch Your Step", "Blossom Time", "Yip, Yip, Yaphank", 4,2},
	{"Nadia Comaneci was the first gymnast to ever do what at the Olympics?", "Get a perfect 10", "Win an Olympic gold medal", "Win an Olympic gold medal", "Forfeit her position", 1,1},
	{"Which of these birds has the biggest brain relative to its size?", "Hummingbird", "EagleSparrow", "Ostrich", "Eagle", 1,1},
	{"A person who is not a banker and lends money at an extremely high interest rate is known as what?", "Brother-in-law", "Paper tiger", "Green snake", "Loan Shark", 4,0},
	{"What name is traditionally given to the party held for a woman who is expecting a baby?", "Baby downpour", "Baby shower", "Baby deluge", "Baby drizzle", 2,0},
	{"Now used to refer to a cat, the word tabby is derived from the name of a district of what world capital?", "Cairo", "New Delhi", "Baghdad", "Moscow", 3,2},
	{"The national flag of which of these countries does not feature three horizontal stripes?", "Russia", "Meat", "Romania", "Bulgaria", 3,1},
	{"The popular children's song It's Raining, It's Pouring mentions an old man  doing what?", "Yelling at squirrels", "Laughing", "Snoring", "Cooking", 1,0},
		
	};
	append(questions, sizeof(questions)/sizeof(questions[0]));
	//display_all();
    
    
    while(1){
    	int o;
    	printf("1. Start game\n");
    	printf("2. Add a question\n");
    	printf("3. Display all available questions\n");
    	printf("4. Edit question\n");
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
			
			case 4: edit_q();
			break;
	
			case 0: exit(0);
			break;
    	}
    }
    
}
