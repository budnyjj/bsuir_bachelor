#include <string>
#include <stdlib.h>
#include <iostream>

class Weapon
{
protected:
  std::string name;
  int blow_power;
  int protect_power;
public:
  Weapon(int bp, int pp)
    : blow_power(bp), protect_power(pp)
  {};
  virtual int strike() {
    int injure = 0;
    if (this->blow_power)
      {
	injure = rand() % this->blow_power;
	this->blow_power -= injure/10;
      }
    return injure;
  };
  virtual int protect(const int& power) {
    int protect = rand() % this->protect_power;
    this->protect_power -= protect % 10;
    int diff = power - protect;
    // std::cout << "diff: " << diff << "; ";
    return (diff > 0) ? diff : 0;
  };
  std::string getName()
  {
    return this->name;
  };
};


class Shield : public Weapon //щит
{
public:
  Shield(int pp)
    : Weapon(0, pp)
  {
    this->name = "SHIELD";
  }
  virtual int strike() {
    return 0;
  };
};


class Club : public Weapon //дубинка
{
public:
  Club(int bp, int pp)
    : Weapon(bp, pp)
  {
    this->name = "CLUB";
  }
};


class Sword : public Weapon
{
public:
  Sword(int bp)
    : Weapon(bp, 0)
  {
    this->name = "SWORD";
  }
  virtual int protect(const int& power)
  {
    return 0;
  };

};
