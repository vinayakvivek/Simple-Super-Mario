#include "matrix.h"
// this is sample file 
// Please incorporate the print function in your matrix.cpp from here 

using namespace std;

Matrix::Matrix(){
	
	M = new int *[n] ;
	
	for( int i=0 ; i<n ; ++i ) {
	
		M[i] = new int[m] ;
		
		for( int j=0 ; j<m ; ++j ) {
			M[i][j] = 0 ;
		}
	}
}


void Matrix::print(){
	for(int i = 0; i < n; i++){
		for (int j = 0; j < m; ++j){
			cout << M[i][j] << " ";
		}
		cout << endl;
	}
}
