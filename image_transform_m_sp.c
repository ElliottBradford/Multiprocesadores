#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main(){
    FILE *image, *outputImage, *lecturas;
    image = fopen("sample.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("img3_dd.bmp","wb");    //Imagen transformada
    long ancho;
    long alto;
    unsigned char r, g, b;               //Pixel
    double t1, t2, time;
    int pivot = 0;
    unsigned char xx[54];
    
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    
    ancho = (long)xx[21]*(long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    
    while(((ancho*3)+pivot)%4 != 0){
        pivot++;
    }
    
    unsigned char* arr_in = (unsigned char*)malloc(((ancho*3)+pivot)*alto*sizeof(unsigned char));
    unsigned char* arr_out = (unsigned char*)malloc(((ancho*3)+pivot)*alto*sizeof(unsigned char));
    
    for(int i = 0; i < ((ancho*3)+pivot)*alto; i++){
        *(arr_in + i) = fgetc(image);
        *(arr_out + i) = *(arr_in + i);
    }

    int count = 0;
    t1 = omp_get_wtime();

        for(int i = 0; i < ((ancho*3)+pivot)*alto; i+=3){
                b = *(arr_in + i);
                g = *(arr_in + i + 1);
                r = *(arr_in + i + 2);
                unsigned char pixel = 0.21*r+0.72*g+0.07*b;
                *(arr_out + i) = pixel;
                *(arr_out + i + 1) = pixel;
                *(arr_out + i + 2) = pixel;
                

                count += 3;
                if(count == ancho*3){
                    i+=pivot;
                    count = 0;
                
            }
        }

    t2 = omp_get_wtime();
    time = t2 - t1;
    printf("Time = %f\n",time);
    
    for(int i = 0; i < ((ancho*3)+pivot)*alto; i++){
        fputc(*(arr_out + i), outputImage);}
    
    fclose(image);
    fclose(outputImage);
    
    return 0;
}
