#include "Control.h"

Control::Control() {
	posX = 0;
	posY = 0;
	alto = 0;
	ancho = 0;
	
}
	



Control::~Control()
{
}




void Control::ResizeAlto(int x)
{
	if (x == 0) {
		ancho = alto + 40;
	}
	else if (x == 1) {
		ancho = alto - 40;
	}
}

void Control::DibujarBorde(SDL_Renderer* render)
{
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderFillRect(render, rectanguloBorde);
}

void Control::Dibujar(SDL_Renderer* render)
{
}

void Control::Dibujar(SDL_Renderer* render, TTF_Font* fuente)
{
}

void Control::ResizeAncho(int x)
{

	if (x == 0) {
		ancho = ancho + 40;
	}
	else if (x == 1) {
		ancho = ancho - 40;
	}
	
}

int Control::getPosX()
{
	return posX;
}

int Control::getPosY()
{
	return posY;
}

int Control::getPosX1()
{
	posX1 = posX + ancho;
	return posX1;
}

int Control::getPosY1()
{
	posY1 = posY + alto;
	return posY1;
}

int Control::getAncho()
{
	return ancho;
}

int Control::getAlto()
{
	return alto;
}

int Control::getColorN()
{
	
	return colorN;
}



void Control::setPosX(int _x)
{
	posX = _x;
}

void Control::setPosY(int _y)
{
	posY = _y;
}

void Control::setAncho(int _ancho)
{
	ancho = _ancho;
}

void Control::SetAlto(int _alto)
{
	alto = _alto;
}

void Control::SetRectanguloBorde()
{
	rectanguloBorde = new SDL_Rect{ getPosX()+5, getPosY()+1 , getAncho(), getAlto() };
}

void Control::SetColorN(int _color)
{
	colorN = _color;
}
