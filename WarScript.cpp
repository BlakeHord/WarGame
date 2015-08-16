#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstdio>

class Card;
class Deck;

int checkDuplicate (Card *head, int limit, int num, int suit); // Headers for functions 
int generateSuit();
int generateNum();
Card* createDeck (Card *lolo, int current, int max);
void playGame(Deck *one, Deck *two);
void deal(Deck *first, Deck *second, Deck master);
void printDeck(Deck master);
void takeCard(Deck *win, Deck *lose);
Deck* tieOption(Deck *one, Deck *two, int &count1, int &count2, Card *ptr1, Card *ptr2);
void confirm();
int compareCards(Card *one, Card *two);

using namespace std;

class Card // How # and suit for cards are stored
{
private:
    int m_suitnum;
    string m_suit;
    int m_num;
  
public:
  
  Card(Card *ptr = NULL)
  {
    next = ptr;
  };
  
  Card *next;
  
  void readCard()
  {
    switch (m_num)
    {
      case 1:
        cout << "Ace";
        break;
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
        cout << m_num;
        break;
      case 11:
        cout << "Jack";
        break;
      case 12:
        cout << "Queen";
        break;
      case 13:
        cout << "King";
        break;
      default:
        cout << "Corrupted Card! RESTART";
        break;
    };
    
    cout << " of " << m_suit;
  };
  
  void init(int suit, int num) // Initialize the card
  {
    m_suitnum = suit;
    switch (m_suitnum)
    {
      case 1:
        m_suit = "Spades";
        break;
      case 2:
        m_suit = "Clubs";
        break;
      case 3:
        m_suit = "Diamonds";
        break;
      case 4:
        m_suit = "Hearts";
        break;
      default:
        cout << "Unknown suit value: RESTART";
        break;
    };
    m_num = num;
  };
  
  int returnNum() // Accessing private variables
  {
    return m_num;
  };
  
  int returnSuitnum()
  {
    return m_suitnum;
  };
};

class Deck // Class for players, including human and computer
{
public:
    int cards;
    Card *head;
    Card *tail;
    
    Deck(int value = 52)
    {
        cards = value; // Allocates memory for first card pointed to by head ptr
        
        head = new Card;
        Card *point = head;
        
        for(int i = 1; i < cards; i++)
        {
          point->next = new Card;
          point = point->next;
        };
    };
    
    void shuffle () // Shuffles deck of 52
    {
        Card *ptr = head; // ptr is equal to head ptr
        
        for(int i = 0; i < cards; i++)
        {
            int suit = 0, num = 0, count[4] = {0}, count2[13] = {0};
            do {
                suit = generateSuit(); // Randomize suit number
                if(count[suit - 1] < 13) // If that suit count is less than 13
                {
                    count[suit - 1]++; // Increase the count by one
                };
            } while (count[suit - 1] > 13); // Do this as long as the suit count is greater than 13, 
                                           // until a suit number that hasn't been filled is used
            do {
                num = generateNum(); // Randomize card number
                if(count2[num - 1] < 4) // If the number count is less than 4
                {
                    count2[num - 1]++; // Increase the count by one
                };
            } while (count2[num - 1] > 4); // Do this as long as the number count is greater than 4,
            
            if(ptr == NULL) // THIS IS THE PROBLEM -------- NOT ANYMORE
            {
              cout << "Error with null pointer\n";
            };
            
            ptr->init(suit, num); // Initialize suit and num form pointer !!!!!!!!!!!!PROGRAM BREAKS DOWN HERE!!!!!!!!!!!!!NOT ANYMORE!!!!!!!!!!!!
            if(checkDuplicate(head, i, num, suit) == 1) // If card is already present in the deck
            {
                i--; // Go again
                count[suit - 1]--; // Redo count of suit and num
                count2[num - 1]--;
            } else 
            {
                ptr = ptr->next;
            };
        }; 
    }  
};

Card* createDeck (Card *lolo, int current, int max)
{
  if(current < max)
  {
    lolo = new Card;
    current++;
    lolo->next = createDeck(lolo->next, current, max);
    return lolo;
  } else
  {
    lolo = new Card;
    return lolo; // Eventually returns the tail card #52
  };
};

int generateSuit() // Randomizes suit/num
{
  return (rand() % 4) + 1;
};

int generateNum()
{
  return (rand() % 13) + 1;
};

void printDeck(Deck master) // Prints full deck or person's deck - not for use in actual game
{
  Card *ptr = master.head;
  for(int i = 0; i < master.cards; i++)
  {
    ptr->readCard();
    cout << "\n";
    ptr = ptr->next;
  };
};

int checkDuplicate (Card *head, int limit, int num, int suit) // Checks that when making deck there is not a duplicate of randomly created card
{
    Card *ptr = head, *limbo;
  for (int i = 0; i < limit; i++)
  {
    if (head->returnNum() == num && head->returnSuitnum() == suit)
    {
      return 1;
    } else
    {
        limbo = head->next;
        head = limbo;
      continue;
    };
  };
  
  return 0;
};

void deal(Deck *first, Deck *second, Deck master) // Deals half of shuffled deck to each player
{
    first->head = master.head;
    
    Card *iter = master.head;
    for(int i = 0; i < 25; i++)
    {
      iter = iter->next;
    };
    
    first->tail = iter;
    second->head = iter->next;
    iter->next = NULL;
    iter = second->head;
    for(int i = 0; i < 25; i++)
    {
      iter = iter->next;
    };
    
    second->tail = iter;
};

