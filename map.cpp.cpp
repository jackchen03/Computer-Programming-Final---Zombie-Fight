/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, vectors, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//The dimensions of the level
const int LEVEL_WIDTH = 2360;
const int LEVEL_HEIGHT = 1204;
const int doorwith=75;

//Screen dimension constants
const int SCREEN_WIDTH =640;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//The dot that will move around on the screen



class Dot
{
    public:
        static const int bar_WIDTH = 20;
		static const int bar_HEIGHT = 20;

        void cantgo();
		//The dimensions of the dot
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 5;

		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move(int camX, int camY);

		//Shows the dot on the screen relative to the camera
		void render( int camX, int camY );

		//Position accessors
		int getPosX();
		int getPosY();
        int getPosX2();
		int getPosY2();
protected:
		//The X and Y offsets of the dot
		int mPosX, mPosY;
		int mPosX2,mPosY2;

		//The velocity of the dot
		int mVelX, mVelY;
		int mVelX2, mVelY2;
		int num;


};

class bucket
{
    friend class Dot;

   public:
       bucket();
       ~bucket();
       void freebucket();
       void freewall();
       bool loadFromFilebucket( std::string path );
       bool loadFromFilewall(std::string path);
       void renderbucket(int x, int y, SDL_Rect* clip = NULL);
       void renderwall(int x, int y, SDL_Rect* clip = NULL);

       void allrender();

   private:

      SDL_Texture* mTexture;
      int mWidth;
      int mHeight;
      SDL_Texture* wTexture;
      int wWidth;
      int wHeight;
      bool pos_xy[LEVEL_WIDTH/40][LEVEL_HEIGHT/63];
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gDotTexture;
LTexture gDotTexture2;
LTexture gBGTexture;
//LTexture
bucket bucketwall;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensionsmPosX2
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}


	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
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

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}



Dot::Dot()
{
    //Initialize the offsets
    mPosX = LEVEL_WIDTH/2-DOT_WIDTH;
    mPosY = LEVEL_HEIGHT/2;
    mPosX2= LEVEL_WIDTH/2+DOT_WIDTH;
    mPosY2 = LEVEL_HEIGHT/2;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    mVelX2=0;
    mVelY2=0;

}

void Dot::handleEvent( SDL_Event& e )
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
            case SDLK_w: mVelY2 -= DOT_VEL; break;
            case SDLK_s: mVelY2 += DOT_VEL; break;
            case SDLK_a: mVelX2 -= DOT_VEL; break;
            case SDLK_d: mVelX2 += DOT_VEL; break;
            case SDLK_g: bucketwall.pos_xy[mPosX/40][mPosY/63]=true;break;
            case SDLK_h: bucketwall.pos_xy[mPosX2/40][mPosY2/63]=true;break;



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
            case SDLK_w: mVelY2 += DOT_VEL; break;
            case SDLK_s: mVelY2 -= DOT_VEL; break;
            case SDLK_a: mVelX2 += DOT_VEL; break;
            case SDLK_d: mVelX2 -= DOT_VEL; break;
        }
        }
    }










void Dot::move( int camX, int camY )

{
    //Move the dot left or right
    mPosX += mVelX;
   if(mPosX==mPosX2&&mPosY==mPosY2){mPosX-=mVelX;}
    cantgo();//barrier
    //boundary of map
    if(  (mPosX < 0 ) || ( mPosX + DOT_WIDTH > LEVEL_WIDTH ) )
    {
        if((mPosX<LEVEL_WIDTH/2-6*DOT_WIDTH)||(mPosX>LEVEL_WIDTH/2+6*DOT_WIDTH)&&((mPosY<4*DOT_HEIGHT)&&(mPosY>0))||((mPosY>LEVEL_HEIGHT-5*DOT_HEIGHT)&&(mPosY<LEVEL_HEIGHT-DOT_HEIGHT)))
          {
              mPosX-=mVelX;
           }



        //Move back
       else { mPosX -= mVelX;}

    }

    //Move the dot up or down
    mPosY += mVelY;
   if(mPosX==mPosX2&&mPosY==mPosY2){mPosY-=mVelY;}
   cantgo();
    //If the dot went too far up or down
    if( ( mPosY < 4*DOT_HEIGHT ) || ( mPosY + 5*DOT_HEIGHT > LEVEL_HEIGHT ) )
    {
       //Move back
       if((mPosX>LEVEL_WIDTH/2-6*DOT_WIDTH)&&(mPosX<LEVEL_WIDTH/2+6*DOT_WIDTH))
       { if( ( mPosY < 0) || ( mPosY + DOT_HEIGHT > LEVEL_HEIGHT ) )
        mPosY-=mVelY;
       }

        else {mPosY -= mVelY;}


    }
      mPosX2 += mVelX2;
      if(mPosX==mPosX2&&mPosY==mPosY2){mPosX2-=mVelX2;}
      cantgo();
    //If the dot went too far to the left or right
    if( ( mPosX2 < 0 ) || ( mPosX2 + DOT_WIDTH > LEVEL_WIDTH ) )
    {
        //Move back
        mPosX2 -= mVelX2;
    }

    //Move the dot up or down
    mPosY2 += mVelY2;
if(mPosX==mPosX2&&mPosY==mPosY2){mPosY2-=mVelY2;}
cantgo();
    //If the dot went too far up or down
    if( ( mPosY2 < 4*DOT_HEIGHT ) || ( mPosY2 + 5*DOT_HEIGHT > LEVEL_HEIGHT ) )
    {
        //Move back
        mPosY2 -= mVelY2;



    }
}

