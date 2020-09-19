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
