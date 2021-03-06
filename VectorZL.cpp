#include"VectorZL.h"


template<class T>
VectorZL<T>::VectorZL(T a, T b,T c){ x=a,y=b,z=c;
}

// template<class T>
// VectorZL<T>::VectorZL<T>( VectorZL<T> const &vec){
// 	x=veck.x; y=veck.y; z=veck.z;
	
// }

template<class T>VectorZL<T> VectorZL<T>::operator +  (const VectorZL& Vicky)const{
	return VectorZL<T>(x+Vicky.x,y+Vicky.y,z+Vicky.z);
}

template<class T>
VectorZL<T> VectorZL<T>::operator - (const VectorZL& Vicky)const{
	return VectorZL<T>(x-Vicky.x,y-Vicky.y,z-Vicky.z);
}

//Produit vectoriel
template<class T>
VectorZL<T> VectorZL<T>::operator ^  (const VectorZL& Vicky)const{
	VectorZL<T> a(y*Vicky.z-z*Vicky.y,z*Vicky.x-x*Vicky.z,x*Vicky.y-y*Vicky.x);
//	a.setColor(VectorZL<T>(getColor().y*Vicky.getColor().z-getColor().z*Vicky.getColor().y,getColor().z*Vicky.getColor().x-getColor().x*getColor().Vicky.getColor().z,getColor().x*Vicky.getColor().y-getColor().y*Vicky.getColor().x).unitVector()*255);
	return a;

}

template<class T>
T VectorZL<T>::operator *  (const VectorZL& Vicky)const{
	return x*Vicky.x+y*Vicky.y+z*Vicky.z;
}

template<class T>
VectorZL<T> VectorZL<T>::operator *  (const T& mult)const{
	VectorZL<T> a(x*mult,y*mult,z*mult);
	a.Claire=this->Claire;
	return a;
}

template<class T>
VectorZL<T> VectorZL<T>::operator /  (const T& mult)const{
	return (mult==0)?VectorZL<T>(INFINI,INFINI,INFINI):(VectorZL<T>(x/mult,y/mult,z/mult));
}

template<class T>
bool VectorZL<T>::operator !=  (const VectorZL& Vicky)const{
	return (x!=Vicky.x)||(y!=Vicky.y)||(z!=Vicky.z);
}

template<class T>
ostream& operator << (ostream& s,const VectorZL<T>& v){
	s<<"("<< v.x<<","<<v.y<<","<<v.z<<")";
	return s;
}

template<class T>
istream& operator >> (istream& s,VectorZL<T> v){
	s>>v.x;	s>>v.y;	s>>v.z;
	return s;
}
template<class T>
T VectorZL<T>::Rayon()const{
	return sqrt(x*x+y*y+z*z);
}



template<class T>
VectorZL<T> VectorZL<T>::unitVector(){
	T r=Rayon();
	VectorZL<T> a(x/r,y/r,z/r);
	a.setColor(getColor());
	return a;
}

template<class T>
void VectorZL<T>::setColor(VectorZL<T> x){
	// cout <<x;
		Claire.rgbRed = x.x;
		Claire.rgbGreen =x.y;
		Claire.rgbBlue = x.z;
	}
template<class T>
VectorZL<T> VectorZL<T>::getColor()const{
	return Victor(Claire.rgbRed,Claire.rgbGreen,Claire.rgbBlue);
}

template<class T>
bool VectorZL<T>::Inside(VectorZL<T> const &a,VectorZL<T> const &b, VectorZL<T> const &c){
	return ((((*this-a)^(b-a)).z>=0)&&(((*this-b)^(c-b)).z>=0)&&(((*this-c)^(a-c)).z>=0))||((((*this-a)^(b-a)).z<0)&&(((*this-b)^(c-b)).z<0)&&(((*this-c)^(a-c)).z<0));
}



template<class T>
GMatrix<T>::GMatrix(){
for(int i=0;i<4;i++)
	for(int j=0;j<4;j++)
		mat[i][j]=(i==j)?1:0;
}

template<class T>
GMatrix<T> GMatrix<T>::operator +  (const GMatrix<T>& Mathiew)const{
	GMatrix<T> bingo;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			bingo.mat[i][j]=mat[i][j]+Mathiew.mat[i][j];
	return bingo;
}
template<class T>
GMatrix<T> GMatrix<T>::operator +  (const VectorZL<T>& Vick)const{
	GMatrix<T> bingo=*this;
	bingo.mat[0][3]+=Vick.x;
	bingo.mat[1][3]+=Vick.y;
	bingo.mat[2][3]+=Vick.z;
	return bingo;
}

template<class T>
VectorZL<T> GMatrix<T>::De_Translation(){
	VectorZL<T> a(mat[0][3],mat[1][3],mat[2][3]);
	mat[0][3]=0;	mat[1][3]=0;	mat[2][3]=0;
	return a;
}

template<class T>
GMatrix<T> GMatrix<T>::operator *  (float var){
	GMatrix<T> p;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			p.mat[i][j]=mat[i][j]*var;
	return p;
}


template<class T>
GMatrix<T> GMatrix<T>::operator /  (float var){
	GMatrix<T> p;
	if(var!=0)
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				p.mat[i][j]=mat[i][j]*var;
	else
		cout<<"\033[31mException \033[0m: Division By zero, but the program will continue..";
	return p;
}

