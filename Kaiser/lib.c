#include "commun.h"

/**primitives de files**/

void initfile(void){
	tete = NULL;
	queue = NULL;
}

int filevide(void){
	return tete == NULL;
}

void ajouter(int v){
	t_element* nouv;

	nouv = malloc(sizeof(t_element));
	nouv->nombre = v;
	nouv->suivant = NULL;
	if(filevide())
		tete = nouv;
	else
		queue->suivant = nouv;
	queue = nouv;
}

void retirer(int* v){
	t_element* premier;

	if(!filevide()){
		premier = tete;
		*v = premier->nombre;
		tete = premier->suivant;
		free(premier);
	}
}

/******************************/


int randint(int min, int max){
/**Fonction générant un entier aléatoire entre deux bornes en paramètres**/
	static int first = 0;

	if (first == 0){
		srand (time (NULL));
		first = 1;
	}
	return (rand()%(max - min + 1) + min);
}

int int_len(unsigned x){
/**Fonction qui retourne la taille d un entier**/
    if (x >= 1000000000) return 10;
    if (x >= 100000000)  return 9;
    if (x >= 10000000)   return 8;
    if (x >= 1000000)    return 7;
    if (x >= 100000)     return 6;
    if (x >= 10000)      return 5;
    if (x >= 1000)       return 4;
    if (x >= 100)        return 3;
    if (x >= 10)         return 2;
    return 1;
}
void swap(char *c1, char *c2){
/**Fonction qui echange deux caracteres**/
    char tmp = *c1;
    *c1 = *c2;
    *c2 = tmp;
}
void reverse(char str[], int length){ 
/**Fonction qui inverse les caracteres d une string**/
    int start = 0; 
    int end = length -1; 
    while (start < end) 
    { 
        swap(&(*(str+start)), &(*(str+end))); 
        start++; 
        end--; 
    } 
} 
char* ft_itoa(int num, int base){ 
/**Fonction qui transforme un entier en string**/
    char *str = malloc(sizeof(char) * int_len(num));
    int i = 0; 
    int isNegative = 0; 
  
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    } 
  
    if (num < 0 && base == 10) 
    { 
        isNegative = 1; 
        num = -num; 
    } 
  
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 

    if (isNegative) 
        str[i++] = '-'; 
  
    str[i] = '\0';
  
    reverse(str, i); 
  
    return str; 
}