#include"mario.h"
void mpipe::set_mpipe( double x , double h, double y , double w ) {
	p.reset( x , y , w , h ) ;
	p.hide();
	p1.reset( x, y , w-15 ,h );
	p1.setColor(COLOR("green"));
	p1.setFill();
	p2.reset( x, y-h/2+20, w ,40);
	p2.setColor(COLOR(50,150,50));
	p2.setFill();
}
void mpipe::move( double dx , double dy = 0 ) {
	p.move( dx , dy ) ;
	p1.move(dx,dy);
	p2.move(dx,dy);
}
//---------
void blocks::set_blocks( double x ,  double h, double y , double w ) {
	b.reset( x , y , w , h ) ;
	b.setColor(COLOR(150,50,50)) ;
	b.setFill();
	b1.reset(x , y , w-10 ,h-10);
	b1.setColor(COLOR("red"));
	b1.setFill() ;
}
void blocks::move( double dx , double dy = 0 ) {
	b.move( dx , dy ) ;
	b1.move( dx , dy ) ;
}
//---------

void mushrooms::set_mushrooms( double x ,  double h, double y , double w ) {
	beginFrame();	
	rm.reset( x , y , w , h ) ;
	rm.setColor(COLOR("orange")) ;
	rm.setFill();
	//rm.hide();
	r.reset( x , y+h/4 , w/2 , h/2 );
	r.setColor(COLOR("white")) ;
	r.setFill();
	//r.hide();
	int k=0;
    for(int i=1;i<=4;i++){
        for(int j=i;j<=4;j++){
		if(k<15)
		{
            c[k].reset(x+(j-i+1)*10-w/2,y+h/3-10,10);
            c[k].setColor(COLOR(55+i*30,55+i*15,0));
            c[k++].setFill();
		//c[k-1].hide();
		}
        }
        x+=10.0/2;
        y-=10.0/2;
    }
	endFrame();	
}
void mushrooms::move( double dx , double dy = 0 ) {
	beginFrame();	
	rm.move( dx , dy ) ;
	r.move( dx , dy );
	if(dy!=0)
		r.show();
	for(int j=0;j<15;j++){
	c[j].move(dx,dy);
	if(dy!=0)
		c[j].show();
	}
	endFrame();
}
void mushrooms::hide(){
	rm.hide();
	r.hide();
	for(int j=0;j<15;j++){
	c[j].hide();
	}
}
//-----------

void coins::set_coins( double x , double y , double w=10 ) {
	c.reset( x , y , w ) ;
	c.setColor(COLOR(200,200,0)) ;
	c.setFill() ;
	c1.reset( x , y , w-2);
	c1.setColor(COLOR("yellow")) ;
	c1.setFill() ;
}
void coins::move( double dx , double dy = 0 ) {
	c.move( dx , dy ) ;
	c1.move( dx, dy ) ;
}

//ground
void ground::set_ground( double x1 , double x2 ,double y=g_level) {
	l.reset( x1 , y , x2 ,y ) ;
	l.setColor(COLOR("red")) ;
}
void ground::set_width(double wd){
    width=wd;
}
void ground::move( double dx , double dy = 0 ) {
	l.move( dx , dy ) ;
}

//clouds
void cloud::set_cloud( double x , double y , double r=10 ) {
        int k=0;
        beginFrame();
    for(int i=1;i<=5;i++){
        for(int j=i;j<=5;j++){
		if(k<15)
		{
            c[k].reset(x+j*20,y,r);
            c[k].setColor(COLOR(55+i*30,55+i*30,55+i*30));
            c[k++].setFill();
		}
        }
        x+=-r/2;
        y-=r/2;
    }
    endFrame();
}
void cloud::move( double dx , double dy = 0 ) {
	for(int i=0;i<15;i++)
	c[i].move( dx , dy ) ;
}
//---------

