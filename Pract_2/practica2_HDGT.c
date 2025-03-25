#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int h=3;
int w=100;

const int MAX = 4;

typedef struct Nodo { 
    char *c;
    struct Nodo *sig;
} Nodo;

int isEmpty( Nodo *node ) {
    return node == NULL;
}

void showCadenas(Nodo *list){

    int i=0;
    if( !isEmpty(list) ){
        Nodo *aux = list;
        //printf("\nPalabras en lista:");
        while( aux != NULL ) {
            printf("\n%s ",aux->c);
            aux = aux->sig;
            i++;
        } 
        printf("\n");
    }

    else{
        printf("La lista esta vacia\n");
    }

}

Nodo* getFile(const char* filename) {
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error al abrir el archivo: %s\n", filename);
        exit(1);
    }

    Nodo *aux = NULL;
    char word[100];

    while (fscanf(file, "%s", word) != EOF) {

        Nodo *newNode = (Nodo*)malloc(sizeof(Nodo));
        newNode->c = strdup(word);
        newNode->sig = NULL;

        if(aux == NULL){
            aux = newNode;
        }
        else{
            Nodo *temp = aux;
            while(temp->sig != NULL){
                temp = temp->sig;
            }
            temp->sig = newNode;
        }

    }


    showCadenas(aux);

    fclose(file);
    return aux;
}

//Union
int existsInResult(Nodo *list, const char *word) {
    while (list != NULL) {
        if (strcmp(list->c, word) == 0) {
            return 1;
        }
        list = list->sig;
    }
    return 0;
}

void join(Nodo *n1, Nodo *n2){

    Nodo *temp1 = n1;
    Nodo *temp2 = n2;

    // Add unique words from n2 to n1
    while (temp2 != NULL) {
        if (!existsInResult(n1, temp2->c)) {
            Nodo *last = n1;
            while (last->sig != NULL) {
                last = last->sig;
            }
            last->sig = temp2;
            Nodo *next = temp2->sig;
            temp2->sig = NULL;
            temp2 = next;
        } else {
            Nodo *next = temp2->sig;
            temp2 = next;
        }
    }

    showCadenas(n1);

}

//Concatenacion
Nodo* concatenate(Nodo *n1, Nodo *n2) {

    Nodo *result = NULL;
    Nodo *temp1 = n1;

    while (temp1 != NULL) {
        Nodo *temp2 = n2;
        while (temp2 != NULL) {

            //printf("%s%s\n", temp1->c, temp2->c);

            
            Nodo *newNode = (Nodo*)malloc(sizeof(Nodo));
            char *concatenatedWord = (char*)malloc(strlen(temp1->c) + strlen(temp2->c) + 1);

            strcpy(concatenatedWord, temp1->c);
            strcat(concatenatedWord, temp2->c);
            
            //Nuevo nodo
            newNode->c = concatenatedWord;
            newNode->sig = NULL;

            if (result == NULL) {
                result = newNode;
            }
            
            else {
                Nodo *aux = result;
                while( aux->sig != NULL ) {
                    aux = aux->sig;
                }
                aux->sig = newNode;
            }

            temp2 = temp2->sig;
        }
        temp1 = temp1->sig;
    }

    return result;
}

void concatenateShow(Nodo *n1, Nodo *n2) {

    Nodo *temp1 = n1;

    while (temp1 != NULL) {
        Nodo *temp2 = n2;
        while (temp2 != NULL) {

            printf("%s%s\n", temp1->c, temp2->c);

            temp2 = temp2->sig;
        }
        temp1 = temp1->sig;
    }
}

//Potencia
void potencia(Nodo *n, int pot){

    Nodo *aux = n;

    for(int i=0; i<pot-1; i++){
        aux = concatenate(n,aux);
    }

    showCadenas(aux);

}

void cerraduraKleene(Nodo *n){

    for(int i=1; i<MAX; i++){
        potencia(n,i);
    }

}

void cerraduraPositiva(Nodo*n){

    printf("0\n");
    cerraduraKleene(n);

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

void reflexion(Nodo *n){
        
        Nodo *current = n;

        while (current != NULL) {
            char *temp = strdup(current->c);
            invertirCadena(temp);

            printf("%s\n", temp);
            
            free(temp);
            current = current->sig;
        }
    
}

int main(){

    int rept=1;
    int opt;
    int choose[2];

    Nodo *words[3];
    const char *filename[3] = {"arch1.txt","arch2.txt","arch3.txt"};

    for(int i=0; i<3; i++){
        words[i] = NULL;
    }

    for(int i=0; i<3; i++){
        printf("%s",filename[i]);
        words[i] = getFile(filename[i]);

    }

    while(rept){

       //Operaciones de cadenas
        printf("\n------Selecione una de las siguientes operaciones------\n");
        printf("\n1. Union\n2. Concatenacion\n3. Cerradura de Kleene\n4. Cerradura Positiva\n5. Potencia\n6. Reflexion\n0. Salir\n--> ");

        scanf("%d",&opt);

        switch( opt ){

        case 1:
            printf("----Union----\n");
            
            printf("Selecciona dos lenguajes:\n");

            scanf("%d %d",&choose[0],&choose[1]);
            join( words[choose[0]-1],words[choose[1]-1] );

            break;

        case 2:
            printf("----Concatenacion----\n");

            printf("Selecciona dos lenguajes:\n");
            scanf("%d %d",&choose[0],&choose[1]);

            printf("Concatenacion de los lenguajes %d y %d:\n",choose[0],choose[1]);

            concatenateShow( words[choose[0]-1],words[choose[1]-1] );

            break;
        
        case 3:
            printf("----Cerradura de Kleene----\n");

            printf("Selecciona un lenguaje:\n");
            scanf("%d",&choose[0]);

            cerraduraKleene( words[choose[0]-1] );

            break;

        case 4:
            printf("----Cerradura Positiva----\n");

            printf("Selecciona un lenguaje:\n");
            scanf("%d",&choose[0]);

            cerraduraPositiva( words[choose[0]-1] );
            break;

        case 5:
            printf("----Potencia----\n");

            printf("Selecciona un lenguaje:\n");
            scanf("%d",&choose[0]);

            printf("Escribir potencia: ");
            scanf("%d", &choose[1]);

            potencia( words[choose[0]-1],choose[1] );

            break;

        case 6:
            printf("----Reflexion----\n");

            printf("Selecciona un lenguaje:\n");
            scanf("%d",&choose[0]);

            reflexion( words[choose[0]-1] );

            break;

        case 0:
            rept = 0;
            break;

        default:
            printf("Opcion no valida\n");
            break;
        }
    }

    return 0;

}