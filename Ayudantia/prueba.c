    
#include<stdio.h>

/* Fijense que podemos hasta reemplazar librerias pero cuidado con el orden,
hasta aqui no estaba definido CHAO, sin embargo, posteriormente si se hace 
la referencia
*/

/* Aqui no estaria definido*/ 
#if defined(CHAO)
#include<math.h>
#endif

#define HOLA 0
#define CHAO 1

/* Aqui si lo esta!!!*/
#if defined(CHAO)
#include<math.h>
#include<stdint.h>
#endif


int main()
{

    printf("\n\nCodigo para entender un poquito el preprocessador\n\n");

#ifdef HOLA
    printf("\nEsta parte del codigo no sera filtrada por el preprocessador\n");
#else
    printf("Esto no se imprimira, recordemos lo que pasa aqui\n");
#endif

    /* Podemos usar los define tambien para reemplazar codigo 
    y tambien podemos dejar en la linea de abajo codigo largo si es
    la linea anterior termina con una coma...
    */ 
    printf("\nEl valor de HOLA es %d\nMientras que CHAO es %d\n", 
        (int*)HOLA, (uint8_t)CHAO);

    if(HOLA || CHAO)
    {
        printf("\nFormato Linux para condicionales\n");
    }
    if(CHAO > 0){
        printf("\nFormato GNU para condicionales\n\n");
    }


    return 0;

}