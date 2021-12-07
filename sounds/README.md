# Sound Effect Files

This folder contains the `.m4a` files for various muzzle flashes. Also a script `m4a2wav.sh` which creates `Tnn.WAV` for each `nn.M4A` file. WAV files take up more space, but play faster because on the AdaFruit SFX board.

Run the `m4a2wav.sh` script to create the T*.WAV files and then copy them to the AdaFruit SFX board as specified in the documentation.

The script `wav2sfx.sh` and `wav2sfx.cmd` copy the T*.WAV files to the Adafruit SFX board. Note that Mac OS (un)helfully creates a `.fseventsd` file when the SFX board is mounted which can mess up with entry positioning (files are assumed) to be copied in sequence so file 0 is `T00.WAV`, file 1 is `T01.WAV` etc.

Even if you delete `.fseventsd`, it takes position 0 in the file order, so Adafruit plays the wrong file.

Only reliable solution ATM is to mount the USB on Windows, delete all the files and use the Windows script to copy the files one by one in order.

Or us Linux if available to do the same.
