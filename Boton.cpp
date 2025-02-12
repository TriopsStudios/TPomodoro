#include "Boton.h"

Boton::Boton(int _x, int _y, int _ancho, int _alto, int color)
{


	setPosX(_x);
	setPosY(_y);
	setAncho(_ancho);
	SetAlto(_alto);
	colorInicial = color;
	SetColorN(colorInicial);
	
	texto = "undefined";
	rectangulo = new SDL_Rect { getPosX(), getPosY(), getAncho(), getAlto() };
	
}

Boton::Boton(int _x, int _y, int _ancho, int _alto, int _color, int colorTexto, std::string _texto)
{
	setPosX(_x);
	setPosY(_y);
	setAncho(_ancho);
	SetAlto(_alto);
	colorInicial = _color;
	colorN = _color;
	
	color->r = TUIHandler::GetColor(colorN).r;
	
	color->g = TUIHandler::GetColor(colorN).g;

	color->b = TUIHandler::GetColor(colorN).b;

	color->a = TUIHandler::GetColor(colorN).a;

	colorInicialTexto = colorTexto;

	texto = _texto;
	SetColorN(colorInicial);
	rectangulo = new SDL_Rect{ getPosX(), getPosY(), getAncho(), getAlto() };
}

void Boton::Dibujar(SDL_Renderer* render)
{

	SDL_SetRenderDrawColor(render, color->r, color->g,color->b, 255);
	
		SDL_RenderFillRect(render, rectangulo);
	



}

