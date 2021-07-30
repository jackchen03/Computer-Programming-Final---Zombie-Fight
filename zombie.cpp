#include"zombie.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <string>


zombie::zombie()
{
    //Initialize the offsets
    mPosX = LEVEL_WIDTH1/2-DOT_WIDTH;
    mPosY = LEVEL_HEIGHT1/2;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    direction = 4;
    moving = 0;
    health = 100;
    die = 0;

}
int zombie::get_relative_pos_x(SDL_Rect& camera){  int temp=0;temp=mPosX-camera.x;}
int zombie::get_relative_pos_y(SDL_Rect& camera){  int temp=0;temp=mPosY-camera.y;}

void zombie::handleEvent( SDL_Rect &camera,SDL_Renderer* gRenderer,LTexture& wTexture, bucket& bucketwall )
{


        //Adjust the velocity
        switch( direction )
        {
            case 8: mVelY =- DOT_VEL; mVelX = 0; break;
            case 2: mVelY = DOT_VEL; mVelX = 0; break;
            case 4: mVelX =- DOT_VEL; mVelY = 0; break;
            case 6: mVelX = DOT_VEL; mVelY = 0; break;
            case 9: mVelY =- DOT_VEL; mVelX = DOT_VEL; break;
            case 3: mVelY = DOT_VEL; mVelX = DOT_VEL; break;
            case 7: mVelY =- DOT_VEL; mVelX = -DOT_VEL; break;
            case 1: mVelY = DOT_VEL; mVelX = -DOT_VEL; break;



        }


}


void zombie::move( int camX, int camY,bucket & bucketwall, Dot& d)
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
bool zombie:: collision(zombie& zombie){
  //Let's e xamine the x axis first:
  //If the leftmost or rightmost point of the first sprite lies somewhere inside the second, continue.
  if( (mPosX >= zombie.getPosX() && mPosX <= (zombie.getPosX()+ 40)) ||
      ((mPosX  + 40) >= zombie.getPosX()) &&( (mPosX  +40) <= (zombie.getPosX() +40))){
    //Now we look at the y axis:
    if( (mPosY >= zombie.getPosY() && mPosY <= (zombie.getPosY()+ 63)) ||
      ((mPosY  + 63) >= zombie.getPosY()) &&( (mPosY  +63) <= (zombie.getPosY() +63))){
      //The sprites appear to overlap.
      return true;
    }
  }}


void zombie:: cantgo(bucket & bucketwall,int camX, int camY){
    int i=0,j=0;

  for(i=0;i<LEVEL_WIDTH1/40;i++){
        for(j=0;j<LEVEL_HEIGHT1/63;j++){
    if (((bucketwall.pos_xy_wall[i][j]==true))&&i==mPosX/40&&j==mPosY/63) {  mPosX -= mVelX;mPosY -= mVelY;}

         }
  }
}


void zombie::render( int camX, int camY,LTexture&gDotTexture, SDL_Renderer* gRenderer )
{


    //Show the dot relative to the camera
	gDotTexture.render( mPosX - camX, mPosY - camY,gRenderer );

}


int zombie::getPosX()
{
	return mPosX;
}

int zombie::getPosY()
{
	return mPosY;
}

bool zombie::loadMediaMove(SDL_Renderer* gRenderer, LTexture moveTexture[10][3])
{    bool success = true;

     if( !moveTexture[1][1].loadFromFile( "move 1-1.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[1][2].loadFromFile( "move 1-2.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[1][3].loadFromFile( "move 1-3.png", gRenderer ) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }

	 if( !moveTexture[2][1].loadFromFile( "move 2-1.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[2][2].loadFromFile( "move 2-2.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[2][3].loadFromFile( "move 2-3.png", gRenderer ) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }

	 if( !moveTexture[3][1].loadFromFile( "move 3-1.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[3][2].loadFromFile( "move 3-2.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[3][3].loadFromFile( "move 3-3.png", gRenderer ) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }

	 if( !moveTexture[4][1].loadFromFile( "move 4-1.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[4][2].loadFromFile( "move 4-2.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[4][3].loadFromFile( "move 4-3.png", gRenderer ) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }

	 if( !moveTexture[6][1].loadFromFile( "move 6-1.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[6][2].loadFromFile( "move 6-2.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[6][3].loadFromFile( "move 6-3.png", gRenderer ) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }

	 if( !moveTexture[7][1].loadFromFile( "move 7-1.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[7][2].loadFromFile( "move 7-2.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[7][3].loadFromFile( "move 7-3.png", gRenderer ) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }

	 if( !moveTexture[8][1].loadFromFile( "move 8-1.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[8][2].loadFromFile( "move 8-2.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[8][3].loadFromFile( "move 8-3.png", gRenderer ) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }

	 if( !moveTexture[9][1].loadFromFile( "move 9-1.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[9][2].loadFromFile( "move 9-2.png" , gRenderer) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }
	 if( !moveTexture[9][3].loadFromFile( "move 9-3.png", gRenderer ) )
	 {
		printf( "Failed to load press texture!\n" );
		success = false;
	 }




     return success;




}

