
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>
#include <algorithm>

/* ************************************************************************** */

ushort menuChoice = 0;

int main() {
  std::cout << "Lasd Libraries 2022" << std::endl;

  while(menuChoice != 3) {

    while (std::cout << std::endl << "Welcome to the Exercise 5." << std::endl << "Choose the function:" << std::endl
        << std::endl << "\t[1] lasdtest;" << std::endl << std::endl << "\t[2] mytest;"
        << std::endl << std::endl << "\t[3] Exit." << std::endl << std::endl && !(std::cin >> menuChoice)) {

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error: Invalid input." << std::endl << std::endl;
    }
    
    switch (menuChoice) {
        case 1:
            lasdtest();
            break;
        case 2:
            myTestMainMenu();
            break;
        case 3:
            std::cout << std::endl << "Exiting the program..." << std::endl;
            break;
        default:
        std::cout << std::endl << std::endl << "Error: Invalid entered value. Return to the Main Menu..." << std::endl;
        break;
      }
    }

    return 0;
}
