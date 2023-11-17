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
#include "corrector.h"
#define DEBUG 0

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
	iEstadisticas = 0;

	if (DEBUG == 1)
		printf("%s", szNombre);

	fopen_s(&fpDict, szNombre, "r");

	if (fpDict != NULL)
	{
		if (DEBUG == 1)
			printf("\nSi abrio el archivo\n");

		iNumE = 0;
		contp = 0;

		while (fgets(texto, sizeof(texto), fpDict) != NULL)
		{
			
			for (cont = 0; cont < strlen(texto); cont++)
			{
				if (texto[cont] == ' ' && (cont == 0 || texto[cont - 1] != ' '))
				{
					wdetec[contp] = '\0';
					_strlwr_s(wdetec);
					strcpy_s(szPalabras[iNumE], TAMTOKEN, wdetec);
					if (DEBUG == 1)
					{
						_strlwr_s(wdetec);
						printf("\n%s", wdetec);
					}
					contp = 0;
					iNumE++;
				}
				else
				{
					if (texto[cont] != ',' && texto[cont] != '.' && texto[cont] != '(' && texto[cont] != ')' && texto[cont] != ' ')
					{
						wdetec[contp] = texto[cont];
						contp++;
					}
				}
			}
			if (texto[strlen(texto) - 1] != ' ')
			{
				wdetec[contp] = '\0';
				_strlwr_s(wdetec);
				strcpy_s(szPalabras[iNumE], TAMTOKEN, wdetec);
				iNumE++;
				if (DEBUG == 1)
				{
					_strlwr_s(wdetec);
					printf("\n%s", wdetec);
				}
			}
		}
		iNumElementos = iNumE;


		if (DEBUG == 1)
			printf("\nNum de elementos: %i\n", iNumE);
			fclose(fpDict);
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
