# taps-bot
Arduino based-device for automatize, record and play physical taps sequences.

# What i need?
 - 1 Servo
 - 10 or 14 wires (what do you think what you need)
 - 2 switches
 - 2 buttons
 - 1 Stylus Pen (or use your imagination if you want to set up in an PC)
 - Arduino Uno
 
 ## How it works?
 Step 1:
 First, view the included schema for connect the things.
 By default all of these pins are set-up by default in the code/pre-compiled binaries:
  - PIN 2 for recording switch
  - PIN 4 for play switch
  - PIN 7 for mode button
  - PIN 10 for pulse button
  - PIN 11 for attach the servo
  
  After you read and view the schema and wired everything, you are ready for the next step
  
  Step 2:
  Flash the pre-compiled binaries or upload the sketch with the Arduino IDE or Visual Studio Code (Arduino extension installed)
  Once you are done, the device is ready to go!
  
  # FAQs
  For avoid you post useless issues, here we go answering some questions what you may have
  
  Q: The schema is horrible you dont have it in better quality?
  A: idk man, im new doing these things, i taked an snapshot of the schema maded in SimulIDE
  
  Q: The taps are out of sync with real taps what i recorded
  A: This project it is an brand new thing what i maded for an school project, dont expect an high acurracy of that, if do you want, try to "calibrate" the taps. Go to line 57 and 59 and modify carefully the "60" value, test it and if it stills not working, repeat with other value and test again the acurracy
  
  Q: Your counting system is shit, why you dont maded it with "millis()" function to calculate an more acurrated delay between taps?
  A: Tried, but i dont have time to adapt it, if do you want launch an pull request with your fixed code.
  
  Q: Why i cant record more than 100 taps?
  A: Go to line 5 and modify max_taps number "100" with the ammount of taps what do you need, and upload.
  WARNING: Please dont abuse putting an dumb value like 99999 or 100000 taps, dont overload your arduino.
  # Releases
  07/12/2018 : First launch to github
  Im expecting to launch updates for delete annoying bugs and improve the delay detection system, but until then enjoy the bugs
  Also i want to add the calibration mode, for help the process viewing what value is correct for your servo
  
  ## Im updating this read.me with useful info and more questions.