void mario_shape::shape1( double x , double y , double l , double b ,double rad) {
   	r.reset( x , y , b , l ) ;
    head.reset( x , y-l/2+rad , rad ) ;
    head.setColor(COLOR("blue"));
    head.setFill() ;
    body.reset( x , y-l/2 , x , y+l/2 ) ;
    if(b==rb)
        small_size=0;
    else
        small_size=1;
}
void mario_shape::moveTo( double x , double y ,double l, double rad) {
    beginFrame() ;
        head.moveTo( x , y-l/2+rad) ;
        body.moveTo( x , y ) ;
        r.moveTo( x , y ) ;
    endFrame() ;
}
void mario_shape::move( double dx , double dy ) {
	beginFrame() ;
		head.move( dx , dy ) ;
		body.move( dx , dy ) ;
		r.move( dx , dy ) ;
	endFrame() ;
}
//---------
void background::set(char c , int i , float x , float h , float y , float w ) {	

	if(c=='p')
        p[i].set_mpipe( x , h , y , w ) ;
    else if(c=='b')
        bl[i].set_blocks( x , h , y , w );
    else if(c=='c')
        co[i].set_coins( x , y , w );
    else if(c=='g'){
    	if(y!=0)
        	g[i].set_ground( x , w ,y);
        else
        	g[i].set_ground( x , w );
        g[i].set_width(w-x);
    }
    else if(c=='l')
        cl[i].set_cloud( x , y , w);
    else if(c=='t')
        t[i].set_turtle( x , y , w);
    else if(c=='m'){
        ms[i].set_mushrooms( bl[(int)w].b.getX() ,b_size, bl[(int)w].b.getY(),b_size );
    	//ms[i].hide();
    }
}
//--------
void background::settime(){
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    if(time!=300-(int)elapsed)
        t1.reset(900,20,time);
    time=300-elapsed;
}
void background::move( double dx , double dy ) {
	int i ;
	pos+=dx;
	beginFrame() ;
		for( i=1 ; i<n_pipes ; ++i ) {
			p[i].move( dx , dy ) ;
		}
		for( i=1 ; i<n_blocks ; ++i ) {
			bl[i].move( dx , dy ) ;
		}
		for( i=1 ; i<n_coins ; ++i ) {
			co[i].move( dx , dy ) ;
		}
		for( i=1 ; i<n_grounds ; ++i ) {
			g[i].move( dx , dy ) ;
		}
		for( i=1 ; i<n_clouds ; ++i ) {
			cl[i].move( dx , dy ) ;
		}
		for( i=1 ; i<n_turtles ; ++i ) {
            		t[i].move( dx , dy ) ;
 		}
 		for( i=1 ; i<n_mushrooms ; ++i ) {
           		 ms[i].move( dx , dy ) ;
 		}

	endFrame() ;
}

