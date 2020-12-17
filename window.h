#pragma once

#include <string>
#include <SDL2\SDL.h>

class Window{
public:
    Window(const std::string &title, int width, int height);
    ~Window();

    void poolEvents();
    void StartWindow();
    void clear() const;
    void Draw() const;
    void Axis() const;
    void Line(int xi, int yi, int xf, int yf) const;
    void Circumference(int r) const;
    void Ellipse(int a, int b) const;
    void Parabola(int p) const;
    void Hyperbola(int a, int b) const;

    inline bool isClosed() const {return _closed; } //inline make function efficients.

private:
    bool init();

private:
    std::string _title;
    int _width = 800;
    int _height = 800;
    int xAxis = _width / 2;
    int yAxis = _height / 2;
    bool _closed = false;

    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
};