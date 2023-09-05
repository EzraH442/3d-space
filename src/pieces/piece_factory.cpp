#include "pieces/piece_factory.hpp"

#include <SDL.h>

#include "enums.hpp"
#include "pieces/i_piece.hpp"
#include "pieces/j_piece.hpp"
#include "pieces/l_piece.hpp"
#include "pieces/o_piece.hpp"
#include "pieces/s_piece.hpp"
#include "pieces/t_piece.hpp"
#include "pieces/tetris_piece.hpp"
#include "pieces/z_piece.hpp"

TetrisPieceFactory::TetrisPieceFactory() {}

std::unique_ptr<TetrisPiece3d> TetrisPieceFactory::createPiece(
    const PieceType& type) {
  switch (type) {
    case PieceType::J:
      return std::make_unique<j_piece>();
    case PieceType::L:
      return std::make_unique<l_piece>();
    case PieceType::S:
      return std::make_unique<s_piece>();
    case PieceType::T:
      return std::make_unique<t_piece>();
    case PieceType::Z:
      return std::make_unique<z_piece>();
    case PieceType::O:
      return std::make_unique<o_piece>();
    case PieceType::I:
      return std::make_unique<i_piece>();
  }
}