#include "card.h"

using namespace std;

  Card::Card()
  {
    myRank = 1;
    mySuit = spades;
  }

  Card::Card(int rank, Suit s)
  {
    myRank = rank;
    mySuit = s;
  }

  string Card::toString() const
  {
    string integer[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    string stringHold;

    if(mySuit == spades){
      stringHold = "s";
    }else if(mySuit == hearts){
      stringHold = "h";
    }else if(mySuit == diamonds){
      stringHold = "d";
    }else{
      stringHold = "c";
    }
   
    string stringCard = integer[myRank-1] + stringHold;
    return stringCard;
  }

  bool Card::sameSuitAs(const Card& c) const
  {
    if(mySuit == c.mySuit){
      return true;
    }else{
      return false;
    }
  }

  int Card::getRank() const
  {
    return myRank;
  }
  
  string Card::suitString(Suit s) const
  {
    string stringHold;

    if(s == spades){
      stringHold = "s";
    }else if(s == hearts){
      stringHold = "h";
    }else if(s == diamonds){
      stringHold = "d";
    }else{
      stringHold = "c";
    }

    return stringHold;
  }

  string Card::rankString(int r) const
  {
    string rank[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    return rank[r-1];
  }

  bool Card::operator ==(const Card& rhs) const
  {
    if((myRank == rhs.myRank)&&(mySuit == rhs.mySuit)){
      return true;
    }else{
      return false;
    }
  }

  bool Card::operator !=(const Card& rhs) const
  {
    if((myRank != rhs.myRank)||(mySuit != rhs.mySuit)){
      return true;
    }else{
      return false;
    }
  }

  ostream& operator << (ostream& out, const Card& c)
  {
    out << c.toString();
    return out;
  }
