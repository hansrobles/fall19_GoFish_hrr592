#include <ctime>
#include <cstdlib>
#include "deck.h"

using namespace std;

  Deck::Deck()
  {
    srand((unsigned)time(0));

    int deckIndex = 0;
    for(int suitCount  = 0; suitCount < 4; suitCount ++){
      for(int i = 1; i < 14; i ++){
        Card c(i, (Card::Suit)suitCount);
        myCards[deckIndex] = c;
        deckIndex ++;
      }
    }

    myIndex = 0;
  }

  void Deck::shuffle()
  {
    int pointer1, pointer2;
    for(int i = 0; i < SIZE; i++){
      pointer1 = (rand() % SIZE);
      pointer2 = (rand() % SIZE);

      Card temp = myCards[pointer1];
      myCards[pointer1] = myCards[pointer2];
      myCards[pointer2] = temp;
    }
    return;
  }

  Card Deck::dealCard()
  {
    Card c = myCards[myIndex];
    myIndex ++;
    return c;
  }

  int Deck::size() const
  {
    return (SIZE - myIndex);
  } 
