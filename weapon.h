#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <string>
#include"zombie.h"
#include"map.h"
#include <SDL_mixer.h>
const int zombienumber1=20;

class showbullet
{
   public:
       showbullet(char* weapon,int a, int b,int c,int d,int f,int i );
       ~showbullet();
       bool loadFromRenderedText( std::string textureText, SDL_Color textColor,TTF_Font *gFont,SDL_Renderer* gRenderer);
       void free();
       void render( int x, int y,SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);
       bool bulletremain();
       void decreasebullet();
       char weaponremainging[zombienumber1];
       int speed() {return speedconstant;}
       void changespeed(int x) {speedconstant=x;}
       int decreaseblood() ;
       void changeupgrade() {upgrade=1;}
       void increasebullet();
       void increasebullet10();
   private:
       SDL_Texture* mTexture;
       int mWidth;
       int mHeight;
       int stringlength;
       char bullets[3];
       int speedconstant;
       int damage;
       int damageupgrade;
       int upgrade;
};

class showgun
{
    public:
        showgun(int changex,int changey);

        void shotgunhit(zombie (&zombie)[zombienumber1],int characterdirection);
        void pistrolhit(zombie (&zombie)[zombienumber1],int characterdirection);
        void UZIhit(zombie (&zombie)[zombienumber1],int characterdirection);

        void showline(SDL_Renderer* gRenderer);
        bool loadFromFile( std::string path,SDL_Renderer* gRenderer );
        void free();
        void render( int x, int y, SDL_Renderer* gRenderer ,SDL_Rect* clip = NULL);
        void changelength(int x,int y);
        void showshotgunline(SDL_Renderer* gRenderer);
        void changestart(int x, int y);

        void pistrolhitzombieking(zombie (&zombie)[zombienumber1],int characterdirection);
        void shotgunhitzombieking(zombie (&zombie)[zombienumber1],int characterdirection);
        void UZIhitzombieking(zombie (&zombie)[zombienumber1],int characterdirection);



        void changepistrolfinaloutput(zombie (&zombie)[zombienumber1],showbullet &pistrolbullet,int characterdirection);
        void changeUZIfinaloutput(zombie (&zombie)[zombienumber1],showbullet &uzibullet,int characterdirection);
        void changeshotgunfinaloutput(zombie (&zombie)[zombienumber1],showbullet &shotgunbullet,int characterdirection);


        void setcharacterpositionx(int x ) {characterpositionx=x; positionx=x;}
        void setcharacterpositiony(int y)  {characterpositiony=y;positiony=y;}
    private:
       int characterpositionx;
       int characterpositiony;
       int positionx;
       int positiony;
       int startx;
       int starty;
       int endingx;
       int endingy;
       int changex;
       int changey;
       SDL_Texture* mTexture=NULL;
       int mWidth;
       int mHeight;
       int zombiegethit;//判斷距離遠近
};


class showgenerade
{
    public:
        showgenerade();
        ~showgenerade();
        bool loadFromFile( std::string path,SDL_Renderer* gRenderer );
        bool loadFromFileflash1(std::string path,SDL_Renderer* gRenderer);
        bool loadFromFileflash2(std::string path,SDL_Renderer* gRenderer);
        void free();
        void render( Mix_Chunk * &UZI,int x,int y,int camerax,int cameray,showbullet &generadebullet,zombie(&zombie)[20],SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);
        void showburst1(int x,int y,SDL_Renderer* gRenderer,SDL_Rect* clip = NULL);
        void showburst2(Mix_Chunk * &UZI,int x,int y,int camx,int camy,zombie(&zombie)[20],showbullet &generadebullet,SDL_Renderer* gRenderer,SDL_Rect* clip = NULL);
        void setgeneradedirection(int x) {generadedirection=x;}
        bool generadeaction;
        void setoriginalcharacterpositionx (int x) {originalcharacterpositionx=x;}
        void setoriginalcharacterpositiony (int y) {originalcharacterpositiony=y;}
        void changeupgrade0() {upgrade=true;}
        int damage() ;
        void changeupgrade1(){damageupgrage=true;}

    private:
        SDL_Texture* mTexture=NULL;
        SDL_Texture* gTexture;
        SDL_Texture* hTexture;
        int generadepositionx;
        int generadepositiony;
        int mWidth;
        int mHeight;
        int gWidth;
        int hWidth;
        int gHeight;
        int hHeight;
        int generademotion;
        bool upgrade;
        int generadedirection;
        int originalcharacterpositionx;
        int originalcharacterpositiony;
        int damagecountdown;
        bool damageupgrage;
};

