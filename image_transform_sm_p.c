//Import libraries
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 6

int main(){
	omp_set_num_threads(NUM_THREADS);
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

    int count = 0;
    t1 = omp_get_wtime();
    #pragma omp parallel
    {
		#pragma omp for
		for(int i = 0; i < ((ancho*3)+pivot)*alto; i+=3){
				b = fgetc(image);
				g = fgetc(image);
				r = fgetc(image);
				unsigned char pixel = 0.21*r+0.72*g+0.07*b;
				fputc(pixel, outputImage);
				fputc(pixel, outputImage);
				fputc(pixel, outputImage);
				
				count += 3;
				if(count == ancho*3){
					for(int j = 0; j < pivot; j++){
						fputc(fgetc(image), outputImage);
					}
					i+=pivot;
					count = 0;
				}
		}
    }
    t2 = omp_get_wtime();
    time = t2 - t1;
	printf("Time = %f\n",time);
    
    fclose(image);
    fclose(outputImage);
    
	return 0;
}
