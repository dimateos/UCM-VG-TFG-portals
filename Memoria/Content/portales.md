> Portales - en algún momento se introducirán

## 1. ¿Qué es un portal?

Un portal es una discontinuidad del espacio 3D donde la cara trasera de un rectángulo 2D es definida como la cara frontal de otro rectángulo 2D localizado en otra posición. Esta discontinuidad implica que no se desplace ninguna geometría ni se sobreponga el espacio de maneras incomprensibles.

> gráfico 2D mostrando efecto

Otra forma de pensarlo es como el marco de una puerta que separa dos estancias, solo que que en realidad éstas no son tangentes en el espacio 3D. La transición es totalmente inapreciable, como si ambos lugares estuviesen simplemente conectados. Ello no implica que un par de portales deban estar siempre contiguos a una pared, pero en estos casos, no existe forma de notar la diferencia. Podrían estar separados por apenas unos centímetros o cientos de metros.

> ejemplo de puerta en portal 2 que literalmente es un portal por cuestiones técnicas

## 2. ¿Cómo implementar un portal?

Las características de un portal se pueden separar a la hora de entenderlo y desarrollarlo. La parte mas obvia es la visual: representar los objetos que se ven a través del plano del portal correctamente. La otra parte es la física: transportar los objetos que atraviesan el portal.

Existen múltiples detalles que tener en cuenta, al fin y al cabo, la parte interesante de los portales es que el usuario no note ninguna transición. Como en un truco de magia, solo se debe mostrar la superficie, nada de lo que ocurra fuera de ella es perceptible. En caso de errores se produce la desorientación del usuario al producirse situaciones visuales carentes de sentido.

### 2.1. Técnicas físicas
No se trata de simplemente transportar objetos y conservar sus velocidades y aceleraciones. Se debe conservar las interacciones de los mismos incluso cuando atraviesen parcialmente un portal.

> ejemplo de cubo parcialmente atravesado chocando con otro

*Este proyecto abarca el apartado gráfico, principalmente.*

### 2.2. Técnicas gráficas
Desde el punto de vista gráfico existen pocas formas de conseguir el efecto, independientes de la API gráfica. De las opciones que se explican a continuación, no todas están soportadas por cualquier version de API.

#### 2.2.1. Texturas
Tal y como se explicó en la sección X anterior, las llamadas al API para dibujar escriben en determinadas zonas de memoria. Una de esas zonas es el buffer que posteriormente se pinta en pantalla. Se puede asociar una textura a un buffer específico para posteriormente pintarla.

En el caso de los portales, son planos con una de éstas texturas asociadas a un buffer de dibujado. Previamente a dibujar la escena desde el punto de vista principal, se dibuja en los buffers de las texturas de cada portal desde el punto vista adecuado.

> grafico mostrando el efecto

#### 2.2.2 Stencil
Tal y como se explicó en la sección X anterior, existen diferentes buffers para realizar tests a la hora de pintar fragmentos. Se pueden definir normas para concretar cuando se modifican los valores del buffer a la hora de pintar y también en que casos se descartan fragmentos.

En el caso de los portales, tras renderizar la escena desde el punto de vista principal, se modifica el stencil buffer dibujando los portales en sus respectivas posiciones. Posteriormente se dibuja la escena desde el punto de vista adecuado de cada portal, pero solo se mantienen los fragmentos cuyo respectivo valor del stencil buffer estaba marcado.

> grafico mostrando el efecto

#### 2.2.3 Renderizado físico
Existen diferentes técnicas de renderizado físico, éstas técnicas tratan de simular el mundo de una manera mas realista. etc

Teóricamente, se podría interceptar los rayos que chocan con la superficie de un portal y simular que saliesen (con la misma dirección) por la superficie contraria del portal conectado. De esta forma, se aprovecha de la gran ventaja de usar técnicas de renderizado físico, la iluminación será correcta sin importar de las condiciones.

> grafico mostrando el efecto

#### 2.2.4 Comparación
El uso de texturas como se ha descrito, está soportado desde las primeras versiones de API gráficas. Hoy en día los stencils buffers también, pero su introducción fue posterior. El renderizado físico moderno (RTX) necesita hardware específico que lo hace viable a tiempo real (para escenas complejas).

En nuestro caso de estudio, el desarrollo de los juegos Portal, el prototipo (Narbacular Drop) utilizaba exclusivamente texturas. En Portal 1, se pasó a utilizar la técnica de stencil pero mantuvieron las texturas para tarjetas gráficas antiguas de la época. Portal 2 directamente utiliza exclusivamente stencil buffer.

