#include <simplecpp>
#include <time.h>
#include <fstream>
#include <string>

const double rl = 70 , rb = 40 , r = 10 , x0 = 100 ;
const double g_level = 600 , wl = 1380 , wh = 800 ;
const double p_width = 100 , p_height = 150, b_size = 50, c_size = 10;
const double t_size = 20 ;
const clock_t start=clock();
const int n_coins=50,n_grounds=10,n_pipes=10,n_blocks=20,n_clouds=10,n_turtles=10,n_mushrooms=4;
	
//turtle----
struct turtle {
    Rectangle rt,r[5];
    Circle c1,c2,c3;
    bool small_size;
    bool dead;
    double d ;
    double x0 ;
    double v ;
    void set_turtle( double x , double y , double distance ,double sx=t_size , double sy=t_size) {
        beginFrame();
        rt.reset( x+20 , y , sx , sy) ;
        rt.setColor( COLOR("black")) ;
        rt.setFill() ;
        rt.hide();
        for(int i=1;i<5;i++)
        {
            r[i].reset(x+20 , y+(2-i)*sy/5 , sx-i*2 , sy/5);
            r[i].setColor(COLOR(100+i*20,100+i*20,100+i*20));
            r[i].setFill();
        }
        c1.reset(x+20+sx/4,y+2*sy/5,sy/10);
        c1.setColor(COLOR("black"));
        c1.setFill();
        c2.reset(x+20-sx/4,y+2*sy/5,sy/10);
        c2.setColor(COLOR("black"));
        c2.setFill();
        c3.reset(x+20-sx/2,y+sy/5,sy/7);
        c3.setColor(COLOR("black"));
        c3.setFill();

        x0 = x ;
        d = distance ;
        v = 5 ;
        if(sy==t_size){
            small_size=0;
            dead=0;
        }
        else{
            small_size=1;
            dead=1;
        }
        endFrame();
    }
    void moveTo( double dx , double dy ) {
        rt.hide();
        rt.moveTo( dx , dy ) ;
        for(int i=0;i<5;i++)
            r[i].moveTo(dx,dy);
        c1.moveTo(dx,dy);
        c2.moveTo(dx,dy);
        c3.moveTo(dx,dy);
        x0 += dx ;
    }
    void move( double dx , double dy ) {
        rt.move( dx , dy ) ;
        for(int i=0;i<5;i++)
            r[i].move(dx,dy);
        c1.move(dx,dy);
        c2.move(dx,dy);
        c3.move(dx,dy);
        x0 += dx ;
    }
    void move_between () {
        if( rt.getX()-d >= x0-10 ) {
            v *= -1 ;
            c3.move((t_size+2*t_size/7-4),0);
        }

        else if(  rt.getX() <= x0+10) {
            v *= -1 ;
            c3.move(-(t_size+2*t_size/7-4),0);
        }
        beginFrame();
        rt.move( v , 0 ) ;
        for(int i=0;i<5;i++)
            r[i].move(v,0);
        c1.move(v,0);
        c2.move(v,0);
        c3.move(v,0);
        endFrame();
    }
};
//mpipe-----
struct mpipe {
	Rectangle p,p1,p2;
	void set_mpipe( double x , double y , double w , double h ) ;
	void move( double dx , double dy ) ;
};

//coins
struct coins{
    Circle c,c1;
    void set_coins( double x , double y , double h ) ;
	void move( double dx , double dy ) ;
};

//mushroom
struct mushrooms{
	Rectangle rm;
	Rectangle r;
	Circle c[15];
	void set_mushrooms( double x ,  double h, double y , double w  ) ;
	void move( double dx , double dy ) ;
	void hide();
};

//blocks
struct blocks {
	Rectangle b,b1;
	void set_blocks( double x , double y , double w , double h ) ;
	void move( double dx , double dy ) ;
};


//ground----
struct ground {
	Line l;
	int width;
	void set_ground( double x1 , double x2 ,double y) ;
	void set_width( double wd);
	void move( double dx , double dy ) ;
};
//-----------

//clouds
struct cloud{
    Circle c[15];
    int x,y;
    void set_cloud( double cx , double cy ,double r) ;
	void move( double dx , double dy ) ;
};
//-----

//mario_shape-----
struct mario_shape {
	Circle head ;
	Line body ;
	Rectangle r ;
	bool small_size;
	void shape1( double x , double y , double l=rl, double b=rb, double rad=10 ) ;
	void move( double dx , double dy ) ;
	void moveTo( double x , double y , double l=rl , double rad=10 ) ;
};

