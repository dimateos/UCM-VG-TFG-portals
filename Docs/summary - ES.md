# MOTOR GRÁFICO CON PORTALES PARA SIMULAR ESCENAS 3D NO EUCLIDIANAS

* **Diego Mateos Arlanzón**
* GRADO EN DESARROLLO DE VIDEOJUEGOS
	* FACULTAD DE INFORMÁTICA /  UNIVERSIDAD COMPLUTENSE DE MADRID
* Trabajo Fin de Grado en Desarrollo de Videojuegos
	* Curso académico 2019-2020 (*Septiembre *)
	* Directora: *Ana Gil Luezas*

## Indice
- [MOTOR GRÁFICO CON PORTALES PARA SIMULAR ESCENAS 3D NO EUCLIDIANAS](#motor-gr%C3%A1fico-con-portales-para-simular-escenas-3d-no-euclidianas)
	- [Indice](#indice)
	- [- Resumen -](#resumen)
		- [Palabras clave](#palabras-clave)
	- [Introducción](#introducci%C3%B3n)
		- [Motivación](#motivaci%C3%B3n)
		- [Objetivos y plan de trabajo](#objetivos-y-plan-de-trabajo)
		- [Estructura de la memoria](#estructura-de-la-memoria)
	- [Conclusiones y trabajo futuro](#conclusiones-y-trabajo-futuro)
		- [Conclusiones](#conclusiones)
		- [Trabajo futuro](#trabajo-futuro)
	- [Bibliografía](#bibliograf%C3%ADa)

## - Resumen  -
Este proyecto se centra en la simulación de escenas 3D en las que pueden existir portales. Un portal es un fenómeno físico que afecta al espacio de la escena, de tal forma que las propiedades necesarias para poder seguir siendo considerada euclidiana dejan de cumplirse. Los portales se manifiestan por pares y esencialmente conectan dos superficies separadas de dicho espacio; esto consecuentemente permite ver y desplazarse a través de ellos, independientemente de la distancia.

El objetivo principal de este proyecto es generar un recurso público completo, riguroso y autocontenido, sobre el funcionamiento y la implementación de estos portales en un motor gráfico sencillo. Para poder desarrollar el proyecto, ha sido necesario realizar una amplia investigación sobre casos existentes de implementación (principalmente sobre la saga de videojuegos Portal), y las tecnologías disponibles para elaborar mi propia versión.

En esta memoria se explica de forma accesible y didáctica todo lo necesario para comprender el fenómeno de los portales. Incluso se introducen los fundamentos de la informática gráfica y concretamente de OpenGL, para que una persona ajena al tema, si lo desea, pueda seguir también la parte técnica de la explicación. Respecto a mi implementación propia, se aporta íntegramente el código fuente, y la exposición concreta sobre los portales se mantiene suficientemente abstracta para ser reproducible con facilidad en la arquitectura de cualquier otro motor.

### Palabras clave
Motor gráfico, Portales, Renderizado, Escena 3D, Informática gráfica, OpenGL, Shader.

## Introducción
En este breve capítulo se presentan las motivaciones detrás del proyecto, sus objetivos concretos y el plan de trabajo seguido. También se explica esquemáticamente la estructura completa de la memoria.

El código fuente asociado a este proyecto se puede encontrar en: 	https://github.com/dimateos/TFG_Portals

### Motivación
Los portales son un fenómeno interesante del que se pueden encontrar ejemplos en diversas producciones de todo tipo de industrias: animación, cine, videojuegos, etc. Entre estos destacan los portales utilizados en videojuegos, ya que normalmente sus propiedades se definen rigurosamente y se simulan en tiempo real. Pero por desgracia, su implementación técnica es compleja y la información disponible acerca de ella es limitada y dispersa (y totalmente inexistente en español). De este hecho surge el deseo de realizar una extensa investigación para poder llevar a cabo el desarrollo de mi propia implementación. Además, la intención en este proyecto es partir desde cero y crear un motor gráfico sencillo; esto permite ampliar mis conocimientos sobre la informática gráfica y motores en general.

El propósito final del proyecto es solventar la falta de información concreta encontrada inicialmente. Esto se pretende conseguir mediante la redacción de un documento que explique el funcionamiento y la implementación de los portales en un motor gráfico sencillo. Así, esta memoria en sí misma, junto con el asociado código fuente de mi implementación, compondrían un recurso público que destaca por ser completo, riguroso y autocontenido. Para que la explicación sea lo más accesible y didáctica posible, incluso se introducen los fundamentos de la informática gráfica y la tecnologías utilizadas para que una persona ajena al tema, si lo desea, pueda seguir también la parte técnica de la exposición. Respecto a mi implementación propia, se detalla íntegramente, para que pueda ser consultada de forma útil. Y finalmente la explicación concreta referente a los portales se mantiene suficientemente abstracta para ser reproducible con facilidad en la arquitectura de cualquier otro motor.

### Objetivos y plan de trabajo
Los objetivos de este proyecto se pueden listar ordenados por prioridad. Se tiene en cuenta la posibilidad de no poder completarlos todos debido a una carga de trabajo superior a la anticipada. Este mismo orden se ha seguido como plan de trabajo:

1. Estudiar cómo funcionan los portales y métodos de implementación existentes.
2. Estudiar los fundamentos de la informática gráfica requeridos para implementarlos.
3. Desarrollar un motor gráfico sencillo reutilizable con capacidades lógicas suficientes.
4. Implementar una escena 3D interactiva como base para el desarrollo.
5. Implementar los portales de forma progresiva, empezando por sus propiedades más básicas, hasta las más complejas.
6. Redactar la parte de la memoria referente a los fundamentos de la informática gráfica, para que sea más accesible, y para aliviar la carga de explicación posterior.
7. Redactar la parte de la memoria referente al completo funcionamiento e implementación de los portales, lo más didáctica y útil posible.
8. Redactar la parte de la memoria referente a la arquitectura del motor propio, para que sea posible consultar el código fuente de forma productiva.
9. Implementar mejoras sobre el motor gráfico, principalmente soporte para iluminación y para importación de modelos o escenas completas.
10. Desarrollar escenas más impresionantes, que empleen los portales de formas sorprendentes e interesantes.

### Estructura de la memoria
> Esta sección hace referencia a la parte escrita del trabajo. Se puede encontrar en la carpeta [docs](https://github.com/dimateos/TFG_Portals/tree/master/Docs).

Este documento trata de ser muy accesible y por ello parte del mismo puede ser información redundante para una persona que ya domine el tema. Concretamente los capítulos **`[2]`** y **`[4]`** referentes a la informática gráfica, se pueden leer por encima si no se requiere una explicación sobre su estado del arte y fundamentos. El capítulo **`[3]`** detalla brevemente la arquitectura del motor propio, si ésta no es de interés, puede ser saltado y consultado en caso de duda. Finalmente los relativamente extensos capítulos **`[5]`** y **`[6]`** explican el estado del arte de los portales y su funcionamiento e implementación completamente.

## Conclusiones y trabajo futuro
En este conciso capítulo final se presentan las conclusiones del proyecto respecto a sus objetivos y plan de trabajo. También se añaden posibles ideas de trabajo futuro.

### Conclusiones
Una vez finalizado el proyecto es un buen momento para reflexionar y realizar una valoración sobre el trabajo completado y lo aprendido durante el mismo. Desde el punto de vista de los objetivos listados en el apartado `[Objetivos y plan de trabajo]`, **menos los dos últimos**, todos se han cumplido satisfactoriamente a tiempo. Este resultado se debe a que desde el principio, en el plan de trabajo, se ha tenido en cuenta la posibilidad de no poder lograr todos los objetivos, y por ello se han perseguido por orden de prioridad.

Respecto a los **objetivos completados**, alguno ha resultado más complicado de lo anticipado. El trabajo relacionado con el estudio de *OpenGL* **`[2]`** y la implementación del motor **`[3]`** ha costado bastante más de lo esperado, pero igualmente estoy satisfecho con el aprendizaje. La cantidad de tiempo invertida en la investigación **`[1]`** y el desarrollo **`[5]`** de los portales ya había sido prevista, aunque la implementación final de la recursión ha llevado más tiempo ya que ha ido mejorando progresivamente. Creo que el nivel de detalle en la redacción de la memoria **`[6,7,8]`** ha sido más elevado del intencionado inicialmente, y con ello el volumen de páginas y trabajo, pero estoy muy contento con el resultado. La interactividad de la escena implementada **`[4]`** ha crecido continuamente junto con la redacción de contenidos, y ha llegado a un nivel de interacción y configuración más que destacable. La recursión de los portales ha sido especialmente difícil de explicar **`[7]`** y ha requerido una gran cantidad de figuras.

No se han logrado los objetivos relacionados con la implementación de mejoras en el motor gráfico **`[9]`** y el desarrollo de escenas más interesantes para los portales **`[10]`**. Estos objetivos de menor prioridad, han resultado descartados por falta de tiempo y necesidad. El motor gráfico actual ha permitido generar todas las imágenes para la memoria, y las propias texturas sencillas sin iluminación aportan claridad y simpleza al resultado. Asimismo, la importación de modelos no ha sido estimada y se han utilizado objetos de geometría sencilla. La escena final que se centra en la interactividad y utilidad, permite configurar y mostrar cada una las características de los portales en tiempo real. No se usan los portales de formas *sorprendentes*, pero las propias opciones de configuración son bastante más didácticas e *interesantes* de lo planeado inicialmente.

### Trabajo futuro
En este apartado se describen posibles ideas que añaden más valor al proyecto. Además de los dos objetivos no cumplidos, a lo largo de la realización de este proyecto han surgido otras ideas interesantes. A continuación se listan sin un orden particular:

*Objetivo previos*:
* Implementar mejoras sobre el motor gráfico, principalmente soporte para iluminación y para importación de modelos o escenas completas.
* Desarrollar escenas más sorprendentes, que empleen los portales de formas más interesantes. Por ejemplo, con más de un par de portales.

*Otros*:
* Desarrollo de una interfaz gráfica que facilite la interacción con la escena. Esto permitiría al usuario tener una experiencia mejor, sin necesidad de conocer los controles.
* Desarrollo de una implementación alternativa basada en stencil-buffer, con la capacidad de poder activarla en tiempo real. Esto permitiría poder realizar una comparación más directa entre ambos métodos de implementación.
* Desarrollo de diversas optimizaciones, éstas podrían ser interesantes para casos en los que se simulen escenas relativamente complejas. Por ejemplo: detección de portales fuera del espacio de pantalla para agilizar el proceso de renderizado o detección de ausencia de superposición entre portales en espacio de pantalla para agilizar el proceso de recursión.
* Creación de un Shader que optimice la gestión de las texturas de los portales. En vez de guardar una textura con la escena completa y posteriormente asignarla al portal correctamente, quizás sea posible guardarla previamente de forma *optimizada* para que la asignación sea directa (que no requiera un proceso especial).

## Bibliografía
1. Diego Mateos Arlanzón. TFG - MOTOR GRÁFICO CON PORTALES PARA SIMULAR ESCENAS 3D NO EUCLIDIANAS. Repositorio del proyecto. https://github.com/dimateos/TFG_Portals, 2020
2. Portal: No Escape. Live Action Short Film by Dan Trachtenberg. https://www.youtube.com/watch?v=4drucg1A6Xk, 2011
3. Portal. Selling point reference. https://store.steampowered.com/app/400/ Portal, 2007
4. Computer History Museum (Mountain View, CA). The Utah Teapot. https://www.computerhistory.org/revolution/computer-graphics-music-and-art/15/206, 2020
5. Unity Technologies. Unity official webpage. https://unity.com/es, 2020
6. Epic Games, Inc. Unreal Engine official webpage. https://www.unrealengine.com /en-US/, 2020
7. GIGABYTE productos. Tarjeta gráfica GeForce RTX 2060. https://www.gigabyte.com/es/Graphics-Card/GV-N2060GAMING-OC-6GD#kf, 2018
8. Nvidia Corporation. Nvidia official webpage. https://www.nvidia.com/es-es/about-nvidia/, 2020
9. GIGABYTE. Gigabyte official webpage. https://www.gigabyte.com/About, 2020
10. Khronos Group Inc. OpenGL - The Industry's Foundation for High Performance Graphics.  https://www.opengl.org/, 2020
11. Khronos Group Inc. Khronos official webpage. https://www.khronos.org/, 2020
12. OpenGL Wiki contributors. Language bindings. https://www.khronos.org/opengl/wiki/Language_ bindings, 2020
13. Standard C++ Foundation. Standard C++. https://isocpp.org/, 2020
14. Khronos Group Inc. Vulkan Overview. https://www.khronos.org/vulkan/, 2020
15. Khronos Group Inc. Vulkan Overview slides 2016. https://www.khronos.org/assets/uploads/developers/library/overview/vulkan-overview.pdf, 2016
16. Microsoft. Getting started with Direct3D. https://docs.microsoft.com/en-us/windows/win32/getting-started-with-direct3d, 2018
17. Nvidia Gameworks. Transitioning from OpenGL to Vulkan. https://developer.nvidia.com/transitioning-opengl-vulkan, 2016
18. UNIVERSIDAD COMPLUTENSE DE MADRID (UCM). FACULTAD DE INFORMÁTICA (FDI). Ficha docente de la asignatura IG I. http://web.fdi.ucm.es/UCMFiles/pdf/FICHAS_DOCENTES/2017/1362.pdf, 2017-2018
19. OpenGL Wiki contributors. History of OpenGL. https://www.khronos.org/opengl/wiki/History_of_OpenGL, 2020
20. UNIVERSIDAD COMPLUTENSE DE MADRID (UCM). FACULTAD DE INFORMÁTICA (FDI). Ficha docente de la asignatura IG II. http://web.fdi.ucm.es/UCMFiles/pdf/FICHAS_DOCENTES/2017/1372.pdf, 2017-2018
21. OGRE. OGRE - Open Source 3D Graphics Engine. https://www.ogre3d.org/, 2020
22. OpenGL Wiki contributors. Shader. https://www.khronos.org/opengl/wiki/ Shader, 2019
23. OpenGL Wiki contributors. Core Language (GLSL). https://www.khronos.org/opengl/wiki/Core_Language_(GLSL), 2019
24. Joey de Vries (https://twitter.com/JoeyDeVriez). Learn OpenGL.  https://learnopengl.com/, 2020
25. Joey de Vries.  Kendall & Welling publishing. Learn OpenGL - Graphics Programming.  https://learnopengl.com/book/book_pdf.pdf, 2020
26. Joey de Vries. learnopengl.com code repository. https://github.com/JoeyDeVries/LearnOpenGL, 2020
27. Creative Commons. Attribution-NonCommercial 4.0 International. https://creativecommons.org/licenses/by-nc/4.0, 2016
28. Creative Commons. Attribution 4.0 International. https://creativecommons.org/ licenses/by/4.0, 2016
29. Alexander Overvoorde. Modern OpenGL Guide. https://open.gl/, 2019
30. Alexander Overvoorde. open.gl content repository. https://github.com/Overv/ Open.GL, 2019
31. Creative Commons. Attribution-ShareAlike 4.0 International. https://creativecommons.org/licenses/by-sa/4.0/, 2016
32. OpenGL Wiki contributors. OpenGL Wiki. https://www.khronos.org/opengl/wiki/, 2018
33. OpenGL Mathematics. GL 0.9.9 API documentation, https://glm.g-truc.net/0.9.9/api/modules.html, 2020
34. Simple DirectMedia Layer. SDL 2.0 wiki frontpage. https://wiki.libsdl.org/FrontPage, 2018
35. GLFW. GLFW - An OpenGL library. https://www.glfw.org/, 2020
36. glad. GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specs. https://github.com/Dav1dde/glad, 2020
37. OpenGL Wiki contributors. OpenGL Loading Library. https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library, 2019
38. OpenGL Mathematics (GLM). A C++ mathematics library for graphics programming. https://glm.g-truc.net/0.9.9/index.html, 2020
39. stb_image. Image loading/decoding from file/memory: JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC. https://github.com/nothings/stb, 2020
40. Microsoft. IDE de Visual Studio. https://visualstudio.microsoft.com/es/, 2020
41. Linus Torvalds. Git, free and open source. https://git-scm.com/, 2020
42. GitHub, Inc. About. https://github.com/about, 2020
43. Update method. Robert Nystrom, Game Programming Patterns. https://gameprogrammingpatterns.com/update-method.html, 2014
44. Game loop. Robert Nystrom, Game Programming Patterns. https://gameprogrammingpatterns.com/game-loop.html, 2014
45. Delta time. Cristian Barrio (BYC), Parallelcube. https://www.parallelcube.com/es/2017/10/25/por-que-necesitamos-utilizar-delta-time/, 2017
46. Event-Subscriber pattern. Alexander Shvets (refactoring.guru), Dive Into Design Patterns. https://refactoring.guru/design-patterns/observer, 2020
47. Paul E. Black and Algorithms and Theory of Computation Handbook, CRC Press LLC, 1999. Tree. Dictionary of Algorithms and Data Structures. https://xlinux.nist.gov/dads/HTML/tree.html, 2017
48. Wikipedia contributors. Tree traversal. In Wikipedia, The Free Encyclopedia. https://en.wikipedia.org/w/index.php?title=Tree_traversal&oldid=968976983, 2020
49. Sumanta Guha; Computer Graphics through OpenGL; Segunda edición, CRC Press, 2015
50. Peter Shirley, Steve Marschner; Fundamentals of Computer Graphics; Third Edition, CRC Press, 2009
51. OpenGL Wiki contributors. Tesselation. https://www.khronos.org/opengl/wiki/Tessellation, 2019
52. Department of Mathematics. University of Maryland. Gimbal Lock. http://www.math.umd.edu/~immortal/MATH431/lecturenotes/ch_gimballock.pdf, 2018
53. Wolfram mathworld. Quaternion. https://mathworld.wolfram.com/Quaternion.html, 2020
54. Blender Documentation Team. The Blender 2.90 Manual. Licensed under CC-BY-SA v4.0. https://docs.blender.org/manual/en/latest/editors/3dview/navigate/views.html, 2020
55. Techopedia. First Person Shooter (FPS). https://www.techopedia.com/definition/241/first-person-shooter-fps, 2011
56. Valve Corporation. Official webpage. https://www.valvesoftware.com/es/, 1996-2020
57. Portal 2. Official webpage. https://www.thinkwithportals.com/, 2011
58. Narbacular Drop. Overview from official webpage. http://www.nuclearmonkeysoftware.com/narbaculardrop.html?overview.html, 2004-2008
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


