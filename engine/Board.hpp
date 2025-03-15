#pragma once

//
// Created by auste on 3/9/2025.
//

#include <cstdint>
#include <ostream>

namespace Chess::Engine
{


    class Board
    {

        // bitboard definitions
        uint64_t pawns{};
        uint64_t knights{};
        uint64_t bishops{};
        uint64_t rooks{};
        uint64_t queens{};
        uint64_t kings{};

        uint64_t whites{};
        uint64_t blacks{};

        uint64_t occupancy{};

        uint64_t knightMoves[64]{}; // precomputed knight moves


    private:
        // These are for precomputing valid moves for each piece type in each square, for SPEED
        void GenerateKnightMoves();

    public:
        Board();
        void Reset();

        static uint64_t GetSquare(uint64_t rank, uint64_t file);
        static uint64_t GetSquare(uint64_t index);

        static uint64_t GetRookMoves(int square, uint64_t blockers);

        friend std::ostream &operator<<(std::ostream &os, const Board &board);
    };

} // namespace Chess::Engine
