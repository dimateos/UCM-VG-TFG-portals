# Motor gráfico con portales para simular escenas 3D no euclidianas

> > **`EN`**: [Here](./README.md) you can find the English version.

* **Diego Mateos Arlanzón** *dimateos@ucm.es*
* GRADO EN DESARROLLO DE VIDEOJUEGOS
	* FACULTAD DE INFORMÁTICA /  UNIVERSIDAD COMPLUTENSE DE MADRID
* Trabajo Fin de Grado en Desarrollo de Videojuegos
	* Curso académico 2019-2020 (*Septiembre *)
	* Directora: *Ana Gil Luezas*

### Índice
- [Motor gráfico con portales para simular escenas 3D no euclidianas](#motor-gr%C3%A1fico-con-portales-para-simular-escenas-3d-no-euclidianas)
		- [Índice](#%C3%ADndice)
	- [Documentación](#documentaci%C3%B3n)
	- [Cuestiones (*issues*)](#cuestiones-issues)
	- [Versiones de la aplicación (*releases*)](#versiones-de-la-aplicaci%C3%B3n-releases)
	- [Compilación y dependencias](#compilaci%C3%B3n-y-dependencias)

## Documentación

En la carpeta [`/docs`](./Docs) se puede encontrar la siguiente información:

* [**RESUMEN**](./Docs/summary%20-%20ES.md) de la memoria (*Resumen, Introducción y Conclusiones*).
* Toda la [**memoria**](./Docs/memoria%20completa%20-%20ES.pdf) escrita (en español).
* La [bibliografía](./Docs/bibliography.md) completa de la memoria.
* La [asignación de teclas](./Docs/keyMapping%20-%20ES.md) de la aplicación para realizar tests y configuraciones en tiempo real.

## Cuestiones (*issues*)

Por favor considera crear un [`issue`](https://github.com/dimateos/TFG_Portals/issues):

* Si tienes alguna sugerencia.
* Si encuentras algun tipo de error (software bug o *errata*).

> También puedes enviarme un [*mail*](https://github.com/dimateos) para cualquier consulta

## Versiones de la aplicación (*releases*)

La última versión de la aplicación se puede encontrar en el apartado de [`releases`](https://github.com/dimateos/TFG_Portals/releases) (junto con más información).

![sample0](./Docs/sample0.png)
![sample1](./Docs/sample1.png)

## Compilación y dependencias

Este proyecto se ha desarrollado en una solución de [**`Visual Studio (2017)`**](https://visualstudio.microsoft.com/es/) que se encuentra dentro de la carpeta [`/VisualStudio`](./VisualStudio).

> El archivo [readme](./VisualStudio/README.md) explica su estructura de carpetas y la instalación de dependencias.

* [SDL 2.0](https://wiki.libsdl.org/FrontPage). Simple DirectMedia Layer.
* [glad](https://github.com/Dav1dde/glad). GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specs.
* [GLM](https://glm.g-truc.net/0.9.9/index.html). OpenGL Mathematics (GLM). A C++ mathematics library for graphics programming.
* [stb_image](https://github.com/nothings/stb). Image loading/decoding from file/memory: JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC.
