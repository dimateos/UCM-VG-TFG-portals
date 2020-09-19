# GRAPHICS ENGINE WITH PORTALS TO SIMULATE NON-EUCLIDEAN 3D SCENES

* **Diego Mateos Arlanzón**
* DEGREE IN VIDEOGAME DEVELOPMENT
	* FACULTAD DE INFORMÁTICA /  UNIVERSIDAD COMPLUTENSE DE MADRID
* Degree Final Dissertation in Videogames Development
	* Academic year 2019-2020 (*september*)
	* Director: *Ana Gil Luezas*

## Index
- [GRAPHICS ENGINE WITH PORTALS TO SIMULATE NON-EUCLIDEAN 3D SCENES](#graphics-engine-with-portals-to-simulate-non-euclidean-3d-scenes)
	- [Index](#index)
	- [- Abstract -](#abstract)
		- [Keywords](#keywords)
	- [Introduction](#introduction)
		- [Motivation](#motivation)
		- [Goals and work plan](#goals-and-work-plan)
		- [Structure of the memory](#structure-of-the-memory)
	- [Conclusions and future work](#conclusions-and-future-work)
		- [Conclusions](#conclusions)
		- [Future work](#future-work)
	- [Bibliography](#bibliography)

## - Abstract -
This project focuses on the simulation of 3D scenes in which portals may exist. A portal is a physical phenomenon that affects the space of the scene, in such a way that the properties necessary to continue to be considered Euclidean are no longer fulfilled. Portals manifest in pairs and essentially connect two separate surfaces from said space; this consequently allows you to see and move through them, regardless of distance.

The main objective of this project is to generate a complete, rigorous and self-contained public resource about the inner workings and implementation of these portals in a simple graphic engine. In order to develop the project, it has been necessary to carry out extensive research on existing implementation cases (mainly on the Portal videogame saga), and the technologies available to develop my own version.

In this dissertation, everything necessary to understand the phenomenon of the portals is explained in an accessible and didactic way. Even the fundamentals of computer graphics and specifically OpenGL are introduced, so that a person outside the subject, if they wish, can also follow the technical part of the explanation. Regarding my own implementation, it is fully detailed, but the specific exposition about the portals remains sufficiently abstract to be easily reproducible in the architecture of any other engine.

### Keywords
Graphics engine, Portals, Rendering, 3D Scene, Computer graphics, OpenGL, Shader.

## Introduction
In this brief chapter, the motivations behind the project, its specific objectives and the followed work plan are all presented. The complete memory structure is also schematically explained.

The associated source code can be found at: 	https://github.com/dimateos/TFG_Portals

### Motivation
Portals are an interesting phenomenon for which examples can be found in various productions from all kinds of industries: animation, film, video games, etc. Among these, the portals used in videogames stand out, since their properties are normally rigorously defined and simulated in real time. But unfortunately, its technical implementation is complex and the information available about it is limited and scattered (and totally non-existent in Spanish). From this fact arises the desire to carry out extensive research in order to be able to build my own implementation. Furthermore, the intention in this project is to start from scratch and create a simple graphics engine; this allows me to expand my knowledge of computer graphics and engines in general.

The final purpose of the project is to solve the lack of concrete information initially encountered. This is intended to be achieved by writing a document that explains the inner workings and the implementation of the portals in a simple graphics engine. So this dissertation itself, together with the associated source code of my implementation, would form a public resource that stands out for being complete, rigorous and self-contained. To make the explanation as accessible and didactic as possible, even the fundamentals of computer graphics and the technologies used are introduced so that a person outside the subject, if they wish, can also follow the technical part of the exposition. Regarding my own implementation, it is detailed in full, so that it may be consulted in a useful way. And finally, the concrete explanation regarding the portals remains abstract enough to be easily reproducible in the architecture of any other engine.

### Goals and work plan
The objectives of this project can be listed in order of priority. The probability of being unable to complete all of them due to a higher than anticipated workload is taken into account. This same order has been followed as a work plan:

1. Study how portals and existing implementation methods work.
2. Study the fundamentals of computer graphics required to implement them.
3. Develop a simple reusable graphics engine with sufficient logic capabilities.
4. Implement an interactive 3D scene as a base for the development.
5. Implement the portals progressively, starting with its most basic properties, to the most complex ones.
6. Write the part of the dissertation referring to the fundamentals of computer graphics, to make it more accessible, and to ease the later explanation.
7. Write the part of the dissertation referring to the complete inner workings and implementation of the portals, as didactic and useful as possible.
8. Write the part of the dissertation referring to the architecture of the engine itself, so that it is possible to consult the source code in a productive way.
9. Implement improvements to the graphics engine, mainly support for lighting and for importing models or complete scenes.
10. Develop more impressive scenes, using the portals in surprising and interesting ways.

### Structure of the memory
> This section refers to the written part of the dissertation. You can find it under the [docs](https://github.com/dimateos/TFG_Portals/tree/master/Docs) folder.

This document tries to be very accessible and therefore part of it may be redundant information for a person who already knows the subject. Specifically, chapters **`[2]`** and **`[4]`** referring to computer graphics, can be read over if an explanation of their state of the art and fundamentals is not required. Chapter **`[3]`** briefly details the architecture of the engine itself, if this is not of interest, it may be skipped and consulted in case of doubt. Finally, the extensive chapters **`[5]`** and **`[6]`** explain the state of the art of the portals and their inner workings and implementation completely.

## Conclusions and future work
This concise final chapter presents the conclusions of the project regarding its objectives and work plan. Possible ideas for future work are also added.

### Conclusions
Once the project is finished, it is a good time to reflect and make an assessment of the work completed and what has been learned during itself. From the point of view of the objectives listed in section `[Goals and work plan]`, **except the last two**, all have been fulfilled satisfactorily on time. This result is due to the fact that from the beginning, in the work plan, the possibility of not being able to achieve all the objectives was already taken into account, and therefore they have been pursued in order of priority.

Regarding the **completed objectives**, some have been more complicated than anticipated. The work related to the study of *OpenGL* **`[2]`** and the implementation of the engine **`[3]`**  has taken a lot longer than expected, but I am still satisfied with the learning. The amount of time invested in research **`[1]`** and development **`[5]`** of the portals had already been anticipated, although the final implementation of the recursion has taken longer as it has progressively improved. I think that the level of detail in the writing of the dissertation **`[6,7,8]`** has been higher than initially intended, and with it the volume of pages and work, but I am very happy with the result. The interactivity of the implemented scene **`[4]`** has grown continuously along with the writing of content, and has reached a level of interaction and configuration more than remarkable. Portal recursion has been especially difficult to explain **`[7]`** and has required a large number of figures.

The objectives related to the implementation of improvements in the graphics engine **`[9]`** and the development of more interesting scenes for the portals **`[10]`** have not been achieved.  These lower priority objectives have been discarded due to lack of time and *necessity*. The current graphics engine has managed to generate all the images for the dissertation, and the simple textures without lighting themselves add clarity and simplicity to the result. Likewise, the importing of models has not been estimated and simple geometry objects have been used. The final scene that focuses on interactivity and utility, allows you to configure and display each of the characteristics of the portals in real time. The portals are not used in *surprising* ways, but the configuration options themselves are much more didactic and *interesting* than initially planned.

### Future work
This section describes possible ideas that add more value to the project. In addition to the two unfulfilled objectives, other interesting ideas have emerged throughout the execution of this project. Here they are listed below in no particular order:

*Previous objective*:
* Implement improvements to the graphics engine, mainly support for lighting and for importing models or complete scenes.
* Develop more impressive scenes, using the portals in surprising and interesting ways. For example, with more than a couple of portals.

*Others*:
* Development of a graphical interface that facilitates interaction with the scene. This would allow the user to have a better experience, without needing to know the controls.
* Development of an alternative implementation based on stencil-buffer, with the ability to activate it in real time. This would allow a more direct comparison between both implementation methods.
* Development of various optimizations, these could be interesting for cases in which relatively complex scenes are simulated. For example: detection of portals outside the screen space to speed up the rendering process or detection of the absence of overlapping between portals in screen space to speed up the recursion process.
* Creation of a Shader that optimizes the management of portals textures. Instead of saving a texture with the entire scene and then assigning it to the portal correctly, it may be possible to pre-save it in an *optimized* way so that the assignment is straightforward (requiring no special processing).

## Bibliography
1. Diego Mateos Arlanzón. TFG - MOTOR GRÁFICO CON PORTALES PARA SIMULAR ESCENAS 3D NO EUCLIDIANAS. Repositorio del proyecto. https://github.com/dimateos/TFG_Portals, 2020
2. Portal: No Escape. Live Action Short Film by Dan Trachtenberg. https://www. youtube.com/watch?v=4drucg1A6Xk, 2011
3. Portal. Selling point reference. https://store.steampowered.com/app/400/ Portal, 2007
4. Computer History Museum (Mountain View, CA). The Utah Teapot. https:// www.computerhistory.org/revolution/computer-graphics-music-and-art/15/206, 2020
5. Unity Technologies. Unity official webpage. https://unity.com/es, 2020
6. Epic Games, Inc. Unreal Engine official webpage. https://www.unrealengine.com /en-US/, 2020
7. GIGABYTE productos. Tarjeta gráfica GeForce RTX 2060. https://www.gigabyte .com/es/Graphics-Card/GV-N2060GAMING-OC-6GD#kf, 2018
8. Nvidia Corporation. Nvidia official webpage. https://www.nvidia.com/es-es/ about-nvidia/, 2020
9. GIGABYTE. Gigabyte official webpage. https://www.gigabyte.com/About, 2020
10. Khronos Group Inc. OpenGL - The Industry's Foundation for High Performance Graphics.  https://www.opengl.org/, 2020
11. Khronos Group Inc. Khronos official webpage. https://www.khronos.org/, 2020
12. OpenGL Wiki contributors. Language bindings. https://www.khronos.org /opengl/wiki/Language_ bindings, 2020
13. Standard C++ Foundation. Standard C++. https://isocpp.org/, 2020
14. Khronos Group Inc. Vulkan Overview. https://www.khronos.org/vulkan/, 2020
15. Khronos Group Inc. Vulkan Overview slides 2016. https://www.khronos.org /assets/uploads/developers/library/overview/vulkan-overview.pdf, 2016
16. Microsoft. Getting started with Direct3D. https://docs.microsoft.com/en-us/ windows/win32/getting-started-with-direct3d, 2018
17. Nvidia Gameworks. Transitioning from OpenGL to Vulkan. https://developer.nvidia.com/transitioning-opengl-vulkan, 2016
18. UNIVERSIDAD COMPLUTENSE DE MADRID (UCM). FACULTAD DE INFORMÁTICA (FDI). Ficha docente de la asignatura IG I. http://web.fdi. ucm.es/UCMFiles/pdf/FICHAS_DOCENTES/2017/1362.pdf, 2017-2018
19. OpenGL Wiki contributors. History of OpenGL. https://www.khronos.org/ opengl/wiki/History_of_OpenGL, 2020
20. UNIVERSIDAD COMPLUTENSE DE MADRID (UCM). FACULTAD DE INFORMÁTICA (FDI). Ficha docente de la asignatura IG II. http://web.fdi. ucm.es/UCMFiles/pdf/FICHAS_DOCENTES/2017/1372.pdf, 2017-2018
21. OGRE. OGRE - Open Source 3D Graphics Engine. https://www.ogre3d.org/, 2020
22. OpenGL Wiki contributors. Shader. https://www.khronos.org/opengl/wiki/ Shader, 2019
23. OpenGL Wiki contributors. Core Language (GLSL). https://www.khronos.org/ opengl/wiki/Core_Language_(GLSL), 2019
24. Joey de Vries (https://twitter.com/JoeyDeVriez). Learn OpenGL.  https:// learnopengl.com/, 2020
25. Joey de Vries.  Kendall & Welling publishing. Learn OpenGL - Graphics Programming.  https://learnopengl.com/book/book_pdf.pdf, 2020
26. Joey de Vries. learnopengl.com code repository. https://github.com/ JoeyDeVries/ LearnOpenGL, 2020
27. Creative Commons. Attribution-NonCommercial 4.0 International. https:// creativecommons.org/licenses/by-nc/4.0, 2016
28. Creative Commons. Attribution 4.0 International. https://creativecommons.org/ licenses/by/4.0, 2016
29. Alexander Overvoorde. Modern OpenGL Guide. https://open.gl/, 2019
30. Alexander Overvoorde. open.gl content repository. https://github.com/Overv/ Open.GL, 2019
31. Creative Commons. Attribution-ShareAlike 4.0 International. https://creative commons.org/licenses/by-sa/4.0/, 2016
32. OpenGL Wiki contributors. OpenGL Wiki. https://www.khronos.org/ opengl/wiki/, 2018
33. OpenGL Mathematics. GL 0.9.9 API documentation, https://glm.g-truc.net/ 0.9.9/api/modules.html, 2020
34. Simple DirectMedia Layer. SDL 2.0 wiki frontpage. https://wiki. libsdl.org/FrontPage, 2018
35. GLFW. GLFW - An OpenGL library. https://www.glfw.org/, 2020
36. glad. GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specs. https://github.com/Dav1dde/glad, 2020
37. OpenGL Wiki contributors. OpenGL Loading Library. https://www.khronos.org/ opengl/wiki/OpenGL_Loading_Library, 2019
38. OpenGL Mathematics (GLM). A C++ mathematics library for graphics programming. https://glm.g-truc.net/0.9.9/index.html, 2020
39. stb_image. Image loading/decoding from file/memory: JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC. https://github.com/nothings/stb, 2020
40. Microsoft. IDE de Visual Studio. https://visualstudio.microsoft.com/es/, 2020
41. Linus Torvalds. Git, free and open source. https://git-scm.com/, 2020
42. GitHub, Inc. About. https://github.com/about, 2020
43. Update method. Robert Nystrom, Game Programming Patterns. https://game programmingpatterns.com/update-method.html, 2014
44. Game loop. Robert Nystrom, Game Programming Patterns. https://game programmingpatterns.com/game-loop.html, 2014
45. Delta time. Cristian Barrio (BYC), Parallelcube. https://www.parallelcube.com/ es/2017/10/25/por-que-necesitamos-utilizar-delta-time/, 2017
46. Event-Subscriber pattern. Alexander Shvets (refactoring.guru), Dive Into Design Patterns. https://refactoring.guru/design-patterns/observer, 2020
47. Paul E. Black and Algorithms and Theory of Computation Handbook, CRC Press LLC, 1999. Tree. Dictionary of Algorithms and Data Structures. https://xlinux.nist.gov/dads/HTML/tree.html, 2017
48. Wikipedia contributors. Tree traversal. In Wikipedia, The Free Encyclopedia. https://en.wikipedia.org/w/index.php?title=Tree_traversal&oldid=968976983, 2020
49. Sumanta Guha; Computer Graphics through OpenGL; Segunda edición, CRC Press, 2015
50. Peter Shirley, Steve Marschner; Fundamentals of Computer Graphics; Third Edition, CRC Press, 2009
51. OpenGL Wiki contributors. Tesselation. https://www.khronos.org/ opengl/wiki/Tessellation, 2019
52. Department of Mathematics. University of Maryland. Gimbal Lock. http://www.math.umd.edu/~immortal/MATH431/lecturenotes/ch_gimballock.pdf, 2018
53. Wolfram mathworld. Quaternion. https://mathworld.wolfram.com/ Quaternion.html, 2020
54. Blender Documentation Team. The Blender 2.90 Manual. Licensed under CC-BY-SA v4.0. https://docs.blender.org/manual/en/latest/editors/3dview/naviga te/ views.html, 2020
55. Techopedia. First Person Shooter (FPS). https://www.techopedia.com/ definition/241/first-person-shooter-fps, 2011
56. Valve Corporation. Official webpage. https://www.valvesoftware.com/es/, 1996-2020
57. Portal 2. Official webpage. https://www.thinkwithportals.com/, 2011
58. Narbacular Drop. Overview from official webpage. http://www.nuclearmonkey software.com/narbaculardrop.html?overview.html, 2004-2008
59. DigiPen Institute of Technology. Official webpage. https://www.digipen.edu/, 2020
60. Antichamber. Official webpage. http://www.antichamber-game.com/, 2013
61. Narbacular Drop available documents. Including Technical Design, Game Design and Postmortem. http://www.nuclearmonkeysoftware.com/narbaculardrop.html, 2005
62. DigiPen Institute of Technology. Narbacular Drop Technical Design Document. http://www.nuclearmonkeysoftware.com/documents/narbacular_drop_technical_design_document.pdf, 2004
63. Portal Problems - Lecture 11 - CS50's Introduction to Game Development 2018. CS50, Harvard University. https://www.youtube.com/watch?v=ivyseNMVt-4, 2018
64. Creative Commons. Attribution-NonCommercial-ShareAlike 4.0 International Public License. https://creativecommons.org/licenses/by-nc-sa/4.0/, 2016
65. Game Developers Conference (GDC). Portal 2: Creating a Sequel to a Game That Doesn't Need One. https://www.youtube.com/watch?v=BYFvwbby2YM, 2016
66. The Portal Wiki. Unofficial wiki. https://theportalwiki.com/wiki/Main_Page, 2020
67. Geoff Keighley. Documentary: The Final Hours of Portal 2. http://www.thefinalhoursofportal2.com/, 2011
68. Sebastian Lague. Coding Adventure: Portals in Unity. Licensed under MIT License. https://github.com/SebLague/Portals, 2020
69. Wolfram mathworld. Plane. https://mathworld.wolfram.com/Plane.html, 2020
70. Eric Lengyel. Terathon Software. Oblique View Frustum Depth Projection and Clipping. Published in Journal of Game Development, Vol. 1, No. 2. http://www.terathon.com/lengyel/Lengyel-Oblique.pdf, 2005
