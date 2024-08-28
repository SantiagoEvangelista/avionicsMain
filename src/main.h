
#include <stdint.h>
#include <stdbool.h>
#include <sbus.h>


#ifndef MAIN_H
#define MAIN_H


#define FOLLOW_PATH_MODE 0
#define MANUAL_MODE 1
#define MANUAL_ALT_HOLD 2

#define PAYLOAD_ONE_PIN 0
#define PAYLOAD_TWO_PIN 0


bfs::SbusTx sbusTx(&Serial2);

typedef struct {
  int setpointEcefX;
  int setpointEcefY;
  int setpointEcefZ;
  uint8_t mode;
  uint8_t payloadDeploy;
  uint8_t thrust;
  uint8_t roll;
  uint8_t pitch;
  uint8_t yaw;
} groundStationPacket;

typedef struct{
  int ecefX;
  int ecefY;
  int ecefZ;
  int velocityX;
  int velocityY;
  int velocityZ;
  int orientationX;
  int orientationY;
  int orientationZ;
  int angularVelocityX;
  int angularVelocityY;
  int angularVelocityZ;
} state;


typedef struct{
  uint8_t thrust;
  uint8_t roll;
  uint8_t pitch;
  uint8_t yaw;
} droneCommand;


void writeSBUS(droneCommand command){
    bfs::SbusData data;

    //convert command into sbus data

    //TODO: TEST THE CHANNELS ORDER
    data.ch[0] = command.thrust;
    data.ch[1] = command.roll;
    data.ch[2] = command.pitch;
    data.ch[3] = command.yaw;
    
    sbusTx.data(data);
    sbusTx.Write();
};

bool getGroundStationPacket(groundStationPacket* packet);

bool getState(state* currState);

droneCommand droneControl(groundStationPacket packet, state currState, droneCommand prevCommand, float dt, droneCommand* command){
    //align the drone to next waypoint (inside packet) with a controller
    //Once aligned (inside a threshold), go to the point mainting the orientation with a controller
    //all of this maintaining the set altitude (measurement inside currState and setpoint altitude is a parameter) with a controller (inside margin and smoothly)

    return *command;
    //three controllers in total (distance, orientation and altitude)
}



#define ALTITUDE_MARGIN 0.1
#define K_ALT 1
#define KD_ALT 1
#define KI_ALT 1

uint8_t altitudeControl(groundStationPacket packet, state currState, uint8_t prevThust, float dt){

    uint8_t thrust = 0;

    if ((packet.setpointEcefZ - currState.ecefZ) > ALTITUDE_MARGIN){
        thrust = K_ALT*(packet.setpointEcefZ - currState.ecefZ) + KD_ALT*(currState.velocityZ) + KI_ALT*(packet.setpointEcefZ - currState.ecefZ)*dt;
    }
    else{
        thrust = prevThust;
    }
    
    return thrust;
}

void deployPayload(uint8_t payloadDeploy){
    switch (payloadDeploy){
    case 0:
        break;

    case 1:
        break;
    
    case 2:
        break;
    
    default:
        break;
    }
}



#endif

