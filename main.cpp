#include "TUIL.h"
#include "Control.h"
#include "Boton.h"
#include "TextLabel.h"
#include "Imagen.h"
#include <vector>
#include <cmath>
#include "Rectangulo.h"
#include <thread>


TUIHandler uihandler;

std::vector<Boton> vectorBotones;



int anchoVentana = 900;
int altoVentana = 800;
int posXVentana = 20;
int posYVentana = 20;
int* estado = new int; //0 nada, 1 concentrate, 2 descansa
int* ciclo = new int;

SDL_Window* ventana;
SDL_Renderer* render;

TTF_Font* fuente;
TTF_Font* fuenteSecundaria;

int tiempoInicial = 3000; //25 minutos en milisegundos
int minutos = tiempoInicial / 60000;
int segundos = (tiempoInicial % 60000) / 1000;

std::string minutosTexto = "";
std::string segundosTexto = "";


std::string cadenaTextoTiempo = ".";



std::string* CTTP = &cadenaTextoTiempo;//puntero a cadenaTextoTIempo

int tiempoDescansoInicial =3000; //5 minutos en milisegundos
int minutosDescanso = tiempoDescansoInicial / 60000;
int segundosDescanso = (tiempoDescansoInicial % 60000) / 1000;
std::string minutosDescansoTexto = "";
std::string segundosDescansoTexto = "";


std::string cadenaTextoTiempoDescanso = ".";

std::string* CTTD = &cadenaTextoTiempoDescanso;

bool loop = true;
bool timerIniciado = false;

//DECLARACION E INICIALIZACION ELEMENTOS GRAFICOS
Imagen fondoPrincipal(0, 0, anchoVentana, altoVentana);
Imagen panelUno((anchoVentana - (anchoVentana / 1.2)) / 2, anchoVentana / 10, anchoVentana / 1.2, altoVentana / 4);
Imagen panelAbout((anchoVentana-500)/2, (altoVentana-200)/2, 500, 200);
bool* showAbout = new bool;
//*************************************************************************





//DECLARACION E INICIACION TEXTOS
TextLabel titulo((anchoVentana - (anchoVentana / 1.2)) / 2, 0, anchoVentana / 1.2, altoVentana / 10);
TextLabel saludo((anchoVentana - 400) / 2, 120, 400, 40);
TextLabel textoPomodoro((anchoVentana - 400) / 4, 160, 190, 20);
TextLabel textoDescanso((anchoVentana)-(anchoVentana / 3), 160, 190, 20);
TextLabel timerPomodoro((anchoVentana - 400) / 4, 180, 100, 80);
TextLabel timerDescanso((anchoVentana)-(anchoVentana / 3), 180, 100, 80);
TextLabel textoConcentrate(((anchoVentana - 220) / 2), (altoVentana - 150), 220, 100);

std::string* nombreUsuario = new std::string();

//punteros
Boton* botonStartPtr = nullptr;
Boton* botonPararPtr = nullptr;
Boton* botonAboutPtr = nullptr;



//RECTANGULOS
Rectangulo rectUno((anchoVentana-300)/2, altoVentana- 200, 300, 200);

void Redibujar();

void Timer();
void ReiniciarTimer();
void limpiarMierda();

