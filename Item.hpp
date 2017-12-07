#ifndef ITEM_H
#define ITEM_H
#include "Case.hpp"

class Item : public Case {
private:
  mutable string name;
  mutable int pods;

public:
  //CONSTRUCTOR
  Item(char s = '?', string n = "Unknown Item", int i = -1, int j = -1, 
       const int p = 1);
  Item(const Item &i);

  //OPERATORS
  Item& operator=(const Item &i);

  //GETTERS
  string getName() const;
  int getPods() const;

  //SETTER
  void setPods(const int i);
  void setName(string c);

  virtual void print();

};

#endif

