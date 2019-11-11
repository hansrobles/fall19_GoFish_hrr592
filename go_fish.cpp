#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

#include "player.h"
#include "deck.h"
#include "card.h"

using namespace std;

int main(){
  ofstream myFile ("gofish_results.txt", ios::out| ios::trunc);
  
  Deck deck;
  Player p1("Jeff");
  Player p2("Geoff");
  Card cardHold1;
  Card cardHold2;
  int handSizeHold;

  deck.shuffle();
  myFile << p1.getName() << " is playing against " << p2.getName() << endl;

  //these statements are used to indicate that the program is doing something
  cout << ".";

  //deal out cards to begin game
  for(int i = 0; i < 7; i++){
    p1.addCard(deck.dealCard());
    p2.addCard(deck.dealCard());
  }
 
  //displays players' initial hands
  myFile << p1.getName() << " has " << p1.showHand() << endl;
  myFile << p2.getName() << " has " << p2.showHand() << endl;

  //check initial hands for pairs
  handSizeHold = p1.getHandSize();
  for(int i = 0; i < handSizeHold; i++){
    if(p1.checkHandForBook(cardHold1, cardHold2)){
      p1.removeCardFromHand(cardHold1);
      p1.removeCardFromHand(cardHold2);
      p1.bookCards(cardHold1, cardHold2);
      myFile << p1.getName() << " books " << cardHold1 << " and " << cardHold2 << endl;
    }
  }

  handSizeHold = p2.getHandSize();
  for(int i = 0; i < handSizeHold; i++){
    if(p2.checkHandForBook(cardHold1, cardHold2)){
      p2.removeCardFromHand(cardHold1);
      p2.removeCardFromHand(cardHold2);
      p2.bookCards(cardHold1, cardHold2);
      myFile << p2.getName() << " books " << cardHold1 << " and " << cardHold2 << endl;
    }
  }
  
  myFile << '\n';

  Player *playerPoint = &p1;                                                 //used to switch between players
  Card pickCard;                                                             //placeholder for cards

  //defines the parameters to keep the game going
  while((deck.size() != 0)||(p1.getHandSize() != 0)||(p2.getHandSize() != 0)){
    
    //prevents player from having to pick from a hand with zero cards
    if(((*playerPoint).getHandSize() == 0)&&(deck.size() != 0)){
      pickCard = deck.dealCard();
      myFile << (*playerPoint).getName() << " has 0 cards on hand and draws " << pickCard << endl;
      (*playerPoint).addCard(pickCard);
    }

    cout << ".";

    pickCard = (*playerPoint).chooseCardFromHand();             
    myFile << (*playerPoint).getName() << " asks - Do you have a(n) " << pickCard.rankString(pickCard.getRank()) << endl;
  
    //switches to another player
    if((*playerPoint).showHand() == p1.showHand()){playerPoint = &p2;}else{playerPoint = &p1;};
  
    if((*playerPoint).cardInHand(pickCard)){
      myFile << (*playerPoint).getName() << " says - Yes. I have " << pickCard.rankString(pickCard.getRank()) << endl;
      pickCard = (*playerPoint).removeCardFromHand(pickCard);
      
      if((*playerPoint).showHand() == p1.showHand()){playerPoint = &p2;}else{playerPoint = &p1;};
     
      myFile << (*playerPoint).getName() << " books the " << pickCard.rankString(pickCard.getRank()) << endl;
      
      //defines the process of adding a card to hand and booking it 
      (*playerPoint).addCard(pickCard);
      (*playerPoint).checkHandForBook(cardHold1, cardHold2);
      (*playerPoint).removeCardFromHand(cardHold1);
      (*playerPoint).removeCardFromHand(cardHold2);
      (*playerPoint).bookCards(cardHold1, cardHold2);
      
      //prevents player from having zero cards on hand after booking a pair
      if(((*playerPoint).getHandSize() == 0)&&(deck.size() != 0)){
        pickCard = deck.dealCard();
        myFile << (*playerPoint).getName() << " has 0 cards on hand and draws " << pickCard << endl;
        (*playerPoint).addCard(pickCard);
      }

      //displays players current hand
      myFile << p1.getName() << " has " << p1.showHand() << endl;
      myFile << p2.getName() << " has " << p2.showHand() << endl;
      myFile << '\n';
    }else{
      myFile << (*playerPoint).getName() << " says - Go Fish" << endl;
        
      if((*playerPoint).showHand() == p1.showHand()){playerPoint = &p2;}else{playerPoint = &p1;};

      //defines when a player picks from the deck
      if(deck.size() != 0){
        pickCard = deck.dealCard();
        
        myFile << (*playerPoint).getName() << " draws a(n) " << pickCard.rankString(pickCard.getRank()) << endl;
        
        (*playerPoint).addCard(pickCard);

        //defines the process whenever a player has pair on hand after drawing
        if((*playerPoint).checkHandForBook(cardHold1, cardHold2)){
          (*playerPoint).removeCardFromHand(cardHold1);
          (*playerPoint).removeCardFromHand(cardHold2);
          (*playerPoint).bookCards(cardHold1, cardHold2);

          myFile << (*playerPoint).getName() << " books " << cardHold1 << " and " << cardHold2 << endl;
        }

        if(((*playerPoint).getHandSize() == 0)&&(deck.size() != 0)){
          pickCard = deck.dealCard();
          myFile << (*playerPoint).getName() << " has 0 cards on hand and draws " << pickCard << endl;
          (*playerPoint).addCard(pickCard);
        }

        if((*playerPoint).showHand() == p1.showHand()){playerPoint = &p2;}else{playerPoint = &p1;};
        
        myFile << p1.getName() << " has " << p1.showHand() << endl;
        myFile << p2.getName() << " has " << p2.showHand() << endl;
        myFile << '\n';
      }else{

        myFile << "No more cards in deck" << endl;
        if((*playerPoint).showHand() == p1.showHand()){playerPoint = &p2;}else{playerPoint = &p1;};

        myFile << p1.getName() << " has " << p1.showHand() << endl;
        myFile << p2.getName() << " has " << p2.showHand() << endl;

        myFile << '\n';
      }
    }
  }

  myFile << p1.getName() << " has " << p1.getBookSize() << " pairs" << endl;
  myFile << p2.getName() << " has " << p2.getBookSize() << " pairs" << endl; 
  myFile << '\n';

  if(p1.getBookSize() > p2.getBookSize()){
    myFile << p1.getName() << " wins" << endl;
    myFile << p2.getName() << " is executed via firing squad" << endl;
  }else if(p1.getBookSize() < p2.getBookSize()){
    myFile << p2.getName() << " wins" << endl;
    myFile << p1.getName() << " is executed via electrocution" << endl;
  }else{
    myFile << p1.getName() << " and " << p2.getName() << " are tied" << endl;
    myFile << "Both live for now" << endl;
  }

 cout << "." << endl;
 myFile.close();
 return 0;
}