int main(int argc, char* argv[]) {
	
	//DECLARACION E INICIACION VARIABLES LOCALES
	
		*ciclo = 0;
	*showAbout = false;
		uihandler.ObtenerNombreUsuario(nombreUsuario);
	bool* presionandoBoton = new bool();
	*presionandoBoton = false;

	ReiniciarTimer();

	std::thread hiloTemporizador;
	

	//INICIALIZACION COMÚN

	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	bool dragging = false;
	if (uihandler.InicializarSistemas(EVERYTHING, true) != 0) {
	
			return -1;
	}



	ventana = uihandler.CrearVentana("TPomodoro", posXVentana, posYVentana, anchoVentana, altoVentana, SDL_WINDOW_BORDERLESS);
	if (ventana == nullptr) {

	}

	render = uihandler.CrearRenderer(ventana, 0);
	uihandler.SetIcono(ventana, "Images/icono.png");
	fuente = uihandler.CargarFuente("Fonts/upheavtt.ttf", 70);
	fuenteSecundaria = uihandler.CargarFuente("Fonts/kindergarten.ttf", 70);
	//****************************************************************************
	//CREACION BOTONES

	Boton botonStart((anchoVentana - (anchoVentana / 1.2)) / 2, 400, 200, 80, VERDE, AZUL, "Start");

	Boton botonParar(panelUno.getPosX1() - 200, 400, 200, 80, AZUL, VERDE, "Parar");

	Boton botonAbout(0, altoVentana - 50, 100, 50, ROJO, AZUL, "About");

	botonStartPtr = &botonStart;
	botonPararPtr = &botonParar;
	botonAboutPtr = &botonAbout;


	//Botones al vector
	vectorBotones.push_back(botonStart);
	vectorBotones.push_back(botonParar);
	vectorBotones.push_back(botonAbout);


	//INicializacion rectangulos
	rectUno.SetColor(VERDE);


	//CARGA TEXTURA IMAGENES
	fondoPrincipal.CargarTextura("Images/panelUno.png", render);
	panelUno.CargarTextura("Images/panelDos.png", render);
	panelAbout.CargarTextura("Images/panelAbout.png", render);
	//**************************************************************//



	//MOSTRAR TEXTURAS
	fondoPrincipal.MostrarTextura(render, 255, 0);
	panelUno.MostrarTextura(render, 255, true);	
	
	//**************************************************************

	//DIBUJAR BOTONES Y OTROS ELEMENTOS
	botonStart.Dibujar(render, fuente);
	botonParar.Dibujar(render, fuente);
	botonAbout.Dibujar(render, fuente);

	//DIBUJAR TEXTOS
	titulo.DibujarTexto("TPomodoro Timer", fuente, ROJO, render, true);
	saludo.DibujarTexto("Hola, " + *nombreUsuario, fuente, ROJO, render, false);
	textoPomodoro.DibujarTexto("Pomodoro: ", fuente, CIAN, render, false);
	textoDescanso.DibujarTexto("Desncaso: ", fuente, VERDE, render, false);
	timerPomodoro.DibujarTexto(*CTTP, fuente, CIAN, render, true);
	timerDescanso.DibujarTexto(*CTTD, fuente, VERDE, render, true);
	textoConcentrate.DibujarTexto("Concentrate", fuente, CIAN, render, false);

	rectUno.Dibujar(render, true);

	//EVENTOS AQUI
	SDL_Event event;
	while (loop == true) {
		*presionandoBoton = false;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					loop = 0;
					break;
				}
			}
			if (event.type == SDL_QUIT) {
				loop = false;
				break;
			}
			if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					int newWidth = event.window.data1;
					int newHeight = event.window.data2;

					if (newWidth > anchoVentana) {

					}
					if (newWidth < anchoVentana) {

					}
					if (newHeight < altoVentana) {

					}
					if (newHeight > altoVentana) {

					}



				}
				break;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					for (int e = 0; e < vectorBotones.size(); e++) {
						if (mouseX >= vectorBotones[e].getPosX() && mouseX <= vectorBotones[e].getPosX1() && mouseY >= vectorBotones[e].getPosY() && mouseY <= vectorBotones[e].getPosY1()) {//*
						
							if (vectorBotones[e].GetTexto() == "Start" && botonStartPtr->esPulsable() != false) {
							

									if (!timerIniciado) timerIniciado = true;
								botonStart.SetTexto("Corriendo");
								botonStartPtr->esPulsableSet(false);
								 hiloTemporizador = std::thread(Timer);
								 hiloTemporizador.detach();
								 break;

							}

							else if (vectorBotones[e].GetTexto() == "Parar" && vectorBotones[e].esPulsable()) {
								
									botonStart.SetTexto("Start");

								botonStart.esPulsableSet(true);

								timerIniciado = false;
								break;
							}
							else if (vectorBotones[e].GetTexto() == "About" && vectorBotones[e].esPulsable()) {
								
								if (*showAbout) *showAbout = false;
								else if (!*showAbout) *showAbout = true;

								

								
								break;
							}


						}//*
						else {
							dragging = true;
							SDL_GetMouseState(&mouseX, &mouseY);
							SDL_GetWindowPosition(ventana, &posXVentana, &posYVentana);
						}
					}

				}
			}
			if (event.type == SDL_MOUSEBUTTONUP) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					dragging = false;
				}
			}
			if (event.type == SDL_MOUSEMOTION && dragging) {
				int CurrentXMouse, CurrentYMouse;
				int movX, movY;
				SDL_GetMouseState(&CurrentXMouse, &CurrentYMouse);
				movX = CurrentXMouse - mouseX;
				movY = CurrentYMouse - mouseY;

				if (std::abs(movX) > 10 || std::abs(movY) > 10) {

					SDL_SetWindowPosition(ventana, posXVentana + movX + 2, posYVentana + movY + 2);
					SDL_GetWindowPosition(ventana, &posXVentana, &posYVentana);

				}

			}
			else if (event.type == SDL_MOUSEMOTION) {
				 mouseX = event.motion.x;
				 mouseY = event.motion.y;
				for (int e = 0; e < vectorBotones.size(); e++) {
					if (mouseX >= vectorBotones[e].getPosX() && mouseX <= vectorBotones[e].getPosX1() && mouseY >= vectorBotones[e].getPosY() && mouseY <= vectorBotones[e].getPosY1()) {

						if (vectorBotones[e].GetTexto() == "Start" && vectorBotones[e].isHigh() == false) {
							
							botonStartPtr->setHigh(true);
							
								break;

						}
						else if (vectorBotones[e].GetTexto() == "Parar" && vectorBotones[e].isHigh() == false) {
							botonPararPtr->setHigh(true);
							break;
						}
						else if (vectorBotones[e].GetTexto() == "About" && vectorBotones[e].isHigh() == false) {
							botonAboutPtr->setHigh(true);
							break;
						}
					}

					else {

						if (botonStartPtr->isHigh() == true) {
						
								botonStartPtr->setHigh(0);

						}
						if (botonPararPtr->isHigh() == true) {
							botonPararPtr->setHigh(0);
						}
						if (botonAboutPtr->isHigh() == true) {
							botonAboutPtr->setHigh(0);
						}

					}

				}

			}//
			


		}
	
	
		SDL_RenderClear(render);
		
		Redibujar();
		SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
		uihandler.RefrescarRender(render);
		SDL_Delay(5);
	}

	//EVENTOS FINAL









	uihandler.DestruirVentana(ventana);
	
	limpiarMierda();
	SDL_Quit();
	return 0;

}

