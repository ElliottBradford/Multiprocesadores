/*
	Programa de conversión de imágenes usando el método de Schedule. 

	Elliott Bradford Lopez Montiel	A01327179
	Miguel Angel Fierro Gutiérrez	A01326928

	*NOTA: Para modificar la operación sobre las 10 imágenes, cambiar el nombre de la función deseada (img2gray, imginv, imgblur) en la función main.
*/

//Librerías y constantes
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 60

//Normalización de la imagen mediante la definición del pixel en sus 3 colores
struct my_pixel{
  unsigned char r, g, b;
};

//Declaración de funciones
void img2gray(char* name_in, char* name_out);
void imginv(char* name_in, char* name_out);
void imgblur(char* name_in, char* name_out, int kernel_size);

int main(){
	omp_set_num_threads(NUM_THREADS); //Declaración de número de threads

	//Variables para cálculo de tiempo
	double t1_1, t2_1, time_1;
	double t1_2, t2_2, time_2;
	double t1_3, t2_3, time_3;
	double t1_4, t2_4, time_4;
	double t1_5, t2_5, time_5;
	double t1_6, t2_6, time_6;
	double t1_7, t2_7, time_7;
	double t1_8, t2_8, time_8;
	double t1_9, t2_9, time_9;
	double t1_10, t2_10, time_10;

	//Llamadas a funciones para realizar la operación adecuada con las 10 imágenes con su respectiva sección
	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				t1_1 = omp_get_wtime();
				(void)imgblur("f1_g.bmp", "f1_blur.bmp", 21);
				t2_1 = omp_get_wtime();
			}

			#pragma omp section
			{
				t1_2 = omp_get_wtime();
				(void)imgblur("f2_g.bmp", "f2_blur.bmp", 21);
				t2_2 = omp_get_wtime();
			}

			#pragma omp section
			{
				t1_3 = omp_get_wtime();
				(void)imgblur("f3_g.bmp", "f3_blur.bmp", 21);
				t2_3 = omp_get_wtime();
			}

			#pragma omp section
			{
				t1_4 = omp_get_wtime();
				(void)imgblur("f4_g.bmp", "f4_blur.bmp", 21);
				t2_4 = omp_get_wtime();
			}

			#pragma omp section
			{
				t1_5 = omp_get_wtime();
				(void)imgblur("f5_g.bmp", "f5_blur.bmp", 21);
				t2_5 = omp_get_wtime();
			}

			#pragma omp section
			{
				t1_6 = omp_get_wtime();
				(void)imgblur("f6_g.bmp", "f6_blur.bmp", 21);
				t2_6 = omp_get_wtime();
			}

			#pragma omp section
			{
				t1_7 = omp_get_wtime();
				(void)imgblur("f7_g.bmp", "f7_blur.bmp", 21);
				t2_7 = omp_get_wtime();
			}

			#pragma omp section
			{
				t1_8 = omp_get_wtime();
				(void)imgblur("f8_g.bmp", "f8_blur.bmp", 21);
				t2_8 = omp_get_wtime();
			}

			#pragma omp section
			{
				t1_9 = omp_get_wtime();
				(void)imgblur("f9_g.bmp", "f9_blur.bmp", 21);
				t2_9 = omp_get_wtime();
			}

			#pragma omp section
			{
				t1_10 = omp_get_wtime();
				(void)imgblur("f10_g.bmp", "f10_blur.bmp", 21);
				t2_10 = omp_get_wtime();
			}
		}
	}

	//Cálculo e impresión de tiempo
	time_1 = t2_1 - t1_1;
	time_2 = t2_2 - t1_2;
	time_3 = t2_3 - t1_3;
	time_4 = t2_4 - t1_4;
	time_5 = t2_5 - t1_5;
	time_6 = t2_6 - t1_6;
	time_7 = t2_7 - t1_7;
	time_8 = t2_8 - t1_8;
	time_9 = t2_9 - t1_9;
	time_10 = t2_10 - t1_10;

	printf("Time 1: %f\n", time_1);
	printf("Time 2: %f\n", time_2);
	printf("Time 3: %f\n", time_3);
	printf("Time 4: %f\n", time_4);
	printf("Time 5: %f\n", time_5);
	printf("Time 6: %f\n", time_6);
	printf("Time 7: %f\n", time_7);
	printf("Time 8: %f\n", time_8);
	printf("Time 9: %f\n", time_9);
	printf("Time 10: %f\n", time_10);

	return 0;
}