//background---
class Mario ;
class background {
    	coins co[n_coins];
	ground g[n_grounds] ;
	mpipe p[n_pipes] ;
	blocks bl[n_blocks];
	cloud cl[n_clouds];
	turtle t[n_turtles] ;
	mushrooms ms[n_mushrooms];
	int time;
	Text t1,t2,t3;
	double pos;
  public:
	double ret_pos(){return pos;}
    background(){
	    pos=0;
        time=300;
        t1.reset(900,20,time);
        t2.reset(100,20,0);
        t3.reset(500,20,3);
	    double dx=-100,dy=-100;
	beginFrame() ;
	int i;
		for(i=0 ; i<n_pipes ; ++i ) {
			p[i].set_mpipe( dx , dy ,0,0) ;
			
		}
		for( i=0 ; i<n_blocks ; ++i ) {
			bl[i].set_blocks( dx , dy,0,0 ) ;
		}
		for( i=0 ; i<n_coins ; ++i ) {
			co[i].set_coins( dx , dy ,0) ;
		}
		for( i=0 ; i<n_grounds ; ++i ) {
			g[i].set_ground( dx , dy,-100 ) ;
		}
		for( i=0 ; i<n_clouds ; ++i ) {
			cl[i].set_cloud( dx , dy,0 ) ;
		}
		for( i=0 ; i<n_turtles ; ++i ) {
            		t[i].set_turtle( dx , dy ,0) ;
 		}
 		for( i=0 ; i<n_mushrooms ; ++i ) {
            		ms[i].set_mushrooms( dx , dy ,0 ,0) ;
 		}

	endFrame() ;
    }
  	void set(char c, int i, float x, float h, float y, float w) ;
  	void settime();
  	void move_turtles() {
  	    int i ;
  	    for( i=0 ; i<2 ; ++i ) {
            if(!t[i].dead)
            t[i].move_between() ;
  	    }
  	}
  	void move( double dx , double dy ) ;
  	void moveTo( double x ) ;
  	int obstacle( mario_shape &m ) ;
  	bool gotcoin( mario_shape &m ) ;
  	int got_mushroom( mario_shape &m );
    Rectangle block(int k){return bl[k].b;}
  	int touchturtle( mario_shape &m );
  	void kill_turtle(int &i){
            t[i].v=0;
            t[i].dead=1;
            t[i].set_turtle(t[i].rt.getX(),t[i].rt.getY()+t_size/4,t[i].d,t_size,t_size/2);
            wait(0.5);
            t[i].moveTo(0,0);}
  	void showmoney(const int &mon){ t2.reset(100,20,mon);}
  	void showlife(const int &l){ t3.reset(500,20,l);}
    int get_pos() { return pos ;}
};

//Mario------
class Mario {
	mario_shape m ;
	int money;
	int life;
  double vy;
  public:
  	Mario( double x , double y ) ;
  	void assignmoney(int mo){money+=mo;}
  	void powerup(){
  	    //if(!m.small_size){get_gun();}
         if(m.small_size){increase_mariosize();}
  	}
 // 	void get_gun(){}
  	int reducelife(){
  	    life-=1;
  	    //m.shape1(x0,g_level-rl/2,rl/2,rb/2,5);
        return life;}
  	void reduce_mariosize(){m.shape1(m.r.getX(),m.r.getY()+rl/4,rl/2,rb/2,5);}
  	void increase_mariosize(){m.shape1(m.r.getX(),m.r.getY()-rl/4,rl,rb,10);}
  	void jump( double v ) ;
  	void move_right( double d , background &bg ) ;
  	void move_left( double d , background &bg ) ;
  	void jump( double v , background &bg ) ;
  	mario_shape& ret_shape() { return m ; }
  	int ret_money() { return money; }
  	void fall(background &bg) ;
    int ret_life() { return life ; } 
};
class player{
  char name[20];
  background bg;
  int score;
  Text t;
public:
char* ret_name() { return name ;}
int ret_score() { return score ;}
void get_name()
{
  int i=0;
  XEvent e;
  char x;
       while(1)
       {
        while(checkEvent(e))
        {	
          if(keyPressEvent(e))
  		    {
  		        x = charFromEvent(e) ;
              cout<<(int)x;
              if(x==13||i==20)
                return;
              else
                {
                  if(x=='\b'&&i>0)
                  name[i--]=' ';
                  else
                  name[i++]=x;

                t.reset(600-i*2,100,name);
                }
          }
        }
        ret_bg().settime();
        ret_bg().move_turtles();
      }
}
  background& ret_bg(){
    return bg;
  }
};

class Menu {
    Rectangle s , h , c , e ,sel;
    Rectangle r1[50] , r2[10] ;
    Text st , hi , cr , ex ,sl , mname ;
    player p ;
    char level[20] ;
  public:
    Menu() {
      strcpy( level , "level1" ) ;
    }
    void set_Menu() ;
    void start_game() ;
    void scores() ;
    void select_level() ;
    void create_level() ;
    void hide() ;
    void show() ;
    void get_filename( char[] ) ;
};
