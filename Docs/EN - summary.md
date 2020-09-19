# GRAPHICS ENGINE WITH PORTALS TO SIMULATE NON-EUCLIDEAN 3D SCENES

* **Diego Mateos Arlanzón**
* DEGREE IN VIDEOGAME DEVELOPMENT
	* FACULTAD DE INFORMÁTICA /  UNIVERSIDAD COMPLUTENSE DE MADRID
* Degree Final Dissertation in Videogames Development
	* Academic year 2019-2020 (*september*)
	* Director: *Ana Gil Luezas*

## - Abstract -
This project focuses on the simulation of 3D scenes in which portals may exist. A portal is a physical phenomenon that affects the space of the scene, in such a way that the properties necessary to continue to be considered Euclidean are no longer fulfilled. Portals manifest in pairs and essentially connect two separate surfaces from said space; this consequently allows you to see and move through them, regardless of distance.

The main objective of this project is to generate a complete, rigorous and self-contained public resource about the inner workings and implementation of these portals in a simple graphic engine. In order to develop the project, it has been necessary to carry out extensive research on existing implementation cases (mainly on the Portal videogame saga), and the technologies available to develop my own version.

In this dissertation, everything necessary to understand the phenomenon of the portals is explained in an accessible and didactic way. Even the fundamentals of computer graphics and specifically OpenGL are introduced, so that a person outside the subject, if they wish, can also follow the technical part of the explanation. Regarding my own implementation, it is fully detailed, but the specific exposition about the portals remains sufficiently abstract to be easily reproducible in the architecture of any other engine.

## Keywords
Graphics engine, Portals, Rendering, 3D Scene, Computer graphics, OpenGL, Shader.

## Introduction
In this brief chapter, the motivations behind the project, its specific objectives and the followed work plan are all presented. The complete memory structure is also schematically explained.

The associated source code can be found at: 	https://github.com/dimateos/TFG_Portals

## Motivation
Portals are an interesting phenomenon for which examples can be found in various productions from all kinds of industries: animation, film, video games, etc. Among these, the portals used in videogames stand out, since their properties are normally rigorously defined and simulated in real time. But unfortunately, its technical implementation is complex and the information available about it is limited and scattered (and totally non-existent in Spanish). From this fact arises the desire to carry out extensive research in order to be able to build my own implementation. Furthermore, the intention in this project is to start from scratch and create a simple graphics engine; this allows me to expand my knowledge of computer graphics and engines in general.

The final purpose of the project is to solve the lack of concrete information initially encountered. This is intended to be achieved by writing a document that explains the inner workings and the implementation of the portals in a simple graphics engine. So this dissertation itself, together with the associated source code of my implementation, would form a public resource that stands out for being complete, rigorous and self-contained. To make the explanation as accessible and didactic as possible, even the fundamentals of computer graphics and the technologies used are introduced so that a person outside the subject, if they wish, can also follow the technical part of the exposition. Regarding my own implementation, it is detailed in full, so that it may be consulted in a useful way. And finally, the concrete explanation regarding the portals remains abstract enough to be easily reproducible in the architecture of any other engine.

## Goals and work plan
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

## Structure of the memory
> This section refers to the written part of the dissertation. You can find it under the [docs](https://github.com/dimateos/TFG_Portals/tree/master/Docs) folder.

This document tries to be very accessible and therefore part of it may be redundant information for a person who already knows the subject. Specifically, chapters [2] and [4] referring to computer graphics, can be read over if an explanation of their state of the art and fundamentals is not required. Chapter [3] briefly details the architecture of the engine itself, if this is not of interest, it may be skipped and consulted in case of doubt. Finally, the extensive chapters [5] and [6] explain the state of the art of the portals and their inner workings and implementation completely.

