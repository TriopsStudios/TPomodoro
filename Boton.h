#pragma once
#include "Control.h"


class Boton : public Control
{

public:
	Boton(int _x, int _y, int _ancho, int _alto,int color);
	Boton(int _x, int _y, int _ancho, int _alto, int _color, int colorTexto, std::string _texto);
	void Dibujar(SDL_Renderer* render) override; //Boton Solo
	void Dibujar(SDL_Renderer* render, TTF_Font* fuente) override; //Boton con texto
	void Dibujar(SDL_Renderer* render, SDL_Color* color); //Esta funcion se usara dentro del la funcion HighgLight
	void Dibujar(SDL_Renderer* render, int colorTextoH, TTF_Font* fuente); //Esta funcion se usara dentro del la funcion HighgLight con texto
	void Highlight(int color, SDL_Renderer* render);
	void Higlight();
	void Highlight( int colorTextoH, SDL_Renderer* render, TTF_Font* fuente); //Sobrecarga Highlight con texto
	void Unhighglith(SDL_Renderer* render, TTF_Font* fuente);
	void SetTexto(std::string _textoNuevo);

	void esPulsableSet(bool opcion);
	bool esPulsable();
	
	std::string GetTexto();
	
	bool isHigh();
	void setHigh(bool sethigh);
private:
	bool high = false;
	int colorN = 0;
	SDL_Color* color = new SDL_Color();
	int colorInicial = 0;
	int colorInicialTexto = 0;
	std::string texto = "";
	bool esPulsableVar = true;
};

