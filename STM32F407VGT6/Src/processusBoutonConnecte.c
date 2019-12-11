// processusBoutonConnecte:
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfaceT1.h"
#include "interfaceT2.h"
#include "interfaceT3.h"
#include "interfaceT4.h"
#include "processusBoutonConnecte.h"

#define PROCESSUSBOUTONCONNECTE_COMPTE_MAXIMAL_POUR_RECEVOIR (\
    (unsigned int)(PROCESSUSBOUTONCONNECTE_TEMPS_MAXIMAL_POUR_RECEVOIR_EN_MS \
    * FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ / 1000.0))

#define NOMBRE_D_OCTETS_A_TRANSMETTRE 1
#define NOMBRE_D_OCTETS_A_RECEVOIR NOMBRE_D_OCTETS_A_TRANSMETTRE
#define PAS_D_ERREUR 0
#define ERREUR 1

typedef struct {
  unsigned char information;  
  unsigned char statut;
  unsigned char octetsRecus[NOMBRE_D_OCTETS_A_RECEVOIR];
  unsigned char octetsATransmettre[NOMBRE_D_OCTETS_A_TRANSMETTRE];
} protocole;

unsigned char processusBoutonConnecte_valideLesDonneesRecues(void);
void processusBoutonConnecte_traiteLesDonneesRecues(void);
void processusBoutonConnecte_attendUneReponse(void);

unsigned char processusBoutonConnecte_compteur;
unsigned char processusBoutonConnecte_octetsRecus[NOMBRE_D_OCTETS_A_RECEVOIR];
unsigned char processusBoutonConnecte_octetsATransmettre[NOMBRE_D_OCTETS_A_TRANSMETTRE];
protocole communication;

unsigned char processusBoutonConnecte_valideLesDonneesRecues(void) {
  if ((processusBoutonConnecte_octetsRecus[0] & 0xFC) != 0x00) {
    return ERREUR;
  }
  
  return PAS_D_ERREUR;  
}

void processusBoutonConnecte_traiteLesDonneesRecues(void) {
  for (unsigned char i = 0; i < NOMBRE_D_OCTETS_A_RECEVOIR; i++) {
    processusBoutonConnecte_octetsATransmettre[i] = processusBoutonConnecte_octetsRecus[i];
  }  
}

void processusBoutonConnecte_attendUneReponse(void) {
  if (++processusBoutonConnecte_compteur ==
      PROCESSUSBOUTONCONNECTE_COMPTE_MAXIMAL_POUR_RECEVOIR) {
    
    processusBoutonConnecte_compteur = 0;
    
    serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
        processusBoutonConnecte_attendUneReponse;
    
    return;
  }
  
  if (communication.information == INFORMATION_TRAITEE)
    return;
  
  communication.information = INFORMATION_TRAITEE;
  
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
    processusBoutonConnecte_attendUneReponse;
 
  if (communication.statut != PAS_D_ERREUR)
    return;
  
  if (processusBoutonConnecte_valideLesDonneesRecues() == ERREUR) {
    interfaceT3_allume();
    return;
  }
  
  processusBoutonConnecte_traiteLesDonneesRecues();
}

void processusBoutonConnecte_initialise(void) {
  processusBoutonConnecte_compteur = 0;
  
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
      processusBoutonConnecte_attendUneReponse;
}