#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "./question.h"
#include "./hints.h"
#include "./file_work.h"



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
	{"A person with well-developed abdominal muscles is said to have a what?", "One-pack", "Family pack", "12-pack", "Six pack", 4,0},
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
	{"The popular children's song It's Raining, It's Pouring mentions an old man  doing what?", "Cooking", "Laughing", "Snoring", "Yelling at squirrels", 4,0},
		
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
