#include "Global.h"
#include "Particle.h"
#include "ParSys.h"

using namespace sf;
vector<Texture> tts;

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Particle System");
	Texture tt1, tt2, tt3;
	tt1.loadFromFile("sprite.png");
	tt2.loadFromFile("7up_New_Logo.png");
	tt3.loadFromFile("mountain_dew.png");
	tts.push_back(tt1);
	tts.push_back(tt2);
	tts.push_back(tt3);
	
	ParSys par1 = ParSys(Vector2f(50.f, 50.f), 0.1f, 0, Vector2f(150.f, 75.f), 0.1f, 0, 0);
	ParSys par2 = ParSys(Vector2f(50.f, 800.f), 0.1f, 270, Vector2f(100.f, 100.f), 0.1f, 1, 1);
	ParSys par3 = ParSys(Vector2f(1500.f, 50.f), 0.1f, 90, Vector2f(109.f, 87.f), 0.1f, 2, 2);
	ParSys par4 = ParSys(Vector2f(1500.f, 800.f), 0.1f, 180, Vector2f(150.f, 75.f), 0.1f, 0, 0);

	// run the main loop
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// draw it
		par1.update();
		par2.update();
		par3.update();
		par4.update();
		window.clear();
		par1.draw(window);
		par2.draw(window);
		par3.draw(window);
		par4.draw(window);
		window.display();
	}

	return 0;
}