#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Practica 1 --> Alfabetos y cadenas
//Solo se permiten caracteres alfanuméricos

typedef struct Nodo { 
    char *c;
    struct Nodo *sig;
} Nodo;

int isEmpty( Nodo *node ) {
    return node == NULL;
}

void addElement( Nodo **node, char *c ) {
    
    // Creación del nodo a agregar.
    Nodo *nuevo = malloc( sizeof( Nodo ) );
    nuevo->c = c;
    nuevo->sig = NULL;

    if( (*node) == NULL ) {
        (*node) = nuevo;
    }
    else {
        Nodo *aux = (*node);
        while( aux->sig != NULL ) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }

}

void showCadenas(Nodo *list){

    int i=0;
    if( !isEmpty(list) ){
        Nodo *aux = list;
        printf("\nPalabras en lista:");
        while( aux != NULL ) {
            printf("\n%d.- %s ",i,aux->c);
            aux = aux->sig;
            i++;
        } 
        printf("\n");
    }

    else{
        printf("La lista esta vacia\n");
    }

}

Nodo* searchElement( Nodo **node, char *valueToSearch ) {
    
    Nodo *aux = *node;

    while( aux != NULL ){
        if( strcmp(aux->c,valueToSearch) == 0 )
            return aux;
        
        aux = aux->sig;
    }
    return NULL;
}

int validar(char *c){

    int i = 0;
    for( ; i<strlen(c) ; i++){
        if( (c[i]>0 && c[i]<48) || (c[i]>57 && c[i]<97) || (c[i]>122) || (c[i]<0) )//Fuera del alfabeto alphanumerico
            return 0;
    }
    
    return 1;
}

void getText(char *c){

    while(1){
        printf("\nEscriba un texto: ");
        scanf("%s",c);

        //Validar que las cadenas estén dentro del alfabeto // Idea --> Cod. ASCII
        int x = validar(c);

        if(x)
            return;
        
        printf("La cadena no es valida dentro del alfabeto");
    }
}

void concatenacion( Nodo **list){ //Genera nuevas cadenas

    char c1[50],c2[50],*c3;
    showCadenas(*list);
    printf("Cadenas a concatenar:\n");
    scanf("%s",&c1);
    scanf("%s",&c2);

    if( (strcmp(searchElement(list,&c1)->c,&c1) != 0) || (strcmp(searchElement(list,&c2)->c,&c2) != 0) ){
        printf("\n---Una de las cadenas no se encuestra en el listado---\n");
        return;
    }

    c3 = malloc(strlen(c1) + strlen(c2) + 1);
    if (!c3) {
        printf("Error de asignación de memoria\n");
        return;
    }

    strcpy(c3, c1);
    strcat(c3, c2);

    printf("\nNueva cadena --> %s \n", c3);
    addElement(list, c3);

}

void invertirCadena(char *c1){
    
    int i=0, j= strlen(c1)-1;
    char temp;

    for(; i < j; i++, j--){
        temp = c1[i];
        c1[i] = c1[j];
        c1[j] = temp;
    }
}

void potencia(Nodo **list){ // Genera nuevas cadenas / Potencia positiva y negativa
    //Potencia 0 --> Regresa valor 0

    char c[1000];
    int n;

    printf("Seleccione una cadena");
    showCadenas(*list);
    scanf("%s",c);

    if(strcmp(searchElement(list,&c)->c,&c) != 0)
        return;
    
        printf("Escribir potencia: ");
        scanf("%d", &n);
    
        char *aux = malloc(1); 
        if (!aux) {
            printf("Error de asignación de memoria\n");
            return;
        }
        aux[0] = '\0';
    
        //Casos potencia positiva y negativa
        if (n > 0) {
            for (int i = 0; i < n; i++) {
                aux = realloc(aux, strlen(aux) + strlen(c) + 1);
                if (!aux) {
                    printf("Error de asignación de memoria\n");
                    return;
                }
                strcat(aux, c);
            }
        } else if (n < 0) {
            n = -n; // Convertimos a positivo para calcular la potencia
            for (int i = 0; i < n; i++) {
                aux = realloc(aux, strlen(aux) + strlen(c) + 1);
                if (!aux) {
                    printf("Error de asignación de memoria\n");
                    return;
                }
                strcat(aux, c);
            }
            invertirCadena(aux);
        } else {
            free(aux);
            aux = malloc(2);
            if (!aux) {
                printf("Error de asignación de memoria\n");
                return;
            }
            strcpy(aux, "0");
        }
    
        printf("\n---Cadena nueva: %s---\n", aux);
        addElement(list, aux);

}