void playGame(Deck *one, Deck *two)
{
  while(one->cards && two->cards)
  {
    cout << "-----------------------------------------------------------------------------------------------\n";
    cout << "Cards: " << one->cards << "\t\tPress enter to draw a card";
    
    confirm();
    
    cout << "\nYour card: \t\t\t";
    one->head->readCard();
    cout << "\nOpponent's card: \t\t";
    two->head->readCard();
    cout << "\n";
    
    if(compareCards(one->head, two->head) == 1)
    {
      takeCard(one, two);
      cout << "WIN\n\n";
    } else if(compareCards(one->head, two->head) == -1)
    {
      takeCard(two, one);
      cout << "LOSE\n\n";
    } else if(compareCards(one->head, two->head) == 0)
    {
      cout << "It's a tie! Each player flips a card face down and reveal the last card.\n";
      int ctr1 = 1, ctr2 = 1;
      
      if(tieOption(one, two, ctr1, ctr2, one->head, two->head) == one)
      {
        cout << "And you won the lot!\n\n";
        for(int i = 0; i < ctr2; i++)
        {
          cout << "You took a card\n";
          takeCard(one, two);
        };
      } else
      {
        cout << "And you lost the lot!\n\n";
        for(int i = 0; i < ctr1; i++)
        {
          takeCard(two, one);
          cout << "They took a card\n";
        };
      };
    };
  };
  
  if(one->cards == 0)
  {
    cout << "Sorry, you lost... Womp Womp\n\n";
  } else
  {
    cout << "Hooray! You won! Good job playing a game that requires no skill!\n\n";
  };
};

void takeCard(Deck *win, Deck *lose)
{
  win->tail->next = lose->head;
  win->tail = win->tail->next;
  
  lose->head = lose->head->next;
  
  win->tail->next = win->head;
  win->head = win->head->next;
  win->tail = win->tail->next;
  win->tail->next = NULL;
  
  win->cards++;
  lose->cards--;
};

Deck* tieOption(Deck *one, Deck *two, int &count1, int &count2, Card *ptr1, Card *ptr2)
{
  Card *point1 = ptr1, *point2 = ptr2;
  
  if(one->cards > count1 + 1)
  {
    point1 = point1->next;
    count1++;
    cout << "\nYour first hidden card:\t\t\t";
    point1->readCard();
    cout << "\n";
  };
  if(one->cards > count1 + 1)
  {
    point1 = point1->next;
    count1++;
    cout << "Your second hidden card:\t\t";
    point1->readCard();
    cout << "\n\n";
  };
  if(one->cards > count1 + 1)
  {
    point1 = point1->next;
    count1++;
  };
  
  if(two->cards > count2 + 1)
  {
    point2 = point2->next;
    count2++;
    cout << "Opponent's first hidden card:\t\t";
    point2->readCard();
    cout << "\n";
  };
  if(two->cards > count2 + 1)
  {
    point2 = point2->next;
    count2++;
    cout << "Opponent's second hidden card:\t\t";
    point2->readCard();
    cout << "\n";
  };
  if(two->cards > count2 + 1)
  {
    point2 = point2->next;
    count2++;
  };
  
  cout << "\n\nYour card: \t\t\t";
  point1->readCard();
  cout << "\nOpponent's card: \t\t";
  point2->readCard();
  cout << "\n";
  
  if(compareCards(point1, point2) == 1)
  {
    return one;
  } else if(compareCards(point1, point2) == -1)
  {
    return two;
  } else if(compareCards(point1, point2) == 0)
  {
    Deck *temp;
    return tieOption(one, two, count1, count2, point1, point2);
  };
};

void confirm()
{
  while(1)
  {
    if(cin.get() == '\n')
    {
      return;
    };
  };
};

int compareCards(Card *one, Card *two)
{
  int num1, num2;
  if(one->returnNum() == 1)
  {
    num1 = 14;
  } else
  {
    num1 = one->returnNum();
  };
  
  if(two->returnNum() == 1)
  {
    num2 = 14;
  } else
  {
    num2 = two->returnNum();
  };
  
  if(num1 > num2)
  {
    return 1;
  } else if(num2 > num1)
  {
    return -1;
  } else{
    return 0;
  };
};

void freeDeck(Deck master)
{
  Card *ptr = master.head;
  Card *temp = ptr;
  for(int i = 0; i < 52; i++)
  {
    if(ptr->next)
    {
      temp = ptr->next;
    };
    delete ptr;
    ptr = NULL;
    ptr = temp;
  };
};

int main ()
{
  cout << "Let's play war! You and the computer will draw a card from your hand, and whoever's card is " <<
      "higher wins the other's card!\nIf you both draw the same card, three cards will be drawn, and whoever's third card " <<
      "is higher wins all the cards played\n\nPress enter to start";
  
  confirm();
  
  cout << "\n";
  
  srand(time(NULL));
  Deck master(52);
  
  master.shuffle();
  
  Deck first(26), second(26);
  Deck *one = &first, *two = &second;
  
  deal(one, two, master);
  
  playGame(one, two);
  freeDeck(master); //I'm pretty sure this function works, but I'm not sure - When I try to do a check, I get a segmentation fault, so I think it's good
  
  return 0;
};

// A little buggy, but the interface works! - continue on whenever you read this Blake... FINISH IT
//UPDATE - Game looks good... Keep an eye on it when you're playing to spot any more bugs
