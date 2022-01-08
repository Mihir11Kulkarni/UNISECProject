#include <SPI.h>
#include <LoRa.h>

String RX_String; //Stores the received packet
int dollarIndex[10]; 
String gyro_x;
String gyro_y;
String gyro_z;
String acc_x;
String acc_y;
String acc_z;
String temperature_bme;
String humidity_bme;
String altitude_bme;
String SatName = "";
String GPS_lat;
String GPS_lon;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(434E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.receive(); //Permanently sets the GS to receive mode
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if(packetSize){
      char RX_Char[packetSize];
    for(int i=0;i<packetSize;i++){
      RX_Char[i] = (char)LoRa.read();
    }
    RX_String = String(RX_Char);
    //Serial.println(RX_String); //uncomment to view the received string on serial monitor 
    StringCat(); //Format the received string to view in serial monitor
   }
}

void StringCat(){
  dollarIndex[0]=RX_String.indexOf("$");
  SatName = RX_String.substring(0,dollarIndex[0]);
  dollarIndex[1]=RX_String.indexOf("$",dollarIndex[0]+1);
  GPS_lat = RX_String.substring(dollarIndex[0]+1,dollarIndex[1]);
  dollarIndex[2]=RX_String.indexOf("$",dollarIndex[1]+1);
  GPS_lon = RX_String.substring(dollarIndex[1]+1,dollarIndex[2]);
  dollarIndex[3]=RX_String.indexOf("$",dollarIndex[2]+1);
  temperature_bme = RX_String.substring(dollarIndex[2]+1,dollarIndex[3]);
  dollarIndex[4]=RX_String.indexOf("$",dollarIndex[3]+1);
  altitude_bme = RX_String.substring(dollarIndex[3]+1,dollarIndex[4]);
  dollarIndex[5]=RX_String.indexOf("$",dollarIndex[4]+1);
  gyro_x = RX_String.substring(dollarIndex[4]+1,dollarIndex[5]);
  dollarIndex[6]=RX_String.indexOf("$",dollarIndex[5]+1);
  gyro_y = RX_String.substring(dollarIndex[5]+1,dollarIndex[6]);
  dollarIndex[7]=RX_String.indexOf("$",dollarIndex[6]+1);
  gyro_z = RX_String.substring(dollarIndex[6]+1,dollarIndex[7]);
  dollarIndex[8]=RX_String.indexOf("$",dollarIndex[7]+1);
  acc_x = RX_String.substring(dollarIndex[7]+1,dollarIndex[8]);
  dollarIndex[9]=RX_String.indexOf("$",dollarIndex[8]+1);
  acc_y = RX_String.substring(dollarIndex[8]+1,dollarIndex[9]);
  acc_z = RX_String.substring(dollarIndex[9]+1);
  Serial.print("Name: ");Serial.print(SatName);Serial.print(" LAT: ");Serial.print(GPS_lat);Serial.print(" LON: ");Serial.println(GPS_lon);
  Serial.print("Temp: ");Serial.print(temperature_bme);Serial.print(" ALT: ");Serial.println(altitude_bme);
  Serial.print("GYRO X: ");Serial.print(gyro_x);Serial.print(" Y: ");Serial.print(gyro_y);Serial.print(" Z: ");Serial.println(gyro_z);
  Serial.print("ACC X: ");Serial.print(acc_x);Serial.print(" Y: ");Serial.print(acc_y);Serial.print(" Z: ");Serial.println(acc_z);
}