class shield
{
   public:
       shield();
       ~shield();
       void free();
       bool loadFromFile( std::string path,SDL_Renderer* gRenderer );
       void render(int camarax,int camaray,SDL_Renderer* gRenderer ,Dot &dot1,SDL_Rect* clip = NULL);
       bool acting() ;
       void resetlasttime(int x,int y) ;
       void protecting();
   private:
    SDL_Texture* mTexture=NULL;;
    int mHeight;
    int mWidth;
    int shieldpositionx;
    int shieldpositiony;
    int shieldlasttime;

};



class atom
{
public:
    atom();
    ~atom();
    bool loadFromFile( std::string path,SDL_Renderer* gRenderer );
    void free();
    void render(SDL_Rect* clip,SDL_Renderer* gRenderer );
    SDL_Rect bombsize;
    void resetatom() {amplify=0;}
    bool bursting() {if (amplify<=40) return true ;else return false; }
    void increse() {amplify++;}
    void changerect();
    bool bombing;
private:
     SDL_Texture* mTexture;
     int mWidth;
     int mHeight;
     int amplify;

};



class weapon
{
public:
    weapon();
    void changefirespeed(int x) {firespeed=x;}
    void decreasefirespeed() {firespeed--;}
    void weaponmodeupgrade() {weaponkind++;}
    void changeweapon();
    bool firespeedzero() {if (firespeed==0) return true ; else return false;}
    int getweaponmode() {return weaponmode;}
    int getweaponchangeconstant() {return weaponchangeconstant;}
    void setweaponchangeconstant (int x) {weaponchangeconstant=x;}
    void decreaseweaponchangeconstant() {weaponchangeconstant-=1;}
    void uziget () {weaponkind=1;}
    void shotgun() {weaponkind=2;}
    void generade() {weaponkind=3;}
    void wall() {weaponkind=4;}
    void shield () {weaponkind=5;}
    void atom() {weaponkind=6;}
    void supplementweapon(int ramdom, showbullet &uzibullet,showbullet &shotgunbullet,showbullet &generadebullet,showbullet &wallbullet, showbullet&shieldbullet,showbullet &atombombbullet ) ;
private:
    int firespeed;
    int weaponkind;
    int weaponmode;
    int weaponchangeconstant;
};

class mousebuttom
{
  public:
      mousebuttom(int x,int y,int x0,int y0, int w,int h);
      ~mousebuttom();
      void handlebuttom(SDL_Event* e);
      void freesurface();
      void freebrain();
      bool ending;
      int getmouseevent() {return mouseevent;}
      bool loadFromFile( std::string path,SDL_Renderer* gRenderer );
      bool brainloadFromFile( std::string path,SDL_Renderer* gRenderer );
      void surfacerender(SDL_Rect* clip,SDL_Renderer* gRenderer );
      void brainrender(SDL_Renderer* gRenderer,SDL_Rect* clip=NULL );
      SDL_Rect surface;
      SDL_Rect gameover;


  private:
      int mouseevent;  //0是正常 1 是放上去 2 是點下去
      int xx,xxx;
      int yy,yyy;
      int width;
      int height;
      SDL_Texture* mTexture;
      int mWidth;
      int mHeight;
      SDL_Texture* brainTexture;
      int brainWidth;
      int brainHeight;

};


class fireball
{
  public:
      fireball();
      ~fireball();
      bool loadFromFile( std::string path,SDL_Renderer* gRenderer );
      void start(int x,int y,int positionx, int positiony);
      void render(int x,int y,int camx,int camy,Dot1 &dot1,SDL_Renderer* gRenderer, SDL_Rect* clip = NULL);
      int getacting() {return acting;}
      void setspeed(int x) {speed=x;}
  private:
      int startx;
      int starty;
      int flying;
      int targetx;
      int targety;
      int mWidth;
      int mHeight;
      SDL_Texture* mTexture=NULL;
      bool acting;
      int length;
      int speed;

};

class score
{
  public:
    score();
    bool loadFromRenderedscore( SDL_Color textColor,TTF_Font *scoreFont,SDL_Renderer* gRenderer);
    bool loadFromRenderedText( SDL_Color textColor,TTF_Font *scoreFont,SDL_Renderer* gRenderer);
    void renderscore(int x, int y,SDL_Renderer* gRenderer,SDL_Rect* clip = NULL );
    void rendertext(int x,int y,SDL_Renderer* gRenderer,SDL_Rect* clip = NULL );
    void free();
    bool getrendering() {return rendering;}
    void judgescore();
    void increasescores();
    char * upgrade(weapon &weapons,showbullet &pistrolbullet,showbullet &uzibullet,showbullet &shotgunbullet,showgenerade &generade0,showgenerade &generade1,showbullet &generadebullet,fireball (&ball)[12]);
  private:
    SDL_Texture* mTexture;
    char scores[7];
    int mWidth;
    int mHeight;
    int runtext;
    bool rendering;
    char * storing;
    char judge[5];
    char * judjing;


};



#endif
