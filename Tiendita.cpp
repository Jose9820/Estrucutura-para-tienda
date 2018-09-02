#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N=5;

struct inventarioProductos{
 	string marca, modelo,color, mRam, mInterna, camara, procesador, versionSO;
 	double precio;
 	int ID;
}smartphones[N], compras[N];

//funciones empleadas para guardar y para recuperar la informacion de los smartphones en documento de texto
string reemplazarEspacios(string);
string reemplazarSharp(string);
void insertar(string, string, string, string, string, string, string, string, double, int);
void escribirEnArchivo();
void escribirEnArchivoParaCompras(int); 
void recuperarDeArchivo();
//void recuperarDeArchivoParaCompras();
void pedirDatos();
void inicializar();
int buscarlugarVacio();
int buscarlugarVacioParaCompras();
int busquedaSecuencial(int);
int busquedaSecuencialParaCompras(int);
//funciones de menu
void menuUsuario();
void menuAcceso();
void menuAdministrador();
//funciones para compras y detalles de smartphones
void listaProductos();
void listaCompras();
void mostrarDetalles(int);
void modificarListaCompras();
void modificarDatosSmartphone(int);
void realizarCompra(int);

int main(){
 	char*locale;
 	locale=setlocale(LC_ALL,"");
 	//se incializian las variables de la estrctura smartphone con valores vacios
  	inicializar();
  	//luego se recuera del de documento de texto la informacion que se a introducido con anterioridad
  	recuperarDeArchivo();
  	// se llama a la funcio que mostrara el menu de acceso
 	menuAcceso();
 	return 0;
}

void menuAcceso(){
	int opcion;
 	do{
 		cout << "\tBIENVENID@ a nuestra tienda de smartphones.....\n\t Aqui podras realizar las siguientes acciones:\n";
	 	cout << "\n1. Ingresar como Usuario"
	 		 << "\n2. Ingresar como Administrador"
	 		 << "\n3. Salir";
	 	cout << "\n\nEliga una opcion:\t";
	 	cin >> opcion;
	 	switch(opcion){
	 		case 1:
	 			system("cls");
	 			menuUsuario();
	 			break;
	 		case 2:
	 			system("cls");
	 			menuAdministrador();
	 			break;
	 		case 3:
	 			cout << "\nGracias por utilizar este programa...... =)\n\n";
	 			system("pause");
	 			break;
	 		default:
	 			cout << "\nOpcion no valida. Reintente......\n\n";
	 			system("pause");
	 			break;
		 }
	 	system("cls");
	 }while (opcion != 3);
}

void menuAdministrador(){
 	int opcion;
 	do{
	 	cout << "\tBIENVENID@ a nuestra tienda de smartphones.....\n\t Aqui podras realizar las siguientes acciones:\n";
	  	cout << "\n1. Agregar un smartphone al inventario"
	  		 << "\n2. Modificar los datos de algun smartphone. Es necesario el ID"
	  		 << "\n3. Ver lista de smartphones"
	  		 << "\n4. Salir";
	  	cout << "\n\nEliga una opcion:\t";
	  	cin >> opcion;
	  	switch(opcion){
	  		case 1:
	  			system("cls");
	  			pedirDatos();
	  			escribirEnArchivo();
	  			break;
	  		case 2:
	  			int ID, resultado;
	  			system("cls");
	  			cout << "\nPara realizar esta opcion es necesario el ID del smartphone\n";
			 	cout << "\n\nIngrese el ID a buscar:\t";
			 	cin >> ID;
			 	resultado= busquedaSecuencial(ID);
			 	if (resultado == -1) {
				 	cout << "\n\nRegistro con ID ingresado no encontrado\n";
				 } 
			 	else {
			 		mostrarDetalles(resultado);
			 		modificarDatosSmartphone(resultado);
			 	 }
			  	cout << "\n\n";
	  			system("pause");
	  			break;
	  		case 3:
	  			system("cls");
	  			listaProductos();
	  			cout << "\n\n";
	  			system("pause");
	  			break;
	  		case 4:
	  			cout << "\nHasta pronto.....\n\n";
	  			system("pause");
	  			break;
	  		default:
	  			cout << "Opción no valida. Reintente......\n\n";
	  			system("pause");
	  			break;
		  }
	 	system("cls");
 	 }while (opcion != 4);
}