void ReiniciarTimer()
{
	
	tiempoInicial = 1500000;
	

	if (*ciclo % 4 == 0 && *ciclo != 0) {
		tiempoDescansoInicial = 900000;
	}
	else tiempoDescansoInicial = 300000;
	
	minutos = tiempoInicial / 60000;
	segundos = (tiempoInicial % 60000) / 1000;
	minutosDescanso = tiempoDescansoInicial / 60000;
	segundosDescanso = (tiempoDescansoInicial % 60000) / 1000;
	//Crear la cadena con minutos y segundos
	minutosTexto = std::to_string(minutos);
	segundosTexto = std::to_string(segundos);

	// Asegurarse de que los segundos tengan siempre dos dígitos
	if (segundos < 10) {
		segundosTexto = "0" + segundosTexto;
	}

	*CTTP = minutosTexto + ":" + segundosTexto;



	//Crear la cadena con minutos y segundos
	minutosDescansoTexto = std::to_string(minutosDescanso);
	segundosDescansoTexto = std::to_string(segundosDescanso);

	// Asegurarse de que los segundos tengan siempre dos dígitos
	if (segundosDescanso < 10) {
		segundosDescansoTexto = "0" + segundosDescansoTexto;
	}

	*CTTD = minutosDescansoTexto + ":" + segundosDescansoTexto;
}

