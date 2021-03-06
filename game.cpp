   #include "game.h"
   #include <SDL_mixer.h>
//you can write a game that two people can play
//theo https://tetris.fandom.com/wiki/Tetris_(NES,_Nintendo)
//https://lazyfoo.net/tutorials/SDL/index.php
//press d to disable music
//press r to resume music
/*
  you may be wonder why i hold tetremino in board (not hold shape) because  playing hidden game is too hard
 I played game only hold shape and i got 0 score.So i write hold tetremino to play easier.

  */
  /*
     if you want to optimze code, t think use unsigned char for the 0<=interger<=256 because it use 1 byte and int use 4 or 2 byte
      should use ++varible because use varible++ create a new auxiliary parameters.
      you can use graphs instead of draw by sdl :)))
      -About althogrithm i think every fuction and  class is a good basic for you to develop this game


  */

/*Thuật toán game như sau:
//max đạt dc la level 14

cho chiều rộng 10 ô chiều cao là 20 ô (300*720) và có chiều cao thêm 2 ô nữa nhưng bị ẩn để vẽ hình chiếu

tất cả các ô gạch giá trị bằng 0  và các khối có số khác nhau từ 1 đến 7 nên nếu xếp vào gặp số khác 0 thì dừng
(xử lí va chạm)
Tạo một viên gạch hiện tại để chơi
Tạo hình bóng có dữ liệu từ viên gạch hiện tại
Nếu nhận được phím điều khiển từ bàn phím:
     - Xóa khối gạch,bóng
     - Xử lí
     - Cập nhật lại tình trạng gạch, bóng sau khi xử kí

 // càng về sau (level cao hơn ) thì càng tăng

Kiểm tra đi xuống (cứ hết nhịp game là kiểm tra đi xuống)
  If Đi xuống tiếp được
  Xóa cũ, cập nhật, vẽ mới
Else
    Gán giá trị viên gạch cho bảng
    In ra bảng mới

    If(thua)
     đi đến màn hình game over
     Break;
    Else
    Xóa khối hiện tại
*/
/*
  cách xoay:
       chia làm 4 TH :0,90,180,270(độ)
       ta xét các ma trận vuông [side,side]
       ta vẽ ra rồi thử là dc quy luật

  */
/*
   giải thích tại sao level tăng trong khi const tocdoframes mà tốc độ rơi xuống của khối vẫn tăng:
      theo https://tetris.fandom.com/wiki/Tetris_(NES,_Nintendo) ta dc tốc độ khung hình (nói dễ hiểu thì time
       rơi của khối nó dần ít lại )

  */


   Game mau;
   //ham khoi tao
Color Game::color(unsigned char x_, unsigned char y_, unsigned char z_, unsigned char t_){
        Color color_;
        color_.x=x_;
        color_.y=y_;
        color_.z=z_;
        color_.t=t_;
        return color_;
}

 const Color mau_chinh[] = {
    mau.color(0x28, 0x28, 0x28, 0xFF),
    mau.color(0xff, 0x00, 0x00, 0xff),
    mau.color(0x80, 0x80, 0x80, 0xff),
    mau.color(0xff, 0x00, 0xff, 0xff),
    mau.color(0x00, 0x00, 0x7f, 0xff),
    mau.color(0xff, 0x7f, 0x00, 0xff),
    mau.color(0x7f, 0x40, 0x00, 0xff),
    mau.color(0x00, 0x7f, 0x7f, 0xff)
};
   //màu của các vạch giữa
const Color mau_den[] = {
     mau.color( 0, 0, 0, 0)
    };

//khoi tao
Tetromino tetromino(const unsigned int *khoihinh, const int side){
    return { khoihinh, side };
}
//lay so 1 den 7 cho cac khoi de sap xep
const unsigned int TETROMINO_L[] = {
    6, 0, 0,
    6, 6, 6,
    0, 0, 0
};

