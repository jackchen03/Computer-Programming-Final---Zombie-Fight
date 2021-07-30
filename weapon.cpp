#include"weapon.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <string>
#include"map.h"
#include<cmath>
#include <SDL_mixer.h>

extern const int SCREEN_WIDTH = 1200;
extern const int SCREEN_HEIGHT = 750;


const int zombienumber=20;





atom::atom()
{
    mTexture=NULL;
    mWidth = 0;
	mHeight = 0;
	bombsize.h=10;
	bombsize.w=10;
	bombing=false;
	amplify=0;
}

atom::~atom()
{
    free();
}

bool atom::loadFromFile( std::string path ,SDL_Renderer* gRenderer)
{
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void atom::free()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void atom::render(SDL_Rect* clip,SDL_Renderer* gRenderer)
{
   SDL_Rect renderQuad = {SCREEN_WIDTH/2-bombsize.w/2 , SCREEN_HEIGHT/2-bombsize.h/2, mWidth, mHeight };
   renderQuad.w = bombsize.w;
   renderQuad.h = bombsize.h;
   SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

void atom::changerect()
{   if (bombsize.w<200)
    {
      bombsize.w=200;
      bombsize.h=150;
    }
    else
    {
       bombsize.w+=SCREEN_WIDTH/20;
       bombsize.h+=SCREEN_HEIGHT/20;
    }

}




showgenerade::showgenerade()
{
    mTexture = NULL;
    gTexture=NULL;
    hTexture=NULL;
	mWidth = 0;
	mHeight = 0;
	generadeaction=false;
	generademotion=0;
	damagecountdown=2;
	upgrade=false;
}

showgenerade::~showgenerade()
{
    free();
}

void showgenerade::free()
{
    if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		SDL_DestroyTexture( gTexture );
		SDL_DestroyTexture( hTexture );
		mTexture = NULL;
		gTexture=NULL;
        hTexture=NULL;
		mWidth = 0;
		mHeight = 0;
		gWidth = 0;
        gHeight = 0;

	}
}

bool showgenerade::loadFromFile(std::string path,SDL_Renderer* gRenderer)
{
    SDL_DestroyTexture( mTexture );
	mWidth = 0;
    mHeight = 0;
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else
    {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    mTexture = newTexture;
    return mTexture != NULL;

}

bool showgenerade::loadFromFileflash1(std::string path,SDL_Renderer* gRenderer)
{
    SDL_DestroyTexture( gTexture );
    gWidth = 0;
    gHeight = 0;
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else
    {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        else
        {
            gWidth = loadedSurface->w;
            gHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    gTexture = newTexture;
    return gTexture != NULL;
}

bool showgenerade::loadFromFileflash2(std::string path,SDL_Renderer* gRenderer)
{
    SDL_DestroyTexture( hTexture );
    hWidth = 0;
    hHeight = 0;
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else
    {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        else
        {
            hWidth = loadedSurface->w;
            hHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    hTexture = newTexture;
    return hTexture != NULL;
}

void showgenerade::showburst1(int x,int y,SDL_Renderer* gRenderer,SDL_Rect* clip)
{
    SDL_Rect renderQuad = { x+originalcharacterpositionx+generadepositionx-70, y+originalcharacterpositiony+generadepositiony-50, gWidth, gHeight };
    SDL_RenderCopy( gRenderer, gTexture, clip, &renderQuad );
}

void showgenerade::showburst2(Mix_Chunk * &UZI,int x,int y,int camx,int camy,zombie(&zombie)[zombienumber],showbullet &generadebullet,SDL_Renderer* gRenderer,SDL_Rect* clip)
{
    SDL_Rect renderQuad = { x+originalcharacterpositionx+generadepositionx-95, y+originalcharacterpositiony+generadepositiony-80, hWidth, hHeight };
    SDL_RenderCopy( gRenderer, hTexture, clip, &renderQuad );
    int bombx=x+originalcharacterpositionx+generadepositionx-95;
    int bomby=y+originalcharacterpositiony+generadepositiony-80;
    if (damagecountdown==0)
    {
        damagecountdown=2;
        for (int i=0;i<zombienumber;i++)
        {
             Mix_PlayChannel( -1, UZI, 0 );
            if (zombie[i].getDie()!=1)
        {

             if (zombie[i].zombiepositionx-bombx>=0&&zombie[i].zombiepositionx-bombx<30) if (zombie[i].zombiepositiony-bomby>=(-30)&&zombie[i].zombiepositiony-bomby<(-10)) zombie[i].hurt(generadebullet.decreaseblood(),6);
            if (zombie[i].zombiepositionx-bombx>=(-10)&&zombie[i].zombiepositionx-bombx<30) if (zombie[i].zombiepositiony-bomby>=(-10)&&zombie[i].zombiepositiony-bomby<110) zombie[i].hurt(generadebullet.decreaseblood(),6);
            if (zombie[i].zombiepositionx-bombx>=30&&zombie[i].zombiepositionx-bombx<150) if (zombie[i].zombiepositiony-bomby>=(-30)&&zombie[i].zombiepositiony-bomby<(-10)) zombie[i].hurt(generadebullet.decreaseblood(),2);
            if (zombie[i].zombiepositionx-bombx>=30&&zombie[i].zombiepositionx-bombx<150) if (zombie[i].zombiepositiony-bomby>=(-10)&&zombie[i].zombiepositiony-bomby<110) zombie[i].hurt(generadebullet.decreaseblood(),8);
            if (zombie[i].zombiepositionx-bombx>=150&&zombie[i].zombiepositionx-bombx<180) if (zombie[i].zombiepositiony-bomby>=(-30)&&zombie[i].zombiepositiony-bomby<(-10)) zombie[i].hurt(generadebullet.decreaseblood(),4);
            if (zombie[i].zombiepositionx-bombx>=150&&zombie[i].zombiepositionx-bombx<190) if (zombie[i].zombiepositiony-bomby>=(-10)&&zombie[i].zombiepositiony-bomby<110) zombie[i].hurt(generadebullet.decreaseblood(),4);
        }

        }

    }
    else damagecountdown--;
}

int showgenerade::damage()
{
    if (damageupgrage==false) return 80;
    else return 150;
}

void showgenerade::render(Mix_Chunk * &UZI,int x,int y,int camerax,int cameray,showbullet &generadebullet,zombie(&zombie)[zombienumber],SDL_Renderer* gRenderer, SDL_Rect* clip)
{
    SDL_Rect renderQuad = { x+originalcharacterpositionx+generadepositionx-camerax, y+originalcharacterpositiony+generadepositiony-cameray, mWidth, mHeight };

    if (generademotion<=53) SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
    if (generademotion<=66)
    {
        switch(generadedirection)
        {
        case 0:
            if (generademotion<=1) generadepositiony+=8;
            else if (generademotion<=2) generadepositiony+=7;
            else if (generademotion<=4) generadepositiony+=6;
            else if (generademotion<=5) generadepositiony+=5;
            else if (generademotion<=7) generadepositiony+=4;
            else if (generademotion<=9) generadepositiony+=4;
            else if (generademotion<=11) generadepositiony+=3;
            else if (generademotion<=13) generadepositiony+=3;
            else if (generademotion<=15) generadepositiony+=2;
            else if (generademotion<=17) generadepositiony+=1;
            else if (generademotion<=20) generadepositiony+=5;
            else if (generademotion<=22) generadepositiony+=5;
            else if (generademotion<=24) generadepositiony+=4;
            else if (generademotion<=25) generadepositiony+=3;
            else if (generademotion<=27) generadepositiony+=1;
            else if (generademotion<=28) ;
            else if (generademotion<=29) generadepositiony+=4;
            else if (generademotion<=30) generadepositiony+=3;
            else if (generademotion<=32) generadepositiony+=3;
            else if (generademotion<=34) generadepositiony+=2;
            else if (generademotion<=37) generadepositiony-=1;
            else if (generademotion<=39) generadepositiony+=3;
            if (generademotion<=8) generadepositionx-=3;
            if (generademotion<=11) generadepositionx-=1;
            if (generademotion<=23) generadepositionx-=2;
            if (generademotion<=24) generadepositionx-=0;
            if (generademotion<=40) generadepositionx-=1;
            generademotion++; break;
        case 1:
            if (generademotion<=15) generadepositiony+=5;
            else if (generademotion<=16) generadepositiony+=1;
            else if (generademotion<=28) generadepositiony+=3;
            else if (generademotion<=30) generadepositiony+=1;
            else if (generademotion<=40) generadepositiony+=2;
            else if (generademotion<=45) generadepositiony+=1;
            generademotion++; break;
        case 2:
            if (generademotion<=1) generadepositiony+=8;
            else if (generademotion<=2) generadepositiony+=7;
            else if (generademotion<=4) generadepositiony+=6;
            else if (generademotion<=5) generadepositiony+=5;
            else if (generademotion<=7) generadepositiony+=4;
            else if (generademotion<=9) generadepositiony+=4;
            else if (generademotion<=11) generadepositiony+=3;
            else if (generademotion<=13) generadepositiony+=3;
            else if (generademotion<=15) generadepositiony+=2;
            else if (generademotion<=17) generadepositiony+=1;
            else if (generademotion<=20) generadepositiony+=5;
            else if (generademotion<=22) generadepositiony+=5;
            else if (generademotion<=24) generadepositiony+=4;
            else if (generademotion<=25) generadepositiony+=3;
            else if (generademotion<=27) generadepositiony+=1;
            else if (generademotion<=28) ;
            else if (generademotion<=29) generadepositiony+=4;
            else if (generademotion<=30) generadepositiony+=3;
            else if (generademotion<=32) generadepositiony+=3;
            else if (generademotion<=34) generadepositiony+=2;
            else if (generademotion<=37) generadepositiony-=1;
            else if (generademotion<=39) generadepositiony+=3;
            if (generademotion<=8) generadepositionx+=3;
            if (generademotion<=11) generadepositionx+=1;
            if (generademotion<=23) generadepositionx+=2;
            if (generademotion<=24) generadepositionx+=0;
            if (generademotion<=40) generadepositionx+=1;
            generademotion++; break;
        case 3:
            if (generademotion<=1) {generadepositiony=-2; }
            else if(generademotion<=4) generadepositiony--;
            else if(generademotion<=6) ;
            else if(generademotion<=8) generadepositiony++;
            else if(generademotion<=11) generadepositiony+=2;
            else if(generademotion<=13) generadepositiony+=3;
            else if(generademotion<=15) generadepositiony+=4;
            else if(generademotion<=17) generadepositiony+=5;
            else if(generademotion<=19) generadepositiony+=6;
            else if(generademotion<=20) generadepositiony-=4;
            else if(generademotion<=21) generadepositiony-=3;
            else if(generademotion<=22) generadepositiony-=2;
            else if(generademotion<=23) generadepositiony--;
            else if(generademotion<=24) generadepositiony++;
            else if(generademotion<=25) generadepositiony+=2;
            else if(generademotion<=26) generadepositiony+=3;
            else if(generademotion<=27) generadepositiony+=4;
            else if(generademotion<=28) generadepositiony-=3;
            else if(generademotion<=29) generadepositiony--;
            else if(generademotion<=30) generadepositiony++;
            else if(generademotion<=31) generadepositiony+=2;
            else if(generademotion<=32) generadepositiony++;
            else if(generademotion<=33) ;
            generademotion++;
            if (generademotion<=20)generadepositionx-=4;
            else if (generademotion<=30)generadepositionx-=3;
            else if (generademotion<=40)generadepositionx-=2;
            else if (generademotion<=45)generadepositionx-=1;
            break;
        case 4:
            if (generademotion<=1) {generadepositiony=-2; }
            else if(generademotion<=4) generadepositiony--;
            else if(generademotion<=6) ;
            else if(generademotion<=8) generadepositiony++;
            else if(generademotion<=11) generadepositiony+=2;
            else if(generademotion<=13) generadepositiony+=3;
            else if(generademotion<=15) generadepositiony+=4;
            else if(generademotion<=17) generadepositiony+=5;
            else if(generademotion<=19) generadepositiony+=6;
            else if(generademotion<=20) generadepositiony-=4;
            else if(generademotion<=21) generadepositiony-=3;
            else if(generademotion<=22) generadepositiony-=2;
            else if(generademotion<=23) generadepositiony--;
            else if(generademotion<=24) generadepositiony++;
            else if(generademotion<=25) generadepositiony+=2;
            else if(generademotion<=26) generadepositiony+=3;
            else if(generademotion<=27) generadepositiony+=4;
            else if(generademotion<=28) generadepositiony-=3;
            else if(generademotion<=29) generadepositiony--;
            else if(generademotion<=30) generadepositiony++;
            else if(generademotion<=31) generadepositiony+=2;
            else if(generademotion<=32) generadepositiony++;
            else if(generademotion<=33) ;
            generademotion++;
            if (generademotion<=20)generadepositionx+=4;
            else if (generademotion<=30)generadepositionx+=3;
            else if (generademotion<=40)generadepositionx+=2;
            else if (generademotion<=45)generadepositionx+=1;
            break;
        case 5:
            if (generademotion<=1) generadepositiony-=5;
            else if (generademotion<=2) generadepositiony-=4;
            else if (generademotion<=4) generadepositiony-=4;
            else if (generademotion<=5) generadepositiony-=3;
            else if (generademotion<=7) generadepositiony-=3;
            else if (generademotion<=9) generadepositiony-=2;
            else if (generademotion<=11) generadepositiony-=1;
            else if (generademotion<=13) generadepositiony-=1;
            else if (generademotion<=15) generadepositiony+=1;
            else if (generademotion<=17) generadepositiony+=2;
            else if (generademotion<=20) generadepositiony-=3;
            else if (generademotion<=22) generadepositiony-=2;
            else if (generademotion<=24) generadepositiony-=2;
            else if (generademotion<=25) generadepositiony-=1;
            else if (generademotion<=27) ;
            else if (generademotion<=28) generadepositiony+=1;
            else if (generademotion<=29) generadepositiony-=3;
            else if (generademotion<=30) generadepositiony-=2;
            else if (generademotion<=32) generadepositiony-=2;
            else if (generademotion<=34) generadepositiony-=1;
            else if (generademotion<=37) generadepositiony+=1;
            else if (generademotion<=39) generadepositiony-=3;
            if (generademotion<=8) generadepositionx-=3;
            if (generademotion<=11) generadepositionx-=1;
            if (generademotion<=23) generadepositionx-=2;
            if (generademotion<=24) generadepositionx-=0;
            if (generademotion<=40) generadepositionx-=1;
            generademotion++; break;
        case 6:
            if (generademotion<=5) generadepositiony-=2;
            else if (generademotion<=15) generadepositiony-=5;
            else if (generademotion<=19) generadepositiony-=1;
            else if (generademotion<=25) generadepositiony-=3;
            else if (generademotion<=30) generadepositiony-=1;
            else if (generademotion<=38) generadepositiony-=2;
            else if (generademotion<=45) generadepositiony-=1;
            generademotion++; break;
        case 7:
            if (generademotion<=1) generadepositiony-=5;
            else if (generademotion<=2) generadepositiony-=4;
            else if (generademotion<=4) generadepositiony-=4;
            else if (generademotion<=5) generadepositiony-=3;
            else if (generademotion<=7) generadepositiony-=3;
            else if (generademotion<=9) generadepositiony-=2;
            else if (generademotion<=11) generadepositiony-=1;
            else if (generademotion<=13) generadepositiony-=1;
            else if (generademotion<=15) generadepositiony+=1;
            else if (generademotion<=17) generadepositiony+=2;
            else if (generademotion<=20) generadepositiony-=3;
            else if (generademotion<=22) generadepositiony-=2;
            else if (generademotion<=24) generadepositiony-=2;
            else if (generademotion<=25) generadepositiony-=1;
            else if (generademotion<=27) ;
            else if (generademotion<=28) generadepositiony+=1;
            else if (generademotion<=29) generadepositiony-=3;
            else if (generademotion<=30) generadepositiony-=2;
            else if (generademotion<=32) generadepositiony-=2;
            else if (generademotion<=34) generadepositiony-=1;
            else if (generademotion<=37) generadepositiony+=1;
            else if (generademotion<=39) generadepositiony-=3;
            if (generademotion<=8) generadepositionx+=3;
            if (generademotion<=11) generadepositionx+=1;
            if (generademotion<=23) generadepositionx+=2;
            if (generademotion<=24) generadepositionx+=0;
            if (generademotion<=40) generadepositionx+=1;
            generademotion++; break;

        }
       if ((generademotion>=61)&&(generademotion<=63)) showburst1(x-camerax,y-cameray,gRenderer);
       if ((generademotion>=64)&&(generademotion<=66)) showburst2(UZI,x-camerax,y-cameray,camerax,cameray,zombie,generadebullet,gRenderer);
    }
    else if (upgrade==false)
    {
        generademotion=0;
        generadepositionx=0;
        generadepositiony=0;
        generadeaction=false;
    }
    else
    {
        if (generademotion<=100)
        {
            SDL_Rect renderQuad1 = { x+originalcharacterpositionx-camerax+generadepositionx+2*(generademotion-66), y+originalcharacterpositiony-cameray+generadepositiony+2*(generademotion-66), mWidth, mHeight };
            SDL_Rect renderQuad2 = { x+originalcharacterpositionx-camerax+generadepositionx+2*(generademotion-66), y+originalcharacterpositiony+generadepositiony-cameray-2*(generademotion-66), mWidth, mHeight };
            SDL_Rect renderQuad3 = { x+originalcharacterpositionx-camerax+generadepositionx-2*(generademotion-66), y+originalcharacterpositiony+generadepositiony-cameray+2*(generademotion-66), mWidth, mHeight };
            SDL_Rect renderQuad4 = { x+originalcharacterpositionx-camerax+generadepositionx-2*(generademotion-66), y+originalcharacterpositiony+generadepositiony-cameray-2*(generademotion-66), mWidth, mHeight };
            SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad1 );
            SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad2 );
            SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad3 );
            SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad4 );
            generademotion++;
        }
        else if (generademotion<=103)
        {
            showburst1(x-camerax+2*(generademotion-66),y-cameray+2*(generademotion-66),gRenderer);
            showburst1(x-camerax+2*(generademotion-66),y-cameray-2*(generademotion-66),gRenderer);
            showburst1(x-camerax-2*(generademotion-66),y-cameray+2*(generademotion-66),gRenderer);
            showburst1(x-camerax-2*(generademotion-66),y-cameray-2*(generademotion-66),gRenderer);
            generademotion++;
        }
        else if (generademotion<=106)
        {
            showburst2(UZI,x-camerax+2*(generademotion-66),y-cameray+2*(generademotion-66),camerax,cameray,zombie,generadebullet,gRenderer);
            showburst2(UZI,x-camerax+2*(generademotion-66),y-cameray-2*(generademotion-66),camerax,cameray,zombie,generadebullet,gRenderer);
            showburst2(UZI,x-camerax-2*(generademotion-66),y-cameray+2*(generademotion-66),camerax,cameray,zombie,generadebullet,gRenderer);
            showburst2(UZI,x-camerax-2*(generademotion-66),y-cameray-2*(generademotion-66),camerax,cameray,zombie,generadebullet,gRenderer);
            generademotion++;
        }
        else
        {
        generademotion=0;
        generadepositionx=0;
        generadepositiony=0;
        generadeaction=false;
        }
    }
}

shield::shield()
{
    mTexture = NULL;
    mWidth = 0;
	mHeight = 0;

}

shield::~shield()
{
    free();
}

void shield::free()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

bool shield::loadFromFile(std::string path,SDL_Renderer* gRenderer)
{
    SDL_DestroyTexture( mTexture );
	mWidth = 0;
    mHeight = 0;
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else
    {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    mTexture = newTexture;
    return mTexture != NULL;

}

void shield::render(int camarax,int camaray,SDL_Renderer* gRenderer,Dot &dot1 ,SDL_Rect* clip)
{
    SDL_Rect renderQuad = { shieldpositionx-camarax, shieldpositiony-camaray, mWidth, mHeight };
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
    if (dot1.getPosX()+30-50-shieldpositionx>=(-80)&&dot1.getPosX()+30-50-shieldpositionx<=(-60)&&dot1.getPosY()-shieldpositiony+30>=25&&dot1.getPosY()-shieldpositiony+30<=85)dot1.changeHealth(100);
    if (dot1.getPosX()+30-50-shieldpositionx>=(-60)&&dot1.getPosX()+30-50-shieldpositionx<=115&&dot1.getPosY()-shieldpositiony+30>=(-10)&&dot1.getPosY()-shieldpositiony+30<=115)dot1.changeHealth(100);
    if (dot1.getPosX()+30-50-shieldpositionx>=(-40)&&dot1.getPosX()+30-50-shieldpositionx<=95&&dot1.getPosY()-shieldpositiony+30>=(-10)&&dot1.getPosY()-shieldpositiony+30<=25)dot1.changeHealth(100);
    if (dot1.getPosX()+30-50-shieldpositionx>=(115)&&dot1.getPosX()+30-50-shieldpositionx<=(135)&&dot1.getPosY()-shieldpositiony+30>=25&&dot1.getPosY()-shieldpositiony+30<=85)dot1.changeHealth(100);
}

bool shield::acting()
{
    if (shieldlasttime>0)
    {
        shieldlasttime--;
        return true;
    }
    return false;
}

void shield::resetlasttime(int x,int y)
{
    shieldlasttime=200;
    shieldpositionx=x;
    shieldpositiony=y;
}

showgun::showgun(int begingingx,int begingingy)
{
    characterpositionx=0;
    characterpositiony=0;
    startx=begingingx;
    starty=begingingy;
    zombiegethit=0;
}

void showgun::showline(SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0xFF );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+changex, characterpositiony+starty+endingy+changey, characterpositionx-startx+changex, characterpositiony+starty+changey);
}

void showgun::UZIhit(zombie (&zombie)[zombienumber],int characterdirection)
{
    switch(characterdirection)
    {
    case 0:
        zombiegethit=2000;
        for (int i=0;i<zombienumber;i++) zombie[i].zombiehit=false;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
               if ((zombie[i].zombiepositiony-characterpositiony>=10)&&(zombie[i].zombiepositiony-characterpositiony<=353))
            {
                if (((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)<=25)&&((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)>=-30))
                    zombie[i].zombiehit=true;
            }
            }
        }
          for (int i=0;i<zombienumber;i++)
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit>=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }


        break;
    case 1:
         zombiegethit=0;
        for(int i=0;i<zombienumber;i++) zombie[i].zombiehit=false;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if ((zombie[i].zombiepositiony-characterpositiony>=20)&&(zombie[i].zombiepositiony-characterpositiony<=500))
            {
                if ((zombie[i].zombiepositionx-characterpositionx<=(-5))&&(zombie[i].zombiepositionx-characterpositionx>=(-38)))
                    zombie[i].zombiehit=true;
            }
            }

        }
         for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit<=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }

        break;
    case 2:
          zombiegethit=2000;
          for (int i=0;i<zombienumber;i++) zombie[i].zombiehit=false;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if ((zombie[i].zombiepositiony-characterpositiony>=10)&&(zombie[i].zombiepositiony-characterpositiony<=353))
            {
                if (((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)>=(-35))&&((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)<=35))
                    zombie[i].zombiehit=true;
            }
            }
        }
        for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit>=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }

        break;
    case 3:
         zombiegethit=0;
        for (int i=0;i<zombienumber;i++) zombie[i].zombiehit=false;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if (((zombie[i].zombiepositionx-characterpositionx)>=(-500))&&((zombie[i].zombiepositionx-characterpositionx)<=(-10)))
            {
                if (((zombie[i].zombiepositiony-characterpositiony)>=(-37))&&((zombie[i].zombiepositiony-characterpositiony)<=(15)))
                    zombie[i].zombiehit=true;
            }
            }
        }
        for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit<=zombie[i].zombiepositionx) zombiegethit=zombie[i].zombiepositionx;
               }
           }

        break;
    case 4:
        zombiegethit=3000;
        for (int i=0;i<zombienumber;i++) zombie[i].zombiehit=false;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if (((zombie[i].zombiepositionx-characterpositionx)>=40)&&((zombie[i].zombiepositionx-characterpositionx)<=500))
            {
                if (((zombie[i].zombiepositiony-characterpositiony)>=(-15))&&((zombie[i].zombiepositiony-characterpositiony)<=(38)))
                    zombie[i].zombiehit=true;
            }
            }
        }
        for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit>=zombie[i].zombiepositionx) zombiegethit=zombie[i].zombiepositionx;
               }
           }


        break;
    case 5:
        zombiegethit=0;
        for(int i=0;i<zombienumber;i++) zombie[i].zombiehit=false;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if (((zombie[i].zombiepositiony-characterpositiony)<=0)&&((zombie[i].zombiepositiony-characterpositiony)>=(-353)))
            {
                if (((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)<=38)&&((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)>=(-35)))
                    zombie[i].zombiehit=true;
            }
            }
        }

        for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit<=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }


        break;
    case 6:
        zombiegethit=900;
        for(int i=0;i<zombienumber;i++) zombie[i].zombiehit=false;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
           {
               if ((zombie[i].zombiepositiony-characterpositiony>=(-500))&&(zombie[i].zombiepositiony-characterpositiony<=(-15)))
           {
               if ((zombie[i].zombiepositionx-characterpositionx<=38)&&(zombie[i].zombiepositionx-characterpositionx>=5)) zombie[i].zombiehit=true;
           }
           }
        }
           for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit>=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }


        break;
    case 7:
        zombiegethit=0;
        for(int i=0;i<zombienumber;i++) zombie[i].zombiehit=false;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if (((zombie[i].zombiepositiony-characterpositiony)<=0)&&((zombie[i].zombiepositiony-characterpositiony)>=(-353)))
            {
                if (((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)<=70)&&((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)>=12))
                    zombie[i].zombiehit=true;
            }
            }

        }
        for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit<=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }


        break;
    }

}