bool background::gotcoin( mario_shape &m ){

    double x = m.r.getX() ;
	double y = m.r.getY() ;
	double x_left , x_right ;
	double y_top , y_bottom ;
	if(!m.small_size){
        x_left=x-rb/2 ; x_right=x+rb/2 ;
	    y_top=y-rl/2 ; y_bottom=y+rl/2 ;
	}
	else{
        x_left=x-rb/4 ; x_right=x+rb/4 ;
	    y_top=y-rl/4 ; y_bottom=y+rl/4 ;
	}
    int i ;

    for( i=1 ; i<n_coins ; ++i ) {
		double cx = co[i].c.getX() ;
        double c_bottom = co[i].c.getY()+c_size/2;
        double c_top = co[i].c.getY()-c_size/2;
		double w = c_size ;

		if( ((y_bottom > c_top) && (y_top < c_bottom) && (x_right >= cx-w/2) && (x_left <= cx-w/2 ))
		  ||((y_bottom > c_top) && (y_top < c_bottom) &&(x_left <= cx+w/2) && (x_right >= cx+w/2 ))
		  ||((y_bottom > c_top) && (y_top < c_bottom) && (x_left <= cx+w/2) && (x_right >= cx-w/2 ))
		  ||((y_top < c_bottom) && (y_bottom  > c_top ) && (x_left <= cx+w/2) && (x_right >= cx-w/2)) ){

            for(int j=0;j<10;j++){
                beginFrame();
                co[i].move(0,-20);
                endFrame();
                wait(0.025);
            }

            co[i].c.hide();
            co[i].c1.hide();
            co[i].c.moveTo(0,0);
            co[i].c1.moveTo(0,0);
            return 1;
        }
	}

	return 0;
}
int background::got_mushroom( mario_shape &m )
{
    double x = m.r.getX() ;
	double y = m.r.getY() ;
	double x_left , x_right ;
	double y_top , y_bottom ;
	if(!m.small_size){
        x_left=x-rb/2 ; x_right=x+rb/2 ;
	    y_top=y-rl/2 ; y_bottom=y+rl/2 ;
	}
	else{
        x_left=x-rb/4 ; x_right=x+rb/4 ;
	    y_top=y-rl/4 ; y_bottom=y+rl/4 ;
	}
    int i ;

    for( i=1 ; i<n_mushrooms ; ++i ) {
		double mx = ms[i].rm.getX() ;
        double m_bottom = ms[i].rm.getY()+b_size/2;
        double m_top = ms[i].rm.getY()-b_size/2;
		double w = b_size ;



		if( (y_bottom > m_top) && (y_top < m_bottom) && (x_right >= mx-w/2) && (x_left <= mx-w/2) ) {
            ms[i].hide();
           			return 1 ;
		}
		else if( (y_bottom > m_top) && (y_top < m_bottom) &&(x_left <=mx+w/2 ) && (x_right >= mx+w/2 ) ) {
			ms[i].hide();
			return 2 ;
		}
		else if((y_bottom > m_top) && (y_top < m_bottom) && (x_left <= mx+w/2) && (x_right >= mx-w/2) ) {
            ms[i].hide();
            return 3 ;
		}
		else if( (y_top < m_bottom+10) && (y_bottom  > m_top ) && (x_left <= mx+w/2) && (x_right >= mx-w/2)  ){
            for(int j=0;j<10;j++){
                beginFrame();
                ms[i].move(0,-b_size/10);
                endFrame();
                wait(0.1);
            }
            return 4;
        }
	}

	return 0;
}
int background::touchturtle( mario_shape &m ){

    double x = m.r.getX() ;
	double y = m.r.getY() ;
	double x_left , x_right ;
	double y_bottom ;
	if(!m.small_size){
        x_left=x-rb/2 ; x_right=x+rb/2 ;
	    y_bottom=y+rl/2 ;
	}
	else{
        x_left=x-rb/4 ; x_right=x+rb/4 ;
	    y_bottom=y+rl/4 ;
	}

    for(int i=1 ; i<n_turtles ; ++i ) {
	     double tx = t[i].rt.getX() ;
		 double h , w ;
		 static int oldtime=305;
		 if(!t[i].small_size)
            h=w=t_size;
         else
            h=w=t_size/2;

	     if((oldtime-time)>=5&&(!(t[i].dead))&&( ((y_bottom > g_level-h) && (x_right >= tx-w/2-10) && (x_left <= tx-w/2))
            ||((y_bottom > g_level-h) && (x_left <= tx+w/2+10 ) && (x_right >= tx+w/2)) )) {
                oldtime=time;
			return 1 ;
		}
		else if((y_bottom > g_level-h-5) && (x_left <= tx+w/2+5) && (x_right >= tx-w/2-10) ) {
            return (2+i);
		}

	 }
return 0;
}

