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

En principio no se trata de geometría hiperbólica ni elíptica, simplemete para el observador no se cumplen los Postulados de Euclides todo el rato. Es decir, existen regiones del espacio *localmente* no euclidianas; el resto del mundo será *normal*.

Inicialmente me interesan las siguientes geometrías imposibles:
* Portales *seam-less* (renderizado + atravesables)
* Contenedor finito con espacio infinito dentro
* Túneles mas largos de atravesar por dentro que por alrededor (o viceversa etc)
* Regiones del espacio que cambian las proporciones al atravesarlas

> Difiere mucho un motor que permita ciertas geometrías imposibles a uno que fundamentalmente se base es geometría hiperbólica o elíptica.

La mayor parte de las características de estas geometrías se pueden conseguir con el uso de los mencionados portales *seam-less* de diferentes formas.

La idea es que una persona pueda explorar un entorno y se sorprenda con ejemplos de geometría no euclidiana. Se usan selectas demos creadas con el mortor realizado para hacer más accesibles los postulados de Euclides al romperlos.

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
* Tecnología:
	* [Learn OpenGL](https://learnopengl.com/)

* Vídeos con código accesible:
	* [Non-Euclidean Worlds Engine](https://www.youtube.com/watch?v=kEB11PQ9Eo8)
	* [Demo of a Real-Time Non-Euclidean Ray-tracer](https://www.youtube.com/watch?v=YvU-srHhQxw)
	* ["No! Euclid!" GPU Ray Tracer gets an upgrade!](https://www.youtube.com/watch?v=tl40xidKF-4)
	* [Non Euclidean GPU Ray Tracing Test](https://www.youtube.com/watch?v=0pmSPlYHxoY)

* Geometría no euclidiana:
	* Wikipedia: [Geometria no euclidiana](https://es.wikipedia.org/wiki/Geometr%C3%ADa_no_euclidiana)
	* Wikipedia: [Postulados de Euclides](https://es.wikipedia.org/wiki/Postulados_de_Euclides)

* Juegos
	* [Fragments of euclid](https://nusan.itch.io/fragments-of-euclid), muy inspirado en Escher
	* [Antichamber](http://www.antichamber-game.com/), ilusiones usando el espacio y la perspectiva
	* [Portal](https://es.wikipedia.org/wiki/Portal_(videojuego)), puzles de físicas a traves de portales (el más comercial)
	* Post sobre el desarrollo de un juego VR: [Environmental Redirection in Unseen Diplomacy](https://connect.unity.com/p/articles-environmental-redirection-unseen-diplomacy-1)
	* Video trailer: [Optical Illusion Perspective-Based Puzzle Gameplay: Museum of Simulation Technology](https://www.youtube.com/watch?v=HEBEQhwG-rU)

* Geometría hiperbólica:
	* Demos: [Hyperbolic VR](http://www.segerman.org/XR.html)
	* Video: [Non-euclidean virtual reality](https://www.youtube.com/watch?v=ztsi0CLxmjw) usando esta [web](http://h3.hypernom.com/)
	* Juego: [HyperRogue](http://www.roguetemple.com/z/hyper/)

* Arte:
	* Trabajos de [M. C. Escher](https://mcescher.com/gallery/recognition-success/)

* Interesante:
	* Post: [NonEuclidean rendering engine for Windows, written in C++ OpenGL](https://www.reddit.com/r/programming/comments/abuyuf/noneuclidean_a_noneuclidean_rendering_engine_for/)
	* Video: [Juguetes 4D: una caja de juguetes de cuatro dimensiones](https://www.youtube.com/watch?v=0t4aKJuKP0Q)
	* Video: [Diseñando un Mundo 4D: La Tecnología detrás de Miegakure](https://www.youtube.com/watch?v=vZp0ETdD37E)
	* Video: [A Slower Speed Of Light](https://www.youtube.com/watch?v=hyj1ZZiseDE)