void showgun::pistrolhit(zombie (&zombie)[zombienumber],int characterdirection)
{
    for (int i=0;i<zombienumber;i++) zombie[i].zombiehit=false;
    switch(characterdirection)
    {
    case 0:
        zombiegethit=2000;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                 if ((zombie[i].zombiepositiony-characterpositiony>=10)&&(zombie[i].zombiepositiony-characterpositiony<=282))
            {
                if (((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)<=25)&&((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)>=-30))
                    zombie[i].zombiehit=true;
            }
            }

        }
          for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit>=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }
        break;
    case 1:
         zombiegethit=0;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if ((zombie[i].zombiepositiony-characterpositiony>=20)&&(zombie[i].zombiepositiony-characterpositiony<=400))
            {
                if ((zombie[i].zombiepositionx-characterpositionx<=(-5))&&(zombie[i].zombiepositionx-characterpositionx>=(-38)))
                    zombie[i].zombiehit=true;
            }
            }
        }

         for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit<=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }



        break;
    case 2:
          zombiegethit=2000;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if ((zombie[i].zombiepositiony-characterpositiony>=10)&&(zombie[i].zombiepositiony-characterpositiony<=282))
            {
                if (((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)>=(-35))&&((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)<=35))
                    zombie[i].zombiehit=true;
            }
            }
        }
        for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit>=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }
        break;
    case 3:
         zombiegethit=0;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if (((zombie[i].zombiepositionx-characterpositionx)>=(-400))&&((zombie[i].zombiepositionx-characterpositionx)<=(-10)))
            {
                if (((zombie[i].zombiepositiony-characterpositiony)>=(-37))&&((zombie[i].zombiepositiony-characterpositiony)<=(15)))
                    zombie[i].zombiehit=true;
            }
            }
        }
        for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit<=zombie[i].zombiepositionx) zombiegethit=zombie[i].zombiepositionx;
               }
           }


        break;
    case 4:
        zombiegethit=20000;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if (((zombie[i].zombiepositionx-characterpositionx)>=40)&&((zombie[i].zombiepositionx-characterpositionx)<=400))
            {
                if (((zombie[i].zombiepositiony-characterpositiony)>=(-15))&&((zombie[i].zombiepositiony-characterpositiony)<=(38)))
                    zombie[i].zombiehit=true;
            }
            }
        }
        for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit>=zombie[i].zombiepositionx) zombiegethit=zombie[i].zombiepositionx;
               }
           }


        break;
    case 5:
        zombiegethit=0;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if (((zombie[i].zombiepositiony-characterpositiony)<=0)&&((zombie[i].zombiepositiony-characterpositiony)>=(-282)))
            {
                if (((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)<=38)&&((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)>=(-35)))
                    zombie[i].zombiehit=true;
            }
            }
        }

        for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit<=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }

        break;
    case 6:
        zombiegethit=900;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
           {
               if ((zombie[i].zombiepositiony-characterpositiony>=(-400))&&(zombie[i].zombiepositiony-characterpositiony<=(-15)))
           {
               if ((zombie[i].zombiepositionx-characterpositionx<=38)&&(zombie[i].zombiepositionx-characterpositionx>=5)) zombie[i].zombiehit=true;
           }
           }
        }
           for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit>=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }


        break;
    case 7:
        zombiegethit=0;
        for (int i=0;i<zombienumber;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if (((zombie[i].zombiepositiony-characterpositiony)<=0)&&((zombie[i].zombiepositiony-characterpositiony)>=(-282)))
            {
                if (((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)<=70)&&((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)>=12))
                    zombie[i].zombiehit=true;
            }
            }
        }
        for (int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit<=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }


        break;
    }
}

