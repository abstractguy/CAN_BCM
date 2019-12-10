#ifndef INTERFACET2_H
  #define INTERFACET2_H
  // DESCRIPTION: pour interagir avec un temoin lumineux T2 relie a un STM32F407.
  // Copiez et adaptez ce qui suit dans "main.h".
  // #define INTERFACET2_VALEUR_POUR_ALLUMER  1   
  // #define INTERFACET2_VALEUR_POUR_ETEINDRE 0

  void interfaceT2_allume(void);
  void interfaceT2_eteint(void);
  void interfaceT2_initialise(void);
#endif
