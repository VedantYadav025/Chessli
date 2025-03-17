#pragma once
#include "pieces.h"
#include "utils/chess_constants.h"
#include "utils/utils.h"

#include <cstdint>
#include <vector>
#include <iostream>

namespace Chess
{
	using BitBoard = std::uint64_t;

	constexpr BitBoard maskFile(const std::size_t& file) {
		if (file > 7) return 0; // Simplified for constexpr
		return 0x0101010101010101ULL << file;
	}

	constexpr BitBoard clearFile(const std::size_t& file) {
		if (file > 7) return 0; // Simplified for constexpr (no exceptions)
		return ~maskFile(file);
	}

	constexpr BitBoard maskRank(const std::size_t& rank) {
		if (rank > 7) return 0; // Simplified for constexpr
		return 0xFFULL << (rank * 8);
	}


	constexpr BitBoard clearRank(const std::size_t& rank) {
		if (rank > 7) return 0; // Simplified for constexpr
		return ~maskRank(rank);
	}



	constexpr inline auto setBit = [](BitBoard& bitboard, const Square& sq) -> void
		{
			bitboard |= 1ULL << static_cast<int>(sq);
		};
	constexpr inline auto unsetBit = [](BitBoard& bitboard, const Square& sq) -> void
		{
			bitboard &= ~(1ULL << static_cast<int>(sq));
		};

	inline  BitBoard bitboardOfOccupiedSquares(const std::vector<Square>& vec)
	{
		BitBoard bitboard = 0ULL;
		for (const auto& sq : vec)
		{
			setBit(bitboard, sq);
		}
		return bitboard;
	}

	constexpr std::array<BitBoard, 8> initMaskRank()
	{
		std::array<BitBoard, 8> arr{};
		for (std::size_t i = 0; i < 8; i++)
		{
			arr[i] = maskRank(i);
		}
		return arr;
	}


	constexpr std::array<BitBoard, 8> initClearRank()
	{
		std::array<BitBoard, 8> arr{};
		for (std::size_t i = 0; i < 8; i++)
		{
			arr[i] = clearRank(i);
		}
		return arr;
	}

	constexpr std::array<BitBoard, 8> initMaskFile()
	{
		std::array<BitBoard, 8> arr{};
		for (std::size_t i = 0; i < 8; i++)
		{
			arr[i] = maskFile(i);
		}
		return arr;
	}

	constexpr std::array<BitBoard, 8> initClearFile()
	{
		std::array<BitBoard, 8> arr{};
		for (std::size_t i = 0; i < 8; i++)
		{
			arr[i] = clearFile(i);
		}
		return arr;
	}

	constexpr std::array<BitBoard, 8> mask_rank = initMaskRank();
	constexpr std::array<BitBoard, 8> clear_rank = initClearRank();
	constexpr std::array<BitBoard, 8> mask_file = initMaskFile();
	constexpr std::array<BitBoard, 8> clear_file = initClearFile();

	// printing BitBoard in a nice-way
	void printBitBoard(const BitBoard& bitboard);
	// Getting rook masks
	constexpr inline BitBoard generateRookMasks(const Square& sq)
	{
		int square_bit = static_cast<int>(sq);
		int rank = square_bit / 8;
		int file = square_bit % 8;
		BitBoard rook = mask_file[file] | mask_rank[rank];
		unsetBit(rook, static_cast<Square>(rank * 8)); //rook.unsetBit(rank * 8);
		//rook.unsetBit((rank + 1) * 8 - 1);
		unsetBit(rook, static_cast<Square>((rank + 1) * 8 - 1));
		//rook.unsetBit(file);
		unsetBit(rook, static_cast<Square>(file));
		//rook.unsetBit(file + 56);
		unsetBit(rook, static_cast<Square>(file + 56));
		//rook.unsetBit(static_cast<int>(square));
		unsetBit(rook, static_cast<Square>(sq));
		return rook;
	}

	constexpr inline std::array<BitBoard, 64> initRookMasks()
	{
		std::array<BitBoard, 64> rook_mask;
		for (std::size_t i = 0; i < 64; i++)
			rook_mask[i] = generateRookMasks(static_cast<Square>(i));
		return rook_mask;
	}

	constexpr std::array<BitBoard, 64> rook_mask = initRookMasks();
}