int background::obstacle( mario_shape &m ) {
	double x = m.r.getX() ;
	double y = m.r.getY() ;
	double x_left , x_right ;
	double y_top , y_bottom ;
	if(!m.small_size){
        x_left=x-rb/2 ; x_right=x+rb/2 ;
	    y_top=y-rl/2 ; y_bottom=y+rl/2 ;
	}
	else{
        x_left=x-rb/4 ; x_right=x+rb/4 ;
	    y_top=y-rl/4 ; y_bottom=y+rl/4 ;
	}
    int i ;
	for( i=1 ; i<n_pipes ; ++i ) {
		double px = p[i].p.getX() ;
		double h = p_height , w = p_width ;

		if( (y_bottom > g_level-h) && (x_right >= px-w/2-10) && (x_left <= px-w/2) ) {
			return 1 ;
		}
		else if( (y_bottom > g_level-h) && (x_left <= px+w/2+10 ) && (x_right >= px+w/2 ) ) {
			return 2 ;
		}
		else if( (y_bottom > g_level-h-10) && (x_left <= px+w/2) && (x_right >= px-w/2 ) ) {
            return 3 ;
		}
	}

    for( i=1 ; i<n_blocks ; ++i ) {
		double bx = bl[i].b.getX() ;
        double b_bottom = bl[i].b.getY()+b_size/2;
        double b_top = bl[i].b.getY()-b_size/2;
		double w = b_size ;

		if( (y_bottom > b_top) && (y_top < b_bottom) && (x_right >= bx-w/2-10) && (x_left <= bx-w/2) ) {
			return 1 ;
		}
		else if( (y_bottom > b_top) && (y_top < b_bottom) &&(x_left <= bx+w/2+10 ) && (x_right >= bx+w/2 ) ) {
			return 2 ;
		}
		else if( (y_bottom > b_top-10) && (y_top < b_bottom) && (x_left <= bx+w/2) && (x_right >= bx-w/2) ) {
            return 3 ;
		}
		else if( (y_top < b_bottom+15) && (y_bottom  > b_top ) && (x_left <= bx+w/2) && (x_right >= bx-w/2) ){
            return 4;

        }
	}
	 for( i=1 ; i<n_grounds ; ++i ) {
	    double l_right=g[i].l.getX()+g[i].width/2;
        double l_left=g[i+1].l.getX()-g[i+1].width/2;

        if(y_bottom <= g_level && x_left > l_right && x_right < l_left)
            return 5;
	 }
return 0 ;
}
//----------
Mario::Mario( double x , double y ) {
	m.shape1( x , y ) ;
	money=0;
	life=3;
	reduce_mariosize();
}
void Mario::move_right( double d , background &bg ) {
	if( bg.obstacle(m)!=1 ) {
		bg.move( -d , 0 ) ;
		if(bg.gotcoin(m)){
            assignmoney(10);
            bg.showmoney(money);
		}
		if(bg.got_mushroom(m)==1)
            powerup();

        if(bg.touchturtle(m)==1){
		    if(m.small_size){
                reducelife();
		bg.move(-bg.ret_pos(),0);

                //bg.moveTo(500);
                bg.showlife(life);
            }
            else
                reduce_mariosize();
        }
    }
	bg.settime();
    bg.move_turtles();
}
void Mario::move_left( double d , background &bg ) {
	if( bg.obstacle(m)!=2 ) {
		bg.move( d , 0 ) ;
		if(bg.gotcoin(m)){
            assignmoney(10);
            bg.showmoney(money);
		}
		if(bg.got_mushroom(m)==2)
            powerup();

        if(bg.touchturtle(m)==1){
		    if(m.small_size){
                reducelife();
		bg.move(-bg.ret_pos(),0);

                //bg.moveTo(500);
                bg.showlife(life);
            }
            else
                reduce_mariosize();
        }
		bg.settime();
		bg.move_turtles() ;
	}
}
void Mario::jump( double v , background &bg ) {
    double y = m.r.getY() , x = m.r.getX() ;
    int n=0,q=0;
    char c;
    XEvent e1;
    while(1) {
        if(bg.got_mushroom(m)==3&&v<0)
                powerup();
        if(( bg.obstacle(m)==3 && v<0 )|| (bg.obstacle(m)==4 && v>0) ) break ;
        beginFrame() ;
            m.move( 0 ,-v/2 ) ;
	    wait(0.05) ;
            if(bg.gotcoin(m)){
                assignmoney(10);
                bg.showmoney(money);
            }

            if(v<0&&bg.touchturtle(m)>=2){
                int i=bg.touchturtle(m)-2;
                bg.kill_turtle(i);
            }

            checkEvent(e1);
            while( keyPressEvent(e1) ){
                c = charFromEvent(e1) ;
                if( c=='Q' ) {n++;
                    move_left(10,bg);
                }
                else if( c=='S') {q++;
                    move_right(10,bg);
                }
                x = m.r.getX() ;
		bg.settime();
                break;
            }
        bg.settime();
        bg.move_turtles() ;
        endFrame() ;
        v = v-1 ;
	vy = -v ;
        if( m.r.getY() > y-5 && v < 0 ) {
            m.moveTo( x , y ) ;
            break ;
        }
    }
}

