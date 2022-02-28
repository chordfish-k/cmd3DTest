#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <pthread.h>

#include "Display.h"
#include "Vec.h"
#include "Matrix.h"
#include "Draw.h"
#include "Obj.h"


#define H 80
#define W 150

pthread_t th;

HANDLE hOutput;
COORD headCoord = { 0, H+1 };
COORD beginCoord = { 1, 0 };
Display display(W, H);
Figure fig;

int mouseEvents = 0;
bool mouseDown = false;
bool mouseRDown = false;
bool keys[255];
COORD mouse;
COORD lastPoint = {-1, -1};

double arc = 3.1415926535 / 180.0;


void *mainLoop(void *v){
	int BeginTime = GetTickCount();

	while(1){
			
		if (GetTickCount() - 1000 / 6 >= BeginTime){
			SetConsoleCursorPosition(hOutput, beginCoord);
			
			display.clear();
			
			Draw::DrawObject(display, fig);
			display.show();
			//map(20, 30);
			BeginTime = GetTickCount();  
		}
		
		//Sleep(1);
	}
}

COORD GetLocation() {
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;

	GetConsoleMode(hInput, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode |= ENABLE_MOUSE_INPUT;
	SetConsoleMode(hInput, mode | ENABLE_MOUSE_INPUT);

	INPUT_RECORD record;
	DWORD n;
	for (COORD pos = {}; ReadConsoleInput(hInput, &record, 1, &n) && n == 1; ) {
		if (record.EventType != MOUSE_EVENT)
			continue;

		mouseEvents = 1;

		COORD pos_new = record.Event.MouseEvent.dwMousePosition;
		if (pos_new.X == pos.X && pos_new.Y == pos.Y)
			continue;
		pos = pos_new;

		COORD ans;
		ans.X = pos.X, ans.Y = pos.Y;
		return ans;
	}
	return {};
}

double angleToArc(double a) {
	return a * arc;
}

double clamp(double value, double minimun, double maximun) {
		if (value > maximun) {
			return maximun;
		}
		if (value < minimun) {
			return minimun;
		}
		return value;
	}

void CheckMouse(){
	mouseDown = GetKeyState(VK_LBUTTON) >> 8;
	//if(mouseDown) mouseEvents = 1;
	mouseRDown = GetKeyState(VK_RBUTTON) >> 8;
	if(mouseDown || mouseRDown) mouseEvents = 1;
	else keys[0] = 0;

	mouse = GetLocation();
	mouse.X = mouse.X / 2  ;
	mouse.Y = mouse.Y ;

	int x = mouse.X;
	int y = mouse.Y;
	
	if(mouseDown){
		if(lastPoint.X == -1){
			lastPoint = {(SHORT)x, (SHORT)y};
		}else if(lastPoint.X != x && lastPoint.Y != y){
			//Vec3 v(x - lastPoint.X, y - lastPoint.y, 0);
			double dx = clamp(x - lastPoint.X, -10, 10);
			double dy = clamp(y - lastPoint.Y, -10, 10);
			double angleX = angleToArc(90 * dy / 10.0);
			double angleY = angleToArc(-90 * dx / 10.0);
			Vec3 angle(angleX, angleY, 0.0);
			
			fig.rotate(angle);
			
			lastPoint = {(SHORT)x, (SHORT)y};
		}
	}else{
		lastPoint = {-1, -1};
	}
	
	//SetConsoleCursorPosition(hOutput, headCoord);
	//cout << "X: "<<x <<"   Y: " << y;
}


int main(int argc, char** argv) {
	pthread_create(&th, NULL, mainLoop, NULL);
	
	
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	
	//vector<double> a = {1, 3};
	//vector<double> b = {10, 15};
	//RowVec av(a);
	//RowVec bv(b);
	//RowVec av = makePoint(1, 1);
	//RowVec bv = makePoint(15, 15);
	//Vec2 av(1, 3);
	//Vec2 bv(10, 15);
	
	fig = ReadObj("a.obj");
	Vec3 mv(5, 5, 0);
	//fig.move(mv);
	fig.scale(15);
	
	//Draw::DrawLine(display, av, bv);
	
	//vector<Vec3> fs = {Vec3(10, 0, 0), Vec3(2, 10, 0), Vec3(50, 90, 0)};
	//Face f(fs);
	//Draw::DrawFace(display, f);
	
	while(1){
		
		//检测本窗口是否为当前活动窗口  		
		mouseEvents = 0;
		if(GetConsoleWindow() == GetForegroundWindow()){
			CheckMouse();
		}
		
	}
	
	
	return 0;
}
