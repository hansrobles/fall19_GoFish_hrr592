#include <ctime>
#include <cstdlib>
#include <iterator>
#include "deck.h"
#include "player.h"

using namespace std;

  Player::Player()
  {
    myName = "Jablinski";
  }

  void Player::addCard(Card c)
  {
    myHand.push_back(c);
    return;
  }

  void Player::bookCards(Card c1, Card c2)
  {
    myBook.push_back(c1);
    myBook.push_back(c2);
    return;
  }

  bool Player::checkHandForBook(Card &c1, Card &c2)
  {
    Card cardHold1(14, Card::spades);
    Card cardHold2(15, Card::spades);
    int pairSignal = 0;
    for(vector<Card>::iterator it = myHand.begin(); ((it != myHand.end())&&(pairSignal == 0)); it++){
      cardHold1 = *it;
      for(vector<Card>::iterator it2 = (it+1); ((it2 != myHand.end())&&(pairSignal == 0)); it2++){
        cardHold2 = *it2;
        if(cardHold1.getRank() == cardHold2.getRank()){
          pairSignal = 1;
        }
      }
    }

    if(pairSignal == 1){
      c1 = cardHold1;
      c2 = cardHold2;
      return true;
    }else{
      return false;
    }
  }

  Card Player::chooseCardFromHand() const
  {
    int ranIndex = rand() % myHand.size();
    return(myHand.at(ranIndex));
  }

  bool Player::cardInHand(Card c) const
  {
    for(vector<Card>::const_iterator it = myHand.begin(); it != myHand.end(); it++){
      if((*it).getRank() == c.getRank()){
        return true;
      }
    }
    return false;
  }

  Card Player::removeCardFromHand(Card c)
  {
    Card cardHold;
    int cardFound = 0;
    for(vector<Card>::iterator it = myHand.begin(); cardFound == 0; it++){
      if((*it).getRank() == c.getRank()){
        cardHold = *it;
        myHand.erase(it);
        cardFound = 1;
      }
    }

    return cardHold;
  }

  string Player::showHand() const
  {
    string stringHold;

    if(getHandSize() == 0){
      stringHold = "No cards in hand";
      return stringHold;
    }

    for(vector<Card>::const_iterator it = myHand.begin(); it != myHand.end(); it++){
      stringHold = stringHold + (*it).toString() + ", ";
    }

    return stringHold;
  }

  string Player::showBooks() const
  {
    string stringHold;

    if(getBookSize() == 0){
      stringHold = "No books currently";
      return stringHold;
    }

    int bookSize = myBook.size();
    for(int i = 0; i <= (bookSize-2); i = i + 2){
      Card c1Hold, c2Hold;
      c1Hold = myBook.at(i);
      c2Hold = myBook.at(i+1);
      stringHold = stringHold + c1Hold.toString() + " and " + c2Hold.toString() + ", ";
    }

    return stringHold;
  }

  int Player::getHandSize() const
  {
    return(myHand.size());
  }

  int Player::getBookSize() const
  {
   return((myBook.size())/2);
  }
