#include <iostream>

#include "engine/Board.hpp"

int main(int argc, char *argv[])
{
    Chess::Engine::Board board{};
    std::cout << board << std::endl;
    return 0;
}
