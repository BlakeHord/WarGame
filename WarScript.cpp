#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Card
{
private:
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
    switch (suit)
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

int main ()
{
  srand(time(NULL));
  Card Deck[52];
  shuffle(Deck);
  printDeck(Deck);
  
  return 0;
};
