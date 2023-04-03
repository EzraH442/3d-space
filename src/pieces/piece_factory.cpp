#include "pieces/piece_factory.hpp"

#include "SDL_system.h"
#include "pieces/i_piece.hpp"
#include "pieces/j_piece.hpp"
#include "pieces/l_piece.hpp"
#include "pieces/o_piece.hpp"
#include "pieces/s_piece.hpp"
#include "pieces/t_piece.hpp"
#include "pieces/tetris_piece.hpp"
#include "pieces/z_piece.hpp"

TetrisPieceFactory::TetrisPieceFactory() {}

AbstractTetrisPiece3d* TetrisPieceFactory::createPiece(int id) {
  switch (id) {
    case 0:
      return new j_piece();
    case 1:
      return new l_piece();
    case 2:
      return new s_piece();
    case 3:
      return new t_piece();
    case 4:
      return new z_piece();
    case 5:
      return new o_piece();
    case 6:
      return new i_piece();
  }
  return new j_piece();
}