// programa en C para introducir los datos en la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	int ID;
	//int i;
	char IDs [3];
	char username[30]; 
	char password[30];
	char estado[10];
	char consulta [80];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion, entrando nuestras claves de acceso y
	//el nombre de la base de datos a la que queremos acceder 
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "bd",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
		printf ("Escribe el ID, username, password y estado del jugador, separados por un blanco\n");
		err = scanf ("%d %s %s %s",&ID, username, password, estado);
		if (err!=4) {
			printf ("Error al introducir los datos \n");
			exit (1);
		}
		// Ahora construimos el string con el comando SQL
		// para insertar la persona en la base. Ese string es:
		// INSERT INTO personas VALUES ('ID', 'contraseña', 'estado','username'); 
		strcpy (consulta, "INSERT INTO JUGADOR VALUES ('");
		//concatenamos el ID en un string y lo concatenamos
		sprintf(IDs, "%d", ID);
		strcat (consulta, IDs);
		strcat (consulta, "','");	
		//concatenamos el username 
		strcat (consulta, password); 
		strcat (consulta, "','");
		//concatenamos la password 
		strcat (consulta, estado); 
		strcat (consulta, "','");
		//concatenamos el estado
		strcat (consulta, username);
		strcat (consulta, "'");
		strcat (consulta, ");");
		
		printf("consulta = %s\n", consulta);
		// Ahora ya podemos realizar la insercion 
		err = mysql_query(conn, consulta);
		if (err!=0) {
			printf ("Error al introducir datos la base %u %s\n", 
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
	
	// cerrar la conexion con el servidor MYSQL 
	mysql_close (conn);
	exit(0);
}
