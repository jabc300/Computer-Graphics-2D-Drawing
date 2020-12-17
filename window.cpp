#include "window.h"
#include <iostream>
#include <math.h>

Window::Window(const std::string &title, int width, int height) :
    _title(title), _width(width), _height(height)
{
    //_closed = !init();
}
Window::~Window(){
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Window::StartWindow(){
    _closed = !init();
}

bool Window::init(){
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        std::cerr << "Failed to initialize SDL.\n";
        return 0;
    }
    _window = SDL_CreateWindow(
        _title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _width, _height,
        0
    );

    if(_window == nullptr){
        std::cerr<<"Failed to create window.\n";
        return 0;
    }

    _renderer = SDL_CreateRenderer(_window,-1,SDL_RENDERER_PRESENTVSYNC);

    if(_renderer == nullptr){
        std::cerr << "Failed to create renderer!";
    }

    return true;
}

void Window::poolEvents(){
    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_QUIT:
                _closed = true;
                break;
            default:
                break;
        }
    }
}

void Window::clear() const{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    //DRAW--------------------
    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
    Axis(); //DRAW AXIS
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
}

void Window::Draw() const{
    SDL_RenderPresent(_renderer);
}

void Window::Axis() const{
    int x=0, y= 0;
    while(x<=_width){
        x++;
        SDL_RenderDrawPoint(_renderer, x, yAxis);
    }
    while(y<=_height){
        y++;
        SDL_RenderDrawPoint(_renderer, xAxis, y);
    }
}

void Window::Line(int x, int y, int xf, int yf) const{
    //Midpoint Algorithm-
    float dx = xf-x;
    float dy = yf-y;

    if(dy<=0){
        int aux = xf;
        xf = x;
        x = aux;
        aux = yf;
        yf = y;
        y = aux;
        dx = -dx;
        dy = -dy;
    }

    SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y); //Initial point
    if(dx==0){
        while(y<yf){
            y++;
            SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y); //90 degrees
        }
        return;
    }else{
        int k1,k2,d;
        float m = dy/dx;
        if((0<=m) && (m<=1)){//Slope less than 1
            k1 = 2*dy;
            k2 = 2*(dy-dx);

            d = k1-dx; //initial d

            while(x<xf){
                if(d<0){ //E
                    d += k1;
                }else{ //NE
                    d += k2;
                    y++;
                }
                x++;
                SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y);//draw points
            }
            return;
        }else if(m>1){//Slope greater than 1
            k1 = 2*dx;
            k2 = 2*(dx-dy);
            d = k1-dy; //Initial d
            while(y<yf){
                if(d<=0){ //N
                    d += k1;
                }else{ //NE
                    d += k2;
                    x++;
                }
                y++;
                SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y);//Draw points
            }
            return;
        }
        else if(-1<=m && m<0){//Slope between -1 and 0

            k1 = -2*dy;
            k2 = -2*(dy+dx);

            d = k1-dx; //Inital d

            while(x>xf){
                if(d>0){ //E
                    d += k1;
                }else{ //NE
                    d += k2;
                    y++;
                }
                x--;
                SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y);//Draw points.
            }
            return;
        }else if(m<-1){// Slope less than -1
            k1 = 2*dx;
            k2 = 2*(dx+dy);
            d = k1+dy; //Initial d
            while(y<yf){
                if(d>0){ //N
                    d += k1;
                }else{ //NE
                    d += k2;
                    x--;
                }
                y++;
                SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y);//Draw points.
            }
            return;
        }
    }
}

void Window::Circumference(int r) const{
    //Second Order Difference Algorithm (Circumference)-
    int x=0,y=r,de,dse,d,rcon;
    SDL_RenderDrawPoint(_renderer, xAxis, yAxis - y);//Initial Point.
    SDL_RenderDrawPoint(_renderer, xAxis, yAxis + y);//Down Point.
    SDL_RenderDrawPoint(_renderer, xAxis - y, yAxis);//Left Point.
    SDL_RenderDrawPoint(_renderer, xAxis + y, yAxis);//Right Point.
    de = 3;
    dse = -2*r + 5;
    d = 1 - r;
    rcon = r/SDL_sqrtf(2);
    while((0<=x)&&(x<=rcon)){
        if(d<=0){ //E
            d += de;
            de += 2;
            dse += 2;
        }else{ //SE
            d += dse;
            de += 2;
            dse += 4;
            y--;
        }
        x++;
        //Print Points.
        SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y);
        SDL_RenderDrawPoint(_renderer, xAxis + y, yAxis - x);
        SDL_RenderDrawPoint(_renderer, xAxis + y, yAxis + x);
        SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis + y);

        SDL_RenderDrawPoint(_renderer, xAxis - x, yAxis + y);
        SDL_RenderDrawPoint(_renderer, xAxis - y, yAxis + x);
        SDL_RenderDrawPoint(_renderer, xAxis - y, yAxis - x);
        SDL_RenderDrawPoint(_renderer, xAxis - x, yAxis - y);   
    }
}

