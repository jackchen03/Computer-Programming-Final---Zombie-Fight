#ifndef MAP_H
#define MAP_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <string>
#include "LTexture.h"

const int LEVEL_WIDTH1=2360;
const int LEVEL_HEIGHT1=1204;
extern const int doorwith;
const int SCREEN_WIDTH1=1000;
const int SCREEN_HEIGHT1=600;

class bucket
{
    friend class Dot;
    friend class Dot1;
    friend class Dot2;
    friend class zombie;

   public:
       bucket();
       ~bucket();
       void freebucket();
       void freewall();
       bool loadFromFilebucket( std::string path,SDL_Renderer* gRenderer );
       bool loadFromFilewall(std::string path,SDL_Renderer* gRenderer);
       void renderwall( SDL_Rect &camera,SDL_Renderer* gRenderer,LTexture&,int i,int j, SDL_Rect* clip=NULL);
       void allrender(SDL_Rect &camera,SDL_Renderer* gRenderer,LTexture&,LTexture&, SDL_Rect* clip=NULL);
       void judgethebarrier(int,int);
       bool pos_xy_wall[LEVEL_WIDTH1/40][LEVEL_HEIGHT1/63];


       void putwall(int x,int y);
       bool action(int x,int y);
       SDL_Texture* wTexture;
   private:

      static const int wWidth=40;
      static const int wHeight=63;
      int time_xy_wall[LEVEL_WIDTH1/40][LEVEL_HEIGHT1/63];
};


class Dot
{
    friend class bucket;
    friend class zombie;

    public:
        int   get_relative_pos_x(SDL_Rect&);
        int   get_relative_pos_y(SDL_Rect&);
        int rposx;
        int rposy;
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;
		//Maximum axis velocity of the dot
		static const int DOT_VEL = 4;
		//Initializes the variables
		Dot();
		//Takes key presses and adjusts the dot's velocity

		//related to health
		void hurt(int damage){ characterhealth -= damage; }
//        void heal(int restore){ changeHealth()health += restore; }
        void changeHealth(int h){ characterhealth = h; }
        int getHealth(){ return characterhealth; }




		//Moves the dot
		void move(int camX, int camY,bucket & bucketwall ,Dot&);
        void cantgo(bucket & bucketwall,int camX, int camY );

		//Shows the dot on the screen relative to the camera
		void render( int camX, int camY,LTexture&gDotTexture, SDL_Renderer* gRenderer  );


		int getPosX();
		int getPosY();

		//related to judging moving
		void setmoving(bool a){ moving = a; }
        bool getmoving(){ return moving ; }
        void setDirection(int a){ direction = a ;}
        int getDirection(){ return direction; }


        //related to counters
        void addCounter(){ counter++;}
        int getCounter(){ return counter ;}
        void addHitCounter(){ hitCounter++;}
        int getHitCounter(){ return hitCounter ;}
        void addDieCounter(){ dieCounter++;}
        int getDieCounter(){ return dieCounter ;}
        void setDieCounter(int a){ dieCounter = a;}


         // related to hit or die(hurt)
        bool getHit(){ return hit;}
        void setHit(bool a){ hit = a;}
        void setDie(bool a){ die = a;}
        bool getDie(){ return die;}

        //related to loading media
        bool loadMediaMove(SDL_Renderer* gRenderer , LTexture[4][10][3]);




protected:


		int mPosX,mPosY;
		int characterhealth;
		int mVelX, mVelY;
		bool hit ;
		bool die;
		int direction;
		bool moving;
		int counter;
		int weapon_count ;
		int dieCounter;
		int hitCounter;


};

class Dot1 : public Dot{
 public :

    void handleEvent( SDL_Rect &camera,SDL_Renderer* gRenderer,LTexture& wTexture,SDL_Event& e, bucket& bucketwall );
};


class redbox{
  friend class Dot1;

   public:
       redbox();

       void freeredbox();

       void renderredbox( SDL_Rect &camera,SDL_Renderer* gRenderer,LTexture&);

       bool hitthered(Dot1&,int i);
      //  void  collision(Dot&dot);
      bool pos_xy_red [16];
  private:

      static const int bWidth=45;
      static const int bHeight=41;


     int posxofred[16];
     int posyofred[16];


}
;



#endif
