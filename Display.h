#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <sstream>
#include <vector>

#include "Matrix.h"

class Display
{
	public:
		Matrix<int> *screen_buffer;
	private:
		int _height;
		int _width;
		
		string buff;
		
	public:
		Display(int W, int H){
			screen_buffer = new Matrix<int>(H, W, 0);
			_height = H;
			_width = W;
			//cout << H << " " << W;
			
			
			
		}
		~Display(){
			delete screen_buffer;
		}
		
		void show(){
			buff = "";
			for(int i=0; i<_height; i++){
				for(int j=0; j<_width; j++){
					
					if(screen_buffer->at(i, j)){
						buff += "¡ö";
					}
					else{
						buff += "  ";
					}
					
				}
				buff += "\n";
			}
			cout << buff;
		}
		
		int height() {return _height;}
		int width() {return _width;}
		
		void clear(){
			screen_buffer->initialize();
		}
		
};

#endif
