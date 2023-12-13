#include "../inc/Window.hpp"
#include <iostream>


bool Window::init(){
    window=SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_SHOWN);
    if(window==nullptr) return false;
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer==nullptr) return false;
    TTF_Init();
    font=TTF_OpenFont("fonts\\FUTRFW.TTF",28);
    draw();
    
    return true;
}

void Window::get_event(SDL_Event& event){
    SDL_WaitEvent(&event);
}

void Window::handle_event(SDL_Event& event){
    int mouseX;
    int mouseY;
    int windowX;
    int windowY;
    std::unordered_map<std::string,Cell*>::iterator it;
    
    switch (event.type)
    {
    case SDL_QUIT:
    
        quit=true;
        break;
    
    case SDL_MOUSEBUTTONDOWN:
        SDL_GetWindowPosition(window,&windowX,&windowY);
        SDL_GetGlobalMouseState(&mouseX,&mouseY);
        first=abs(windowY-mouseY)/cell_height+65;
        second=abs(windowX-mouseX)/cell_width;
        draw();
        //std::cout<<first<<" "<<second<<std::endl;
        break;
    case SDL_KEYDOWN:
        //std::cout<<get_char(event)<<std::endl;
        it=cells.find(std::string{first,static_cast<char>(second+48)});
        std::cout<<first<<" "<<second<<std::endl;
        std::cout<<std::string{first,static_cast<char>(second+48)}<<std::endl;
        if(it==cells.end()){
            cells[std::string{first,static_cast<char>(second+48)}]=new Cell(std::string{first,static_cast<char>(second+48)},"");
            cells[std::string{first,static_cast<char>(second+48)}]->content.push_back(get_char(event));
            //std::cout<<it->second->position<<std::endl;
            draw();
            break;
        }
        it->second->content.push_back(get_char(event));
        std::cout<<it->second->position<<" "<<it->second->content<<std::endl;
        draw();
        //pos=pos
        //cells.find()
        break;
    default:
        break;
    }
    
}

void Window::loop(){
    SDL_Event event;
    while(!quit){
        get_event(event);
        handle_event(event);
    }
}

Window::~Window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::draw(){
    SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xff);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0xff,0xff,0xff,0xff);
    int curX=0;
    while(curX<width){
        curX+=cell_width;
        SDL_RenderDrawLine(renderer,curX,0,curX,height); 
    }
    int curY=0;
    while(curY<height){
        curY+=cell_height;
        SDL_RenderDrawLine(renderer,0,curY,width,curY);
    }
    if(second!=-1){
        SDL_Rect active_cell;
        active_cell.h=cell_height;
        active_cell.w=cell_width;
        active_cell.x=second*cell_width;
        active_cell.y=(first-65)*cell_height;
        //std::cout<<active_cell.x<<" "<<active_cell.y<<std::endl;
        SDL_SetRenderDrawColor(renderer,50,50,50,0xff);
        SDL_RenderFillRect(renderer,&active_cell);
    }

    SDL_SetRenderDrawColor(renderer,0xff,0xff,0xff,0xff);
    for(auto it:cells){
       Cell* cur_cell=it.second;
       std::cout<<(int)cur_cell->position[1]<<" "<<(int)cur_cell->position[0]<<std::endl;
       int x=(cur_cell->position[1]-48)*cell_width;
       int y=(cur_cell->position[0]-65)*cell_height;
       render_text(cur_cell->content,x,y);
    }
    SDL_RenderPresent(renderer);
}
//CHECK Text Input And Clipboard Handling
char Window::get_char(SDL_Event& event){
    auto it=key_map.find(event.key.keysym.sym);
    if(it==key_map.end()) return 0;
    if(it->first==SDLK_0 && (event.key.keysym.mod & KMOD_LSHIFT)==1) return ')';
    if(it->first==SDLK_9 && (event.key.keysym.mod & KMOD_LSHIFT)==1) return '(';
    if(it->first==SDLK_8 && (event.key.keysym.mod & KMOD_LSHIFT)==1) return '*';
    if(it->first==SDLK_EQUALS && (event.key.keysym.mod & KMOD_LSHIFT)==1) return '+';
    return it->second;
}

void Window::render_text(std::string text_to_render,int x,int y){
    SDL_Surface* text_surface=TTF_RenderText_Solid(font,text_to_render.c_str(),{0xff,0xff,0xff,0xff});
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,text_surface);
    SDL_FreeSurface(text_surface);
    SDL_Rect rect;
    rect.h=cell_height;
    rect.w=cell_width;
    rect.x=x;
    rect.y=y;
    
    SDL_RenderCopy(renderer,texture,NULL,&rect);
    
    //SDL_DestroyTexture(texture);
}