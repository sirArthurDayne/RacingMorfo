#include<SFML/Graphics.hpp>
#include<iostream>

#define LOG(x) std::cout<<x<<std::endl

/*

.##....##.########...#######...######..####..######.....########..########..########..######..########.##....##.########....###.....##....
.##...##..##.....##.##.....##.##....##..##..##....##....##.....##.##.....##.##.......##....##.##.......###...##....##......##.##...####...
.##..##...##.....##.##.....##.##........##..##..........##.....##.##.....##.##.......##.......##.......####..##....##.....##...##...##....
.#####....########..##.....##..######...##...######.....########..########..######....######..######...##.##.##....##....##.....##........
.##..##...##...##...##.....##.......##..##........##....##........##...##...##.............##.##.......##..####....##....#########..##....
.##...##..##....##..##.....##.##....##..##..##....##....##........##....##..##.......##....##.##.......##...###....##....##.....##.####...
.##....##.##.....##..#######...######..####..######.....##........##.....##.########..######..########.##....##....##....##.....##..##....
*/
//---------------------------------------------ESTRUCTURA DEL MAPA--------------------------------//
const int ANCHO = 1024;
const int ALTO = 768;
const int ANCHURA_CALLE = 2000;
const float CAM_PROFUNIDAD = 0.84f;
const int DISTANCIA_SEGMENTO = 200;

struct HacerLineas
{
	float x, y, z;																//Coordenadas del centro de la linea
	float xScreen, yScreen, wScreen;											//Coordenadas en pantalla
	float escala;

	HacerLineas()																	//Constructor
	{
		x = y = z = 0;			
	}
																				//Convierte coord. de la ventana en coord. de pantalla
	void ConvertirProyeccion(int camaraX, int camaraY, int camaraZ)														
	{
		escala = CAM_PROFUNIDAD / ( z - camaraZ);
		xScreen = (1 + escala * (x - camaraX)) * ANCHO / 2;
		yScreen = (1 - escala * (y - camaraY)) * ALTO / 2;
		wScreen = escala * ANCHURA_CALLE * ANCHO / 2;
	}
};
//-------------------------------------------TEXTURA DEL FONDO-----------------------------------//poligono cuyos angulos menores a 180`
/* parametros(ref a ventana, color de la forma, coordenadas del trapecio x1& y1 &x2 &y2, largo w1 &w2) @ = punto
										|---------------w2-------------|
								   x2<--@###############@##############@--> y2
									   #							    #
									  #									 #
									 #									  #
									#									   #
							  x1<--@#####################@#################@-->y1
								   |--------------------w1-----------------|
								   
*/														
static void DibujarQuad(sf::RenderWindow& ventana, sf::Color color, int x1, int y1, int w1, int x2, int y2, int w2 )	
{
	sf::ConvexShape cvx;														//Crea una figura convexa
	cvx.setFillColor(color);													//establecemos un color
	
	cvx.setPointCount(4);														//Establecemos la cantidad de puntos del poligono
	
	cvx.setPoint(0, sf::Vector2f(x1 - w1, y1) );								//1 punto
	cvx.setPoint(1, sf::Vector2f(x2 - w2, y2) );								//2 punto
	cvx.setPoint(2, sf::Vector2f(x2 + w2, y2) );								//3 punto
	cvx.setPoint(3, sf::Vector2f(x1 + w1, y1) );								//4 punto

	//LOG(cvx.getLocalBounds().width);
	ventana.draw(cvx);															//Dibujar textura
}

int main()
{
	//--------------------------------------CREAR VENTANA--------------------------------------//
	sf::RenderWindow ventana( sf::VideoMode( ANCHO, ALTO ), "Racing2D-ByKrosis", sf::Style::Resize);

	ventana.setFramerateLimit(60);												//limita a 60FPS

	//------------------------------------------RECURSOS--------------------------------------//
	std::vector<HacerLineas> genLineas;

																				//Cantidad de lineas visibles en el mapa(1600)
	for (int i = 0; i < 1600; i++)
	{
		HacerLineas linea;														//Crea un objeto de struct HacerLineas		
		linea.z = DISTANCIA_SEGMENTO * i;										//Le asigna una profundidad (Z) a cada linea
		
		genLineas.push_back(linea);												//las agrega al array genLineas

	}
		int cantidadLineas = genLineas.size();									//Guarda el tamano del array dinamico

	//---------------------------------------LOOP PRINCIPAL------------------------------------//
	while ( ventana.isOpen() )
	{
		//------------------------------------EVENTOS DEL JUEGO---------------------------------//
		sf::Event evt;
		while ( ventana.pollEvent(evt) )
		{
			switch (evt.type)
			{
			case sf::Event::Resized:											//redimensiona la ventana
				LOG(evt.size.width);
				LOG(evt.size.height);
				break;
			case sf::Event::KeyPressed:											//ESC cierra la ventana
				if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )
				{
					ventana.close();
				}
				break;
			}
		}
		//----------------------------------LIMPIAR PANTALLA-----------------------------------//
		ventana.clear(sf::Color::White);

		//-----------------------------------DIBUJAR EN PANTALLA----------------------------------//
		
		//------------------------------------DIBUJAR TEXTURAS FONDO------------------------//
		//DibujarQuad(ventana, sf::Color::Blue, 500, 500, 200, 500, 300, 100);//500,500, 200,500,300,100

		for (int i = 0; i < 300; i++)											//Generara el dibujado del mapeado
		{
			HacerLineas& L = genLineas[ i % cantidadLineas ];					//Crea una ref a genLineas y pasa sus datos

			L.ConvertirProyeccion(0, 1500, 0);									//Convierte coordenadas

																				// le asigna un color al pasto dependiendo de sus coord.
			sf::Color hierba = (i / 3) % 2 ? sf::Color(5, 183, 29) : sf::Color(2, 145, 21); //TRUE mas claro FALSE mas oscuro

			HacerLineas p = genLineas[ (i-1) % cantidadLineas +1];

			DibujarQuad(ventana, hierba, 0, p.yScreen, ANCHO, 0, L.yScreen, ANCHO);
		}
		LOG(cantidadLineas);
		//----------------------------------DIBUJAR CALLE----------------------------------//

		//----------------------------------MOSTRAR EN PANTALLA--------------------------------//
		ventana.display();
	}

	return 0;
}