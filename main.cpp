//GRAVITY
#include <time.h>       /* time */
#include <string>       /*strings*/
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Portada.hpp"


int main(int argc, const char* argv[]){
    
    srand (time(NULL));

    sf::RenderWindow window(sf::VideoMode(640,480), "CAN_U_SEE_ME!?!", sf::Style::Close);
    sf::Vector2f screenSize = sf::Vector2f(window.getSize().x,window.getSize().y);    
    float deltatime = 0;
    
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(65);
    //Portada portada;
    
    //Cover
    //portada.notAnimation();
    //portada.display(&window, "res/pics/portada.png");
    
    
    //GAME


    sf::Image deepthImage;
    deepthImage.loadFromFile("res/pics/dm.png");

    sf::Image finalImage;
    finalImage.create(640,480,deepthImage.getPixelsPtr());

    
     sf::Clock timer;

     sf::Font font;
     font.loadFromFile("res/fonts/font.otf");

     float timePassed = 0;

    while(window.isOpen()){
        
        deltatime = timer.restart().asSeconds();
        timePassed += deltatime;


        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close(); 
            if (event.type == sf::Event::Resized) {window.setSize(sf::Vector2u(event.size.width, event.size.height));}
            if (sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left) {
                    //for (Penguin& penguin : penguins){
                    //    if(penguin.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))){
                    //        penguin.setVel(sf::Vector2f(rand()%100-50.0f, -200.0f));
                    //        penguin.setTexture(penguinUp);
                    //    }
                    //}
                }
            }
        }

        if (sf::Touch::isDown(0)) {
            /*for (Penguin& penguin : penguins){
                if(penguin.getGlobalBounds().contains(sf::Vector2f(sf::Touch::getPosition(0, window)))){
                    penguin.setVel(sf::Vector2f(rand()%100-50.0f, -200.0f));
                    penguin.setTexture(penguinUp);
                }
            }*/
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) window.close();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        




        const int maxwidth=640;
        int xdpi=75;    // x-resolution of typical monitor

        int width=640;  // width of display in pixels
        int height=480; // height of display in pixels

        int lookL[maxwidth];
        sf::Color colour[maxwidth]; // any type suitable for storing colours

        int obsDist=xdpi*12;
        int eyeSep=xdpi*2.5;

        int featureZ, sep;
        int x,y, left,right;

        for (y=0; y < height; y++) {
            for (x=0; x<width; x++) { lookL[x]=x; }

             for (x=0; x<width; x++) {
                  featureZ = deepthImage.getPixel(x,y).r; // insert a function or refer to a depth-map here

                  // the multiplication below is 'long' to prevent overflow errors
                  sep=(int)(((long)eyeSep*featureZ)/(featureZ+obsDist));
                  left=x-sep/2; right=left+sep;
                  if ((left>=0) && (right<width)) lookL[right]=left;
             }

//       The second stage is to apply the pattern within the constraints imposed by the links. This is quite simple and the program speaks for itself (random-dot method):

         for (x=0; x<width; x++) {
              if (lookL[x]==x)
                  colour[x]= sf::Color(std::rand()%255,std::rand()%255,std::rand()%255); // unconstrained
              else
                   colour[x]=colour[lookL[x]]; // constrained
         }

         for (x=0; x<width; x++) {
              finalImage.setPixel(x,y, colour[x]);
         }
        }




        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) finalImage.saveToFile("screenshot_"+std::to_string(rand()%1337)+".png");


        static sf::Texture texture;
        texture.loadFromImage(finalImage);
        static sf::Sprite sprite;
        sprite.setTexture(texture);


        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }
}
