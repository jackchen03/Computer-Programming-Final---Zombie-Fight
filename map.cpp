#include"map.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <string>
#include<iostream>

using namespace std;
Dot::Dot()
{
    //Initialize the offsets
    mPosX = LEVEL_WIDTH1/2;
    mPosY = LEVEL_HEIGHT1-100;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    direction = 4;
    moving = 0;
    characterhealth = 100;
}

void Dot1::handleEvent( SDL_Rect &camera,SDL_Renderer* gRenderer,LTexture& wTexture,SDL_Event& e, bucket& bucketwall )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
           // case SDLK_g: bucketwall.pos_xy_wall[mPosX/40][mPosY/63]=true;

        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;

        }
        }
}


void Dot::move( int camX, int camY,bucket & bucketwall, Dot& d)
{
    //Move the dot left or right
    mPosX += mVelX;
   if(mPosX==d.mPosX&&mPosY==d.mPosY){mPosX-=mVelX;}
    cantgo(bucketwall,camX,camY );//barrier
    //boundary of map
    if(  (mPosX < 0 ) || ( mPosX + DOT_WIDTH > LEVEL_WIDTH1 ) )
    {
        if((mPosX<LEVEL_WIDTH1/2-6*DOT_WIDTH)||(mPosX>LEVEL_WIDTH1/2+6*DOT_WIDTH)&&((mPosY<4*DOT_HEIGHT)&&(mPosY>0))||((mPosY>LEVEL_HEIGHT1-5*DOT_HEIGHT)&&(mPosY<LEVEL_HEIGHT1-DOT_HEIGHT)))
          {
              mPosX-=mVelX;
           }



        //Move back
       else { mPosX -= mVelX;}

    }

    //Move the dot up or down
    mPosY += mVelY;
   if(mPosX==d.mPosX&&mPosY==d.mPosY){mPosY-=mVelY;}
   cantgo(bucketwall,camX,camY);
    //If the dot went too far up or down
    if( ( mPosY < 4*DOT_HEIGHT ) || ( mPosY + 5*DOT_HEIGHT > LEVEL_HEIGHT1 ) )
    {
       //Move back
       if((mPosX>LEVEL_WIDTH1/2-6*DOT_WIDTH)&&(mPosX<LEVEL_WIDTH1/2+6*DOT_WIDTH))
       { if( ( mPosY < 0) || ( mPosY + DOT_HEIGHT > LEVEL_HEIGHT1 ) )
        mPosY-=mVelY;
       }

        else {mPosY -= mVelY;}


    }

}

void Dot:: cantgo(bucket & bucketwall,int camX, int camY){
    int i=0,j=0;

for(i=0;i<LEVEL_WIDTH1/40;i++){
        for(j=0;j<LEVEL_HEIGHT1/63;j++){
    if (((bucketwall.pos_xy_wall[i][j+1]==true))&&i==mPosX/40&&j==mPosY/63) {  mPosX -= mVelX;mPosY -= mVelY;}

}
}
}




void Dot::render( int camX, int camY,LTexture&gDotTexture, SDL_Renderer* gRenderer )
{
    //Show the dot relative to the camera
	gDotTexture.render( mPosX - camX, mPosY - camY,gRenderer );
    if (characterhealth>=0)
    {
       SDL_Rect fillRect = { mPosX - camX, mPosY - camY-35, (50*characterhealth)/100, 15};
       if (characterhealth>=50)SDL_SetRenderDrawColor( gRenderer, 0, 255, 0, 0xFF );
       else if (characterhealth>=20)SDL_SetRenderDrawColor( gRenderer, 255, 140, 0, 0xFF );
       else SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 0xFF );

	   SDL_RenderFillRect( gRenderer, &fillRect );
    }


	SDL_Rect outlineRect = { mPosX - camX, mPosY - camY-35, 50, 15 };
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );
    SDL_RenderDrawRect( gRenderer, &outlineRect );
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
}


int Dot::getPosX()
{
	return mPosX;
}

int Dot::getPosY()
{
	return mPosY;
}
int Dot::get_relative_pos_x(SDL_Rect& camera){  int temp=0;temp=mPosX-camera.x;}
int Dot::get_relative_pos_y(SDL_Rect& camera){  int temp=0;temp=mPosY-camera.y;}

