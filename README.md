# ivry_udp_bridge
 An UDP interface for iVRy that supports OpenTrack. It gives you basic freedom to move around the room!

### Usage
Place the .exe in \Steam\steamapps\common\iVRy\bin\win64, set the tracking to "Custom" in the iVRy settings, restart SteamVR and activate OpenTrack. It should kick in right away (Well, as long as you have OpenTrack actually tracking something).

Be sure to check that you are using the "UDP over network" output interface in OpenTrack, and that it was configured to send packets to 127.0.0.1 at port 8021.

When starting up for the first time, the app will create a file called `udp_bridge_config.ini` next to itself. Within it, you can configure the port number and adjust sensetivity for X, Y and Z axes respectively. For example, a config with Y axis disabled will look like that: `8021 0.100000 0.000000 -0.100000`.

[Releases](https://github.com/AXKuhta/ivry_udp_bridge/releases)