template<class T>
VectorZL<T> GMatrix<T>::operator *  (const VectorZL<T>& Vicky)const{
	// T x=Vicky.x*mat[3][0]+Vicky.y*mat[3][1]+Vicky.z*mat[3][2]+mat[3][3];
	// if(x!=0&&x!=1)
	// 	return y*(1/x);
	//The Scene::Localise() function is the one responsible for conversion process..
	VectorZL<T> a(Vicky.x*mat[0][0]+Vicky.y*mat[0][1]+Vicky.z*mat[0][2]+mat[0][3],Vicky.x*mat[1][0]+Vicky.y*mat[1][1]+Vicky.z*mat[1][2]+mat[1][3],Vicky.x*mat[2][0]+Vicky.y*mat[2][1]+Vicky.z*mat[2][2]+mat[2][3]);
	a.Claire=Vicky.Claire;
	return a;
}
			//🙄️
template<class T>
GMatrix<T> GMatrix<T>::operator * (const GMatrix<T>& Mathiew)const{
	GMatrix<T> p;
	T s;
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
		s=0;
			for(int k=0;k<4;k++)
				s+=mat[i][k]*Mathiew.mat[k][j];
			p.mat[i][j]=s;
		}
	}
	return p;
}

template<class T>
GMatrix<T> GMatrix<T>::operator -  (const VectorZL<T>& Vick)const{	// it's pathetic, 😔️ but I needed it quickly..
	GMatrix<T> bingo=*this;
	bingo.mat[0][3]-=Vick.x;
	bingo.mat[1][3]-=Vick.y;
	bingo.mat[2][3]-=Vick.z;
	return bingo;
}

template<class T>
void GMatrix<T>::Set_Scale(VectorZL<T> Vick){
	mat[0][0]=Vick.x;
	mat[1][1]=Vick.y;
	mat[2][2]=Vick.z;
}

template<class U>
ostream& operator << (ostream& s,const GMatrix<U>& v){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++)
			s<<v.mat[i][j]<<" ";
		s<<endl;
	}
	return s;
}

template<class U>
istream& operator >> (istream& s,GMatrix<U> v){
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			s>>v.mat[i][j];
	return s;
}

void Entity::RefreshModel(){
	Mody scaler,rotationalx,rotationaly,rotationalz;
	scaler.mat[0][0]=scale.x;
	scaler.mat[1][1]=scale.y;
	scaler.mat[2][2]=scale.z;

	rotationalx.mat[1][1]=cos(3.14/180*rotation.x);
	rotationalx.mat[2][1]=sin(3.14/180*rotation.x);
	rotationalx.mat[1][2]=-sin(3.14/180*rotation.x);
	rotationalx.mat[2][2]=cos(3.14/180*rotation.x);

	//cout<<"x rotation"<<rotationalx;

	rotationaly.mat[0][0]=cos(3.14/180*rotation.y);
	rotationaly.mat[2][0]=-sin(3.14/180*rotation.y);
	rotationaly.mat[0][2]=sin(3.14/180*rotation.y);
	rotationaly.mat[2][2]=cos(3.14/180*rotation.y);

	//cout<<"y rotation"<<rotationaly;

	rotationalz.mat[0][0]=cos(3.14/180*rotation.z);
	rotationalz.mat[0][1]=-sin(3.14/180*rotation.z);
	rotationalz.mat[1][0]=sin(3.14/180*rotation.z);
	rotationalz.mat[1][1]=cos(3.14/180*rotation.z);

	//cout<<"z rotation"<<rotationalz;

	cout<<"model"<<endl;
	model=(scaler*rotationalx*rotationaly*rotationalz);//-position;
	cout<<model;
}

void Camera::RefreshProjection(){

}

void Camera::RefreshViewport(){

}


void Camera::translateVisual(Victor trans){
	setPosition(trans);
	// visual.mat[0][3]+=trans.x;
	// visual.mat[1][3]+=trans.y;
	// visual.mat[2][3]+=trans.z;
}

void Camera::rotateVisual(Victor rot){
	//rot=rot*3.14/180;//next time remember to override *=
	//TODO : to be continued..

}

void Camera::setVisual(Victor chng){
	setPosition(chng);
	// visual.mat[0][3]=chng.x;
	// visual.mat[1][3]=chng.y;
	// visual.mat[2][3]=chng.z;
}

void Camera::LookAt(Victor Loky,Victor uppy){
	Mody x;
	x=x-getPosition();
	Victor dir=(Loky-getPosition()).unitVector();
	cout <<"direction vector"<<dir<<endl;
	//cout<<"visual mover"<<endl<<x;
	if(dir*uppy==0){
		Victor Zaxis=Victor(-dir.x,-dir.y,-dir.z);// TODO: override - operator..
		Victor Xaxis=(uppy.unitVector())^Zaxis;//Reminder: ^ Produit vectoriel..
	visual.mat[0][0]=Xaxis.x; visual.mat[1][0]=uppy.unitVector().x; visual.mat[2][0]=Zaxis.x;
	visual.mat[0][1]=Xaxis.y; visual.mat[1][1]=uppy.unitVector().y; visual.mat[2][1]=Zaxis.y;
	visual.mat[0][2]=Xaxis.z; visual.mat[1][2]=uppy.unitVector().z;  visual.mat[2][2]=Zaxis.z;
	cout <<"visual "<<endl<<visual;
	visual.mat[0][4]=(visual*x).mat[0][4];
	visual.mat[1][4]=(visual*x).mat[1][4];
	visual.mat[2][4]=(visual*x).mat[2][4];
	}
	else
		cout<<"\033[31mWarning!!\033[0m make sure to input a compatible UP vector next time.."<<endl;


}

