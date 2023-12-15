#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unordered_map>
#include "../inc/Cell.hpp"

class Window{
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool init();

    typedef struct {
        SDL_Texture* texture;
        bool valid;
    } Texture;

    std::unordered_map<std::string,Texture*> texture_map;

    const int width=1000;
    const int height=600;
    const char* title="Excel";
    const int cell_width=200;
    const int cell_height=50;
    const int letter_width=20;
    bool quit=false;
    char first=-1;
    int second=-1;
    TTF_Font* font;

    public:

    const std::unordered_map<int,char> key_map={
        {SDLK_a,'a'},{SDLK_b,'b'},{SDLK_c,'c'},{SDLK_d,'d'},
        {SDLK_e,'e'},{SDLK_f,'f'},{SDLK_g,'g'},{SDLK_h,'h'},
        {SDLK_i,'i'},{SDLK_j,'j'},{SDLK_k,'k'},{SDLK_l,'l'},
        {SDLK_m,'m'},{SDLK_n,'n'},{SDLK_o,'o'},{SDLK_p,'p'},
        {SDLK_q,'q'},{SDLK_r,'r'},{SDLK_s,'s'},{SDLK_t,'t'},
        {SDLK_u,'u'},{SDLK_v,'v'},{SDLK_w,'w'},{SDLK_x,'x'},
        {SDLK_y,'y'},{SDLK_z,'z'},{SDLK_0,'0'},{SDLK_1,'1'},
        {SDLK_2,'2'},{SDLK_3,'3'},{SDLK_4,'4'},{SDLK_5,'5'},
        {SDLK_6,'6'},{SDLK_7,'7'},{SDLK_8,'8'},{SDLK_9,'9'},
        {SDLK_COMMA,','},{SDLK_ASTERISK,'*'},
        {SDLK_SPACE,' '},{SDLK_EXCLAIM,'!'},{SDLK_LEFTPAREN,'('},
        {SDLK_RIGHTPAREN,')'},{SDLK_PLUS,'+'},{SDLK_MINUS,'-'},
        {SDLK_SLASH,'/'},{SDLK_DELETE,(char)0x7f},{SDLK_EQUALS,'='}
    };

    std::unordered_map<std::string,Cell*> cells;

    Window(){if(!init()) std::cout<<"Error"<<std::endl;}

    void get_event(SDL_Event& event);

    void handle_event(SDL_Event& event);

    void loop();

    void draw();

    char get_char(SDL_Event& event);

    void render_text(std::string text_to_render,int x,int y);

    ~Window();

    void make_text_texture(std::string text_to_render,int x,int y);

    void handle_mouse();

    void handle_keyboard(SDL_Event& event);
};

#endif