const unsigned int TETROMINO_J[] = {
    0, 0, 7,
    7, 7, 7,
    0, 0, 0
};
const unsigned int TETROMINO_O[] = {
    2, 2,
    2, 2
};
const unsigned int TETROMINO_T[] = {
    0, 0, 0,
    3, 3, 3,
    0, 3, 0
};
const unsigned int TETROMINO_S[] = {
    0, 4, 4,
    4, 4, 0,
    0, 0, 0
};
const unsigned int TETROMINO_Z[] = {
    5, 5, 0,
    0, 5, 5,
    0, 0, 0
};
const unsigned int TETROMINO_I[] = {
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};
//lay tat ca cac khoi de khi random
const Tetromino TETROMINOS[] = {
    tetromino(TETROMINO_I, 4),
    tetromino(TETROMINO_O, 2),
    tetromino(TETROMINO_T, 3),
    tetromino(TETROMINO_S, 3),
    tetromino(TETROMINO_Z, 3),
    tetromino(TETROMINO_L, 3),
    tetromino(TETROMINO_J, 3)
};
//theo tetris (nitendo) max tốc dộ là level 14
//https://tetris.fandom.com/wiki/Tetris_(NES,_Nintendo)
 float Game::thoi_gian_theo_level(int level){
    if (level > 14){
        level = 14;
    }
   // cout<<tocdo[level] * tocdoframe;
    return tocdo[level] * tocdoframe;
}
//lấy 1 random 1 số trong khoảnh từ 0 đến piece
int Game::lay_ngau_nhien_1_so( int piece){
    return  rand()%piece;
}


void Game::khoi_tao_toc_do_va_toa_do_khoi(Game *game){
   unsigned char temp=game->piece.random_tetromino_next;
    game->piece = {};
    //lay random manh
   //if(temp==0){

    //game->piece.random_tetromino = (unsigned char)lay_ngau_nhien_1_so(0, sizeof(TETROMINOS) / sizeof((TETROMINOS)[0]));
   //}else{
       //cout<<"vkl";
       game->piece.random_tetromino = temp;
  // }
    game->piece.random_tetromino_next = (unsigned char)lay_ngau_nhien_1_so( sizeof(TETROMINOS) / sizeof((TETROMINOS)[0]));
    //game->piece.random_tetromino = game->piece.random_tetromino_next;
    //nơi bắt đầu là ở giữa chiều rộng board(rong/2,0)
    game->piece.offset_cot = RONG/2;
    //toc do
    game->time_next = game->time + thoi_gian_theo_level(game->level);
}

bool Game::delay_Tetromino(Game *game){
    (game->piece.offset_hang)++;
    if (xem_o_co_con_khong(&game->piece, game->board, RONG , CAO)==false)
    {
         (game->piece.offset_hang)--;
         hop_cac_khoi_lai_voi_nhau(game);
         khoi_tao_toc_do_va_toa_do_khoi(game);
       return false;
    }

    game->time_next = game->time + thoi_gian_theo_level(game->level);
    //cout<< game->time_next<<endl;
   // cout<<"gametime"<<game->time<<endl;
    return true;
}
bool Game::xem_o_co_con_khong(const Piece *piece,const unsigned char *board, int rong, int cao){
     const Tetromino *tetromino = TETROMINOS + piece->random_tetromino;

     for (int hang = 0;hang < tetromino->side;++hang){
        for (int cot = 0;cot < tetromino->side;++cot){
            unsigned char value = lay_khoi_Tetromino(tetromino, hang, cot, piece->rotation);
            if (value > 0){
                    //cout<<piece->offset_cot + cot;
                //cout<<*(tetromino+3);
              if (piece->offset_cot + cot < 0){
                    return false;
                }
              if (piece->offset_cot + cot >= rong){
                    return false;
                }
              if (piece->offset_hang + hang < 0){
                    return false;
                }
              if (piece->offset_hang + hang >= cao){
                    return false;
                }
              if (lay_mot_toa_do_trong_ma_tran(board, rong, piece->offset_hang + hang, piece->offset_cot + cot)!=0){
                    return false;
                }
            }
        }
    }
    return true;
}
//lay cac khoi khi da cham dat
void Game:: hop_cac_khoi_lai_voi_nhau(Game *game)
{
    const Tetromino *tetromino = TETROMINOS + game->piece.random_tetromino;
    //i là row và j là col
    for (int i = 0;i < tetromino->side;++i){
        for (int j = 0;j < tetromino->side;++j){
            unsigned char value = lay_khoi_Tetromino(tetromino, i, j, game->piece.rotation);
            if (value!=0)
            {
                int board_i = game->piece.offset_hang + i;
                int board_col = game->piece.offset_cot + j;
                gan_gia_tri_cho_mot_toa_do_trong_ma_tran(game->board, RONG , board_i, board_col, value);
            }
        }
    }
}

