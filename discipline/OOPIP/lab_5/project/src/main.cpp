#include "weapon.hpp"
#include <iostream>

int main() {

  const int ATTACK_POWER = 100;
  const int NUM_ITERATIONS = 10;

  Shield sh(1000);
  std::cout << sh.getName() << std::endl;
  std::cout << "STRIKE: ";
  for (int i = 0; i < NUM_ITERATIONS; i++)
    std::cout << sh.strike() << ", ";
  std::cout << std::endl;

  std::cout << "PROTECT: ";
  for (int i = 0; i < NUM_ITERATIONS; i++)
    std::cout << sh.protect(ATTACK_POWER) << ", ";
  std::cout << std::endl;
  std::cout <<
    "---------------------" << std::endl;
  
  Sword sw(1000);
  std::cout << sw.getName() << std::endl;
  std::cout << "STRIKE: ";
  for (int i = 0; i < NUM_ITERATIONS; i++)
    std::cout << sw.strike() << ", ";
  std::cout << std::endl;

  std::cout << "PROTECT: ";
  for (int i = 0; i < NUM_ITERATIONS; i++)
    std::cout << sw.protect(ATTACK_POWER) << ", ";
  std::cout << std::endl;
  std::cout <<
    "---------------------" << std::endl;

  Club cl(500, 500);
  std::cout << cl.getName() << std::endl;
  std::cout << "STRIKE: ";
  for (int i = 0; i < NUM_ITERATIONS; i++)
    std::cout << cl.strike() << ", ";
  std::cout << std::endl;

  std::cout << "PROTECT: ";
  for (int i = 0; i < NUM_ITERATIONS; i++)
    std::cout << cl.protect(ATTACK_POWER) << ", ";
  std::cout << std::endl;
  std::cout <<
    "---------------------" << std::endl;

  Weapon * w = new Sword(10);
  std::cout << w->protect(ATTACK_POWER) << std::endl;

  return 0;
}
