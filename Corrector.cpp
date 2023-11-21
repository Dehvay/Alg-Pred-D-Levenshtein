/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Ponga su nombre y numero de cuenta aqui.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "corrector.h"
#define DEBUG 0

int esEspacioBlanco(char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\0' || c == '.' || c == ',' || c == '(' || c == ')' || c == ';';
}

//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	FILE* fpDict;
	char texto[4000];
	char wdetec[200];
	int cont, contp, iNumE;
	iNumElementos = 0;

	fopen_s(&fpDict, szNombre, "r");

	if (fpDict != NULL)
	{
		iNumE = 0;
		contp = 0;
		while (!feof(fpDict))
		{
			fgets(texto, sizeof(texto), fpDict);

			for (cont = 0; cont < strlen(texto); cont++)
			{
				if (cont > 0 && (texto[cont] == ' ' || texto[cont] == '\t' || texto[cont] == '\n' || texto[cont] == '\r' || texto[cont] == '\0' || texto[cont] == '.' || texto[cont] == ',' || texto[cont] == '(' || texto[cont] == ')' || texto[cont] == ';') && cont > 0 && !esEspacioBlanco(texto[cont - 1]))
				{
					wdetec[contp] = '\0';
					_strlwr_s(wdetec);
					int palabraExistente = 0;
					for (int i = 0; i < iNumE; i++)
					{
						if (strcmp(szPalabras[i], wdetec) == 0)
						{
							iEstadisticas[i]++;
							palabraExistente = 1;
							break;
						}
					}

					if (!palabraExistente)
					{
						strcpy_s(szPalabras[iNumE], TAMTOKEN, wdetec);
						iEstadisticas[iNumE] = 1;
						iNumE++;
					}
					contp = 0;
				}
				else
				{
					if (!(texto[cont] == ' ' || texto[cont] == '\t' || texto[cont] == '\n' || texto[cont] == '\r' || texto[cont] == '\0') && texto[cont] != ',' && texto[cont] != '.' && texto[cont] != '(' && texto[cont] != ')' && texto[cont] != ';')

					{
						wdetec[contp] = texto[cont];
						contp++;
					}
				}
			}
			if (cont > 0 && !(texto[strlen(texto) - 1] == ' ' || texto[strlen(texto) - 1] == '\t' || texto[strlen(texto) - 1] == '\n' || texto[strlen(texto) - 1] == '\r' || texto[strlen(texto) - 1] == '\0' || texto[strlen(texto) - 1] == '.'))
			{
				wdetec[contp] = '\0';
				int palabraExistente = 0;
				for (int i = 0; i < iNumE; i++)
				{
					if (strcmp(szPalabras[i], wdetec) == 0)
					{
						iEstadisticas[i]++;
						palabraExistente = 1;
						break;
					}
				}

				if (!palabraExistente)
				{
					strcpy_s(szPalabras[iNumE], TAMTOKEN, wdetec);
					iEstadisticas[iNumE] = 1;
					iNumE++;
				}
				contp = 0;
			}
		}
		iNumElementos = iNumE;

		//bubble sort
		int cont1, cont2, auxi, i;
		char aux[TAMTOKEN];
		for (cont1 = 0; cont1 < iNumElementos - 1; cont1++)
			for(cont2 = 0; cont2 < iNumElementos - 1; cont2++)
				if (strcmp(szPalabras[cont2], szPalabras[cont2 + 1]) > 0)
				{
					strcpy_s(aux, TAMTOKEN, szPalabras[cont2]);
					strcpy_s(szPalabras[cont2], TAMTOKEN, szPalabras[cont2 + 1]);
					strcpy_s(szPalabras[cont2 + 1], TAMTOKEN, aux);
					auxi = iEstadisticas[cont2];
					iEstadisticas[cont2] = iEstadisticas[cont2 + 1];
					iEstadisticas[cont2 + 1] = auxi;
				}
	}
	else
	{
		if (DEBUG == 1)
			printf("\nNo se abrio el archivo");
	}
}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su código
	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata
	
	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su código
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}