Entity::Entity(Victor a,Victor b){
	position=a;
	rotation=b;
	RefreshModel();
}

Mody Entity::getModelisation(){
	return model;
}

Camera::Camera(){

//projection matrix would be standardised for the moment
	proj.mat[0][0]= 2*NEAR/(right-left);
	proj.mat[1][1]= 2*NEAR/(top-bottom);
	proj.mat[2][2]= (FAR+NEAR)/(NEAR-FAR);
	proj.mat[2][3]= 2*NEAR*FAR/(FAR-NEAR);
	proj.mat[1][2]= (bottom+top)/(bottom-top);
	proj.mat[3][3]= 0;
	proj.mat[3][2]=1;
	proj.mat[0][2]=(left+right)/(left-right);	//I struggled before adding this line..

//ViewPort initialisation:
	viewport.mat[0][0]= XLENG/2;
	viewport.mat[1][1]= YLENG/2;
	viewport.mat[2][2]=0;
	viewport.mat[3][3]= 1;
	viewport.mat[0][3]= XLENG/2-0.5;
	viewport.mat[1][3]= YLENG/2-0.5;
	
	//buffer should be later set free if correction boolean in the scene is false..
	//but it's okay..

	Buffer=new Victor*[WIDTH];
	for (int i = 0; i < WIDTH; i++){
		Buffer[i]=new Victor[HEIGHT];
		for (int j = 0; j < HEIGHT; j++){
			Buffer[i][j]=Victor(INFINI,INFINI,INFINI);	//if we want to do exactly as we were taught..
			Buffer[i][j].setColor(Victor(0,0,0)); //for a dark background
		}
	}
	


}





void Entity::setPosition(Victor const  rot){
	position=rot;
}

void Entity::modelPosition(Victor const  rot){
	model.mat[0][3]=-rot.x;	model.mat[1][3]=-rot.y;	model.mat[2][3]=-rot.z;
}

Victor	Entity::getPosition() const{
	return position;
}

void Entity::translate(Victor const disp){
	position=position+disp;
}

void Entity::setRotation(Victor const disp){
	rotation = disp;
	RefreshModel();
}

void Entity::setScale(Victor const rot){
	scale=rot;
	RefreshModel();
}
Victor Entity::getScale ()const{
	return scale;
}

void Entity::rotate(Victor const  rot){

}

Victor	Entity::getRotation(){
	return rotation;
}

Mody Camera::getProjection(){
	return proj;
}
Mody Camera::getViewport(){
	return viewport;
}
Mody Camera::getVisualisation(){
	return visual;
}

void Camera::printSettings(){
	cout<<"Projection"<<endl<<getProjection();
	cout<<"Visualisation"<<endl<<getVisualisation();
	cout<<"Viewport"<<endl<<getViewport();
	cout<<"Product"<<endl<<getViewport()*getProjection()*getVisualisation();//*mod;
}






Object::Object(int a){
	count=a;
	Vertex= new Victor[a];
	Line=new bool*[a];
	for(int i=0;i<a;i++){
		Line[i]=new bool[a];
		for(int j=0;j<a;j++)
			Line[i][j]=false;
	}//	let the points be independent before definition..
	svt=NULL;
	cout<<"A new object has been created"<<endl;




}

void Object::setLine(int a,int b){
	if(a>count||a<0||b>count||b<0)
		cout<<"Can't set Line, illegal indexing detected"<<endl;
	else{
		Line[a][b]=(a!=b);	//just making sure there will be no meaningless values;
		//Line[b][a]=(a!=b);	//transposing to ensure that the line will be drawn
	}
}

void Object::Draw(Scene &scene){
	cout<<"Modelisation\n"<<getModelisation();
	for(int i=0;i<count;i++)
		for(int j=0;j<count;j++)
			if(Line[i][j]){
			//3/12/2020 10:11 DDAlgo has been chosen because of productivity;
				DDAlgo(scene.bitmap,scene.Localise(this,Vertex[i]),scene.Localise(this,Vertex[j]));
				//cout<<endl;
					//	LineBrezenham(bitmap,Localise(p->Vertex[i]),Localise(p->Vertex[j]));
					//Brezenham & midpoint Algorithms are the only usable codes in scene coding for now.. (1:16 AM 18/11/2020) "Apparently not.."
			}
}

