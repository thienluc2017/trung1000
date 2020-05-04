#pragma once
#include"tetromino.h"
#include "input.h"
#include "piece.h"
class Game{
   public:
     Color color(unsigned char , unsigned char , unsigned char, unsigned char);
     int game();
   private:
     enum Game_Screen{man_hinh_bat_dau=0,man_hinh_choi,man_hinh_thay_doi_line,man_hinh_end_game};
     enum Vi_tri_ve_chu{Vi_tri_ve_chu_trai,Vi_tri_ve_chu_giua};
     unsigned char board[220];
     unsigned char lines[CAO];
     int dong_cho;
     Piece piece;
     Game_Screen man_hinh;
     int level;
     int line_break;
     int scores;
     float time_next;
     float highlight_end_time;
     float time;
     float thoi_gian_theo_level(int );
     int  lay_ngau_nhien_1_so( int );
     bool cap_nhat_game_bat_dau(Game *, const Input *);
     void khoi_tao_toc_do_va_toa_do_khoi(Game *);
     bool delay_Tetromino(Game *);
     bool xem_o_co_con_khong(const Piece *piece,const unsigned char *, int , int );
     void hop_cac_khoi_lai_voi_nhau(Game *);
     unsigned char lay_khoi_Tetromino(const Tetromino *, int , int , int );
     unsigned char lay_mot_toa_do_trong_ma_tran(const unsigned char *, int , int , int );
     unsigned char xem_dong_da_day_chua(const unsigned char *, int , int );
     void gan_gia_tri_cho_mot_toa_do_trong_ma_tran(unsigned char *, int , int , int , unsigned char );
     unsigned char xem_dong_trong_khong(const unsigned char *, int , int );
     int find_lines(const unsigned char *, int , int , unsigned char *);
     void cap_nhat_luc_choi(Game *,const Input *);
     int cap_nhat_game(Game *,const Input *);
     void cap_nhat_cac_dong(Game *);
     void cap_nhat_end_game(Game *, const Input *);
     void draw_piece(SDL_Renderer *,const Piece *,int , int ,bool );
     int tinh_diem(int , int );
     void ve_khoi_Tetromino(SDL_Renderer *,int , int, unsigned char ,int , int ,bool  );
     void xoahang(unsigned char *, int , int , const unsigned char *);
     void draw_board(SDL_Renderer *,const unsigned char *, int , int ,int , int );
     void viet_chu(SDL_Renderer *,TTF_Font *,const char *,int , int ,Game::Vi_tri_ve_chu ,Color );
     void ve_hinh_chieu(SDL_Renderer *,int x, int , int , int , Color );
     void ve_hinh_voi_toa_do(SDL_Renderer *,int x, int , int , int , Color );
     void draw_piecehidden(SDL_Renderer *,const Piece *,int , int ,bool );
     void render_gamehidden(Game *,SDL_Renderer *,TTF_Font *);
     void ve_khoi_Tetromino_mot_lan_duoc_luon(SDL_Renderer *renderer,int hang, int cot, unsigned char value,int toa_do_x, int toa_do_y,bool );

};

