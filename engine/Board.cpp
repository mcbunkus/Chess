#include "Board.hpp"

#include <unordered_map>

namespace Chess::Engine
{

    Board::Board() { Reset(); }


    void Board::Reset()
    {
        pawns = 0x00FF00000000FF00ULL;
        knights = 0x4200000000000042ULL;
        bishops = 0x2400000000000024ULL;
        rooks = 0x8100000000000081ULL;
        queens = 0x0800000000000008ULL;
        kings = 0x1000000000000010ULL;

        whites = 0x000000000000FFFFULL;
        blacks = 0xFFFF000000000000ULL;

        occupancy = 0xFFFF00000000FFFFULL;
    }

    uint64_t Board::GetSquare(uint64_t rank, uint64_t file) const { return 1ULL << ((8 * rank + file)); }

    std::ostream &operator<<(std::ostream &os, const Board &board)
    {

        static std::string RESET = "\033[0m";
        static std::string GREEN = "\033[32m"; // for white pieces
        static std::string BLUE = "\033[34m"; // for black pieces


        // starts from top left, then to the right
        for (uint64_t rank = 8; rank > 0; rank--)
        {
            os << " " << rank << "  ";
            for (uint64_t file = 0; file < 8; file++)
            {
                // rank - 1 is a little confusing, but for internal calculations, rank and file starts at 0. The
                // loop starts at 8 for printing the rank number on the side, but also because it's unsigned, there's
                // shenanigans when it tries to decrement below 0 while simultaneously checking if rank >= 0 ...
                uint64_t square = board.GetSquare(rank - 1, file);

                if (!(square & board.occupancy))
                {
                    os << " - ";
                }

                if (square & board.whites)
                {
                    os << GREEN;
                }
                else if (square & board.blacks)
                {
                    os << BLUE;
                }

                if (square & board.pawns)
                {
                    os << " P " << RESET;
                }
                else if (square & board.knights)
                {
                    os << " N " << RESET;
                }
                else if (square & board.bishops)
                {
                    os << " B " << RESET;
                }
                else if (square & board.rooks)
                {
                    os << " R " << RESET;
                }
                else if (square & board.queens)
                {
                    os << " Q " << RESET;
                }
                else if (square & board.kings)
                {
                    os << " K " << RESET;
                }
            }
            os << '\n';
        }

        return os;
    }
} // namespace Chess::Engine