Circle::Circle(int step,Victor cent,float r){//prise en charge seulement pour la norme z
	centre=cent;
	ray=r;
	count= 360/step;
	Vertex= new Victor[count];
	Line=new bool*[count];
	for(int i=0;i<count;i++){
		Line[i]=new bool[count];
		for(int j=0;j<count;j++)
			Line[i][j]=false;
	}//	let the points be independent before definition..
	for(int i=0;i<count;i++)
		Vertex[i]=Victor(centre.x+ray*cos(3.14*i*step/180),centre.y+ray*sin(3.14*i*step/180),centre.z);
	for(int i=0;i<count;i++)	//initialising circle
		Line[i][(i+1)]=true;
	//Line[count-1][(0)]=true;
	svt=NULL;
	cout<<"A new Circle has been created"<<endl;
}

Sphere::Sphere(int step,Victor cent,float r){

	modelPosition(cent);
	Line=NULL;	//here I'll need a ternary relation
	count=360/step+2;//360/step+2
	ray=r;
	seg=new bool**[count];
	Virty=new Victor*[count];
	for(int i=0;i<count;i++){
		seg[i]=new bool*[count/2];
		Virty[i]=new Victor[count];
		for(int j=0;j<count/2;j++){
			seg[i][j]=new bool[count];
		}
	}
	for(int i=0;i<count;i++)
		for(int j=0;j<count/2;j++)
			for(int k=0;k<count/2;k++)
				seg[i][j][k]=false;	//just making sure that segfaults won't occur..
	cout<<"how??"<<endl;
	for(int i=0;i<count;i++)
		for(int j=0;j<count/2;j++){
			seg[i][j][(i+1)%(count)]=true;
			Virty[i][j]=Victor(ray*sin(3.14*j*step/180)*cos(3.14*i*step/180),ray*sin(3.14*j*step/180)*sin(3.14*i*step/180),ray*cos(3.14*j*step/180));
			Virty[i][j].setColor(Victor(abs(255*sin(3.14*j*step/180)*cos(3.14*i*step/180)),abs(255*sin(3.14*j*step/180)*sin(3.14*i*step/180)),abs(255*cos(3.14*j*step/180))));//
			// cout <<"Red "<<Virty[i][j].ClairergbRed<<endl;
			// cout <<"Green "<<Virty[i][j].Claire.rgbGreen<<endl;
			// cout <<"Blue "<<Virty[i][j].Claire.rgbBlue<<endl;

		}
}

Sphere::Sphere(){}

void Sphere::Draw(Scene &scene){
	
	cout <<"Let's draw a sphere.."<<endl;
	
	if(Coloring){

		for(int i=0;i<count;i++){
			for(int j=0;j<count/2;j++){
				for(int k=0;k<count;k++){
					if(seg[i][j][k]){
						if(Virty[i][j]!=Virty[k][j]){	//this condition saves a lot of stuff..
							if(scene.correction){
								Z_Buffering(scene.camera.Buffer,scene.Localise(this,Virty[i][j]),scene.Localise(this,Virty[k][j]),scene.Localise(this,Virty[i][(j+1)%count]));
								Z_Buffering(scene.camera.Buffer,scene.Localise(this,Virty[((i+1)%(count))][(j+1)%(count/2)]),scene.Localise(this,Virty[(i+1)%count][j]),scene.Localise(this,Virty[i][(j+1)%(count/2)]));
							}
							else{
							//	cout <<"this "<<Virty[i][j].getColor()<<" to ";
								pseudo_Naive_coloring(scene.bitmap,scene.Localise(this,Virty[i][j]),scene.Localise(this,Virty[k][j]),scene.Localise(this,Virty[i][(j+1)%count]));
								pseudo_Naive_coloring(scene.bitmap,scene.Localise(this,Virty[((i+1)%(count))][(j+1)%(count/2)]),scene.Localise(this,Virty[(i+1)%count][j]),scene.Localise(this,Virty[i][(j+1)%(count/2)]));
							}
						}
					}
				}
			}
		}
		if(scene.correction){//omit to get a hole in the sphere.. 
			for(int i=0;i<count-1;i++)
				Z_Buffering(scene.camera.Buffer,scene.Localise(this,Virty[i][0]),scene.Localise(this,Virty[i+1][1]),scene.Localise(this,Virty[i][1]));
		}


	}

	if(display){
		cout<<"Sphere's Modelisation:\n"<<scene.objects->getModelisation();
		cout<<"Position:\n"<<scene.objects->getPosition();
		Mody z=scene.camera.getViewport()*scene.camera.getProjection()*scene.camera.getVisualisation()*(getModelisation());
		z=z*(1/z.mat[3][3]);
		cout<<"Product before point :\n"<<z;
		for(int i=0;i<count;i++){
			for(int j=0;j<count/2;j++){
				for(int k=0;k<count;k++){
					if(seg[i][j][k]){
						if(Virty[i][j]!=Virty[k][j]){
							//cout<<scene.Localise(this,Virty[i][j])<<endl;
							if(!scene.correction)
								DDAlgo(scene.bitmap,scene.Localise(this,Virty[i][j]),scene.Localise(this,Virty[k][j]));
						}
					}
				}
			}
		}
		for(int i=0;i<count;i++){
			for(int j=0;j<count/2-1;j++){
				//	if(seg[i][(j+1)%count][k]||seg[i][(j+1)%count][(k+1)%(count)])
						//if(Virty[i][j]!=Virty[i][(j+1)%(count/2)])
				DDAlgo(scene.bitmap,scene.Localise(this,Virty[i][j]),scene.Localise(this,Virty[i][(j+1)%(count/2)]));
			}
		}
	}



}

