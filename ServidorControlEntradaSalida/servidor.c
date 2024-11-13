#include "interface1.h"
#include "interface2.h"
#include <string.h>
#include <stdlib.h> // Para malloc
#include <stdio.h>
#include <time.h>

#define MAX_USERS 5

int posUsuarios = 0;
usuarios usuariosDentro;
nodo_usuario vectorUsuarios[MAX_USERS];

// Función para formatear la hora
char *formatear_hora()
{
    time_t now;
    struct tm *tm_info;
    char *hora_formateada = (char *)malloc(10 * sizeof(char));

    time(&now);
    tm_info = localtime(&now);

    strftime(hora_formateada, 10, "%I:%M %p", tm_info);

    return hora_formateada;
}

// Función para formatear la fecha
char *formatear_fecha()
{
    time_t now;
    struct tm *tm_info;
    char *fecha_formateada = (char *)malloc(20 * sizeof(char));

    time(&now);
    tm_info = localtime(&now);

    strftime(fecha_formateada, 20, "%Y-%m-%d", tm_info);

    return fecha_formateada;
}

int usuario_dentro(char *cod)
{
    int i = 0;
    for (i = 0; i < posUsuarios; i++)
    {
        if (strcmp(cod, vectorUsuarios[i].codigo) == 0)
        {
            return i;
        }
    }
    return -1;
}

nodo_respuesta1 *solicitarentrada_1_svc(char **argp, struct svc_req *rqstp)
{
    static nodo_respuesta1 result;
    CLIENT *clnt;
    nodo_usuario *objUsuarioResultado;
    char *consultarusuario_1_arg;

#ifndef DEBUG
    clnt = clnt_create("localhost", autorizar_usuarios, autorizar_usuarios_version, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror("localhost");
        exit(1);
    }
#endif /* DEBUG */

    printf("\n-Usuario con codigo %s esta solicitando entrar.", *argp);
    fflush(stdout);

    objUsuarioResultado = consultarusuario_1(argp, clnt);

    if (objUsuarioResultado == (nodo_usuario *)NULL)
    {
        clnt_perror(clnt, "call failed");
    }
    else if (strcmp((*objUsuarioResultado).codigo, "-1") == 0)
    {
        // Usuario no encontrado
        strcpy(result.codigo, "-1");
        strcpy(result.respuesta, "Acceso denegado, codigo no registrado, por favor contacte al administrador de la aplicacion.");
    }
    else
    {
        int pos_usuario = usuario_dentro(*argp);
        // Usuario encontrado, agregar al vector si no esta adentro
        if (posUsuarios < (MAX_USERS))
        {
            if (pos_usuario != -1)
            {
                printf("\n-Usuario ya se encuentra dentro de las instalaciones.");
                fflush(stdout);
                strcpy(result.codigo, "-2");
                strcpy(result.respuesta, "El usuario ya se encuentra dentro de las instalaciones.");
            }
            else
            {
                strcpy(vectorUsuarios[posUsuarios].codigo, objUsuarioResultado->codigo);
                strcpy(vectorUsuarios[posUsuarios].nombres, objUsuarioResultado->nombres);
                strcpy(vectorUsuarios[posUsuarios].apellidos, objUsuarioResultado->apellidos);
                strcpy(vectorUsuarios[posUsuarios].rol, objUsuarioResultado->rol);
                strcpy(vectorUsuarios[posUsuarios].hora_entrada, formatear_hora());
                strcpy(vectorUsuarios[posUsuarios].fecha_entrada, formatear_fecha());
                posUsuarios++;
                printf("\n-Usuario ingresado correctamente.");
                strcpy(result.codigo, objUsuarioResultado->codigo);
                strcpy(result.respuesta, "ACCESO CONCEDIDO");
                strcpy(result.hora_entrada, formatear_hora());
                strcpy(result.fecha_entrada, formatear_fecha());
                strcpy(result.nombres, objUsuarioResultado->nombres);
                strcpy(result.apellidos, objUsuarioResultado->apellidos);
                strcpy(result.rol, objUsuarioResultado->rol);
            }
        }
        else
        {
            printf("\n-Cupo máximo de usuarios alcanzado.");
            strcpy(result.codigo,"-1");
            strcpy(result.respuesta, "Cupo máximo de usuarios alcanzado, por favor intente mas tarde.");
        }
    }

#ifndef DEBUG
    clnt_destroy(clnt);
#endif /* DEBUG */
    return &result;
}