void Mario::fall(background &bg){
    if(bg.obstacle(m)==5){
    	for(int i=0;i<10;i++)
        	m.move(0,10);
   		bg.showlife(reducelife()) ;
        bg.move( -bg.get_pos() , 0 ) ;
    }

    while( (bg.obstacle(m)!=3) ) {
    	
    	double l = rl ;
    	if( m.small_size ) 
    		l = rl/2 ;
    	if( m.r.getY() > g_level-l/2-5 ) {
    		m.moveTo( m.r.getX() , g_level-l/2-5 ) ;
    		break ;
    	}
    	m.move( 0 , vy ) ;
    	wait(0.05) ;
    	vy++ ;

    	if(bg.gotcoin(m)){
                assignmoney(10);
                bg.showmoney(money);
            }

        if(bg.touchturtle(m)>=2){
            int i=bg.touchturtle(m)-2;
            bg.kill_turtle(i);
        }
        bg.settime();
        bg.move_turtles() ;
    }
	vy = 0 ;
}
//-----------

//-Menu---
void Menu::start_game() {
    hide() ;
    Text name( wl/2 , wh/2 , level ) ;
    wait(1) ;

    std::ifstream f;
    //cout << level ;
    strcat( level , ".txt" ) ;
    f.open( level, ios::in ) ;

    char c;int i,x,y;

    while(!f.eof())
    {
        f>>c>>i>>x>>y;
        if(f.eof())
            break;
        else
        switch(c)
        {                               
            case 'm':                
                p.ret_bg().set('m' , i , 0 , 0 , 0 , x );             
                break;
            case 'p':                
                p.ret_bg().set('p' , i , x , p_height , g_level-p_height/2 , p_width );
                break;
            case 'b':               
                p.ret_bg().set('b' , i , x , b_size ,  y , b_size );                     
                break;
            case 'c':                
                p.ret_bg().set('c' , i , x , 0 , y , c_size );              
                break;
            case 'g':                
                p.ret_bg().set('g' , i , x , 0 , 0 ,y);
                break;
            case 'l':                
                p.ret_bg().set('l' , i , x , 0 , y,10 );
                break;
            case 't':                
                p.ret_bg().set('t', i , x , 0 , g_level-t_size/2 , y );
                break;
        }
    }

    f.close();
    
    beginFrame();
    for(int i=0;i<50;i++){
        Rectangle r(wl/2,(wh*(2*i+1)/50)/2,wl,wh/50);
        r.setColor(COLOR(50+i*2,50+i*2,105+i*3));
        r.setFill();
        r.imprint();
    }
    for(int i=0;i<10;i++){
        if(i==0){
            Rectangle r(wl/2,g_level+(wh*(2*i+1)/50)/2,wl,wh/50);
            r.setColor(COLOR(50,150,50));
            r.setFill();
            r.imprint();
        }
        else{
            Rectangle r(wl/2,g_level+(wh*(2*i+1)/50)/2,wl,wh/50);
            r.setColor(COLOR(105+i*15,10+i*5,10+i*5));
            r.setFill();
            r.imprint();
        }
    }

    Mario mario( x0 , g_level-rl/2-5) ;
    endFrame();
    
    p.ret_bg().settime();
    p.ret_bg().move_turtles() ;
    XEvent e;
    char u ;
    double d = 20 ;
    p.ret_bg().showmoney(mario.ret_money());
    Text t(500,100,"Name:");
    p.get_name();

    while(1){
       
        while(checkEvent(e)){
            
            if(keyPressEvent(e))
            {
                u = charFromEvent(e) ;
                cout<<u;
                if( u=='S' ) {
                    mario.move_right( d , p.ret_bg() ) ;
                }
                else if( u=='Q' ) {
                    mario.move_left( d , p.ret_bg() ) ;
                }
                else if( u=='R' ) {
                    mario.jump( 30, p.ret_bg() ) ;
                }
                mario.fall(p.ret_bg());
            p.ret_bg().settime();
            }
        }
        if(p.ret_bg().touchturtle(mario.ret_shape())==1){
            if(mario.ret_shape().small_size){
                p.ret_bg().showlife(mario.reducelife());
            p.ret_bg().move(-p.ret_bg().ret_pos(),0);
            }
            else
                mario.reduce_mariosize();
            
        }
        if( mario.ret_life()==0 ) return ;
        
        p.ret_bg().settime();
        p.ret_bg().move_turtles();
    }
}