void showgun::shotgunhit(zombie (&zombie)[zombienumber],int characterdirection)
{

    switch (characterdirection)
    {
    case 0:
        zombiegethit=2000;
        for (int i=0;i<=19;i++) zombie[i].zombiehit=false;
        for (int i=0;i<=19;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if (((zombie[i].zombiepositiony-characterpositiony)>=10)&&((zombie[i].zombiepositiony-characterpositiony)<=100))
            {
                if (((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)<=35)&&((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)>=-35))
                    zombie[i].zombiehit=true;
            }
            if (((zombie[i].zombiepositiony-characterpositiony)>=100)&&((zombie[i].zombiepositiony-characterpositiony)<=176))
            {
                if (((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)<=35)&&((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)>=-40))
                    zombie[i].zombiehit=true;
            }

            }
        }

        for (int i=0;i<=19;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit>=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }


        break;
    case 1:
        zombiegethit=0;
        for(int i=0;i<=19;i++) zombie[i].zombiehit=false;
        for (int i=0;i<=19;i++)
        {
            if (zombie[i].getDie()!=1)
           {
               if ((zombie[i].zombiepositiony-characterpositiony<=40)&&(zombie[i].zombiepositiony-characterpositiony>=0))
           {
               if ((zombie[i].zombiepositionx-characterpositionx<=23)&&(zombie[i].zombiepositionx-characterpositionx>=(-23))) zombie[i].zombiehit=true;
           }
           if ((zombie[i].zombiepositiony-characterpositiony<=60)&&(zombie[i].zombiepositiony-characterpositiony>=41))
           {
               if ((zombie[i].zombiepositionx-characterpositionx<=25)&&(zombie[i].zombiepositionx-characterpositionx>=(-25))) zombie[i].zombiehit=true;
           }
           if ((zombie[i].zombiepositiony-characterpositiony<=200)&&(zombie[i].zombiepositiony-characterpositiony>=61))
           {
               if ((zombie[i].zombiepositionx-characterpositionx<=30)&&(zombie[i].zombiepositionx-characterpositionx>=(-28))) zombie[i].zombiehit=true;
           }
           if ((zombie[i].zombiepositiony-characterpositiony<=250)&&(zombie[i].zombiepositiony-characterpositiony>=201))
           {
               if ((zombie[i].zombiepositionx-characterpositionx<=35)&&(zombie[i].zombiepositionx-characterpositionx>=(-30))) zombie[i].zombiehit=true;
           }
           }
        }
           for (int i=0;i<=19;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit<=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }

           break;
    case 2:
        zombiegethit=2000;
        for (int i=0;i<=19;i++) zombie[i].zombiehit=false;
        for (int i=0;i<=19;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if (((zombie[i].zombiepositiony-characterpositiony)>=10)&&((zombie[i].zombiepositiony-characterpositiony)<=100))
            {
                if (((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)<=35)&&((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)>=-38))
                    zombie[i].zombiehit=true;
            }
            if (((zombie[i].zombiepositiony-characterpositiony)>=100)&&((zombie[i].zombiepositiony-characterpositiony)<=176))
            {
                if (((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)<=38)&&((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)>=-40))
                    zombie[i].zombiehit=true;
            }
            }

        }

        for (int i=0;i<=19;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit>=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }


        break;
    case 3:
        zombiegethit=0;
        for (int i=0;i<=19;i++) zombie[i].zombiehit=false;
        for (int i=0;i<=19;i++)
        {
            if (zombie[i].getDie()!=1)
           {
               if ((zombie[i].zombiepositionx-characterpositionx>=(-40))&&(zombie[i].zombiepositionx-characterpositionx<=0))
           {
               if ((zombie[i].zombiepositiony-characterpositiony<=23)&&(zombie[i].zombiepositiony-characterpositiony>=(-23))) zombie[i].zombiehit=true;
           }
           if ((zombie[i].zombiepositionx-characterpositionx>=(-60))&&(zombie[i].zombiepositionx-characterpositionx<=(-41)))
           {
               if ((zombie[i].zombiepositiony-characterpositiony<=25)&&(zombie[i].zombiepositiony-characterpositiony>=(-25))) zombie[i].zombiehit=true;
           }
           if ((zombie[i].zombiepositionx-characterpositionx>=(-200))&&(zombie[i].zombiepositionx-characterpositionx<=(-61)))
           {
               if ((zombie[i].zombiepositiony-characterpositiony<=30)&&(zombie[i].zombiepositiony-characterpositiony>=(-28))) zombie[i].zombiehit=true;
           }
           if ((zombie[i].zombiepositionx-characterpositionx>=(-250))&&(zombie[i].zombiepositionx-characterpositionx<=(-201)))
           {
               if ((zombie[i].zombiepositiony-characterpositiony<=35)&&(zombie[i].zombiepositiony-characterpositiony>=(-30))) zombie[i].zombiehit=true;
           }
           }
        }

           for (int i=0;i<=19;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit<=zombie[i].zombiepositionx) zombiegethit=zombie[i].zombiepositionx;
               }
           }
        break;
    case 4:
        zombiegethit=3000;
        for (int i=0;i<=19;i++) zombie[i].zombiehit=false;
        for (int i=0;i<=19;i++)
        {
            if (zombie[i].getDie()!=1)
           {
               if ((zombie[i].zombiepositionx-characterpositionx<=40)&&(zombie[i].zombiepositionx-characterpositionx>=0))
           {
               if ((zombie[i].zombiepositiony-characterpositiony<=23)&&(zombie[i].zombiepositiony-characterpositiony>=(-23))) zombie[i].zombiehit=true;
           }
           if ((zombie[i].zombiepositionx-characterpositionx<=60)&&(zombie[i].zombiepositionx-characterpositionx>=41))
           {
               if ((zombie[i].zombiepositiony-characterpositiony<=25)&&(zombie[i].zombiepositiony-characterpositiony>=(-25))) zombie[i].zombiehit=true;
           }
           if ((zombie[i].zombiepositionx-characterpositionx<=200)&&(zombie[i].zombiepositionx-characterpositionx>=61))
           {
               if ((zombie[i].zombiepositiony-characterpositiony<=30)&&(zombie[i].zombiepositiony-characterpositiony>=(-28))) zombie[i].zombiehit=true;
           }
           if ((zombie[i].zombiepositionx-characterpositionx<=250)&&(zombie[i].zombiepositionx-characterpositionx>=201))
           {
               if ((zombie[i].zombiepositiony-characterpositiony<=35)&&(zombie[i].zombiepositiony-characterpositiony>=(-30))) zombie[i].zombiehit=true;
           }
           }
        }
           for (int i=0;i<=19;i++)
           {

               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit>=zombie[i].zombiepositionx) zombiegethit=zombie[i].zombiepositionx;
               }
           }
           break;
    case 5:
        zombiegethit=0;
        for(int i=0;i<=19;i++) zombie[i].zombiehit=false;
        for (int i=0;i<=19;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if (((zombie[i].zombiepositiony-characterpositiony)<=0)&&((zombie[i].zombiepositiony-characterpositiony)>=(-100)))
            {
                if (((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)<=35)&&((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)>=-35))
                    zombie[i].zombiehit=true;
            }
            if (((zombie[i].zombiepositiony-characterpositiony)>=(-176))&&((zombie[i].zombiepositiony-characterpositiony)<=(-100)))
            {
                if (((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)<=42)&&((zombie[i].zombiepositionx-characterpositionx-zombie[i].zombiepositiony+characterpositiony)>=-42))
                    zombie[i].zombiehit=true;
            }
            }

        }

        for (int i=0;i<=19;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit<=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }
        break;
    case 6:
        zombiegethit=900;
        for(int i=0;i<=19;i++) zombie[i].zombiehit=false;
        for (int i=0;i<=19;i++)
        {
            if (zombie[i].getDie()!=1)
           {
               if ((zombie[i].zombiepositiony-characterpositiony>=(-40))&&(zombie[i].zombiepositiony-characterpositiony<=0))
           {
               if ((zombie[i].zombiepositionx-characterpositionx<=23)&&(zombie[i].zombiepositionx-characterpositionx>=(-23))) zombie[i].zombiehit=true;
           }
           if ((zombie[i].zombiepositiony-characterpositiony>=(-60))&&(zombie[i].zombiepositiony-characterpositiony<=(-41)))
           {
               if ((zombie[i].zombiepositionx-characterpositionx<=25)&&(zombie[i].zombiepositionx-characterpositionx>=(-25))) zombie[i].zombiehit=true;
           }
           if ((zombie[i].zombiepositiony-characterpositiony>=(-200))&&(zombie[i].zombiepositiony-characterpositiony<=(-61)))
           {
               if ((zombie[i].zombiepositionx-characterpositionx<=30)&&(zombie[i].zombiepositionx-characterpositionx>=(-28))) zombie[i].zombiehit=true;
           }
           if ((zombie[i].zombiepositiony-characterpositiony>=(-250))&&(zombie[i].zombiepositiony-characterpositiony<=(-201)))
           {
               if ((zombie[i].zombiepositionx-characterpositionx<=35)&&(zombie[i].zombiepositionx-characterpositionx>=(-30))) zombie[i].zombiehit=true;
           }
           }
        }
           for (int i=0;i<=19;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit>=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }
           break;
    case 7:
        zombiegethit=0;
        for(int i=0;i<=19;i++) zombie[i].zombiehit=false;
        for (int i=0;i<=19;i++)
        {
            if (zombie[i].getDie()!=1)
            {
                if (((zombie[i].zombiepositiony-characterpositiony)<=0)&&((zombie[i].zombiepositiony-characterpositiony)>=(-100)))
            {
                if (((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)<=95)&&((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)>=20))
                    zombie[i].zombiehit=true;
            }
            if (((zombie[i].zombiepositiony-characterpositiony)>=(-176))&&((zombie[i].zombiepositiony-characterpositiony)<=(-100)))
            {
                if (((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)<=98)&&((zombie[i].zombiepositionx-characterpositionx+zombie[i].zombiepositiony-characterpositiony)>=20))
                    zombie[i].zombiehit=true;
            }
            }

        }

        for (int i=0;i<=19;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   if (zombiegethit<=zombie[i].zombiepositiony) zombiegethit=zombie[i].zombiepositiony;
               }
           }


        break;
    }
}

