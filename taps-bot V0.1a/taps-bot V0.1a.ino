/****************************************************
* taps-bot V0.1a
* Copyright (c) PANCHO7532 - P7Comunications LTD S.A
*****************************************************/
#include <Servo.h> //including the library for handle servo
Servo motor;
const int servo_minms = 500; //500 for towerpro 9g-SG90, 1000 for simulIDE servo
const int servo_maxms = 2500; //2500 for towerpro 9g-SG90, 2000 for simulIDE servo
const int max_taps = 100;
const byte record_button = 2;
const byte play_button = 4;
const byte mode_button = 7;
const byte pulse_button = 10;
const byte servo_pin = 11;
byte mode_choices = 0;
unsigned long taps_delay[max_taps];
unsigned long taps_delay2[max_taps];
long counter[4];
bool a1, a2, a3, a4, a5;
unsigned int secs_play = 5000;
void change_mode() {
	if(digitalRead(mode_button) == LOW) {
		mode_choices++;
		if(mode_choices > 2) {
			mode_choices = 0;
		}
		if(mode_choices == 0) {
			Serial.println("[INFO] - Remote mode enabled!!!");
		} else if(mode_choices == 1) {
			Serial.println("[INFO] - Recording/Play mode enabled!!!");
		} else if(mode_choices == 2) {
			Serial.println("[INFO] - Calibration mode enabled!!!");
		} else {
			Serial.println("[ERROR] - An error ocurred while switching the modes.");
		}
		delay(1000); //for avoid problems
	}
}

void recording_mode() {
	if(a3 == true) {
		Serial.println("[REC] - Recording started!!!");
		a3 = false;
	}
	stage1:
	while(digitalRead(10) == HIGH) { //when is not pressed
		counter[0]++;
		if(digitalRead(10) == LOW) {
			break;
		}
	}
	while(digitalRead(10) == LOW) { //when it is pressed
		counter[1]++;
		if(digitalRead(10) == HIGH) {
			break;
		}
	}
	taps_delay[counter[2]] = counter[0]/60;
	taps_delay2[counter[2]] = counter[1]/60;
	Serial.print("[REC] - Tap recorded! PRS: ");
	Serial.print(counter[0]/60);
	Serial.print(" PRS2: ");
	Serial.print(counter[1]/60);
	Serial.println();
	counter[0] = 0;
	counter[1] = 0;
	counter[2]++;
	if(digitalRead(2) == LOW) {
		goto stage1;
	} else {
		a3 = true;
		return;
	}
}
void play_mode() {
	if(a4 == true) {
		Serial.print("[PLAY] - The ");
		Serial.print(counter[2]);
		Serial.print(" recorded taps will be played in: ");
		Serial.print(secs_play/1000);
		Serial.print(" seconds.");
		Serial.println();
		a4 = false;
	}
	delay(secs_play);
	stage2:
	Serial.println("[PLAY] - Playing sequence...");
	/*
	for(counter[4] = 0; counter[4] < counter[2]; counter[4]++) {
		motor.writeMicroseconds((servo_minms + servo_maxms) /3);
		delay(taps_delay[counter[4]]);
		motor.writeMicroseconds(servo_minms);
		delay(taps_delay2[counter[4]]);
	}
	*/
	while(counter[4] < counter[2]) {
		Serial.println(taps_delay[counter[4]]);
		motor.writeMicroseconds((servo_minms + servo_maxms) /3);
		delay(taps_delay[counter[4]]);
		Serial.println(taps_delay2[counter[4]]);
		motor.writeMicroseconds(servo_minms);
		delay(taps_delay2[counter[4]]);
		motor.writeMicroseconds(servo_minms);
		counter[4]++;
	}
	Serial.println("[PLAY] - Sequence finished!!!");
	Serial.println("[PLAY] - For replay the sequence press PULSE, turn off PLAY to exit and delete sequence.");
	while(a5 == true) {
		if(digitalRead(4) == HIGH) {
			delay(300);
			a5 = false;
			counter[2] == 0;
			counter[4] == 0;
			return;
		} else if(digitalRead(10) == LOW) {
			goto stage2;
		}
	}
}

void calibration_mode() {

}
void setup() {
	//Insert code here for run once
	a1 = true;
	a2 = true;
	a3 = true;
	a4 = true;
	a5 = true;
	counter[0] = 0;
	counter[1] = 0;
	counter[2] = 0;
	counter[3] = 0;
	counter[4] = 0;
	motor.attach(servo_pin);
	Serial.begin(9600);
	pinMode(record_button, INPUT_PULLUP);
	pinMode(play_button, INPUT_PULLUP);
	pinMode(mode_button, INPUT_PULLUP);
	pinMode(pulse_button, INPUT_PULLUP);
	pinMode(13, OUTPUT);
	Serial.println("======================================================");
  	Serial.println("Auto-Taps device");
  	Serial.println("Copyright PANCHO7532 - P7Comunications LTD S.A 2018");
  	Serial.println("======================================================");
  	Serial.println("[INFO] - Standby");
}

void loop() {
	//Insert code here for run again to the infinite
	change_mode(); //Loop things
	switch(mode_choices) {
		case 0:
		while(digitalRead(10) == LOW) {
			motor.writeMicroseconds((servo_minms + servo_maxms) / 3);
		}
		motor.writeMicroseconds(servo_minms);
		return;
		case 1:
		if(digitalRead(2) == LOW && digitalRead(4) == LOW) {
			if(a2 == true) {
				Serial.println("[ERROR] - Please leave one switch on. (Record or Play)");
				a2 == false;
				return;
			}
			return;
		}
		a2 = true;
		if(digitalRead(2) == LOW && digitalRead(4) == HIGH) {
			recording_mode();
		} else if(digitalRead(2) == HIGH && digitalRead(4) == LOW) {
			play_mode();
		}
		return;
		case 2:
		calibration_mode();
		return;
		default:
		if(a1 == true) {
			Serial.println("[ERROR] - Invalid mode detected, reboot arduino!");
			a1 = false;
		}
		return;
	}
}