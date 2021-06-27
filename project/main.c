#include<stdio.h>

#include<stdlib.h>

#include<string.h>

#include<time.h>

#include "./question.h"

#include "./hints.h"

#include "./file_work.h"


//-------------------------------------------------------------

void start_game() {
  struct question_t *questions = sv_10q(); //size=10
  int round = 1;
  int ans;

  int Fiftyfifty = 1;
  int CallFriend = 1;
  int Help = 1;

  int flag_fifty = 0;

  for (int i = 0; i < 10; i++, round++) {
    system("clear");
    printf("\t\t\t[---Question for round %d---]\n", round);
    printf("\n");
    printf("%s\n", questions[i].question);

    printf("\t1. %s\n", questions[i].a);
    printf("\t2. %s\n", questions[i].b);
    printf("\t3. %s\n", questions[i].c);
    printf("\t4. %s\n", questions[i].d);
    printf("\t5. Use Jokers\n");

    a:

      printf("\nEnter your option: ");
    scanf("%d", & ans);
    if (ans == 5) {
      jokers(questions[i], &Fiftyfifty, &CallFriend, &Help, &flag_fifty);
      goto a;

    }
    if (ans != questions[i].answer) {
      printf("\nYou lost the game.\nYou played for [%d] rounds\n", round);
      printf("\n\n");
      return;
    }
    flag_fifty = 0;

  }
  printf("Congratulations! You won!\n\n");
}

