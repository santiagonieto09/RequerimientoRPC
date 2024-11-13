#include "interface1.h"
#include <string.h>
#include <stdio.h>

void autorizar_usuarios1_1(char *host)
{
	CLIENT *clnt;
	nodo_respuesta1 *result_1;
	char *solicitarentrada_1_arg;
	nodo_respuesta1 *result_2;
	char *solicitarsalida_1_arg;
	usuarios *result_3; // Cambiado a usuarios *
	char *listarusuarios_1_arg;
	int opcion;
	char *codigo;
	nodo_respuesta1 *objUsuarioResultado;

#ifndef DEBUG
	clnt = clnt_create(host, autorizar_usuarios1, autorizar_usuarios_version1, "udp");
	if (clnt == NULL)
	{
		clnt_pcreateerror(host);
		exit(1);
	}
#endif /* DEBUG */

	do
	{
		printf("\n\n========== Menú ==========");
		printf("\n1. Solicitar entrada");
		printf("\n2. Solicitar salida");
		printf("\n3. Salir");
		printf("\n==========================");
		printf("\nDigite opción: ");
		scanf("%d", &opcion);
		switch (opcion)
		{
		case 1:
			printf("\n----- Solicitar entrada -----");
			codigo = (char *)malloc(sizeof(char) * 20);
			printf("\nDigite el código del usuario: ");
			scanf("%s", codigo);
			objUsuarioResultado = solicitarentrada_1(&codigo, clnt);

			if (objUsuarioResultado == (nodo_respuesta1 *)NULL)
			{
				clnt_perror(clnt, "call failed");
			}
			else if (strcmp((*objUsuarioResultado).codigo, "-1") == 0 || strcmp((*objUsuarioResultado).codigo, "-2") == 0)
			{
				printf("\n%s", (*objUsuarioResultado).respuesta);
			}
			else
			{
				printf("\n\t%s",(*objUsuarioResultado).respuesta);
				printf("\n%s", (*objUsuarioResultado).rol);
				fflush(stdout);
				printf("\n%s %s", (*objUsuarioResultado).nombres,(*objUsuarioResultado).apellidos);
				printf("\nHora y fecha de acceso: %s, %s", (*objUsuarioResultado).hora_entrada,(*objUsuarioResultado).fecha_entrada);
			}
			break;
		case 2:
			printf("\n----- Solicitar salida -----");
			codigo = (char *)malloc(sizeof(char) * 20);
			printf("\nDigite el codigo del usuario: ");
			scanf("%s", codigo);
			objUsuarioResultado = solicitarsalida_1(&codigo, clnt);
			if (objUsuarioResultado == (nodo_respuesta1 *)NULL)
			{
				clnt_perror(clnt, "call failed");
			}
			else if (strcmp((*objUsuarioResultado).codigo, "-1") == 0 || strcmp((*objUsuarioResultado).codigo, "-2") == 0)
			{
				printf("\n%s",(*objUsuarioResultado).respuesta);
			}
			else
			{
				printf("\n\t%s\n",(*objUsuarioResultado).respuesta);
				printf("%s", (*objUsuarioResultado).rol);
				printf("\n%s %s", (*objUsuarioResultado).nombres,(*objUsuarioResultado).apellidos);
				printf("\nHora y fecha de salida: %s, %s", (*objUsuarioResultado).hora_salida,(*objUsuarioResultado).fecha_salida);
			}
			break;
		case 3:
			printf(" Saliendo...\n");
			clnt_destroy(clnt);
            exit(0);
			break;
		default:
			printf("Opción inválida.\n");
			break;
		}
	} while (opcion != 3);

	result_1 = solicitarentrada_1(&solicitarentrada_1_arg, clnt);
	if (result_1 == (nodo_respuesta1 *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}

	result_2 = solicitarsalida_1(&solicitarsalida_1_arg, clnt);
	if (result_2 == (nodo_respuesta1 *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}

#ifndef DEBUG
	clnt_destroy(clnt);
#endif /* DEBUG */
}

int main(int argc, char *argv[])
{
	char *host;

	if (argc < 2)
	{
		printf("usage: %s server_host\n", argv[0]);
		exit(1);
	}
	host = argv[1];
	autorizar_usuarios1_1(host);
	exit(0);
}
