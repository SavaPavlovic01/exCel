#include "../inc/Window.hpp"
#include <iostream>
#include "../inc/csv_parser.hpp"
#include "../inc/csv_lexer.hpp"
#include "../inc/table_struct_visitor.hpp"


bool Window::init(){
    window=SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_SHOWN);
    if(window==nullptr) return false;
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer==nullptr) return false;
    TTF_Init();
    font=TTF_OpenFont("fonts\\FUTRFW.TTF",34);
    draw();
    
    return true;
}

void Window::get_event(SDL_Event& event){
    SDL_WaitEvent(&event);
}

void Window::handle_event(SDL_Event& event){
    switch (event.type)
    {
    case SDL_QUIT:
        quit=true;
        break;
    case SDL_MOUSEBUTTONDOWN:
        handle_mouse(); 
        break;
    case SDL_KEYDOWN:
        handle_keyboard(event);
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
    TTF_CloseFont(font);
    TTF_Quit();
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
        active_cell.y=(first-97)*cell_height;
        //std::cout<<active_cell.x<<" "<<active_cell.y<<std::endl;
        SDL_SetRenderDrawColor(renderer,50,50,50,0xff);
        SDL_RenderFillRect(renderer,&active_cell);
    }

    SDL_SetRenderDrawColor(renderer,0xff,0xff,0xff,0xff);
    std::string active_pos=std::string{first}+std::to_string(second);
    for(auto it:cells){
        Cell* cur_cell=it.second;
        //std::cout<<(int)cur_cell->position[1]<<" "<<(int)cur_cell->position[0]<<std::endl;
        if(cur_cell->type==Cell_type::NUM_CELL || cur_cell->type==Cell_type::STRING_CELL|| cur_cell->position==active_pos){
            int x=(cur_cell->position[1]-48)*cell_width;
            int y=(cur_cell->position[0]-97)*cell_height;
            render_text(cur_cell->content,x,y);
        }else{
            if(!cur_cell->expr_val){
                int x=(cur_cell->position[1]-48)*cell_width;
                int y=(cur_cell->position[0]-97)*cell_height;
                render_text(cur_cell->content,x,y);    
            }else {
                Visitor visitor(cells);
                int error=0;
                int x=(cur_cell->position[1]-48)*cell_width;
                int y=(cur_cell->position[0]-97)*cell_height;
                render_text(std::to_string(cur_cell->get_val(&visitor,error)),x,y);
            }
            
        } 
       
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
    auto it=texture_map.find(text_to_render);
    if(it==texture_map.end()){
        texture_map[text_to_render]=new Texture();
        make_text_texture(text_to_render,x,y);
    }
    else {
        if(!texture_map[text_to_render]->valid) make_text_texture(text_to_render,x,y);
    }

    SDL_Rect rect;
    int text_width=text_to_render.size()*letter_width;
    if(text_width>cell_width) text_width=cell_width;
    rect.h=cell_height;
    rect.w=text_width;
    rect.x=x;
    rect.y=y;
    
    SDL_RenderCopy(renderer,texture_map[text_to_render]->texture,NULL,&rect);
    
    //SDL_DestroyTexture(texture);
}

void Window::make_text_texture(std::string text_to_render,int x,int y){
    SDL_Surface* text_surface=TTF_RenderText_Solid(font,text_to_render.c_str(),{0xff,0xff,0xff,0xff});
    SDL_Texture* texture=SDL_CreateTextureFromSurface(renderer,text_surface);
    SDL_FreeSurface(text_surface);
    
    texture_map[text_to_render]->texture=texture;
    texture_map[text_to_render]->valid=true;
}

void Window::handle_mouse(){
    int windowX,windowY,mouseX,mouseY;
    SDL_GetWindowPosition(window,&windowX,&windowY);
    SDL_GetGlobalMouseState(&mouseX,&mouseY);
    first=abs(windowY-mouseY)/cell_height+97;
    second=abs(windowX-mouseX)/cell_width;
    std::cout<<first<<second<<std::endl;
    draw();
}

void Window::handle_keyboard(SDL_Event& event){
    char clicked;
    clicked=get_char(event);
    std::string cell_pos=std::string{first}+std::to_string(second);
    auto it=cells.find(cell_pos);
    std::cout<<first<<" "<<second<<std::endl;
    std::cout<<cell_pos<<std::endl;
    if(clicked==0) return;
    if(it==cells.end()){
        Cell* cell;
        Parser parser;
        cell=parser.parse_cell(cell_pos,std::string{clicked});
        cells[cell_pos]=cell;
        cells[cell_pos]->content.push_back(clicked);
        draw();
        return;
    }
    it->second->content.push_back(clicked);
    std::cout<<it->second->position<<" "<<it->second->content<<std::endl;
    std::string to_parse=it->second->content;
    Parser parser;
    cells[cell_pos]=parser.parse_cell(cell_pos,to_parse);
    cells[cell_pos]->content=to_parse;
    draw();
}