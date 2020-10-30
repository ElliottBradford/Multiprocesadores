/*
	Programa de conversión de imágenes usando el método de Sections. 

	Elliott Bradford Lopez Montiel	A01327179
	Miguel Angel Fierro Gutiérrez	A01326928

	*NOTA: Para modificar la operación sobre las 10 imágenes, cambiar el nombre de la función deseada (img2gray, imginv, imgblur) en la función main.
	**ADVERTENCIA: En éste método, no es posible ejecutar la función imgblur para las 10 imágenes simultáneamente por la cantidad de memoria que se requiere. 
*/

//Librerías y constantes
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define NUM_THREADS 20

//Normalización de la imagen mediante la definición del pixel en sus 3 colores
struct my_pixel{
  unsigned char r, g, b;
};

//Declaración de funciones
void img2gray(char* name_in, char* name_out);
void imginv(char* name_in, char* name_out);
void imgblur(char* name_in, char* name_out, int kernel_size);

//Función main
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
    
    //División de las dimensiones de la imagen en 4
    int h_alto_1 = (alto%2)==0?(alto/2):((alto-1)/2);
    int h_alto_2 = alto - h_alto_1;
    int h_ancho_1 = (ancho%2)==0?(ancho/2):((ancho-1)/2);
    int h_ancho_2 = ancho - h_ancho_1;
    
    //4 secciones de memoria para la entrada y 4 secciones de memoria para la salida
    struct my_pixel* my_sub_arr_1 = (struct my_pixel*)malloc(h_ancho_1*h_alto_1*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_2 = (struct my_pixel*)malloc(h_ancho_2*h_alto_1*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_3 = (struct my_pixel*)malloc(h_ancho_1*h_alto_2*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_4 = (struct my_pixel*)malloc(h_ancho_2*h_alto_2*sizeof(struct my_pixel));
    struct my_pixel* my_sub_out_arr_1 = (struct my_pixel*)malloc(h_ancho_1*h_alto_1*sizeof(struct my_pixel));
    struct my_pixel* my_sub_out_arr_2 = (struct my_pixel*)malloc(h_ancho_2*h_alto_1*sizeof(struct my_pixel));
    struct my_pixel* my_sub_out_arr_3 = (struct my_pixel*)malloc(h_ancho_1*h_alto_2*sizeof(struct my_pixel));
    struct my_pixel* my_sub_out_arr_4 = (struct my_pixel*)malloc(h_ancho_2*h_alto_2*sizeof(struct my_pixel));
    
	//Lectura y asignación de los pixeles de la imagen 
	for(int i = 0; i < alto; i++){
		for(int j = 0; j < ancho; j++){
			if(j < h_ancho_1 && i < h_alto_1){
				my_sub_arr_1[(i*h_ancho_1)+j].b = fgetc(image);
				my_sub_arr_1[(i*h_ancho_1)+j].g = fgetc(image);
				my_sub_arr_1[(i*h_ancho_1)+j].r = fgetc(image);
			}
			else if(i < h_alto_1 && j >= h_ancho_1){
				my_sub_arr_2[(i*h_ancho_2)+j-h_ancho_1].b = fgetc(image);
				my_sub_arr_2[(i*h_ancho_2)+j-h_ancho_1].g = fgetc(image);
				my_sub_arr_2[(i*h_ancho_2)+j-h_ancho_1].r = fgetc(image);
			}
			else if(i >= h_alto_1 && j < h_ancho_1){
				my_sub_arr_3[((i-h_alto_1)*h_ancho_1)+j].b = fgetc(image);
				my_sub_arr_3[((i-h_alto_1)*h_ancho_1)+j].g = fgetc(image);
				my_sub_arr_3[((i-h_alto_1)*h_ancho_1)+j].r = fgetc(image);
			}
			else{
				my_sub_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].b = fgetc(image);
				my_sub_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].g = fgetc(image);
				my_sub_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].r = fgetc(image);
			}
		}
		for(int k = 0; k < pivot; k++){
			fgetc(image);
		}
	}
	
	//Se realiza la operación de conversión a grises para las 4 secciones de la imagen
	#pragma omp parallel
	{
		#pragma omp sections
		{	
			#pragma omp section
			for(int i = 0; i < h_alto_1; i++){
				for(int j = 0; j < h_ancho_1; j++){
					unsigned char pixel = 0.21*my_sub_arr_1[(i*h_ancho_1)+j].r+0.72*my_sub_arr_1[(i*h_ancho_1)+j].g+0.07*my_sub_arr_1[(i*h_ancho_1)+j].b;
					my_sub_out_arr_1[(i*h_ancho_1)+j].b = pixel;
					my_sub_out_arr_1[(i*h_ancho_1)+j].g = pixel;
					my_sub_out_arr_1[(i*h_ancho_1)+j].r = pixel;
				}
			}
			
			#pragma omp section
			for(int i = 0; i < h_alto_1; i++){
				for(int j = 0; j < h_ancho_2; j++){
					unsigned char pixel = 0.21*my_sub_arr_2[(i*h_ancho_2)+j].r+0.72*my_sub_arr_2[(i*h_ancho_2)+j].g+0.07*my_sub_arr_2[(i*h_ancho_2)+j].b;
					my_sub_out_arr_2[(i*h_ancho_2)+j].b = pixel;
					my_sub_out_arr_2[(i*h_ancho_2)+j].g = pixel;
					my_sub_out_arr_2[(i*h_ancho_2)+j].r = pixel;
				}
			}
			
			#pragma omp section
			for(int i = 0; i < h_alto_1; i++){
				for(int j = 0; j < h_ancho_1; j++){
					unsigned char pixel = 0.21*my_sub_arr_3[(i*h_ancho_1)+j].r+0.72*my_sub_arr_3[(i*h_ancho_1)+j].g+0.07*my_sub_arr_3[(i*h_ancho_1)+j].b;
					my_sub_out_arr_3[(i*h_ancho_1)+j].b = pixel;
					my_sub_out_arr_3[(i*h_ancho_1)+j].g = pixel;
					my_sub_out_arr_3[(i*h_ancho_1)+j].r = pixel;
				}
			}
			
			#pragma omp section
			for(int i = 0; i < h_alto_1; i++){
				for(int j = 0; j < h_ancho_2; j++){
					unsigned char pixel = 0.21*my_sub_arr_4[(i*h_ancho_2)+j].r+0.72*my_sub_arr_4[(i*h_ancho_2)+j].g+0.07*my_sub_arr_4[(i*h_ancho_2)+j].b;
					my_sub_out_arr_4[(i*h_ancho_2)+j].b = pixel;
					my_sub_out_arr_4[(i*h_ancho_2)+j].g = pixel;
					my_sub_out_arr_4[(i*h_ancho_2)+j].r = pixel;
				}
			}
		}
	}

	//Se libera la memoria de entrada
	free(my_sub_arr_1);
	free(my_sub_arr_2);
	free(my_sub_arr_3);
	free(my_sub_arr_4);
	
	//Escritura de la imagen resultante en las 4 secciones de salida
	for(int i = 0; i < alto; i++){
		for(int j = 0; j < ancho; j++){
			if(j < h_ancho_1 && i < h_alto_1){
				fputc(my_sub_out_arr_1[(i*h_ancho_1)+j].b, outputImage);
				fputc(my_sub_out_arr_1[(i*h_ancho_1)+j].g, outputImage);
				fputc(my_sub_out_arr_1[(i*h_ancho_1)+j].r, outputImage);
			}
			else if(i < h_alto_1 && j >= h_ancho_1){
				fputc(my_sub_out_arr_2[(i*h_ancho_2)+j-h_ancho_1].b, outputImage);
				fputc(my_sub_out_arr_2[(i*h_ancho_2)+j-h_ancho_1].g, outputImage);
				fputc(my_sub_out_arr_2[(i*h_ancho_2)+j-h_ancho_1].r, outputImage);
			}
			else if(i >= h_alto_1 && j < h_ancho_1){
				fputc(my_sub_out_arr_3[((i-h_alto_1)*h_ancho_1)+j].b, outputImage);
				fputc(my_sub_out_arr_3[((i-h_alto_1)*h_ancho_1)+j].g, outputImage);
				fputc(my_sub_out_arr_3[((i-h_alto_1)*h_ancho_1)+j].r, outputImage);
			}
			else{
				fputc(my_sub_out_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].b, outputImage);	
				fputc(my_sub_out_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].g, outputImage);
				fputc(my_sub_out_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].r, outputImage);
			}
		}
		for(int k = 0; k < pivot; k++){
			fputc(0, outputImage);
		}
	}
	
	//Se libera la memoria de salida
	free(my_sub_out_arr_1);
	free(my_sub_out_arr_2);
	free(my_sub_out_arr_3);
	free(my_sub_out_arr_4);

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
    
    //División de las dimensiones de la imagen en 4
    int h_alto_1 = (alto%2)==0?(alto/2):((alto-1)/2);
    int h_alto_2 = alto - h_alto_1;
    int h_ancho_1 = (ancho%2)==0?(ancho/2):((ancho-1)/2);
    int h_ancho_2 = ancho - h_ancho_1;
    
    //4 secciones de memoria para la entrada y 4 secciones de memoria para la salida
    struct my_pixel* my_sub_arr_1 = (struct my_pixel*)malloc(h_ancho_1*h_alto_1*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_2 = (struct my_pixel*)malloc(h_ancho_2*h_alto_1*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_3 = (struct my_pixel*)malloc(h_ancho_1*h_alto_2*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_4 = (struct my_pixel*)malloc(h_ancho_2*h_alto_2*sizeof(struct my_pixel));
    struct my_pixel* my_sub_out_arr_1 = (struct my_pixel*)malloc(h_ancho_1*h_alto_1*sizeof(struct my_pixel));
    struct my_pixel* my_sub_out_arr_2 = (struct my_pixel*)malloc(h_ancho_2*h_alto_1*sizeof(struct my_pixel));
    struct my_pixel* my_sub_out_arr_3 = (struct my_pixel*)malloc(h_ancho_1*h_alto_2*sizeof(struct my_pixel));
    struct my_pixel* my_sub_out_arr_4 = (struct my_pixel*)malloc(h_ancho_2*h_alto_2*sizeof(struct my_pixel));
    
    //Lectura y asignación de los pixeles de la imagen 
    for(int i = 0; i < alto; i++){
		for(int j = 0; j < ancho; j++){
			if(j < h_ancho_1 && i < h_alto_1){
				my_sub_arr_1[(i*h_ancho_1)+j].b = fgetc(image);
				my_sub_arr_1[(i*h_ancho_1)+j].g = fgetc(image);
				my_sub_arr_1[(i*h_ancho_1)+j].r = fgetc(image);
			}
			else if(i < h_alto_1 && j >= h_ancho_1){
				my_sub_arr_2[(i*h_ancho_2)+j-h_ancho_1].b = fgetc(image);
				my_sub_arr_2[(i*h_ancho_2)+j-h_ancho_1].g = fgetc(image);
				my_sub_arr_2[(i*h_ancho_2)+j-h_ancho_1].r = fgetc(image);
			}
			else if(i >= h_alto_1 && j < h_ancho_1){
				my_sub_arr_3[((i-h_alto_1)*h_ancho_1)+j].b = fgetc(image);
				my_sub_arr_3[((i-h_alto_1)*h_ancho_1)+j].g = fgetc(image);
				my_sub_arr_3[((i-h_alto_1)*h_ancho_1)+j].r = fgetc(image);
			}
			else{
				my_sub_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].b = fgetc(image);
				my_sub_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].g = fgetc(image);
				my_sub_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].r = fgetc(image);
			}
		}
		for(int k = 0; k < pivot; k++){
			fgetc(image);
		}
	}
	
	//Se realiza la operación para la inversión de imagen para las 4 secciones de la imagen
	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
			for(int i = 0; i < h_alto_1; i++){
				for(int j = 0; j < h_ancho_1; j++){
					my_sub_out_arr_1[(i*h_ancho_1)+j] = my_sub_arr_1[(i*h_ancho_1)+h_ancho_1-1-j];
				}
			}
			#pragma omp section	
			for(int i = 0; i < h_alto_1; i++){
				for(int j = 0; j < h_ancho_2; j++){
					my_sub_out_arr_2[(i*h_ancho_2)+j] = my_sub_arr_2[(i*h_ancho_2)+h_ancho_2-1-j];
				}
			}
			#pragma omp section	
			for(int i = 0; i < h_alto_2; i++){
				for(int j = 0; j < h_ancho_1; j++){
					my_sub_out_arr_3[(i*h_ancho_1)+j] = my_sub_arr_3[(i*h_ancho_1)+h_ancho_1-1-j];
				}
			}
			#pragma omp section	
			for(int i = 0; i < h_alto_2; i++){
				for(int j = 0; j < h_ancho_2; j++){
					my_sub_out_arr_4[(i*h_ancho_2)+j] = my_sub_arr_4[(i*h_ancho_2)+h_ancho_2-1-j];
				}
			}
		}
	}

	//Se libera la memoria de entrada
	free(my_sub_arr_1);
	free(my_sub_arr_2);
	free(my_sub_arr_3);
	free(my_sub_arr_4);
	
	//Escritura de la imagen resultante en las 4 secciones de salida
	for(int i = 0; i < alto; i++){
		for(int j = 0; j < ancho; j++){
			if(j < h_ancho_2 && i < h_alto_1){
				fputc(my_sub_out_arr_2[(i*h_ancho_2)+j].b, outputImage);
				fputc(my_sub_out_arr_2[(i*h_ancho_2)+j].g, outputImage);
				fputc(my_sub_out_arr_2[(i*h_ancho_2)+j].r, outputImage);
			}
			else if(i < h_alto_1 && j >= h_ancho_2){
				fputc(my_sub_out_arr_1[(i*h_ancho_1)+j-h_ancho_2].b, outputImage);
				fputc(my_sub_out_arr_1[(i*h_ancho_1)+j-h_ancho_2].g, outputImage);
				fputc(my_sub_out_arr_1[(i*h_ancho_1)+j-h_ancho_2].r, outputImage);
			}
			else if(i >= h_alto_1 && j < h_ancho_2){
				fputc(my_sub_out_arr_4[((i-h_alto_1)*h_ancho_2)+j].b, outputImage);
				fputc(my_sub_out_arr_4[((i-h_alto_1)*h_ancho_2)+j].g, outputImage);
				fputc(my_sub_out_arr_4[((i-h_alto_1)*h_ancho_2)+j].r, outputImage);
			}
			else{
				fputc(my_sub_out_arr_3[((i-h_alto_1)*h_ancho_1)+j-h_ancho_2].b, outputImage);	
				fputc(my_sub_out_arr_3[((i-h_alto_1)*h_ancho_1)+j-h_ancho_2].g, outputImage);
				fputc(my_sub_out_arr_3[((i-h_alto_1)*h_ancho_1)+j-h_ancho_2].r, outputImage);
			}
		}
		for(int k = 0; k < pivot; k++){
			fputc(0, outputImage);
		}
	}
	
	//Se libera la memoria de salida
	free(my_sub_out_arr_1);
	free(my_sub_out_arr_2);
	free(my_sub_out_arr_3);
	free(my_sub_out_arr_4);
	
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
    
    //División de las dimensiones de la imagen en 4
    int h_alto_1 = (alto%2)==0?(alto/2):((alto-1)/2);
    int h_alto_2 = alto - h_alto_1;
    int h_ancho_1 = (ancho%2)==0?(ancho/2):((ancho-1)/2);
    int h_ancho_2 = ancho - h_ancho_1;
    
    //4 secciones de memoria para la entrada, 4 secciones de memoria para la salida, y 4 secciones para la matriz expandida para acomodar las operaciones del kernel
    struct my_pixel* my_sub_arr_1 = (struct my_pixel*)malloc(h_ancho_1*h_alto_1*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_2 = (struct my_pixel*)malloc(h_ancho_2*h_alto_1*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_3 = (struct my_pixel*)malloc(h_ancho_1*h_alto_2*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_4 = (struct my_pixel*)malloc(h_ancho_2*h_alto_2*sizeof(struct my_pixel));
    struct my_pixel* my_sub_out_arr_1 = (struct my_pixel*)malloc(h_ancho_1*h_alto_1*sizeof(struct my_pixel));
    struct my_pixel* my_sub_out_arr_2 = (struct my_pixel*)malloc(h_ancho_2*h_alto_1*sizeof(struct my_pixel));
    struct my_pixel* my_sub_out_arr_3 = (struct my_pixel*)malloc(h_ancho_1*h_alto_2*sizeof(struct my_pixel));
    struct my_pixel* my_sub_out_arr_4 = (struct my_pixel*)malloc(h_ancho_2*h_alto_2*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_exp_1 = (struct my_pixel*)malloc((h_ancho_1+m)*(h_alto_1+m)*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_exp_2 = (struct my_pixel*)malloc((h_ancho_2+m)*(h_alto_1+m)*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_exp_3 = (struct my_pixel*)malloc((h_ancho_1+m)*(h_alto_2+m)*sizeof(struct my_pixel));
    struct my_pixel* my_sub_arr_exp_4 = (struct my_pixel*)malloc((h_ancho_2+m)*(h_alto_2+m)*sizeof(struct my_pixel));

    //Lectura y asignación de los pixeles de la imagen 
    for(int i = 0; i < alto; i++){
		for(int j = 0; j < ancho; j++){
			if(j < h_ancho_1 && i < h_alto_1){
				my_sub_arr_1[(i*h_ancho_1)+j].b = fgetc(image);
				my_sub_arr_1[(i*h_ancho_1)+j].g = fgetc(image);
				my_sub_arr_1[(i*h_ancho_1)+j].r = fgetc(image);
			}
			else if(i < h_alto_1 && j >= h_ancho_1){
				my_sub_arr_2[(i*h_ancho_2)+j-h_ancho_1].b = fgetc(image);
				my_sub_arr_2[(i*h_ancho_2)+j-h_ancho_1].g = fgetc(image);
				my_sub_arr_2[(i*h_ancho_2)+j-h_ancho_1].r = fgetc(image);
			}
			else if(i >= h_alto_1 && j < h_ancho_1){
				my_sub_arr_3[((i-h_alto_1)*h_ancho_1)+j].b = fgetc(image);
				my_sub_arr_3[((i-h_alto_1)*h_ancho_1)+j].g = fgetc(image);
				my_sub_arr_3[((i-h_alto_1)*h_ancho_1)+j].r = fgetc(image);
			}
			else{
				my_sub_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].b = fgetc(image);
				my_sub_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].g = fgetc(image);
				my_sub_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].r = fgetc(image);
			}
		}
		for(int k = 0; k < pivot; k++){
			fgetc(image);
		}
	}
	
	//Llenado de la matriz expandida con ceros (pixeles vacíos)
	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
			for(int i = 0; i < h_alto_1+m; i++){
				for(int j = 0; j < h_ancho_1+m; j++){
					my_sub_arr_exp_1[(i*(h_ancho_1+m))+j] = pixel_null;
				}
			}
			
			#pragma omp section
			for(int i = 0; i < h_alto_1+m; i++){
				for(int j = 0; j < h_ancho_2+m; j++){
					my_sub_arr_exp_2[(i*(h_ancho_2+m))+j] = pixel_null;
				}
			}
			
			#pragma omp section
			for(int i = 0; i < h_alto_2+m; i++){
				for(int j = 0; j < h_ancho_1+m; j++){
					my_sub_arr_exp_3[(i*(h_ancho_1+m))+j] = pixel_null;
				}
			}
			
			#pragma omp section
			for(int i = 0; i < h_alto_2+m; i++){
				for(int j = 0; j < h_ancho_2+m; j++){
					my_sub_arr_exp_4[(i*(h_ancho_2+m))+j] = pixel_null;
				}
			}
			
			//Las siguientes 12 secciones copian los pixeles en los bordes de las secciones colindantes a la actual
			//para evitar que la imagen resultante esté dividida por una cruz 
			#pragma omp section
			for(int i = 0; i < h_alto_1; i++){
				for(int j = 0; j < h_ancho_1; j++){
					my_sub_arr_exp_1[((i+n)*(h_ancho_1+m))+j+n] = my_sub_arr_1[(i*h_ancho_1)+j];
				}
			}
			
			#pragma omp section
			for(int i = n; i < h_alto_1+m; i++){
				for(int j = h_ancho_1+n; j < h_ancho_1+m; j++){
					my_sub_arr_exp_1[(i*(h_ancho_1+m))+j] = my_sub_arr_2[((i-n)*h_ancho_2)+j-(h_ancho_1+n)];
				}
			}
			
			#pragma omp section
			for(int i = h_alto_1+n; i <h_alto_1+m; i++){
				for(int j = n; j < h_ancho_1+m; j++){
					my_sub_arr_exp_1[(i*(h_ancho_1+m))+j] = my_sub_arr_3[((i-h_alto_1-n)*h_ancho_1)+j-n];
				}
			}
			
			#pragma omp section
			for(int i = 0; i < h_alto_1; i++){
				for(int j = 0; j < h_ancho_2; j++){
					my_sub_arr_exp_2[((i+n)*(h_ancho_2+m))+j+n] = my_sub_arr_2[(i*h_ancho_2)+j];
				}
			}
			
			#pragma omp section
			for(int i = n; i < h_alto_1+m; i++){
				for(int j = 0; j < n; j++){
					my_sub_arr_exp_2[(i*(h_ancho_2+m))+j] = my_sub_arr_1[((i-n)*h_ancho_1)+j+h_ancho_2-n];
				}
			}
			
			#pragma omp section
			for(int i = h_alto_1+n; i < h_alto_1+m; i++){
				for(int j = 0; j < h_ancho_2+n; j++){
					my_sub_arr_exp_2[(i*(h_ancho_2+m))+j] = my_sub_arr_4[((i-h_alto_1-n)*h_ancho_2)+j];
				}
			}
			
			#pragma omp section
			for(int i = 0; i < h_alto_2; i++){
				for(int j = 0; j < h_ancho_1; j++){
					my_sub_arr_exp_3[((i+n)*(h_ancho_1+m))+j+n] = my_sub_arr_3[(i*h_ancho_1)+j];
				}
			}
			
			#pragma omp section
			for(int i = 0; i < n; i++){
				for(int j = n; j < h_ancho_1+m; j++){
					my_sub_arr_exp_3[(i*(h_ancho_1+m))+j] = my_sub_arr_1[((i+h_alto_1-n)*h_ancho_1)+j-n];
				}
			}
			
			#pragma omp section
			for(int i = n; i < h_alto_2+m; i++){
				for(int j = h_ancho_1+n; j < h_ancho_1+m; j++){
					my_sub_arr_exp_3[(i*(h_ancho_1+m))+j] = my_sub_arr_4[((i-n)*h_ancho_1)+j-n-h_ancho_1];
				}
			}

			#pragma omp section
			for(int i = 0; i < h_alto_2; i++){
				for(int j = 0; j < h_ancho_2; j++){
					my_sub_arr_exp_4[((i+n)*(h_ancho_2+m))+j+n] = my_sub_arr_4[(i*h_ancho_2)+j];
				}
			}
			
			#pragma omp section
			for(int i = n; i < h_alto_2+m; i++){
				for(int j = 0; j < n; j++){
					my_sub_arr_exp_4[(i*(h_ancho_2+m))+j] = my_sub_arr_3[((i-n)*h_ancho_1)+j+h_ancho_1-n];
				}
			}
			
			#pragma omp section
			for(int i = 0; i < n; i++){
				for(int j = n; j < h_ancho_2+n; j++){
					my_sub_arr_exp_4[(i*(h_ancho_2+m))+j] = my_sub_arr_2[((i+h_alto_1-n)*h_ancho_2)+j-n];
				}
			}
		}
	}
	//Se libera la memoria de entrada
	free(my_sub_arr_1);
	free(my_sub_arr_2);
	free(my_sub_arr_3);
	free(my_sub_arr_4);
	
	double s_b;
    double s_g;
    double s_r;
    
    //Se realiza la operación del kernel sobre las 4 secciones de la imagen para desenfocarla y se asigna a la matriz expandida
    //para compensar por el tamaño requerido
    #pragma omp parallel
    {
    	#pragma omp sections
    	{
    		#pragma omp section
		    for(int i = 0; i < h_alto_1; i++){
		        for(int j = 0; j < h_ancho_1; j++){
		            s_b = 0.0;
		            s_g = 0.0;
		            s_r = 0.0;
		            for(int k = 0; k < kernel_size; k++){
		                for(int l = 0; l < kernel_size; l++){
		                    s_b += (double)(my_sub_arr_exp_1[((i+k)*(h_ancho_1+m))+j+l].b)*kernel[(k*kernel_size)+l];
		                    s_g += (double)(my_sub_arr_exp_1[((i+k)*(h_ancho_1+m))+j+l].g)*kernel[(k*kernel_size)+l];
		                    s_r += (double)(my_sub_arr_exp_1[((i+k)*(h_ancho_1+m))+j+l].r)*kernel[(k*kernel_size)+l];
		                }
		            }
		            my_sub_out_arr_1[(i*h_ancho_1)+j].b = (unsigned char)s_b;
		            my_sub_out_arr_1[(i*h_ancho_1)+j].g = (unsigned char)s_g;
		            my_sub_out_arr_1[(i*h_ancho_1)+j].r = (unsigned char)s_r;
		        }
		    }
		    
		    #pragma omp section
		    for(int i = 0; i < h_alto_1; i++){
		        for(int j = 0; j < h_ancho_2; j++){
		            s_b = 0.0;
		            s_g = 0.0;
		            s_r = 0.0;
		            for(int k = 0; k < kernel_size; k++){
		                for(int l = 0; l < kernel_size; l++){
		                    s_b += (double)(my_sub_arr_exp_2[((i+k)*(h_ancho_2+m))+j+l].b)*kernel[(k*kernel_size)+l];
		                    s_g += (double)(my_sub_arr_exp_2[((i+k)*(h_ancho_2+m))+j+l].g)*kernel[(k*kernel_size)+l];
		                    s_r += (double)(my_sub_arr_exp_2[((i+k)*(h_ancho_2+m))+j+l].r)*kernel[(k*kernel_size)+l];
		                }
		            }
		            my_sub_out_arr_2[(i*h_ancho_2)+j].b = (unsigned char)s_b;
		            my_sub_out_arr_2[(i*h_ancho_2)+j].g = (unsigned char)s_g;
		            my_sub_out_arr_2[(i*h_ancho_2)+j].r = (unsigned char)s_r;
		        }
		    }
		    
		    #pragma omp section
		    for(int i = 0; i < h_alto_2; i++){
		        for(int j = 0; j < h_ancho_1; j++){
		            s_b = 0.0;
		            s_g = 0.0;
		            s_r = 0.0;
		            for(int k = 0; k < kernel_size; k++){
		                for(int l = 0; l < kernel_size; l++){
		                    s_b += (double)(my_sub_arr_exp_3[((i+k)*(h_ancho_1+m))+j+l].b)*kernel[(k*kernel_size)+l];
		                    s_g += (double)(my_sub_arr_exp_3[((i+k)*(h_ancho_1+m))+j+l].g)*kernel[(k*kernel_size)+l];
		                    s_r += (double)(my_sub_arr_exp_3[((i+k)*(h_ancho_1+m))+j+l].r)*kernel[(k*kernel_size)+l];
		                }
		            }
		            my_sub_out_arr_3[(i*h_ancho_1)+j].b = (unsigned char)s_b;
		            my_sub_out_arr_3[(i*h_ancho_1)+j].g = (unsigned char)s_g;
		            my_sub_out_arr_3[(i*h_ancho_1)+j].r = (unsigned char)s_r;
		        }
		    }
		    
		    #pragma omp section
		    for(int i = 0; i < h_alto_2; i++){
		        for(int j = 0; j < h_ancho_2; j++){
		            s_b = 0.0;
		            s_g = 0.0;
		            s_r = 0.0;
		            for(int k = 0; k < kernel_size; k++){
		                for(int l = 0; l < kernel_size; l++){
		                    s_b += (double)(my_sub_arr_exp_4[((i+k)*(h_ancho_2+m))+j+l].b)*kernel[(k*kernel_size)+l];
		                    s_g += (double)(my_sub_arr_exp_4[((i+k)*(h_ancho_2+m))+j+l].g)*kernel[(k*kernel_size)+l];
		                    s_r += (double)(my_sub_arr_exp_4[((i+k)*(h_ancho_2+m))+j+l].r)*kernel[(k*kernel_size)+l];
		                }
		            }
		            my_sub_out_arr_4[(i*h_ancho_2)+j].b = (unsigned char)s_b;
		            my_sub_out_arr_4[(i*h_ancho_2)+j].g = (unsigned char)s_g;
		            my_sub_out_arr_4[(i*h_ancho_2)+j].r = (unsigned char)s_r;
		        }
		    }
		}
    }

    //Se libera la memoria de la matriz expandida y del kernel
    free(my_sub_arr_exp_1);
	free(my_sub_arr_exp_2);
	free(my_sub_arr_exp_3);
	free(my_sub_arr_exp_4);
	free(kernel);
	
	//Escritura de la imagen resultante en las 4 secciones de salida
	for(int i = 0; i < alto; i++){
		for(int j = 0; j < ancho; j++){
			if(j < h_ancho_1 && i < h_alto_1){
				fputc(my_sub_out_arr_1[(i*h_ancho_1)+j].b, outputImage);
				fputc(my_sub_out_arr_1[(i*h_ancho_1)+j].g, outputImage);
				fputc(my_sub_out_arr_1[(i*h_ancho_1)+j].r, outputImage);
			}
			else if(i < h_alto_1 && j >= h_ancho_1){
				fputc(my_sub_out_arr_2[(i*h_ancho_2)+j-h_ancho_1].b, outputImage);
				fputc(my_sub_out_arr_2[(i*h_ancho_2)+j-h_ancho_1].g, outputImage);
				fputc(my_sub_out_arr_2[(i*h_ancho_2)+j-h_ancho_1].r, outputImage);
			}
			else if(i >= h_alto_1 && j < h_ancho_1){
				fputc(my_sub_out_arr_3[((i-h_alto_1)*h_ancho_1)+j].b, outputImage);
				fputc(my_sub_out_arr_3[((i-h_alto_1)*h_ancho_1)+j].g, outputImage);
				fputc(my_sub_out_arr_3[((i-h_alto_1)*h_ancho_1)+j].r, outputImage);
			}
			else{
				fputc(my_sub_out_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].b, outputImage);	
				fputc(my_sub_out_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].g, outputImage);
				fputc(my_sub_out_arr_4[((i-h_alto_1)*h_ancho_2)+j-h_ancho_1].r, outputImage);
			}
		}
		for(int k = 0; k < pivot; k++){
			fputc(0, outputImage);
		}
	}
	
	//Se libera la memoria de salida
	free(my_sub_out_arr_1);
	free(my_sub_out_arr_2);
	free(my_sub_out_arr_3);
	free(my_sub_out_arr_4);
	
}

