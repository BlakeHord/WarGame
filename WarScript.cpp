#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

class Card;

int generateSuit();
int generateNum();
void shuffle (Card Deck[52]);
void printDeck(Card Deck[52]);
int checkDuplicate (Card Deck[52], int limit, int num, int suit);

using namespace std;

class Card
{
private:
  int m_suitnum;
  string m_suit;
  int m_num;
  
public:
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
  
  void init(int suit, int num)
  {
    m_suitnum  = suit;
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
  
  int returnNum()
  {
    return m_num;
  };
  
  int returnSuitnum()
  {
    return m_suitnum;
  };
};

int generateSuit()
{
  return (rand() % 4) + 1;
};

int generateNum()
{
  return (rand() % 13) + 1;
};

void shuffle (Card Deck[52])
{
  for(int i = 0; i < 52; i++)
  {
    int suit = 0, num = 0, count[4] = {0}, count2[13] = {0};
    do {
      suit = generateSuit();
      if(count[suit - 1] < 13)
      {
        count[suit - 1]++;
      };
    } while (count[suit - 1] > 13);
    
    do {
      num = generateNum();
      if(count2[num - 1] < 4)
      {
        count2[num - 1]++;
      };
    } while (count2[num - 1] > 4);
    
    Deck[i].init(suit, num);
    
    if(checkDuplicate(Deck, i, num, suit) == 1)
    {
      i--;
    };
  };
};

void printDeck(Card Deck[52])
{
  for(int i = 0; i < 52; i++)
  {
    Deck[i].readCard();
    cout << "\n";
  };
};

int checkDuplicate (Card Deck[52], int limit, int num, int suit)
{
  for (int i = 0; i < limit; i++)
  {
    if (Deck[i].returnNum() == num && Deck[i].returnSuitnum() == suit)
    {
      return 1;
    } else
    {
      continue;
    };
  };
  
  return 0;
};

int main ()
{
  cout << "Let's play war! You and the computer will draw a card from your hand, and whoever's card is " <<
      "higher wins the other's card\nIf you both draw the same card, three cards will be drawn, and whoever's third card " <<
      "is higher wins all the cards played\n\nPress enter to start";
  
  string buff;
  gets(buff);
  
  srand(time(NULL));
  Card Deck[52];
  shuffle(Deck);
  
  
  return 0;
};
