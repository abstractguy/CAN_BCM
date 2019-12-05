//processusBoutonConnecte:
//Historique: 
// 2018-10-28, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interfaceT2.h"
#include "interfaceT3.h"
#include "interfaceT4.h"
#include "interfaceB1.h"
#include "processusBoutonConnecte.h"

//Definitions privees
#define PROCESSUSBOUTONCONNECTE_COMPTE_MAXIMAL_POUR_RECEVOIR (\
    (unsigned int)(PROCESSUSBOUTONCONNECTE_TEMPS_MAXIMAL_POUR_RECEVOIR_EN_MS \
    *FREQUENCE_DE_LA_BASE_DE_TEMPS_EN_HZ / 1000.0))

#define INTERFACES0008_RELACHE  0x00
#define INTERFACES0008_APPUYE  0xFF
#define NOMBRE_D_OCTETS_A_TRANSMETTRE 1
#define NOMBRE_D_OCTETS_A_RECEVOIR NOMBRE_D_OCTETS_A_TRANSMETTRE
#define PAS_D_ERREURS 0
#define ERREUR 1
#define ERREUR_AU_NIVEAU_DU_PILOTE 1
#define ERREUR_OCTET_INVALIDE 2

typedef struct {
  unsigned char information;  
  unsigned char statut;
  unsigned char octetsRecus[NOMBRE_D_OCTETS_A_RECEVOIR];
  unsigned char requete;
  unsigned char octetsATransmettre[NOMBRE_D_OCTETS_A_TRANSMETTRE];
} protocole;

//Declarations de fonctions privees:
void processusBoutonConnecte_changeT2(void);
unsigned char processusBoutonConnecte_valideLesDonneesRecues(void);
void processusBoutonConnecte_traiteLesDonneesRecues(void);
void processusBoutonConnecte_attendApresLeBouton(void);
void processusBoutonConnecte_attendUneDemande(void);
void processusBoutonConnecte_attendUneReponse(void);

//Definitions de variables privees:
unsigned char processusBoutonConnecte_etatDeT2;
unsigned char processusBoutonConnecte_compteur;
unsigned char processusBoutonConnecte_octetsRecus[NOMBRE_D_OCTETS_A_RECEVOIR];
unsigned char processusBoutonConnecte_octetsATransmettre[NOMBRE_D_OCTETS_A_TRANSMETTRE];
protocole communication;

//Definitions de fonctions privees:
void processusBoutonConnecte_changeT2(void) {
  if (processusBoutonConnecte_etatDeT2 == 0) {
    processusBoutonConnecte_etatDeT2 = 1;
    interfaceT2_allume();
    return;
  }
  processusBoutonConnecte_etatDeT2 = 0;
  interfaceT2_eteint();  
}

unsigned char processusBoutonConnecte_valideLesDonneesRecues(void) {
  for (unsigned char i = 0; i < NOMBRE_D_OCTETS_A_RECEVOIR; i++) {
    if ((processusBoutonConnecte_octetsRecus[i] & 0xF7) != 0x00) {
      return ERREUR;
    }
  }
  return PAS_D_ERREURS;  
}

void processusBoutonConnecte_traiteLesDonneesRecues(void) { //exemple de traitement qui divise les donnees recues par 2. 
  //Le processus pourrait faire autre chose (exemple: transmettre les donnees par lien CAN)
  for (unsigned char i = 0; i < NOMBRE_D_OCTETS_A_RECEVOIR; i++) {
    processusBoutonConnecte_octetsATransmettre[i] = processusBoutonConnecte_octetsRecus[i];
  }  
}

void processusBoutonConnecte_attendApresLeBouton(void) {
  if (interfaceB1.etatDuModule == MODULE_PAS_EN_FONCTION)
    return;
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
    processusBoutonConnecte_attendUneDemande;
  processusBoutonConnecte_attendUneDemande(); //on sauve une interruption    
}

void processusBoutonConnecte_attendUneDemande(void) {
  if (interfaceB1.information == INFORMATION_TRAITEE)
    return;
  interfaceB1.information = INFORMATION_TRAITEE;
  if (interfaceB1.etatDuBouton == INTERFACEB1_RELACHE)
    return;
  processusBoutonConnecte_compteur = 0;
  interfaceT4_eteint(); //T4 sert a indiquer les erreurs detectees par interfaceS0008
  interfaceT3_eteint(); //T3 sert a indiquer les erreurs detectees par processusBoutonConnecte
  communication.requete = REQUETE_ACTIVE;
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
    processusBoutonConnecte_attendUneReponse;
}

void processusBoutonConnecte_attendUneReponse(void) {
  processusBoutonConnecte_compteur++;
  if (processusBoutonConnecte_compteur ==
      PROCESSUSBOUTONCONNECTE_COMPTE_MAXIMAL_POUR_RECEVOIR) {
    processusBoutonConnecte_compteur = 0;
    interfaceT4_allume();
    serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
        processusBoutonConnecte_attendUneDemande;
    return;
  }
  if (communication.information == INFORMATION_TRAITEE)
    return;
  communication.information = INFORMATION_TRAITEE;
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
    processusBoutonConnecte_attendUneDemande;
 
  processusBoutonConnecte_changeT2();
  if (communication.statut != PAS_D_ERREURS) {
    interfaceT4_allume();
    return;
  }
  if (processusBoutonConnecte_valideLesDonneesRecues() == ERREUR) {
    interfaceT3_allume();
    return;
  }
  processusBoutonConnecte_traiteLesDonneesRecues();
  interfaceT3_eteint();
}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void processusBoutonConnecte_initialise(void) {
  processusBoutonConnecte_compteur = 0;
  processusBoutonConnecte_etatDeT2 = 0;
  interfaceT2_eteint();
  interfaceT3_eteint();
  interfaceT4_eteint();
  for (unsigned char i = 0; i < NOMBRE_D_OCTETS_A_TRANSMETTRE; i++)
    processusBoutonConnecte_octetsATransmettre[i] = i;
  serviceBaseDeTemps_execute[PROCESSUSBOUTONCONNECTE_PHASE] =
      processusBoutonConnecte_attendApresLeBouton;
}