void showgun::pistrolhitzombieking(zombie (&zombie)[zombienumber],int characterdirection)
{
    ;
}

void showgun::shotgunhitzombieking(zombie (&zombie)[zombienumber],int characterdirection)
{
    ;
}

void showgun::UZIhitzombieking(zombie (&zombie)[zombienumber],int characterdirection)
{
    ;
}



void showgun::changepistrolfinaloutput(zombie(&zombie)[zombienumber],showbullet &pistrolbullet,int characterdirection)
{
    switch (characterdirection)
    {
        case 0:
            for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }

        for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=characterpositionx-zombie[i].zombiepositionx-25;
                   endingy=zombie[i].zombiepositiony-characterpositiony-25;
                   zombie[i].hurt(pistrolbullet.decreaseblood(),1);
               }
           }
        break;
        case 1:
            for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }
           for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   zombie[i].hurt(pistrolbullet.decreaseblood(),2);
                   endingy=(zombie[i].zombiepositiony-characterpositiony-50)  ;
               }
           }
        break;
        case 2:
            for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }

        for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=characterpositionx-zombie[i].zombiepositionx+10;
                   endingy=zombie[i].zombiepositiony-characterpositiony-20;
                   zombie[i].hurt(pistrolbullet.decreaseblood(),3);
               }
           }
        break;
        case 3:
            for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositionx) zombie[i].zombiehit=false;
           }
           for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   zombie[i].hurt(pistrolbullet.decreaseblood(),4);
                   endingx=(characterpositionx-zombie[i].zombiepositionx-30)  ;
               }
           }
        break;
        case 4:
            for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositionx) zombie[i].zombiehit=false;
           }
           for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   zombie[i].hurt(pistrolbullet.decreaseblood(),6);
                   endingx=(characterpositionx-zombie[i].zombiepositionx+50)  ;
               }
           }
        break;
        case 5:
            for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }

        for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=characterpositionx-zombie[i].zombiepositionx-25;
                   endingy=zombie[i].zombiepositiony-characterpositiony+30;
                   zombie[i].hurt(pistrolbullet.decreaseblood(),7);
               }
           }
        break;
        case 6:
            for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }
           for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   zombie[i].hurt(pistrolbullet.decreaseblood(),8);
                   endingy=(zombie[i].zombiepositiony-characterpositiony+40);
               }
           }
        break;
        case 7:
            for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }

           for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=characterpositionx-zombie[i].zombiepositionx+75;
                   endingy=zombie[i].zombiepositiony-characterpositiony+30;
                   zombie[i].hurt(pistrolbullet.decreaseblood(),9);
               }
           }
           break;


    }
}

