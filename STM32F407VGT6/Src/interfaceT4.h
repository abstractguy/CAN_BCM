#ifndef INTERFACET4_H
  #define INTERFACET4_H
  //MODULE: interfaceT4
  //DESCRIPTION: pour interagir avec un temoin lumineux T4 relie a un STM32F407. 

  //DEFINITIONS REQUISES PAR LE MODULE:
  //Dependances materielles
  //(copiez et adaptez ce qui suit dans "main.h")
  //#define INTERFACET4_VALEUR_POUR_ALLUMER  1   
  //#define INTERFACET4_VALEUR_POUR_ETEINDRE 0

  //Fonctions publiques:
  void interfaceT4_allume(void);
  void interfaceT4_eteint(void);
  void interfaceT4_initialise(void);
#endif
