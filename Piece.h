#pragma once
class Piece
{

   public:
      //random
     unsigned char random_tetromino=0;
      unsigned char random_tetromino_next;
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
