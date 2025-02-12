#pragma once
#include "Control.h"
class Rectangulo : public Control
{
public:
    Rectangulo(int _x, int _y, int _ancho, int _alto);
    ~Rectangulo();
   
    void Dibujar(SDL_Renderer* render, bool borde);
    void SetColor(int _color);

private:
    int colorN;
    SDL_Color* color = new SDL_Color();
    int colorInicial;
    int colorInicialTexto;
    SDL_Rect* rect = new SDL_Rect();
};