//Conversión a escala de grises
void img2gray(char* name_in, char* name_out){
	FILE *image, *outputImage;
	image = fopen(name_in,"rb");
	outputImage = fopen(name_out,"wb");
	long ancho;
    long alto;
    long tamano;
    int pivot = 0;
    unsigned char xx[54];
    
    
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    
    //Dimensiones de la imagen
    ancho = (long)xx[21]*(long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    
    while(((ancho*3)+pivot)%4 != 0){
        pivot++;
    }
    
    //Secciones de memoria para la imagen de entrada y salida
    struct my_pixel* arr_in = (struct my_pixel*)malloc(alto*ancho*sizeof(struct my_pixel));
    struct my_pixel* arr_out = (struct my_pixel*)malloc(alto*ancho*sizeof(struct my_pixel));
	
	//Lectura y asignación de los pixeles de la imagen utilizando la directiva schedule(guided)
	#pragma omp parallel
	{
		#pragma omp for schedule(guided)
	    for(int i = 0; i < alto; i++){
	    	for(int j = 0; j< ancho; j++){
	    		arr_in[(i*ancho)+j].b = fgetc(image);
	    		arr_in[(i*ancho)+j].g = fgetc(image);
	    		arr_in[(i*ancho)+j].r = fgetc(image);
	    	}

	    	for(int k = 0; k < pivot; k++){
	    		fgetc(image);
	    	}
	    }
	}

	//Se realiza la operación de conversión a grises utilizando la directiva schedule(guided)
	#pragma omp parallel
	{
		#pragma omp for schedule(guided)
	    for(int i = 0; i < alto; i++){
	    	for(int j = 0; j < ancho; j++){
	    		unsigned char pixel = 0.21*arr_in[(i*ancho)+j].r+0.72*arr_in[(i*ancho)+j].g+0.07*arr_in[(i*ancho)+j].b;
	    		arr_out[(i*ancho)+j].b = pixel;
	    		arr_out[(i*ancho)+j].g = pixel;
	    		arr_out[(i*ancho)+j].r = pixel;
	    	}
	    }
	}

	//Se libera la memoria de entrada
	free(arr_in);
	
	//Escritura de la imagen resultante utilizando la directiva schedule(guided)
	#pragma omp parallel
	{
		#pragma omp for schedule(guided)
		for(int i = 0; i < alto; i++){
			for(int j = 0; j < ancho; j++){
				fputc(arr_out[(i*ancho)+j].b, outputImage);
				fputc(arr_out[(i*ancho)+j].g, outputImage);
				fputc(arr_out[(i*ancho)+j].r, outputImage);
			}
			for(int k = 0; k < pivot; k++){
	    		fputc(0, outputImage);
	    	}
		}
	}

	//Se libera la memoria de salida
	free(arr_out);

}

//Inversión de imagen
void imginv(char* name_in, char* name_out){
	FILE *image, *outputImage;
	image = fopen(name_in,"rb");
	outputImage = fopen(name_out,"wb");
	long ancho;
    long alto;
    long tamano;
    int pivot = 0;
    unsigned char xx[54];
    
    
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    
    //Dimensiones de la imagen
    ancho = (long)xx[21]*(long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    
    while(((ancho*3)+pivot)%4 != 0){
        pivot++;
    }
    
    //Secciones de memoria para la imagen de entrada y salida
	struct my_pixel* arr_in = (struct my_pixel*)malloc(alto*ancho*sizeof(struct my_pixel));
    struct my_pixel* arr_out = (struct my_pixel*)malloc(alto*ancho*sizeof(struct my_pixel));
	
	//Lectura y asignación de los pixeles de la imagen utilizando la directiva schedule(guided)
	#pragma omp parallel
	{
		#pragma omp for schedule(guided)
	    for(int i = 0; i < alto; i++){
	    	for(int j = 0; j< ancho; j++){
	    		arr_in[(i*ancho)+j].b = fgetc(image);
	    		arr_in[(i*ancho)+j].g = fgetc(image);
	    		arr_in[(i*ancho)+j].r = fgetc(image);
	    	}

	    	for(int k = 0; k < pivot; k++){
	    		fgetc(image);
	    	}
	    }
	}

	//Se realiza la operación de inversión utilizando la directiva schedule(guided)
	#pragma omp parallel
	{
		#pragma omp for schedule(guided)
	    for(int i = 0; i < alto; i++){
			for(int j = 0; j < ancho; j++){
				arr_out[(i*ancho)+j] = arr_in[(i*ancho)+ancho-1-j];
			}
		}
	}

	//Se libera la memoria de entrada
	free(arr_in);
	
	//Escritura de la imagen resultante utilizando la directiva schedule(guided)
	#pragma omp parallel
	{
		#pragma omp for schedule(guided)
		for(int i = 0; i < alto; i++){
			for(int j = 0; j < ancho; j++){
				fputc(arr_out[(i*ancho)+j].b, outputImage);
				fputc(arr_out[(i*ancho)+j].g, outputImage);
				fputc(arr_out[(i*ancho)+j].r, outputImage);
			}
			for(int k = 0; k < pivot; k++){
	    		fputc(0, outputImage);
	    	}
		}
	}
	//Se libera la memoria de salida
	free(arr_out);
	
}

//Desenfoque de imagen
void imgblur(char* name_in, char* name_out, int kernel_size){
	FILE *image, *outputImage;
	image = fopen(name_in,"rb");
	outputImage = fopen(name_out,"wb");
	long ancho;
    long alto;
    long tamano;
    int pivot = 0;
    unsigned char xx[54];
    
    //Pixel vacío
    struct my_pixel pixel_null;
	pixel_null.b = 0;
	pixel_null.g = 0;
	pixel_null.r = 0;
    
    for(int i=0; i<54; i++) {
      xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    }
    
    //Dimensiones de la imagen
    ancho = (long)xx[21]*(long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    
    while(((ancho*3)+pivot)%4 != 0){
        pivot++;
    }
    
    //Creación del kernel para la función
    double* kernel = (double*)malloc(kernel_size*kernel_size*sizeof(double));

    for(int i = 0; i < kernel_size; i++){
        for(int j = 0; j < kernel_size; j++){
            kernel[(i*kernel_size)+j] = 1.0/(double)(kernel_size*kernel_size);
        }
    }
    int m = kernel_size - 1;
    int n = m/2;
    
    //Secciones de memoria de entrada, salida, y matriz expandida para acomodar las operaciones del kernel
    struct my_pixel* arr_in = (struct my_pixel*)malloc(alto*ancho*sizeof(struct my_pixel));
    struct my_pixel* arr_out = (struct my_pixel*)malloc(alto*ancho*sizeof(struct my_pixel));
	struct my_pixel* arr_exp = (struct my_pixel*)malloc((alto+m)*(ancho+m)*sizeof(struct my_pixel));

	//Lectura y asignación de los pixeles de la imagen utilizando la directiva schedule(guided)
	#pragma omp parallel
	{
		#pragma omp for schedule(guided)
	    for(int i = 0; i < alto; i++){
	    	for(int j = 0; j< ancho; j++){
	    		arr_in[(i*ancho)+j].b = fgetc(image);
	    		arr_in[(i*ancho)+j].g = fgetc(image);
	    		arr_in[(i*ancho)+j].r = fgetc(image);
	    	}

	    	for(int k = 0; k < pivot; k++){
	    		fgetc(image);
	    	}
	    }
	}

	//Llenado de la matriz expandida con ceros (pixeles vacíos) utilizando la directiva schedule(guided)
	#pragma omp parallel
	{
		#pragma omp for schedule(guided)
	    for(int i = 0; i < alto+m; i++){
	    	for(int j = 0; j < ancho+m; j++){
	    		arr_exp[(i*(ancho+m))+j] = pixel_null;
	    	}
	    }
	}

	//Se centra la imagen de entrada en la matriz expandida utilizando la directiva schedule(guided)
	#pragma omp parallel
	{
		#pragma omp for schedule(guided)
	    for(int i = 0; i < alto; i++){
	    	for(int j = 0; j < ancho; j++){
	    		arr_exp[((i+n)*(ancho+m))+j+n] = arr_in[(i*ancho)+j];
	    	}
	    }
	}

	//Se libera la memoria de entrada
	free(arr_in);
	
	double s_b;
    double s_g;
    double s_r;

    //Se realiza la operación del kernel sobre la imagen para desenfocarla para compensar 
    //por el tamaño requerido
    #pragma omp parallel
    {
    	#pragma omp for schedule(guided)
	    for(int i = 0; i < alto; i++){
	    	for(int j = 0; j < ancho; j++){
	    		s_b = 0.0;
	    		s_g = 0.0;
	    		s_r = 0.0;

	    		for(int k = 0; k < kernel_size; k++){
	    			for(int l = 0; l < kernel_size; l++){
	    				s_b += (double)(arr_exp[((i+k)*(ancho+m))+j+l].b)*kernel[(k*kernel_size)+l];
	    				s_g += (double)(arr_exp[((i+k)*(ancho+m))+j+l].g)*kernel[(k*kernel_size)+l];
	    				s_r += (double)(arr_exp[((i+k)*(ancho+m))+j+l].r)*kernel[(k*kernel_size)+l];
	    			}
	    		}
	    		arr_out[(i*ancho)+j].b = (unsigned char)s_b;
	    		arr_out[(i*ancho)+j].g = (unsigned char)s_g;
	    		arr_out[(i*ancho)+j].r = (unsigned char)s_r;
	    	}
	    }
    }

    //Se libera la memoria de la matriz expandida y del kernel
	free(arr_exp);
	free(kernel);

	//Escritura de la imagen resultante utilizando la directiva schedule(guided)
	#pragma omp parallel
	{
		#pragma omp for schedule(guided)
		for(int i = 0; i < alto; i++){
			for(int j = 0; j < ancho; j++){
				fputc(arr_out[(i*ancho)+j].b, outputImage);
				fputc(arr_out[(i*ancho)+j].g, outputImage);
				fputc(arr_out[(i*ancho)+j].r, outputImage);
			}
			for(int k = 0; k < pivot; k++){
				fputc(0, outputImage);
			}
		}
	}

	//Se libera la memoria de salida
	free(arr_out);
	
}

