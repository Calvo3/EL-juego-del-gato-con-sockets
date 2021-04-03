#include <stdio.h>
#include <stdlib.h>
#include<winsock2.h>
#include<windows.h>
#include<conio.h>
#include<math.h>

int Quien_Empieza(){
	int VALOR=rand() % 2;
	return VALOR;
}


int main(){
	
	//SOCKETS
		WSADATA wsa;
	
	WSAStartup(MAKEWORD(2,2),&wsa);
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Error al crear el socket : %d",WSAGetLastError());
		return 1;
	}
	
	//Creando el Socket
	int server_socket;
	server_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if((server_socket = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP )) == INVALID_SOCKET)
	{
		printf("Error al crear el socket : %d" , WSAGetLastError());
	}
	
	//Definiendo la direccion
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(6680);
	server_address.sin_addr.s_addr=INADDR_ANY;
	
	 //enlazar socket con la ip y el puerto
	 bind(server_socket,(struct sockaddr*)&server_address, sizeof(server_address));
	 
	 listen(server_socket, 3);
	 
	 printf("Esperando Cliente....\n\n");
	 
	 int client_socket;
	 client_socket= accept(server_socket, 0, 0);
	 
	 //FIN INICIACION DE SOCKETS
	 
	 //Quien Empieza??
	 
	 int X=Quien_Empieza();
	 
	 //SI JUGADOR1 ES EL SERVIDOR
	 
	 if(X==1){
	 	send(client_socket,&X, sizeof(X),0);
	 	
	 	char nombre_jugador1[30];
		char nombre_jugador2[30];
		char ganador[30];
		char matriz_jugador1[3][3]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
		char matriz_jugador2[3][3]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
		int fila,fila2;
		int columna, columna2;
		int cont=0;
		int i=0,j=0;
		int aux=1;
		
		printf("\n--Bienvenido al Juego del Gato--\n");
		printf("Reglas:\n");
		printf("1.-El primero en completar 3 cuadros gana \n");
		printf("2.-Para seleccionar un cuadro hay que escribir con coordenadas, fila/columna\n");
	
		system("pause");
	
		printf("\n Introduzca su nombre: ");gets(nombre_jugador1);
		send(client_socket,&nombre_jugador1,sizeof(nombre_jugador1),0);
		recv(client_socket, &nombre_jugador2, sizeof(nombre_jugador2),0);
		printf("\n El nombre del jugador 2 es: %s\n", nombre_jugador2);
		
		do{
		//inicializando variables
		fila=0;
		fila2=0;
		columna=0;
		columna2=0;
		
		fflush(stdin);
		//Muestra Tabla
		printf("\t\t\t0   1    2    3     \n");
		for(i=0;i<3;i++){
			printf("\t\t\t%i  [%c] ", aux, matriz_jugador1[i][0]);
				for(j=1;j<3;j++){
			printf(" [%c] ", matriz_jugador1[i][j]);
		}printf("\n\n");aux++;
	}aux=1;
	//Turno del Jugador 1
	printf("\nAhora tu turno \n");
	while((columna>3 || columna<1) || (fila>3 || fila<1) || (matriz_jugador1[fila-1][columna-1]=='x') || (matriz_jugador1[fila-1][columna-1]=='o') ){
	
	printf("Seleccione fila: ");scanf("%i", &fila);
	printf("Seleccione Columna: ");scanf("%i", &columna);
	
	}
	
	send(client_socket, &fila, sizeof(fila),0);
	send(client_socket, &columna, sizeof(columna),0);
	
	matriz_jugador1[fila-1][columna-1]='x';
	
	
	//Mostrar Tablero
				printf("\t\t\t0   1    2    3     \n");
				for(i=0;i<3;i++){
					printf("\t\t\t%i  [%c] ", aux, matriz_jugador1[i][0]);
						for(j=1;j<3;j++){
					printf(" [%c] ", matriz_jugador1[i][j]);
				}printf("\n\n");aux++;
			}aux=1;
	

	//Verificando Ganador
	if((matriz_jugador1[0][0]=='x' && matriz_jugador1[0][1]=='x' && matriz_jugador1[0][2]=='x')||(matriz_jugador1[1][0]=='x' && matriz_jugador1[1][1]=='x' && matriz_jugador1[1][2]=='x')||(matriz_jugador1[2][0]=='x' && matriz_jugador1[2][1]=='x' && matriz_jugador1[2][2]=='x')||(matriz_jugador1[0][0]=='x' && matriz_jugador1[1][0]=='x' && matriz_jugador1[2][0]=='x')||(matriz_jugador1[0][1]=='x' && matriz_jugador1[1][1]=='x' && matriz_jugador1[2][1]=='x')||(matriz_jugador1[0][2]=='x' && matriz_jugador1[1][2]=='x' && matriz_jugador1[2][2]=='x')||(matriz_jugador1[0][0]=='x' && matriz_jugador1[1][1]=='x' && matriz_jugador1[2][2]=='x')||(matriz_jugador1[2][0]=='x' && matriz_jugador1[1][1]=='x' && matriz_jugador1[0][2]=='x')){
		strcpy(ganador, nombre_jugador1);
		cont=1;
	}
	
	//Si no hay ganador se pasa al jugador 2
	else {
		//copiando matriz 1 a matriz 2
		for(i=0;i<3;i++){
			matriz_jugador2[i][0]=matriz_jugador1[i][0];
				for(j=0;j<3;j++){
			matriz_jugador2[i][j]=matriz_jugador1[i][j];
		}
	}
	
	//Turno del Jugador 2
	printf("\nAhora es el turno de %s\n\n",nombre_jugador2);
	
	recv(client_socket,&fila2,sizeof(fila2),0);
	recv(client_socket,&columna2,sizeof(columna2),0);
	
	matriz_jugador2[fila2-1][columna2-1]='o';
	//Mostrar Tablero
				printf("\t\t\t0   1    2    3     \n");
				for(i=0;i<3;i++){
					printf("\t\t\t%i  [%c] ", aux, matriz_jugador2[i][0]);
						for(j=1;j<3;j++){
					printf(" [%c] ", matriz_jugador2[i][j]);
				}printf("\n\n");aux++;
			}aux=1;
			
	
	
	//Verificando Ganador
	if((matriz_jugador2[0][0]=='o' && matriz_jugador2[0][1]=='o' && matriz_jugador2[0][2]=='o')||(matriz_jugador2[1][0]=='o' && matriz_jugador2[1][1]=='o' && matriz_jugador2[1][2]=='o')||(matriz_jugador2[2][0]=='o' && matriz_jugador2[2][1]=='o' && matriz_jugador2[2][2]=='o')||(matriz_jugador2[0][0]=='o' && matriz_jugador2[1][0]=='o' && matriz_jugador2[2][0]=='o')||(matriz_jugador2[0][1]=='o' && matriz_jugador2[1][1]=='o' && matriz_jugador2[2][1]=='o')||(matriz_jugador2[0][2]=='o' && matriz_jugador2[1][2]=='o' && matriz_jugador2[2][2]=='o')||(matriz_jugador2[0][0]=='o' && matriz_jugador2[1][1]=='o' && matriz_jugador2[2][2]=='o')||(matriz_jugador2[2][0]=='o' && matriz_jugador2[1][1]=='o' && matriz_jugador2[0][2]=='o')){
		strcpy(ganador, nombre_jugador2);
		cont=1;
	}
	else {
		//Copiando matriz 2 a matriz 1
		for(i=0;i<3;i++){
			matriz_jugador1[i][0]=matriz_jugador2[i][0];
				for(j=0;j<3;j++){
			matriz_jugador1[i][j]=matriz_jugador2[i][j];
		}
	}
	}
		
	}



		
		
	}while(cont==0);
	printf("\nFelicidades a %s por ganar!!!", ganador);
	
	 	
	 	
	 } 
	 
	 //SI JUGADOR1 ES EL CLIENTE
	 
	 else if(X==0){
	 	send(client_socket,&X, sizeof(X),0);
	 	
	 	char nombre_jugador1[30];
		char nombre_jugador2[30];
		char ganador[30];
		char matriz_jugador1[3][3]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
		char matriz_jugador2[3][3]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
		int fila,fila2;
		int columna, columna2;
		int cont=0;
		int i=0,j=0;
		int aux=1;
		
		printf("\n--Bienvenido al Juego del Gato--\n");
		printf("Reglas:\n");
		printf("1.-El primero en completar 3 cuadros gana \n");
		printf("2.-Para seleccionar un cuadro hay que escribir con coordenadas, fila/columna\n");
	
		system("pause");
	
		recv(client_socket, &nombre_jugador1, sizeof(nombre_jugador1),0);
		printf("\n El nombre del jugador 2 es: %s", nombre_jugador1);
		printf("\n Introduzca su nombre: ");gets(nombre_jugador2);
		send(client_socket, &nombre_jugador2, sizeof(nombre_jugador2),0);
		
		do{
		//inicializando variables
		fila=0;
		fila2=0;
		columna=0;
		columna2=0;
		
		fflush(stdin);
		//Muestra Tabla
		printf("\t\t\t0   1    2    3     \n");
		for(i=0;i<3;i++){
			printf("\t\t\t%i  [%c] ", aux, matriz_jugador1[i][0]);
				for(j=1;j<3;j++){
			printf(" [%c] ", matriz_jugador1[i][j]);
		}printf("\n\n");aux++;
	}aux=1;
	//Turno del Jugador 1
	printf("\nAhora es el turno del jugador 2: \n\n");
	
	recv(client_socket,&fila, sizeof(fila),0);
	recv(client_socket,&columna, sizeof(columna),0);
	
	matriz_jugador1[fila-1][columna-1]='x';
	
	
	//Mostrar Tablero
				printf("\t\t\t0   1    2    3     \n");
				for(i=0;i<3;i++){
					printf("\t\t\t%i  [%c] ", aux, matriz_jugador1[i][0]);
						for(j=1;j<3;j++){
					printf(" [%c] ", matriz_jugador1[i][j]);
				}printf("\n\n");aux++;
			}aux=1;
	

	//Verificando Ganador
	if((matriz_jugador1[0][0]=='x' && matriz_jugador1[0][1]=='x' && matriz_jugador1[0][2]=='x')||(matriz_jugador1[1][0]=='x' && matriz_jugador1[1][1]=='x' && matriz_jugador1[1][2]=='x')||(matriz_jugador1[2][0]=='x' && matriz_jugador1[2][1]=='x' && matriz_jugador1[2][2]=='x')||(matriz_jugador1[0][0]=='x' && matriz_jugador1[1][0]=='x' && matriz_jugador1[2][0]=='x')||(matriz_jugador1[0][1]=='x' && matriz_jugador1[1][1]=='x' && matriz_jugador1[2][1]=='x')||(matriz_jugador1[0][2]=='x' && matriz_jugador1[1][2]=='x' && matriz_jugador1[2][2]=='x')||(matriz_jugador1[0][0]=='x' && matriz_jugador1[1][1]=='x' && matriz_jugador1[2][2]=='x')||(matriz_jugador1[2][0]=='x' && matriz_jugador1[1][1]=='x' && matriz_jugador1[0][2]=='x')){
		strcpy(ganador, nombre_jugador1);
		cont=1;
	}
	
	//Si no hay ganador se pasa al jugador 2
	else {
		//copiando matriz 1 a matriz 2
		for(i=0;i<3;i++){
			matriz_jugador2[i][0]=matriz_jugador1[i][0];
				for(j=0;j<3;j++){
			matriz_jugador2[i][j]=matriz_jugador1[i][j];
		}
	}
	
	//Turno del Jugador 2
	printf("\nAhora es tu turno\n",nombre_jugador2);
	
	while((columna2>3 || columna2<1) || (fila2>3 || fila2<1) || (matriz_jugador2[fila2-1][columna2-1]=='x') || (matriz_jugador2[fila2-1][columna2-1]=='o') ){
	
	printf("Seleccione fila: ");scanf("%i", &fila2);
	printf("Seleccione Columna: ");scanf("%i", &columna2);
	
	}
	
	send(client_socket, &fila2, sizeof(fila2),0);
	send(client_socket, &columna2, sizeof(columna2),0);
	
	matriz_jugador2[fila2-1][columna2-1]='o';
	//Mostrar Tablero
				printf("\t\t\t0   1    2    3     \n");
				for(i=0;i<3;i++){
					printf("\t\t\t%i  [%c] ", aux, matriz_jugador2[i][0]);
						for(j=1;j<3;j++){
					printf(" [%c] ", matriz_jugador2[i][j]);
				}printf("\n\n");aux++;
			}aux=1;
			
	
	
	//Verificando Ganador
	if((matriz_jugador2[0][0]=='o' && matriz_jugador2[0][1]=='o' && matriz_jugador2[0][2]=='o')||(matriz_jugador2[1][0]=='o' && matriz_jugador2[1][1]=='o' && matriz_jugador2[1][2]=='o')||(matriz_jugador2[2][0]=='o' && matriz_jugador2[2][1]=='o' && matriz_jugador2[2][2]=='o')||(matriz_jugador2[0][0]=='o' && matriz_jugador2[1][0]=='o' && matriz_jugador2[2][0]=='o')||(matriz_jugador2[0][1]=='o' && matriz_jugador2[1][1]=='o' && matriz_jugador2[2][1]=='o')||(matriz_jugador2[0][2]=='o' && matriz_jugador2[1][2]=='o' && matriz_jugador2[2][2]=='o')||(matriz_jugador2[0][0]=='o' && matriz_jugador2[1][1]=='o' && matriz_jugador2[2][2]=='o')||(matriz_jugador2[2][0]=='o' && matriz_jugador2[1][1]=='o' && matriz_jugador2[0][2]=='o')){
		strcpy(ganador, nombre_jugador2);
		cont=1;
	}
	else {
		//Copiando matriz 2 a matriz 1
		for(i=0;i<3;i++){
			matriz_jugador1[i][0]=matriz_jugador2[i][0];
				for(j=0;j<3;j++){
			matriz_jugador1[i][j]=matriz_jugador2[i][j];
		}
	}
	}
		
	}



		
		
	}while(cont==0);
	printf("\nFelicidades a %s por ganar!!!", ganador);
	 	
	 }
	
	
	close(server_socket);
	printf("\n\nFin del programa...");getch();
	return 0;
}
