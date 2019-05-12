#include <iostream>

#include "LeaveATip.h"

#define CONTINUE_WORD "yes"
#define EXIT_WORD "no"

using namespace fuzzylogic;

int main(int argc, char **argv) {

    if (argc != 1) {
        std::cerr << "Usage : " << ((argc >= 1) ? argv[0] : "program") << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Welcome to \"Leave a tip\" !" << std::endl << "You can evaluate the tip to leave" << std::endl
              << std::endl;

    LeaveATip leaveATip;

    std::string answer;

    do {
        answer = EXIT_WORD;

        type service = 0;
        type food = 0;

        std::cout << "Tip interval : [0, 25]" << std::endl;

        std::cout << "Please enter your marks..." << std::endl;

        std::cout << "Service mark : " << std::endl;
        std::cin >> service;

        std::cout << "Food mark : " << std::endl;
        std::cin >> food;

        leaveATip.setFood(food);
        leaveATip.setService(service);


        std::cout << "The amount of the tip is : " << leaveATip.evaluateTip() << '$' << std::endl << std::endl;

        std::cout << "Do you want continue ?" << '(' << CONTINUE_WORD << '/' << EXIT_WORD << ')' << std::endl;

        std::cin >> answer;

    } while (answer == CONTINUE_WORD);

    return EXIT_SUCCESS;
}