#include "Actuator.h"
#include "Screen.h"

Screen::Screen() {
    this -> mode = 0; //mode 0 = time display // mode 1 = lap display
    this -> pauseTime = 1000; // ms that lap time will display at the end of the lap
    this -> modeTimeStart = 0;
    this -> timeStartTime = millis();

    
}


void Screen::displayLapTime(unsigned int inTime) {
    this -> mode = 1;

    this -> modeTimeStart = millis();

    // Code that displays on the screen what the passed in laptime was

    unsigned long currentTime = 0;

    unsigned int seconds = currentTime % 60;

    unsigned int minutes = currentTime / 60;

    //Displays it on the screen

    this->matrix.writeDigitNum(0, minutes / 10);
    this->matrix.writeDigitNum(1, minutes % 10);

    this->matrix.writeDigitNum(2, ':');

    this->matrix.writeDigitNum(3, seconds / 10);
    this->matrix.writeDigitNum(4, seconds % 10);

    matrix.drawColon(true);
    matrix.writeDisplay();


}

void Screen::displayTime() {
    if(mode != 1) {
        // Display the code for the time

        Serial.println("IN DISPLAY");


        unsigned long currentTime = (millis() - this->timeStartTime) / 1000;

        unsigned int seconds = currentTime % 60;

        unsigned int minutes = currentTime / 60;


        Serial.print("SECONDS: ");
        Serial.println(seconds);

        Serial.print("MINUTES: ");
        Serial.println(minutes);

        //Displays it on the screen

        this->matrix.writeDigitNum(0, minutes / 10);
        this->matrix.writeDigitNum(1, minutes % 10);

        this->matrix.writeDigitNum(2, ':');

        this->matrix.writeDigitNum(3, seconds / 10);
        this->matrix.writeDigitNum(4, seconds % 10);

        this->matrix.drawColon(true);
        this->matrix.writeDisplay();
    };

    if(this->pauseTime <= millis() - this->modeTimeStart) { // Checks how long the mode 1 laptime display has been on and switches back to mode 0 if its been on long enough
        this->mode = 0;
    }
}

void Screen::updateValue(const SensorData& data) {

    //Pull the lap time from the sensorData object

    //Strip time data to get the unsigned

    //displayLapTime();
}

void Screen::setMatrix(Adafruit_7segment myMatrix) {
    this->matrix = myMatrix;

    Serial.println("SET MATRIX"); 

}