void Menu::scores() {
    
    hide() ;

    Text t1( wl/4 , wh/4 , "Name") ;
    Text t2( wl/4+200 , wh/4 , "Score") ;
    Text b( wl/4 , wh/4 + 350, "Back to menu" ) ;
    Rectangle b1( wl/4 , wh/4 , 200 , 30 ) ;
    Rectangle b2( wl/4+200 , wh/4 , 200 , 30 );
    Rectangle b3( wl/4 , wh/4+350 , 200 , 30 ) ;
    Text n[10] , s[10] ;
    char name[20] ;
    int score ;
    strcpy( name , p.ret_name() ) ;
    fstream f( "scores.txt" , ios::in | ios::out | ios::app ) ;
    f << name << " " << p.ret_score() ;

    int i = 0 ;
    f.seekg(0) ;
    while( !f.eof() ) {
        f >> name >> score ;
        if( f.eof() ) break ;
        n[i].reset( wl/4 , wh/4+40+30*i , name ) ;
        s[i].reset( wl/4+200 , wh/4+40+30*i , score ) ;
        i++ ;
    }

    int p = getClick() ;
    double x = p/65536 , y = p%65536 ;

    if( (abs(x-wl/4) <= 100) && ( abs(y-wh/4-350) <= 15 ) ) 
        return ;
}

void Menu::set_Menu() {
    //initCanvas( "Mario" , wl , wh ) ;
    beginFrame() ;
        for(int i=0;i<50;i++){
            r1[i].reset(wl/2,(wh*(2*i+1)/50)/2,wl,wh/50);
            r1[i].setColor(COLOR(50+i*2,50+i*2,105+i*3));
            r1[i].setFill();
            //r1[i].imprint();
        }
        for(int i=0;i<10;i++){
            if(i==0){
                r2[i].reset(wl/2,g_level+(wh*(2*i+1)/50)/2,wl,wh/50);
                r2[i].setColor(COLOR(50,150,50));
                r2[i].setFill();
                //r2[i].imprint();
            }
            else{
                r2[i].reset(wl/2,g_level+(wh*(2*i+1)/50)/2,wl,wh/50);
                r2[i].setColor(COLOR(105+i*15,10+i*5,10+i*5));
                r2[i].setFill();
                //r.imprint();
            }
        }
        mname.reset( wl/2 , 300 , "SUPER MARIO" ) ;
        mname.setColor(COLOR("red")) ;
        st.reset( x0 , 400 , "Start Game" ) ;
        s.reset( x0 , 400 , 200 , 30 ) ;
        hi.reset( x0 , 450 , "High Scores" ) ;
        h.reset( x0 , 450 , 200 , 30 ) ;
        cr.reset( x0 , 500 , "Create Level" ) ;
        c.reset( x0 , 500 , 200 , 30 ) ;
        sl.reset( x0 , 550 , "Select level" ) ;
        sel.reset( x0 , 550 , 200 , 30 ) ;
        ex.reset( x0 , 600 , "Exit" ) ;
        e.reset( x0 , 600 , 200 , 30 ) ;
    endFrame() ;
}

void Menu::hide() {
    st.hide() ;
    s.hide() ;
    hi.hide() ;
    h.hide() ;
    cr.hide() ;
    c.hide() ;
    sl.hide() ;
    sel.hide() ;
    ex.hide() ;
    e.hide() ;
    mname.hide() ;
}

