---
title: Westinghouse M95A Rifle Modification
layout: splash
header:
  overlay_image: /assets/images/rifle.jpg
  overlay_filter: 0.50
  actions:
    - label: "<i class='fas fa-download'></i> Build now"
      url: "#instructions"
    - label: "<i class='fab fa-github'></i> View on GitHub"
      url: "https://github.com/jsware/t800-rifle"
excerpt: >
  A modification to the Westinghouse M95A Phased Plasma Rifle in a 40W Range to add lights and sounds.
gallery:
  - url: /assets/images/leds.jpg
    image_path: /assets/images/leds.jpg
    alt: "Red/Blue LEDs"
    title: "Glue 2 red LEDs for each blue into the acrylic to make purple"
  - url: /assets/images/ledtrans.jpg
    image_path: /assets/images/ledtrans.jpg
    alt: "LED Transistor"
    title: "Wire a transistor to control the LEDs together"
  - url: /assets/images/laser.jpg
    image_path: /assets/images/laser.jpg
    alt: "Laser Pen Core"
    title: "Remove the core of a laser pen from its housing and connect +ve/-ve wires"
  - url: /assets/images/lasertrans.jpg
    image_path: /assets/images/lasertrans.jpg
    alt: "Laser and LED transistor"
    title: "Start to assemble to Laser, LED transistor and LEDs together"
  - url: /assets/images/laserleds.jpg
    image_path: /assets/images/laserleds.jpg
    alt: "Power Laser"
    title: "Bind the LED +ve PIN to the silver housing with insulating tape and connect the +ve to resistors and the transistor"
  - url: /assets/images/connectors.jpg
    image_path: /assets/images/connectors.jpg
    alt: "Rifle Connectors"
    title: "Create matching colour wired from the Nano to make connections easier"
---
# Terminator T-800 Rifle Modification

A rifle modification for the Agora/Hachette T-800 1:2 size Endoskeleton model. This modification brings the standard (silent) gun to life with a number of options:

1. Random fire with realistic sounds and muzzle flash.
2. Optional Laser Pen addition to create phased plasma effect. **NB: Do not fit if using the gun as a toy. Lasers can damage eyes if fired into the face!**
3. Optional trigger to control manual firing.
4. Optional motion detection to automatically fire.

See the following video for an example of automatic random firing with phased plasma bolt effect (smoke/humidifier required for laser visibility).

{% include video id="efiEVk9kDKA" provider="youtube" %}

## Instructions

### Mandatory Parts

*NB: I do not endorse any of the supplier links here. These are what I used. You may have better sources.*

