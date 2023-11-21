/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(c) Andres Govea Ramirez.
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#define DEPURAR 1
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
	FILE* fpDicc;
	char linea[7200];
	char pDetectada[TAMTOKEN], referencia[NUMPALABRAS][TAMTOKEN],aux[NUMPALABRAS][TAMTOKEN];
	int i, iPalabra = 0, espacio, j;
	iNumElementos = 0;
	// abrir el achivo
	
	fopen_s(&fpDicc, szNombre, "r");
	if (fpDicc != NULL)
	{

		while (!feof(fpDicc))
		{
			fgets(linea, sizeof(linea), fpDicc);
			
			for (i = 0; i <= strlen(linea); i++)
			{

				if (linea[i] == ' ' || linea[i] == '\t' || linea[i] == '\n' || linea[i] == '\r' || linea[i] == '\0')
				{
					if (!espacio && iPalabra > 0) {
						pDetectada[iPalabra] = '\0';
						_strlwr(pDetectada);
						strcpy(referencia[iNumElementos], pDetectada);
						int j;
						for (j = 0; j < iNumElementos; j++)
						{
							if (strcmp(referencia[j], pDetectada) == 0)
							{
								iEstadisticas[j]++;
								break;
							}
						}

						if (j == iNumElementos) 
						{

							strcpy_s(szPalabras[iNumElementos], TAMTOKEN, pDetectada);
							iEstadisticas[iNumElementos] = 1;
							iNumElementos++;  
						}

						iPalabra = 0;
					}
					espacio = 1;
				}
				else 
				{
					if (linea[i] != '(' && linea[i] != ')' && linea[i] != ',' && linea[i] != '.' && linea[i] != ';' && linea[i] != '-' && linea[i] != '_' && linea[i] != '¿' && linea[i] != '?' && linea[i] != '!' && linea[i] != '¡' && linea[i] != '"' && linea[i] != ':' && linea[i] != '{' && linea[i] != '}' && linea[i] != '<' && linea[i] != '>' && linea[i] != '[' && linea[i] != ']' && linea[i] != '~') 
					{
						pDetectada[iPalabra] = linea[i];
						iPalabra++;
					}
					espacio = 0;
				}

			}

		}

		for (int k = 0; k < iNumElementos - 1; k++)
		{
			for (int n = 0; n < iNumElementos - k - 1; n++)
			{
				if (strcmp(szPalabras[n], szPalabras[n + 1]) > 0)
				{
					
					char temp[TAMTOKEN];
					strcpy_s(temp, TAMTOKEN, szPalabras[n]);
					strcpy_s(szPalabras[n], TAMTOKEN, szPalabras[n + 1]);
					strcpy_s(szPalabras[n + 1], TAMTOKEN, temp);

					int tempEstadisticas = iEstadisticas[n];
					iEstadisticas[n] = iEstadisticas[n + 1];
					iEstadisticas[n + 1] = tempEstadisticas;
				}
			}
		}

		fclose(fpDicc);
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
	void	ListaCandidatas(
		char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
		int		iNumSugeridas,						//Lista de palabras clonadas
		char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
		int		iEstadisticas[],					//Lista de las frecuencias de las palabras
		int		iNumElementos,						//Numero de elementos en el diccionario
		char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
		int		iPeso[],							//Peso de las palabras en la lista final
		int& iNumLista)							//Numero de elementos en la szListaFinal
	{

		//Sustituya estas lineas por su código
		strcpy(szListaFinal[0], szPalabrasSugeridas[0]); //la palabra candidata
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
		char* szPalabraLeida,						// Palabra a clonar
		char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
		int& iNumSugeridas)						//Numero de elementos en la lista
	{

















		//Sustituya estas lineas por su código
		strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
		iNumSugeridas = 1;							//Una sola palabra sugerida
	}
