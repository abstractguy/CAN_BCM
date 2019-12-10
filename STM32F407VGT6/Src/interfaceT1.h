#ifndef INTERFACET1_H
  #define INTERFACET1_H
  // DESCRIPTION: pour interagir avec un temoin lumineux T1 relie a un STM32F407.
  // Copiez et adaptez ce qui suit dans "main.h".
  // #define INTERFACET1_VALEUR_POUR_ALLUMER  1   
  // #define INTERFACET1_VALEUR_POUR_ETEINDRE 0

  void interfaceT1_allume(void);
  void interfaceT1_eteint(void);
  void interfaceT1_initialise(void);
#endif
