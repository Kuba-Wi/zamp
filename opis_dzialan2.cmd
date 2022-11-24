#define ROTATE_SPEED     30
/*
 *  Przykładowy zestaw poleceń
 */
  Set   Ob_A 2 0 30    // Polozenie obiektu A 
  Set   Ob_B 10 10 0   // Polozenie obiektu B
  Rotate Ob_B ROTATE_SPEED 40
  Pause 1000 /* Zawieszenie na 1 sek. */
  Move  Podstawa  10 8
  Rotate Ob_B ROTATE_SPEED 60 /* Rotate i Move wykonywane razem */
  Move  Podstawa 10 1            /* powoduja jazde po luku         */
