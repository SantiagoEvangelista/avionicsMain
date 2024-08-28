
#include <stdint.h>
#include <stdbool.h>
#include <sbus.h>


#ifndef MAIN_H
#define MAIN_H


#define FOLLOW_PATH_MODE 0
#define MANUAL_MODE 1



bfs::SbusTx sbusTx(&Serial2);

typedef struct {
  int setpointEcefX;
  int setpointEcefY;
  int setpointEcefZ;
  uint8_t mode;
  uint8_t payloadStatus;
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

    sbusTx.data(data);
    sbusTx.Write();
};

bool getGroundStationPacket(groundStationPacket* packet);

bool getState(state* currState);

droneCommand droneControl(groundStationPacket packet, state currState, state prevState, float dt, droneCommand* command){

    //align the drone to next waypoint (inside packet) with a controller
    //Once aligned (inside a threshold), go to the point mainting the orientation with a controller
    //all of this maintaining the set altitude (measurement inside currState and setpoint altitude is a parameter) with a controller (inside margin and smoothly)


    //three controllers in total (distance, orientation and altitude)
}


#endif

