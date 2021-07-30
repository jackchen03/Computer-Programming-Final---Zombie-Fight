#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <string>
#include "map.h"


class zombie : public Dot{
   friend class bucket;


    public:

		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;
		//Maximum axis velocity of the dot
		static const int DOT_VEL = 1 ;
		//Initializes the variables
		zombie();
		//Takes key presses and adjusts the dot's velocity

		//related to health
		void hurt(int damage,int x){ health -= damage;direction=x; }
        void heal(int restore){ health += restore; }
        void setHealth(int h){ health = h; }
        int getHealth(){ return health; }

        int   get_relative_pos_x(SDL_Rect&);
        int   get_relative_pos_y(SDL_Rect&);

		//Moves the dot
		void handleEvent( SDL_Rect &camera,SDL_Renderer* gRenderer,LTexture& wTexture, bucket& bucketwall );
		void move(int camX, int camY,bucket & bucketwall ,Dot&);
        void cantgo(bucket & bucketwall,int camX, int camY );
		//Shows the dot on the screen relative to the camera
		void render( int camX, int camY,LTexture&gDotTexture, SDL_Renderer* gRenderer  );


		int getPosX();
		int getPosY();
		void setPos(int x,int y){ mPosX = x; mPosY = y;}

		//related to judging moving
		void setmoving(bool a){ moving = a; }
        bool getmoving(){ return moving ; }
        void setDirection(int a){ direction = a ;}
        int getDirection(){ return direction; }


        //related to counters
        void addCounter(){ counter++;}
        int getCounter(){ return counter ;}

        //related to loading media
        bool loadMediaMove(SDL_Renderer* gRenderer, LTexture moveTexture[10][3]);


        bool zombiehit;
        int zombiepositionx;
        int zombiepositiony;

        bool collision(zombie&);
        int mPosX,mPosY;
        int mVelX, mVelY;
private:


		//int mPosX,mPosY;
		int health;
		//int mVelX, mVelY;
		bool hit ;
		int direction;
		bool moving;
		int counter;




};






#endif
