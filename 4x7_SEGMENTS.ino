/*
*******************************************
  DATE : 07/05/2022
  AUTHEUR : RACHEL SYSTÈME

  Ce programme d'afficher une combinaison des digits sur un afficheur
  4x7 segments à anode commune.

  NB : Si vous utilisez un afficheur 4x7 segments à cathode commune,
  modifier la constante : "_anode_commune = false"

*******************************************
*/

//Si différent remplacé par : _anode_commune = false ;
const bool _anode_commune = true;

// Pins attachés aux différents segments
#define _a 2
#define _b 3
#define _c 4
#define _d 5
#define _e 6
#define _f 7
#define _g 8

// Pins attachés aux différents digits
#define _digit_1 9
#define _digit_2 10
#define _digit_3 11
#define _digit_4 12

// Temps d'affiche des digits
#define _ATTENTE 1000

// Tableaux contenant les pins utilisés
const int pin_segment[7]= {_a,_b,_c,_d,_e,_f,_g};
const int pin_digit[4]  = { _digit_1,
                            _digit_2,
                            _digit_3,
                            _digit_4
                          };

// Combinaisons des digits à afficher
const int digit[4][7] = {
  //a,b,c,d,e,f,g
  {1,1,1,1,1,1,0}, //ZERO
  {0,1,1,0,0,0,0}, //ONE
  {1,1,0,1,1,0,1}, //TWO
  {1,1,1,1,0,0,1} //THREE
};

void setup() {
  // Définitions des pins comme sortie 
  for (int i = 0; i < 7; ++i){
    pinMode(pin_segment[i],OUTPUT);

    //Initialisation des pins
    if (_anode_commune)
      digitalWrite(pin_segment[i],HIGH);    
    else
      digitalWrite(pin_segment[i],LOW); 
  }

   for (int i = 0; i < 4; ++i){
    pinMode(pin_digit[i],OUTPUT);
    
    //Initialisation des pins
    if (_anode_commune)
      digitalWrite(pin_digit[i],LOW);    
    else
      digitalWrite(pin_digit[i],HIGH);
  }
}

void loop() {

  affiche(_ATTENTE); // appel à la fonction
  
  // Déclaration de la variable  
  unsigned long depart = millis();

  // Boucle qui affiche les 4 digits en même temps
  while(true){
    affiche(2); // appel à la fonction

    if ((millis()-depart)>_ATTENTE)
      break;
  }
}

/*
  Cette fonction permet d'allumer la combinaison des segments contenue
  dans le tableau "digit".
  Paramètre :
    Type : int
    Nom : attente
    Rôle : définis la durée que les segments seront allumés  
*/
void affiche(int attente){
  if (_anode_commune){
    for (int i = 0; i < 4; ++i){
      digitalWrite(pin_digit[i],HIGH);

      for (int l = 0; l < 7; ++l){
        digitalWrite(pin_segment[l],!digit[i][l]);
      }
      delay(attente);
      digitalWrite(pin_digit[i],LOW);
    }
  }
  else
  {
    for (int i = 0; i < 4; ++i){
      digitalWrite(pin_digit[i],LOW);

      for (int l = 0; l < 7; ++l){
        digitalWrite( pin_segment[l],digit[i][l]);
      }
      delay(attente);
      digitalWrite(pin_digit[i],HIGH);
    }
  }
}
