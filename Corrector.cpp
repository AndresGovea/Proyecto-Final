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
#define DEPURAR 3
#define ABECEDARIO 32
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
	char linea[850000];
	char pDetectada[TAMTOKEN], referencia[NUMPALABRAS][TAMTOKEN];
	int i, iPalabra = 0, espacio, n, k, j;
	iNumElementos = 0;
	// abrir el achivo

	fopen_s(&fpDicc, szNombre, "r");
	if (fpDicc != NULL)
	{

		while (!feof(fpDicc))
		{
			fgets(linea, sizeof(linea), fpDicc);

			for (i = 0; i < strlen(linea); i++)
			{

				if (linea[i] == ' ' || linea[i] == '\t' || linea[i] == '\n' || linea[i] == '\r' || linea[i] == '\0')
				{
					if (!espacio && iPalabra > 0) {
						pDetectada[iPalabra] = '\0';
						_strlwr_s(pDetectada, TAMTOKEN);
						strcpy_s(referencia[iNumElementos], TAMTOKEN, pDetectada);

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
					if (linea[i] != '(' && linea[i] != ')' && linea[i] != ',' && linea[i] != '.' && linea[i] != ';' && linea[i] != '_' && linea[i] != '¿' && linea[i] != '?' && linea[i] != '¡' && linea[i] != ':' && linea[i] != '{' && linea[i] != '}' && linea[i] != '<' && linea[i] != '>' && linea[i] != '[' && linea[i] != ']' && linea[i] != '~' && linea[i] != '´' && linea[i] != '|' && linea[i] != '´')
					{
						pDetectada[iPalabra] = linea[i];
						iPalabra++;
					}
					espacio = 0;
				}

			}
			if (iPalabra > 0) {
				pDetectada[iPalabra] = '\0';
				_strlwr_s(pDetectada, TAMTOKEN);
				strcpy_s(referencia[iNumElementos], TAMTOKEN, pDetectada);
				if (DEPURAR == 7)
				{
					printf("Palabra detectada: %s\n", pDetectada);
				}
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
				if (DEPURAR == 7)
				{
					printf("Recuento de '%s': %d\n", pDetectada, iEstadisticas[j]);
				}
				iPalabra = 0;
			}

		}

		for (k = 0; k < iNumElementos - 1; k++)
		{
			for (n = 0; n < iNumElementos - k - 1; n++)
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
		strcpy_s(szListaFinal[0],TAMTOKEN, szPalabrasSugeridas[0]); //la palabra candidata
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

		char abecedario[32] = { 'a', 'b', 'c', 'd','e','f','g','h','i','j','k','l','m','n','ñ','o','p','q','r','s','t','u', 'v','w','x','y','z', 'á', 'é', 'í', 'ó', 'ú' };
		int longitud, a, u, w, l, j, q;
		char ayuda[TAMTOKEN], otraAyuda[TAMTOKEN];
		int contador;
		char aux[TAMTOKEN];
		char candidatas[3300][TAMTOKEN];
		int iSugeridas = 0;

		longitud = strlen(szPalabraLeida);


		strcpy_s(ayuda, TAMTOKEN, szPalabraLeida);
		strcpy_s(otraAyuda, TAMTOKEN, szPalabraLeida);
		strcpy_s(aux, TAMTOKEN, szPalabraLeida);
		//Eliminación de caracteres
		for (contador = 0; contador < longitud; contador++)
		{
			int e = 0;
			for (a = 0; a < longitud; a++)
			{
				if (a != contador)
				{
					szPalabraLeida[e] = ayuda[a];
					e++;
				}
			}
			szPalabraLeida[e] = '\0'; // Asegúrate de terminar la cadena correctamente

			if (DEPURAR == 0)
			{
				printf("\n%s", szPalabraLeida);
			}

			strcpy_s(candidatas[iSugeridas], TAMTOKEN, szPalabraLeida); // Guarda la versión actual de la palabra
			iSugeridas++;
		}


		for (u = 0; u < longitud; u += 2)
		{
			if (u + 1 < longitud)
			{
				char noPMT = otraAyuda[u];
				otraAyuda[u] = otraAyuda[u + 1];
				otraAyuda[u + 1] = noPMT;
			}
			strcpy_s(candidatas[iSugeridas],TAMTOKEN, otraAyuda);
			iSugeridas++;
			if (DEPURAR == 0)
			{
				printf("\n%s", otraAyuda);
			}
		}

		for (contador = 0; contador < longitud; contador++)
		{
			for (w = 0; w < ABECEDARIO; w++)
			{
				szPalabraLeida[contador] = abecedario[w];
				if (DEPURAR == 0)
				{
					printf("\n%s", szPalabraLeida);
				}
			}

			strcpy_s(candidatas[iSugeridas],TAMTOKEN, szPalabraLeida);
			iSugeridas++;
			strcpy_s(szPalabraLeida, TAMTOKEN, ayuda);
		}
		for (contador = 0; contador <= longitud; contador++)
		{
			for (q = 0; q < ABECEDARIO; q++)
			{
				// Inserta la letra del abecedario en la posición contador
				for (j = longitud; j >= contador; j--) {
					szPalabraLeida[j + 1] = szPalabraLeida[j];
				}
				szPalabraLeida[contador] = abecedario[q];
				if (DEPURAR == 0)
				{
					printf("\n%s", szPalabraLeida);
				}
				strcpy_s(candidatas[iSugeridas], TAMTOKEN, szPalabraLeida);
				iSugeridas++;
				strcpy_s(szPalabraLeida, TAMTOKEN, ayuda);
			}
		}
	

				iNumSugeridas = iSugeridas;
				l = 0;
			while (l < iSugeridas)
			{
				strcpy_s(szPalabrasSugeridas[l],TAMTOKEN, candidatas[l]);
				l++;
			}
		

	}