void showgun::changeUZIfinaloutput(zombie (&zombie)[20],showbullet &uzibullet,int characterdirection)
{
    switch (characterdirection)
    {
    case 0:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }
        for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=characterpositionx-zombie[i].zombiepositionx-25;
                   endingy=zombie[i].zombiepositiony-characterpositiony-25;
                   zombie[i].hurt(uzibullet.decreaseblood(),1);
               }
           }
        break;
    case 1:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }
           for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   zombie[i].hurt(uzibullet.decreaseblood(),2);
                   endingy=(zombie[i].zombiepositiony-characterpositiony-50)  ;
               }
           }
        break;
    case 2:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }
        for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=characterpositionx-zombie[i].zombiepositionx+10;
                   endingy=zombie[i].zombiepositiony-characterpositiony-20;
                   zombie[i].hurt(uzibullet.decreaseblood(),3);
               }
           }
        break;
    case 3:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositionx) zombie[i].zombiehit=false;
           }
           for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=(characterpositionx-zombie[i].zombiepositionx-30)  ;
                   zombie[i].hurt(uzibullet.decreaseblood(),4);
               }
           }
        break;
    case 4:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositionx) zombie[i].zombiehit=false;
           }
           for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   zombie[i].hurt(uzibullet.decreaseblood(),6);
                   endingx=(characterpositionx-zombie[i].zombiepositionx+50)  ;
               }
           }
        break;
    case 5:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }

        for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=characterpositionx-zombie[i].zombiepositionx-25;
                   endingy=zombie[i].zombiepositiony-characterpositiony+30;
                   zombie[i].hurt(uzibullet.decreaseblood(),7);
               }
           }
        break;
    case 6:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }
           for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   zombie[i].hurt(uzibullet.decreaseblood(),8);
                   endingy=(zombie[i].zombiepositiony-characterpositiony+40)  ;
               }
           }
        break;
    case 7:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }

        for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=characterpositionx-zombie[i].zombiepositionx+75;
                   endingy=zombie[i].zombiepositiony-characterpositiony+30;
                   zombie[i].hurt(uzibullet.decreaseblood(),9);
               }
           }
        break;
    }
}