void Dot:: cantgo(){
    int i=0,j=0;

for(i=0;i<LEVEL_WIDTH/40;i++){
        for(j=0;j<LEVEL_HEIGHT/63;j++){
    if (bucketwall.pos_xy[i][j]==true&&i==mPosX/40&&j==mPosY/63) {  mPosX -= mVelX;mPosY -= mVelY;}
    if (bucketwall.pos_xy[i][j]==true&&i==mPosX2/40&&j==mPosY2/63) {  mPosX2 -= mVelX2;mPosY2 -= mVelY2;}


}
}
}

void Dot::render( int camX, int camY )
{


    //Show the dot relative to the camera
	gDotTexture.render( mPosX - camX, mPosY - camY );
    gDotTexture2.render(mPosX - camX-(mPosX-mPosX2),mPosY - camY-(mPosY-mPosY2));
}


int Dot::getPosX()
{
	return mPosX;
}
int Dot::getPosX2()
{
	return mPosX2;
}

int Dot::getPosY()
{
	return mPosY;
}
int Dot::getPosY2()
{
	return mPosY2;
}

bucket::bucket()
{
    mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	wTexture=NULL;
	wWidth=0;
	mHeight=0;
	for(int i=0;i<LEVEL_WIDTH/40;i++)for(int j=0;j<LEVEL_HEIGHT/63;j++){pos_xy[i][j]=false;}
}

bucket::~bucket()
{
    freebucket();
    freewall();
}

void bucket::freebucket()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
    }
}

void bucket::freewall()
{
    if( wTexture != NULL )
    {
        SDL_DestroyTexture( wTexture );
		wTexture = NULL;
		wWidth = 0;
		wHeight = 0;
    }
}

bool bucket::loadFromFilebucket( std::string path )
{
    freebucket();
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

bool bucket::loadFromFilewall( std::string path )
{
    freewall();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ) printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    else
    {
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL ) printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        else
        {
            wWidth = loadedSurface->w;
            wHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    wTexture = newTexture;
    return wTexture != NULL;
}

void bucket::renderbucket( int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}


void bucket::renderwall( int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderQuad = { x, y, wWidth, wHeight };
    SDL_RenderCopy( gRenderer, wTexture, clip, &renderQuad );
}


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
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
	if( !gDotTexture2.loadFromFile( "dot.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !gDotTexture.loadFromFile( "dot.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	//Load background texture
	if( !gBGTexture.loadFromFile( "map_1.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}


	//load bucket and wall
	if( !bucketwall.loadFromFilebucket( "bucket.png" ) )
	{
		printf( "Failed to load bucket texture!\n" );
		success = false;
	}
	if( !bucketwall.loadFromFilewall( "wall.png" ) )
	{
		printf( "Failed to load bucket texture!\n" );
		success = false;
	}


	return success;
}

void close()
{
	//Free loaded images
	gDotTexture.free();
	gDotTexture2.free();
	gBGTexture.free();

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
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot1;

//           bucket bucketall;
			//The camera area
			SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

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
					dot1.handleEvent( e );

				}

				//Move the dot
				dot1.move(camera.x, camera.y);

				//Center the camera over the dot
				camera.x = ( dot1.getPosX() + Dot::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
				camera.y = ( dot1.getPosY() + Dot::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

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

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				SDL_RenderClear( gRenderer );


				//Render background
				gBGTexture.render( 0, 0, &camera );

				//Render objects
				dot1.render( camera.x, camera.y );
                bucketwall.renderwall(dot1.getPosX()+20,dot1.getPosY()+20);
				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