int main() {
  srand(time(0));
  struct question_t questions[] = {
    {
      "A person with well-developed abdominal muscles is said to have a what?",
      "One-pack",
      "Family pack",
      "12-pack",
      "Six pack",
      4,
      0
    },
    {
      "Which sort of animal is Walt Disney's Dumbo?",
      "Elephant",
      "Deer",
      "Donkey",
      "Lion",
      1,
      1
    },
    {
      "Compiled by Benjamin Franklin in 1737, The Drinker's Dictionary included all but which of these synonyms for drunkenness?",
      "Nimptopsical",
      "Buzzey",
      "Staggerish",
      "Pifflicated",
      4,
      2
    },
    {
      " What do eagles usually eat?",
      "Fruit",
      "Meat",
      "Worms",
      "Leaves",
      3,
      1
    },
    {
      "In the children’s book series, where is Paddington Bear originally from?",
      "Iceland",
      "Peru",
      "India",
      "Canada",
      2,
      2
    },
    {
      "Which animal is the tallest?",
      "Giraffe",
      "Lion",
      "Horse",
      "Cat",
      1,
      0
    },
    {
      "Which letter must appear on the beginning of the registration number of all non-military aircraft in the US?",
      "A",
      "U",
      "L",
      "N",
      4,
      2
    },
    {
      "Which first lady was a ninth-generation descendant of Pocahontas?",
      "Edith Wilson",
      "Helen Taft",
      "Bess Truman",
      "Mamie Eisenhower",
      1,
      1
    },
    {
      "The US icon Uncle Sam was based on Samuel Wilson who worked during the War of 1812 as a what?",
      "Mail deliverer",
      "Meat inspector",
      "Historian",
      "Weapons mechanic",
      2,
      2
    },
    {
      "Khrushchev's famous 1960 shoe-banging outburst at the UN was in response to a delegate from which nation?",
      "Austria",
      "The Philippines",
      "Turkey",
      "Spain",
      3,
      2
    },
    {
      "Where did Scotch whisky originate?",
      "Belgium",
      "Spain",
      "Ireland",
      "Wales",
      3,
      0
    },
    {
      "When was Henry VIII born?",
      "28th June 1491",
      "4th July 1478",
      "6th January 1490",
      "12th February 1468",
      2,
      2
    },
    {
      "The song God Bless America was originally written for what 1918 musical?",
      "Oh Lady! Lady!!",
      "Watch Your Step",
      "Blossom Time",
      "Yip, Yip, Yaphank",
      4,
      2
    },
    {
      "Nadia Comaneci was the first gymnast to ever do what at the Olympics?",
      "Get a perfect 10",
      "Get an injury",
      "Win an Olympic gold medal",
      "Forfeit her position",
      1,
      1
    },
    {
      "Which of these birds has the biggest brain relative to its size?",
      "Hummingbird",
      "EagleSparrow",
      "Ostrich",
      "Eagle",
      1,
      1
    },
    {
      "A person who is not a banker and lends money at an extremely high interest rate is known as what?",
      "Brother-in-law",
      "Paper tiger",
      "Green snake",
      "Loan Shark",
      4,
      0
    },
    {
      "What name is traditionally given to the party held for a woman who is expecting a baby?",
      "Baby downpour",
      "Baby shower",
      "Baby deluge",
      "Baby drizzle",
      2,
      0
    },
    {
      "Now used to refer to a cat, the word tabby is derived from the name of a district of what world capital?",
      "Cairo",
      "New Delhi",
      "Baghdad",
      "Moscow",
      3,
      2
    },
    {
      "The national flag of which of these countries does not feature three horizontal stripes?",
      "Russia",
      "Germany",
      "Romania",
      "Bulgaria",
      3,
      1
    },
    {
      "The popular children's song It's Raining, It's Pouring mentions an old man doing what?",
      "Cooking",
      "Laughing",
      "Snoring",
      "Yelling at squirrels",
      4,
      0
    },
    {
      "Which of the following singers has won the award for best bulgarian pop folk singer the most times?",
      "Galena",
      "Anelia",
      "Preslava",
      "Lorena",
      3,
      1
    },
    {
      "On September 14, 2013, Floyd Mayweather must defend his WBA title against which boxer?",
      "Juan Manuel Márquez",
      "Canelo Alvarez",
      "José Luis Castillo",
      "Felipe Garcia",
      2,
      2
    },
    {
      "What name is given to the revolving belt machinery in an airport that delivers checked luggage from the plane to baggage reclaim?",
      "Hangar",
      "Concourse",
      "Carousel",
      "Terminal",
      3,
      1
    },
    {
      "The hammer and sickle is one of the most recognisable symbols of which political ideology?",
      "Republicanism",
      "Communism",
      "Conservatism",
      "Liberalism",
      2,
      1
    },
    {
      "Construction of which of these famous landmarks was completed first?",
      "Empire State Building",
      "Royal Albert Hall",
      "Eiffel Tower",
      "Big Ben Clock Tower",
      4,
      2
    },
    {
      "Which of these cetaceans is classified as a toothed whale ?",
      "Gray whale",
      "Sperm whale",
      "Humback whale",
      "Minke whale",
      2,
      2
    },
    {
      "Who is the only British politician to have held all four “Great Offices of State” at some point during their career?",
      "David Lloyd George",
      "Harold Wilson",
      "James Callaghan",
      "John Major",
      3,
      2
    },
    {
      "Which of these brands was chiefly associated with the manufacture of household locks?",
      "Phillips",
      "Ronseal",
      "Chubb",
      "Flymo",
      3,
      1
    },
    {
      "Obstetrics is a branch of medicine particularly concerned with what?",
      "Childbirth",
      "Broken bones",
      "Heart conditions",
      "Old age",
      1,
      1
    },
    {
      "What does the word loquacious mean?",
      "Angry",
      "Chatty",
      "Beautiful",
      "Shy",
      2,
      1
    },
    {
      "At the closest point, which island group is only 50 miles south-east of the coast of Florida?",
      "Bahamas",
      "US Virgin Islands",
      "Turks and Caicos Islands",
      "Bermuda",
      1,
      2
    },
    {
      "The famous bulgarian influencer Stoyan Kolev is from which bulgarian city?",
      "Burgas",
      "Sofia",
      "Varna",
      "Plovdiv",
      1,
      0
    },
    {
      "After the suspension of Slavi's show, on BTV comes a brand new show with a new host. What is the origin of the new host of the show?",
      "Bulgarian",
      "Greek",
      "American",
      "Italian",
      2,
      0
    },

  };
  append(questions, sizeof(questions) / sizeof(questions[0]));

  system("clear");

  while (1) {
    int o;
    printf("\tStani Bogat\n");
    printf("1. Start game\n");
    printf("2. Add a question\n");
    printf("3. Display all available questions\n");
    printf("4. Edit question\n");
    printf("0. Exit\n\n");
    printf("Select option: ");
    scanf("%d", & o);
    getchar();
    printf("\n");
    switch (o) {
    case 1:
      start_game();
      break;

    case 2:
      system("clear");
      append_ui();
      system("clear");
      break;

    case 3:
      system("clear");
      display_all();
      break;

    case 4:
      system("clear");
      edit_q();
      system("clear");
      break;

    case 0:
      exit(0);
      break;
    }
  }

}
