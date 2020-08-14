// Include Arduino FreeRTOS library
#include <Arduino_FreeRTOS.h>

// Include queue support
#include <queue.h>

#define T_C 262
#define T_D 294
#define T_E 330
#define T_F 370
#define T_G 392
#define T_A 440
#define T_B 493



#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978



const int C = 10;
const int D = 9;
const int E = 8;
const int F = 7;
const int G = 6;
const int A = 5;
const int B = 4;
const int song = 3;
const int song2=2;

const int Buzz = 11;
const int LED = 13;

QueueHandle_t QUEUE;

void setup() {
  pinMode(LED, OUTPUT);

  
  pinMode(Buzz, OUTPUT);
  pinMode(C, INPUT);
  digitalWrite(C,HIGH);
  
  pinMode(D, INPUT);
  digitalWrite(D,HIGH);
  
  pinMode(E, INPUT);
  digitalWrite(E,HIGH);
  
  pinMode(F, INPUT);
  digitalWrite(F,HIGH);
  
  pinMode(G, INPUT);
  digitalWrite(G,HIGH);
  
  pinMode(A, INPUT);
  digitalWrite(A,HIGH);
  
  pinMode(B, INPUT);
  digitalWrite(B,HIGH);

  pinMode(song, INPUT);
  digitalWrite(song,HIGH);

  pinMode(song2, INPUT);
  digitalWrite(song2,HIGH);

  digitalWrite(LED,LOW);

  QUEUE = xQueueCreate(30,  sizeof(int) );

    xTaskCreate(GetNotes,"GETnotes", 128, NULL,0, NULL);
                
    xTaskCreate(PlayNotes, "PlayNotes",  128, NULL, 1,NULL);                

  vTaskStartScheduler();
}





int melody1[] = {
NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4,  NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_F4, 0, 0,
NOTE_DS4, NOTE_DS4, NOTE_F4, NOTE_D4, 0, 0, 0, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D5, NOTE_D5,
NOTE_G3, NOTE_AS3, NOTE_C4, NOTE_G3, NOTE_G3, NOTE_AS3, NOTE_AS4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_AS4, NOTE_AS4, 
NOTE_G3, NOTE_AS3, NOTE_C4, NOTE_G3, NOTE_G3, NOTE_AS3,
};

int melody2[] = {
NOTE_AS4, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4,  NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_F4, 0, 0,
NOTE_DS4, NOTE_DS4, NOTE_F4, NOTE_D4, NOTE_G3, NOTE_AS3, NOTE_C4, NOTE_F3, NOTE_AS3, NOTE_A3, NOTE_F3, 
NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D5, NOTE_D5,
NOTE_G3, NOTE_AS3, NOTE_C4, NOTE_F3, NOTE_AS3, NOTE_G3, NOTE_AS4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_AS4, NOTE_AS4, 
};


float noteDurations1[] = {
  
4.5, 2.25, 2.25, 4.5, 2.25, 2.25, 2.25, 2.25, 2.25, 4.5, 3, 9, 4.5, 
4.5, 2.25, 4.5, 2.25, 1.125, 2.25, 4.5, 4.5, 2.25, 4.5, 2.25, 4.5, 2.25, 
4.5, 4.5, 4.5, 2.25, 4.5, 4.5, 4.5, 2.25, 4.5, 2.25, 4.5, 2, 
4.5, 4.5, 4.5, 2.25, 4.5, 4.5,};


float noteDurations2[] = {
4.5, 2.25, 2.25, 4.5, 2.25, 2.25, 2.25, 2.25, 2.25, 4.5, 3, 9, 4.5, 
4.5, 2.25, 4.5, 4.5, 4.5, 4.5, 4.5, 4.5, 3, 3, 4.5, 
2.25, 4.5, 2.25, 4.5, 2.25, 
4.5, 4.5, 4.5, 4.5, 2.25, 4.5, 4.5, 2.25, 4.5, 2.25, 4.5, 2.25, 

} ;



void loop() {

  
}


