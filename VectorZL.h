#ifndef VECTORZL_H
#define VECTORZL_H

#include<iostream>
#include "FreeImage.h"
#include<math.h>
#include<string.h>

using namespace std;

//image constants
#define WIDTH 800
#define HEIGHT 600
#define BPP 24

//scene constants
#define XLENG 400
#define YLENG 400

//camera settings
#define NEAR -1
#define FAR -400

#define INFINI 20000

void Test();

void WorldBuilder();

template <class T> 
T Max(T const &a,T const &b,T const &c){
	return (a>=b&&a>=c)?a:((b>=c)?b:c);
}

template <class T> 
T Min(T const &a,T const &b,T const &c){
	return (a<=b&&a<=c)?a:((b<=c)?b:c);
}

template <class T> 
void Swap(T &a,T &b){
	T x=a; a=b; b=x;
}

template <class T> 
T abso(T a){
	if (a<0){
		return -a;
	}
	return a;
}
template <class T> 
T sign(T a){
	if (a>0){
		return 1;
	}
	if (a < 0){
		return -1;
	}
	return 0;
}

template<class T> 
class VectorZL{
	public:
	T x,y,z;
	RGBQUAD Claire;
 	VectorZL<T>(T =0,T =0,T =0);
	// VectorZL<T>(VectorZL<T> const &vec); 
	VectorZL<T> operator+(const VectorZL<T>& Vicky)const;
 	T operator *  (const VectorZL<T>& Vicky)const;
	VectorZL<T> operator *  (const T& mult)const;
	VectorZL<T> operator / (const T& mult)const;
 	VectorZL<T> operator-(const VectorZL<T>& Vicky)const;
 	//Produit vectoriel
 	VectorZL<T> operator^(const VectorZL<T>& Vicky)const;
	T Rayon()const;
	VectorZL<T> unitVector();
	VectorZL<T> getColor()const;
	//Useful for Coloring.. just make sure you are following the clockwise "convention"
	bool Inside(VectorZL<T> const &a,VectorZL<T> const &b, VectorZL<T> const &c);


	//streams	
 	bool operator !=  (const VectorZL<T>& Vicky)const;
	void setColor(VectorZL<T> x);

	template<class U>
	friend ostream& operator<<(ostream& s,const VectorZL<U>& v);

	template<class U>
	friend istream& operator>>(istream& s,VectorZL<U> v);
};
template<class T> 
class GMatrix{	
	public:
	T mat[4][4];
 	GMatrix<T>();
	VectorZL<T> De_Translation();	// removes & returns the translation component
	GMatrix<T> operator+(const GMatrix<T>& Mathiew)const;
	GMatrix<T> operator+(const VectorZL<T>& Vick)const;// it will be used in translation component..
 	GMatrix<T> operator /  (float var);
	GMatrix<T> operator*(float var);
	VectorZL<T> operator*(const VectorZL<T>& Vicky)const;
	GMatrix<T> operator*(const GMatrix<T>& Mathiew)const;
 	
 	GMatrix<T> operator-(const GMatrix<T>& Vick)const;
	GMatrix<T> operator-(const VectorZL<T>& Vick)const;
	void Set_Scale(VectorZL<T> Vick);	// scales the GMatrix 
	//streams	
	template<class U>	
	friend ostream& operator<<(ostream& s,const GMatrix<U>& v);
	template<class U>
	friend istream& operator>>(istream& s,GMatrix<U> v);
};
typedef VectorZL<float> Victor;
typedef GMatrix<float> Mody;	// simplifying my typenames..
class Entity{
	Victor rotation=Victor(0,0,0),position=Victor(0,0,0),scale=Victor(1,1,1);
	virtual void RefreshModel();
	Mody model;
public:
	Entity(Victor = Victor(0,0,0),Victor = Victor(0,0,0));
	virtual void setPosition(Victor const  rot);
	virtual void modelPosition(Victor const  rot);
	virtual Victor	getPosition()const;
	virtual void translate(Victor const  disp);
	virtual void setRotation(Victor const  disp);//angles of rotation..
	virtual Victor	getRotation();
	virtual void setScale(Victor const  rot);
	virtual Victor getScale()const;
	virtual void rotate(Victor rot);
	virtual Mody getModelisation();
};
class Camera : public Entity {
	Mody proj,viewport,visual;
	public:
	Victor **Buffer=NULL;
	int top=0,bottom=-1,right=0,left=-1;//I wrote this before we studied The Ratio technique..
	//I didn't change it, because it's still not causing problems..
	Camera();
	virtual void RefreshProjection();
	virtual void RefreshViewport();
	virtual void translateVisual(Victor trans);
	virtual void rotateVisual(Victor rot);
	
	
	
	virtual void setVisual(Victor chng);
	virtual void printSettings();
	virtual Mody getProjection();
	virtual Mody getViewport();
	virtual Mody getVisualisation();
	void LookAt(Victor = Victor(0,0,0),Victor =Victor(0,1,0));
};
class Scene;
class Object : public Entity{
	public :
	RGBQUAD color;
	int count;
	bool **Line=NULL;	//much like a transition matrix
	bool display=false;
	bool Coloring=true;
	Victor *Vertex=NULL;
	Object(int = 1);
	virtual void setLine(int a,int b);
	virtual void Draw(Scene &scene);
	Object *svt=NULL;	//this should help the scene class;
};

class Circle : public Object{
	public:
	Circle(int step,Victor cent,float =1);
	Victor centre;
	float ray;
};

class Sphere : public Object{
	public:
	float ray;
	Victor centre;
	Victor **Virty=NULL;
	bool ***seg=NULL;//all set to true in the constructor, but what if you wanted a hemisphere or something..this would help a lot..
	Sphere(int step,Victor cent,float ray);
	Sphere();
	virtual void Draw(Scene &scene);
};

class Cylindre : public Sphere{
	public:
	int longitude;
	Cylindre(int =15,Victor =Victor(0,0,0));
	void Draw(Scene &scene);
};

class Scene{
	public:
	bool correction = true;//set true to use the Z-buffer to get correct images..  
	Camera camera;
	FIBITMAP *bitmap=NULL;
	Object *objects=NULL;
	string name;
	Scene(string = "test.png");
	~Scene();	//strictly avoid calling the destructor explicitly!!
	Object* CreateObject(int =15);	//15 is the default angle step
	Object* CreateObject(int step,Victor cent,float r,int =3);
	Object* CreateObject(int n,Victor cent);//Cylinder things..
	void DrawPicture();
	void SaveImage();
	void PrintCameraSettings();
	Victor Localise(Object* p,Victor const &v);
	void setBackgroundcol(RGBQUAD color);
	void MoveCamera(Victor a);
	friend Object* CreateQuad(Scene &S,Victor a,Victor b,Victor c,Victor d);
};

void DrawLineEval(FIBITMAP* betty, Victor V1, Victor V2);
void DDAlgo(FIBITMAP* betty, Victor V1, Victor V2);
void LineBrezenham(FIBITMAP* betty, Victor V1, Victor V2);
void MidpointLine(FIBITMAP* betty, Victor V1, Victor V2);
bool LegalPoint(int x,int y);
Object* CreateQuad(Scene &S,Victor a,Victor b,Victor c,Victor d);
//be carefull.. use this after projecting..(Incorrect Image)
void pseudo_Naive_coloring(FIBITMAP* betty,Victor const &V1,Victor V2,Victor V3);
void Z_Buffering(Victor **&Buffer,Victor const &V1,Victor V2,Victor V3);


#endif
