//*********************************************
// TRIOPS USER INTERFACE LIBRARY
// CREATED BY ALEJANDRO MARTINEZ MANZANO - TRIOPS STUDIOS
//
// 2025
//*********************************************

#ifndef TUIL_H
#define TUIL_H

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>
#include <vector>


#define VIDEO SDL_INIT_VIDEO
#define AUDIO SDL_INIT_AUDIO
#define TIMER SDL_INIT_TIMER
#define EVENTS SDL_INIT_EVENTS
#define EVERYTHING VIDEO|AUDIO|TIMER|EVENTS

#define ROJO 0
#define VERDE 1
#define AZUL 2
#define CIAN 3
#define ROSA 4
#define GRIS 5
#define MORADO 6
#define ROJOH 7
#define VERDEH 8
#define AZULH 9
#define CIANH 10
#define ROSAH 11
#define GRISH 12
#define MORADOH 13

#define DEBUG std::cout<<
#define END <<std::endl;


class TUIHandler {
public:
    TUIHandler();
    ~TUIHandler();

    int InicializarSistemas(Uint32, bool);
    SDL_Window* CrearVentana(std::string, int, int, int, int, Uint32);
    void DestruirVentana(SDL_Window* ventana);
    SDL_Surface* CrearSurface(SDL_Window*);
    SDL_Renderer* CrearRenderer(SDL_Window*, Uint32);
    void RefrescarRender(SDL_Renderer* renderer);
    void ObtenerNombreUsuario (std::string* _nombreUsuario);
    void SetIcono(SDL_Window* _ventana, std::string ruta);
   

    int FuncionDebugVector(); //Eliminar

    TTF_Font* CargarFuente(std::string ruta, int tamaño);
    static SDL_Color GetColor(int indice);

private:
    static const std::vector<SDL_Color> colores;
    

  




};

#endif 
