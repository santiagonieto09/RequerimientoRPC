#include "interface2.h"
#include <string.h>

#define MAX_USERS 5

nodo_usuario vectorUsuarios[MAX_USERS];
int posUsuarios = 0;


int usuario_registrado(char *cod)
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

bool_t *registrarusuariosistema_1_svc(nodo_usuario *argp, struct svc_req *rqstp)
{
    static bool_t result;
    printf("\n\n-Registrando Usuario con codigo: %s.", argp->codigo);
    fflush(stdout);
    if (posUsuarios < MAX_USERS)
    {
        vectorUsuarios[posUsuarios] = *argp;
        posUsuarios++;
        printf("\n-Usuario Registrado.");
        result = TRUE;
    }
    else
    {
        printf("\n-Cantidad máxima de usuarios alcanzada.");
        result = FALSE;
    }
    fflush(stdout);
    return &result;
}

bool_t *borrarusuariosistema_1_svc(char **argp, struct svc_req *rqstp)
{
    static bool_t result;

    int i;
    int usuarioEncontrado = usuario_registrado(*argp);
    printf("\n-Borrando usuario con codigo; %s", *argp);
    fflush(stdout);
    if (usuarioEncontrado == -1)
    {
        printf("\n-El usuario con código %s no se encuentra registrado.\n", *argp);
        result = FALSE;
    }

     // Se crea un vector temporal
    nodo_usuario vectorUsuarios_temp[MAX_USERS];
    int indice_temp = 0;
    for (int i = 0; i < posUsuarios; i++)
    {
        if (i != usuarioEncontrado)
        {
            // Copiar elementos excepto el que se eliminará
            vectorUsuarios_temp[indice_temp++] = vectorUsuarios[i];
        }
    }
    posUsuarios--;
    // Limpiar el vector original
    memset(vectorUsuarios, 0, sizeof(vectorUsuarios));
    //Copiar los usuarios del vector temporal al vector original
    for(int i= 0; i < posUsuarios; i++){
        vectorUsuarios[i]=vectorUsuarios_temp[i];
    }
    
    result = TRUE; 
    printf("\n-Usuario eliminado existosamente.");
    return &result;
}

nodo_usuario *consultarusuario_1_svc(char **argp, struct svc_req *rqstp)
{    
    static nodo_usuario result;
    printf("\n-Consultando Usuario con codigo: %s", *argp);
    int i, bandera;
    bandera = 0;
    fflush(stdout);
    for (i = 0; i < MAX_USERS; i++)
    {
        if (strcmp(*argp, vectorUsuarios[i].codigo) == 0)
        {
            result = vectorUsuarios[i];
            bandera = 1;
            fflush(stdout);
            printf("\n-El Usuario existe.");
            break;
        }
    }
    if (bandera == 0)
    {
        strcpy(result.codigo, "-1");
        strcpy(result.nombres, "");
        strcpy(result.apellidos, "");
        strcpy(result.rol, "");
        strcpy(result.hora_entrada, ""); 
        strcpy(result.fecha_entrada, ""); 
        strcpy(result.hora_salida, ""); 
        strcpy(result.fecha_salida, "");
        fflush(stdout);
        printf("\n-El Usuario no existe.");
    }

    return &result;
}

bool_t *iniciar_sesion_1_svc(nodo_administrador *argp, struct svc_req *rqstp)
{
    static bool_t result;
    printf("\n-Ingresando con usuario: %s",argp->usuario);
    fflush(stdout);
    if (strcmp(argp->usuario, "administrador") == 0 && strcmp(argp->clave, "12345678") == 0)
    {
        result = TRUE;
        printf("\n-Ingreso Autorizado.");
        fflush(stdout);
    }
    else
    {
        result = FALSE;
        printf("\n-Ingreso No Autorizado.");
        fflush(stdout);
    }
    return &result;
}


