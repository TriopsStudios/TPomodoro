#ifndef CONTROL_H

#define CONTROL_H

#include "TUIL.h"

class Control
{
public:

	Control();
	~Control();


	virtual void Dibujar(SDL_Renderer* render);
	virtual void Dibujar(SDL_Renderer* render, TTF_Font* fuente); //Dibujar con texto
	
	void ResizeAncho(int x);
	void ResizeAlto(int x);
	void DibujarBorde(SDL_Renderer* render);
	

	int getPosX();
	int getPosY();
	int getPosX1();
	int getPosY1();
	int getAncho();
	int getAlto();
	int getColorN();
	//SDL_Color* getColor();

	void setPosX(int _x);
	void setPosY(int _y);
	void setAncho(int _ancho);
	void SetAlto(int _alto);
	void SetRectanguloBorde();
	void SetColorN(int _color);
	SDL_Rect* rectangulo;



private:
	int posX;
	int posY;
	int posX1;
	int posY1;
	int ancho;
	int alto;
	int colorN; //codigon numero
	SDL_Rect* rectanguloBorde;
	//SDL_Color* color;
	



};

#endif