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
        while ((gameon = game.promptInput()))
        {
            // After player's move, check opponent's state
            if (game.isOpponentCheckmate()) {
                std::cout << "You win by checkmate!" << std::endl;
                break;
            } else if (game.isOpponentInCheck()) {
                std::cout << "Opponent is in check!" << std::endl;
            }

            game.AIMove();

            // After AI's move, check player's state
            if (game.isCheckmate()) {
                std::cout << "Checkmate! You lost!" << std::endl;
                break;
            } else if (game.isInCheck()) {
                std::cout << "Check!" << std::endl;
            }
        }
    }
    return 0;
}
