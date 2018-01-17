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

    sf::Image patternbmp;
    patternbmp.loadFromFile("res/pics/pattern1.png");
//    patternbmp.loadFromFile("res/pics/pattern2.jpg");


    int patHeight=patternbmp.getSize().y;

     const int maxwidth=640*6;  // allow space for up to 6 times oversampling
     int xdpi=75; int ydpi=75;

     int yShift=ydpi/16;

     int width=640;
     int height=480;

     int oversam=4; // oversampling ratio
     int lookL[maxwidth]; int lookR[maxwidth];
     sf::Color colour[maxwidth], col;
     int lastlinked; int i;

     int vwidth=width*oversam;

     int obsDist=xdpi*12;
     int eyeSep=xdpi*2.5; int veyeSep=eyeSep*oversam;

     int maxdepth=xdpi*12;
     int maxsep=(int)(((long)eyeSep*maxdepth)/(maxdepth+obsDist)); // pattern must be at
                                                                   // least this wide
     int vmaxsep=oversam*maxsep;

     int s=vwidth/2-vmaxsep/2; int poffset=vmaxsep-(s % vmaxsep);

     int featureZ, sep;
     int x,y, left,right;
     bool vis;
    
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
        





 /*        for (y=0; y<height; y++)
         {
          for (x=0; x<vwidth; x++)
          { lookL[x]=x; lookR[x]=x; }

          for (x=0; x<vwidth; x++)
          {
           if ((x % oversam)==0) // SPEEDUP for oversampled pictures
           {
            featureZ= deepthImage.getPixel(x/oversam,y).r;//<depth of image at (x/oversam,y)>

            sep=(int)(((long)veyeSep*featureZ)/(featureZ+obsDist));
           }

           left=x-sep/2; right=left+sep;

           vis=true;

           if ((left>=0) && (right<vwidth))
           {
            if (lookL[right]!=right) // right pt already linked
            {
             if (lookL[right]<left) // deeper than current
             {
              lookR[lookL[right]]=lookL[right]; // break old links
              lookL[right]=right;
             }
             else vis=false;
            }

            if (lookR[left]!=left) // left pt already linked
            {
             if (lookR[left]>right) // deeper than current
             {
              lookL[lookR[left]]=lookR[left]; // break old links
              lookR[left]=left;
             }
             else vis=false;
            }
            if (vis==true) { lookL[right]=left; lookR[left]=right; } // make link
           }
          }

          lastlinked=-10; // dummy initial value

          for (x=s; x<vwidth; x++)
          {
           if ((lookL[x]==x) || (lookL[x]<s))
           {
            if (lastlinked==(x-1)) colour[x]=colour[x-1];
            else
            {
             colour[x]=patternbmp.getPixel(((x+poffset) % vmaxsep)/oversam,
                                           (y+((x-s)/vmaxsep)*yShift) % patHeight);
            }
           }
           else
           {
            colour[x]=colour[lookL[x]];

            lastlinked=x; // keep track of the last pixel to be constrained
           }
          }

          lastlinked=-10; // dummy initial value

          for (x=s-1; x>=0; x--)
          {
           if (lookR[x]==x)
           {
            if (lastlinked==(x+1)) colour[x]=colour[x+1];
            else
            {
             colour[x]=patternbmp.getPixel(((x+poffset) % vmaxsep)/oversam,
                                        (y+((s-x)/vmaxsep+1)*yShift) % patHeight);
            }
           }
           else
           {
            colour[x]=colour[lookR[x]];

            lastlinked=x; // keep track of the last pixel to be constrained
           }
          }*/


        for (y=0; y<height; y++)
        {
         for (x=0; x<vwidth; x++)
         { lookL[x]=x; lookR[x]=x; }

         for (x=0; x<vwidth; x++)
         {
          if ((x % oversam)==0) // SPEEDUP for oversampled pictures
          {
           featureZ= deepthImage.getPixel(x/oversam,y).r;

           sep=(int)(((long)veyeSep*featureZ)/(featureZ+obsDist));
          }

          left=x-sep/2; right=left+sep;

          vis=true;

          if ((left>=0) && (right<vwidth))
          {
           if (lookL[right]!=right) // right pt already linked
           {
            if (lookL[right]<left) // deeper than current
            {
             lookR[lookL[right]]=lookL[right]; // break old links
             lookL[right]=right;
            }
            else vis=false;
           }

           if (lookR[left]!=left) // left pt already linked
           {
            if (lookR[left]>right) // deeper than current
            {
             lookL[lookR[left]]=lookR[left]; // break old links
             lookR[left]=left;
            }
            else vis=false;
           }
           if (vis==true) { lookL[right]=left; lookR[left]=right; } // make link
          }
         }

         lastlinked=-10; // dummy initial value

         for (x=0; x<vwidth; x++)
         {
          if (lookL[x]==x)
          {
           if (lastlinked==(x-1)) colour[x]=colour[x-1];
           else
           {
            colour[x]=patternbmp.getPixel((x % vmaxsep)/oversam,
                                          (y+(x/vmaxsep)*yShift) % patHeight);
           }
          }
          else
          {
           colour[x]=colour[lookL[x]];

           lastlinked=x; // keep track of the last pixel to be constrained
          }
         }

          int red, green, blue;

          for (x=0; x<vwidth; x+=oversam)
          {
           red=0; green=0; blue=0;

           // use average colour of virtual pixels for screen pixel
           for (i=x; i<(x+oversam); i++)
           {
            col=colour[i];
            red+=col.r;
            green+=col.g;
            blue+=col.b;
           }
           col=sf::Color(red/oversam, green/oversam, blue/oversam);

           finalImage.setPixel(x/oversam,y, col);
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
