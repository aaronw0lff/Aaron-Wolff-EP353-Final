I built a program to easily generate the sub frequency component of a synthesized kick drum, by using user-entered values, in Hertz, and milliseconds. This is a very precise, and reliable way to create this element, which is an important enough factor in a mix to necessitate this tool.

The instructions prompt you for values while running the program, 
as it guides you through the process, andI will describe the parameters needed to create your intended kick here:


    Initial Frequency: This is the value of the starting point of the initial transient's pitch descent, in Hz. 150 to 500 is a generally acceptable range for a standard kick.

    Attack Time: This is the time in milliseconds from the Initial Frequency to the Resting Frequency, which will be the primary low frequency of the kick. Generally, the higher the Initial Frequency, the shorter the Attack Time should be. I recommend values from 10 to 100 milliseconds.

    Resting Frequency: The primary sub component of your kick. If your kick is meant to be tuned, like an 808, or otherwise pitched kick drum, this will be the note that you hear. To find references for what number in Hz your intended note will be, check the included file; "Notename_to_Hz_table.png". 

         - Here you will be asked if you want your kick to escend past your Resting Frequency, and down to 20 Hz, the lowest pitch humans can discern. If you want to make an 808, or otherwise pitched kick, you should type "n" for no. Otherwise, type "y" for yes. - 

    Rest Time: You will only need this value if you decide to descend. This is the amount of time that your kick will stay on your Resting Frequency before it descends. I recommend shorter values, from 0, for a completely unpitched kick, to 100, for a more pitched, but still short kick. 

    Fade Time: This is the amount of time that the tail will take to fade out. If you chose to descend, Fade Time will control the pitch descent to 20 Hz, and also the amplitude fade out to silence. I recommend values from 50, for a very tight kick, to 1000, for a 1-second long 808.


The program will output a file named "K_I_C_C.wav" at 192,000 sample rate. In order to save your kick, and create more kicks with this program, you must rename your output "K_I_C_C.wav" file, because the program will write a new file named exactly "K_I_C_C.wav" every time it completes its process.

In order to run this program, you must install the libsndfile library (http://www.mega-nerd.com/libsndfile/), and the PortAudio library: (http://www.portaudio.com/). You must also have a wavetable of a single cycle of a 1 Hz sine wave, at 192,000 Hz sample rate inside this folder, called "192sinetable.wav". If you want to use an altername wavetable, it must still be 192,000 sample rate, and be named "192sinetable.wav"

You may compile the project by navigating to this folder in the command line, and using the command: "gcc SubKickGen.c AmpEnvelope.c PitchEnvelope.c Wavetable.c -o SubKickGen.o -lsndfile -lportaudio -O0",
and then run it using: "./SubKickGen.o". 

Enjoy!