/* Declaración de constantes */
const MAXCODIGO1 = 10;
const MAXNOMBRES1 = 30;
const MAXAPELLIDOS1 = 30;
const MAXROL1 = 20;
const MAXRESPUESTA1 = 20;
const MAXHORA = 20;
const MAXFECHA = 30;
const MAXUSUARIOS = 100;

/* Estructura para representar una respuesta de usuario */
struct nodo_respuesta1 {
    char codigo[MAXCODIGO1];
    char nombres[MAXNOMBRES1];
    char apellidos[MAXAPELLIDOS1];
    char rol[MAXROL1];
    char respuesta[MAXRESPUESTA1];
    char hora_entrada[MAXHORA];
    char fecha_entrada[MAXFECHA];
    char hora_salida[MAXHORA];
    char fecha_salida[MAXFECHA];
};

struct usuarios {
    nodo_respuesta1 vectorUsuarios[5];
};

/* Definición de las operaciones que se pueden realizar */
program autorizar_usuarios1 {
    version autorizar_usuarios_version1 {
        nodo_respuesta1 solicitarEntrada(string codigo)=1;
        nodo_respuesta1 solicitarSalida(string codigo)=2;
        usuarios listarUsuarios()=3;
    }=1;
} = 0x20000002;