void menuUsuario(){
	int opcion;
 	do{
 		int ID, resultado, respuesta;
	 	cout << "\tBIENVENID@ a nuestra tienda de smartphones.....\n\t Aqui podras realizar las siguientes acciones:\n";
	 	cout << "\n1. Ver lista de smartphones disponibles"
	 		 << "\n2. Comprar alguna smartphone. Es necesario el ID"
	 		 << "\n3. Ver mas detalles de algun smartphone. Es necesario el ID"
	 		 << "\n4. Ver lista de compras"
	 		 << "\n5. Modificar lista de compras"
	 		 << "\n6. Salir";
	 	cout << "\n\nEliga una opcion:\t";
	 	cin >> opcion;
	 	switch(opcion){
	  		case 1:
	  			system("cls");
	  			listaProductos();
	  			cout << "\n\n";
	  			system("pause");
	  			break;
	  		case 2:
	  			system("cls");
	  			cout << "\nPara realizar esta opcion es necesario el ID del smartphone\n";
			 	cout << "\n\nIngrese el ID a buscar:\t";
			 	cin >> ID;
			 	resultado= busquedaSecuencial(ID);
	  			if (resultado == -1) {
				 	cout << "\n\nRegistro con ID ingresado no encontrado\n";
				 } 
			 	else {
			 		mostrarDetalles(resultado);
			 		cout << "\n Confirmar la compra de este smartphone:\n1. Si\n2. No\n";
			 		cin >> respuesta;
			 		if (respuesta == 1){
			 			cout << "\n¡Compra lista!. La compra sera agragada a su lista de compras\n";
					 	realizarCompra(ID);
					 }else if(respuesta == 2){
					 	cout << "\nCompra cancelada...... =(\n";
					 }
			 	 }
	  			cout << "\n\n";
	  			system("pause");
	  			break;
	  		case 3:
	  			system("cls");
	  			cout << "\nPara realizar esta opcion es necesario el ID del smartphone\n";
			 	cout << "\n\nIngrese el ID a buscar:\t";
			 	cin >> ID;
			 	resultado= busquedaSecuencial(ID);
			 	if (resultado == -1) {
				 	cout << "\n\nRegistro con ID ingresado no encontrado\n";
				 } 
			 	else {
			 		mostrarDetalles(resultado);
			 	 }
	  			cout << "\n\n";
	  			system("pause");
	  			break;
	  		case 4:
	  			system("cls");
	  			listaCompras();
	  			cout << "\n\n";
	  			system("pause");
	  			break;
	  		case 5:
	  			system("cls");
	  			modificarListaCompras();
	  			cout << "\n\n";
	  			system("pause");
	  			break;
	  		case 6:
	  			cout << "\nGracias por su preferencia. Vuelva pronto...... =)";
	  			cout << "\nSu Compra sera enviada a su domicilio\n\n";
	  			system("pause");
	  			break;
	  		default:
	  			cout << "\nOpcion no valida. Reintente......\n\n";
	  			system("pause");
	  			break;
	  	 }	
	   	system("cls");
	 }while(opcion != 6);
}

int busquedaSecuencial(int b) {
 	for (int i = 0; i < N; i++) {
 		if (smartphones[i].ID == b) {
	 		return i;
	 	 }
	 }
 	return - 1 ;
 }

int busquedaSecuencialParaCompras(int b) {
 	for (int i = 0; i < N; i++) {
 		if (compras[i].ID == b) {
	 		return i;
	 	 }
	 }
 	return - 1 ;
 }

void listaProductos(){
 	cout << setw(6) << "ID"
 		 << setw(22) << "Marca"
 		 << setw(22) << "Modelo"
 		 << setw(22) << "Color"
 		 << setw(22) << "Precio" << endl;
 	cout << setw(10) << "   -------------------------------------------------------------------------------------------\n";
 	for (int i=0; i < N; i++){
 		if (smartphones[i].ID != 0){
 			cout << setw(6) << smartphones[i].ID 
			     << setw(22) << smartphones[i].marca 
			     << setw(22) << smartphones[i].modelo 
			     << setw(22) << smartphones[i].color 
			     << setw(18) << "$" << smartphones[i].precio << endl;
		 }
	 }
}

void realizarCompra(int ID){
 	int lugarVacio, resultado;
  	lugarVacio=buscarlugarVacioParaCompras();
  	resultado=busquedaSecuencial(ID);
 	if (lugarVacio == -1) {
 		cout << "Ya no hay lugar" << endl;
	 	return;
	 }
 	compras[lugarVacio].marca = smartphones[resultado].marca;
 	compras[lugarVacio].modelo = smartphones[resultado].modelo;
 	compras[lugarVacio].color = smartphones[resultado].color;
 	compras[lugarVacio].mRam = smartphones[resultado].mRam;
 	compras[lugarVacio].mInterna = smartphones[resultado].mInterna;
 	compras[lugarVacio].camara = smartphones[resultado].camara;
 	compras[lugarVacio].procesador = smartphones[resultado].procesador;
 	compras[lugarVacio].versionSO = smartphones[resultado].versionSO;
 	compras[lugarVacio].precio = smartphones[resultado].precio;
 	compras[lugarVacio].ID= smartphones[resultado].ID;
 	smartphones[resultado].ID = 0;
}

