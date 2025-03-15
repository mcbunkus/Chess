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
        uint64_t pawns;
        uint64_t knights;
        uint64_t bishops;
        uint64_t rooks;
        uint64_t queens;
        uint64_t kings;

        uint64_t whites;
        uint64_t blacks;

        uint64_t occupancy;


    public:
        Board();
        void Reset();

        uint64_t GetSquare(uint64_t rank, uint64_t file) const;

        friend std::ostream &operator<<(std::ostream &os, const Board &board);
    };

} // namespace Chess::Engine
