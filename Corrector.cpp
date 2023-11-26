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
#define DEPURAR 7
#define ABECEDARIO 32

void ordenamiento(char palabra[][TAMTOKEN], int iEstadisticas[], int elementos) 
{
	int anterior, inicio;
	char aux[TAMTOKEN];
	int ayudaEx;
	bool permuta;

	for (anterior = 0; anterior < elementos - 1; anterior++)
	{
		permuta = false;

		for (inicio = 0; inicio < elementos - anterior - 1; inicio++)
		{
			if (strcmp(palabra[inicio], palabra[inicio + 1]) > 0) 
			{

				strcpy_s(aux, palabra[inicio]);
				strcpy_s(palabra[inicio], TAMTOKEN,palabra[inicio + 1]);
				strcpy_s(palabra[inicio + 1],TAMTOKEN, aux);

				ayudaEx = iEstadisticas[inicio];
				iEstadisticas[inicio] = iEstadisticas[inicio + 1];
				iEstadisticas[inicio + 1] = ayudaEx;
				permuta = true;
			}
		}

		if (!permuta) 
		{
			break;
		}
	}
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
	FILE* fpDicc;
	char linea[NUMPALABRAS];
	char pDetectada[TAMTOKEN];
	int i, iPalabra = 0, j, archivo, tempEstadisticas;
	char temp[TAMTOKEN];
	iNumElementos = 0;
	
	fopen_s(&fpDicc, szNombre, "r");
	if (fpDicc != NULL)
	{
		while (!feof(fpDicc))
		{
			fgets(linea, sizeof(linea), fpDicc);
			archivo = strlen(linea);
			for (i = 0; i < archivo; i++)
			{
				//Eliminamos caracteres no desados 
				if (linea[i] != '(' && linea[i] != ')' && linea[i] != ',' && linea[i] != '.'
					&& linea[i] != ';' && linea[i] != '¡' && linea[i] != '*' && linea[i] != '{'
					&& linea[i] != '}' && linea[i] != '<' && linea[i] != '>' && linea[i] != ' '
					&& linea[i] != '\n')
				{
					pDetectada[iPalabra] = linea[i];
					iPalabra++;
				}

				else if (iPalabra > 0)
				{
					pDetectada[iPalabra] = '\0';
					_strlwr_s(pDetectada, TAMTOKEN);
					strcpy_s(szPalabras[iNumElementos], TAMTOKEN, pDetectada);

					for (j = 0; j < iNumElementos; j++)
					{
						if (strcmp(szPalabras[j], pDetectada) == 0)
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
			}
		}
		ordenamiento(szPalabras, iEstadisticas, iNumElementos);
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
		strcpy_s(szListaFinal[0], TAMTOKEN, szPalabrasSugeridas[0]); //la palabra candidata
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
		int longitud, i, j;
		char ayuda[TAMTOKEN], otraAyuda[TAMTOKEN];
		int contador;
		char aux[TAMTOKEN];
		char candidatas[3300][TAMTOKEN];
		int iSugeridas = 0;

		longitud = strlen(szPalabraLeida);

		strcpy_s(ayuda, TAMTOKEN, szPalabraLeida);
		strcpy_s(otraAyuda, TAMTOKEN, szPalabraLeida);
		strcpy_s(aux, TAMTOKEN, szPalabraLeida);

		strcpy_s(candidatas[iSugeridas], TAMTOKEN, szPalabraLeida);
		iSugeridas++;
		//Eliminación de caracteres
		for (contador = 0; contador < longitud; contador++)
		{
			int e = 0;
			for (i = 0; i < longitud; i++)
			{
				if (i != contador)
				{
					szPalabraLeida[e] = ayuda[i];
					e++;
				}
			}
			szPalabraLeida[e] = '\0';

			strcpy_s(candidatas[iSugeridas], TAMTOKEN, szPalabraLeida);
			iSugeridas++;
		}

		//transposición 
		for (i = 0; i < longitud; i += 2)
		{
			if (i + 1 < longitud)
			{
				char noPMT = otraAyuda[i];
				otraAyuda[i] = otraAyuda[i + 1];
				otraAyuda[i + 1] = noPMT;
			}
			strcpy_s(candidatas[iSugeridas], TAMTOKEN, otraAyuda);
			iSugeridas++;

		}

		for (i = 0; i < longitud; i++)
		{  // Para cada caracter en 'palabraOriginal'...
			for (int j = 0; j < 32; j++) {  // ...prueba reemplazándolo con cada caracter en 'abecedario'
				aux[i] = abecedario[j];
				strcpy_s(candidatas[iSugeridas], TAMTOKEN, aux);
				iSugeridas++;
			}
			aux[i] = szPalabraLeida[i];  // Restaura el caracter original antes de pasar al siguiente
		}


		for (contador = 0; contador <= longitud; contador++)
		{
			for (i = 0; i < ABECEDARIO; i++)
			{
				// Inserta la letra del abecedario en la posición contador
				for (j = longitud; j >= contador; j--) {
					szPalabraLeida[j + 1] = szPalabraLeida[j];
				}
				szPalabraLeida[contador] = abecedario[i];

				strcpy_s(candidatas[iSugeridas], TAMTOKEN, szPalabraLeida);
				iSugeridas++;
				strcpy_s(szPalabraLeida, TAMTOKEN, ayuda);
			}
		}

		iNumSugeridas = iSugeridas;
		i = 0;
		while (i < iSugeridas)
		{
			strcpy_s(szPalabrasSugeridas[i], TAMTOKEN, candidatas[i]);
			i++;
		}
	}

