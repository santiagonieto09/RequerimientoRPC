/*Declaracion de datos a transferir entre el cliente y el servidor*/

/*Declaracion de constantes*/
const MAXCODIGO = 10;
const MAXNOMBRES = 30;
const MAXAPELLIDOS = 30;
const MAXROL = 20;
const MAXHORA = 20;
const MAXFECHA = 30;
const MAXLOGIN = 20;

/*Declaracion de la estructura que permite almacenar los datos de un usuario que desea entrar o salir de las instalaciones*/
struct nodo_usuario{
	char codigo[MAXCODIGO];
	char nombres[MAXNOMBRES];
	char apellidos[MAXAPELLIDOS];
	char rol[MAXROL];
	char hora_entrada[MAXHORA]; 
    char fecha_entrada[MAXFECHA];
	char hora_salida[MAXHORA]; 
    char fecha_salida[MAXFECHA];	
};
/*Declaracion de la estructura que permite almacenar los datos de un administrador del servidor*/
struct nodo_administrador{
	char usuario[MAXLOGIN];
	char clave[MAXLOGIN];	
};

/*Definicion de las operaciones que se pueden realizar*/
program autorizar_usuarios{
	version autorizar_usuarios_version{
		bool registrarUsuarioSistema(nodo_usuario objUsuario)=1;
		bool borrarUsuarioSistema(string codUsuario)=2;
		nodo_usuario consultarUsuario(string codigo)=3;
		bool iniciar_sesion(nodo_administrador objAdministrador)=4;
	}=1;
}=0x20000001;