Cylindre::Cylindre(int step,Victor cent){
	count= 360/step;
	setPosition(cent);
	longitude=101;//longitude is the length of our cylinder

	seg=new bool**[longitude];
	for(int i=0;i<longitude;i++){
		seg[i]=new bool*[count];
		for(int j=0;j<count;j++){
			seg[i][j]=new bool[count];
			for(int k=0;k<count;k++){
				seg[i][j][k]=false;
			}
		}
	}
	Virty=new Victor*[longitude];
	for(int i=0;i<longitude;i++){
		Virty[i]=new Victor[count];
		for(int j=0;j<count;j++){
			Virty[i][j]=Victor((cent.x+0.5+abs(cos(3.14*i/longitude/8*5))*cos(3.14/180*j*step)),(cent.y+0.5+abs(cos(3.14*i/longitude/8*5))*sin(step*3.14/180*j)),cent.z-0.5+i*0.01);
			seg[i][j][(j+1)%count]=true;
		}
	}
}

void Cylindre::Draw(Scene &scene){
	if(display){
	cout<<"Did we make it??"<<endl;
		for(int i=0;i<longitude;i++){
			for(int j=0;j<count;j++){
				for(int k=0;k<count;k++){
					if(seg[i][j][k]){
						if(Virty[i][j]!=Virty[k][j]){
							DDAlgo(scene.bitmap,scene.Localise(this,Virty[i][j]),scene.Localise(this,Virty[i][k]));
						//	cout<<scene.Localise(this,Virty[i][j])<<scene.Localise(this,Virty[i][k])<<endl;
							}
						}
				}
			}
		}
		for(int i=0;i<count;i++){
			for(int j=0;j<longitude-1;j++){
				//	if(seg[i][(j+1)%count][k]||seg[i][(j+1)%count][(k+1)%(count)])
						//if(Virty[i][j]!=Virty[i][(j+1)%(count/2)])
				DDAlgo(scene.bitmap,scene.Localise(this,Virty[j][i]),scene.Localise(this,Virty[(j+1)%longitude][i]));
			}
		}
	}
}

Scene::Scene(string a){
	name=a;
	objects=NULL;
	bitmap=FreeImage_Allocate(WIDTH,HEIGHT,BPP);
	if(!bitmap)
		exit(1);//What?! We can't even allocate images? Die!
}

Victor Scene::Localise(Object* p,Victor const &v){
		Mody x=camera.getViewport()*camera.getProjection()*camera.getVisualisation()*(p->getModelisation());
//cout<<v.getColor()<<endl;
		if(((v.x*x.mat[3][0]+v.y*x.mat[3][1]+v.z*x.mat[3][2]+x.mat[3][3]))!=0&&((v.x*x.mat[3][0]+v.y*x.mat[3][1]+v.z*x.mat[3][2]+x.mat[3][3]))!=1)
			x=x*(1/((v.x*x.mat[3][0]+v.y*x.mat[3][1]+v.z*x.mat[3][2]+x.mat[3][3])));

		Victor a=x*(v); //!!!	these two lines
		a.setColor(v.getColor());//!!! bugged me for a while..
		if(correction){//
			Mody f=camera.getVisualisation()*(p->getModelisation());
			if(((v.x*f.mat[3][0]+v.y*f.mat[3][1]+v.z*f.mat[3][2]+f.mat[3][3]))!=0&&((v.x*f.mat[3][0]+v.y*f.mat[3][1]+v.z*f.mat[3][2]+f.mat[3][3]))!=1)
				f=f*(1/((v.x*f.mat[3][0]+v.y*f.mat[3][1]+v.z*f.mat[3][2]+f.mat[3][3])));
			a.z=((f*v).z);//it won't do any harm.. useful for Z_buffering..
		}
		// if(a.getColor()!=v.getColor())
		// 	cout<<a.getColor()<<" to "<<v.getColor();


		return a;

}

void Scene::DrawPicture(){
	cout <<endl<<"Let's draw our scene.."<<endl;
	Object *p=objects;

	while(p!=NULL){
		//hide objects with (ObjectName).display=false ; (ObjectName).Coloring=false
		p->Draw(*this);
		p=p->svt;
	}
	if(correction)//now we copy our data from the buffer to the image
		for (int i = 0; i < WIDTH; i++)
		{
			for (int j = 0; j < HEIGHT; j++)
			{
				FreeImage_SetPixelColor(bitmap,i,j,&camera.Buffer[i][j].Claire);
				//how satisfying.. when I made the buffer this morning and it was really
				//smooth and easy to implement it because my conception helped a lot..
				//I guess hard work pays off after all.. 09:50AM 18/12/2020
			}
			
		}
		

}

Object* Scene::CreateObject(int n){
	if(objects==NULL){
		objects=new Object(n);
		return objects;
	}
	Object *p=objects;
	while(p->svt!=NULL)
		p=p->svt;
	p->svt=new Object(n);
	return p;
}

