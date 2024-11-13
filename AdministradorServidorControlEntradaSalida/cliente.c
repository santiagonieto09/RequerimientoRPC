#include "interface1.h"
#include <string.h>

void autorizar_usuarios1_1(char *host)
{
    CLIENT *clnt;
    nodo_respuesta1 *result_1;
    char *solicitarentrada_1_arg;
    nodo_respuesta1 *result_2;
    char *solicitarsalida_1_arg;
    usuarios *result_3;
    char *listarusuarios_1_arg;
    usuarios *usuariosDentro;
    int opcion = 0;

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
        printf("\n1. Consultar usuarios dentro de las instalacionones.");
        printf("\n2. Salir.");
        printf("\n==========================");
        printf("\nDigite opción: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            int cantUsuarios = 0;
            usuariosDentro = listarusuarios_1(NULL, clnt);
            if (usuariosDentro == (usuarios *)NULL)
            {
                clnt_perror(clnt, "call failed");
            }
            else
            {         
                printf("\t|  Codigo  |Hora Entrada| Fecha Entrada |\n");  
                for (int i = 0; i < 5; i++)
                {

                    if (strcmp((usuariosDentro->vectorUsuarios[i].codigo), "") != 0)
                    {
                        cantUsuarios++;
                        printf("\t| %s |  %s  |   %s  |\n", usuariosDentro->vectorUsuarios[i].codigo, usuariosDentro->vectorUsuarios[i].hora_entrada, usuariosDentro->vectorUsuarios[i].fecha_entrada);
                    }                    
                }
                printf("\nCantidad de usuarios al interior de las instalaciones: %d\n", cantUsuarios);
            }

            break;
        case 2:
            printf(" Saliendo...\n");
            clnt_destroy(clnt);
            exit(0);
            break;
        default:
            printf("Opción inválida.\n");
            break;
        }
    } while (opcion != 2);
    result_3 = listarusuarios_1((void *)&listarusuarios_1_arg, clnt);
    if (result_3 == (usuarios *)NULL)
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
