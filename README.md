# lfwaf
Literally "Lightest filter wheel and focuser". This project aim to design a complete system based on indy library, Arduino like controller and 3D prints in order to get the less heavy focuser and filter wheel for Newton astro-photography.

In parralel to the Arduino code, an indi driver is developped under ~/Projects/indi/examples/lfwaf. You can refer to https://indilib.org/develop/developer-manual/163-setting-development-environment.html for indi driver dev 
To call the inidiserver during devlopment, use "indiserver -v ~/Projects/indi/examples/lfwaf/lfwaf" and open an indi client, I used Kstars. From Kstars, use "Tools|Device|Device Manager", Select "Client Tab" and a connection to the host (usualy localhost) on port 7624.
