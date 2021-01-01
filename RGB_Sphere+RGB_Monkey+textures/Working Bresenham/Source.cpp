#include<FreeImage.h>
#include<iostream>
#include<time.h>
#include <ctime>
#include <cstdlib>
#define WIDTH 800
#define HEIGHT 600
#define BPP 24
using namespace std;
typedef struct Vertice{
	float x;
	float y;
}Vertice;
int abso(int a);
int sign(int a);
void bresenhame(int V1.x, int V2.x, int V1.y, int V2.y,FIBITMAP *bitmap);
void dessin(int V1.x, int V2.x, int V1.y, int V2.y);
void downTriangle(FIBITMAP *g,Vertice v1, Vertice v2, Vertice v3);
void upTriangle(FIBITMAP *g,Vertice v1, Vertice v2, Vertice v3);
void dessinerTri(FIBITMAP *g, Vertice v1, Vertice v2, Vertice v3);
int main(int argc ,char** argv){
	int V1.x=0, V2.x=300, V1.y=0, V2.y=300;
	FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP);
	Vertice v1, v2, v3;
	if (!bitmap)
		exit(1);
	// vers le haut 
	/*v1.x = 10; v1.y = 10;
	v2.x = 210; v2.y = 10;
	v3.x = 110; v3.y = 300;*/
	// vers le bas 
	/*v1.x = 150; v1.y = 10;
	v2.x = 200; v2.y = 300;
	v3.x = 100; v3.y = 300;*/
	// 
	v1.x = 100; v1.y = 60;
	v2.x = 200; v2.y = 20;
	v3.x = 310; v3.y = 150;


	dessinerTri(bitmap, v1, v2, v3);
	
	system("pause");
	return 0;
}
int abso(int a){
	if (a<0){
		return -a;
	}
	return a;
}
int sign(int a){
	if (a>0){
		return 1;
	}
	if (a < 0){
		return -1;
	}
	return 0;
}
void bresenhame(int V1.x, int V2.x, int V1.y, int V2.y,FIBITMAP *bitmap){
	int e, s1,s2,deltax,deltay, x = 0, y = 0;
	int temp;
	bool change = false;
	FreeImage_Initialise();
	RGBQUAD color;
	x = V1.x;
	y = V1.y;
	s1 = sign(V2.x - V1.x);
	s2 = sign(V2.y - V1.y);
	deltax = abso(V2.x - V1.x);
	deltay = abso(V2.y - V1.y);
	e = 2 * deltay - deltax;
	if (deltax<deltay){
		temp = deltax;
		deltax = deltay;
		deltay = temp;
		change = true;
	}
	for (int i = 0; i < deltax; i++){
		color.rgbRed = 255;
		color.rgbGreen = 255;
		color.rgbBlue = 255;
		FreeImage_SetPixelColor(bitmap, x, y, &color);
		while (e>0){
			if (change){
				x = x + s1;
			}
			else{
				y = y + s2;
			}
			e = e - 2 * deltax;
		}
		if (change){
			y = y + s2;
		}
		else{
			x = x + s1;
		}
		e = e + 2*deltay;
	}
	if (FreeImage_Save(FIF_PNG, bitmap, " test.png", 0))
		//cout << "Image s u c c e s s f u l l y saved ! " << endl;
	FreeImage_DeInitialise();
}
void dessin(int V1.x, int V2.x, int V1.y, int V2.y){
	float m, b;
	int x = 0,y,temp;
	FreeImage_Initialise();
	FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP);
	RGBQUAD color;
	m = (V2.y - V1.y) / (V2.x - V1.x);
	b = V2.y - m*V2.x;
	if (m > 1){
		temp = V1.x;
		V1.x = V1.y;
		V1.y = temp;
		temp = V2.x;
		V2.x = V2.y;
		V2.y = temp;
	}
	if (V1.x > V2.x){
		temp = V1.x;
		V1.x = V2.x;
		V2.x = temp;
	}
	for (x = V1.x; x < V2.x; x++){
		y = (int)(m*x + b);
		FreeImage_SetPixelColor(bitmap, x, y, &color);
	}
	if (FreeImage_Save(FIF_PNG, bitmap, " test.png", 0))
		cout << "Image s u c c e s s f u l l y saved ! " << endl;
	FreeImage_DeInitialise();
}
void downTriangle(FIBITMAP *g,Vertice v1, Vertice v2, Vertice v3){
	cout << "bottom" << endl;
	cout << v1.x << endl << v2.x << endl << v3.x <<  endl;
	cout << v1.y << endl << v2.y << endl << v3.y << endl;
	float inv1 = (float)((v2.x - v1.x) / (v2.y-v1.y));
	float inv2 = (float)((v3.x - v1.x) / (v3.y - v1.y));
	cout << inv1 << endl << inv2 << endl;
	float  curV2.x = v1.x;
	float curx2 = v1.x;
	for (int scanliney = v1.y; scanliney <= v2.y; scanliney++){
		bresenhame((int)curV2.x, (int)curx2, scanliney, scanliney,g);
		curV2.x += inv1;
		curx2 += inv2;
	}
}
void upTriangle(FIBITMAP *g, Vertice v1, Vertice v2, Vertice v3){
	cout << "top" << endl;
	cout << v1.x << endl << v2.x << endl << v3.x << endl;
	cout << v1.y << endl << v2.y << endl << v3.y << endl;
	float inv1 =(float) ((v3.x - v1.x) / (v3.y - v1.y));
	float inv2 = (float)((v3.x - v2.x) / (v3.y - v2.y));
	cout << inv1 << endl << inv2 << endl;
	float  curV2.x = v3.x;
	float curx2 = v3.x;
	for (int scanliney = v3.y; scanliney > v1.y; scanliney--){
		bresenhame((int)curV2.x, (int)curx2 ,scanliney , scanliney, g);
		curV2.x -= inv1;
		curx2 -= inv2;
	}
}
void dessinerTri(FIBITMAP *g, Vertice v1, Vertice v2, Vertice v3){
	if (v2.y == v3.y){
		downTriangle(g, v1, v2, v3);
	}
	else{
		if (v1.y == v2.y){
			upTriangle(g, v1, v2, v3);
		}
		else{
			Vertice v4;
			v4.x = v1.x+((v2.y-v1.y)/(v3.y-v1.y))*(v3.x-v1.x);
			v4.y = v2.y;
			downTriangle(g, v1, v2, v4);
			upTriangle(g, v2, v4, v3);
		}
	}
}
