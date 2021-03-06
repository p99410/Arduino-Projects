#include <Stepper.h>
#include <Servo.h> 
byte byteRead; 
boolean done; 
int num;
int dig;
boolean cmd;
Servo serv;
int steps;
Stepper stepper(2048, 8,9,10,11);
int ang;




void setup() { 


  Serial.begin(9600);
  serv.attach(5);
}


void loop() {


  done = true; // so that the big "while" wouldn't be triggered unless byteRead is 65
  num = 0; // set for this new loop


  byteRead = Serial.read();
  while(byteRead == 65 || done == false)
  { 


    done = false; // so that "while" wouldn't stop inspite of changes of byteRead
    delay(10); // for better communication
    byteRead = Serial.read();


    while(byteRead >= 48 && byteRead <= 57 && done == false)
    { 


      num = (byteRead -48) + num * 10;
      delay(10); 
      byteRead = Serial.read(); // read before "if" and another aound of "while"


      if (byteRead ==10)
      { 
        done = true; // to end both big and small "while", I know there's a command for
        // this situation, but I forgot how to use it... called "break" maybe
        cmd = true; // to help distinguish if there IS a command. 
        // so that the servo wouldn't keep going to 0
        Serial.print ("Received: ");
        Serial.print ("A");
        Serial.println (num);




      }
    }
  }


  if (cmd == true ) // if there's actually a command
  { 
    if (num <= 180 && num >= 0 ){
      ang=serv.read();
      if (ang < num){

        for(ang = ang;ang<num;ang=ang+1){
          //servo action


          serv.write(ang); 
          delay(10);
        }


        //Serial action
      }
    
    if (ang > num){
      { 
        for(ang=ang;ang>num; ang=ang-1){
          //servo action
          serv.write(ang); 
          delay(10);
        }


      }
      delay(15);
      cmd = false; 
      num = 0;
    }
    }
  
  else
  {
    Serial.println("error: excessive angle");
    // if there is a command and Arduino receives a excessive angle number
    // this code automatically ignores "-", so no worries about negative degrees
  }


}












while(byteRead == 83 || done == false)
{ 


  done = false; // so that "while" wouldn't stop inspite of changes of byteRead
  delay(10); // for better communication
  byteRead = Serial.read();


  while(byteRead >= 48 && byteRead <= 57 && done == false)
  { 


    steps = (byteRead -48) + steps * 10;
    delay(10); 
    byteRead = Serial.read(); // read before "if" and another aound of "while"


    if (byteRead ==10)
    { 
      done = true; // to end both big and small "while", I know there's a command for
      // this situation, but I forgot how to use it... called "break" maybe
      cmd = true; // to help distinguish if there IS a command. 
      // so that the servo wouldn't keep going to 0
      Serial.print ("Received: ");
      Serial.print ("S");
      Serial.println (steps);




    }
  }
}






if (cmd == true ) // if there's actually a command
{ 


  //stepper action


  stepper.setSpeed(13);


  stepper.step(steps);
  cmd = false; 
  steps = 0;


}

}


