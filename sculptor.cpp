#include "sculptor.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include "malloc.h"

/**
 * @brief quad é a função que calcula o quadrado de um valor
 * @param x é o valor inicial.
 * @return retorna o quadrado do valor inicial.
 */
float quad(int x){
    return (x*x);
}

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    nx = _nx, ny = _ny, nz = _nz;


     /*Voxel*** v = NULL;
     v = new Voxel**[nx];
     for(int i = 0;i<nx;i++){
         v[i] = new Voxel*[ny];
         for(int j = 0; j<ny ;j++){
             v[i][j] = new Voxel[nz];
         }
     } */



    v = new Voxel**[nx];
    for (int i = 0; i < nx; i++){
        v[i] = new Voxel*[ny];
        for (int j = 0; j < ny; j++){
            v[i][j] = new Voxel[nz];
        }
    }

    /*v = new Voxel**[nx];
    v[0] = new Voxel*[nx*ny];
    v[0][0] = new Voxel[nx*ny*nz];
    for(int i = 1; i < nx ; i++){
        v[i] = v[i-1]+ny;
        for(int j = 1; j < ny; j++){
            v[i][j] = v[i-1][j-1] + nz;
        }
    }*/

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                v[i][j][k].isOn = false;
            }
        }
    }
}

Sculptor::~Sculptor()
{
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            delete [] v[i][j];
        }
        delete [] v[i];
    }
    delete [] v;

    /*delete v[0][0];
    delete v[0];
    delete v; */

}

void Sculptor::setColor(float mr, float mg, float mb, float alpha)
{
    r = mr;
    g = mg;
    b = mb;
    a = alpha;
}

void Sculptor::putVoxel(int mx, int my, int mz)
{
    if(mx >= 0 && mx < nx && my >= 0 && my < ny && mz >= 0 && mz < nz){
        v[mx][my][mz].r = r;
        v[mx][my][mz].g = g;
        v[mx][my][mz].b = b;
        v[mx][my][mz].isOn = true;
        v[mx][my][mz].a = a;
    }
}

void Sculptor::cutVoxel(int x, int y, int z)
{
    v[x][y][z].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    if(x1 >= x0 && y1 >= y0 && z1 >= z0){
        for(int i = x0; i < x1; i++){
            for(int j = y0; j < y1; j++){
                for(int k = z0; k < z1; k++){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k < z1; k++){
                cutVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    for(int i = -radius; i < radius; i++){
        for(int j = -radius; j < radius; j++){
            for(int k = -radius; k < radius; k++){
                if((quad(xcenter - i) + quad(ycenter - j) + quad(zcenter - k)) < quad(radius)){
                    putVoxel(xcenter - i, ycenter - j, zcenter - k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    for(int i = -radius; i < radius; i++){
        for(int j = -radius; j < radius; j++){
            for(int k = -radius; k < radius; k++){
                if((quad(xcenter - i) + quad(ycenter - j) + quad(zcenter - k)) < quad(radius)){
                    cutVoxel(xcenter - i, ycenter - j, zcenter - k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(char* filename)
{
    int i, j, k, elements = 0, cont = 0, cont2 = 0;

    std::ofstream fout;

    fout.open("filename.off");

    if(!fout.is_open()){
        fout << "deu merda" << "\n";
        exit(1);
    }

    fout << "OFF" << "\n";

    for(i = 0; i < nx; i++){
        for(j = 0; j < ny; j++){
            for(k = 0; k < nz; k++){
                if(!v[i][j][k].isOn){
                    elements++;
                }
            }
        }
    }

    fout << elements*8 << " " << elements*6 << " " << 0 << " \n";

    for(i = 0; i < nx; i++){
        for(j = 0; j < ny; j++){
            for(k = 0; k < nz; k++){
                if(!v[i][j][k].isOn){

                    fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << " \n";
                    fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << " \n";
                    fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << " \n";
                    fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << " \n";
                    fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << " \n";
                    fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << " \n";
                    fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << " \n";
                    fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << " \n";
                }
            }
        }
    }

    for(i = 0; i < nx; i++){
        for(j = 0; j < ny; j++){
            for(k = 0; k < nz; k++){
                if(!v[i][j][k].isOn){

                    cont = cont2*8;
                    fout << 4 << " " << cont << " " << cont+3 << " " << cont+2 << " " << cont+1 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << 4 << " " << cont+4 << " " << cont+5 << " " << cont+6 << " " << cont+7 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << 4 << " " << cont << " " << cont+1 << " " << cont+5 << " " << cont+4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << 4 << " " << cont << " " << cont+4 << " " << cont+7 << " " << cont+3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << 4 << " " << cont+3 << " " << cont+7 << " " << cont+6 << " " << cont+2 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    fout << 4 << " " << cont+1 << " " << cont+2 << " " << cont+6 << " " << cont+5 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << "\n";
                    cont2++;
                }
            }
        }
    }
    fout.close();
}
