#include "sculptor.h"
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

Sculptor::Sculptor(int _x, int _y, int _z){
    nx =_x; ny =_y; nz =_z;

    if (nx <= 0 || ny <= 0 || nz <= 0){
        nx = ny = nz = 0;
    }

    v = new Voxel**[nz];

    v[0] = new Voxel*[nz*nx];

    for (int z=1; z<nz; z++){
        v[z] = v[z-1] + nx;
    }

    v[0][0] = new Voxel[nz*nx*ny];

    int counter = 0;
    for (int z=0; z<nz; z++){
        for(int x=0; x<nx; x++){
            v[z][x] = v[0][0] + counter*ny;
            counter++;
        }
    }
}

Sculptor::~Sculptor(){
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}

void Sculptor::setColor(float red, float green, float blue, float opacity){
   r = red;
   g = green;
   b = blue;
   a = opacity;
}

void Sculptor::putVoxel(int x, int y, int z){

    v[x][y][z].show = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].o = a;

}

void Sculptor::cutVoxel(int x, int y, int z){
v[z][y][x].show = true;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){

    for(int z=z0; z<=z1; z++){
        for(int y=y0; y<=y1; y++){
            for(int x=x0; x<=x1; x++){
                putVoxel(x,y,z);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){

    for(int z=z0; z<=z1; z++){
        for(int x=x0; x<=x1; x++){
            for(int y=y0; y<=y1; y++){

                cutVoxel(x,y,z);
            }
        }
    }

}

void Sculptor::putSphere(int xc, int yc, int zc, int r){

    double diameter;

    for(int z=0; z<=nz; z++){
        for(int y=0; y<=ny; y++){
            for(int x=0; x<=nz; x++){

                diameter = pow(x - xc, 2) + pow(y - yc, 2) + pow(z - zc, 2);
                if(diameter <= pow(r,2) ){

                    putVoxel(x, y, z);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xc, int yc, int zc, int r){

    double diameter;

    for(int z=0; z<=nz; z++){
        for(int y=0; y<=ny; y++){
            for(int x=0; x<=nx; x++){

                diameter = pow(x - xc, 2) + pow(y - yc, 2) + pow(z - zc, 2) ;
                if(diameter <= pow(r,2) ){

                    cutVoxel(x, y, z);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xc, int yc, int zc, int rx, int ry, int rz){

    double diameter;

    if(rx == 0){
        for(int z=0; z<=nz; z++){
            for(int y=0; y<=ny; y++){

                diameter = pow(y - yc, 2)/pow(ry, 2) + pow(z - zc, 2)/pow(rz, 2);

                if(diameter <=1){

                    putVoxel(xc, y, z);
                }

            }
         }

    }else if(ry == 0){

        for(int z=0; z<=nz; z++){
            for(int x=0; x<=nx; x++){

                diameter = pow(x - xc, 2)/pow(rx, 2) + pow(z - zc, 2)/pow(rz, 2);

                if(diameter <=1){

                    putVoxel(x, yc, z);
                }

            }
         }

    }else if(rz == 0){

        for(int x=0; x<=nx; x++){
            for(int y=0; x<=ny; y++){

                diameter = pow(x - xc, 2)/pow(rx, 2) + pow(y - yc, 2)/pow(ry, 2);

                if(diameter <=1){

                    putVoxel(x, y, zc);
                }

            }
         }

    }else{

        for(int z=0; z<=nz; z++){
            for(int y=0; y<=ny; y++){
                for(int x=0; x<=ny; x++){

                    diameter = pow(x - xc, 2)/pow(rx, 2) + pow(y - yc, 2)/pow(rz, 2) + pow(z - zc, 2)/pow(rz, 2);
                    if(diameter <= 1){

                        putVoxel(x, y, z);

                    }
                }
            }
        }
    }

}

void Sculptor::cutEllipsoid(int xc, int yc, int zc, int rx, int ry, int rz){

    double diameter;

    if(rx == 0){
        for(int z=0; z<=nz; z++){
            for(int y=0; y<=ny; y++){

                diameter = pow(y - yc, 2)/pow(ry, 2) + pow(z - zc, 2)/pow(rz, 2);

                if(diameter <=1){

                    cutVoxel(xc, y, z);
                }

            }
         }

    }else if(ry == 0){

        for(int z=0; z<=nz; z++){
            for(int x=0; x<=nx; x++){

                diameter = pow(x - xc, 2)/pow(rx, 2) + pow(z - zc, 2)/pow(rz, 2);

                if(diameter <=1){

                    cutVoxel(x, yc, z);
                }

            }
         }

    }else if(rz == 0){

        for(int x=0; x<=nx; x++){
            for(int y=0; x<=ny; y++){

                diameter = pow(x - xc, 2)/pow(rx, 2) + pow(y - yc, 2)/pow(ry, 2);

                if(diameter <=1){

                    cutVoxel(x, y, zc);
                }

            }
         }

    }else{

        for(int z=0; z<=nz; z++){
            for(int x=0; x<=nx; x++){
                for(int y=0; y<=ny; y++){

                    diameter = pow(x - xc, 2)/pow(rx, 2) + pow(y - yc, 2)/pow(rz, 2) + pow(z - zc, 2)/pow(rz, 2);
                    if(diameter <= 1){

                        cutVoxel(x, y, z);

                    }
                }
            }
        }
    }

}


void Sculptor::writeOFF(const char* filedoc){
    ofstream fout;

    fixed(fout);

    int numberOfVertices=0;
    int numberOfFaces=0;
    int aux=0;
    fout.open(filedoc);

    if(fout.is_open()){
        cout << "Saving file...\n";
    }
    else{
        cout << "File cannot be started...\n";
        exit(1);
    }

    fout<<"OFF"<<endl;

    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                if(v[i][j][k].show){
                    numberOfVertices=numberOfVertices+8;
                    numberOfFaces=numberOfFaces+6;
                }
            }
        }
    }

    fout<<numberOfVertices<<" "<<numberOfFaces<<" "<<0<<endl;


    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                if(v[i][j][k].show){


                        fout<<i-0.5<<" "<<j+0.5<<" "<<k-0.5<<endl;
                        fout<<i-0.5<<" "<<j-0.5<<" "<<k-0.5<<endl;
                        fout<<i+0.5<<" "<<j-0.5<<" "<<k-0.5<<endl;
                        fout<<i+0.5<<" "<<j+0.5<<" "<<k-0.5<<endl;
                        fout<<i-0.5<<" "<<j+0.5<<" "<<k+0.5<<endl;
                        fout<<i-0.5<<" "<<j-0.5<<" "<<k+0.5<<endl;
                        fout<<i+0.5<<" "<<j-0.5<<" "<<k+0.5<<endl;
                        fout<<i+0.5<<" "<<j+0.5<<" "<<k+0.5<<endl;

                }
            }
        }
    }

    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                if(v[i][j][k].show){
                    fout<<4<<" "<<aux+0<<" "<<aux+3<<" "<<aux+2<<" "<<aux+1<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].o<<endl;
                    fout<<4<<" "<<aux+4<<" "<<aux+5<<" "<<aux+6<<" "<<aux+7<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].o<<endl;
                    fout<<4<<" "<<aux+0<<" "<<aux+1<<" "<<aux+5<<" "<<aux+4<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].o<<endl;
                    fout<<4<<" "<<aux+0<<" "<<aux+4<<" "<<aux+7<<" "<<aux+3<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].o<<endl;
                    fout<<4<<" "<<aux+3<<" "<<aux+7<<" "<<aux+6<<" "<<aux+2<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].o<<endl;
                    fout<<4<<" "<<aux+1<<" "<<aux+2<<" "<<aux+6<<" "<<aux+5<<" "<<v[i][j][k].r<<" "
                    <<v[i][j][k].g<<" "<<v[i][j][k].b<<" "<<v[i][j][k].o<<endl;
                    aux=aux+8;
                }
            }
        }
    }

    if(fout.is_open()){
        cout << "File saved with successfully!"<<endl;
    }

}
