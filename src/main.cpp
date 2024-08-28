#include <Arduino.h>
#include <main.h>
#include <sbus.h>



groundStationPacket packet;
state currState;
state prevState;
droneCommand command;
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
      droneControl(packet,currState,prevState,dt,&command);
      t = millis();
      break;


    case MANUAL_MODE:
      //get the command values inside the packet
      command.thrust=packet.thrust;
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