Object* Scene::CreateObject(int step,Victor cent,float r,int dimension){
	if(dimension==2){
		if(objects==NULL){
			objects=new Circle(step,cent,r);
			return objects;
		}
		Object *p=objects;
		while(p->svt!=NULL)
			p=p->svt;
		p->svt=new Circle(step,cent,r);
		cout<<"A circle has been created"<<endl;
		return p;
	}
	if(dimension==3){
		if(objects==NULL){
			objects=new Sphere(step,cent,r);
			return objects;
		}
		Object *p=objects;
		while(p->svt!=NULL)
			p=p->svt;
		p->svt=new Sphere(step,cent,r);
		cout<<"A circle has been created"<<endl;
		return p;
	}
	return NULL;
}

Object* Scene::CreateObject(int n,Victor centy){
	if(objects==NULL){
		objects=new Cylindre(n,centy);
		cout<<"The first object is created"<<endl;
		return objects;
	}
	Object *p=objects;
	while(p->svt!=NULL)
		p=p->svt;
	p->svt=new Cylindre(n,centy);
	return p;
}

void Scene::PrintCameraSettings(){
	camera.printSettings();
}

void Scene::setBackgroundcol(RGBQUAD color){
	for(int i=0;i<WIDTH;i++)
		for(int j=0;j<HEIGHT;j++){
			if(correction){
				if(camera.Buffer[i][j].z==INFINI)
					camera.Buffer[i][j].setColor(Victor(color.rgbRed,color.rgbGreen,color.rgbBlue));
			}
			else
				FreeImage_SetPixelColor(bitmap,i,j,&color);
		}
	cout<<"Background color "<<Victor(color.rgbRed,color.rgbGreen,color.rgbBlue)<<endl;

}

void Scene::MoveCamera(Victor a){
	camera.setPosition(a);
	camera.setVisual(a);
}

Scene::~Scene(){

}

void Scene::SaveImage(){
	if(FreeImage_Save(FIF_PNG,bitmap,"hello.png",0))
			cout<<"Image successfully saved!"<<endl;
}

typedef VectorZL<float> Veck;
void Test(){	//I used this when I first wrote the templates..(Sometime in October 2020)
	Veck a(2,2,2);
	cout<<(Veck(0,1,0)^Veck(1,0,0))<<endl;
	cout<< (Veck(0,0,1)^Veck(1,0,0))<<endl;
	Mody x;
	cout<< x;
	cout<<(a^Veck(1,0,0))<<endl;
}

void WorldBuilder(){
	cout<<"Welcome to the my virtual world builder, I hope you enjoy the trip.."<<endl;
	FreeImage_Initialise();

	Scene scene("hello.png");
	cout<<"\033[33mWere they created?\033[0m"<<endl;

	// scene.CreateObject(15,Victor(-5,-5,-5),2);
	// // scene.camera.translateVisual(Victor(5,0,0));
	// scene.camera.LookAt(Victor(-5,-5,-5),Victor(-2,-3,5));

// 	scene.CreateObject(15,Victor(0,0,-5),2);
// //	scene.camera.translateVisual(Victor(0,10,0));
// //	scene.camera.LookAt(Victor(0,0,0),Victor(0,0,1));

	Object *p=	scene.CreateObject(15,Victor(2,2,2),1);
	scene.camera.LookAt(Victor(5,5,5),Victor(3,-1,-2));
//	p->setScale(Victor(2,2,2));



	// scene.CreateObject(15,Victor(5,5,5),2);
	// // scene.camera.translateVisual(Victor(15,0,0));
	// scene.camera.LookAt(Victor(5,5,5),Victor(3,-1,-2));

	// scene.CreateObject(15,Victor(0,0,0),2);
	// scene.camera.translateVisual(Victor(0,0,-10));
	// scene.camera.LookAt(Victor(0,0,0),Victor(0,1,0));


	// scene.CreateObject(15,Victor(-5,0,0),2);
	// scene.camera.translateVisual(Victor(15,0,0));
	


	//CreateQuad(scene,Victor(-50,-10,-100),Victor(50,-10,-100),Victor(50,10,-100),Victor(-50,10,-100));
	//scene.camera.LookAt(Victor(-10,0,0),Victor(-1,-1,2));


	//-------will you look at this code graveyard..
	//-------How sad is it to think that in a past time, these were once totally functional lines..
	//CreateQuad(scene,Victor(-10,-15,-50),Victor(10,-15,-50),Victor(10,15,-50),Victor(-10,15,-50));
	//scene.CreateObject(1,Victor(0,0,-50),5);
	//CreateQuad(scene,Victor(-10,-20,-50),Victor(10,-20,-50),Victor(10,20,-50),Victor(-10,20,-50));
	//scene.CreateObject(15,Victor(-20,-20,-100),50,3);	//sphere draw
	//Object *p=scene.CreateObject(15,Victor(450,450,-50));
	//Object *p=scene.CreateObject(45,Victor(100,100,-50));
	//p->setScale(Victor(20,20,20));
	//p->setRotation(Victor(-45,-45,0));
	//cout<<"Viewport"<<
	//DrawLineEval(bitmap,Victor(0,0,0),Victor(WIDTH/2,HEIGHT/2,0));
	//MidpointLine(bitmap,Victor(0,0,0),Victor(WIDTH/2,HEIGHT/2,0));
//LineBrezenham(bitmap,Victor(0,0,0),Victor(WIDTH/2,HEIGHT,0));
	//Drawsagradientfrombluetogreen:
	/*
	for(int i=0;i<WIDTH;i++){
		for(int j=0;j<HEIGHT;j++){
			color.rgbRed=0;
			color.rgbGreen=(double)i/WIDTH*255.0;
			color.rgbBlue=(double)j/HEIGHT*255.0;
			FreeImage_SetPixelColor(bitmap,i,j,&color);
			//Noticehowwe'recallingthe&operatoron"color"
			//sothatwecanpassapointertothecolorstruct.
		}
	}
	*/

//	p=scene.objects;


	cout<<"\033[36mI believe they're there somewhere, if I don't make it through, promise me you'll debug this out..\033[0m"<<endl;

//this should be the last value in the Z-BUFFER.. it's still my favorite color..
	RGBQUAD color;
	color.rgbBlue=100.0;
	color.rgbRed=10.0;
	color.rgbGreen=125.0;
	scene.setBackgroundcol(color);

	scene.PrintCameraSettings();
	scene.DrawPicture();
	scene.SaveImage();
	cout<<"\033[36mI'm happy I had to deal with no segfaults..\033[0m"<<endl;
	FreeImage_DeInitialise();	//Cleanup!
}