void Menu::show() {
    st.show() ;
    s.show() ;
    hi.show() ;
    h.show() ;
    cr.show() ;
    c.show() ;
    sl.show() ;
    sel.show() ;
    ex.show() ;
    e.show() ;
    mname.show() ;
}

void Menu::select_level() {
    hide() ;
    std::fstream f( "Levels.txt" , ios::in ) ;
    char level_name[20] ;
    f.seekg(0) ;

    int i = 0  , n = 0 , j ;
    Text t[10] ; Rectangle rt[10] ;
    while( !f.eof() ) {
        f >> level_name ;
        if( f.eof() ) break ;
        t[i].reset( wl/4 , wh/4+40*i , level_name ) ;
        rt[i].reset( wl/4 , wh/4+40*i , 200 , 30 ) ;
        i++ ;
    }
    n = i ;

    Text b( wl/4 , wh/4+200 , "Back to menu" ) ;
    
    Rectangle b2( wl/4 , wh/4+200 , 200 , 30 ) ;

    int p = getClick() ;
    double x = p/65536 , y = p%65536 ;

    for( i=0 ; i<n ; ++i ) {
        if( (abs(x-wl/4) <= 100) && (abs(y-(wh/4+40*i)) <=15) ) {
            f.seekg(0) ;
            j = 0 ;
            while( j<=i ) {
                f >> level_name ;
                j++ ;
            }
            strcpy( level , level_name ) ;
            return ;
        }   
    }

    if( (abs(x-wl/4) <= 100) && ( abs(y-wh/4-200) <= 15 ) ) 
        return ;
}

void get_flname(char name[20]){
    Text t;
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
                  {name[i--]=' ';name[i]='\0';}
                  else
                  {name[i++]=x;name[i]='\0';}

                t.reset(750,50,name);
                }
            }
        }
    }
}

