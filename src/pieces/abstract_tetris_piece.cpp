#include "pieces/abstract_tetris_piece.hpp"

AbstractTetrisPiece3d::~AbstractTetrisPiece3d(){};
AbstractTetrisPiece3d::AbstractTetrisPiece3d(){};
AbstractTetrisPiece3d::AbstractTetrisPiece3d(const Color& c) : color(c){};

Color AbstractTetrisPiece3d::getColor() const { return color; }