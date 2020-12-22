#include <iostream>
#include <string>
#include "board.hpp"

int main()
{
    chessBoard game;
    std::cout << "\n Chess bot v.1" << std::endl;
    game.printHelp();
    bool gameon = true;
    while (gameon)
    {
        game.reset();
        std::string pick_side = "";
        while (pick_side != "b" && pick_side != "w" && pick_side != "q")
        {
            std::cout << std::endl
                      << "Choose side: (b)lack or (w)hite or (q)uit? ";
            std::cin >> pick_side;
        }
        if (pick_side == "q")
        {
            std::cout << "Thanks For Playing." << std::endl;
            break;
        }

        if (pick_side == "b")
        {
            game.AIMove();
        }
        else
        {
            game.printBoard();
        }
        while (gameon = game.promptInput()) // promptInput check for user illegal moves
        {
            if (!game.hasKing()) // has king only works if king is got not a check or check mate
            {
                std::cout << " You Win!" << std::endl;
                break;
            }
            game.AIMove();
            if (!game.hasKing()) // has king only works if king is got not a check or check mate
            {
                std::cout << " You Lost!" << std::endl;
                break;
            }
        }
    }

    return 0;
}