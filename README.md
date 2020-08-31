# ivry_udp_bridge
 An UDP interface for iVRy that supports OpenTrack.

Place the .exe in \Steam\steamapps\common\iVRy\bin\win64, set the tracking to "Custom" in the iVRy settings, restart SteamVR and activate OpenTrack. It should kick in right away (Well, as long as you have OpenTrack actually tracking something).

Be sure to check that you are using the "UDP over network" output interface in OpenTrack, and that it was configured to send packets to 127.0.0.1 at port 8021.

It gives you basic freedom to move around the room! Though you might want to disable the Y-axis in OpenTrack `default.ini` profile (Open it in notepad and edit `y-max-value=` to be `0`).

[Releases](https://github.com/AXKuhta/ivry_udp_bridge/releases)
