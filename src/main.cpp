#include <Arduino.h>
#include <main.h>
#include <sbus.h>



groundStationPacket packet;
state currState;
droneCommand prevCommand={0,0,0,0};
droneCommand command;
uint8_t prevThrust = 0;
float t = 0;
float dt = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sbusTx.Begin();
  t=millis();
}

void loop() {


  //get ground station packet and state

  if (!getGroundStationPacket(&packet) || !getState(&currState)){
    
    //handle shit

  }
  
  
  switch (packet.mode){
    case FOLLOW_PATH_MODE:
      dt = millis() - t;
      prevCommand = droneControl(packet,currState,prevCommand,dt,&command);
      t = millis();
      break;


    case MANUAL_MODE:
      //get the command values inside the packet
      command.thrust=packet.thrust;
      prevThrust=command.thrust;
      command.pitch=packet.pitch;
      command.roll=packet.roll;
      command.yaw=packet.yaw;      
      break;

    case MANUAL_ALT_HOLD:
          //get the command values inside the packet
      dt = millis() - t;
      command.thrust = altitudeControl(packet,currState,prevThrust,dt);
      t = millis();
      prevThrust = command.thrust;
      command.pitch=packet.pitch;
      command.roll=packet.roll;
      command.yaw=packet.yaw;      
      break;

    default:
      break;
  }
    
    
  if (packet.payloadDeploy){
    deployPayload(packet.payloadDeploy);
  }

  writeSBUS(command);
}