void showgun::changeshotgunfinaloutput(zombie (&zombie)[20],showbullet &shotgunbullet,int characterdirection)
{
    switch(characterdirection)
    {
    case 0:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }

        for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=characterpositionx-zombie[i].zombiepositionx-25;
                   endingy=zombie[i].zombiepositiony-characterpositiony-25;
                   zombie[i].hurt(shotgunbullet.decreaseblood(),1);
               }
           }
        break;
    case 1:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }
           for(int i=0;i<=19;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingy=(zombie[i].zombiepositiony-characterpositiony-50)  ;
                   zombie[i].hurt(shotgunbullet.decreaseblood(),2);
               }
           }
        break;
    case 2:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }

        for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=characterpositionx-zombie[i].zombiepositionx+50;
                   endingy=zombie[i].zombiepositiony-characterpositiony-25;
                   zombie[i].hurt(shotgunbullet.decreaseblood(),3);
               }
           }
        break;
    case 3:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositionx) zombie[i].zombiehit=false;
           }
           for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   zombie[i].hurt(shotgunbullet.decreaseblood(),4);
                   endingx=(characterpositionx-zombie[i].zombiepositionx)  ;
               }
           }
        break;
    case 4:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositionx) zombie[i].zombiehit=false;

           }
           for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   zombie[i].hurt(shotgunbullet.decreaseblood(),6);
                   endingx=(characterpositionx-zombie[i].zombiepositionx) ;
               }
           }
        break;
    case 5:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }

        for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=characterpositionx-zombie[i].zombiepositionx-25;
                   endingy=zombie[i].zombiepositiony-characterpositiony+30;
                   zombie[i].hurt(shotgunbullet.decreaseblood(),7);
               }
           }
        break;
    case 6:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }
           for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   zombie[i].hurt(shotgunbullet.decreaseblood(),8);
                   endingy=(zombie[i].zombiepositiony-characterpositiony+40)  ;
               }
           }
        break;
    case 7:
        for (int i=0;i<zombienumber;i++)
           {
               if (zombiegethit!=zombie[i].zombiepositiony) zombie[i].zombiehit=false;
           }

        for(int i=0;i<zombienumber;i++)
           {
               if (zombie[i].zombiehit==true)
               {
                   endingx=characterpositionx-zombie[i].zombiepositionx+75;
                   endingy=zombie[i].zombiepositiony-characterpositiony+30;
                   zombie[i].hurt(shotgunbullet.decreaseblood(),9);
               }
           }
        break;
    }
}

void showgun::free()
{
    if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

 void showgun::render( int x, int y,SDL_Renderer* gRenderer, SDL_Rect* clip  )
 {
     SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
 }

 bool showgun::loadFromFile( std::string path,SDL_Renderer* gRenderer )
 {
     free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else
    {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    mTexture = newTexture;
    return mTexture != NULL;

 }

 void showgun::changelength(int x, int y)
{
    endingx=x;
    endingy=y;
}

void showgun::changestart(int x, int y)
{
    changex=x;
    changey=y;
}

void showgun::showshotgunline(SDL_Renderer* gRenderer)
{
    SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0xFF );
    if ((endingx*endingx+endingy*endingy)<=2500)
    {
        SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+(SDL_GetTicks()%3)+changex, positiony+starty+endingy+(SDL_GetTicks()%3)+changey, positionx-startx+changex, positiony+starty+changey);
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-(SDL_GetTicks()%3)+changex, positiony+starty+endingy+(SDL_GetTicks()%3)+changey, positionx-startx+changex, positiony+starty+changey);
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+changex, positiony+starty+endingy+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+((SDL_GetTicks()+1)%3)+changex, positiony+starty+endingy+((SDL_GetTicks()+1)%3)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-((SDL_GetTicks()+1)%3)+changex, positiony+starty+endingy+((SDL_GetTicks()+1)%3)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-(SDL_GetTicks()%3)+changex, positiony+starty+endingy-(SDL_GetTicks()%1)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-(SDL_GetTicks()%3)+changex, positiony+starty+endingy+(SDL_GetTicks()%1)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-((SDL_GetTicks()+1)%3+changex), positiony+starty+endingy-((SDL_GetTicks()+1)%3)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-((SDL_GetTicks()+1)%3+changex), positiony+starty+endingy+((SDL_GetTicks()+1)%3)+changey, positionx-startx+changex, positiony+starty+changey );
    }
    else if ((endingx*endingx+endingy*endingy)<=10000)
    {
        SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+(SDL_GetTicks()%5)+changex, positiony+starty+endingy+(SDL_GetTicks()%5)+changey, positionx-startx+changex, positiony+starty+changey);
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-(SDL_GetTicks()%5)+changex, positiony+starty+endingy+(SDL_GetTicks()%5)+changey, positionx-startx+changex, positiony+starty+changey);
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+changex, positiony+starty+endingy+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+((SDL_GetTicks()+3)%5)+changex, positiony+starty+endingy+((SDL_GetTicks()+3)%5)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-((SDL_GetTicks()+3)%5)+changex, positiony+starty+endingy+((SDL_GetTicks()+3)%5)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-(SDL_GetTicks()%5)+changex, positiony+starty+endingy-(SDL_GetTicks()%5)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-(SDL_GetTicks()%5)+changex, positiony+starty+endingy+(SDL_GetTicks()%5)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-((SDL_GetTicks()+3)%5+changex), positiony+starty+endingy-((SDL_GetTicks()+3)%5)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-((SDL_GetTicks()+3)%5+changex), positiony+starty+endingy+((SDL_GetTicks()+3)%5)+changey, positionx-startx+changex, positiony+starty+changey );
    }
    else if ((endingx*endingx+endingy*endingy)<=22500)
    {
        SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+(SDL_GetTicks()%8)+changex, positiony+starty+endingy+(SDL_GetTicks()%8)+changey, positionx-startx+changex, positiony+starty+changey);
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-(SDL_GetTicks()%8)+changex, positiony+starty+endingy+(SDL_GetTicks()%8)+changey, positionx-startx+changex, positiony+starty+changey);
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+changex, positiony+starty+endingy+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+((SDL_GetTicks()+3)%8)+changex, positiony+starty+endingy+((SDL_GetTicks()+3)%8)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-((SDL_GetTicks()+3)%8)+changex, positiony+starty+endingy+((SDL_GetTicks()+3)%8)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-(SDL_GetTicks()%8)+changex, positiony+starty+endingy-(SDL_GetTicks()%8)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-(SDL_GetTicks()%8)+changex, positiony+starty+endingy+(SDL_GetTicks()%8)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-((SDL_GetTicks()+3)%8+changex), positiony+starty+endingy-((SDL_GetTicks()+3)%8)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-((SDL_GetTicks()+3)%8+changex), positiony+starty+endingy+((SDL_GetTicks()+3)%8)+changey, positionx-startx+changex, positiony+starty+changey );
    }
    else if ((endingx*endingx+endingy*endingy)<=40000)
    {
        SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+(SDL_GetTicks()%11)+changex, positiony+starty+endingy+(SDL_GetTicks()%11)+changey, positionx-startx+changex, positiony+starty+changey);
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-(SDL_GetTicks()%11)+changex, positiony+starty+endingy+(SDL_GetTicks()%11)+changey, positionx-startx+changex, positiony+starty+changey);
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+changex, positiony+starty+endingy+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx+((SDL_GetTicks()+3)%11)+changex, positiony+starty+endingy+((SDL_GetTicks()+3)%11)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, characterpositionx-startx-endingx-((SDL_GetTicks()+3)%11)+changex, positiony+starty+endingy+((SDL_GetTicks()+3)%11)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, positionx-startx-endingx-(SDL_GetTicks()%11)+changex, positiony+starty+endingy-(SDL_GetTicks()%11)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, positionx-startx-endingx-(SDL_GetTicks()%11)+changex, positiony+starty+endingy+(SDL_GetTicks()%11)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, positionx-startx-endingx-((SDL_GetTicks()+3)%11+changex), positiony+starty+endingy-((SDL_GetTicks()+3)%11)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, positionx-startx-endingx-((SDL_GetTicks()+3)%11+changex), positiony+starty+endingy+((SDL_GetTicks()+3)%11)+changey, positionx-startx+changex, positiony+starty+changey );
    }
    else
    {
        SDL_RenderDrawLine( gRenderer, positionx-startx-endingx+(SDL_GetTicks()%15)+changex, positiony+starty+endingy+(SDL_GetTicks()%15)+changey, positionx-startx+changex, positiony+starty+changey);
    SDL_RenderDrawLine( gRenderer, positionx-startx-endingx-(SDL_GetTicks()%15)+changex, positiony+starty+endingy+(SDL_GetTicks()%15)+changey, positionx-startx+changex, positiony+starty+changey);
    SDL_RenderDrawLine( gRenderer, positionx-startx-endingx+changex, positiony+starty+endingy+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, positionx-startx-endingx+((SDL_GetTicks()+3)%15)+changex, positiony+starty+endingy+((SDL_GetTicks()+3)%15)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, positionx-startx-endingx-((SDL_GetTicks()+3)%15)+changex, positiony+starty+endingy+((SDL_GetTicks()+3)%15)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, positionx-startx-endingx-(SDL_GetTicks()%15)+changex, positiony+starty+endingy-(SDL_GetTicks()%15)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, positionx-startx-endingx-(SDL_GetTicks()%15)+changex, positiony+starty+endingy+(SDL_GetTicks()%15)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, positionx-startx-endingx-((SDL_GetTicks()+3)%15+changex), positiony+starty+endingy-((SDL_GetTicks()+3)%15)+changey, positionx-startx+changex, positiony+starty+changey );
    SDL_RenderDrawLine( gRenderer, positionx-startx-endingx-((SDL_GetTicks()+3)%15+changex), positiony+starty+endingy+((SDL_GetTicks()+3)%15)+changey, positionx-startx+changex, positiony+starty+changey );
    }

}

