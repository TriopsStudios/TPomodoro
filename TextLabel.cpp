#include "TextLabel.h"

TextLabel::TextLabel(int _x, int _y, int _ancho, int _alto)
{
	setPosX(_x);
	setPosY(_y);
	setAncho(_ancho);
	SetAlto(_alto);
	rectBorde = new SDL_Rect{ getPosX() + 3, getPosY() + 3, getAncho() + 5, getAlto() + 5 };
}

TextLabel::~TextLabel()
{
}

void TextLabel::DibujarTexto(std::string mensaje, TTF_Font* fuente, int color, SDL_Renderer* render, bool borde)
{
	SDL_Color colorUso = { 0,0,0,0 };
	if (borde) {

		SDL_Surface* textSurfaceBorde = TTF_RenderText_Solid(fuente, mensaje.c_str(), colorUso);
		if (!textSurfaceBorde) {
			std::cerr << "Error al crear la superficie de texto en funcion ImprimirTexto - borde(): " << TTF_GetError() << std::endl;
			TTF_CloseFont(fuente);
		}
		SDL_Texture* textTextureBorde = SDL_CreateTextureFromSurface(render, textSurfaceBorde);
		SDL_FreeSurface(textSurfaceBorde);
		if (!textTextureBorde) {
			std::cerr << "Error al crear la textura de texto: en ImprimirTexto - borde() " << SDL_GetError() << std::endl;
			TTF_CloseFont(fuente);
		}

		SDL_RenderCopy(render, textTextureBorde, NULL, rectBorde);
		SDL_DestroyTexture(textTextureBorde);
	}

	switch (color) {
	case ROJO:
		colorUso = { 255,0,0,255 };
		break;
	case AZUL:
		colorUso = { 0,0,255,255 };
		break;
	case VERDE:
		colorUso = { 0,255,0,255 };
		break;
	case CIAN:
		colorUso = { 0, 255, 255,255 };
		break;
	case ROSA:
		colorUso = { 255, 192, 203,255 };
		break;
	case GRIS:
		colorUso = { 128, 128, 128,255 };
		break;
	case MORADO:
		colorUso = { 128, 0, 128,255 };
		break;
	}
	

	SDL_Surface* textSurface = TTF_RenderText_Solid(fuente, mensaje.c_str(), colorUso);

	if (!textSurface) {
		std::cerr << "Error al crear la superficie de texto en funcion ImprimirTexto(): " << TTF_GetError() << std::endl;
		TTF_CloseFont(fuente);
	}

	SDL_Rect textRect;
	textRect.x = getPosX(); // Posición X
	textRect.y = getPosY(); // Posición Y
	textRect.w = getAncho(); // Ancho del texto
	textRect.h = getAlto(); // Altura del texto





	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(render, textSurface);
	SDL_FreeSurface(textSurface);
	if (!textTexture) {
		std::cerr << "Error al crear la textura de texto: en ImprimirTexto() " << SDL_GetError() << std::endl;
		TTF_CloseFont(fuente);
	}

	SDL_RenderCopy(render, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
}


