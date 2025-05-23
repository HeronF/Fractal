#include <iostream>
#include <fstream>
#include <complex>
#include<math.h>

using namespace std;


//classe cores
typedef struct coress{
int cor1,cor2,cor3; 
}cores;


//Tamanho do Arquivo
float width = 2000;     //Valor padrão 1000
float height = 4000;    // Valor padrão 1000

//Protótipos
int value_mandelbrot_out(int i, int j, int foco, float amplia);
void mandenbrolt_out_creation(int foco, float amplia);
//protótipos 

//Chamada Main

int main () 
{ 
 mandenbrolt_out_creation(70, 0.5);    // Valor padrão (50,2)
 return 0;
}

int value_mandelbrot_out(int x, int y, int foco, float amplia)
{
    cores corval;
    corval.cor1=corval.cor2=corval.cor3=0;
    complex<double> cpoint((double)x/(amplia*width)-2, (double)y/(amplia*height)-1);
    complex<double> z(0, 0);
    int nb_iter = 0;
    while (abs (z) < 2 && nb_iter <= foco) 
    {
        z = z * z + cpoint;
        nb_iter++;
    }
    if (nb_iter < foco) return 3*(255*nb_iter)/foco;
    /* {
      if(nb_iter<=foco/3)
      {
        corval.cor1=3*nb_iter;
        corval.cor2=0;
        corval.cor3=0;
      }
      else if((nb_iter>foco/3)&&(nb_iter<=2*foco/3))
      {
        corval.cor1=255;
        corval.cor2=round(((3-foco/nb_iter)*nb_iter/foco)*255);
        corval.cor3=0;
      }
      else if(nb_iter>2*foco/3)
      {
        corval.cor1=255;
        corval.cor2=255;
        corval.cor3=round(((3-2*foco/nb_iter)*nb_iter/foco)*255);
      }
      return corval;
      }*/
    else 
       return 0;
}

void mandenbrolt_out_creation(int foco, float amplia)
  {
    ofstream my_Image ("mandelbrot4.ppm"); 
    if (my_Image.is_open ()) {
        my_Image << "P3\n" << width << " " << height << " 255\n";
        for (int i = 0; i < width; i++) {
             for (int j = 0; j < height; j++)  {    
               int val = value_mandelbrot_out(i, j, foco, amplia); 
               if(val<=255)
               {
               my_Image << val << ' ' << 0 << ' ' << 0 << endl;
               }
               else if(val>255&&val<=610)
               {
               my_Image << 255 << ' ' << val-255 << ' ' << 0 << endl;
               }
               else
               {
                 my_Image << 255 << ' ' << 255 << ' ' << val-610 << endl;
               }
               
             }
        }
        my_Image.close();
    }
    else cout << "Could not open the file";
    return;
}
