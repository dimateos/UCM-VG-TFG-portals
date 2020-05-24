# Portals Prototyped

All the portals mechanics have been implemented, including the most complex ones: *oblique proyection, recursion and object slicing*. The code is in a **prototype state** as there is a lot to improve.regarding the graphics capabilities and logic arquitecture.

Scene description:
* Full free camera movement control
* A few colored props and platforms
* Two portals: one has recursion and can be moved
	* *Atm* the have no frames so the slicing can be better appreciated
	* To see the slicing better I suggest moving the portal next to each other
	* Purple textures indicate the end of teh recursion
* One panel *in-scene* showing the last frame
	* This shows renderframe usage vs portal recursion which is done each frame

Interesing controls:
* WASD + mouse: free movement
* ALT: free/capture cursor
* ESC: quit
* L: show/hide virtual portal cameras axes
* K: start/stop controling the portal to move/rotate it locally to test any portal set up
	* T: toggle between control movement or rotation (Q / E for roll)
	* R: reset position or rotation
	* This controls can also affects player body but not camera
* O: switch portal rendering options (correct, unmapped camera texture or inactive)
* P + 1-9: switch post processing modes