void listaCompras(){
 	cout << setw(6) << "ID"
 		 << setw(22) << "Marca"
 		 << setw(22) << "Modelo"
 		 << setw(22) << "Color"
 		 << setw(22) << "Precio" << endl;
 	cout << setw(10) << "   -------------------------------------------------------------------------------------------\n";
 	for (int i=0; i < N; i++){
 		if (compras[i].ID != 0){
 			cout << setw(6) << compras[i].ID 
			     << setw(22) << compras[i].marca 
			     << setw(22) << compras[i].modelo 
			     << setw(22) << compras[i].color 
			     << setw(18) << "$" << compras[i].precio << endl;
		 }
	 }
}

void modificarListaCompras(){
	int ID, opcion, resultado;
 	listaCompras();
 	cout << "\nPara realizar esta opcion es necesario el ID del smartphone\n";
 	cout << "\n\nIngrese el ID a buscar:\t";
 	cin >> ID;
 	resultado = busquedaSecuencialParaCompras(ID);
  	if (resultado == -1) {
  		cout << "\n\nRegistro con ID ingresado no encontrado\n";
  		return;
 	}else {
 		cout << "\nDesea eleminar esta compra de su lista\n1. Si\n2. No\n";
 		cin >> opcion;
 		if (opcion == 1){
 			cout << "\nCompra elimidada exitosamente\n";
 			compras[resultado].ID=0;
		 }else if(opcion == 2){
		 	cout << "\nAcción cancelada\n";
		 }else{
		 	cout << "\nError. Opción no valida\n";
		 }
  	 }
 	
}

void mostrarDetalles(int i){
	cout << "\n\nMarca:\t" << smartphones[i].marca
		 << "\nModelo:\t" << smartphones[i].modelo
		 << "\nColor:\t" << smartphones[i].color
		 << "\nMemoria Ram:\t" << smartphones[i].mRam
		 << "\nMemoria Interna:\t" << smartphones[i].mInterna
		 << "\nCamara:\t" << smartphones[i].camara
		 << "\nProcesador:\t" << smartphones[i].procesador
		 << "\nVersion SO:\t" << smartphones[i].versionSO
		 << "\nPrecio:\t" << smartphones[i].precio << endl;
}

string reemplazarEspacios(string texto) {
 	for (int i = 0; i < ( int) texto.length(); ++i) {
	 	if (texto [i] == ' ' ) {
 			texto .replace(i, 1, "#");
 		 }
 	 }
 	return texto;
}

string reemplazarSharp(string texto) {
 	for (int i = 0; i < (int) texto .length(); ++i) {
 		if (texto [i] == '#') {
 			texto.replace(i, 1, " ");
 		 }
 	 }
 	return texto;
}

void insertar(string marcaX, string modeloX, string colorX, string mRamX, string mInternaX, string camaraX, string procesadorX, string versionSOX, double precioX, int IDX) {
 	int lugarVacio = buscarlugarVacio();
 	if (lugarVacio == -1) {
 		cout << "Ya no hay lugar" << endl;
	 	return;
	 }
 	smartphones[lugarVacio].marca = marcaX;
 	smartphones[lugarVacio].modelo = modeloX;
 	smartphones[lugarVacio].color = colorX;
 	smartphones[lugarVacio].mRam = mRamX;
 	smartphones[lugarVacio].mInterna = mInternaX;
 	smartphones[lugarVacio].camara = camaraX;
 	smartphones[lugarVacio].procesador = procesadorX;
 	smartphones[lugarVacio].versionSO = versionSOX;
 	smartphones[lugarVacio].precio = precioX;
 	smartphones[lugarVacio].ID = IDX;
}