void Window::Ellipse(int a, int b) const{
//MidPoint Algorithm (Ellipse)-
    int x = 0, y = b,ac,bc;
    float d1,d2;
    
    ac=a*a;
    bc=b*b;
    d1 = bc - ac*b + ac*0.25;

    SDL_RenderDrawPoint(_renderer, xAxis, yAxis - y);//Initial Point.
    SDL_RenderDrawPoint(_renderer, xAxis, yAxis + y);//Point Below.
    SDL_RenderDrawPoint(_renderer, xAxis - a, yAxis);//Point Left.
    SDL_RenderDrawPoint(_renderer, xAxis + a, yAxis);//Point Right.

    while((ac*(y-0.5)) > (bc*(x+1)))
    {
        if(d1<0){//E
            d1 += bc*(2*x + 3);
        }else{//SE
            d1 += bc*(2*x + 3) + ac*(-2*y + 2);
            y--;
        }
        x++;
        SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y);//ZONE 1 UPPER RIGHT
        SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis + y);//ZONE 1 LOWER RIGHT
        SDL_RenderDrawPoint(_renderer, xAxis - x, yAxis - y);//ZONE 1 UPPER LEFT
        SDL_RenderDrawPoint(_renderer, xAxis - x, yAxis + y);//ZONE 1 LOWER LEFT
    }
    d2 = bc*(x + 0.5)*(x + 0.5) + ac*(y - 1)*(y - 1) - ac*bc;

    while(y > 0){
        if(d2 < 0){ //SE
            d2 += ac*(-2*y + 3) + bc*(2*x + 2);
            x++;
        }
        else{ //S
            d2 += ac*(-2*y + 3);
        }
        y--;
        SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y);//ZONA 2 UPPER RIGHT
        SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis + y);//ZONA 2 LOWER RIGHT
        SDL_RenderDrawPoint(_renderer, xAxis - x, yAxis - y);//ZONA 2 UPPER LEFT
        SDL_RenderDrawPoint(_renderer, xAxis - x, yAxis + y);//ZONE 2 LOWER LEFT
    }
}

void Window::Parabola(int p) const{
    //MidPoint Algorithm (Parabola)-
    int x = 0, y = 0;
    float d1,d2;
    d1 = 1 - 2*p;
    SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y);//INITIAL POINT
    while(((x+1)<2*p)&&((x<xAxis)&&(y<yAxis))){
        if(d1 < 0){//E
            d1 += 2*x + 3;
        }else{//NE
            d1 += 2*x + -4*p + 3;
            y++;
        }
        x++;
        SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y);//RIGHT POINT
        SDL_RenderDrawPoint(_renderer, xAxis - x, yAxis - y);//LEFT POINT
    }
    d2 = (x + 0.5)*(x + 0.5) - 4*p*(y + 1);
    while((x<xAxis)&&(y<yAxis))
    {
        if(d2 < 0){//NE
            d2 += 2*x - 4*p - 2;
            x++;
        }else{//N
            d2 += -4*p;
        }
        y++;
        SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y);//RIGHT POINT
        SDL_RenderDrawPoint(_renderer, xAxis - x, yAxis - y);//LEFT POINT
    }
}

void Window::Hyperbola(int a, int b) const{
    //MidPoint Algorithm (Hiperbola)-
    int x = 0, y = a,ac,bc;
    float d1,d2;
    
    ac=a*a;
    bc=b*b;
    d1 = bc*(a+0.25) - ac;

    SDL_RenderDrawPoint(_renderer, xAxis, yAxis - y);//Initial Point
    SDL_RenderDrawPoint(_renderer, xAxis, yAxis + y);//Point Below.

    while(((-ac*(x+1)) < (bc*(y+0.5)))&&((x<xAxis)&&(y<yAxis)))
    {
        if(d1>0){//E
            d1 += ac*(-2*x - 3);
        }else{//NE
            d1 += bc*(2*y + 2) - ac*(2*x + 3);
            y++;
        }
        x++;
        SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y);//ZONE 1 UPPER RIGHT
        SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis + y);//ZONE 1 LOWER RIGHT
        SDL_RenderDrawPoint(_renderer, xAxis - x, yAxis - y);//ZONE 1 UPPER LEFT
        SDL_RenderDrawPoint(_renderer, xAxis - x, yAxis + y);//ZONE 1 LOWER LEFT
    }
    d2 = bc*(y + 1)*(y + 1) - ac*(x + 0.5)*(x + 0.5) - ac*bc;

    while((x<xAxis)&&(y<yAxis)){
        if(d2 > 0){ //NE
            d2 += bc*(-2*y + 3) - ac*(2*x + 2);
            x++;
        }
        else{ //S
            d2 += bc*(2*y + 3);
        }
        y++;
        SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis - y);//ZONA 2 UPPER RIGHT
        SDL_RenderDrawPoint(_renderer, xAxis + x, yAxis + y);//ZONA 2 LOWER RIGHT
        SDL_RenderDrawPoint(_renderer, xAxis - x, yAxis - y);//ZONA 2 UPPER LEFT
        SDL_RenderDrawPoint(_renderer, xAxis - x, yAxis + y);//ZONE 2 LOWER LEFT
    }
}