void Timer()
{
	while (timerIniciado) {
		
		SDL_Delay(1000);
		if (tiempoInicial > 0) {
			*estado = 1;
			tiempoInicial -= 1000;
			minutos = tiempoInicial / 60000;
			segundos = (tiempoInicial % 60000) / 1000;
			*CTTP = std::to_string(minutos) + ":" +
				(segundos < 10 ? "0" : "") + std::to_string(segundos);
			
		}
		else if (tiempoInicial <=0)
		{
			if (tiempoDescansoInicial > 0) {
				*estado = 2;
				tiempoDescansoInicial -= 1000;
				minutosDescanso = tiempoDescansoInicial / 60000;
				segundosDescanso = (tiempoDescansoInicial % 60000) / 1000;
				*CTTD = std::to_string(minutosDescanso) + ":" +
					(segundosDescanso < 10 ? "0" : "") + std::to_string(segundosDescanso);
			}
			if (tiempoDescansoInicial <= 0) {
				timerIniciado = false;
				ciclo++;
				ReiniciarTimer();
				botonStartPtr->SetTexto("Start");
				botonStartPtr->esPulsableSet(true);
				*estado = 0;
				
	
			}
		}
			
	}
	

}

void limpiarMierda()
{



	
	SDL_DestroyRenderer(render);
	TTF_CloseFont(fuente);
}

void Redibujar() //Usar esta funcion para redibujar todos los elementos "permanentes en pantalla
{
	//MOSTRAR TEXTURAS
	fondoPrincipal.MostrarTextura(render, 255, 0);
	panelUno.MostrarTextura(render, 255, true);

	//**************************************************************
	
	//DIBUJAR BOTONES 
	if (botonStartPtr->isHigh()) {

		botonStartPtr->Highlight(VERDE, render, fuente);
	}
	else {
		botonStartPtr->Unhighglith(render, fuente);
	
	
	}
	if (botonPararPtr->isHigh()) {
		
		botonPararPtr->Highlight(AZUL, render, fuente);
	
	}
	else botonPararPtr->Unhighglith(render, fuente);
	if (botonAboutPtr->isHigh()) {
		botonAboutPtr->Highlight(CIAN, render, fuente);
	}
	else {
		botonAboutPtr->Unhighglith(render, fuente);
	}
	

	//DIBUJAR TEXTOS
	titulo.DibujarTexto("TPomodoro Timer", fuente, ROJO, render, true);
	saludo.DibujarTexto("Hola, " + *nombreUsuario, fuente, ROJO, render, false);
	textoPomodoro.DibujarTexto("Pomodoro: ", fuente, CIAN, render, false);
	textoDescanso.DibujarTexto("Desncaso: ", fuente, VERDE, render, false);
	timerPomodoro.DibujarTexto(*CTTP, fuente, CIAN, render, true);
	timerDescanso.DibujarTexto(*CTTD, fuente, VERDE, render, true);
	
	rectUno.Dibujar(render, true);
	switch (*estado) {
	case 0:
		textoConcentrate.DibujarTexto("-", fuente,AZUL, render,false);
		break;
	case 1:
		textoConcentrate.DibujarTexto("Concentrate", fuente, ROJO, render, true);
		break;
	case 2:
		textoConcentrate.DibujarTexto("Descansa", fuente, MORADO, render, true);
		break;
	default:
		textoConcentrate.DibujarTexto("-", fuente, AZUL, render, false);
	}
	if (*showAbout) {
		panelAbout.MostrarTextura(render, 255, false);
	}

}
