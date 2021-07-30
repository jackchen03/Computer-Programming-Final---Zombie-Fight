#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <string>
#include"map.h"
#include "LTexture.h"
#include "zombie.h"
#include <cmath>
#include"weapon.h"
#include <SDL_mixer.h>
using namespace std;
fireball ball[12];
//The dimensions of the level
const int LEVEL_WIDTH = 2360;
const int LEVEL_HEIGHT = 1204;
const int doorwith=75;
const int zombie_number = 20;
const int hero_width = 63;
const int hero_height =75;
const int zombie_width = 43;
const int zombie_height = 60;


//Screen dimension constants
const int SCREEN_WIDTH=1000;
const int SCREEN_HEIGHT = 600;
const int bosspositionx=300;
const int bosspositiony=800;

int characterpositionx;
int characterpositiony;
int characterdirection;
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

bool init();
bool loadMedia();
void close();
bool acting[20];


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Surface* gScreenSurface = NULL;
TTF_Font *gFont = NULL;
TTF_Font *scoreFont = NULL;
SDL_Color textColor = { 0, 0, 0 };

LTexture redboxTexture;
LTexture gDotTexture;
LTexture wTexture;
LTexture bTexture;
LTexture gBGTexture;
LTexture moveTexture1[4][10][3]; //hero ( weapon, direction , counter )
LTexture hitTexture1[10]; //hero
LTexture dieTexture1[10]; //hero
LTexture currentTexture1[3]; //hero
LTexture currentTexture[zombie_number][3]; //zombie
LTexture dieTexture[10]; //zombie
LTexture hitTexture[10]; //zombie
LTexture moveTexture[10][3]; //zombie
LTexture boss1Texture[10];
LTexture boss1CurrentTexture;
bucket bucketwall;

//weapons
showbullet pistrolbullet("pistol",9,9,9,20,25,40);
showbullet uzibullet("UZI",1,0,0,10,40,60);
showbullet shotgunbullet("shotgun",0,2,0,40,70,150);
showbullet generadebullet("Grenades",0,1,0,70,80,150);
showbullet wallbullet("Walls",0,1,0,0,0,0);
showbullet shieldbullet("shield",0,0,5,100,0,0);
showbullet timestopbullet("timestop",0,0,3,0,0,0);
showbullet atombombbullet("atombombs",0,0,5,100,200,200);
showgenerade generade0;
showgenerade generade1;
// uzi+pistrol
showgun direction1 (20,60); //showgun(主角x座標,主角y座標,x偏移量,y偏移量,x射程距離,y射程距離)
showgun direction2 (0,100);
showgun direction3 (-50,60);
showgun direction4(20,20);
showgun direction6(-70,40);
showgun direction7(20,-10);
showgun direction8(-45,-10);
showgun direction9(-97,-10);
Mix_Chunk *UZI = NULL;
Mix_Chunk *shotgun = NULL;
Mix_Chunk *pistol = NULL;
Mix_Chunk *barrel = NULL;
Mix_Chunk *generade = NULL;

mousebuttom mouse(350,400,350,530,250,60);
score scoreupgrade;

atom atombomb;
weapon weapons;
shield protectshield;
bucket bucket;
Dot1 dot1;

redbox RED;

