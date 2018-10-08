#include "SFML/Graphics.hpp"
#include "Credits.hpp"
#include "Settings.hpp"
#include <iostream>
#include <vector>
#include <string>

Credits::Credits(){
	//x position of Text objects
	yText = 700; 

	//y position of Text objects
	xText = 250;
	
	//Speed of the game
	timeModifier = 24;

	//y Position for picture
	yPic = 1900;

	//x position of pictures
	xPic = 175;

	//Position for monsters
	yMon = 550;
	xMon = 80;
	
	//Factor by which Text objects are spaced out
	staggerFactor = 2;

	//Speed of the game
	timeFactor = 500;
	
	//Vector of vectors that holds team with their respective team members
	credits = {{"CREDITS TEAM", "Justin Johns", "Kanoa Ellis", "Alicia Stoll", "Mohamed", "Harman"},
		{"PLAYER TEAM", "Zach Thomas", "Matt Kennedy", "James Lund", "Will Shreeve"},
		{"OPTIONS TEAM", "Christna Kidwell", "Matt Tetreau", "Eric Schoenborn", "Lauren DeFrancesco", "Atone Joryman"},
		{"GORGON 7", "Gorgon Slime Boss XII", "Gorgonzola Lord", "Gorgon Squire", "Colombian Gorgon"}};
}

int Credits::start(sf::RenderWindow &rw){

	this->window = &rw;

	window ->setFramerateLimit(timeFactor);

	//Loads the games standard font in
	if(!font.loadFromFile("fonts/Notable-Regular.ttf")){
		return EXIT_FAILURE; 
	}

	//Set's the gameTitle Text object's features 
	gameTitle.setFont(font);
	gameTitle.setString("NOT ON MY BLOCK");
	gameTitle.setFillColor(sf::Color::White);
	gameTitle.setCharacterSize(30);
	gameTitle.setPosition(xText, yText);

	//Set's the groups Text object font and color 
	groups.setFont(font);
	groups.setFillColor(sf::Color::White);

	/** Loads a splash here
	 * The splash here will be used for a sliding picture */

	if(!splash.loadFromFile("images/overlordtheultimate.jpg")){
		std::cerr << "Can't load start image." << std::endl;
	}

	window->clear();

	overlord.setTexture(splash);

	/** Loads a monster texture here which can be used multiple times;
	 * monster sprites are then created here */
	sf::Texture mTexture;
	if(!mTexture.loadFromFile("sprites/monster_one.png")){
		std::cerr << "Can't load start image." << std::endl;
	}

	monster1.setTexture(mTexture);
	monster2.setTexture(mTexture);

	//Counter for monster movement
	count = 0;

	//runs the credits scene
	while(window->isOpen()){
		window->clear();

		sf::Event event;

		// This loop will run everytime an event occurs
		while (window->pollEvent(event))
		{
			// Check for specific events
			switch (event.type)
			{	//Adds working exit button
				case sf::Event::Closed:
					window->close();
					exit(0);
					break;
				
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{	//Adds working speeup button
						case sf::Keyboard::A:
							timeModifier = 4;	
							break;
						//Adds another exit option
						case sf::Keyboard::Escape:
							window->close();
							exit(0);
							break;

						default:
							break;
					}
					break;
				//returns game speed to normal after releasing the speedup key
				case sf::Event::KeyReleased:
					switch(event.key.code)
					{
						case sf::Keyboard::A:
							timeModifier = 24;
							break;

						default:
							break;
					}
					break;

				default: 
					break;
			}
		}

		//Draw Monster sprites
		window->draw(monster1);
		window->draw(monster2);

		//Draw gameTitle Text 
		window->draw(gameTitle);

		window->draw(overlord);

		int x = 1;
		
		//Formats each element in the credits array and draw's them on the screen
		for(int i = 0; i < credits.size(); i++){

			for(int j =0; j < credits[i].size(); j++){
				groups.setString(credits[i][j]);

				if(j == 0){
					groups.setCharacterSize(25);
					groups.setPosition(xText, yText + (50 * x++));
				}else{	
					groups.setCharacterSize(20);
					groups.setPosition(xText, yText + (50 * x++));
				}	

				window -> draw(groups);	

			}

		}

		//Get elapsed time
		time = clock.getElapsedTime();
		//Convert time to milliseconds
		mills = time.asMilliseconds();

		//Speed control for scrolling credits;
		if(mills %  timeModifier == 0){
			gameTitle.setPosition(xText, yText--);
			groups.setPosition(xText, yText--);
			overlord.setPosition(xPic, yPic-=2);

		}
		//Control for monster movement (Dance!)	
		if(mills % (timeModifier * 6)  == 0){
			if (count % 4 == 0){
				yMon -= 10;
			} else if (count % 4 == 1){
				xMon += 10;
			} else if (count % 4 == 2) {
				yMon += 10;
			} else if (count % 4 == 3) {
				xMon -= 10;
			}
			monster1.setPosition(xMon, yMon);
			monster2.setPosition(xMon + 600, yMon);
			++count;
		}


		window->display();

	}
	return 0; 
}