showbullet::showbullet(char* weapon,int a, int b,int c,int d,int f,int i)
{
    bullets[0]=a+48;
    bullets[1]=b+48;
    bullets[2]=c+48;
    speedconstant=d;
    damage=f;
    damageupgrade=i;
    for (stringlength=0;(weaponremainging[stringlength]=weapon[stringlength])!='\0';stringlength++) ;
    mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	upgrade=0;
}

bool showbullet::bulletremain()
{
    if (bullets[0]!='0'||bullets[1]!='0'||bullets[2]!='0') return true;
    else return false;
}

bool showbullet::loadFromRenderedText( std::string textureText, SDL_Color textColor,TTF_Font *gFont,SDL_Renderer* gRenderer )
{
    free();
    textureText[stringlength]=' ';
    textureText[stringlength+1]=bullets[0];
    textureText[stringlength+2]=bullets[1];
    textureText[stringlength+3]=bullets[2];
    textureText[stringlength+4]='\0';
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )  printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    else
    {
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )  printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface( textSurface );
    }
    return mTexture != NULL;
}

void showbullet::increasebullet()
{
    if (bullets[2]!='9') bullets[2]+=1;
    else if (bullets[1]!='9')
    {
        bullets[1]+=1;
        bullets[2]='0';
    }
    else if (bullets[0]!='9')
    {
        bullets[2]='0';
        bullets[1]='0';
        bullets[0]+=1;
    }

}

void showbullet::increasebullet10()
{
    if (bullets[1]!='9') bullets[1]+=1;
    else if (bullets[0]!='9')
    {
        bullets[1]='0';
        bullets[0]+=1;
    }
    else bullets[2]='9';
}

showbullet::~showbullet()
{
    free();
}

void showbullet::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void showbullet::render( int x, int y,SDL_Renderer* gRenderer, SDL_Rect* clip)
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}


void showbullet::decreasebullet()
{
     if (bullets[0]=='1')
     {
        bullets[0]='0';
        bullets[1]='9';
        bullets[2]='9';
     }
     else if (bullets[2]=='0')
    {
      bullets[1]=bullets[1]-1;
      bullets[2]='9';}
     else bullets[2]=bullets[2]-1;
}

int showbullet::decreaseblood()
{
    if (upgrade==0) return damage;
    else return damageupgrade;
}

void weapon::changeweapon()
{
    if (weaponmode+1<=weaponkind) weaponmode++;
    else weaponmode=0;
}

weapon::weapon()
{
    int firespeed=0;
    int weaponkind=0;
    int weaponmode=0;
    int weaponchangeconstant=0;
}

void weapon::supplementweapon(int ramdom, showbullet &uzibullet,showbullet &shotgunbullet,showbullet &generadebullet,showbullet &wallbullet, showbullet&shieldbullet,showbullet &atombombbullet )
{
    ramdom=(ramdom+1)%(weaponkind+1);
    switch (ramdom)
    {
    case 1:
        uzibullet.increasebullet10();
    case 2:
        shotgunbullet.increasebullet10();
    case 3:
        generadebullet.increasebullet10();
    case 4:
        wallbullet.increasebullet10();
    case 5:
        shieldbullet.increasebullet();
    case 6:
        atombombbullet.increasebullet();
    }
}

mousebuttom::mousebuttom(int x,int y,int x0,int y0, int w,int h)
{
    xx=x;
    yy=y;
    xxx=x0;
    yyy=y0;
    width=w;
    height=h;
    ending=false;
    surface.w=SCREEN_WIDTH;
    surface.h=SCREEN_HEIGHT;
    surface.x=0;
    surface.y=0;
    gameover.w=1000;
    gameover.h=600;
    gameover.x=0;
    gameover.y=0;

}

mousebuttom::~mousebuttom()
{
    freebrain();
    freesurface();
}

void mousebuttom::handlebuttom(SDL_Event* e )
{
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        int x,y;
        SDL_GetMouseState( &x, &y );
        bool inside = true;
        if( x < xx ) inside=false;
        else if (x>width+xx) inside=false;
        else if (y<yy) inside=false;
        else if (y>height+yy) inside=false;
        if (!inside) mouseevent=0;
        else
        {
            switch(e->type)
            {
                case SDL_MOUSEMOTION:
                    mouseevent=1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouseevent=2;
                    ending=true;
                    break;
            }
        }
        if (inside==false)
        {
            inside=true;
            if (x<xxx) inside=false;
            else if (x>xxx+width) inside=false;
            else if (y<yyy) inside=false;
            else if (y>yyy+height) inside=false;
            if (!inside) mouseevent=0;
            else
            {
                switch(e->type)
                {
                    case SDL_MOUSEMOTION:
                        mouseevent=1;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        mouseevent=3;
                        ending=true;
                        break;
                }
            }
        }
    }


}

void mousebuttom::freesurface()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void mousebuttom::freebrain()
{
    if( brainTexture != NULL )
    {
        SDL_DestroyTexture( brainTexture );
        brainTexture = NULL;
        brainWidth = 0;
        brainHeight = 0;
    }
}