bool init()
{
    bool success = true;
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
        for (int i=0;i<20;i++) acting[i]=false;
    }
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	            {
	            	printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
	            	success = false;
	            }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) printf( "Warning: Linear texture filtering not enabled!" );
        gWindow = SDL_CreateWindow( "Zombie War", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {   gScreenSurface = SDL_GetWindowSurface( gWindow );
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
            }
        }

    }
    return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
   if( !redboxTexture.loadFromFile( "red.png",gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !bTexture.loadFromFile( "bucket.png",gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !wTexture.loadFromFile( "wall.png",gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}


	if( !gDotTexture.loadFromFile( "dot.bmp",gRenderer ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load background texture
	if( !gBGTexture.loadFromFile( "map_2.png",gRenderer ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	//抓閃光
          if( !direction1.loadFromFile( "pistol/flash1.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
    	  if( !direction2.loadFromFile( "pistol/flash2.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
	      if( !direction3.loadFromFile( "pistol/flash3.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
    	  if( !direction4.loadFromFile( "pistol/flash4.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
    	  if( !direction6.loadFromFile( "pistol/flash6.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
    	  if( !direction7.loadFromFile( "pistol/flash7.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
    	  if( !direction8.loadFromFile( "pistol/flash8.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
    	  if( !direction9.loadFromFile( "pistol/flash9.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}


//手榴彈
if( !generade0.loadFromFile( "generade/generade.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

       if( !generade0.loadFromFileflash1( "generade/explode1.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
      if( !generade0.loadFromFileflash2( "generade/explode2.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

    if( !generade1.loadFromFile( "generade/generade.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

       if( !generade1.loadFromFileflash1( "generade/explode1.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
      if( !generade1.loadFromFileflash2( "generade/explode2.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}


    //原子彈
    if( !atombomb.loadFromFile( "generade/explode2.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
	//防護罩
    if( !protectshield.loadFromFile( "shield.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}



	//load bucket and wall
	/*if( !bucketwall.loadFromFilebucket( "bucket.png",gRenderer ) )
	{
		printf( "Failed to load bucket texture!\n" );
		success = false;
	}
	/*if( !bucketwall.loadFromFilewall( "wall.png",gRenderer ) )
	{
		printf( "Failed to load bucket texture!\n" );
		success = false;
	}*/

	//文字
	gFont = TTF_OpenFont( "lazy.ttf", 12 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
    }
    scoreFont = TTF_OpenFont( "lazy.ttf", 40 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
    }
// 火球
   for(int i=0;i<=11;i++)
   {
      if( !ball[i].loadFromFile( "fireball.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
   }

   //介面
    if( !mouse.loadFromFile( "start.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
    if( !mouse.brainloadFromFile( "brain.png",gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
	}
	//sound
    pistol = Mix_LoadWAV( "Pistol.wav" );
	if( pistol == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	UZI = Mix_LoadWAV( "Uzi.wav" );
	if( UZI == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	shotgun = Mix_LoadWAV( "Shotgun.wav" );
	if( shotgun == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	barrel = Mix_LoadWAV( "Barrel.wav" );
	if( barrel == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
    generade = Mix_LoadWAV( "Generade.wav" );
	if( generade == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}




	return success;
}

void close()
{
	//Free loaded images
	redboxTexture.free();
	gDotTexture.free();
	gBGTexture.free();
    wTexture.free();
   // bTexture.free()
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
          bool hitthered=false;
          int countred=0;

           bool colli;
           int ramdom=0;

			int fireballcountdown=200;
			zombie zombie[zombie_number];
			for(int i=0;i<zombie_number;i++){
                zombie[i].setPos(200+100*i,200+40*i);
			}
			for(int i=0;i<zombie_number;i++){
                zombie[i].setPos(200+100*i,200+40*i);
              			}


	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{

     for(int i=0; i<zombie_number;i++){
        if(!zombie[i].loadMediaMove(gRenderer, moveTexture ))
        {
			printf( "Failed to load media!\n" );
		}
	 }

		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}

		if(!dot1.loadMediaMove(gRenderer, moveTexture1))
        {
			printf( "Failed to load media!\n" );
		}



		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;





			//The camera area


			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the dot
					dot1.handleEvent( camera,gRenderer,wTexture,e,bucketwall );

				}



//起始畫面
    if (mouse.ending==false)
   {
        mouse.handlebuttom(&e);
        mouse.surfacerender(&mouse.surface,gRenderer);
        if (mouse.getmouseevent()==1)mouse.brainrender(gRenderer);
   }

   switch (mouse.getmouseevent())
   {
    case 3:
              quit=true; break;
   case 2:
       ramdom++;
                if (ramdom==100) ramdom=0;



                for (int i=0;i<zombie_number;i++)
                {
                    if (acting[i]==false)
                    {
                        if (zombie[i].getDie())
                        {
                            acting[i]=true;
                            scoreupgrade.increasescores();
                        }
                    }
                    if (acting[i]==true)
                    {
                        if (zombie[i].getDie()==0)
                        {
                            acting[i]=false;
                        }
                    }

                }
                if (ramdom==1)
                {
                    for(int i=0; i<zombie_number;i++){
                    if(zombie[i].getDie()==1){


                            zombie[i].setDie(0);
                            zombie[i].setHealth(100);
                            zombie[i].setPos(1130,190);
                            zombie[i].setDieCounter(0);
                            break;

                    }

                }
                }




				//judge the direction
				for(int i=0; i<zombie_number;i++){
                    if(abs((zombie[i].getPosX()-dot1.getPosX()))<1){
                        if(zombie[i].getPosY()>dot1.getPosY()){zombie[i].setDirection(8);}
                        else{zombie[i].setDirection(2);}
                    }
                    if(abs((zombie[i].getPosY()-dot1.getPosY()))<1){
                        if(zombie[i].getPosX()>dot1.getPosX()){zombie[i].setDirection(4);}
                        else{zombie[i].setDirection(6);}
                    }
                    else if(zombie[i].getPosX()>dot1.getPosX()){
                        if(zombie[i].getPosY()>dot1.getPosY()){zombie[i].setDirection(7);}
                        else{zombie[i].setDirection(1);}
                    }
                    else if(zombie[i].getPosX()<dot1.getPosX()){
                        if(zombie[i].getPosY()>dot1.getPosY()){zombie[i].setDirection(9);}
                        else{zombie[i].setDirection(3);}
                    }




				}

				for(int i=0; i<zombie_number;i++){
                    zombie[i].handleEvent( camera,gRenderer,wTexture,bucketwall );
                    zombie[i].move(camera.x, camera.y,bucketwall , dot1);

                     colli=false;
                        for(int j=0;j<zombie_number;j++){
                          if(i!=j){
                        colli=zombie[i].collision(zombie[j]);
                        if(colli==true){zombie[i].mPosX-=zombie[i].mVelX;
                        zombie[i].mPosY-=zombie[i].mVelY;}
                          }
                  zombie[i].cantgo(bucketwall,camera.x, camera.y);
				}
				}


				 // decide the state of the heroes
                const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

				 if( currentKeyStates[ SDL_SCANCODE_LEFT ]&&currentKeyStates[ SDL_SCANCODE_UP ] )
				{ 	 dot1.setDirection(7); dot1.setmoving(1);	}
				else if( currentKeyStates[ SDL_SCANCODE_RIGHT ]&&currentKeyStates[ SDL_SCANCODE_UP ] )
				{    dot1.setDirection(9);  dot1.setmoving(1);	}
				else if( currentKeyStates[ SDL_SCANCODE_LEFT ]&&currentKeyStates[ SDL_SCANCODE_DOWN ] )
				{    dot1.setDirection(1);  dot1.setmoving(1) ;			}
				else if( currentKeyStates[ SDL_SCANCODE_RIGHT ]&&currentKeyStates[ SDL_SCANCODE_DOWN ] )
				{    dot1.setDirection(3);  dot1.setmoving(1);		}
				else if( currentKeyStates[ SDL_SCANCODE_UP ] )
				{ 	 dot1.setDirection(8);  dot1.setmoving(1);	}

				else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
				{   dot1.setDirection(2); dot1.setmoving(1);   }

				else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
				{   dot1.setDirection(4); dot1.setmoving(1) ; }

				else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
				{   dot1.setDirection(6); dot1.setmoving(1) ;  }
				else{dot1.setmoving(0); }


				//Move the dot
				dot1.move(camera.x, camera.y,bucketwall ,zombie[0]);
				for(int j=0;j<zombie_number;j++){
                     dot1.cantgo(bucketwall,camera.x, camera.y );
                }




				camera.x = ( dot1.getPosX() + hero_width/ 2 ) - SCREEN_WIDTH / 2;
				camera.y = ( dot1.getPosY() + hero_height / 2 ) - SCREEN_HEIGHT / 2;


				//Keep the camera in bounds
				if( camera.x < 0 )
				{
					camera.x = 0;
				}
				if( camera.y < 0 )
				{
					camera.y = 0;
				}
				if( camera.x > LEVEL_WIDTH - camera.w )
				{
					camera.x = LEVEL_WIDTH - camera.w;
				}
				if( camera.y > LEVEL_HEIGHT - camera.h )
				{
					camera.y = LEVEL_HEIGHT - camera.h;
				}
                for(int i=0;i<zombie_number;i++)
                {
                  zombie[i].zombiepositionx=zombie[i].get_relative_pos_x(camera);
                  zombie[i].zombiepositiony=zombie[i].get_relative_pos_y(camera);
                }

                dot1.rposx=dot1.get_relative_pos_x(camera);
                dot1.rposy=dot1.get_relative_pos_y(camera);
                characterpositionx=dot1.rposx;
                characterpositiony=dot1.rposy;



                direction1.setcharacterpositionx(dot1.rposx);
                direction1.setcharacterpositiony(dot1.rposy);
                direction2.setcharacterpositionx(dot1.rposx);
                direction2.setcharacterpositiony(dot1.rposy);
                direction3.setcharacterpositionx(dot1.rposx);
                direction3.setcharacterpositiony(dot1.rposy);
                direction4.setcharacterpositionx(dot1.rposx);
                direction4.setcharacterpositiony(dot1.rposy);
                direction6.setcharacterpositionx(dot1.rposx);
                direction6.setcharacterpositiony(dot1.rposy);
                direction7.setcharacterpositionx(dot1.rposx);
                direction7.setcharacterpositiony(dot1.rposy);
                direction8.setcharacterpositionx(dot1.rposx);
                direction8.setcharacterpositiony(dot1.rposy);
                direction9.setcharacterpositionx(dot1.rposx);
                direction9.setcharacterpositiony(dot1.rposy);







				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				//Render background
				gBGTexture.render( 0, 0,gRenderer, &camera );


                //weapon
                if (dot1.getDirection()<=4) characterdirection=dot1.getDirection()-1;
                else characterdirection=dot1.getDirection()-2;


                 if( currentKeyStates[  SDL_SCANCODE_SPACE ] )
				{   if (weapons.firespeedzero())
				    {
				        switch (weapons.getweaponmode())
				        {
        case 0:
                           if (pistrolbullet.bulletremain())
                {             weapons.changefirespeed(pistrolbullet.speed());

                Mix_PlayChannel( -1, pistol, 0 );
				            switch(characterdirection)
                {    case 0:

                        direction1.changestart(0,0);
                        direction1.changelength(282,282);
                        direction1.pistrolhit(zombie,characterdirection);
                        direction1.changepistrolfinaloutput(zombie,pistrolbullet,characterdirection);
                        direction1.showline(gRenderer);
                        direction1.render(characterpositionx-30,characterpositiony+25,gRenderer);
                        break;
                    case 1:
                        direction2.changestart(0,0);
                        direction2.changelength(0,400);
                        direction2.pistrolhit(zombie,characterdirection);
                        direction2.changepistrolfinaloutput(zombie,pistrolbullet,characterdirection);
                        direction2.showline(gRenderer);
                        direction2.render(characterpositionx-30,characterpositiony+50,gRenderer);
                        break;
                    case 2:
                        direction3.changestart(0,0);
                        direction3.changelength(-282,282);
                        direction3.pistrolhit(zombie,characterdirection);
                        direction3.changepistrolfinaloutput(zombie,pistrolbullet,characterdirection);
                        direction3.showline(gRenderer);
                        direction3.render(characterpositionx+30,characterpositiony+50,gRenderer);
                        break;
                    case 3:
                        direction4.changestart(0,0);
                        direction4.changelength(400,0);
                        direction4.pistrolhit(zombie,characterdirection);
                        direction4.changepistrolfinaloutput(zombie,pistrolbullet,characterdirection);
                        direction4.showline(gRenderer);
                        direction4.render(characterpositionx-70,characterpositiony-15,gRenderer);
                        break;
                    case 4:
                        direction6.changestart(0,0);
                        direction6.changelength(-400,0);
                        direction6.pistrolhit(zombie,characterdirection);
                        direction6.changepistrolfinaloutput(zombie,pistrolbullet,characterdirection);
                        direction6.showline(gRenderer);
                        direction6.render(characterpositionx+52,characterpositiony+25,gRenderer);
                        break;
                    case 5:
                        direction7.changestart(0,0);
                        direction7.changelength(282,-282);
                        direction7.pistrolhit(zombie,characterdirection);
                        direction7.changepistrolfinaloutput(zombie,pistrolbullet,characterdirection);
                        direction7.showline(gRenderer);
                        direction7.render(characterpositionx-25,characterpositiony-20,gRenderer);
                        break;
                    case 6:
                        direction8.changestart(0,0);
                        direction8.changelength(0,-400);
                        direction8.pistrolhit(zombie,characterdirection);
                        direction8.changepistrolfinaloutput(zombie,pistrolbullet,characterdirection);
                        direction8.showline(gRenderer);
                        direction8.render(characterpositionx+15,characterpositiony-15,gRenderer);
                        break;
                    case 7:
                        direction9.changestart(0,0);
                        direction9.changelength(-282,-282);
                        direction9.pistrolhit(zombie,characterdirection);
                        direction9.changepistrolfinaloutput(zombie,pistrolbullet,characterdirection);
                        direction9.showline(gRenderer);
                        direction9.render(characterpositionx+45,characterpositiony-2,gRenderer);
                        break; }  }
          break;
        case 1:

                         if (uzibullet.bulletremain())
                         {
                             weapons.changefirespeed(uzibullet.speed());
                             uzibullet.decreasebullet();
                             Mix_PlayChannel( -1, UZI, 0 );
                             switch(characterdirection)
                             {case 0:
                                direction1.changestart(0,0);
                                direction1.changelength(353,353);
                                direction1.UZIhit(zombie,characterdirection);
                                direction1.changeUZIfinaloutput(zombie,uzibullet,characterdirection);
                                direction1.showline(gRenderer);
                                direction1.render(characterpositionx-30,characterpositiony+25,gRenderer);
                                break;
                             case 1:
                                direction2.changestart(0,0);
                                direction2.changelength(0,500);
                                direction2.UZIhit(zombie,characterdirection);
                                direction2.changeUZIfinaloutput(zombie,uzibullet,characterdirection);
                                direction2.showline(gRenderer);
                                direction2.render(characterpositionx-30,characterpositiony+50,gRenderer);
                                break;
                             case 2:
                                direction3.changestart(0,0);
                                direction3.changelength(-353,353);
                                direction3.UZIhit(zombie,characterdirection);
                                direction3.changeUZIfinaloutput(zombie,uzibullet,characterdirection);
                                direction3.showline(gRenderer);
                                direction3.render(characterpositionx+30,characterpositiony+50,gRenderer);
                                break;
                             case 3:
                                direction4.changestart(0,0);
                                direction4.changelength(500,0);
                                direction4.UZIhit(zombie,characterdirection);
                                direction4.changeUZIfinaloutput(zombie,uzibullet,characterdirection);
                                direction4.showline(gRenderer);
                                direction4.render(characterpositionx-70,characterpositiony-15,gRenderer);
                                break;
                             case 4:
                                direction6.changestart(0,0);
                                direction6.changelength(-500,0);
                                direction6.UZIhit(zombie,characterdirection);
                                direction6.changeUZIfinaloutput(zombie,uzibullet,characterdirection);
                                direction6.showline(gRenderer);
                                direction6.render(characterpositionx+52,characterpositiony+25,gRenderer);
                                break;
                             case 5:
                                direction7.changestart(0,0);
                                direction7.changelength(353,-353);
                                direction7.UZIhit(zombie,characterdirection);
                                direction7.changeUZIfinaloutput(zombie,uzibullet,characterdirection);
                                direction7.showline(gRenderer);
                                direction7.render(characterpositionx-25,characterpositiony-20,gRenderer);
                                break;
                            case 6:
                                direction8.changestart(0,0);
                                direction8.changelength(0,-500);
                                direction8.UZIhit(zombie,characterdirection);
                                direction8.changeUZIfinaloutput(zombie,uzibullet,characterdirection);
                                direction8.showline(gRenderer);
                                direction8.render(characterpositionx+15,characterpositiony-15,gRenderer);
                                break;
                            case 7:
                                direction9.changestart(0,0);
                                direction9.changelength(-353,-353);
                                direction9.UZIhit(zombie,characterdirection);
                                direction9.changeUZIfinaloutput(zombie,uzibullet,characterdirection);
                                direction9.showline(gRenderer);
                                direction9.render(characterpositionx+45,characterpositiony-2,gRenderer);
                                break;} }
           break;
        case 2:
                        if (shotgunbullet.bulletremain())
                        {
                            weapons.changefirespeed(shotgunbullet.speed());
                            Mix_PlayChannel( -1, shotgun, 0 );
                            shotgunbullet.decreasebullet();
                            switch(characterdirection)
                            {
                            case 0:
                                direction1.changestart(0,5);
                                direction1.changelength(176,176);
                                direction1.shotgunhit(zombie,characterdirection);
                                direction1.changeshotgunfinaloutput(zombie,shotgunbullet,characterdirection);
                                direction1.showshotgunline(gRenderer);
                                direction1.render(characterpositionx-40,characterpositiony+40,gRenderer);break;
                            case 1:
                                direction2.changestart(10,0);
                                direction2.changelength(0,250);
                                direction2.shotgunhit(zombie,characterdirection);
                                direction2.changeshotgunfinaloutput(zombie,shotgunbullet,characterdirection);
                                direction2.showshotgunline(gRenderer);
                                direction2.render(characterpositionx-25,characterpositiony+50,gRenderer);break;
                            case 2:
                                direction3.changestart(0,0);
                                direction3.changelength(-176,176);
                                direction3.shotgunhit(zombie,characterdirection);
                                direction3.changeshotgunfinaloutput(zombie,shotgunbullet,characterdirection);
                                direction3.showshotgunline(gRenderer);
                                direction3.render(characterpositionx+30,characterpositiony+50,gRenderer);break;
                            case 3:
                                direction4.changestart(0,10);
                                direction4.changelength(250,0);
                                direction4.shotgunhit(zombie,characterdirection);
                                direction4.changeshotgunfinaloutput(zombie,shotgunbullet,characterdirection);
                                direction4.showshotgunline(gRenderer);
                                direction4.render(characterpositionx-70,characterpositiony-5,gRenderer);break;
                            case 4:
                                direction6.changestart(5,10);
                                direction6.changelength(-250,0);
                                direction6.shotgunhit(zombie,characterdirection);
                                direction6.changeshotgunfinaloutput(zombie,shotgunbullet,characterdirection);
                                direction6.showshotgunline(gRenderer);
                                direction6.render(characterpositionx+62,characterpositiony+35,gRenderer);break;
                            case 5:
                                direction7.changestart(0,0);
                                direction7.changelength(176,-176);
                                direction7.shotgunhit(zombie,characterdirection);
                                direction7.changeshotgunfinaloutput(zombie,shotgunbullet,characterdirection);
                                direction7.showshotgunline(gRenderer);
                                direction7.render(characterpositionx-30,characterpositiony-15,gRenderer);break;
                            case 6:
                                direction8.changestart(0,0);
                                direction8.changelength(0,-250);
                                direction8.shotgunhit(zombie,characterdirection);
                                direction8.changeshotgunfinaloutput(zombie,shotgunbullet,characterdirection);
                                direction8.showshotgunline(gRenderer);
                                direction8.render(characterpositionx+15,characterpositiony-15,gRenderer);break;
                            case 7:
                                direction9.changestart(0,15);
                                direction9.changelength(-176,-176);
                                direction9.shotgunhit(zombie,characterdirection);
                                direction9.changeshotgunfinaloutput(zombie,shotgunbullet,characterdirection);
                                direction9.showshotgunline(gRenderer);
                                direction9.render(characterpositionx+53,characterpositiony+1,gRenderer); break;
                           }
          break;
        case 3:
                    if (generadebullet.bulletremain())
                    {

                        if (generade0.generadeaction==false)
                        {
                          weapons.changefirespeed(generadebullet.speed());
                          generadebullet.decreasebullet();
                         generade0.generadeaction=true;
                         generade0.setgeneradedirection(characterdirection);
                         weapons.changefirespeed(generadebullet.speed());
                         generade0.setoriginalcharacterpositionx(characterpositionx+camera.x);
                         generade0.setoriginalcharacterpositiony(characterpositiony+camera.y);
                        }
                        else if (generade1.generadeaction==false)
                        {
                         weapons.changefirespeed(generadebullet.speed());
                          generadebullet.decreasebullet();
                         generade1.generadeaction=true;
                          generade1.setgeneradedirection(characterdirection);
                         weapons.changefirespeed(generadebullet.speed());
                         generade1.setoriginalcharacterpositionx(characterpositionx);
                         generade1.setoriginalcharacterpositiony(characterpositiony);
                        }

                    }

         break;
        case 4:
            weapons.changefirespeed(11);
            if (bucketwall.action(dot1.getPosX(),dot1.getPosY()))
            {
                if (wallbullet.bulletremain())
            {
                Mix_PlayChannel( -1, barrel, 0 );
               bucketwall.putwall(dot1.getPosX(),dot1.getPosY());
               wallbullet.decreasebullet();
            }
            }
            break;

        case 6:

                   if (atombombbullet.bulletremain())
                   {
                    weapons.changefirespeed(atombombbullet.speed());
                    atombombbullet.decreasebullet();
                    if (atombomb.bombing==false)
                   {

                      atombomb.bombing=true;
                   }

                   }

            break;
        case 5:
                   if (shieldbullet.bulletremain())
                   {

                       if (!protectshield.acting())
                       {
                           protectshield.resetlasttime(dot1.getPosX()-80,dot1.getPosY()-60);
                           shieldbullet.decreasebullet();
                       }
                   }
                   break;

                        }




				        }

				    }


				}
                //魔王火球
                fireballcountdown--;
                if (fireballcountdown==0)
                {
                    fireballcountdown=200;
                    if (ball[0].getacting()==false)
                    {
                         ball[0].start(bosspositionx,bosspositiony,dot1.getPosX(),dot1.getPosY());
                    }
                    else if (ball[1].getacting()==false)
                    {
                        ball[1].start(bosspositionx,bosspositiony,dot1.getPosX(),dot1.getPosY());
                    }
                    if (ball[2].getacting()==false)
                    {
                        ball[2].start(bosspositionx,bosspositiony,dot1.getPosX()+150*(ramdom%5)+100,dot1.getPosY()+150*(ramdom%5)+100);
                    }
                    else if (ball[3].getacting()==false)
                    {
                        ball[3].start(bosspositionx,bosspositiony,dot1.getPosX()+150*(ramdom%3)+100,dot1.getPosY()+150*(ramdom%3)+100);
                    }
                    if (ball[4].getacting()==false)
                    {
                        ball[4].start(bosspositionx,bosspositiony,dot1.getPosX()-150*(ramdom%4)-100,dot1.getPosY()-150*(ramdom%4)-100);
                    }
                    else if (ball[5].getacting()==false)
                    {
                        ball[5].start(bosspositionx,bosspositiony,dot1.getPosX()-150*(ramdom%6)-100,dot1.getPosY()-150*(ramdom%6)-100);
                    }
                }
                if (fireballcountdown==100)
                {

                    if (ball[6].getacting()==false)
                    {
                         ball[6].start(2000,800,dot1.getPosX(),dot1.getPosY());
                    }
                    else if (ball[7].getacting()==false)
                    {
                        ball[7].start(2000,800,dot1.getPosX(),dot1.getPosY());
                    }
                    if (ball[8].getacting()==false)
                    {
                        ball[8].start(2000,800,dot1.getPosX()+150*(ramdom%5)+100,dot1.getPosY()+150*(ramdom%5)+100);
                    }
                    else if (ball[9].getacting()==false)
                    {
                        ball[9].start(2000,800,dot1.getPosX()+150*(ramdom%3)+100,dot1.getPosY()+150*(ramdom%3)+100);
                    }
                    if (ball[10].getacting()==false)
                    {
                        ball[10].start(2000,800,dot1.getPosX()-150*(ramdom%4)-100,dot1.getPosY()-150*(ramdom%4)-100);
                    }
                    else if (ball[11].getacting()==false)
                    {
                        ball[11].start(2000,800,dot1.getPosX()-150*(ramdom%6)-100,dot1.getPosY()-150*(ramdom%6)-100);
                    }
                }



                for (int i=0;i<=11;i++)
                {
                    if (ball[i].getacting()) ball[i].render(dot1.getPosX(),dot1.getPosY(),camera.x,camera.y,dot1,gRenderer);
                }







                //武器+換武器
				if (currentKeyStates[ SDL_SCANCODE_M ])
                {   if (weapons.getweaponchangeconstant()==0)
                  {
                    weapons.changeweapon();
                    weapons.setweaponchangeconstant(20);
                  }
                }

       // load 子彈
      //武器+換武器
                if (!weapons.firespeedzero()) weapons.decreasefirespeed();
                if (weapons.getweaponchangeconstant()!=0) weapons.decreaseweaponchangeconstant();
                switch(weapons.getweaponmode())
                {
                case 0:
                         if( !pistrolbullet.loadFromRenderedText( pistrolbullet.weaponremainging, textColor,gFont,gRenderer ) )   printf( "Failed to render text texture!\n" );
                         pistrolbullet.render( characterpositionx+10-15, characterpositiony-16,gRenderer );break;
                case 1:
                        if( !uzibullet.loadFromRenderedText( uzibullet.weaponremainging, textColor,gFont,gRenderer ) )   printf( "Failed to render text texture!\n" );
                         uzibullet.render( characterpositionx+10-15, characterpositiony-16,gRenderer );break;
                case 2:
                         if( !shotgunbullet.loadFromRenderedText( shotgunbullet.weaponremainging, textColor,gFont,gRenderer ) )   printf( "Failed to render text texture!\n" );
                         shotgunbullet.render( characterpositionx+10-15, characterpositiony-16,gRenderer );break;
                case 3:
                        if( !generadebullet.loadFromRenderedText( generadebullet.weaponremainging, textColor,gFont,gRenderer ) )   printf( "Failed to render text texture!\n" );
                        generadebullet.render( characterpositionx+10-15, characterpositiony-16 ,gRenderer);break;
                case 4:
                        if( !wallbullet.loadFromRenderedText( wallbullet.weaponremainging, textColor,gFont,gRenderer ) )   printf( "Failed to render text texture!\n" );
                        wallbullet.render( characterpositionx+10-15, characterpositiony-16 ,gRenderer);break;
                case 5:
                        if( !shieldbullet.loadFromRenderedText( shieldbullet.weaponremainging, textColor, gFont,gRenderer ) )   printf( "Failed to render text texture!\n" );
                        shieldbullet.render( characterpositionx+10-15, characterpositiony-16,gRenderer );break;
                case 6:
                         if( !atombombbullet.loadFromRenderedText( atombombbullet.weaponremainging, textColor, gFont,gRenderer ) )   printf( "Failed to render text texture!\n" );
                        atombombbullet.render( characterpositionx+10-15, characterpositiony-16,gRenderer );break;

                }




                 if (generade0.generadeaction==true) generade0.render(generade,30,0,camera.x,camera.y,generadebullet,zombie,gRenderer);
                 if (generade1.generadeaction==true) generade1.render(generade,30,0,camera.x,camera.y,generadebullet,zombie,gRenderer);
                 if (atombomb.bombing)
                 {
                     if (atombomb.bursting())
                       {
                           atombomb.changerect();
                           atombomb.render(&atombomb.bombsize,gRenderer);
                           atombomb.bombing=true;
                           atombomb.increse();
                       }
                       else
                       {
                           for (int i=0;i<zombie_number;i++)
                           {
                               zombie[i].hurt(200,1);
                           }
                           atombomb.resetatom();
                           atombomb.bombsize.h=0;
                           atombomb.bombsize.w=0;
                           atombomb.bombing=false;
                       }
                 }
                 if (protectshield.acting())
                {
                    protectshield.render(camera.x,camera.y,gRenderer,dot1);
                }



                if (scoreupgrade.getrendering()==true)
                {
                    scoreupgrade.upgrade(weapons,pistrolbullet,uzibullet,shotgunbullet,generade0,generade1,generadebullet,ball);
                    scoreupgrade.loadFromRenderedText(textColor,scoreFont,gRenderer);
                    scoreupgrade.rendertext(200,SCREEN_HEIGHT/2,gRenderer);
                }
                scoreupgrade.judgescore();
                scoreupgrade.loadFromRenderedscore(textColor,scoreFont,gRenderer);
                scoreupgrade.renderscore(SCREEN_WIDTH/2,0+40,gRenderer);



		for(int i=0; i<zombie_number;i++){
     if(zombie[i].getDie()!=1){
        if(zombie[i].getHealth()<=0) { zombie[i].setDie(1); }
        else{

          switch(zombie[i].getDirection()){
                   case 1 :
                          currentTexture[i][0] = moveTexture[1][1];
                          currentTexture[i][1] = moveTexture[1][2];
                          currentTexture[i][2] = moveTexture[1][3];

                       break;
                   case 2 :
                          currentTexture[i][0] = moveTexture[2][1];
                          currentTexture[i][1] = moveTexture[2][2];
                          currentTexture[i][2] = moveTexture[2][3];


                       break;
                   case 3 :
                          currentTexture[i][0] = moveTexture[3][1];
                          currentTexture[i][1] = moveTexture[3][2];
                          currentTexture[i][2] = moveTexture[3][3];


                       break;
                   case 4 :
                          currentTexture[i][0] = moveTexture[4][1];
                          currentTexture[i][1] = moveTexture[4][2];
                          currentTexture[i][2] = moveTexture[4][3];


                       break;
                   case 6 :
                          currentTexture[i][0] = moveTexture[6][1];
                          currentTexture[i][1] = moveTexture[6][2];
                          currentTexture[i][2] = moveTexture[6][3];


                       break;
                   case 7 :
                          currentTexture[i][0] = moveTexture[7][1];
                          currentTexture[i][1] = moveTexture[7][2];
                          currentTexture[i][2] = moveTexture[7][3];


                       break;
                   case 8 :
                          currentTexture[i][0] = moveTexture[8][1];
                          currentTexture[i][1] = moveTexture[8][2];
                          currentTexture[i][2] = moveTexture[8][3];


                       break;
                   case 9 :
                          currentTexture[i][0] = moveTexture[9][1];
                          currentTexture[i][1] = moveTexture[9][2];
                          currentTexture[i][2] = moveTexture[9][3];


                       break;

             }
            for(int j=0;j<3;j++) currentTexture[i][j].setWidth(zombie_width);
            for(int j=0;j<3;j++) currentTexture[i][j].setHeight(zombie_height);
            zombie[i].addCounter();
            zombie[i].render( camera.x, camera.y, currentTexture[i][(zombie[i].getCounter()/10)%3],gRenderer );

      }
     }

	}
    if(dot1.getHealth()<=0){  //dying
        currentTexture1[0] = dieTexture1[1];
        currentTexture1[1] = dieTexture1[2];
        currentTexture1[2] = dieTexture1[3];
        mouse.loadFromFile( "gameover.png",gRenderer );
        mouse.surfacerender(&mouse.gameover,gRenderer);
        SDL_RenderPresent( gRenderer );
        SDL_Delay( 2000 );
        close();
        quit=true;
    }



    else if(dot1.getmoving() == 1 ){   // moving
        switch(weapons.getweaponmode()+1){
        case 1 :
            switch(dot1.getDirection()){
                   case 1 :
                         currentTexture1[0] = moveTexture1[1][1][1];
                         currentTexture1[1] = moveTexture1[1][1][2];
                         currentTexture1[2] = moveTexture1[1][1][3];

                       break;
                   case 2 :
                        currentTexture1[0] = moveTexture1[1][2][1];
                        currentTexture1[1] = moveTexture1[1][2][2];
                        currentTexture1[2] = moveTexture1[1][2][3];

                       break;
                   case 3 :
                        currentTexture1[0] = moveTexture1[1][3][1];
                        currentTexture1[1] = moveTexture1[1][3][2];
                        currentTexture1[2] = moveTexture1[1][3][3];

                       break;
                   case 4 :
                         currentTexture1[0] = moveTexture1[1][4][1];
                         currentTexture1[1] = moveTexture1[1][4][2];
                         currentTexture1[2] = moveTexture1[1][4][3];

                       break;
                   case 6 :
                          currentTexture1[0] = moveTexture1[1][6][1];
                          currentTexture1[1] = moveTexture1[1][6][2];
                          currentTexture1[2] = moveTexture1[1][6][3];

                       break;
                   case 7 :
                          currentTexture1[0] = moveTexture1[1][7][1];
                          currentTexture1[1] = moveTexture1[1][7][2];
                          currentTexture1[2] = moveTexture1[1][7][3];

                       break;
                   case 8 :
                          currentTexture1[0] = moveTexture1[1][8][1];
                          currentTexture1[1] = moveTexture1[1][8][2];
                          currentTexture1[2] = moveTexture1[1][8][3];

                       break;
                   case 9 :
                        currentTexture1[0] = moveTexture1[1][9][1];
                        currentTexture1[1] = moveTexture1[1][9][2];
                        currentTexture1[2] = moveTexture1[1][9][3];

                       break;

             }  break ;  //break for weapon switch

       case 2 :
            switch(dot1.getDirection()){
                   case 1 :
                         currentTexture1[0] = moveTexture1[2][1][1];
                         currentTexture1[1] = moveTexture1[2][1][2];
                         currentTexture1[2] = moveTexture1[2][1][3];

                       break;
                   case 2 :
                        currentTexture1[0] = moveTexture1[2][2][1];
                        currentTexture1[1] = moveTexture1[2][2][2];
                        currentTexture1[2] = moveTexture1[2][2][3];

                       break;
                   case 3 :
                        currentTexture1[0] = moveTexture1[2][3][1];
                        currentTexture1[1] = moveTexture1[2][3][2];
                        currentTexture1[2] = moveTexture1[2][3][3];

                       break;
                   case 4 :
                         currentTexture1[0] = moveTexture1[2][4][1];
                         currentTexture1[1] = moveTexture1[2][4][2];
                         currentTexture1[2] = moveTexture1[2][4][3];

                       break;
                   case 6 :
                          currentTexture1[0] = moveTexture1[2][6][1];
                          currentTexture1[1] = moveTexture1[2][6][2];
                          currentTexture1[2] = moveTexture1[2][6][3];

                       break;
                   case 7 :
                          currentTexture1[0] = moveTexture1[2][7][1];
                          currentTexture1[1] = moveTexture1[2][7][2];
                          currentTexture1[2] = moveTexture1[2][7][3];

                       break;
                   case 8 :
                          currentTexture1[0] = moveTexture1[2][8][1];
                          currentTexture1[1] = moveTexture1[2][8][2];
                          currentTexture1[2] = moveTexture1[2][8][3];

                       break;
                   case 9 :
                        currentTexture1[0] = moveTexture1[2][9][1];
                        currentTexture1[1] = moveTexture1[2][9][2];
                        currentTexture1[2] = moveTexture1[2][9][3];

                       break;

             }  break ;  //break for weapon switch

      case 3 :
            switch(dot1.getDirection()){
                   case 1 :
                         currentTexture1[0] = moveTexture1[3][1][1];
                         currentTexture1[1] = moveTexture1[3][1][2];
                         currentTexture1[2] = moveTexture1[3][1][3];

                       break;
                   case 2 :
                        currentTexture1[0] = moveTexture1[3][2][1];
                        currentTexture1[1] = moveTexture1[3][2][2];
                        currentTexture1[2] = moveTexture1[3][2][3];

                       break;
                   case 3 :
                        currentTexture1[0] = moveTexture1[3][3][1];
                        currentTexture1[1] = moveTexture1[3][3][2];
                        currentTexture1[2] = moveTexture1[3][3][3];

                       break;
                   case 4 :
                         currentTexture1[0] = moveTexture1[3][4][1];
                         currentTexture1[1] = moveTexture1[3][4][2];
                         currentTexture1[2] = moveTexture1[3][4][3];

                       break;
                   case 6 :
                          currentTexture1[0] = moveTexture1[3][6][1];
                          currentTexture1[1] = moveTexture1[3][6][2];
                          currentTexture1[2] = moveTexture1[3][6][3];

                       break;
                   case 7 :
                          currentTexture1[0] = moveTexture1[3][7][1];
                          currentTexture1[1] = moveTexture1[3][7][2];
                          currentTexture1[2] = moveTexture1[3][7][3];

                       break;
                   case 8 :
                          currentTexture1[0] = moveTexture1[3][8][1];
                          currentTexture1[1] = moveTexture1[3][8][2];
                          currentTexture1[2] = moveTexture1[3][8][3];

                       break;
                   case 9 :
                        currentTexture1[0] = moveTexture1[3][9][1];
                        currentTexture1[1] = moveTexture1[3][9][2];
                        currentTexture1[2] = moveTexture1[3][9][3];

                       break;
             }  break ;  //break for weapon switch

       default :
            switch(dot1.getDirection()){
                   case 1 :
                         currentTexture1[0] = moveTexture1[0][1][1];
                         currentTexture1[1] = moveTexture1[0][1][2];
                         currentTexture1[2] = moveTexture1[0][1][3];

                       break;
                   case 2 :
                        currentTexture1[0] = moveTexture1[0][2][1];
                        currentTexture1[1] = moveTexture1[0][2][2];
                        currentTexture1[2] = moveTexture1[0][2][3];

                       break;
                   case 3 :
                        currentTexture1[0] = moveTexture1[0][3][1];
                        currentTexture1[1] = moveTexture1[0][3][2];
                        currentTexture1[2] = moveTexture1[0][3][3];

                       break;
                   case 4 :
                         currentTexture1[0] = moveTexture1[0][4][1];
                         currentTexture1[1] = moveTexture1[0][4][2];
                         currentTexture1[2] = moveTexture1[0][4][3];

                       break;
                   case 6 :
                          currentTexture1[0] = moveTexture1[0][6][1];
                          currentTexture1[1] = moveTexture1[0][6][2];
                          currentTexture1[2] = moveTexture1[0][6][3];

                       break;
                   case 7 :
                          currentTexture1[0] = moveTexture1[0][7][1];
                          currentTexture1[1] = moveTexture1[0][7][2];
                          currentTexture1[2] = moveTexture1[0][7][3];

                       break;
                   case 8 :
                          currentTexture1[0] = moveTexture1[0][8][1];
                          currentTexture1[1] = moveTexture1[0][8][2];
                          currentTexture1[2] = moveTexture1[0][8][3];

                       break;
                   case 9 :
                        currentTexture1[0] = moveTexture1[0][9][1];
                        currentTexture1[1] = moveTexture1[0][9][2];
                        currentTexture1[2] = moveTexture1[0][9][3];

                       break;
             }  break ;  //break for weapon switch
        }
    }
    else {  // not moving
        switch(weapons.getweaponmode()+1){
        case 1 :
            switch(dot1.getDirection()){
                   case 1 :
                         currentTexture1[0] = moveTexture1[1][1][2];
                         currentTexture1[1] = moveTexture1[1][1][2];
                         currentTexture1[2] = moveTexture1[1][1][2];

                       break;
                   case 2 :
                        currentTexture1[0] = moveTexture1[1][2][2];
                        currentTexture1[1] = moveTexture1[1][2][2];
                        currentTexture1[2] = moveTexture1[1][2][2];

                       break;
                   case 3 :
                        currentTexture1[0] = moveTexture1[1][3][2];
                        currentTexture1[1] = moveTexture1[1][3][2];
                        currentTexture1[2] = moveTexture1[1][3][2];

                       break;
                   case 4 :
                         currentTexture1[0] = moveTexture1[1][4][2];
                         currentTexture1[1] = moveTexture1[1][4][2];
                         currentTexture1[2] = moveTexture1[1][4][2];

                       break;
                   case 6 :
                          currentTexture1[0] = moveTexture1[1][6][2];
                          currentTexture1[1] = moveTexture1[1][6][2];
                          currentTexture1[2] = moveTexture1[1][6][2];

                       break;
                   case 7 :
                          currentTexture1[0] = moveTexture1[1][7][2];
                          currentTexture1[1] = moveTexture1[1][7][2];
                          currentTexture1[2] = moveTexture1[1][7][2];

                       break;
                   case 8 :
                          currentTexture1[0] = moveTexture1[1][8][2];
                          currentTexture1[1] = moveTexture1[1][8][2];
                          currentTexture1[2] = moveTexture1[1][8][2];

                       break;
                   case 9 :
                        currentTexture1[0] = moveTexture1[1][9][2];
                        currentTexture1[1] = moveTexture1[1][9][2];
                        currentTexture1[2] = moveTexture1[1][9][2];

                       break;

             }  break ;  //break for weapon switch

       case 2 :
            switch(dot1.getDirection()){
                   case 1 :
                         currentTexture1[0] = moveTexture1[2][1][2];
                         currentTexture1[1] = moveTexture1[2][1][2];
                         currentTexture1[2] = moveTexture1[2][1][2];

                       break;
                   case 2 :
                        currentTexture1[0] = moveTexture1[2][2][2];
                        currentTexture1[1] = moveTexture1[2][2][2];
                        currentTexture1[2] = moveTexture1[2][2][2];

                       break;
                   case 3 :
                        currentTexture1[0] = moveTexture1[2][3][2];
                        currentTexture1[1] = moveTexture1[2][3][2];
                        currentTexture1[2] = moveTexture1[2][3][2];

                       break;
                   case 4 :
                         currentTexture1[0] = moveTexture1[2][4][2];
                         currentTexture1[1] = moveTexture1[2][4][2];
                         currentTexture1[2] = moveTexture1[2][4][2];

                       break;
                   case 6 :
                          currentTexture1[0] = moveTexture1[2][6][2];
                          currentTexture1[1] = moveTexture1[2][6][2];
                          currentTexture1[2] = moveTexture1[2][6][2];

                       break;
                   case 7 :
                          currentTexture1[0] = moveTexture1[2][7][2];
                          currentTexture1[1] = moveTexture1[2][7][2];
                          currentTexture1[2] = moveTexture1[2][7][2];

                       break;
                   case 8 :
                          currentTexture1[0] = moveTexture1[2][8][2];
                          currentTexture1[1] = moveTexture1[2][8][2];
                          currentTexture1[2] = moveTexture1[2][8][2];

                       break;
                   case 9 :
                        currentTexture1[0] = moveTexture1[2][9][2];
                        currentTexture1[1] = moveTexture1[2][9][2];
                        currentTexture1[2] = moveTexture1[2][9][2];

                       break;

             }  break ;  //break for weapon switch

      case 3 :
            switch(dot1.getDirection()){
                   case 1 :
                         currentTexture1[0] = moveTexture1[3][1][2];
                         currentTexture1[1] = moveTexture1[3][1][2];
                         currentTexture1[2] = moveTexture1[3][1][2];

                       break;
                   case 2 :
                        currentTexture1[0] = moveTexture1[3][2][2];
                        currentTexture1[1] = moveTexture1[3][2][2];
                        currentTexture1[2] = moveTexture1[3][2][2];

                       break;
                   case 3 :
                        currentTexture1[0] = moveTexture1[3][3][2];
                        currentTexture1[1] = moveTexture1[3][3][2];
                        currentTexture1[2] = moveTexture1[3][3][2];

                       break;
                   case 4 :
                         currentTexture1[0] = moveTexture1[3][4][2];
                         currentTexture1[1] = moveTexture1[3][4][2];
                         currentTexture1[2] = moveTexture1[3][4][2];

                       break;
                   case 6 :
                          currentTexture1[0] = moveTexture1[3][6][2];
                          currentTexture1[1] = moveTexture1[3][6][2];
                          currentTexture1[2] = moveTexture1[3][6][2];

                       break;
                   case 7 :
                          currentTexture1[0] = moveTexture1[3][7][2];
                          currentTexture1[1] = moveTexture1[3][7][2];
                          currentTexture1[2] = moveTexture1[3][7][2];

                       break;
                   case 8 :
                          currentTexture1[0] = moveTexture1[3][8][2];
                          currentTexture1[1] = moveTexture1[3][8][2];
                          currentTexture1[2] = moveTexture1[3][8][2];

                       break;
                   case 9 :
                        currentTexture1[0] = moveTexture1[3][9][2];
                        currentTexture1[1] = moveTexture1[3][9][2];
                        currentTexture1[2] = moveTexture1[3][9][2];

                       break;
             }  break ;  //break for weapon switch

       default :
            switch(dot1.getDirection()){
                   case 1 :
                         currentTexture1[0] = moveTexture1[0][1][2];
                         currentTexture1[1] = moveTexture1[0][1][2];
                         currentTexture1[2] = moveTexture1[0][1][2];

                       break;
                   case 2 :
                        currentTexture1[0] = moveTexture1[0][2][2];
                        currentTexture1[1] = moveTexture1[0][2][2];
                        currentTexture1[2] = moveTexture1[0][2][2];

                       break;
                   case 3 :
                        currentTexture1[0] = moveTexture1[0][3][2];
                        currentTexture1[1] = moveTexture1[0][3][2];
                        currentTexture1[2] = moveTexture1[0][3][2];

                       break;
                   case 4 :
                         currentTexture1[0] = moveTexture1[0][4][2];
                         currentTexture1[1] = moveTexture1[0][4][2];
                         currentTexture1[2] = moveTexture1[0][4][2];

                       break;
                   case 6 :
                          currentTexture1[0] = moveTexture1[0][6][2];
                          currentTexture1[1] = moveTexture1[0][6][2];
                          currentTexture1[2] = moveTexture1[0][6][2];

                       break;
                   case 7 :
                          currentTexture1[0] = moveTexture1[0][7][2];
                          currentTexture1[1] = moveTexture1[0][7][2];
                          currentTexture1[2] = moveTexture1[0][7][2];

                       break;
                   case 8 :
                          currentTexture1[0] = moveTexture1[0][8][2];
                          currentTexture1[1] = moveTexture1[0][8][2];
                          currentTexture1[2] = moveTexture1[0][8][2];

                       break;
                   case 9 :
                        currentTexture1[0] = moveTexture1[0][9][2];
                        currentTexture1[1] = moveTexture1[0][9][2];
                        currentTexture1[2] = moveTexture1[0][9][2];

                       break;
             }  break ;  //break for weapon switch
        }
    }








             //--------------------------------------                --------------- //-------------------------------------





				currentTexture1[0].setWidth(hero_width);
				currentTexture1[0].setHeight(hero_height);
				currentTexture1[1].setWidth(hero_width);
				currentTexture1[1].setHeight(hero_height);
				currentTexture1[2].setWidth(hero_width);
				currentTexture1[2].setHeight(hero_height);

				dot1.addCounter();
                for (int i=0;i<=59;i++)
                {
                    for (int j=0;j<=19;j++)
                        bucketwall.renderwall(camera,gRenderer,wTexture,i,j);
                                        }
                                          for(int i=0;i<16;i++){
                  hitthered=false;
                  hitthered=RED.hitthered(dot1,i);

                  if (hitthered==true){if( RED.pos_xy_red[i]==true){weapons.supplementweapon(ramdom,uzibullet,shotgunbullet,generadebullet,wallbullet,shieldbullet,atombombbullet);}//start=clock();}
                  RED.pos_xy_red[i]=false;

                   }


				}
				if(countred==4000){for(int i=0;i<16;i++){RED.pos_xy_red[i]=true; }}

                RED.renderredbox(camera,gRenderer,redboxTexture);





   }		dot1.render( camera.x, camera.y, currentTexture1[(dot1.getCounter()/10)%3],gRenderer );
            countred++;











				//Update screen

				SDL_RenderPresent( gRenderer );
			}
		}

	}
	//Free resources and close SDL
	close();

	return 0;
}
