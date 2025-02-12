#pragma once
#include "Control.h"
class Imagen : public Control
{

public:
	Imagen(int _x, int _y, int _ancho, int _alto);
	void CargarTextura(std::string ruta, SDL_Renderer* render);
	void MostrarTextura(SDL_Renderer* render, int alpha, bool borde);
	

private:
	SDL_Texture* textura = nullptr;




};

