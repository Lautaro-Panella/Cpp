#include <iostream>
#include <math.h>
using namespace std; 

// Panella Raúl Lautaro. TSP TT.

struct Ascensor { // Ascensor, donde se encuentra y sus pisos recorridos.
	int pisoActual;
	int acumulado;
}ascensores[100];

int main(int argc, char *argv[]) {
	
	int numPisos; // Variables.
	int numAscensores;
	int origen;
	int destino;
	int masCercano = 0;
	int distanciaMenor = 100;
	int acumTotal = 0;
	int menosUsado = 0;
	int acumMenor = 100;
	int masUsado = 0;
	int acumMayor = 0;
	int edificio [100][100];
	
	do { // Pido y valido cantidad de pisos y cantidad de ascensores.
	    cout << "Ingrese la cantidad de pisos, deben ser más de 1: "; cin >> numPisos;
    } while (numPisos <= 1);
	do {
	    cout << "Ingrese la cantidad de ascensores, no puede ingresar menos de 1 ascensor: "; cin >> numAscensores;
    } while (numAscensores < 1);
	cout << "Usted ingresó: " << numPisos << " pisos y " << numAscensores << " ascensores." << endl;
	
	for (int i = 0; i < numAscensores; i++) { // Ubico los ascensores en Pb e inicializo el acumulado de pisos en 0.
		ascensores[i].pisoActual = 0;
		ascensores[i].acumulado = 0;
    }
	for (int i = 0; i < numPisos; i++) { // Relleno el edificio de tamaño (pisos x ascensores) de 0.
		for (int j = 0; j < numAscensores; j++) {
		    edificio [i] [j] = 0; 	
		}
	}
    do { // Secuencia de llamadas de ascensores, origen y destino.
		do {
		cout << "Ingrese el origen (para finalizar ingrese un número negativo): "; cin >> origen;
		if (origen < 0) {
			break;
		}
		cout << "Ingrese el destino: "; cin >> destino;
		if (origen == destino || origen >= numPisos || destino < 0 || destino >= numPisos) {
			cout << "Llamada desde el piso " << origen << " con destino a " << destino << " <- Desechada." << endl;
		}
		} while (origen == destino || origen >= numPisos || destino < 0 || destino >= numPisos);
		if (origen >= 0) {
			cout << "Llamada desde el piso " << origen << " con destino a " << destino << "." << endl;
		}
		if (origen < 0) {
			break;
		}
		for (int i = 0; i < numAscensores; i++) { // Busco el ascenor más cercano al origen de la llamada.
			if ((abs(ascensores[i].pisoActual - origen)) < distanciaMenor) { // Calculo la distancia al origen.
				distanciaMenor = (abs(ascensores[i].pisoActual - origen)); // Si es la distancia la menor, la guardo.
				masCercano = i; // Guardo el número de ascensor mas cercano.
			}
		}
		for (int i = 0; i < numAscensores; i++) { 
			if ((abs(ascensores[i].pisoActual - origen)) == distanciaMenor) { // Comparo si hay varios ascensores a la misma distancia al origen.
				if (ascensores [i].acumulado < acumMenor) { // Busco cual de ellos es el de menor distancia recorrida en pisos.
			    acumMenor = ascensores[i].acumulado; // Si el acumulado es el menor, lo guardo.
				masCercano = i; // Selecciono el ascensor a llamar.
				}
			}
		}
		cout << "El ascensor más cercano es el número " << masCercano << ", con " << ascensores[masCercano].acumulado << " pisos recorridos." << endl;
		ascensores [masCercano].acumulado += (abs(ascensores [masCercano].pisoActual - origen)) + (abs(origen - destino)); // Guardo la cantidad de pisos recorridos por el ascensor selecciondo.
		ascensores [masCercano].pisoActual = destino; // Guardo el piso donde quedó ubicado dicho ascensor.
		cout << "Se utilizó el ascensor número " << masCercano << ", el cual ahora tiene " << ascensores [masCercano].acumulado << " pisos recorridos, y se encuentra en el piso número " << ascensores [masCercano].pisoActual << "." << endl;
		distanciaMenor = 100; // Reinicio la variable distanciaMenor en un valor alto para que siempre la distancia real sea menor a 100 y no quede en un valor muy bajo.
		acumMenor = 100; // Reinicio la variable acumMenor en un valor alto para que siempre el acumulado real sea menor a 100 y no quede en un valor muy bajo.
		for (int i = 0; i < numPisos; i++) { // Limpio la columna donde se va a mover el ascensor seleccionado para cargar la nueva posición y acumulado.
			edificio [i] [masCercano] = 0;
		}
		edificio [destino] [masCercano] = ascensores [masCercano].acumulado; // Cargo el ascensor en el piso de destino con sus pisos recorridos.	
		for (int i = (numPisos-1); i >= 0 ; i--) { // Muestro el edificio con sus ascensores y pisos recorridos por cada uno de ellos.
			for (int j = 0; j < numAscensores; j++) {
				cout << edificio [i] [j] << " "; 	
			}
			cout << "" << endl;
		}
	} while(origen >= 0);
	for (int i = 0; i < numAscensores; i++) { // Busco el acumulado total de pisos recorridos.
		acumTotal += ascensores [i].acumulado;
	}
	for (int i = 0; i < numAscensores; i++) { // Busco el ascensor menos usado.
		if (ascensores[i].acumulado < acumMenor) {
			acumMenor = ascensores[i].acumulado;
			menosUsado = i;
		}	
	}
	for (int i = 0; i < numAscensores; i++) { // Busco el ascensor mas usado.
		if (ascensores[i].acumulado > acumMayor) {
			acumMayor = ascensores[i].acumulado;
			masUsado = i;
		}	
	} // Conclusiones:
	cout << "El recorrido total en pisos para todos los ascensores es de " << acumTotal << " pisos." << endl; 
	cout << "El ascensor menos usado es el número " << menosUsado << " con " << acumMenor << " pisos recorridos." << endl;
	cout << "El ascensor más usado es el número " << masUsado << " con " << acumMayor << " pisos recorridos." << endl;
	return 0;
}