//lay khoi Tetromino theo cach xoay(rotation)
 unsigned char Game::lay_khoi_Tetromino(const Tetromino *tetromino, int hang, int cot, int rotation){
    int canhmatran = tetromino->side;
    switch (rotation){
    case 0:
        //giu nguyen
        return tetromino->khoihinh[hang * canhmatran + cot];
        break;
    case 1:
        //xoay 90 do
        return tetromino->khoihinh[(canhmatran - cot - 1) * canhmatran + hang];
        break;
    case 2:
        //xoay 180 do
         return tetromino->khoihinh[(canhmatran - hang - 1) * canhmatran + (canhmatran - cot - 1)];
         break;
    case 3:
        //xoay 270 do
        return tetromino->khoihinh[cot * canhmatran + (canhmatran - hang - 1)];
        break;
    }
    return 0;
}
//lay ve 1 tetromino
unsigned char Game::lay_mot_toa_do_trong_ma_tran(const unsigned char *gia_tri, int rong, int hang, int cot)
{

    return gia_tri[hang * rong +cot];
}
//lay ve 1 tetromino chua gia tri
 void Game::gan_gia_tri_cho_mot_toa_do_trong_ma_tran(unsigned char *gia_tri, int rong, int hang, int cot, unsigned char value){

    gia_tri[hang * rong + cot] = value;
}
//xem hàng đã đầy chưa(check  mọi cột vs hàng đó đầy chưa)
unsigned char Game::xem_dong_da_day_chua(const unsigned char *gia_tri, int rong, int row)
{
    for (int col = 0;col < rong;col++){
        if (!Game::lay_mot_toa_do_trong_ma_tran(gia_tri, rong, row, col))
        {
            return 0;
        }
    }
    return 1;
}
//xem (const hang,cot ) trống ko
 unsigned char Game:: xem_dong_trong_khong(const unsigned char *gia_tri, int rong, int row){
    for (int col = 0;col < rong;++col){
        if (Game::lay_mot_toa_do_trong_ma_tran(gia_tri, rong, row, col)){
            return 0;
        }
    }
    return 1;
}
//nếu hàng đó đầy thì lines sẽ +1 nếu ko thì +0
int Game::find_lines(const unsigned char *gia_tri, int rong, int height, unsigned char *lines_out){
    int count = 0;
    for (int row = 0;row < height;++row){
        unsigned char filled = Game::xem_dong_da_day_chua(gia_tri, rong, row);
        lines_out[row] = filled;
        count += filled;
    }
    //count=10;
    return count;
}
//xoa hàng với dong cho trc
void Game::xoahang(unsigned char *gia_tri, int chieurongboard, int chieucaoboard, const unsigned char *dongcanxoa){
    int hangtamthoi = chieucaoboard - 1;
    for (int i = chieucaoboard - 1;i >= 0;--i){
        while (hangtamthoi >= 0 && dongcanxoa[hangtamthoi]){
            hangtamthoi--;
        }
        if (hangtamthoi < 0){
            memset(gia_tri + i * chieurongboard, 0, chieurongboard);
        }else{
            if (hangtamthoi != i){
                memcpy(gia_tri + i * chieurongboard,gia_tri + hangtamthoi * chieurongboard,chieurongboard);
            }
            hangtamthoi--;
        }
    }
}
//tinh diem theo 1 lan vo dc bao nhieu hang
//4 la max vi max side la 4
int Game::tinh_diem(int level, int so_dong_bi_pha)
{
    switch (so_dong_bi_pha){
    case 1:
        return 10 * (level + 1);
    case 2:
        return 20 * (level + 1);
    case 3:
        return 50 * (level + 1);
    case 4:
        return 100 * (level + 1);
    }
    return 0;
}
//neu an namepace thi den level tiep theo

 void Game::cap_nhat_end_game(Game *game, const Input *dauvao){

    if (dauvao->space_ > 0||dauvao->hidden_>0){
     game->man_hinh = Game::man_hinh_bat_dau;
    }
}

