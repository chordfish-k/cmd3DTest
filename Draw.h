#ifndef DRAW_H
#define DRAW_H

#include <cmath>

#include "Vec.h"
#include "Face.h"
#include "Matrix.h"
#include "Display.h"
#include "Obj.h"

namespace Draw{
	
	void DrawPoint(Display &display, Vec3 point){
		Vec3 zero(display.width()/2-15, display.height()/2);
		point = point + zero;
		if(point.x < 0 || point.y < 0 || point.x >= display.width() || point.y >= display.height()) return;
		
		vector<vector<int>> &grid = display.screen_buffer->p;
		grid[round(point.y)][round(point.x)] = 1;
	}
	
	void DrawLine(Display &display, Vec3 st, Vec3 ed){
		//st.print();
		//ed.print();
		//vector<vector<int>> &grid = display.screen_buffer->p;
		int x = st.x;
		int y = st.y;
		int x2 = ed.x;
		int y2 = ed.y;
		int dx = abs(x2 - x);
		int dy = abs(y2 - y);
		int r = (dx < dy) ? 1 : 0;
		if(r){	
			int tmp = x;
			x = y;
			y = tmp;
			tmp = x2;
			x2 = y2;
			y2 = tmp;
			tmp = dx;
			dx = dy;
			dy = tmp;
		}
		int ix = (x2 - x) > 0 ? 1 : -1;
		int iy = (y2 - y) > 0 ? 1 : -1;
		int cx = x, cy = y;
		int d = dy * 2 - dx;
		
		while(cx != x2){
			if(d < 0){
				d += dy * 2;	
			}else{
				d += (dy - dx) * 2;
				cy += iy;
			}
			Vec2 v;
			if(r){
				//cout << cy << ", " << cx << endl;
				//v = {cy, cx};
				v = Vec2(cy, cx);
				//DrawPoint(display, {cy, cx});
			}else{
				//cout << cx << ", " << cy << endl;
				v = Vec2(cx, cy);
				//DrawPoint(display, {cx, cy});
			}
			//v.print();
			DrawPoint(display, v);
			cx += ix;
		}
		//display.screen_buffer->print();
	}
	
	void DrawFace(Display &display, Face &f) {
		for (int i = 0; i < f.ls.size(); i++) {
			DrawLine(display, f.v[f.ls[i].first], f.v[f.ls[i].second]);
		}
	}
	
	void DrawObject(Display &display, Figure& obj) {
		for (int i = 0; i < obj.fs.size(); i++) {
			int v_nums = obj.fs[i].size();

			vector<Vec3> vs;
			for (int j = 0; j < v_nums; j++) {
				vs.push_back(obj.vs[obj.fs[i][j]]);
			}
			Face f(vs);
			//Face f(vs);
			DrawFace(display, f);
		}
	}
}

#endif