Desde el punto de vista técnico, no tiene mucho sentido comparar la técnica de renderizado físico con las otras ya que es fundamentalmente diferente. En su caso se simplifica el proceso por el coste de cómputo que implica simular de forma realista la luz.

Realizar los portales utilizando texturas proporciona una abstracción conceptual más sencilla. Los portales se pueden ver como objetos con una determinada textura, la cuál ha de ser pintada previamente. Esta abstracción permite separar el renderizado de la escena y el de las texturas.

Por otro lado tiene sus repercusiones:
* Se utiliza más memoria para los buffers auxiliares en los que pintar. Mínimo 1 si se pinta secuencialmente los portales.
* En el caso de que se vea un portal a través de otro, se necesita lógica para pintar primero la textura del portal trasero ya que ésta se pinta posteriormente en la textura del portal delantero. En la recursión igual, es necesario dibujar la más profunda primero.
* Aunque no es obvio, que el portal utilice una textura plana como una pared puede provocar situaciones inesperadas. Por ejemplo, el plano cercano de la cámara puede atravesar el portal al acercarse o efectos de post-procesado de escena que necesiten información de profundidad se complican.

Estos problemas no ocurren al utilizar el stencil buffer:
* Se utiliza el mismo buffer para dibujar y un stencil buffer (que no necesita mucha precisión)
* Se dibuja directamente la escena desde el punto de vista principal y posteriormente las recursiones si son necesarias.
* La profundidad es real, no textura 2D.

El uso de stencil buffer conlleva un orden de renderizado complejo, entrelazado con los tipos de objetos de la escena. Por ejemplo, se renderizan primero los objetos opacos, después la recursión de los portales hasta el final y posteriormente los objetos translúcidos de cada recursión.

#### 2.2.5 Conclusión
Para este proyecto decidí implementar primero los portales utilizando texturas y observar las dificultades que puedan surgir. Posteriormente quizás implementar otras técnicas?

> No he desarrollado los portales con stencils ni PBR

A continuación se explica en detalle como desarrollar, paso por paso, cada característica del comportamiento de un par de portales. En cada punto se exponen los conceptos teóricos, su implementación, los posibles problemas y sus soluciones.


## x. Desarrollo
* Render textures utilizando renderbuffers
	* vs stencils - mas sencillo y no tanto crecimiento de memoria
* Posicion relativa de la camara virtual
	* camara virtual o simplemente transform y utilizar la misma camara
* Coordenadas en pantalla de los vertices del portal
	* se puede usar stencil para no dibujar fuera
	* duda de poder editar frustum - portal usa planos definidos
* Orden de renderizado para no sobreescribir - porque se necesita extra
	* primero portales (de profundos a cercanos) luego todo
	* con stencils primero la escena y luego las recursiones
* Comprobar cada frame si se ha pasado al otro lado del portal
	* no depender de sistema físico que se actualice a diferente frecuencia
* Solucionar problemas de camara haciendo clipping al plano
	* reducir el cercano de la camara - mala idea
	* utilizar prisma en vez de plano con culling de las caras internas desactivado
		* y que igualmente mapee la textura en coordenadas de pantalla de sus vertices
		* se extiende en la dirección contraria del portal respecto al jugador
	* esté problema no surge con stencils ya que no existe un plano que pueda atravesar
		* además se simplifica la realización de efectos post renderizado que necesiten depth
		* también evita hacer clip a las paredes traseras (aunque en portal estas se eliminan)
* Solucionar problemas de camara haciendo que su near sea el plano del portal
	* objeto entre camara virtual y portal (pared por ejemplo)
	* con plano definido por el usuario o con proyeccion oblicua
* Recursión entre portales, no se puede usar la misma textura del frame anterior
	* efecto retardado y ademas se funde todo con la proximidad
	* se renderiza la escena multiples veces en el mismo frame
		* desde posiciones calculadas recursivamente de la camara empezando por el final
* Slicing duplicando el objeto y utilizando un shader con un plano de clip
	* ya no se produce clip durante la recursión
	* además se pueden ver cuerpos atravesar el portal de salida desde la entrada etc


## Optimizar
* no renderizar portal si esta fuera de pantalla
	* utilizar el estencil buffer para saber si algo se ha pintado
	* utilizar el frustum de la camara para ver si se va a renderizar
* evitar recursión si no hay portales superpuestos
	* utilizar el stencil para saber si algo ha utilizado recursión
	* utilizar bounding boxes en coordenadas de pantalla