void recuperarDeArchivo() {
 	ifstream lecturaArchivo("smartphones.txt" , ios::in);
	if (!lecturaArchivo) {
	 	cerr << "No se pudo abrir el archivo" << endl;
	 	exit(1);
	 }	
  	string marcaX, modeloX,colorX, mRamX, mInternaX, camaraX, procesadorX, versionSOX;
 	double precioX;
 	int IDX;
  	while (lecturaArchivo >> marcaX >> modeloX >> colorX >> mRamX >> mInternaX >> camaraX >> procesadorX >> versionSOX >> precioX >> IDX) {
	 	insertar(
		 	reemplazarSharp(marcaX),
		 	reemplazarSharp(modeloX),
	 		reemplazarSharp(colorX), 
	 	 	reemplazarSharp(mRamX),
	 	 	reemplazarSharp(mInternaX),
	 	 	reemplazarSharp(camaraX),
	 	 	reemplazarSharp(procesadorX),
	 	 	reemplazarSharp(versionSOX),
	 		precioX,
		 	IDX);
	}
}

void escribirEnArchivo() {
 	ofstream salidaArchivo("smartphones.txt" , ios ::out);
 	if (!salidaArchivo) {
	 	cerr << "No se pudo abrir archivo" << endl;
 		exit(1);
 	}
  	for (int i = 0; i < N; i ++) {
  		if (smartphones[i].ID != 0) {
 			salidaArchivo
			 	<< reemplazarEspacios(smartphones[i].marca) << ' '
			 	<< reemplazarEspacios(smartphones[i].modelo) << ' '
			 	<< reemplazarEspacios(smartphones[i].color) << ' '
			 	<< reemplazarEspacios(smartphones[i].mRam) << ' '
			 	<< reemplazarEspacios(smartphones[i].mInterna) << ' '
			 	<< reemplazarEspacios(smartphones[i].camara) << ' '
			 	<< reemplazarEspacios(smartphones[i].procesador) << ' '
			 	<< reemplazarEspacios(smartphones[i].versionSO) << ' '
			 	<< smartphones[i].precio << ' '
			 	<< smartphones[i].ID << ' ' << endl;
	 	 }
 	 }
 }
 
void escribirEnArchivoParaCompras(int ID){
 	ofstream salidaArchivo("ListaCompras.txt" , ios ::out);
 	if (!salidaArchivo){
 		cerr << "Nose puede abrir archivo" << endl;
 		exit(1);
	 }
 	for (int i = 0; i < N; i ++) {
  		if (compras[i].ID != 0) {
 			salidaArchivo
			 	<< reemplazarEspacios(compras[i].marca) << ' '
			 	<< reemplazarEspacios(compras[i].modelo) << ' '
			 	<< reemplazarEspacios(compras[i].color) << ' '
			 	<< reemplazarEspacios(compras[i].mRam) << ' '
			 	<< reemplazarEspacios(compras[i].mInterna) << ' '
			 	<< reemplazarEspacios(compras[i].camara) << ' '
			 	<< reemplazarEspacios(compras[i].procesador) << ' '
			 	<< reemplazarEspacios(compras[i].versionSO) << ' '
			 	<< compras[i].precio << ' '
			 	<< compras[i].ID << ' ' << endl;
	 	 }
 	 }
}

void inicializar() {
 	for (int i = 0 ; i < N; i ++) {
	 	smartphones[i].marca = "" ;
	 	smartphones[i].modelo = "";
	 	smartphones[i].color = "";
	  	smartphones[i].mRam = "";
	 	smartphones[i].mInterna = "";
	 	smartphones[i].camara = "";
	 	smartphones[i].procesador = "";
	 	smartphones[i].versionSO = "";
	 	smartphones[i].precio = 0;
	 	smartphones[i].ID = 0;
	 	compras[i].marca = "";
	 	compras[i].modelo = "";
	 	compras[i].color = "";
	 	compras[i].mRam = "";
	 	compras[i].mInterna = "";
	 	compras[i].camara = "";
	 	compras[i].procesador = "";
	 	compras[i].versionSO = "";
	 	compras[i].precio = 0;
	 	compras[i].ID= 0;
	 	
	 }
 }

int buscarlugarVacio() {
 	for (int i = 0 ; i < N; i ++) {
 		if (smartphones[i].ID == 0 ) {
	 		return i;
 		 }
	 }
 	return -1 ;
}

int buscarlugarVacioParaCompras() {
 	for (int i = 0 ; i < N; i ++) {
 		if (compras[i].ID == 0 ) {
	 		return i;
 		 }
	 }
 	return -1 ;
}