void Boton::Dibujar(SDL_Renderer* render, TTF_Font* fuente)
{

	/*rectangulo->x = getPosX();
	rectangulo->y = getPosY();
	rectangulo->w = getAncho();
	rectangulo->h = getAlto();*/
	Boton::Dibujar(render);
	
	SDL_Color colorUso = { 0,0,0,0 };
	
	switch (colorInicialTexto) {
	case ROJO:
		colorUso = TUIHandler::GetColor(ROJO);
		break;
	case AZUL:
		colorUso = TUIHandler::GetColor(AZUL);
		break;
	case VERDE:
		colorUso = TUIHandler::GetColor(VERDE);
		break;
	case CIAN:
		colorUso = TUIHandler::GetColor(CIAN);
		break;
	case ROSA:
		colorUso = TUIHandler::GetColor(ROSA);
		break;
	case GRIS:
		colorUso = TUIHandler::GetColor(GRIS);
		break;
	case MORADO:
		colorUso = TUIHandler::GetColor(MORADO);;
		break;
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid(fuente, texto.c_str(), colorUso);

	if (!textSurface) {
		std::cerr << "Error al crear la superficie de texto en funcion Dibujar() de la clase boton): " << TTF_GetError() << std::endl;
		TTF_CloseFont(fuente);
	}
	
	SDL_Rect textRect;
	
	textRect.w = getAncho()/1.5; // Ancho del texto
	textRect.h = getAlto()/1.5; // Altura del texto
	textRect.x = getPosX() + (getAncho()  / 6); // Posición X
	textRect.y = getPosY() + (getAlto() / 3); // Posición Y





	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(render, textSurface);
	SDL_FreeSurface(textSurface);
	if (!textTexture) {
		std::cerr << "Error al crear la textura de texto: en ImprimirTexto() " << SDL_GetError() << std::endl;
		TTF_CloseFont(fuente);
	}

	SDL_RenderCopy(render, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);

	
}

void Boton::Dibujar(SDL_Renderer* render,SDL_Color* color)
{
	
	SDL_SetRenderDrawColor(render, color->r, color->g, color->b, color->a);
	
		SDL_RenderFillRect(render, rectangulo);
	
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	



}

void Boton::Dibujar(SDL_Renderer* render, int colorTextoH, TTF_Font* fuente)
{
	rectangulo->x = getPosX();
	rectangulo->y = getPosY();
	rectangulo->w = getAncho();
	rectangulo->h = getAlto();
	SDL_Color* colorBotonH = new SDL_Color;
	
	
	switch (colorInicial) {
	case ROJO:
		*colorBotonH = TUIHandler::GetColor(ROJOH);
		break;
	case AZUL:
		*colorBotonH = TUIHandler::GetColor(AZULH);
		break;
	case VERDE:
		*colorBotonH = TUIHandler::GetColor(VERDEH);
		break;
	case CIAN:
		*colorBotonH = TUIHandler::GetColor(CIANH);;
		break;
	case ROSA:
		*colorBotonH = TUIHandler::GetColor(ROSAH);
		break;
	case GRIS:
		*colorBotonH = TUIHandler::GetColor(GRISH);
		break;
	case MORADO:
		*colorBotonH = TUIHandler::GetColor(MORADOH);
		break;
	default:
		*colorBotonH = TUIHandler::GetColor(ROJOH);
		break;
	}
	
	Boton::Dibujar(render, colorBotonH);
	delete colorBotonH;




	SDL_Color colorUso = { 0,0,0,0 };
	switch (colorTextoH) {
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

	SDL_Surface* textSurface = TTF_RenderText_Solid(fuente, texto.c_str(), colorUso);

	if (!textSurface) {
		std::cerr << "Error al crear la superficie de texto en funcion ImprimirTexto(): " << TTF_GetError() << std::endl;
		TTF_CloseFont(fuente);
	}

	SDL_Rect textRect;
	textRect.w = getAncho() / 1.5; // Ancho del texto
	textRect.h = getAlto() / 1.5; // Altura del texto
	textRect.x = getPosX() + (getAncho() / 6); // Posición X
	textRect.y = getPosY() + (getAlto() / 3); // Posición Y





	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(render, textSurface);
	SDL_FreeSurface(textSurface);
	if (!textTexture) {
		std::cerr << "Error al crear la textura de texto: en ImprimirTexto() " << SDL_GetError() << std::endl;
		TTF_CloseFont(fuente);
	}

	SDL_RenderCopy(render, textTexture, NULL, &textRect);
	SDL_DestroyTexture(textTexture);
}

void Boton::Highlight(int color, SDL_Renderer* render)
{
		//Boton::Dibujar(render, color);
	


}

void Boton::Higlight()
{
	SDL_Color* colorBotonHighlight = new SDL_Color;



	switch (colorInicial) {
	case ROJO:
		*colorBotonHighlight = TUIHandler::GetColor(ROJOH);
		break;
	case AZUL:
		*colorBotonHighlight = TUIHandler::GetColor(AZULH);
		break;
	case VERDE:
		*colorBotonHighlight = TUIHandler::GetColor(VERDEH);
		break;
	case CIAN:
		*colorBotonHighlight = TUIHandler::GetColor(CIANH);;
		break;
	case ROSA:
		*colorBotonHighlight = TUIHandler::GetColor(ROSAH);
		break;
	case GRIS:
		*colorBotonHighlight = TUIHandler::GetColor(GRISH);
		break;
	case MORADO:
		*colorBotonHighlight = TUIHandler::GetColor(MORADOH);
		break;
	default:
		*colorBotonHighlight = TUIHandler::GetColor(ROJOH);
		break;
	}
	color->r = colorBotonHighlight->r;
	color->g = colorBotonHighlight->g;
	color->b = colorBotonHighlight->b;
	color->a = colorBotonHighlight->a;

}

void Boton::Highlight( int colorTextoH, SDL_Renderer* render, TTF_Font* fuente)
{
	
	Boton::Dibujar(render, colorTextoH, fuente);
	
}

void Boton::Unhighglith(SDL_Renderer* render, TTF_Font* fuente)
{
	
	SDL_Color* colorBotonH = new SDL_Color;
	if (fuente == NULL) {
		
		switch (colorInicial) {
		case ROJO:
			SDL_SetRenderDrawColor(render, 255, 0, 0, 255);

			break;
		case AZUL:
			SDL_SetRenderDrawColor(render, 0, 0, 255, 255);

			break;
		case VERDE:
			SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
			break;
		case CIAN:
			SDL_SetRenderDrawColor(render, 0, 255, 255, 255);
			break;
		case ROSA:
			SDL_SetRenderDrawColor(render, 255, 192, 128, 255);
			break;
		case GRIS:
			SDL_SetRenderDrawColor(render, 128, 128, 128, 255);
			break;
		case MORADO:
			SDL_SetRenderDrawColor(render, 128, 0, 128, 255);
			break;
		}
		SDL_RenderFillRect(render, rectangulo);
	

	
	}
	else {
	
		switch (colorInicial) {


		case ROJO:
			*colorBotonH = TUIHandler::GetColor(ROJO);
			break;
		case AZUL:
			*colorBotonH = TUIHandler::GetColor(AZUL);
			break;
		case VERDE:
			*colorBotonH = TUIHandler::GetColor(VERDE);
			break;
		case CIAN:
			*colorBotonH = TUIHandler::GetColor(CIAN);;
			break;
		case ROSA:
			*colorBotonH = TUIHandler::GetColor(ROSA);
			break;
		case GRIS:
			*colorBotonH = TUIHandler::GetColor(GRIS);
			break;
		case MORADO:
			*colorBotonH = TUIHandler::GetColor(MORADO);
			break;
		default:
			*colorBotonH = TUIHandler::GetColor(GRIS);
			break;
		}

	}
			Boton::Dibujar(render, colorBotonH);
			delete colorBotonH;
			SDL_Color colorUso = { 0,0,0,0 };
			switch (colorInicialTexto) {
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

			SDL_Surface* textSurface = TTF_RenderText_Solid(fuente, texto.c_str(), colorUso);

			if (!textSurface) {
				std::cerr << "Error al crear la superficie de texto en funcion ImprimirTexto(): " << TTF_GetError() << std::endl;
				TTF_CloseFont(fuente);
			}

			SDL_Rect textRect;
			textRect.w = getAncho() / 1.5; // Ancho del texto
			textRect.h = getAlto() / 1.5; // Altura del texto
			textRect.x = getPosX() + (getAncho() / 6); // Posición X
			textRect.y = getPosY() + (getAlto() / 3); // Posición Y





			SDL_Texture* textTexture = SDL_CreateTextureFromSurface(render, textSurface);
			SDL_FreeSurface(textSurface);
			if (!textTexture) {
				std::cerr << "Error al crear la textura de texto: en ImprimirTexto() " << SDL_GetError() << std::endl;
				TTF_CloseFont(fuente);
			}

			SDL_RenderCopy(render, textTexture, NULL, &textRect);
			SDL_DestroyTexture(textTexture);
}

void Boton::SetTexto(std::string _textoNuevo)
{
	texto = _textoNuevo;

}

void Boton::esPulsableSet(bool opcion)
{
	esPulsableVar = opcion;

}

bool Boton::esPulsable()
{
	
	return esPulsableVar;
}




std::string Boton::GetTexto()
{
	return texto;
}

bool Boton::isHigh()
{
	return high;
}

void Boton::setHigh(bool sethigh)
{
	high = sethigh;
	
}