int C_inQueue = 0;
int D_inQueue= 0;
int E_inQueue= 0;
int F_inQueue = 0;
int G_inQueue = 0;
int A_inQueue = 0;
int B_inQueue = 0;
int sonG_inQueue=0;
int sonG2_inQueue=0;
void GetNotes(void *pvParameters)
{
  (void) pvParameters;
  while (1)
  {
    
    while (digitalRead(C) == LOW && C_inQueue == 0) {
      int c_int = T_C;
      xQueueSend(QUEUE,&c_int, portMAX_DELAY);
      C_inQueue = 1;
    }
    

    while (digitalRead(D) == LOW && D_inQueue== 0) {
      int d_int = T_D;
      xQueueSend(QUEUE,&d_int, portMAX_DELAY);
      D_inQueue= 1;
    }


    while (digitalRead(E) == LOW && E_inQueue== 0) {
      int e_int = T_E;
      xQueueSend(QUEUE,&e_int, portMAX_DELAY);
      E_inQueue= 1;
    }


    while (digitalRead(F) == LOW && F_inQueue == 0) {
      int f_int = T_F;
      xQueueSend(QUEUE, &f_int, portMAX_DELAY);
      F_inQueue = 1;
    }

    while (digitalRead(G) == LOW && G_inQueue == 0) {
      int g_int = T_G;
      xQueueSend(QUEUE, &g_int, portMAX_DELAY);
      G_inQueue = 1;
    }


    while (digitalRead(A) == LOW && A_inQueue == 0) {
      int a_int = T_A;
      xQueueSend(QUEUE, &a_int, portMAX_DELAY);
      A_inQueue = 1;
    }
 

    while (digitalRead(B) == LOW && B_inQueue == 0) {
      int b_int = T_B;
      xQueueSend(QUEUE, & b_int , portMAX_DELAY);
      B_inQueue = 1;
    }

    while(digitalRead(song) ==LOW  && sonG_inQueue == 0) {
      int order= song;
      xQueueSend(QUEUE, &order, portMAX_DELAY);
      sonG_inQueue=1;
  }
    while(digitalRead(song2) ==LOW  && sonG2_inQueue == 0) {
      int order2= song2;
      xQueueSend(QUEUE, &order2, portMAX_DELAY);
      sonG2_inQueue=1;
  }
  
    while (digitalRead(C) == LOW && C_inQueue == 1) {
       digitalWrite(LED,HIGH); 
    } 

     while (digitalRead(D) == LOW && D_inQueue== 1) {
       digitalWrite(LED,HIGH);
    }
        while (digitalRead(E) == LOW && E_inQueue== 1) {
       digitalWrite(LED,HIGH);
    }
        while (digitalRead(E) == LOW && F_inQueue == 1) {
       digitalWrite(LED,HIGH);
    }
        while (digitalRead(G) == LOW && G_inQueue == 1) {
       digitalWrite(LED,HIGH);
    }
   while (digitalRead(A) == LOW && A_inQueue == 1) {
       digitalWrite(LED,HIGH);
    }
    
      while (digitalRead(B) == LOW && B_inQueue == 1) {
       digitalWrite(LED,HIGH);
    }
      while (digitalRead(song) == LOW &&  sonG_inQueue == 1) {
      
    }
          while (digitalRead(song2) == LOW &&  sonG2_inQueue == 1) {
      
    }
    
    noTone(Buzz);
    digitalWrite(LED,LOW);
    C_inQueue = 0;
    D_inQueue= 0;
    E_inQueue= 0;
    F_inQueue = 0;
    G_inQueue = 0;
    A_inQueue = 0;
    B_inQueue = 0;
    sonG_inQueue=0;
    sonG2_inQueue=0;
  }
}

void PlayNotes(void *pvParameters)
{
  (void) pvParameters;
  int Queue_out = 0;

  while (1) 
  {
    Queue_out = 0;

    if (xQueueReceive(QUEUE, &Queue_out, portMAX_DELAY) == pdTRUE) {
      if(Queue_out==3){ // FIrst melody
        Queue_out = 0;
        digitalWrite(LED,HIGH);
                  for (int thisNote=0; thisNote <20; thisNote++) {
                  int noteDuration = 600 / noteDurations1[thisNote];
                  tone(Buzz, melody1[thisNote], noteDuration);
                  int pauseBetweenNotes = noteDuration ;
                  delay(pauseBetweenNotes);
                    }digitalWrite(LED,LOW);
        }
        else if (Queue_out==2){
          digitalWrite(LED,HIGH);
                  Queue_out = 0;
                  for (int thisNote=10; thisNote <40; thisNote++) {
                  int noteDuration = 600 / noteDurations2[thisNote];
                  tone(Buzz, melody2[thisNote], noteDuration);
                  int pauseBetweenNotes = noteDuration ;
                  delay(pauseBetweenNotes);
                    }digitalWrite(LED,LOW);
          
          }

       else
       tone(Buzz,Queue_out);
 
    }
    
//    vTaskDelay(1);
  }
}
