#include "Imagen.h"
#include <string>

Imagen::Imagen(int _x, int _y, int _ancho, int _alto)
{
	setPosX(_x);
	setPosY(_y);
	setAncho(_ancho);
	SetAlto(_alto);
	SetRectanguloBorde();

}

void Imagen::CargarTextura(std::string ruta, SDL_Renderer* render)
{
	SDL_Surface* image = IMG_Load(ruta.c_str());
	if (image == NULL) {
		std::cout << "ERROR SDL IMAGE en CargarTextura: No se pudo cargar la imagen: " << ruta << " " << IMG_GetError();
		textura = NULL;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, image);
	if (texture == NULL) {
		std::cout << "ERROR en SDL_CreateTextureFromSurface: No se pudo cargar la imagen: " << SDL_GetError() << std::endl;
		textura = NULL;
	}
	
	SDL_FreeSurface(image);
	//DEBUG "textura cargada correctamente" END
	textura = texture;
	SDL_SetTextureBlendMode(textura, SDL_BLENDMODE_BLEND);
}

void Imagen::MostrarTextura(SDL_Renderer* render, int alpha, bool borde)
{

	if (borde == false) {
		//SDL_RenderClear(renderer);
		SDL_Rect renderRect = { getPosX(), getPosY(), getAncho(), getAlto() };

		SDL_SetTextureAlphaMod(textura, alpha);
		//Render texture to screen
		if (SDL_RenderCopy(render, textura, NULL, &renderRect) != 0) {
			std::cout << "Error al mostrar textura en funcion MostrarTextura()" << SDL_GetError() << std::endl;
		}
	}

	if (borde == true) {
		//SDL_RenderClear(renderer);
		SDL_Rect renderRect = { getPosX(), getPosY(), getAncho(), getAlto() };
		DibujarBorde(render);
		SDL_SetTextureAlphaMod(textura, alpha);
		//Render texture to screen
		if (SDL_RenderCopy(render, textura, NULL, &renderRect) != 0) {
			std::cout << "Error al mostrar textura en funcion MostrarTextura()" << SDL_GetError() << std::endl;
		}
		

	}



}

