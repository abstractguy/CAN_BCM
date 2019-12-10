//interfaceT3:
#include "main.h"
#include "piloteIOT3.h"
#include "interfaceT3.h"

//Definitions de fonctions publiques:
void interfaceT3_allume(void) {
  piloteIOT3_metLaSortieA(INTERFACET3_VALEUR_POUR_ALLUMER);
}

void interfaceT3_eteint(void) {
  piloteIOT3_metLaSortieA(INTERFACET3_VALEUR_POUR_ETEINDRE);
}

void interfaceT3_initialise(void) {
  piloteIOT3_metLaSortieA(INTERFACET3_VALEUR_POUR_ETEINDRE);
}