void pedirDatos() {
  	string marcaX, modeloX,colorX, mRamX, mInternaX, camaraX, procesadorX, versionSOX;
 	double precioX;
 	int IDX;
	cout << "\nEscriba los datos del smartphone." << endl;
 	cout << "\nID: " ;	
 	cin >> IDX;
 	for (int i = 0; i < N; i ++) {
 		if (IDX == smartphones[i].ID) {
 		 	cout << "\nYa existe un registro con esta ID\n";
 		 	return;
		 }
	 }
 	cout << "Marca: " ;
 	getline(cin, marcaX);
 	getline(cin, marcaX);
 	cout << "Modelo: " ;
 	getline(cin, modeloX);
 	 	cout << "Color: " ;
 	getline(cin, colorX);
 	cout << "Memoria Ram: " ;
 	getline(cin, mRamX);
 	cout << "Memoria Interna: " ;
 	getline(cin, mInternaX);
 	cout << "Camara: " ;
 	getline(cin, camaraX);
 	cout << "Procesador: " ;
 	getline(cin, procesadorX);
 	cout << "Versión SO: " ;
 	getline(cin, versionSOX);
 	cout << "Precio: ";
 	cin >> precioX;
 	insertar(marcaX, modeloX,colorX, mRamX, mInternaX, camaraX, procesadorX, versionSOX, precioX, IDX);
}

void menuCambiar() {
 	cout << "\n¿Qué desea cambiar?" << endl;
 	cout << "1.- Marca" << endl;
 	cout << "2.- Modelo" << endl;
 	cout << "3.- Color" << endl;
 	cout << "4.- Memoria Ram" << endl;
 	cout << "5.- Memoria Interna" << endl;
 	cout << "6.- Camara" << endl;
 	cout << "7.- Procesador" << endl;
 	cout << "8.- Versión SO" << endl;
 	cout << "9.- Precio" << endl;
 	cout << "10.- Cancelar" << endl;
 	cout << "\nElija su opción:\t" << endl;
}

void modificarDatosSmartphone(int ID){
 	int opcion;
 	menuCambiar();
 	cin>>opcion;
 	switch (opcion) {
	 	case 1:
 	 		cout << "\nNuevo nombre de marca: " << endl;
 	  		getline(cin, smartphones[ID].marca);
 	 		getline(cin, smartphones[ID].marca);
  	 		cout << "Cambio efectuado" << endl;
 	 		escribirEnArchivo();
	 		break;
	 	case 2:
	  		cout << "\nNuevo nombre de modelo:" << endl;
 	 		getline(cin, smartphones[ID].modelo);
 	 		getline(cin, smartphones[ID].modelo);
	 		cout << "Cambio efectuado" << endl;
	 		escribirEnArchivo();
	 		break;
	 	case 3:
 	 		cout << "\nDame nuevo color:" << endl;
  	 		getline(cin, smartphones[ID].color);
 	 		getline(cin, smartphones[ID].color);
 	  		cout << "Cambio efectuado" << endl;
 	 		escribirEnArchivo();
	  	break;
	   	case 4:
	  		cout << "\nMemoria ram:" << endl;
	  		getline(cin, smartphones[ID].mRam);
 	   		getline(cin, smartphones[ID].mRam);
	  		cout << "Cambio efectuado" << endl;
	   		escribirEnArchivo();
	  		break;
	   	case 5:
	  		cout << "\nMemoria interna:" << endl;
	   		getline(cin, smartphones[ID].mInterna);
 	  		getline(cin, smartphones[ID].mInterna);
	 		cout << "Cambio efectuado" << endl;
	   		escribirEnArchivo();
	  		break;
	 	case 6:
	  		cout << "\nCamara:" << endl;
	 		getline(cin, smartphones[ID].camara);
 	 		getline(cin, smartphones[ID].camara);
	  		cout << "Cambio efectuado" << endl;
	 		escribirEnArchivo();
	 		break;
		case 7:
	 		cout << "\nProcesador:" << endl;
	 		getline(cin, smartphones[ID].procesador);
 	  		getline(cin, smartphones[ID].procesador);
	 		cout << "Cambio efectuado" << endl;
	 		escribirEnArchivo();
	 		break;
	 	case 8:
	 		cout << "\nVersion SO:" << endl;
	 		getline(cin, smartphones[ID].versionSO);
 	  		getline(cin, smartphones[ID].versionSO);
	 		cout << "Cambio efectuado" << endl;
	 		escribirEnArchivo();
	 		break;
	  	case 9:
	  		cout << "\nNuevo precio:" << endl;
	 		cin >> smartphones[ID].precio;
	 		cout << "Cambio efectuado" << endl;
	 		escribirEnArchivo();
	  		break;
	 	case 10:
	 		
	 		break;
	  	default:
	  		cout << "\nOpcion no valida.\n";
	 		break;
	 }
}
