int SER_Pin = 11;   //pin 14 on the 75HC595 data
int RCLK_Pin = 10;  //pin 12 on the 75HC595 latch
int SRCLK_Pin = 13; //pin 11 on the 75HC595 clock

//How many of the shift registers - change this
#define number_of_74hc595s 8

#define t1 2
#define t2 3
#define t3 4
#define t4 5
#define t5 6
#define t6 7
#define t7 8
#define t8 9

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];

void setup(){
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  pinMode(t1, OUTPUT);
  pinMode(t2, OUTPUT);
  pinMode(t3, OUTPUT);
  pinMode(t4, OUTPUT);
  pinMode(t5, OUTPUT);
  pinMode(t6, OUTPUT);
  pinMode(t7, OUTPUT);
  pinMode(t8, OUTPUT);
  Serial.begin(9600);  
  //reset all register pins
  clearRegisters();
  writeRegisters();
}               


//set all register pins to LOW
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     registers[i] = LOW;
  }
} 

//set all register pins to LOW
void lightAllRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     registers[i] = HIGH;
  }
}

void clearLayers(){
  for(int i = 2; i < 10; i++){
     digitalWrite(i, LOW);
  }
}


//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters(){

  digitalWrite(RCLK_Pin, LOW);

  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);

    int val = registers[i];

    digitalWrite(SER_Pin, val);
    digitalWrite(SRCLK_Pin, HIGH);

  }
  digitalWrite(RCLK_Pin, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
}

/*60
10
3 -t3,t4
7 - t1
27 -t6
30 - t7*/

void loop(){
  CubeCubing(6, 5, 36, 35, 28, 27);
  delay(300);
  clearRegisters();
  writeRegisters();
  delay(100); 
  clearLayers(); 
}

void CubeCubing(int topLayer, int botLayer,int supEsq, int supDir, int infEsq, int infDir){
    
  if(supEsq < 64){
    digitalWrite(topLayer,HIGH); 
    digitalWrite(botLayer,HIGH);
    setRegisterPin(supDir,HIGH);
    setRegisterPin(supEsq,HIGH);
    setRegisterPin(infDir,HIGH);
    setRegisterPin(infEsq,HIGH);   
    writeRegisters();
    
    for(int i = infDir; i < infEsq; i++){
      setRegisterPin(i,HIGH);  
    }

    for(int i = infEsq; i < supEsq;){
      setRegisterPin(i,HIGH);
      i = i + 8;       
    }

    for(int i = supDir; i < supEsq; i++){
      setRegisterPin(i,HIGH);  
    }

    for(int i = infDir; i < supDir;){
      setRegisterPin(i,HIGH);
      i = i + 8;       
    }

    writeRegisters();         
    delay(500);
    CubeCubing(topLayer + 1, botLayer - 1, supEsq + 9, supDir + 7, infEsq - 7, infDir - 9);     
  }
}

void Around(){
  digitalWrite(t1,HIGH);
   
  for(int i = 7; i < 64;){
    setRegisterPin(i,HIGH);   
    writeRegisters();
    setRegisterPin(i - 8,LOW);   
    writeRegisters();    
      
    i = i + 8;
  }
  
  for(int i = 2; i < 10; i++){
    digitalWrite(i,HIGH);
    delay(1);
    digitalWrite(i,LOW);
  }
  
  digitalWrite(t8,HIGH);
  for(int i = 63; i > 0;){
    setRegisterPin(i,HIGH);   
    writeRegisters();
    setRegisterPin(i,LOW);   
    writeRegisters();
    
    i = i - 8;
  }
  
  setRegisterPin(7,HIGH);   
  writeRegisters();

  for(int i = 9; i >= 2; i--){
    digitalWrite(i,HIGH);
    delay(1);
    digitalWrite(i,LOW);
  }
}