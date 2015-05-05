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

void shuffle (Card Deck[52])
{
  srand(time(NULL));
  
  
}

int main ()
{
  Card Ace1;
  Ace1.init(1, 1);
  
  Ace1.readCard();
  
  return 0;
};
