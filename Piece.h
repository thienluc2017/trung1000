#pragma once
class Piece
{

   public:
      //random
     unsigned char random_tetromino;
     //toa do hang
     int offset_hang;
     //toa do cot
     int offset_cot;
     //co che xoay
     int rotation;
   private:
     int x_;
     int y_;
     //goc
     int angle_;
};