void Menu::create_level() {
    hide() ;
    beginFrame();
    for(int i=0;i<50;i++){
        Rectangle r(wl/2,(wh*(2*i+1)/50)/2,wl,wh/50);
        r.setColor(COLOR(50+i*2,50+i*2,105+i*3));
        r.setFill();
        r.imprint();
    }
    for(int i=0;i<10;i++){
        if(i==0){
            Rectangle r(wl/2,g_level+(wh*(2*i+1)/50)/2,wl,wh/50);
            r.setColor(COLOR(50,150,50));
            r.setFill();
            r.imprint();
        }
        else{
            Rectangle r(wl/2,g_level+(wh*(2*i+1)/50)/2,wl,wh/50);
            r.setColor(COLOR(105+i*15,10+i*5,10+i*5));
            r.setFill();
            r.imprint();
        }
    }

    background bg;
    double d=30;
   
    endFrame();

    Text t,t1;
    t.reset(750,20,"Level Name:");

    char file_name[20];
    get_flname(file_name);
    t1.reset(750,50,file_name);
    std::fstream g;
    g.open("Levels.txt",ios::out|ios::app);
    g<<file_name;
    g.close();
    strcat(file_name,".txt");
    std::fstream f;
    f.open(file_name,ios::out);

    int x,y,x1;
    int np=0,nb=0,nc=0,nl=0,nt=0,ng=0,nm=0;
    int s,i;
    char c='1';
    XEvent e;
    Line l(0,g_level-b_size/2-100,1380*7,g_level-b_size/2-100);
    l.setColor(COLOR("blue"));
    bg.set('p' , np++ , 50 , p_height/4 , 50 , p_width/4 );
    bg.set('b' , nb++ , 150 , b_size ,  50 , b_size );
    bg.set('c' , nc++ , 250 , 0 , 50 , c_size );
    bg.set('g' , ng++ , 300 , 0 , 50 , 400);
    bg.set('l' , nl++ , 400 , 0 , 50 , 10 );
    bg.set('t', nt++ , 550 , 0 , 50 , 0 );
    //bg.set('m' , nm++ , 0 , 0 , 0 , 0  );
    mushrooms m_demo;
    m_demo.set_mushrooms( 650 , b_size, 50 ,b_size);
    nm++;
    Line l1(0,100,1000,100);
    for(int j=0;j<=7;j++)
    {
        Line l1(j*100,0,j*100,100);
        l1.imprint();
    }
        while(c!='0')
        {
            while(checkEvent(e))
            {
                if(keyPressEvent(e))
                {
                c = charFromEvent(e);
                switch(c)
                    {
                    case 'Q':
                        beginFrame();
                        bg.move(d,0);
                        endFrame();
                        break;
                    case 'S':
                        beginFrame();
                        bg.move(-d,0);
                        endFrame();
                        break;
                    }
                }
            
                else if(mouseButtonPressEvent(e))
                {
                x=e.xbutton.x;y=e.xbutton.y;
                //cout<<x<<" "<<y;
                for(int j=0;j<7;j++)
                    if(y<=100)
                        if((x>=j*100&&x<=(j+1)*100))
                        {
                            switch(j)
                            {
                                case 0:
                                        c='p';
                                        break;
                                case 1:
                                        c='b';
                                        break;
                                case 2:
                                        c='c';
                                        break;
                                case 3:
                                        c='g';
                                        break;
                                case 4:
                                        c='l';
                                        break;
                                case 5:
                                        c='t';
                                        break;
                                case 6:
                                        c='m';
                                        break;
                            }

                            switch(c)
                            {                               
                                case 'm':
                                    s=getClick();
                                    x=s/65536;y=s%65536;
                                    for(i=0;i<nb;i++)
                                        if(x>bg.block(i).getX()-b_size/2 
                                            && x<bg.block(i).getX()+b_size/2 
                                            && y>bg.block(i).getY()-b_size/2 
                                            && y<bg.block(i).getY()+b_size/2){break;}

                                    bg.set('m' , nm++ , 0 , 0 , 0 , i );
                                    f<<c<<" "<<(nm-1)<<" "<<i<<" "<<0<<" ";
                                    break;
                                case 'p':
                                    s=getClick();
                                    x=s/65536;y=s%65536;
                                    bg.set('p' , np++ , x , p_height , g_level-p_height/2 , p_width );
                                    f<<c<<" "<<(np-1)<<" "<<x<<" "<<0<<" ";
                                    break;
                                case 'b':
                                    s=getClick();
                                    x=s/65536;y=s%65536;
                                    if(y>g_level-b_size/2-100){
                                        bg.set('b' , nb++ , x , b_size ,  g_level-b_size/2-100 , b_size );
                                        f<<c<<" "<<(nb-1)<<" "<<x<<" "<<g_level-b_size/2-100<<" ";
                                    }
                                    else{
                                        bg.set('b' , nb++ , x , b_size ,  g_level-b_size/2-250 , b_size );
                                        f<<c<<" "<<(nb-1)<<" "<<x<<" "<<g_level-b_size/2-250<<" ";
                                    }
                                    break;
                                case 'c':
                                    s=getClick();
                                    x=s/65536;y=s%65536;
                                    bg.set('c' , nc++ , x , 0 , y , c_size );
                                    f<<c<<" "<<(nc-1)<<" "<<x<<" "<<y<<" ";
                                    break;
                                case 'g':
                                    s=getClick();
                                    x=s/65536;y=s%65536;
                                    s=getClick();
                                    x1=s/65536;
                                    bg.set('g' , ng++ , x , 0 , 0 ,x1);
                                    f<<c<<" "<<(ng-1)<<" "<<x<<" "<<x1<<" ";
                                    break;
                                case 'l':
                                    s=getClick();
                                    x=s/65536;y=s%65536;
                                    //cin>>x1;
                                    bg.set('l' , nl++ , x , 0 , y,10 );
                                    f<<c<<" "<<(nl-1)<<" "<<x<<" "<<y<<" ";
                                    break;
                                case 't':
                                    s=getClick();
                                    x=s/65536;y=s%65536;
                                    s=getClick();
                                    x1=s/65536;
                                    bg.set('t', nt++ , x , 0 , g_level-t_size/2 , x1-x );
                                    f<<c<<" "<<(nt-1)<<" "<<x<<" "<<x1-x<<" ";
                                    break;
                            }
                            break;
                        }
                }

            }    
        
        }

    f.close();    
}
//-------
