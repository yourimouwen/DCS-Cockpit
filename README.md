Hi all!

I made a 3D printed attitude indicator and altimeter, which I linked with the beautiful game of DCS: World to display its information on these flight instruments. This is the first step in making my own small cockpit around my monitor. I'm sorry if some parts aren't clear, please tell me if they are. Putting the 3d printed objects together should speak for itself, and if it isn't clear, please comment! Also, the attitude indicator is not perfect, there is a small delay between the game and the indicator and the altimeter might skip a few steps sometimes. I'm not sure why this is, but please comment if you find out why!

[Both the attitude indicator and the altimeter](https://preview.redd.it/5xmenvi67te71.jpg?width=4608&format=pjpg&auto=webp&s=4ed48c29a340ce8f4951d20adae439e11591863e)

So basically, there already exist 3d files for [altimeters](https://www.thingiverse.com/thing:2744359) and [attitude indicators](https://www.thingiverse.com/thing:2473812) on the internet. My own part in this is being able to make a program to output the information of DCS: World onto these instruments. Therefore, I will mostly go into my code and how the project came together, and how you can make these to have your own cockpit instruments.

Here is my [github](https://github.com/yourimouwen/DCS-Cockpit), where you can download all program files.

In short, the windows console program starts a connection with DCS over your local WiFi network and also connects with the Arduino through a USB serial connection. Then the Export.lua file sends the needed data (such as the bank, pitch, etc. of your aircraft) to the windows console program over your local network through the loopback IP address. The console program does some calculations to make it readable for the motors that are connected to the Arduino and then sends that code to the Arduino, which drives the motors of the attitude indicator and altimeter.

Let's first treat the attitude indicator. I will not go too much into the parts and 3d prints you'll need, since you can find and download them on the website of the link earlier in the post. You'll also need at least the following for both the attitude indicator and the altimeter:

* An Arduino Uno, or another Arduino with a USB or other serial connection to connect to and enough GPIO pins
* Enough wires, Both male-to-male and male-to-female Dupont jumper wires are recommended
* M3 nuts and bolts
* A power supply/adapter to output 5V and at least 2-3 Amps (1.5 amps is also fine if you plan to not build more of these cockpit instruments. I do though, and it's always nice to have more current available)
* A breadboard and a breadboard power module with 5V output

For the attitude indicator, you'll need:

* 2 SG90 servos 9g with screws
* White paint to paint a few small plastic pieces

Putting the attitude meter together should not be very hard. You can see in [this video](https://www.youtube.com/watch?v=DBns286NXeo) what the final product should look like. However, if the design is not clear, please feel free to comment on my post.

As for the wiring, put the Signal pin of the servo responsible for the bank of the aircraft on pin number 3 and the Signal pin of the servo responsible for the pitch of the aircraft on pin number 5. I used an Arduino Uno, so using a different Arduino you might have to change the .ino file to fit the pins. Just make sure it connects with a PWM or pins with a \~/tilde on the Arduino.

For the altimeter, you'll need:

* A 28BYJ-48 stepper motor with ULN2003 driver board
* A rotary encoder upon which you can mount buttons. I used [this one](https://nl.aliexpress.com/item/32915420023.html?spm=a2g0s.9042311.0.0.eb0d4c4dnHVF9X)
* 5mm, 4mm and 3mm hollow copper tubes. 6mm, 4mm and 2mm were only available in my area, so I used those which are fine too
* Superglue
* White paint to paint a few plastic pieces

A dremel or multitool can be quite handy to drill holes and to sand things. [This video](https://www.youtube.com/watch?v=YhThtm_ZIwE) explains very well how the altimeter is put together. The guy is also funny to watch.

For the rotary encoder, I snapped off the cylindrical 3d printed part because it didn't print straight and is likely to break. Instead, I drilled a hole in it and superglued some copper tubing into it and placed the knob onto the other side of the copper tubing. Then, I shoved the rotary encoder into the gear. Make sure it rotates well before superglueing the knob, you really can't get it off when it's glued in place.

As for the wiring of the altimeter, make sure to put IN1 on pin 11, IN2 on pin 10, IN3 on pin 9 and IN4 on pin 8. Again, if you change the order or if you use a different Arduino, make sure to check that the order in the Arduino code is also correct (using the order of 8, 10, 9, 11 or IN4, IN2, IN3, IN1).The rotary encoder is a bit tricky, since different rotary encoders use different names for the pinout. Mine have the names, KEY, S1 and S2. The KEY pin on the encoder goes to pin number 7 on the Arduino, the S2 pin goes to pin number 4 and the S1 pin goes to pin number 2.

The 5V and + wires connect to the + and the GND and - wires connect to the - on the breadboard. Make sure that the power module is on the correct side of the breadboard or you won't get any power to the motors. Also, *very important*, make sure that a wire runs from the - on the breadboard to one of the GND pins on the Arduino, otherwise your motors won't get any power.

&#x200B;

[The wiring is going to be a mess, but it's worth it!](https://preview.redd.it/ozzccuqa7te71.jpg?width=4608&format=pjpg&auto=webp&s=575c6ed6adc323593cbdfca66fb62d230d7b5c13)

&#x200B;

[The attitude meter and altimeter from the back with the respective servos and motor and rotary encoder.](https://preview.redd.it/847heh9d7te71.jpg?width=4608&format=pjpg&auto=webp&s=a591d8b43a8a7d2d71db1c7e3efd9f03d1882772)

After putting these together, having all wires checked and connected properly, and plugging your Arduino into you PC we now dive into setting up the software. Download the files from my GitHub page and create a shortcut for the DCS Cockpit console program to make it easy for you and put in on your Desktop. Let's first bother with the Arduino code. Download the Arduino IDE from the internet and open the DCSCockpit-Arduino.ino file from the Arduino IDE. Connect your Arduino to the IDE by selecting the right board (and downloading the right drivers if you have an Chinese Arduino clone like I do) and upload the code to the Arduino. That should be it.

Then, start up the console program. It should find the Arduino, otherwise specify the COM-port the Arduino is connected to in the console window. When going into a mission, the console program should say "DCS connected". Give the shortcut to the console program a cool icon and name for extra fire!

Now for the Export.lua file, you don't want to mess with the original Export.lua file in the DCS folder. Go to your Saved Games folder in "Drive:\\Users\\*username*\\Saved Games\\DCS\\Scripts\\" and paste it in there. If the Scripts folder does not exist yet, you have to create it yourself and give it this name. [This video](https://www.youtube.com/watch?v=c19Gi0SjEE0) also explains this. The guy even sounds like a pilot.

The rotary encoder is used to find the zero position. I didn't connect the small gear to the large gear that displays the barometric pressure (the latter is therefore only for show) because then the rotary encoder can be used for the Arduino to know where the zero position is found and won't result in much friction. First, turning the rotary encoder allows rough turning of the needle. Should the game end unexpectedly when your plane is at 3000ft, for example, you can then quickly set the needle back to the zero position by doing so. After clicking the rotary encoder once, you can make fine adjustments to perfectly line the needles up to the 0 on the top. Clicking once more, you tell the Arduino that the current position is the zero position. Click once more to make sure that rotating the encoder now won't result in the needle moving, it's basically in a safe position and you are now ready to fly. Clicking once more will make the encoder go back to rough adjustments for the needles. Do these adjustments just before starting the mission.

That should be all. If you now start up the windows program and then DCS, it should work. If it doesn't, check your wiring again and make sure that the Ground of the external power supply is connected through a wire to the Arduino Ground (GND).

Finally, I would very much like to thank the creator [Alvaro Alea](https://www.thingiverse.com/alvaroalea/designs) of the 3d files to be able to make this awesome project and u/truetofiction for helping me with debugging my code!
