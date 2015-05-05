#include <iostream>
#include <string>

using namespace std;

class Card
{
private:
  string m_suit;
  int m_num;
  
public:
  Card(string suit, int num)
  {
    m_suit = suit;
    m_num = num;
  };
  
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
};

int main ()
{
  Card Ace1("Spades", 1);
  
  Ace1.readCard();
  
  return 0;
};