bool mousebuttom::loadFromFile( std::string path ,SDL_Renderer* gRenderer)
{
    freesurface();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

bool mousebuttom::brainloadFromFile( std::string path ,SDL_Renderer* gRenderer)
{
    freebrain();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        else {
            brainWidth = loadedSurface->w;
            brainHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    brainTexture = newTexture;
    return brainTexture != NULL;
}

void mousebuttom::surfacerender(SDL_Rect* clip,SDL_Renderer* gRenderer )
{
    SDL_Rect renderQuad = {0, 0, clip->w, clip->h };
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

void mousebuttom::brainrender(SDL_Renderer* gRenderer,SDL_Rect* clip )
{
    SDL_Rect renderQuad = {620, 280, 300, 400};
    SDL_RenderCopy( gRenderer, brainTexture, clip, &renderQuad );
}

score::score()
{
    for(int i=0;i<=6;i++) scores[i]='0';
    rendering=false;
    runtext=0;
    mTexture=NULL;
    mWidth = 0;
    mHeight = 0;
}

void score::free()
{

	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

bool score::loadFromRenderedscore(SDL_Color textColor,TTF_Font *scoreFont,SDL_Renderer* gRenderer)
{
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid( scoreFont, scores, textColor );
    if( textSurface == NULL )  printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    else
    {
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )  printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface( textSurface );
    }
    return mTexture != NULL;

}

bool score::loadFromRenderedText(SDL_Color textColor,TTF_Font *scoreFont,SDL_Renderer* gRenderer)
{
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid( scoreFont, storing, textColor );
    if( textSurface == NULL )  printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    else
    {
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )  printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface( textSurface );
    }
    return mTexture != NULL;

}


void score::renderscore(int x, int y,SDL_Renderer* gRenderer,SDL_Rect* clip )
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

void score::increasescores()
{
    if (scores[4]!='9') scores[4]+=1;
    else if (scores[3]!='9')
    {
        scores[3]+=1;
        scores[4]='0';
    }
    else if (scores[2]!='9')
    {
        scores[4]='0';
        scores[3]='0';
        scores[2]+=1;
    }
    else if (scores[1]!='9')
    {
        scores[4]='0';
        scores[3]='0';
        scores[2]='0';
        scores[1]+=1;
    }
    else if (scores[0]!='9')
    {
        scores[4]='0';
        scores[3]='0';
        scores[2]='0';
        scores[1]='0';
        scores[0]+=1;
    }
}

void score::rendertext(int x,int y,SDL_Renderer* gRenderer,SDL_Rect* clip )
{
    SDL_Rect renderQuad = { x, y-runtext, mWidth, mHeight };
    if (judjing!=storing)
    {
        runtext=0;

        judjing=storing;
    }

    runtext+=2;
    if (runtext==100)
    {
        runtext=0;
        rendering=false;
    }
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

void score::judgescore()
{
    if (judge[0]!=scores[0]||judge[1]!=scores[1]||judge[2]!=scores[2]||judge[3]!=scores[3]||judge[4]!=scores[4])
    {
        judge[0]=scores[0];
        judge[1]=scores[1];
        judge[2]=scores[2];
        judge[3]=scores[3];
        judge[4]=scores[4];
        if (scores[2]=='0'&&scores[3]=='0')
       {
        if (scores[4]=='3'||scores[4]=='6'||scores[4]=='9') rendering=true;
       }
       else if (scores[2]=='0'&&scores[3]=='1')
       {
        if (scores[4]=='0'||scores[4]=='2'||scores[4]=='5'||scores[4]=='8') rendering=true;
       }
       else if (scores[2]=='0'&&scores[3]=='2')
       {
        if (scores[4]=='0'||scores[4]=='1'||scores[4]=='4'||scores[4]=='5'||scores[4]=='7') rendering=true;
       }
       else if (scores[2]=='0'&&scores[3]=='3')
       {
        if (scores[4]=='0'||scores[4]=='2'||scores[4]=='4'||scores[4]=='6') rendering=true;
       }
       else if (scores[2]=='0'&&scores[3]=='4')
       {
        if (scores[4]=='5') rendering=true;
       }
    }

}

char * score::upgrade(weapon &weapons,showbullet &pistrolbullet,showbullet &uzibullet,showbullet &shotgunbullet,showgenerade &generade0,showgenerade &generade1,showbullet &generadebullet,fireball (&ball)[12])
{
    if (scores[3]=='0'&&scores[2]=='0')
    {
       if (scores[4]=='3')
    {
        char* s1="Pistol Damage Upgrade";
        storing=s1;
        pistrolbullet.changeupgrade();
        return s1;
    }
    else if (scores[4]=='6')
    {
        char* s1="UZI get";
        storing=s1;
        weapons.uziget();
        return s1;
    }
    else if (scores[4]=='9')
    {
        char* s1="UZI Damage upgrade";
        storing=s1;
        uzibullet.changeupgrade();
        return s1;
    }
    }

    if (scores[2]=='0'&&scores[3]=='1')
    {
        for (int i=0;i<=5;i++)
        {
            ball[i].setspeed(6);
        }
        if (scores[4]=='0')
        {
            char* s1="Shotgun Get";
            storing=s1;
            weapons.shotgun();
            return s1;
        }
        if (scores[4]=='2')
        {
            char* s1="Grenades Get";
            weapons.generade();
            storing=s1;
            return s1;
        }
        if (scores[4]=='5')
        {
            char* s1="Shotgun Damage Upgrade";
            storing=s1;
            shotgunbullet.changeupgrade();
            return s1;
        }
        if (scores[4]=='8')
        {
            char* s1="Grenades Damage Upgrade";
            storing=s1;
            generadebullet.changeupgrade();
            generadebullet.changeupgrade();
            return s1;
        }

    }
    if (scores[2]=='0'&&scores[3]=='2')
    {
        for (int i=0;i<=5;i++)
        {
            ball[i].setspeed(7);
        }
        if (scores[4]=='1')
        {
            char* s1="Walls Get";
            storing=s1;
            weapons.wall();
            return s1;
        }

        if (scores[4]=='5')
        {
            char* s1="Shield Get";
            storing=s1;
            weapons.shield();
            return s1;
        }
        if (scores[4]=='7')
        {
            char* s1="Grenade Upgrade";
            storing=s1;
            generade0.changeupgrade0();
            generade1.changeupgrade0();
            return s1;
        }
    }
    if (scores[2]=='0'&&scores[1]=='3')
    {
        for (int i=0;i<=5;i++)
        {
            ball[i].setspeed(9);
        }
        if (scores[4]=='2')
        {
            char* s1="Pistol Speed Upgrade";
            storing=s1;
            pistrolbullet.changespeed(12);
            return s1;
        }
        if (scores[4]=='4')
        {
            char* s1="UZI Speed Upgrade";
            storing=s1;
            uzibullet.changespeed(6);
            return s1;
        }
        if (scores[4]=='6')
        {
            char* s1="Shotgun Speed Upgrade";
            storing=s1;
            shotgunbullet.changespeed(25);
            return s1;
        }
    }
    if (scores[2]=='0'&&scores[3]=='4')
    {
        for (int i=0;i<=5;i++)
        {
            ball[i].setspeed(11);
        }
        if (scores[4]=='5')
        {
            char* s1="Atombomb Get";
            storing=s1;
            weapons.atom();
            return s1;
        }
    }



    if (scores[2]=='0'&&scores[3]=='5')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(12);
        }
    }

    if (scores[2]=='0'&&scores[3]=='7')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(14);
        }
    }

    if (scores[2]=='0'&&scores[3]=='9')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(15);
        }
    }
    if (scores[2]=='1'&&scores[3]=='1')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(16);
        }
    }
    if (scores[2]=='1'&&scores[3]=='5')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(17);
        }
    }
    if (scores[2]=='1'&&scores[3]=='9')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(18);
        }
    }
    if (scores[2]=='2'&&scores[3]=='3')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(19);
        }
    }
    if (scores[2]=='2'&&scores[3]=='8')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(20);
        }
    }
    if (scores[2]=='3'&&scores[3]=='2')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(21);
        }
    }
    if (scores[2]=='3'&&scores[3]=='5')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(22);
        }
    }
    if (scores[2]=='3'&&scores[3]=='8')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(23);
        }
    }
if (scores[2]=='4'&&scores[3]=='1')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(24);
        }
    }
    if (scores[2]=='4'&&scores[3]=='4')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(25);
        }
    }
    if (scores[2]=='4'&&scores[3]=='7')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(26);
        }
    }
    if (scores[2]=='5'&&scores[3]=='0')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(27);
        }
    }
    if (scores[2]=='5'&&scores[3]=='3')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(28);
        }
    }
    if (scores[2]=='5'&&scores[3]=='6')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(29);
        }
    }
    if (scores[2]=='5'&&scores[3]=='9')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(30);
        }
    }
    if (scores[2]=='6'&&scores[3]=='1')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(35);
        }
    }
    if (scores[2]=='6'&&scores[3]=='6')
    {
        for (int i=0;i<=11;i++)
        {
            ball[i].setspeed(40);
        }
    }
}

fireball::~fireball()
{
    SDL_DestroyTexture( mTexture );
}

fireball::fireball()
{

    acting=false;
    flying=0;
    speed=5;
}

bool fireball::loadFromFile(std::string path,SDL_Renderer* gRenderer )
{
    SDL_DestroyTexture( mTexture );
	mWidth = 0;
    mHeight = 0;
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else
    {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void fireball::start(int x,int y,int positionx, int positiony)
{
    startx=x;
    starty=y;
    targetx=positionx;
    targety=positiony;
    length=sqrt((targetx-startx)*(targetx-startx)+(targety-starty)*(targety-starty));
    flying=1;
    acting=true;
}

void fireball::render(int x,int y,int camx,int camy,Dot1 &dot1,SDL_Renderer* gRenderer, SDL_Rect* clip )
{
    flying++;
    SDL_Rect renderQuad = { startx+flying*(targetx-startx)/length*speed-camx, starty+flying*(targety-starty)/length*speed-camy, mWidth, mHeight };
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
    if (flying==300)
    {
        acting=false;
        flying=0;

    }
        if (startx+flying*(targetx-startx)/length*speed-x<=30&&startx+flying*(targetx-startx)*speed/length-x>=(-10)&&starty+flying*(targety-starty)/length*speed-y<=70&&starty+flying*(targety-starty)/length*speed-y>=(-15))
        {
            acting=false;
            flying=0;
            dot1.hurt(30);
        }

}