Object* CreateQuad(Scene &S,Victor a,Victor b,Victor c,Victor d){
Object *p=S.CreateObject(4);
	p->Vertex[0]=a;
	p->Vertex[1]=b;
	p->Vertex[2]=c;
	p->Vertex[3]=d;
//	for(int i=0;i<4;i++)
//		S.objects->setLine(i,(i+1)%4);

	return p;
}


void DrawLineEval(FIBITMAP* betty,RGBQUAD color, Victor V1, Victor V2){
	double m=((double)(V2.y-V1.y))/(V2.x-V1.x);
	if(abs(m)<1){
		for(int i=V1.x;i<=V2.x;i++){
			FreeImage_SetPixelColor(betty,i,floor(V1.y+m*(i-V1.x)),&color);
		}
	}
	else{
		m=1/m;
		for(int i=V1.y;i<=V2.y;i++){
			FreeImage_SetPixelColor(betty,floor(V1.x+m*(i-V1.y)),i,&color);
		}
	}
}

void DDAlgo(FIBITMAP* betty, Victor V1, Victor V2){

	//	Was left for Ali to Code
	RGBQUAD coolio=V1.Claire;
	// coolio.rgbRed=V1.x;
	// coolio.rgbGreen=V1.y;
	// coolio.rgbBlue=V1.z;

	//cout<<V1.getColor();


	Victor start_p;
	Victor end_p;
	if (V1.x <= V2.x)
	{
		start_p.x = V1.x;
		start_p.y = V1.y;
		end_p.x = V2.x;
		end_p.y = V2.y;
	}
	else {
		start_p.x = V2.x;
		start_p.y = V2.y;
		end_p.x = V1.x;
		end_p.y = V1.y;
	}
	int delta_x = end_p.x - start_p.x;
	int delta_y = end_p.y - start_p.y;
	float m = (double)delta_y / (double)delta_x;
	FreeImage_SetPixelColor(betty, floor(start_p.x + 0.5), floor(start_p.y + 0.5), &coolio);
	if (delta_x == 0) {
		if (start_p.y < end_p.y)
			for (int y = start_p.y + 1; y < end_p.y; y++)
				FreeImage_SetPixelColor(betty, start_p.x, y, &coolio);
		else
			for (int y = end_p.y + 1; y < start_p.y; y++)
				FreeImage_SetPixelColor(betty, start_p.x, y, &coolio);
	}
	else if (delta_y == 0)	{
		if (start_p.x < end_p.x)
			for (int x = start_p.x + 1; x < end_p.x; x++)
				FreeImage_SetPixelColor(betty, x, start_p.y, &coolio);
		else
			for (int x = end_p.x + 1; x < start_p.x; x++)
				FreeImage_SetPixelColor(betty, x, start_p.y, &coolio);
	}
	else if (abs(m) < 1) {
		float y = start_p.y;
		for (int x = start_p.x + 1; x < end_p.x; x++)		{
			y = y + m;
			FreeImage_SetPixelColor(betty, x, floor(y + 0.5), &coolio);
		}
	}
	else {
		float x = start_p.x;
		if (start_p.y < end_p.y)
			for (int y = start_p.y + 1; y < end_p.y; y++)			{
				x = x + 1.0 / m;
				FreeImage_SetPixelColor(betty, floor(x + 0.5), y, &coolio);
			}
		else
			for (int y = start_p.y - 1; y > end_p.y; y--)			{
				x = x - 1.0 / m;
				FreeImage_SetPixelColor(betty, floor(x + 0.5), y, &coolio);
			}
	}
	FreeImage_SetPixelColor(betty, floor(end_p.x + 0.5), floor(end_p.y + 0.5), &coolio);
}


