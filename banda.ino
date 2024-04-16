int SW1 = 37;
int SW2 = 36;
int SW3 = 35;
int SW4 = 34;
int right = 22;
int left = 23;
int S1 = 30;
int S2 = 31;
int S3 = 32;
int S4 = 33;
bool moving = false;
unsigned long start = 0;
unsigned long end = 0;
unsigned long time = 0;
int counter = 0;
bool visited = false;
bool showed = false;

int move(int *start_move, int *end_move, int *dir1, int *dir2){
  while(digitalRead(*end_move) == 0 && digitalRead(SW2) == 0 && visited == false){
    digitalWrite(*dir1, 1);
  }
  if (digitalRead(*end_move)){
    digitalWrite(*dir1, 0);
    visited = true;
  } else {
    digitalWrite(*dir1, 0);
  }

  while(digitalRead(*start_move) == 0 && digitalRead(SW2) == 0 && visited == true){
    digitalWrite(*dir2, 1);
  } 
  if(digitalRead(*start_move)){
    visited = false;
    counter = counter + 1;
    digitalWrite(*dir2, 0);
  } else{
    digitalWrite(*dir2, 0);
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
  Serial.begin(9600);
}



void loop() {
  // put your main code here, to run repeatedly:
  
  if(digitalRead(SW1)){
    int value_1 = digitalRead(SW3);
    int value_2 = digitalRead(SW4);
    /*Infinitas veces ebtre S1 y S3*/
    if(value_1 == 0 && value_2 == 0){
      while(true){
        move(&S1, &S3, &left, &right);
        Serial.println("Fin");
      }
    }
    if(value_1 == 0 && value_2 == 1) {
        while(counter < 3){
          move(&S2, &S3, &left, &right);
        }       
    }
    if(value_1 == 1 && value_2 == 0){
      if(digitalRead(S1)){
        if(showed == false){
          start = millis();
        }
        while(counter < 1){
          move(&S1, &S2, &left, &right);
        }
        if(showed == false){
          end = millis();
          time = end - start;
          Serial.println(time);
          showed = true;
        }
      }
      if(digitalRead(S3)){
        if(showed == false){
          start = millis();
        }
        while(counter < 1){
          move(&S3, &S2, &right, &left);
        }
        if(showed == false){
          end = millis();
          time = end - start;
          Serial.println(time);
          showed = true;
        }
      }
      if(digitalRead(S4)){
        if(showed == false){
          start = millis();
        }
        while(counter < 1){
          move(&S4, &S2, &right, &left);
        }
        if(showed == false){
          end = millis();
          time = end - start;
          Serial.println(time);
          showed = true;
        }
      }
    }

    if(value_1 == 1 && value_2 == 1){
      Serial.println("Error");
    }
  }
}
