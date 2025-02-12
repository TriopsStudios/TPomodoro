#include "Rectangulo.h"

Rectangulo::Rectangulo(int _x, int _y, int _ancho, int _alto)
{
	setPosX(_x);
	setPosY(_y);
	setAncho(_ancho);
	SetAlto(_alto);

	
	

	
	rectangulo = new SDL_Rect{ getPosX(), getPosY(), getAncho(), getAlto() };

	SetRectanguloBorde();
}

Rectangulo::~Rectangulo()
{

}

void Rectangulo::Dibujar(SDL_Renderer* render, bool borde)
{
	if (borde == true) {
		DibujarBorde(render);
	}
	
	
	SDL_SetRenderDrawColor(render, color->r, color->g, color->b, 255);

	SDL_RenderFillRect(render, rectangulo);

	
}

void Rectangulo::SetColor(int _color)
{

	colorInicial = _color;

	color->r = TUIHandler::GetColor(colorInicial).r;

	color->g = TUIHandler::GetColor(colorInicial).g;

	color->b = TUIHandler::GetColor(colorInicial).b;

	color->a = TUIHandler::GetColor(colorInicial).a;



	SetColorN(colorInicial);

}