//be carefull.. use this after projecting..(Incorrect Image)
void pseudo_Naive_coloring(FIBITMAP* betty,Victor const &V1,Victor V2,Victor V3){//in image plane
	Victor Surf= ((V3-V1)^(V2-V1));//reminder: ^ est le produit vectoriel..
	if(Surf.z<0){
		Swap(V2,V3);
		Surf=Victor(0,0,0)-Surf;//TODO : implement negativity in the template..
	}

	float Trigo_Surface=Surf.z*0.5;//I got the surface!! The Surface!!..

	//getting borders
	float min_x=Min(V1.x,V2.x,V3.x),max_x=Max(V1.x,V2.x,V3.x),min_y=Min(V1.y,V2.y,V3.y),max_y=Max(V1.y,V2.y,V3.y);
	Victor P;
	float alpha,beta,gamma;

	// cout<<"Vector 1"<<V1.getColor()<<endl;
	// cout<<"Vector 2"<<V2.getColor()<<endl;
	// cout<<"Vector 3"<<V3.getColor()<<endl;
	

	//parsing now
	for (int i = min_x; i < max_x; i++){
		for (int j = min_y; j < max_y; j++){
			P.x=i; P.y=j; P.z=0;	//why P.z everytime?? U know.. life is full of surprises.. lol
			if(P.Inside(V1,V2,V3)){//absolute value just to avoid more maintenance..
				alpha=abs(((V3-V2)^(P-V2)).z/Trigo_Surface*0.5);
				beta=abs(((V1-V3)^(P-V3)).z/Trigo_Surface*0.5);
				gamma=abs(((V2-V1)^(P-V1)).z/Trigo_Surface*0.5);
				P.setColor(V1.getColor()*alpha+V2.getColor()*beta+V3.getColor()*gamma);
				// cout<<"The result"<<P.getColor()<<endl;
				FreeImage_SetPixelColor(betty,i,j, &P.Claire);
			}
			else;//I find it somehow sad not to do anything.. I decided to keep the else..
		}
	}
}

void Z_Buffering(Victor **&Buffer,Victor const &V1,Victor V2,Victor V3){

	Victor Surf= ((V3-V1)^(V2-V1));
	if(Surf.z<0){
		Swap(V2,V3);
		Surf=Victor(0,0,0)-Surf;//TODO : implement negativity in the template..
	}

	float Trigo_Surface=abs(Surf.z);//not much of a surface..

	//getting borders
	float min_x=Min(V1.x,V2.x,V3.x),max_x=Max(V1.x,V2.x,V3.x),min_y=Min(V1.y,V2.y,V3.y),max_y=Max(V1.y,V2.y,V3.y);
	Victor P;
	float alpha,beta,gamma;

	// cout<<"Vector 1"<<V1.getColor()<<endl;
	// cout<<"Vector 2"<<V2.getColor()<<endl;
	// cout<<"Vector 3"<<V3.getColor()<<endl;
	


	//parsing now
	for (int i = min_x; i < max_x; i++){
		for (int j = min_y; j < max_y; j++){
			P.x=i; P.y=j; P.z=0;	//why P.z everytime?? U know.. life is full of surprises.. lol
			if(P.Inside(V1,V2,V3)){
				//cout<<"trigo ("<<min_x<<","<<max_x<<")"<<"to ("<<min_y<<","<<max_y<<endl;
				alpha=abs(((P-V2)^(V3-V2)).z/Trigo_Surface);//
				beta=abs(((P-V3)^(V1-V3)).z/Trigo_Surface);
				gamma=abs(((P-V1)^(V2-V1)).z/Trigo_Surface);

				P.z=1/((alpha/V1.z)+beta/V2.z+gamma/V3.z);

				if(Buffer[i][j].z>=P.z){
					Buffer[i][j].z=P.z;// as simple as this..
					Buffer[i][j].setColor((V1.getColor()*alpha/V1.z+V2.getColor()*beta/V2.z+V3.getColor()*gamma/V3.z)*P.z);
				}
			}
			else;//I find it somehow sad not to do anything.. I decided to keep the else..
		}
	}
}



bool LegalPoint(int x,int y){
	return (x<WIDTH&&y<HEIGHT&&x>0&&y>0);
}

void LineBrezenham(FIBITMAP* betty,Victor V1, Victor V2){
	float m, b;
	int x = 0,y,temp;
	FreeImage_Initialise();
	FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP);
	RGBQUAD coolio;

	coolio.rgbBlue=255.0;
	coolio.rgbRed=255.0;
	coolio.rgbGreen=255.0;

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

		FreeImage_SetPixelColor(bitmap, x, y, &coolio);
	}
}

void MidpointLine(FIBITMAP* betty,RGBQUAD color, Victor V1, Victor V2){

// calculate dx & dy
    int dx = V2.x - V1.x;
    int dy = V2.y - V1.y;
    // initial value of decision parameter d
    int d = dy - (dx/2);
    int x = V1.x, y = V1.y;
    // Plot initial given point
    // putpixel(x,y) can be used to print pixel
    // of line in graphics
	if(LegalPoint(x,y))
		FreeImage_SetPixelColor(betty,x,y,&color);
    // iterate through value of X
    while (x < V2.x)
    {
        x++;
        // E or East is chosen
        if (d < 0)
            d = d + dy;
        // NE or North East is chosen
        else
        {
            d += (dy - dx);
            y++;
        }
        // Plot intermediate points
        // putpixel(x,y) is used to print pixel
        // of line in graphics
		if(LegalPoint(x,y))
			FreeImage_SetPixelColor(betty,x,y,&color);
    }

}

