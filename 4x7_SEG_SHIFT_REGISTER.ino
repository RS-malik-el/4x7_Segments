/*
*******************************************
  DATE : 10/05/2022
  AUTHEUR : RACHEL SYSTÈME

  Ce programme d'afficher une combinaison des lettres sur un afficheur
  4x7 segments à anode commune en utilisant le registre à décalage 74HC595.

  NB : Si vous utilisez un afficheur 4x7 segments à cathode commune,
  modifier la constante : "_anode_commune = false"

*******************************************
*/

//Si différent remplacé par : _anode_commune = false ;
const bool _anode_commune = true;

#define PIN_DATA  		6
#define REGISTER_CLOCK  5
#define SERIAL_CLOCK  	4

// Pins attachés aux différents digits
#define _digit_1 12
#define _digit_2 11
#define _digit_3 10
#define _digit_4 9

// Temps d'affiche des digits
#define _ATTENTE 1000

// Tableaux contenant les pins des digits
const int pin_digit[4]  = { _digit_1,
                            _digit_2,
                            _digit_3,
                            _digit_4
                          };
 
// Combinaisons à afficher
const int combinaison[4][8] = {
  //a,b,c,d,e,f,g,dp
  {1,1,1,0,1,1,1,0}, // A
  {0,0,0,1,1,1,0,0}, // L
  {0,0,0,1,1,1,0,0}, // L
  {1,1,1,1,1,1,0,0}  // O
};

 void setup(){
	// Définition des pins comme sortie
	pinMode(PIN_DATA,OUTPUT);
	pinMode(REGISTER_CLOCK,OUTPUT);
	pinMode(SERIAL_CLOCK,OUTPUT);

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
  dans le tableau "combinaison".
  Paramètre :
    Type : int
    Nom : attente
    Rôle : définis la durée que les segments seront allumés  
*/
void affiche(int attente){
	if (_anode_commune){
		for (int l = 0; l < 4; ++l){
			// Préparation du registre à recevoir les données
			digitalWrite(REGISTER_CLOCK,LOW);
				// Ecriture des données
				for (int i = 7; i >= 0; --i){
					digitalWrite(SERIAL_CLOCK,LOW);
					digitalWrite(PIN_DATA,!combinaison[l][i]); // donnée à envoyer
					digitalWrite(SERIAL_CLOCK,HIGH);
				}
			// Mise à jour des sorties du registre
			digitalWrite(REGISTER_CLOCK,HIGH);

			digitalWrite(pin_digit[l],HIGH);
			delay(attente);
			digitalWrite(pin_digit[l],LOW);
		}
	}
	else{
		for (int l = 0; l < 4; ++l){
			// Préparation du registre à recevoir les données
			digitalWrite(REGISTER_CLOCK,LOW);
				// Ecriture des données
				for (int i = 7; i >= 0; --i){
					digitalWrite(SERIAL_CLOCK,LOW);
					digitalWrite(PIN_DATA,combinaison[l][i]); // donnée à envoyer
					digitalWrite(SERIAL_CLOCK,HIGH);
				}
			// Mise à jour des sorties du registre
			digitalWrite(REGISTER_CLOCK,HIGH);

			digitalWrite(pin_digit[l],LOW);
			delay(attente);
			digitalWrite(pin_digit[l],HIGH);
		}	
	}
}