* [Arduino Nano](https://store.arduino.cc/products/arduino-nano). I used one from [Ebay](https://www.ebay.co.uk/itm/Nano-V3-0-Arduino-ATmega328-5V-16MHz-CH340-UNSOLDERED-HEADERS-UK-Stock-/323825474433) but also ran some tests using an official one from somewhere like [The PI Hut](https://thepihut.com/products/arduino-nano) which is *much more expensive* (but has pins soldered so works well on a breadboard).

* [Adafruit Sound Board](https://www.adafruit.com/product/2341) to store and play the gun sounds and an [Adafruit 2.5W Amp](https://www.adafruit.com/product/2130) to connect the sound board to speaker. There is also an [integrated version](https://www.adafruit.com/product/2210) but it only has 2Mb memory and the 9 sounds are stored as WAV files (for immediate playback) and are about 4MB in size.

* A speaker. I used [this 4 ohm 3 watt one](https://www.ebay.co.uk/itm/3W-4R-SPEAKER-3-watt-4-ohm-40mm-x-5mm-/224097819811) as it's quite thin. Be aware of "normal" speakers - they won't fit into the gun chamber.

* Red Superbright LEDs. I used these from [Ebay](https://www.ebay.co.uk/itm/264121902078)

* Blue Superbright LEDs. I used these from [Ebay](https://www.ebay.co.uk/itm/265202579069). Mixing blue and red together makes a brighter purple than [Purple LEDs](https://www.ebay.co.uk/itm/264121899689).

* Resistors to protect the LEDs from full voltage. The Arduino puts 5v to each IO pin which is too much for LEDs. Different colours require [different voltages](https://www.digikey.co.uk/en/resources/conversion-calculators/conversion-calculator-led-series-resistor). Using 5v supply from the Arduino, 2v (mid-range) forward voltage and 15mA (low) forward current gave me 200 ohm which would extend the life of red LEDs. Using the maximum voltage and current (2.1v, 30mA) gives 100 ohm which will be brighter. I used some 100 ohm I already had as the LEDs flash rather than illuminate permanently. [Ebay](https://www.ebay.co.uk/itm/1-4W-Metal-Film-Resistors-1-186-values-available-20-Pack-UK-Seller-Free-P-P-/263898843941) have many suppliers.

* Some AWG 24 wiring to connect things together. Either [multi-core](https://www.amazon.co.uk/dp/B07TT69PPV/) or [solid core](https://www.amazon.co.uk/gp/product/B08BZKVVH2/). These options provide much more than required, depending on your needs. You can also use [Dupont cables](https://www.ebay.co.uk/itm/224448044824) to minimise soldering but they can be prone to disconnecting when you fit them into the gun. I ended up using a mixture.

* Some Heat Shrink tubing. I bought [this example on Amazon](https://www.amazon.co.uk/dp/B08N5246YB) which is good. Alternatives from Ebay might be cheaper. Again much more than you need, but could be useful for other projects depending on your needs.

* A power source. Initially I used 4 x 1.5v AAA batteries, [holder](https://thepihut.com/products/4aa-holder) and [connector cable](https://thepihut.com/products/9v-cable), but they're quite heavy. See the alternative parts below.

* A switch to control whether the Arduino Nano is on or off. This one on [Ebay](https://www.ebay.co.uk/itm/Small-Mini-Black-On-Off-Rocker-Switch-Rectangle-SPST-12V-All-Quantities-/251390016446) matches the main on-off switch of the base.

* [Clear Acryllic](https://www.ebay.co.uk/itm/CLEAR-ACRYLIC-PERSPEX-ROD-SHAFT-BAR-VARIOUS-DIAMETERS-2MM-20MM-LENGTHS-1000-/272045612518) to fit in the gun muzzle and hold the LEDs.

You will also need a soldering iron and some solder to connect things together. Additionally a [hot-glue gun](https://www.hobbycraft.co.uk/black-mini-hot-melt-glue-gun/6389691000.html) from HobbyCraft will help glue things into place. I used blutac initially whilst trying to position everything. Replace with hot glue once you are happy with positioning.

### Alternative Parts:

* I eventually used an [Adafruit PowerBoost 500 Charger](https://www.adafruit.com/product/1944) and [LiPoly Battery](https://www.adafruit.com/product/258). They're lighter and can be recharged without opening up the gun. Make sure you match the +/-ve polarity. You may need to rewire to match using something like these [Micro JST wires](https://www.amazon.co.uk/dp/B07449V33P).

**NB: Be careful cutting LiPoly wires. Cut each wire one at a time and never short the 5v to ground (e.g. by cutting both together with metal wire cutters). Shorting takes no time to burn the circuitry of the battery out. Prolonged shorts can make the battery burst into flames.**

### Optional Parts:

* A [Laser Pen](https://www.ebay.co.uk/itm/10miles-Purple-Laser-Pen-Pointer-1MW-405NM-HIGH-POWER-Lazer-Light-Visible-Beam-/393378205587). You will need to dismantle it to get at the actual diode inside.

* A [TIP120](https://www.ebay.co.uk/itm/5-Pcs-TIP120-Darlington-Transistors-NPN-TO-220-/164713251024) Darlington Transistor to control the power to the laser pen. You cannot draw enough power from the Arduino IO pins to create a reasonable laser. The TIP120 transistor allows the Arduino to switch power to the laser directly from the power source.

* A resistor for the TIP220. I used these 2.7K-ohm from [EBay](https://www.ebay.co.uk/itm/1-4W-Metal-Film-Resistors-1-186-values-available-20-Pack-UK-Seller-Free-P-P-/263898843941?) to limit the Arduino IO pin output.

* Tactile button switch [like this one](https://www.adafruit.com/product/367) to fit behind the trigger in the rifle handle. A Dremel and hot glue is required to make space in the rifle's handle.

* [PIR Sensor](https://www.amazon.co.uk/dp/B07XLKTQMG) if you want the rifle to fire automatically when movement is detected.

## Wiring diagram

The [t800-rifle](https://github.com/jsware/t800-rifle) program for the Arduino supports LEDs, a laser pointer, trigger button and PIR sensor. I was also working on the HC-SR04 but it's quite bulky. The PIR works pretty well in my view.

{% include figure popup=true image_path="/assets/images/bread.jpg" alt="Breadboard Layout" caption="A breadboard is useful in checking everything works prior to soldering and fitting to the rifle" %}

A breadboard is useful for setting it all up to ensure you have the correct wiring before soldering it all together. Dupont cables can be helpful here. I started with the [ELEGOO Mega R3 Project Kit](https://www.amazon.co.uk/ELEGOO-Mega2560-Complete-Ultimate-controller/dp/B01IUZK3JO) if you want to play with electronics. It's expensive but contains lots of parts I can use on other projects.

## Fitting Electronics

You can see from the picture and video how the electronics can be fitted into the gun chamber. I started with 4 x AAA batteries, but they're quite heavy (as is a 9v battery) and pushes the electronics to the front of the rifle. This may put unnecessary weight when held by the endoskeleton.

{% include figure popup=true image_path="/assets/images/rifleaaa.jpg" alt="Rifle with AAA Batteries" caption="Fitting with AAA batteries means you have to open up the gun to replace them" %}

I reengineered to use a LiPoly battery and charger to reduce the weight and also so I didn't have to open up the rifle when the batteries are drained. A USB cable can be fitted plugged into the charger by removing the power clip at the back. See the charger with a blue light and the USB connector pointing downwards:

{% include figure popup=true image_path="/assets/images/riflepoly.jpg" alt="Rifle with Rechargeable LiPoly Battery" caption="Using a LiPoly battery can be recharged without opening up the gun" %}

The video below shows the push button fixed behind the trigger and the LiPoly version. You can see more electronics are behind the handle, making the rifle more balanced.

{% include video id="2Sevzvk_5gs" provider="youtube" %}

Once the electronics are put together the gun fires randomly, but pulling the trigger can make it fire manually. Power off/on again to return to random fire.

The Arduino Nano needs programming first in order to control its behaviour...

## Programming

Programming the Arduino Nano requires some tools. The program can be found on [GitHub](https://github.com/jsware/t800-rifle). To program your Arduino you will need to follow a few steps:

1. Use the [Arduino Getting Started Guide](https://www.arduino.cc/en/Guide) to install the Arduino IDE.
1. I use [Visual Studio Code](https://code.visualstudio.com/) and [PlatformIO](https://platformio.org/) for a better programming environment (which needs the Arduino IDE too). If you also have VS Code and PlatformIO you can open the project directly in VS Code.
1. Download the [t800-rifle](https://github.com/jsware/t800-rifle) program from GitHub.
1. Once you understand how to load simple programs (from the getting started and tutorials) to an Arduino Nano, you can load this modification program to control the LEDs. I would recommend trying out the standard "Blink" program first to ensure you can in principle compile and transfer it to the Nano. Ardunio basics are beyond the scope of this page, but there is plenty of help available via [Google](https://www.google.com/search?q=arduino+hello+world).
1. If you only have the Arduino IDE, do the following to compile and load this modification's program:
  * Create a new project `'t800-rifle'` and copy the following files from the GitHub project into it:
  * `src/main.cpp` (Delete and rename this to the main `t800-rifle.ino` file in your project)
  * `src/t800rifle.cpp`
  * `src/diags.cpp`
  * `include/diags.h`
  * `include t800rifle.h`
  * `include/ver_info.h`
  * **You must delete the original `t800-rifle.ino` file and rename `main.cpp` to `t800-rifle.ino`**
  * The Arduino IDE should now be able to compile and transfer the program to the Nano.
1. The rifle only uses the [SoftwareSerial](https://www.arduino.cc/en/Reference/softwareSerial) inbuilt library. If you want to try enabling the ultrasonic sensor too, you will need additional libraries (SR04).

Check out the Arduino IDE for a little 'easter egg'...

You will also need to load the WAV files into the sound card.

### Sound Effect Files

The sounds folder in the above project contains `.m4a` files for various muzzle flashes. Also a script `m4a2wav.sh` which creates `Tnn.WAV` for each `nn.M4A` file. WAV files take up more space, but play faster on the AdaFruit SFX board.

Run the `m4a2wav.sh` script to create the T*.WAV files and then copy them to the AdaFruit SFX board as specified in the documentation.

The script `wav2sfx.sh` and `wav2sfx.cmd` copy the T*.WAV files to the Adafruit SFX board. Note that Mac OS (un)helfully creates a `.fseventsd` file when the SFX board is mounted which can mess up with directory entry positioning. File are assumed to be copied in sequence so file directory entry 0 is `T00.WAV`, entry 1 is `T01.WAV` etc.

Even if you delete `.fseventsd`, it takes entry 0 in the directory, so Adafruit plays the wrong file.

Only reliable solution I found ATM is to mount the USB on Windows, delete all the files and use the Windows script to copy the files one by one in order.

Or use Linux if available to do the same.

If somehow the SFX board file system gets messed up, follow [these instructions](https://learn.adafruit.com/adafruit-audio-fx-sound-board/downloads) to wipe the card. Note reformatting with the normal operating system format commands will likely render the file system unreadable by the SFX board itself. I also found you need a decent USB cable otherwise it will corrupt the card.

### Building the Laser

**NB: Do not fit if using the gun as a toy. Lasers can damage eyes if fired into the face!**

I would suggest only doing this if you have an aptitude for electronics. You will need to dismantle the laser pen to remove the electronics and then solder resistors, along with red and blue LEDs.

{% include gallery caption="Building up the laser centre of the rifle" %}

1. Glue 2 red LEDs for each blue into the acrylic to make purple.
1. Wire a transistor to control the LEDs together.
1. Remove the core of a laser pen from its housing and connect +ve/-ve wires.
1. Start to assemble to Laser, LED transistor and LEDs together.
1. Bind the LED +ve PIN to the silver housing with insulating tape and connect the +ve to resistors and the transistor
1. Create matching colour wired from the Nano to make connections easier. I used red/black for +ve/ground, green for laser and blue for LEDs.

# Putting it all together

Hopefully this will help any budding modellers to make modifications to their T-800 Endoskeleton. With this rifle modification, my [T-800 Eyes](https://www.jsware.io/t800-eyes/) modification and the [excellent modification](https://t800controller.com/demos.html) from Alex McPherson it creates an epic combination.

{% include video id="icEJ3l1Op4s" provider="youtube" %}
