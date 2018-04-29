#include<SFML/Graphics.hpp>
#include <iostream>

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

//-------------------------------------------TEXTURA DEL FONDO-----------------------------------//poligono cuyos angulos menores a 180`
/* parametros(ref a ventana, color de la forma, coordenadas del trapecio x1& y1 &x2 &y2, largo w1 &w2)
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
	//LOG(cvx.getPoint(0).x );
	//LOG(cvx.getPoint(0).y );
	LOG(cvx.getLocalBounds().height);
	ventana.draw(cvx);															//Dibujar textura
}

int main()
{
	//--------------------------------------CREAR VENTANA--------------------------------------//
	sf::RenderWindow ventana( sf::VideoMode( ANCHO, ALTO ), "Racing2D-ByKrosis", sf::Style::Resize);

	ventana.setFramerateLimit(60);												//limita a 60FPS

	//------------------------------------------RECURSOS--------------------------------------//

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

		//-----------------------------------DIBUJAR OBJETOS----------------------------------//
		
		DibujarQuad(ventana, sf::Color::Blue, 500, 500, 200, 120, 50, 100);//500,500, 200,500,300,100

		//----------------------------------MOSTRAR EN PANTALLA--------------------------------//
		ventana.display();
	}

	return 0;
}