void longCadena( Nodo **list ){

    char *c1;
    showCadenas(*list);
    printf("Seleccciona una cadena:\n");
    scanf("%s",&c1);
    if( strcmp(searchElement(list,&c1)->c,&c1) == 0){
        printf("---La longuitud de la cadena %s es de --> %d ---\n\n",&c1,strlen(&c1));
        return;
    }

    printf("No se encontro la cadena :(");

}

void sufijo( Nodo **list ){

    int i,j;
    char c1[1000];
    //c1 = (char*)malloc(sizeof(char));
    showCadenas(*list);
    printf("Seleccciona una cadena:\n");
    scanf("%s",c1);
    
    if( strcmp(searchElement(list,&c1)->c,&c1) != 0)
        return;

    printf("\nSufijos de la cadena: %s\n",c1);

    for(i=0 ; i<strlen(c1) ; i++){
        for(j=i ; j<strlen(c1) ; j++)
            printf("%c",c1[j]);
        
        printf("\n");
    }    

    //free(c1);
}

void prefijo( Nodo **list ){

    int i,j;
    char c1[1000];
    //c1 = (char*)malloc(sizeof(char));
    showCadenas(*list);
    printf("Seleccciona una cadena:\n");
    scanf("%s",c1);
    
    if( strcmp(searchElement(list,&c1)->c,&c1) != 0)
        return;

    printf("\nPrefijos de la cadena: %s\n",c1);

    for(i=0 ; i<strlen(c1) ; i++){
        for(j=0 ; j<strlen(c1)-i ; j++)
            printf("%c",c1[j]);
        
        printf("\n");
    }    

    //free(c1);
    
}

void subCadena(Nodo **list){

    char c1[100];
    int i,j,k;
    //c1 = (char*)malloc(sizeof(char));
    showCadenas(*list);
    printf("Seleccciona una cadena:\n");
    scanf("%s",c1);
    
    if( strcmp(searchElement(list,&c1)->c,&c1) != 0)
        return;

    printf("\nSubcadenas de la cadena: %s\n",c1);

    printf("%s\n",c1);
    
    //prefijos
    for(i=1 ; i<strlen(c1) ; i++){
        for(j=0 ; j<strlen(c1)-i ; j++)
            printf("%c",c1[j]);
        
        printf("\n");
    }

    //sufijos
    for(i=1 ; i<strlen(c1) ; i++){
        for(j=i ; j<strlen(c1) ; j++)
            printf("%c",c1[j]);
        
        printf("\n");
    }

    //resto
    for(i=1 ; i<strlen(c1) ; i++){
        for(j=i ; j<strlen(c1)-i ; j++)
            printf("%c",c1[j]);
        
        printf("\n");
    }
        
}

void liberarMemoria( Nodo **list ) {
    while( (*list) != NULL ) {
        Nodo *aux = *list;
        *list = (*list)->sig;
        free( aux );
    }
}

int main(){

    //Entrada = 2 cadenas
    char c1[50], c2[50];
    Nodo *words = NULL;
    printf("-------------------------");
    getText(c1);
    printf("-------------------------");
    getText(c2);
    printf("-------------------------");

    addElement(&words,c1);
    addElement(&words,c2);

    showCadenas(words);

    int rept=1;
    int opt;

    while(rept){

        //Operaciones de cadenas
        printf("\nSelecione una de las siguientes operaciones: ");
        printf("\n1. Concatenacion\n2. Potencia\n3. Mostrar sufijos\n4. Mostrar prefijos\n5. Mostrar subcadenas\n6. Longitud de una cadena\n0. Salir\n--> ");

        scanf("%d",&opt);

        switch( opt ){

        case 0:
            rept = 0;
            break;

        case 1:
            printf("----Concatenacion----\n");//Done
            concatenacion(&words);
            break;
        
        case 2:
            printf("----Potencia----\n");
            potencia(&words);
            break;

        case 3:
            printf("----Sufijo----\n");//Done
            sufijo(&words);
            break;

        case 4:
            printf("----Prefijos----\n");//Done
            prefijo(&words);
            break;

        case 5:
            printf("----Subcadenas----\n");//Done
            subCadena(&words);
            break;

        case 6:
            printf("----Longitud cadena----\n");//Done
            longCadena(&words);
            break;
        
        default:
            break;
        }

    }

    liberarMemoria(&words);

}