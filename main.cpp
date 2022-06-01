
//Importa la libreria de allegro
#include <allegro.h>
#include <cstdlib>

//Definimos filas y columnas del mapa
#define MAXFILAS 23 //Para el eje y
#define MAXCOLS 31  //Para el eje x

//Declaramos variables del mapa
BITMAP *buffer;
BITMAP *floor;
BITMAP *escalera;

BITMAP *mariobmp;
BITMAP *mario;

BITMAP *yoshibmp;
BITMAP *yoshi;

//en la segunda fase insertamos los objetos con los que interactua el personaje
BITMAP *barril_parado;
BITMAP *barrilbmp;  //creamos un buffer al igual que con el personaje principal
BITMAP *barril;
BITMAP *coin;
BITMAP *llave;

BITMAP *monito;
BITMAP *peach;

//Direccion con la que se mueve el personaje
int dir = 4;
int dir2 = 4;
//Posicion del personaje
int px = 30*1, py=30*19;
int ypx = 30*1, ypy=30*19;

//direcci?n de movimiento y posici?n del barril
int fdir = 1;
int _x=30*5, _y=30*6;


//Creamos la matriz para el mapa
char mapa[MAXFILAS][MAXCOLS] = {
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	"X............................X",
	"X............   .............X",
	"X............XxX.............X",
	"X.............-..............X",
	"X.............-..............X",
	"X             -  k   o    .|.X",
	"XXXXXXXXXXXXXXXXXXXXXXxXXX...X",
	"X.....................-......X",
	"X.....................-......X",
	"X|....      o         -      X",
	"X..XXXXxXXXXXXXXXXXXXXXXXXXXXX",
	"X......-.....................X",
	"X......-.....................X",
	"X......-.....................X",
	"X  o   -          ..|........X",
	"XXXXXXXXXXXXXXXxXX...........X",
	"X..............-.............X",
	"X..............-.............X",
	"X      o       -             X",
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
			
			//en la fase 2 realizamos el mismo procedimiento para dibujar las monedas en el mapa
			else if(mapa[row][col] == 'o'){
				draw_sprite(buffer, coin, col*30, row*30);
				
				//aca evaluamos si la posicion de mario es igual a la de la moneda
				if(py/30 == row && px/30 == col){
					//de ser as? se inserta un espacio en blanco borrando la moneda
						mapa[row][col] = ' ';
				}
			}
			
			else if(mapa[row][col] == 'k'){
				draw_sprite(buffer,llave, col*30, row*30);
			
				if(py/30 == row && px/30 == col){
						mapa[row][col] = ' ';
				}
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
void dibujar_personaje2(){
	blit(yoshibmp, yoshi, dir*33, 0, 0, 0, 33, 33);
	draw_sprite(buffer, yoshi, px, py);
} 
//Dibujamos al mono y a la princesa
void dibujar_monito_peach(){
	draw_sprite(buffer, monito, 33, 115);
	draw_sprite(buffer, peach, 390, 40);
} 

//Dibujamos el barril en la mano del mono
void dibujar_barril_parado(){
	draw_sprite(buffer, barril_parado, 130, 70);
} 

//Dibujamos el barril que rodar? creando el peque?o buffer 
void dibujar_barril(){
	blit(barrilbmp,barril,0,0,0,0,30,30);
	//draw_sprite(buffer, barril, 160, 180);
	draw_sprite(buffer,barril,_x,_y);
} 

//cuando el barril toca a mario termina el juego 
void choque_barril(){
	if(py==_y && px==_x){
		clear(mario);
		clear(buffer);
		exit (0);
		}
}

void moverbarril(){
	dibujar_barril();
	
	if( mapa[ _y/30 ][ ( _x-30 )/30 ] == '|' ){
		fdir = 2;
	}
	
	if( fdir == 0 ){
		if( mapa[ _y/30 ][ ( _x-30 )/30 ] != 'X' ) {
			_x -= 30;
		}else {
			fdir = rand()%3;
		}
	}
	
	if( fdir == 1 ){
		if( mapa[ _y/30 ][ ( _x+30 )/30  ] != 'X' ) {
			_x += 30;
		}else {
			fdir = rand()%3;
		}
	}
	
	if( fdir == 2 ){
		if( mapa[ ( _y+30 )/30 ][ _x/30 ] != 'X' ) {
			_y += 30;
		}else {
			fdir = rand()%3;
		}
	}

	
}



void pintar(){
	clear(buffer);
	dibujar_mapa();
	dibujar_personaje();
	dibujar_monito_peach();
	dibujar_barril_parado();
	dibujar_barril();
	llave;
	moverbarril();
	coin;
	pantalla();
	choque_barril();
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
	
	
	//fase 2:creamos y cargamos el bitmat de los objetos
	barril_parado = load_bitmap("barril_parado.bmp",NULL);
	barril = create_bitmap(30,30);
	barrilbmp = load_bitmap("barril.bmp",NULL);
	coin = load_bitmap("coin.bmp",NULL);
	llave = load_bitmap("llave.bmp",NULL);
	
	
//	dibujar_personaje();
	
	while(!key[KEY_ESC]){
		
		//Rutina para mover a mario
		
//		dibujar_personaje();
		
		if(key[KEY_RIGHT]) dir = 0;
		else if(key[KEY_LEFT]) dir = 1;
		else if(key[KEY_UP]) dir = 2;
		else if(key[KEY_DOWN]) dir = 3;
		
		if(dir == 0){
			if((mapa[py/30][(px+30)/30] != 'X') && (mapa[py/30][(px+30)/30] != '.') ){
				px += 30;
				dibujar_personaje();
				dir = 4;
//				dibujar_personaje();
			}else dir = 4;
		}
		
		if(dir == 1){
			if((mapa[py/30][(px-30)/30] != 'X') && (mapa[py/30][(px-30)/30] != '.')){
				px -= 30;
				dibujar_personaje();
				dir = 4;
//				dibujar_personaje();
			}else dir = 4;
		}
		
		if(dir == 2){
			if((mapa[(py-30)/30][px/30] != 'X') && (mapa[(py-30)/30][px/30] != '.')){
				py -= 30;
				dibujar_personaje();
				dir = 4;
//				dibujar_personaje();
			}else{
				py -= 30;
				pintar();
				rest(155);
				
				py -= 30;
				pintar();
				rest(155);
				
				py += 30;
				pintar();
				rest(155);
				
				py += 30;
				pintar();
				
				dir = 4;
			};
		}
		
		if(dir == 3){
			if((mapa[(py+30)/30][px/30] != 'X') && (mapa[(py+30)/30][px/30] != '.')){
				py += 30;
				dibujar_personaje();
				dir = 4;
//				dibujar_personaje();
			}else dir = 4;
		}
		
		
		if(key[KEY_D]) dir2 = 0;
		else if(key[A]) dir2 = 1;
		else if(key[W]) dir2 = 2;
		else if(key[S]) dir2 = 3;
		
		if(dir2 == 0){
			if((mapa[ypy/30][(ypx+30)/30] != 'X') && (mapa[ypy/30][(ypx+30)/30] != '.') ){
				ypx += 30;
				dibujar_personaje();
				dir2 = 4;
//				dibujar_personaje();
			}else dir2 = 4;
		}
		
		if(dir == 1){
			if((mapa[py/30][(px-30)/30] != 'X') && (mapa[py/30][(px-30)/30] != '.')){
				px -= 30;
				dibujar_personaje();
				dir = 4;
//				dibujar_personaje();
			}else dir = 4;
		}
		
		if(dir == 2){
			if((mapa[(py-30)/30][px/30] != 'X') && (mapa[(py-30)/30][px/30] != '.')){
				py -= 30;
				dibujar_personaje();
				dir = 4;
//				dibujar_personaje();
			}else{
				py -= 30;
				pintar();
				rest(155);
				
				py -= 30;
				pintar();
				rest(155);
				
				py += 30;
				pintar();
				rest(155);
				
				py += 30;
				pintar();
				
				dir = 4;
			};
		}
		
		if(dir == 3){
			if((mapa[(py+30)/30][px/30] != 'X') && (mapa[(py+30)/30][px/30] != '.')){
				py += 30;
				dibujar_personaje();
				dir = 4;
//				dibujar_personaje();
			}else dir = 4;
		}
		
		
		pintar();
		
		rest(200);
	}
	
}
END_OF_MAIN()






