// interfaceT2:
#include "main.h"
#include "piloteIOT2.h"
#include "interfaceT2.h"

void interfaceT2_allume(void) {
  piloteIOT2_metLaSortieA(INTERFACET2_VALEUR_POUR_ALLUMER);
}

void interfaceT2_eteint(void) {
  piloteIOT2_metLaSortieA(INTERFACET2_VALEUR_POUR_ETEINDRE);
}

void interfaceT2_initialise(void) {
  piloteIOT2_metLaSortieA(INTERFACET2_VALEUR_POUR_ETEINDRE);
}
