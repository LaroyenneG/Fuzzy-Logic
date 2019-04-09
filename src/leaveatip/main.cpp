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

    LeaveATipTest leaveATip;

    std::string answer;

    do {
        answer = EXIT_WORD;

        type service = 0;
        type food = 0;
        type min = 0;
        type max = 0;

        std::cout << "Please enter your tip interval" << std::endl;

        std::cout << "Minimum tip :" << std::endl;
        std::cin >> min;

        std::cout << "Maximum tip" << std::endl;
        std::cin >> max;


        std::cout << "Please enter your marks..." << std::endl;

        std::cout << "Service mark : " << std::endl;
        std::cin >> service;

        std::cout << "Food mark : " << std::endl;
        std::cin >> food;


        leaveATip.setMinTip(min);
        leaveATip.setMaxTip(max);
        leaveATip.setFood(food);
        leaveATip.setService(service);


        std::cout << "The amount of the tip is : " << leaveATip.evaluateTip() << '$' << std::endl << std::endl;

        std::cout << "Do you want continue ?" << '(' << CONTINUE_WORD << '/' << EXIT_WORD << ')' << std::endl;

        std::cin >> answer;

    } while (answer == CONTINUE_WORD);

    return EXIT_SUCCESS;
}