nodo_respuesta1 *solicitarsalida_1_svc(char **argp, struct svc_req *rqstp)
{
    static nodo_respuesta1 result;
    CLIENT *clnt;

    nodo_usuario *objUsuarioResultado;
    char *consultarusuario_1_arg;

#ifndef DEBUG
    clnt = clnt_create("localhost", autorizar_usuarios, autorizar_usuarios_version, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror("localhost");
        exit(1);
    }
#endif /* DEBUG */

    printf("\n-Usuario con codigo %s esta solicitando salir.", *argp);
    fflush(stdout);

    objUsuarioResultado = consultarusuario_1(argp, clnt);

    if (objUsuarioResultado == (nodo_usuario *)NULL)
    {
        clnt_perror(clnt, "call failed");
    }
    else if (strcmp((*objUsuarioResultado).codigo, "-1") == 0)
    {
        // Usuario no encontrado
        strcpy(result.codigo, "-1");
        strcpy(result.respuesta, "Salida denegada, codigo no registrado, por favor contacte al administrador de la aplicacion.");
    }
    else
    {
        int pos_usuario = 0;
        pos_usuario = usuario_dentro(*argp);
        if (pos_usuario == -1)
        {
            printf("\n-El usuario no se encuentra dentro de las instalaciones.");
            strcpy(result.codigo, "-2");
            strcpy(result.respuesta, "El usuario no está al interior de las instalaciones.");
        }
        else
        {
            // Copiar el usuario encontrado a la respuesta
            strcpy(result.codigo,vectorUsuarios[pos_usuario].codigo);
            strcpy(result.nombres, vectorUsuarios[pos_usuario].nombres);
            strcpy(result.apellidos, vectorUsuarios[pos_usuario].apellidos);
            strcpy(result.hora_salida, formatear_hora());
            strcpy(result.fecha_salida, formatear_fecha());
            strcpy(result.respuesta, "SALIDA CONCEDIDA");
            printf("\n-Usuario con codigo %s salio de las instalaciones.", vectorUsuarios[pos_usuario].codigo);
            fflush(stdout);
            // Se crea un vector temporal
            nodo_usuario vectorUsuarios_temp[MAX_USERS];
            int indice_temp = 0;
            for (int i = 0; i < posUsuarios; i++)
            {
                if (i != pos_usuario)
                {
                    // Copiar elementos excepto el que se eliminará
                    vectorUsuarios_temp[indice_temp++] = vectorUsuarios[i];
                }
            }
            posUsuarios--;
            // Limpiar el vector original
            memset(vectorUsuarios, 0, sizeof(vectorUsuarios));
            // Copiar los usuarios del vector temporal al vector original
            for (int i = 0; i < posUsuarios; i++)
            {
                vectorUsuarios[i] = vectorUsuarios_temp[i];
            }
        }
    }

#ifndef DEBUG
    clnt_destroy(clnt);
#endif /* DEBUG */
    return &result;
}

usuarios *listarusuarios_1_svc(void *argp, struct svc_req *rqstp)
{
    printf("\n-Solicitud listar usuarios.");
    static usuarios result;
    for (int i = 0; i < MAX_USERS; i++)
    {
        strcpy(result.vectorUsuarios[i].codigo, vectorUsuarios[i].codigo);
        strcpy(result.vectorUsuarios[i].hora_entrada, vectorUsuarios[i].hora_entrada);
        strcpy(result.vectorUsuarios[i].fecha_entrada, vectorUsuarios[i].fecha_entrada);
    }
    return &result;
}