bool Dot::loadMediaMove(SDL_Renderer* gRenderer,LTexture moveTexture[4][10][3]){
    //Loading success flag
	bool success = true;

    if( !moveTexture[1][1][1].loadFromFile( "pistol 11.png" , gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][1][2].loadFromFile( "pistol 12.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][1][3].loadFromFile( "pistol 13.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][2][1].loadFromFile( "pistol 21.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][2][2].loadFromFile( "pistol 22.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][2][3].loadFromFile( "pistol 23.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

    if( !moveTexture[1][3][1].loadFromFile( "pistol 31.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][3][2].loadFromFile( "pistol 32.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][3][3].loadFromFile( "pistol 33.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][4][1].loadFromFile( "pistol 41.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][4][2].loadFromFile( "pistol 42.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][4][3].loadFromFile( "pistol 43.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][6][1].loadFromFile( "pistol 61.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][6][2].loadFromFile( "pistol 62.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][6][3].loadFromFile( "pistol 63.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][7][1].loadFromFile( "pistol 71.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][7][2].loadFromFile( "pistol 72.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][7][3].loadFromFile( "pistol 73.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][8][1].loadFromFile( "pistol 81.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][8][2].loadFromFile( "pistol 82.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][8][3].loadFromFile( "pistol 83.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][9][1].loadFromFile( "pistol 91.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][9][2].loadFromFile( "pistol 92.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[1][9][3].loadFromFile( "pistol 93.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

    if( !moveTexture[2][1][1].loadFromFile( "UZI 11.png" , gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][1][2].loadFromFile( "UZI 12.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][1][3].loadFromFile( "UZI 13.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][2][1].loadFromFile( "UZI 21.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][2][2].loadFromFile( "UZI 22.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][2][3].loadFromFile( "UZI 23.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

    if( !moveTexture[2][3][1].loadFromFile( "UZI 31.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][3][2].loadFromFile( "UZI 32.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][3][3].loadFromFile( "UZI 33.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][4][1].loadFromFile( "UZI 41.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][4][2].loadFromFile( "UZI 42.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][4][3].loadFromFile( "UZI 43.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][6][1].loadFromFile( "UZI 61.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][6][2].loadFromFile( "UZI 62.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][6][3].loadFromFile( "UZI 63.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][7][1].loadFromFile( "UZI 71.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][7][2].loadFromFile( "UZI 72.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][7][3].loadFromFile( "UZI 73.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][8][1].loadFromFile( "UZI 81.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][8][2].loadFromFile( "UZI 82.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][8][3].loadFromFile( "UZI 83.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][9][1].loadFromFile( "UZI 91.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][9][2].loadFromFile( "UZI 92.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[2][9][3].loadFromFile( "UZI 93.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	 if( !moveTexture[3][1][1].loadFromFile( "shotgun 11.png" , gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][1][2].loadFromFile( "shotgun 12.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][1][3].loadFromFile( "shotgun 13.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][2][1].loadFromFile( "shotgun 21.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][2][2].loadFromFile( "shotgun 22.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][2][3].loadFromFile( "shotgun 23.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

    if( !moveTexture[3][3][1].loadFromFile( "shotgun 31.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][3][2].loadFromFile( "shotgun 32.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][3][3].loadFromFile( "shotgun 33.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][4][1].loadFromFile( "shotgun 41.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][4][2].loadFromFile( "shotgun 42.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][4][3].loadFromFile( "shotgun 43.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][6][1].loadFromFile( "shotgun 61.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][6][2].loadFromFile( "shotgun 62.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][6][3].loadFromFile( "shotgun 63.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][7][1].loadFromFile( "shotgun 71.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][7][2].loadFromFile( "shotgun 72.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][7][3].loadFromFile( "shotgun 73.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][8][1].loadFromFile( "shotgun 81.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][8][2].loadFromFile( "shotgun 82.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][8][3].loadFromFile( "shotgun 83.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][9][1].loadFromFile( "shotgun 91.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][9][2].loadFromFile( "shotgun 92.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[3][9][3].loadFromFile( "shotgun 93.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	 if( !moveTexture[0][1][1].loadFromFile( "nothing 11.png" , gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][1][2].loadFromFile( "nothing 12.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][1][3].loadFromFile( "nothing 13.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
	if( !moveTexture[0][2][1].loadFromFile( "nothing 21.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][2][2].loadFromFile( "nothing 22.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][2][3].loadFromFile( "nothing 23.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

    if( !moveTexture[0][3][1].loadFromFile( "nothing 31.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][3][2].loadFromFile( "nothing 32.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][3][3].loadFromFile( "nothing 33.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][4][1].loadFromFile( "nothing 41.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][4][2].loadFromFile( "nothing 42.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][4][3].loadFromFile( "nothing 43.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][6][1].loadFromFile( "nothing 61.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][6][2].loadFromFile( "nothing 62.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][6][3].loadFromFile( "nothing 63.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][7][1].loadFromFile( "nothing 71.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][7][2].loadFromFile( "nothing 72.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][7][3].loadFromFile( "nothing 73.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][8][1].loadFromFile( "nothing 81.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][8][2].loadFromFile( "nothing 82.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][8][3].loadFromFile( "nothing 83.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][9][1].loadFromFile( "nothing 91.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][9][2].loadFromFile( "nothing 92.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !moveTexture[0][9][3].loadFromFile( "nothing 93.png", gRenderer ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	return success;

}



bucket::bucket()
{


	wTexture=NULL;

	for(int i=0;i<LEVEL_WIDTH1/40;i++)for(int j=0;j<LEVEL_HEIGHT1/63;j++){pos_xy_wall[i][j]=false;}
}

bucket::~bucket()
{
    freewall();
}




void bucket::freewall()
{
    if( wTexture != NULL )
    {
        SDL_DestroyTexture( wTexture );
		wTexture = NULL;

    }
}

/*bool bucket::loadFromFilebucket( std::string path,SDL_Renderer* gRenderer )
{
    freebucket();
    freewall();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else
    {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );

        SDL_FreeSurface( loadedSurface );
    }
    bTexture = newTexture;
    return bTexture != NULL;

}

/*bool bucket::loadFromFilewall( std::string path,SDL_Renderer* gRenderer )
{
    freewall();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else
    {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );

        SDL_FreeSurface( loadedSurface );
    }
    wTexture = newTexture;
    return wTexture != NULL;
}*/



void bucket::putwall(int x,int y)
{
     pos_xy_wall[x/40][y/63]=true;
     time_xy_wall[x/40][y/63]=1000;
}

bool bucket::action(int x,int y)
{
    if (pos_xy_wall[x/40][y/63]==false) return true;
    else return false;
}



void bucket::renderwall( SDL_Rect &camera,SDL_Renderer* gRenderer,LTexture& wTexture,int i,int j, SDL_Rect* clip)
{  if (pos_xy_wall[i][j]==true/*&&pos_xy_bucket[i][j]==false*/){
    int mposx=0,mposy=0;
    mposx=i*40;
    mposy=j*63;
    int x=mposx-camera.x;int y=mposy-camera.y;
    wTexture.render(x, y,gRenderer );
    time_xy_wall[i][j]--;
}
   if (time_xy_wall[i][j]==0) pos_xy_wall[i][j]=false;
}

 redbox::redbox(){
for(int i=0;i<15;i++){pos_xy_red[i]=true;}
for(int i=0;i<2;i++){posxofred[i]=(LEVEL_WIDTH1-600)-300*i;}
for(int i=2;i<4;i++){posxofred[i]=300*i;}
posxofred[4]=posxofred[0];
posxofred[8]= posxofred[1];
posxofred[12]=posxofred[2];
posxofred[5]=posxofred[3];
posxofred[9]= posxofred[0];
posxofred[13]=posxofred[1];
posxofred[6]=posxofred[2];
posxofred[10]= posxofred[3];
posxofred[14]=posxofred[0];
posxofred[7]=posxofred[1];
posxofred[11]= posxofred[2];
posxofred[15]=posxofred[3];
for(int i=0;i<2;i++){
posyofred[4*i]=(LEVEL_HEIGHT1-300)-200*i;}
for(int i=2;i<4;i++){
posyofred[4*i]=(200)+100*i;}
posyofred[1]=posyofred[0];
posyofred[2]= posyofred[0];
posyofred[3]=posyofred[0];
posyofred[5]=posyofred[4];
posyofred[6]= posyofred[4];
posyofred[7]=posyofred[4];
posyofred[9]=posyofred[8];
posyofred[10]= posyofred[8];
posyofred[11]=posyofred[8];
posyofred[13]=posyofred[12];
posyofred[14]= posyofred[12];
posyofred[15]=posyofred[12];





 }
/*

 void redbox :: collision(Dot&dot){



 }*/


void redbox::renderredbox( SDL_Rect &camera,SDL_Renderer* gRenderer,LTexture&redTexture){



for(int i=0;i<16;i++){if(pos_xy_red[i]==true)

    {   int x=0,y=0;
        x=posxofred[i]-camera.x;
       y=posyofred[i]-camera.y;
        redTexture.render(x,y,gRenderer);

}

}

}


bool redbox:: hitthered(Dot1& dot,int i){
  //Let's e xamine the x axis first:
  //If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
  if( (posxofred[i]>= dot.getPosX() && posxofred[i]<= (dot.getPosX()+ 40)) ||
      ((posxofred[i]  + 40) >= dot.getPosX()) &&( (posxofred[i] +40) <= (dot.getPosX() +40))){
    //Now we look at the y axis:
    if( (posyofred[i] >= dot.getPosY() && posyofred[i] <= (dot.getPosY()+ 63)) ||
      ((posyofred[i]  + 63) >= dot.getPosY()) &&( (posyofred[i]  +63) <= (dot.getPosY() +63))){
      //The sprites appear to overlap.
      return true;
    }
  }}


/*
bool redbox:: hitthered(Dot1& dot,int i){
if( ((posxofred[i] >= dot.getPosX()) &&( posxofred[i] <= (dot.getPosX()+ 63))) || (((posxofred[i]+ 45) >= dot.getPosX()) &&( (posxofred[i]  +45) <= (dot.getPosX()() +63)))){
    //Now we look at the y axis:
    if( (posyofred[i] == dot.getPosY()) ||((posyofred[i]  + 41) >= dot.getPosY()) &&( (posyofred[i] +41) <= dot.getPosY() )){
      //The sprites appear to overlap.
      return true;





}}};
*/





