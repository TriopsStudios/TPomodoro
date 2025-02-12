#include "TUIL.h"

 const std::vector<SDL_Color> TUIHandler::colores = {
{ 255, 25, 25, 255 },    // ROJO
{ 25, 255, 25, 255 },    // VERDE
{ 25, 25, 255, 255 },    // AZUL
{ 28, 255, 255, 255 },   // CIAN
{ 255, 210, 218, 255 },  // ROSA
{ 128, 156, 128, 255 },  // GRIS
{ 128, 28, 128, 255 },   // MORADO
{ 255, 145, 145, 255 },    // ROJOH
{ 145, 255, 145, 255 },    // VERDEH
{ 145, 145, 255, 255 },    // AZULH
{ 28, 255, 255, 255 },   // CIANH
{ 255, 210, 218, 255 },  // ROSAH
{ 128, 156, 128, 255 },  // GRISH
{ 128, 28, 128, 255 },   // MORADOH
{ 255, 28, 28, 255 }     // DEFAULT
};



TUIHandler::TUIHandler() {
	
	
}

TUIHandler::~TUIHandler() {
	
}

//IinicializarSistemas. Inicializa los sistemas de SDL que le pasemos y los sistemas PNG y JPG de SDL_Image. Debe ir siempre al principio del programa
int TUIHandler::InicializarSistemas(Uint32 _flags, bool text) {
	
	if (SDL_Init(_flags) < 0) std::cout << "Error in SDL_Init";
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "Error en IMG_init: "<< IMG_GetError()<<std::endl;

	}
	if (text == true) {
		if (TTF_Init() == -1)
		{
			std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError() << std::endl; SDL_Quit();
			return -1;
		}
	}
	
	return 0;
	
}

//CrearVentana. Crea y devuelve una ventana que sera mostrada por defecto. El retorno de la funcion debe ser almacenado en un struct de tipo SDL_Window
SDL_Window* TUIHandler::CrearVentana(std::string _nombreVentana, int _x, int _y, int _w, int _h, Uint32 _flags) {
	SDL_Window* window = SDL_CreateWindow(_nombreVentana.c_str(), _x, _y, _w, _h, _flags);
	if (window == NULL) {
		std::cout << "Error in SDL_CreateWindow: ", SDL_GetError();
	}
	return window;
}

//CrearSurface. Crea una surface en la ventana que elijamos y nos la devuelve. El retorno de la funcion debe ser almacenado en un struc de tipo SDL_Surface. 
//Esta funcion se utiliza para poner la surface principal a una ventana
SDL_Surface* TUIHandler::CrearSurface(SDL_Window* _window) {
	SDL_Surface* surface = SDL_GetWindowSurface(_window);
	return surface;
}

SDL_Renderer* TUIHandler::CrearRenderer(SDL_Window* _window, Uint32 flags)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(_window, -1, flags);
	if (renderer == NULL) {
		std::cout << "ERROR SDL_CreateRenderer: " << SDL_GetError();
	}
	return renderer;
}

void TUIHandler::RefrescarRender(SDL_Renderer* renderer)
{
	SDL_RenderPresent(renderer);
}

void TUIHandler::ObtenerNombreUsuario(std::string* _nombreUsuario)
{
#if defined(_WIN32) || defined(_WIN64)
	char* buffer;
	size_t size = 0;
	_dupenv_s(&buffer, &size, "USERNAME");
	*_nombreUsuario = buffer;

	free(buffer);
#elif defined(__linux__)
	char* buffer;
	size_t size = 0;
	_dupenv_s(&buffer, &size, "USER");
	*username = buffer;
	free(buffer);
#else
	* username = "Unknown";
#endif

}

void TUIHandler::SetIcono(SDL_Window* _ventana, std::string ruta)
{
	SDL_Surface* icono = IMG_Load(ruta.c_str());
	if (!icono) {
		DEBUG "error al crear surface en SetIcono()"<<IMG_GetError() END
	}
	SDL_SetWindowIcon(_ventana, icono);
	SDL_FreeSurface(icono);
}


int TUIHandler::FuncionDebugVector()
{
	return colores.size();
}

TTF_Font* TUIHandler::CargarFuente(std::string ruta, int tamano /*/Tamaño*/)
{
	TTF_Font* font = TTF_OpenFont(ruta.c_str(), tamano);
	if (!font) {
		std::cerr << "Error al abrir la fuente: " << TTF_GetError() << std::endl;
		TTF_Quit();
		//SDL_Quit(); 
	}
	return font;
}

SDL_Color TUIHandler::GetColor(int indice)
{
	
	if (indice >= 0 && indice < colores.size()) {
		
		return colores[indice];
	}
	else {
		DEBUG "Intento de acceso a vector colores fuera del liite" END;
	}

}

void TUIHandler::DestruirVentana(SDL_Window* ventana) {
	SDL_DestroyWindow(ventana);
	ventana = nullptr;
	if (ventana != nullptr) {
		DEBUG "Error al destruir la ventana en funcion Destruir ventana " END
			DEBUG "Puntero ventana: " << ventana END
	
	}
}

