#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//#include "./question.h"
int fifty_arr[3];


//-----------------------Jokers----------------------------

extern int find_max(int *arr){
	int a=arr[0];
	for(int i=0; i<4; i++){
		if(arr[i] > a){
			a=arr[i];
		}
	}
	return a;
}

extern void fill_arr(int *arr){
	for(int i=0;i<4;i++){
		arr[i]=-1;
	}
}

extern int val_not_in_arr(int r ,int *arr){
	for(int i =0;i<4;i++){
		if(arr[i] == -1){
			break;
		}
		else if(arr[i] == r){
			return 0;
		}
		
	}
	return 1;
}



extern char *number_to_answer(struct question_t *q,int ans){
    switch(ans){
        case 0: return q->a; 
        case 1: return q->b;
        case 2: return q->c;
        case 3: return q->d;
    }
    return "\0";// to remove the waring
}
//-----------------------------------------------------------------------
extern void print_q(struct question_t q,int ans1, int ans2 ){
    printf("%s\n",q.question);
    for(int i = 0; i < 4;i++){
        if(i==ans1){
            printf("\t%d. %s\n",i+1,number_to_answer(&q,ans1));
            continue;
        }
        if(i==ans2){
            printf("\t%d. %s\n",i+1,number_to_answer(&q,ans2));
            continue;
        }
        
        printf("\t%d.\n",i+1);
        
    }
    printf("\t5. Use Jokers\n");
}

extern void fiftyfifty(struct question_t q){
    int rngf=0;
    int rngs=0;
    
    do{
		rngf = rand() % 4;
		rngs = rand() % 4;
    }while(!(rngf != rngs && (q.answer == rngf+1 || q.answer == rngs+1)));
    fifty_arr[0] = rngf+1;
    fifty_arr[1] = rngs+1;
    
    print_q(q,rngf,rngs);
    
}

extern void print_available_jokers(int Fiftyfifty,int CallFriend,int Help){
    printf("-----Choose Joker-----\n");
    printf("1. 50/50 = %d\n",Fiftyfifty);
    printf("2. Phone-a-Friend = %d\n",CallFriend);
    printf("3. Ask the Audience = %d\n",Help);	
}

extern void callfriend(struct question_t q, int flag_fifty){
    int probability = rand() % 101;
    int ans;
    
    if(flag_fifty == 0){
        printf("%s\n",q.question);
		
		printf("\t1. %s\n", q.a);
		printf("\t2. %s\n", q.b);
		printf("\t3. %s\n", q.c);
		printf("\t4. %s\n", q.d);
        printf("\t5. Use Jokers\n\n");
    }
    
    if(flag_fifty){
        printf("%s\n",q.question);
        
        for(int i=0; i<4;i++){
            if(fifty_arr[0] == i+1){
                printf("\t%d.%s\n",i+1,number_to_answer(&q,i));
                continue;
            }
            if(fifty_arr[1] == i+1){
                printf("\t%d.%s\n",i+1,number_to_answer(&q,i));
                continue;
            }
            printf("\t%d.\n",i+1);
        }
        printf("\t5. Use Jokers\n\n");
    }
    
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
			ans++;
		}while(ans == q.answer);
	}
	printf("Your friend says {%d} is the correct answer.\n", ans);
	
}

extern void help(struct question_t q,int flag_fifty){
    int probability = rand() % 101;
    
	int arr[4];
	arr[0] = rand() % 101;
	arr[1] = rand() % (101-arr[0]);
	arr[2] = rand() % (101-(arr[0]+arr[1]));
	arr[3] = 100 - (arr[0]+arr[1]+arr[2]);
	int r;
    int ans;


    int tmp_arr[4];
    int j=0;
    

    
    fill_arr(tmp_arr);
    
	if(q.difficulty == 0 && probability <= 80){
		ans = q.answer;	
	}
	else if(q.difficulty == 1 && probability <= 60){
		ans = q.answer;
	}
	else if(q.difficulty == 2 && probability <= 30){
		ans = q.answer;
	}
	else{
		do{
			ans = rand() % 4;
			ans++;
		}while(ans == q.answer);	
	}
    printf("%s\n",q.question);
    
    if(flag_fifty){
    	int max_prcnt; // generate bigger percent
    	do{
    		max_prcnt = rand() % 101;
    	}while(max_prcnt <= 50);
    	
    	if(ans != q.answer){
    		max_prcnt = 100 - max_prcnt;
    	}
		
		
        
        for(int m = 0; m < 4; m++){
            if(fifty_arr[0] == m+1){
            	if(fifty_arr[0] == q.answer){
                	printf("\t%d. %s ---- %d%% \n",m+1,number_to_answer(&q,m),max_prcnt);
                	continue;
                }
            	printf("\t%d. %s ---- %d%% \n",m+1,number_to_answer(&q,m),100 - max_prcnt);
            	continue;           	
				
            }
            if(fifty_arr[1] == m+1){
            	if(fifty_arr[1] == q.answer){
                	printf("\t%d. %s ---- %d%% \n",m+1,number_to_answer(&q,m),max_prcnt);
                	continue;
            	}
            	printf("\t%d. %s ---- %d%% \n",m+1,number_to_answer(&q,m),100 - max_prcnt);      
            	continue;   	
            }
            
            printf("\t%d.\n",m+1);
        }
        printf("\t5. Use Jokers\n");
        return;
    }
	
	for(int i=0;i<4;i++){
		if(ans == i+1){
        	printf("\t%d. %s ---- %d%% \n",i+1,number_to_answer(&q,i),find_max(arr));
		}
		else{		
			do{
				r = rand() % 4;
			}while(!(val_not_in_arr(r, tmp_arr) && arr[r] != find_max(arr)));

			tmp_arr[j] = r;
			j++;
        	printf("\t%d. %s ---- %d%% \n",i+1, number_to_answer(&q,i), arr[r]);
        }
	}
	printf("\t5. Use Jokers\n");
}

extern void jokers(struct question_t q , int *Fiftyfifty,int *CallFriend,int *Help, int *flag_fifty) {
    system("clear");
	int choise;
    print_available_jokers(*Fiftyfifty, *CallFriend, *Help);
    printf("\nEnter the joker: ");
    scanf("%d",&choise);
    system("clear");
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
        help(q,*flag_fifty);
        *Help = 0;
        return;
    };
    printf("%s\n",q.question);
    
    printf("\t1. %s\n", q.a);
    printf("\t2. %s\n", q.b);
    printf("\t3. %s\n", q.c);
    printf("\t4. %s\n", q.d);
    printf("\t5. Use Jokers\n\n");

    printf("This joker is used!\n");
}