void Game::cap_nhat_cac_dong(Game *game){
    if (game->time >= game->highlight_end_time){
        xoahang(game->board, RONG , CAO, game->lines);
        game->line_break += game->dong_cho;
        game->scores += tinh_diem(game->level, game->dong_cho);

     if (game->line_break >= 10+game->level*10){
            game->level++;
        }
      game->man_hinh = Game::man_hinh_choi;
    }
}
//update màn hình game chơi mơi
bool Game::cap_nhat_game_bat_dau(Game *game, const Input *dauvao)
{
        //cout<<(int)dauvao->da<<" ";
        if (dauvao->space_ > 0||dauvao->hidden_>0){

        //cho 0 cho tat ca cac so trong man
        memset(game->board, 0, RONG *CAO);
        //
        game->level = 0;
        game->line_break = 0;
        game->scores = 0;
         //lay khoi va toc do roi cua khoi
        khoi_tao_toc_do_va_toa_do_khoi(game);
        game->man_hinh = man_hinh_choi;
    }
    if (dauvao->hidden_>0){
            //cout<<dauvao->ha<<"-";
        return true;
    }
    return false;

}
//moi khi nhap vao thi se chuyen dong tetremino
void Game::cap_nhat_luc_choi(Game *game,const Input *dauvao){
    Piece piece = game->piece;
    if (dauvao->trai_ > 0){
           piece.offset_cot--;
    }
    if (dauvao->phai_> 0){
        piece.offset_cot++;
    }
    if (dauvao->len_ > 0){
        piece.rotation = (piece.rotation + 1) % 4;
       // cout<<piece.rotation<<endl;
    }
    if (Game::xem_o_co_con_khong(&piece, game->board,RONG ,CAO)){
        game->piece = piece;
    }
    if (dauvao->xuong_ > 0){
        delay_Tetromino(game);
    }
    if (dauvao->space_ > 0){
        while(delay_Tetromino(game));
    }
    while (game->time >= game->time_next){
        delay_Tetromino(game);
    }
     game->dong_cho = find_lines(game->board,RONG , CAO, game->lines);
    if (game->dong_cho > 0)
    {
        game->man_hinh = man_hinh_thay_doi_line;
        game->highlight_end_time = game->time + 0.5f;
    }
    int game_over_row = 0;
    if (!xem_dong_trong_khong(game->board,RONG , game_over_row)){
          Mix_Chunk *start = NULL;
          start = Mix_LoadWAV( "success.wav" );
          Mix_PlayChannel( -1, start, 0 );
         game->man_hinh = man_hinh_end_game;
    }

}
int demso;
int Game::cap_nhat_game(Game *game,const Input *dauvao){

    switch(game->man_hinh){
    case Game:: man_hinh_bat_dau:

        //cout<< Game::cap_nhat_game_bat_dau(game, dauvao);
        if(Game::cap_nhat_game_bat_dau(game, dauvao)==1){
                demso=1;
            }else{
                demso=0;
            }

            return 1;

        break;
    case Game::man_hinh_choi:
         Game::cap_nhat_luc_choi(game, dauvao);
        break;
    case Game::man_hinh_thay_doi_line:
        Game::cap_nhat_cac_dong(game);
        break;
    case Game::man_hinh_end_game:
         Game:: cap_nhat_end_game(game, dauvao);
        break;
    }
    return 0;
}
//ham khoi tao mau ,toa do va ve
void Game::ve_hinh_voi_toa_do(SDL_Renderer *renderer,int x, int y, int rong, int height, Color color){

    SDL_Rect temp = {};
    temp.x = x;
    temp.y = y;
    temp.w = rong;
    temp.h = height;
    SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, color.t);
    SDL_RenderFillRect(renderer, &temp);
}

