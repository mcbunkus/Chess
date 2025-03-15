#include "Board.hpp"

#include <unordered_map>

namespace Chess::Engine
{

    // The constructor preloads all possible moves at each square for each piece type
    Board::Board()
    {
        // precomputing valid moves for knights, which can be done once at the beginning since knights cannot be blocked
        GenerateKnightMoves();
    }

    void Board::GenerateKnightMoves()
    {
        for (uint64_t squareIndex = 0; squareIndex < 64; squareIndex++)
        {
            uint64_t knight = GetSquare(squareIndex);
            uint64_t moves = 0; // possible moves

            moves |= (knight << 17) & 0xFEFEFEFEFEFEFEFEULL; // Up 2, right 1
            moves |= (knight << 15) & 0x7F7F7F7F7F7F7F7FULL; // Up 2, left 1
            moves |= (knight << 10) & 0xFCFCFCFCFCFCFCFCULL; // Right 2, up 1
            moves |= (knight << 6) & 0x3F3F3F3F3F3F3F3FULL; // Left 2, up 1
            moves |= (knight >> 17) & 0x7F7F7F7F7F7F7F7FULL; // Down 2, left 1
            moves |= (knight >> 15) & 0xFEFEFEFEFEFEFEFEULL; // Down 2, right 1
            moves |= (knight >> 10) & 0x3F3F3F3F3F3F3F3FULL; // Left 2, down 1
            moves |= (knight >> 6) & 0xFCFCFCFCFCFCFCFCULL; // Right 2, down 1

            knightMoves[squareIndex] = moves;
        }


        // initializes the board in all starting positions
        Reset();
    }

    uint64_t Board::GetRookMoves(int square, uint64_t blockers)
    {
        uint64_t moves = 0;

        // shift left until a blocker or the end of the board is hit
        for (int i = square + 1; i * 8 != 0; i++)
        {
            moves |= (1ULL << i);
            if (blockers & (1ULL << i))
                break;
        }

        // shift right until a blocker or the end of the board is hit
        for (int i = square - 1; i % 8 != 7 && i >= 0; i--)
        {
            moves |= (1ULL << i);
            if (blockers & (1ULL << i))
                break;
        }

        return moves;
    }


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

    uint64_t Board::GetSquare(const uint64_t index) { return 1ULL << index; }
    uint64_t Board::GetSquare(const uint64_t rank, const uint64_t file) { return 1ULL << ((8 * rank + file)); }

    std::ostream &operator<<(std::ostream &os, const Board &board)
    {

        static std::string RESET = "\033[0m";
        static std::string GREEN = "\033[32m"; // for white pieces
        static std::string BLUE = "\033[34m"; // for black pieces


        os << '\n';

        // starts from top left, then to the right
        for (uint64_t rank = 8; rank > 0; rank--)
        {
            os << " " << rank << "  ";
            for (uint64_t file = 0; file < 8; file++)
            {
                // rank - 1 is a little confusing, but for internal calculations, rank and file starts at 0. The
                // loop starts at 8 for printing the rank number on the side, but also because it's unsigned, there's
                // shenanigans when it tries to decrement below 0 while simultaneously checking if rank >= 0 ...
                const uint64_t square = Board::GetSquare(rank - 1, file);

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

        os << "\n     A  B  C  D  E  F  G  H\n";

        return os;
    }
} // namespace Chess::Engine
