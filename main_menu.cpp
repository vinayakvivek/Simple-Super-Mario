/*
	Simple Super Mario : ( by 150050102 & 150050098 )

*/

#include "mario.h"


int main() {
	initCanvas( "Mario" , wl , wh ) ;
	Menu m ;
	m.set_Menu() ;

	while(1) {
		int p = getClick() ;
		double x = p/65536 , y = p%65536 ;

		if( abs(x-x0) <= 100 ) {
			if( abs(y-400) <= 15 ) {
				m.start_game() ;
				cout << "s" ;
				Text t( wl/2 , wh/2 , "Game Over" ) ;
				wait(5) ;
			}
			else if( abs(y-450) <= 15 ) {
				m.scores() ;
				cout << "h" ;
			}
			else if( abs(y-500) <= 15 ) {
				m.create_level() ;
				cout << "c" ;
			}
			else if( abs(y-550) <= 15 ) {
				m.select_level() ;
			}
			else if(  abs(y-600) <= 15 ) {
				exit(0) ;
			}
		}
		m.show() ;
	}

}