//vẽ honhf chiếu lên board
void Game::ve_hinh_chieu(SDL_Renderer *renderer, int x, int y, int rong, int height, Color color){
    SDL_Rect rect = {};
    rect.x = x;
    rect.y = y;
    rect.w = rong;
    rect.h = height;
    SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, color.t);
    SDL_RenderDrawRect(renderer, &rect);
    //SDL_SetRenderDrawColor(renderer,0, 0,0, 0);
    //SDL_RenderDrawPoint(renderer, x * 720 / 2 / 10 + 720 / 2 / 10 / 2,y * 720 / 2 / 10 + 720 / 2 / 10 / 2);
}
//viết chữ lên màn hình
void Game::viet_chu(SDL_Renderer *renderer,TTF_Font *font,const char *text,int x, int y,Game::Vi_tri_ve_chu can_chinh_le,Color color){
    SDL_Color sdl_color = SDL_Color { color.x, color.y, color.z, color.t };
   // https://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, sdl_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect;
    rect.y = y;
    if( texture == NULL ){
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }else{
            //Get image dimensions
           rect.w = surface->w;
           rect.h = surface->h;
        }


    switch (can_chinh_le){
      case Game::Vi_tri_ve_chu_trai:
         rect.x = x;
         break;
     case Game::Vi_tri_ve_chu_giua:
         rect.x = x - surface->w / 2;
         break;
    }
    SDL_RenderCopy(renderer, texture, 0, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Game::ve_khoi_Tetromino(SDL_Renderer *renderer,int hang, int cot, unsigned char value,int toa_do_x, int toa_do_y,bool outline = false){
    Color base_color = mau_chinh[value];
    Color dark_color = mau_den[value];
    int x = cot * DO_PHONG_DAI  + toa_do_x;
    int y = hang * DO_PHONG_DAI  + toa_do_y;
    if (outline){
        ve_hinh_chieu(renderer, x, y, DO_PHONG_DAI , DO_PHONG_DAI , base_color);
        return;
    }
   //ve khoi tetremino theo ngang,doc
    ve_hinh_voi_toa_do(renderer, x, y, DO_PHONG_DAI , DO_PHONG_DAI , dark_color);
    ve_hinh_voi_toa_do(renderer, x + 3, y,DO_PHONG_DAI  - 3, DO_PHONG_DAI  - 3, base_color);
    ve_hinh_voi_toa_do(renderer, x + 3, y + 3,DO_PHONG_DAI  - 3 * 2, DO_PHONG_DAI  - 3 * 2, base_color);
     //ve_hinh_voi_toa_do(renderer, x, y, DO_PHONG_DAI , DO_PHONG_DAI , dark_color);
    //ve_hinh_voi_toa_do(renderer, x + 3, y,DO_PHONG_DAI  - 3, DO_PHONG_DAI  - 3, base_color);
    //ve_hinh_voi_toa_do(renderer, x + 3, y + 3,DO_PHONG_DAI  - 3 * 2, DO_PHONG_DAI  - 3 * 2, base_color);

   // ve_hinh_chieu(renderer, x+350, y+50, DO_PHONG_DAI , DO_PHONG_DAI , base_color);
}
void Game::ve_khoi_Tetromino_mot_lan_duoc_luon(SDL_Renderer *renderer,int hang, int cot, unsigned char value,int toa_do_x, int toa_do_y,bool outline = false){
    Color base_color = mau_chinh[0];
    Color dark_color = mau_den[0];
    int x = cot * DO_PHONG_DAI  + toa_do_x;
    int y = hang * DO_PHONG_DAI  + toa_do_y;


        if (outline){
        ve_hinh_chieu(renderer, x, y, DO_PHONG_DAI , DO_PHONG_DAI , base_color);
        return;
    }
    ve_hinh_voi_toa_do(renderer, x, y, DO_PHONG_DAI , DO_PHONG_DAI , dark_color);
    ve_hinh_voi_toa_do(renderer, x + 3, y,DO_PHONG_DAI  - 3, DO_PHONG_DAI  - 3, base_color);
    ve_hinh_voi_toa_do(renderer, x + 3, y + 3,DO_PHONG_DAI  - 3 * 2, DO_PHONG_DAI  - 3 * 2, base_color);
   //ve khoi tetremino theo ngang,doc

}
//ham lay tetremino sau ve(ham tong cua lay_khoi_Tetromino va ve_khoi_Tetromino)
void Game::draw_piece(SDL_Renderer *renderer,const Piece *piece,int offset_x, int offset_y,bool outline = false){
    const Tetromino *tetromino = TETROMINOS + piece->random_tetromino;

    for (int row = 0;row < tetromino->side;row++){
        for (int col = 0;col < tetromino->side;++col){
            unsigned char value =Game::lay_khoi_Tetromino(tetromino, row, col, piece->rotation);
            //unsigned char current =Game::lay_khoi_Tetromino(tetromino, row, col, 0);

            if (value){
                  // if(demso!=1){
                    //cout<<piece->offset_hang<<endl;

                    //cout<<row + piece->offset_hang<<endl<<col + piece->offset_cot;
                    ve_khoi_Tetromino(renderer,row + piece->offset_hang,col + piece->offset_cot,value,offset_x, offset_y,outline);
                    ve_khoi_Tetromino(renderer,row + 0,col + 5,value,180, 35,outline);
                    //ve_khoi_Tetromino(renderer,piece->offset_hang,piece->offset_cot,value,350, 50,outline);

                    //ve_khoi_Tetromino(renderer,0,50,value,350, 50,outline);
                 //  }
                 }

             }
        //ve_khoi_Tetromino(renderer,row + piece->offset_hang,col + piece->offset_cot,value,offset_x, offset_y,outline);
    }
    const Tetromino *temp = TETROMINOS + piece->random_tetromino_next;

    for (int row = 0;row < temp->side;row++){
        for (int col = 0;col < temp->side;++col){
            unsigned char giatri =Game::lay_khoi_Tetromino(temp, row, col, 0);

            if (giatri){
                  // if(demso!=1){
                    //cout<<piece->offset_hang<<endl;

                    //cout<<row + piece->offset_hang<<endl<<col + piece->offset_cot;
                    //ve_khoi_Tetromino(renderer,row + piece->offset_hang,col + piece->offset_cot,value,offset_x, offset_y,outline);
                   ve_khoi_Tetromino_mot_lan_duoc_luon(renderer,row + 0,col + 5,giatri,180, 200,true);
                    //ve_khoi_Tetromino(renderer,piece->offset_hang,piece->offset_cot,value,350, 50,outline);

                    //ve_khoi_Tetromino(renderer,0,50,value,350, 50,outline);
                 //  }
                 }

             }
        //ve_khoi_Tetromino(renderer,row + piece->offset_hang,col + piece->offset_cot,value,offset_x, offset_y,outline);
    }
}
//tuong tu raw_piece nhung ham nay dung khi choi hidden game

void Game::draw_piecehidden(SDL_Renderer *renderer,const Piece *piece,int offset_x, int offset_y,bool outline = false){
    const Tetromino *tetromino = TETROMINOS + piece->random_tetromino;
    for (int row = 0;row < tetromino->side;row++){
        for (int col = 0;col < tetromino->side;++col){
            unsigned char value =Game::lay_khoi_Tetromino(tetromino, row, col, piece->rotation);
            if (value){
                   if(piece->offset_hang==0){
                    //cout<<piece->offset_hang<<endl;
                  //  ve_khoi_Tetromino(renderer,row + piece->offset_hang,col + piece->offset_cot,value,offset_x, offset_y,outline);

                   }
                   ve_khoi_Tetromino(renderer,row + 0,col + 5,value,180, 35,outline);
            }

        }
    }
    const Tetromino *temp = TETROMINOS + piece->random_tetromino_next;

    for (int row = 0;row < temp->side;row++){
        for (int col = 0;col < temp->side;++col){
            unsigned char giatri =Game::lay_khoi_Tetromino(temp, row, col, 0);

            if (giatri){
                  // if(demso!=1){
                    //cout<<piece->offset_hang<<endl;

                    //cout<<row + piece->offset_hang<<endl<<col + piece->offset_cot;
                    //ve_khoi_Tetromino(renderer,row + piece->offset_hang,col + piece->offset_cot,value,offset_x, offset_y,outline);
                   ve_khoi_Tetromino_mot_lan_duoc_luon(renderer,row + 0,col + 5,giatri,180, 200,true);
                    //ve_khoi_Tetromino(renderer,piece->offset_hang,piece->offset_cot,value,350, 50,outline);

                    //ve_khoi_Tetromino(renderer,0,50,value,350, 50,outline);
                 //  }
                 }

             }
        //ve_khoi_Tetromino(renderer,row + piece->offset_hang,col + piece->offset_cot,value,offset_x, offset_y,outline);
    }
}
//ve hinh ben duoi
void Game::draw_board(SDL_Renderer *renderer,const unsigned char *board, int rong, int height,int offset_x, int offset_y){
    //ve hinh nen
    ve_hinh_voi_toa_do(renderer, offset_x, offset_y,300, 660 ,mau_chinh[0]);
    Game temp;
    for (int row = 0;row < height;++row){
        for (int col = 0;col < rong;col++){

            unsigned char gia_tri = temp.lay_mot_toa_do_trong_ma_tran(board, rong, row, col);
            //cout<<giatri<<endl;
            if (gia_tri){
                    if(demso!=1)
               temp.ve_khoi_Tetromino(renderer, row, col, gia_tri, offset_x, offset_y);
            }
        }
    }
}
//choi game nhin dc hay ko
//ve len board
void Game::render_gamehidden(Game *game,SDL_Renderer *renderer,TTF_Font *font){
    //Color dark_color = mau_den[0];
     char bo_dem[400];
      int offset_y = 60;
     //cout<<demso;
     //ve board va mau cia board
     Game::draw_board(renderer, game->board,RONG ,CAO, 0, offset_y);
     Game temp;
     if (game->man_hinh == Game::man_hinh_choi  ){
            //ve hinh that
            //cout<<(int)input->da<<endl;
            if(demso!=0){
       temp.draw_piecehidden(renderer, &game->piece, 0, offset_y);
            }else{
               temp.draw_piece(renderer, &game->piece, 0, offset_y);

            }
        Piece piece = game->piece;
        while (xem_o_co_con_khong(&piece, game->board,RONG ,CAO)){
            piece.offset_hang++;
        }
        piece.offset_hang--;
        if(demso==0){
        Game::draw_piece(renderer, &piece, 0, offset_y, true);
       }
     }
   if (game->man_hinh == man_hinh_thay_doi_line){
        for (int row = 0;row < CAO;++row){
            if (game->lines[row]){
                int x = 0;
                int y = row * DO_PHONG_DAI  + offset_y;
                Mix_Chunk *clear = NULL;
                clear = Mix_LoadWAV( "clear.wav" );
                Mix_PlayChannel( -1, clear, 0 );


              //xoa mau hang
              //cho them nhac doan nay ne
               ve_hinh_voi_toa_do(renderer, x, y,RONG  * DO_PHONG_DAI , DO_PHONG_DAI , mau_den[0]);

            }

        }
    }else if (game->man_hinh == man_hinh_end_game){
        int x = RONG  * DO_PHONG_DAI  / 2;
        int y = (CAO * DO_PHONG_DAI  + offset_y) / 2;
        if(game->scores>200){
           viet_chu(renderer, font, "YOU WIN",x, y, Vi_tri_ve_chu_giua,mau_chinh[1]);
        }else{
           viet_chu(renderer, font, "GAME OVER",x, y, Vi_tri_ve_chu_giua,mau_chinh[1]);
        }
    }else if (game->man_hinh == man_hinh_bat_dau){
        int x = RONG  * DO_PHONG_DAI /2;
        int y = (CAO * DO_PHONG_DAI  + offset_y) / 2;
        viet_chu(renderer, font, "PRESS SPACE:NORMAL GAME",x, y, Vi_tri_ve_chu_giua, mau_chinh[5]);
        viet_chu(renderer, font, "PRESS H:HIDDEN GAME",x, y+30, Vi_tri_ve_chu_giua, mau_chinh[5]);

        snprintf(bo_dem, sizeof(bo_dem), "YOUR SCORE: %d", game->scores);
        viet_chu(renderer, font, bo_dem,x, y + 60, Vi_tri_ve_chu_giua, mau_chinh[5]);
    }

    ve_hinh_voi_toa_do(renderer,0, offset_y,RONG  * DO_PHONG_DAI , 60,color(0x00, 0x00, 0x00, 0x00));
   // ve_hinh_voi_toa_do(renderer,0, 200,36*4*3, 72*4*2,color(0x00, 0x00, 0x00, 0x00));
   //http://www.cplusplus.com/reference/cstdio/snprintf/
    snprintf(bo_dem, sizeof(bo_dem), "SPEED LEVEL: %d", game->level);
    viet_chu(renderer, font, bo_dem, 5, 5, Vi_tri_ve_chu_trai, mau_chinh[7]);
    snprintf(bo_dem, sizeof(bo_dem), "LINES BREAK: %d",(int) game->line_break);
    viet_chu(renderer, font, bo_dem, 5, 35, Vi_tri_ve_chu_trai,  mau_chinh[7]);
    snprintf(bo_dem, sizeof(bo_dem), "YOUR SCORES: %d", game->scores);
    viet_chu(renderer, font, bo_dem, 5, 65, Vi_tri_ve_chu_trai,  mau_chinh[7]);
    snprintf(bo_dem, sizeof(bo_dem), "TIMES: %d",(int) game->time);
    viet_chu(renderer, font, bo_dem, 5, 95, Vi_tri_ve_chu_trai,  mau_chinh[0]);
    viet_chu(renderer, font, "HOLD TETROMINO",320, 10, Vi_tri_ve_chu_trai, mau_chinh[0]);
    viet_chu(renderer, font, "NEXT SHAPE",320, 150, Vi_tri_ve_chu_trai, mau_chinh[0]);
    viet_chu(renderer, font, "Esc:EXIT GAME",310, 300, Vi_tri_ve_chu_trai, mau_chinh[0]);
    viet_chu(renderer, font, "d:DISABLE MUSIC",310, 350, Vi_tri_ve_chu_trai, mau_chinh[0]);
    viet_chu(renderer, font, "r:RESUME MUSIC",310, 400, Vi_tri_ve_chu_trai, mau_chinh[0]);
    viet_chu(renderer, font, "space:FREE FALL",310, 450, Vi_tri_ve_chu_trai, mau_chinh[0]);
    viet_chu(renderer, font, "<-:MOVE LEFT",310, 500, Vi_tri_ve_chu_trai, mau_chinh[0]);
    viet_chu(renderer, font, "->:MOVE RIGHT",310, 550, Vi_tri_ve_chu_trai, mau_chinh[0]);
    viet_chu(renderer, font, "|:MOVE DOWN",310, 600, Vi_tri_ve_chu_trai, mau_chinh[0]);
    viet_chu(renderer, font, "V",310, 610, Vi_tri_ve_chu_trai, mau_chinh[0]);
    //không hiểu sao font dracula phair /// ms dc 1 /
    //trong c++ thì \\ ms dc 1
    viet_chu(renderer, font, "/\\:ROTATE",310, 650, Vi_tri_ve_chu_trai, mau_chinh[0]);
    viet_chu(renderer, font, "|",310, 660, Vi_tri_ve_chu_trai, mau_chinh[0]);
    //viet_chu(renderer, font, "d:disable sound",500, 600, Vi_tri_ve_chu_giua, mau_chinh[0]);
}
//xoa
void Close(TTF_Font *font,SDL_Renderer *renderer){
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

}
int Game::game(){
    Mix_Music *gMusic = nullptr;
    int event;

    const unsigned char *currentKeyStates = SDL_GetKeyboardState(&event);
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        return 0;
    }
    if (TTF_Init() < 0){
        return 0;
    }
    SDL_Window *window = SDL_CreateWindow("Classic Tetris",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,500,720,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if( window == nullptr ){
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			//success = false;
		}

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED );
    if( renderer == nullptr ){
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				//success = false;
        }
    if( Mix_OpenAudio( 24100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					//success = false;
				}
     gMusic = Mix_LoadMUS( "tetris.ogg" );
            Mix_PlayMusic( gMusic, -1 );
            Mix_VolumeMusic(MIX_MAX_VOLUME/10);
      Mix_Chunk *gLow = NULL;
      gLow = Mix_LoadWAV( "low.wav" );
      const char *font_name = "dracula.ttf";
      TTF_Font *font = TTF_OpenFont(font_name, 24);

    Game game = {};
    Input dauvao = {};

    Game::khoi_tao_toc_do_va_toa_do_khoi(&game);
    bool quit = false;
    while (!quit)
    {
        game.time = SDL_GetTicks()/ 1000.0f;

        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
      if (e.type == SDL_QUIT)
            {
                quit = true;
            }else if( e.type == SDL_KEYDOWN )

						switch( e.key.keysym.sym )
						{
                         case SDLK_d:
                            Mix_PauseMusic();
                            break;
                         case SDLK_r:
                            Mix_ResumeMusic();
                            break;
                         case SDLK_LEFT:
                         case SDLK_RIGHT:
                         case SDLK_UP:
                         case SDLK_DOWN:
                         case SDLK_h:
                         case SDLK_SPACE:
                             {
                                 Mix_PlayChannel( -1, gLow, 0 );

                                 break;
                             }



                    }

            }

       if (currentKeyStates[SDL_SCANCODE_ESCAPE]){
            quit = true;
        }
        Input temp = dauvao;
        //https://lazyfoo.net/tutorials/SDL/18_key_states/index.php
        dauvao.trai = currentKeyStates[SDL_SCANCODE_LEFT];
        dauvao.phai = currentKeyStates[SDL_SCANCODE_RIGHT];
        dauvao.len = currentKeyStates[SDL_SCANCODE_UP];
        dauvao.xuong = currentKeyStates[SDL_SCANCODE_DOWN];
        dauvao.space = currentKeyStates[SDL_SCANCODE_SPACE];
        dauvao.hidden = currentKeyStates[SDL_SCANCODE_H];
        dauvao.trai_ = currentKeyStates[SDL_SCANCODE_LEFT] - temp.trai;
        dauvao.phai_ = currentKeyStates[SDL_SCANCODE_RIGHT] - temp.phai;
        dauvao.len_ = currentKeyStates[SDL_SCANCODE_UP] - temp.len;
        dauvao.xuong_ = currentKeyStates[SDL_SCANCODE_DOWN] - temp.xuong;
        dauvao.space_ = currentKeyStates[SDL_SCANCODE_SPACE] - temp.space;
        dauvao.hidden_ = currentKeyStates[SDL_SCANCODE_H]- temp.hidden;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        cap_nhat_game(&game, &dauvao);
        render_gamehidden(&game, renderer, font);
        SDL_RenderPresent(renderer);

     }
    Close(font,renderer);
    Mix_FreeChunk( gLow );

    return 0;


}





