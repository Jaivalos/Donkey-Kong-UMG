
//Importa la libreria de allegro
#include <allegro.h>

//Definimos filas y columnas del mapa
#define MAXFILAS 23 //Para el eje y
#define MAXCOLS 31  //Para el eje x

//Declaramos variables del mapa
BITMAP *buffer;
BITMAP *floor;
BITMAP *escalera;

BITMAP *mariobmp;
BITMAP *mario;

BITMAP *monito;
BITMAP *peach;

//Direccion con la que se mueve el personaje
int dir = 4;
//Posicion del personaje
int px = 30*1, py=30*19;

//Creamos la matriz para el mapa
char mapa[MAXFILAS][MAXCOLS] = {
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	"X............................X",
	"X............   .............X",
	"X............XxX.............X",
	"X.............-..............X",
	"X.............-..............X",
	"X             -           ...X",
	"XXXXXXXXXXXXXXXXXXXXXXxXXX...X",
	"X.....................-......X",
	"X.....................-......X",
	"X.....                -      X",
	"X.....XxXXXXXXXXXXXXXXXXXXXXXX",
	"X......-.....................X",
	"X......-.....................X",
	"X......-.....................X",
	"X      -          ...........X",
	"XXXXXXXXXXXXXXXxXX...........X",
	"X..............-.............X",
	"X..............-.............X",
	"X              -             X",
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};

//Creamos la funcion para dibujar el mapa
void dibujar_mapa(){
	//Declaramos dos variables enteras para controlar la matriz del mapa
	int row, col;
	
	//Declaramos dos ciclos for para recorrer toda la matriz mapa
	for(row = 0; row < MAXFILAS; row ++){
		for(col = 0; col < MAXCOLS; col++){
			//Intercambiamos el valor de X por la imagen del piso
			if(mapa[row][col] == 'X'){
				draw_sprite(buffer, floor, col*30, row*30);
			}
		}
	}
	for(row = 0; row < MAXFILAS; row ++){
		for(col = 0; col < MAXCOLS; col++){
			//Intercambiamos el valor de X por la imagen del piso
			if(mapa[row][col] == 'x'){
				draw_sprite(buffer, floor, col*30, row*30);
			}
		}
	}
	//Realizamos lo mismo con el sprite de la escalera
	for(row = 0; row < MAXFILAS; row ++){
		for(col = 0; col < MAXCOLS; col++){
			if(mapa[row][col] == '-'){
				draw_sprite(buffer, escalera, col*30, row*30);
			}
		}
	}
	
}
//Creamos una funcion para cargar el buffer en nuetra pantlla
void pantalla(){
	blit(buffer, screen, 0, 0, 0, 0, 928, 640);
}
//Dibujamos a mario en nustro buffer y luego en la pantalla
void dibujar_personaje(){
	blit(mariobmp, mario, dir*33, 0, 0, 0, 33, 33);
	draw_sprite(buffer, mario, px, py);
} 
//Dibujamos al mono y a la princesa
void dibujar_monito_peach(){
	draw_sprite(buffer, monito, 33, 115);
	draw_sprite(buffer, peach, 390, 40);
} 

int main() {
	
	allegro_init();
	install_keyboard();
	
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 928, 640, 0, 0);
	
	buffer = create_bitmap(928, 640);
	
	floor = load_bitmap("floor.bmp", NULL);
	escalera = load_bitmap("Scale2.bmp", NULL); 
	 
	mariobmp = load_bitmap("mario.bmp",NULL);
	mario = create_bitmap(33,32);
	
	monito = load_bitmap("DK2.bmp",NULL);
	
	peach = load_bitmap("peach.bmp",NULL);
	
	while(!key[KEY_ESC]){
		
		//Rutina para mover a mario
		
		if(key[KEY_RIGHT]) dir = 0;
		else if(key[KEY_LEFT]) dir = 1;
		else if(key[KEY_UP]) dir = 2;
		else if(key[KEY_DOWN]) dir = 3;
		
		if(dir == 0){
			if((mapa[py/30][(px+30)/30] != 'X') && (mapa[py/30][(px+30)/30] != '.') ){
				px += 30;
//				dir = 4;
			}else dir = 4;
		}
		
		if(dir == 1){
			if((mapa[py/30][(px-30)/30] != 'X') && (mapa[py/30][(px-30)/30] != '.')){
				px -= 30;
//				dir = 4;
			}else dir = 4;
		}
		
		if(dir == 2){
			if((mapa[(py-30)/30][px/30] != 'X') && (mapa[(py-30)/30][px/30] != '.')){
				py -= 30;
//				dir = 4;
			}else dir = 4;
		}
		
		if(dir == 3){
			if((mapa[(py+30)/30][px/30] != 'X') && (mapa[(py+30)/30][px/30] != '.')){
				py += 30;
//				dir = 4;
			}else dir = 4;
		}
		
		clear(buffer);
		
		dibujar_mapa();
		dibujar_personaje();
		dibujar_monito_peach();
		pantalla();
		
		rest(200);
	}
	
}
END_OF_MAIN()


