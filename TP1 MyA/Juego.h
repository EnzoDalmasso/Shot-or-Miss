#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

using namespace std;

class Jugar
{
public:
	Jugar();
	void mouse_1();
	bool click(Vector2f izq, Sprite sprt);
	void imp_pant();
	void npc();
	void rotacion_er();

private:
	Event mouse;
	Vector2f pos_mouse;
	RenderWindow* ventana;
	Texture rehen;
	Sprite rehen_s;
	Texture e_terrorista;
	Sprite terrorista;
	Texture mirage;
	Sprite m_mirage;
	int contador;
	int numero_aleatorio;
	int vida;
	int puntaje_total;
	int disparo_ami;

};

Jugar::Jugar()
{
	ventana=new RenderWindow(VideoMode(800, 600, 32), "Ventana 1");

	mirage.loadFromFile("mapamirage.jpg");
	m_mirage.setTexture(mirage);
	
	rehen.loadFromFile("rehen.png");
	rehen_s.setTexture(rehen);
	rehen_s.setPosition(400, 200);

	e_terrorista.loadFromFile("Terrorista.jpg");
	terrorista.setTexture(e_terrorista);
	terrorista.setPosition(200, 200);
	terrorista.setOrigin(e_terrorista.getSize().x / 2, e_terrorista.getSize().y / 2);
	contador = 0;
	srand(time(NULL));
	vida = 3;
	ventana->setFramerateLimit(15);
	puntaje_total = 0;
	disparo_ami = 0;
}

void Jugar::mouse_1()
{
	while (ventana->pollEvent(mouse))
	{
		switch (mouse.type) 
		{
		case Event::MouseMoved:
			pos_mouse = ((Vector2f)Mouse::getPosition(*ventana));
			break;
		case Event::MouseButtonPressed:
			switch (numero_aleatorio)
			{
			case 1:
				if (click(pos_mouse, rehen_s) == true)
				{
					rehen_s.setPosition(1000, 1000);
					cout << "Disparo a rehen" << endl;	
					contador = 45;
					
				}
				vida--;
				cout << "Te quedan "<<vida<< " vida/s" << endl;
				break;

			case 2:
				if (click(pos_mouse, terrorista) == true)
				{
					terrorista.setPosition(1000, 1000);
					puntaje_total++;
					cout << "Que buena punteria" << endl;
					contador = 45;
					disparo_ami = 0;
				}
				break;

			}
			break;
			
		case Event::Closed:

			ventana->close();
			break;

		}
		
	}
}

void Jugar::imp_pant() 
{
	npc();
	
	if (numero_aleatorio == 2)
	{
		disparo_ami = 1;

	}

	while (ventana->isOpen())
	{
		ventana->clear();

		ventana->draw(m_mirage);

		switch (numero_aleatorio)
		{
		case 1:
			ventana->draw(rehen_s);
			break;
		case 2:
			ventana->draw(terrorista);
			break;
		}
		ventana->display();
		mouse_1();
		if (vida == 0)
		{
			ventana->close();
			cout << "Fin del juego" << endl;
			cout << "Tu puntaje total es " << puntaje_total << endl;
		}
		contador++;
		cout << contador << endl;

		if (contador==50)
		{
			if (disparo_ami==1)
			{
				vida--;
				cout << "Me heriste" << endl;
			}
			disparo_ami = 0;

			npc();
			if (numero_aleatorio==2)
			{
				disparo_ami = 1;

			}
			rotacion_er();
			contador = 0;
		}
	}


}
bool Jugar::click(Vector2f izq, Sprite sprt) 
{
	float anchoSprite = sprt.getTexture()->getSize().x;
	float xmaximo = sprt.getPosition().x + anchoSprite / 2.0f;
	float xminimo = sprt.getPosition().x - anchoSprite / 2.0f;


	if (izq.x < xmaximo && izq.x > xminimo)
	{
		float altoSprite = sprt.getTexture()->getSize().y;
		float ymaximo = sprt.getPosition().y + altoSprite / 2.0f;
		float yminimo = sprt.getPosition().y - altoSprite / 2.0f;
		if (izq.y < ymaximo && izq.y > yminimo)
			return true;
	}
	return false;

}
void Jugar::npc()
{
	numero_aleatorio = rand() % 2 + 1;
}

void Jugar::rotacion_er()
{
	int a;
	a = rand() % 2 + 1;
	switch (a)
	{
	case 1:
		rehen_s.setPosition(400, 200);
		terrorista.setPosition(400, 200);
		break;
	case 2:
		rehen_s.setPosition(200, 200);
		terrorista.setPosition(200, 200);
		break;
		
	default:
		break;
	}
}