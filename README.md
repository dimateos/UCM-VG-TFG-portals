# TFG - Non Euclidean Worlds Render
> Documentación inicial en español

Trabajo de fin de grado (TFG) Desarrollo de Videojuegos (GDV) 2019/2020 Universidad Complutense de Madrid (UCM)

* Título: Renderizado de mundos no euclidianos
* Dirigido por: Ana Gil Luezas, Pedro Jesús Martín de la Calle
* Estudiante(s): Diego Mateos Arlanzón (GDV)

# Enlaces / contacto
* mail: dimateos@ucm.es
* [Repo pública](https://github.com/dimateos/TFG_NEWR)
* [Lista de TFGs 2019-20 FDI](https://informatica.ucm.es/tfgs-2019-2020)

# Descripción inicial
> Siglas NEWR ?

Motor de renderizado / aplicación que permitiese explorar entornos con geometría no euclidiana o imposible. Probablemente usando OpenGL, shaders y programación característica para lo no euclidiano, etc.

En principio no se trata ni de geometría hiperbólica ni elíptica, simplemete para el observador no cumple los Postulados de Euclides.

Inicialmente me interesan las siguientes geometrías imposibles:
* Portales seam-less (renderizado + atravesables)
* Contenedor finito con espacio infinito dentro
* Túneles mas largos de atravesar por dentro que por alrededor (o viceversa etc)
* Regiones del espacio que cambian las proporciones al atravesarlas

La mayor parte de las características de estas geometrías se pueden conseguir con el uso de los mencionados portales seam-less de diferentes formas.

La idea es que una persona pueda explorar en un entorno y se sorprenda con ejemplos de geometría no euclideana. Se usan selectas demos creadas con el mortor realizado para hacer más accesibles los postulados de Euclides al ignorarlos.

# Tecnología inicial

* C++, OpenGL, scripts de shaders...

# Conocimientos (asignaturas principales)

* Informática gráfica (IG e IG2)
* Lenguaje C++ y sus capacidades (TPV, MAR, etc)
* Organización de proyectos, código y documentación (P2, P3, SIM)
* Desarrollo de un motor con integración de varias tecnologías (P2, P3, SIM)
* ...

# Posibles ampliaciones
> Descripción vaga

* Fisicas sencillas
* Crear editor (la posibilidad) para poder configurar entornos en tiempo real (y guardarlos)
* Adaptar VR ?
* *Añadir una dimensión extra a la geometria*

# Referencias
* Vídeos con código accesible:
	* [Non-Euclidean Worlds Engine](https://www.youtube.com/watch?v=kEB11PQ9Eo8)
	* [Demo of a Real-Time Non-Euclidean Ray-tracer](https://www.youtube.com/watch?v=YvU-srHhQxw)
	* ["No! Euclid!" GPU Ray Tracer gets an upgrade!](https://www.youtube.com/watch?v=tl40xidKF-4)
	* [Non Euclidean GPU Ray Tracing Test](https://www.youtube.com/watch?v=0pmSPlYHxoY)

* Wikipedia:
	* [Geometria no euclidiana](https://es.wikipedia.org/wiki/Geometr%C3%ADa_no_euclidiana)
	* [Postulados de Euclides](https://es.wikipedia.org/wiki/Postulados_de_Euclides)

* OpenGL:
	* [Learn OpenGL](https://learnopengl.com/)

