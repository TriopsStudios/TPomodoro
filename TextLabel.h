#ifndef TEXTLABEL_H
#define TEXTLABEL_H


#include "Control.h"
#include <string>
class TextLabel : public Control
    
{
public:
    
    TextLabel(int _x, int _y, int _acnho, int _alto);
    ~TextLabel();
    void DibujarTexto(std::string mensaje, TTF_Font* fuente, int color, SDL_Renderer* render, bool borde);

private:

    std::string texto;
    SDL_Rect* rectBorde;


};

#endif
