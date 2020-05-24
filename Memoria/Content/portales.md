> Portales - en algún momento se introducirán

- [1. ¿Qué es un portal?](#1-%C2%BFqu%C3%A9-es-un-portal)
- [2. ¿Cómo implementar un portal?](#2-%C2%BFc%C3%B3mo-implementar-un-portal)
	- [2.1. Técnicas de implementación: parte física](#21-t%C3%A9cnicas-de-implementaci%C3%B3n-parte-f%C3%ADsica)
	- [2.2. Técnicas de implementación: parte gráfica](#22-t%C3%A9cnicas-de-implementaci%C3%B3n-parte-gr%C3%A1fica)
		- [2.2.1. Texturas](#221-texturas)
		- [2.2.2 Stencil](#222-stencil)
		- [2.2.3 Renderizado físico](#223-renderizado-f%C3%ADsico)
		- [2.2.4 Comparación](#224-comparaci%C3%B3n)
		- [2.2.5 Conclusión](#225-conclusi%C3%B3n)
- [3. Desarrollo de un portal](#3-desarrollo-de-un-portal)
	- [3.1. Punto de vista relativo](#31-punto-de-vista-relativo)
	- [3.2. Dibujado de las texturas](#32-dibujado-de-las-texturas)
- [x. Esquema de desarrollo](#x-esquema-de-desarrollo)
- [y. Para realizar explicación + capturas](#y-para-realizar-explicaci%C3%B3n--capturas)
- [z. Optimizar](#z-optimizar)

## 1. ¿Qué es un portal?

Un portal es una discontinuidad del espacio 3D donde la cara trasera de un rectángulo 2D es definida como la cara frontal de otro rectángulo 2D localizado en otra posición. Esta discontinuidad implica que no se desplace ninguna geometría ni se sobreponga el espacio de maneras incomprensibles. Cabe destacar que, salvo en determinadas excepciones, siempre hablaremos de pares de portales *conectados*.

> gráfico 2D mostrando efecto

Otra forma de pensarlo es como el marco de una puerta que separa dos estancias, solo que que en realidad éstas no son tangentes en el espacio 3D. La transición es totalmente inapreciable, como si ambos lugares estuviesen simplemente conectados. Ello no implica que un par de portales deban estar siempre contiguos a una pared, pero en estos casos, no existe forma de notar la diferencia. Podrían estar separados por apenas unos centímetros o cientos de metros.

> ejemplo de puerta en portal 2 que literalmente es un portal por cuestiones técnicas

## 2. ¿Cómo implementar un portal?

Las características de un portal se pueden separar a la hora de entenderlo y desarrollarlo. La parte mas obvia es la visual: representar los objetos que se ven a través del plano del portal correctamente. La otra parte es la física: transportar los objetos que atraviesan el portal.

Existen múltiples detalles a tener en cuenta, al fin y al cabo, la parte interesante de los portales es que el usuario no note ninguna transición. Como en un truco de magia, solo se debe mostrar la superficie, nada de lo que ocurra fuera de ella es perceptible. En caso de errores, el usuario puede desorientarse ante situaciones carentes de sentido: errores gráficos o comportamiento físico no anticipado.

### 2.1. Técnicas de implementación: parte física
No se trata de simplemente transportar objetos y conservar sus velocidades y aceleraciones. Se debe conservar las interacciones de los mismos incluso cuando atraviesen parcialmente un portal.

> ejemplo de cubo parcialmente atravesado chocando con otro

*Este proyecto abarca el apartado gráfico, principalmente.*

### 2.2. Técnicas de implementación: parte gráfica
Desde el punto de vista gráfico existen pocas formas de conseguir el efecto, independientes de la API gráfica. De las opciones que se explican a continuación, no todas están soportadas por cualquier version de API.

#### 2.2.1. Texturas
Tal y como se explicó en la sección X anterior, las llamadas al API para dibujar escriben en determinadas zonas de memoria. Una de esas zonas es el buffer que posteriormente se pinta en pantalla. Se puede asociar una textura a un buffer específico para posteriormente ser pintada utilizando los datos escritos en dicho buffer.

En el caso de los portales, son simples planos con una de éstas texturas asociadas a un buffer de dibujado. Primero se escribe en el respectivo buffer de cada portal la vista de la escena, desde el punto de vista adecuado. Posteriormente, se dibuja toda la escena vista a través de la cámara principal, en la que aparecen los portales utilizando las texturas previamente calculadas.

> grafico mostrando el efecto

#### 2.2.2 Stencil
Como se mencionó en la sección X anterior, existen diferentes buffers para realizar tests a la hora de pintar fragmentos. Se pueden definir normas para concretar cuando se modifican los valores del buffer y cuando se descartan ciertos fragmentos.

Aplicado a los portales, y a diferencia de en el uso de texturas, primero se dibuja la escena vista a través de la cámara principal, sin portales. Después, cada portal es dibujado en su posición. Durante este paso se modifica el stencil buffer para que queden marcados los fragmentos donde se sitúan. Finalmente, se dibuja la escena desde el punto de vista adecuado para cada portal, pero solo se mantienen los fragmentos que coincidan con los marcados previamente.

> grafico mostrando el efecto

#### 2.2.3 Renderizado físico
Existen diferentes técnicas de renderizado físico, éstas técnicas tratan de simular el mundo de una manera mas realista.
> `etc`

Teóricamente, se podría interceptar los rayos que chocan con la superficie de un portal y simular su salida (con la misma dirección) por la superficie contraria del portal conectado. De esta forma, se aprovecha la gran ventaja de las técnicas de renderizado físico: la iluminación será correcta sin importar de las condiciones.

> grafico mostrando el efecto

#### 2.2.4 Comparación
El uso de texturas como se ha descrito, está soportado desde las primeras versiones de API gráficas. Hoy en día los stencils buffers también, pero su introducción fue posterior. El renderizado físico moderno (RTX) necesita hardware específico que lo hace viable a tiempo real (para escenas complejas).

En nuestro caso de estudio, el desarrollo de los juegos Portal, el prototipo (Narbacular Drop) utilizaba exclusivamente texturas. En Portal 1, se pasó a utilizar la técnica de stencil pero mantuvieron las texturas para tarjetas gráficas antiguas de la época. Portal 2 directamente utiliza stencil buffer de forma exclusiva.

Desde un punto de vista pragmático, no tiene mucho sentido comparar la técnica de renderizado físico con las otras, ya que es fundamentalmente diferente. En su caso, se simplifica el proceso por el coste de cómputo que implica simular de forma realista el comportamiento físico de luz.

Realizar los portales utilizando texturas proporciona una abstracción conceptual más sencilla. Los portales se pueden ver como objetos con una determinada textura, la cuál ha de ser pintada previamente. Esta abstracción permite separar el renderizado de la escena y el de las texturas.

Por otro lado tiene sus repercusiones:
* Se utiliza más memoria para los buffers auxiliares en los que pintar. Mínimo 1 si se pinta secuencialmente los portales.
* En el caso de que se vea un portal a través de otro, se necesita lógica para pintar primero la textura del portal trasero ya que ésta se pinta posteriormente en la textura del portal delantero. En la recursión ocurre igual, es necesario dibujar la más profunda primero.
* Aunque no es obvio, que el portal utilice una textura plana (como una simple pared) puede provocar situaciones inesperadas. Por ejemplo, el plano cercano de la cámara puede atravesar el portal al acercarse o efectos de post-procesado de escena que necesiten información de profundidad se complican.

Estos problemas no ocurren al utilizar el stencil buffer:
* Se utiliza el mismo buffer para dibujar y un stencil buffer (que no necesita mucha precisión).
* Se dibuja directamente la escena desde el punto de vista principal y posteriormente las recursiones si son necesarias.
* La profundidad es real, no textura plana 2D.

El inconveniente del uso de stencil buffer es que requiere una lógica bastante más complicada y sin espacio a tanta abstracción. Primariamente requiere un orden de renderizado complejo, entrelazando los tipos de objetos de la escena y los niveles de recursión. Por ejemplo, se empieza por renderizar los objetos opacos desde el punto de vista principal, después los opacos de cada recursión de cada portal, posteriormente los objetos translúcidos de cada recursión y finalmente los translúcidos principales.

#### 2.2.5 Conclusión
> Primera persona: personal?

Para este proyecto decidí implementar primero los portales utilizando texturas y observar las dificultades que puedan surgir. Posteriormente quizás implementar otras técnicas?

> No he desarrollado los portales con stencils ni PBR

A continuación se explica en detalle como desarrollar, paso por paso, cada característica del comportamiento de un par de portales.

> En cada punto se exponen los conceptos teóricos, su implementación, los posibles problemas y sus soluciones.¿

## 3. Desarrollo de un portal
> Primera persona plural: tutorial?

### 3.1. Punto de vista relativo

En nuestra aplicación, la cámara principal se controla como en un *FPS*. Su posición y orientación es controlada por el usuario con el teclado y ratón. El desarrollo de un portal es independiente del tipo de control de cámara, pero es importante dejar claro nuestro el punto de vista. La intención es simular una escena en la que el jugador se mueve y mira libremente, como si estuviese allí. Inicialmente es recomendable permitir que el jugador pueda desplazarse en cualquier dirección (*freelook*), para poder flotar y observar el espacio desde toda perspectiva.

Empezaremos con una escena básica:
* Dos plataformas de distintos colores con un objeto de color parecido en un extremo, por ejemplo un cubo. Los colores ayudan a diferenciar el escenario y entender mejor las perspectivas.
* Un portal en el centro de cada plataforma del mismo color que el objeto de la plataforma contraria. Ambos portales orientados en la misma dirección y sentido, hacia los cubos. Cuando los portales estén conectados, a través de cada uno se vera el cubo de su mismo color, situado en la otra plataforma. En realidad no es necesario que tengan marcos, pero así podemos distinguir sus límites y entenderlos más fácilmente.
* El jugador o cámara principal, situado en el otro extremo de cualquier plataforma, no importa.

![test](Render/3.1.1.svg)
> Foto de la vista superior de la escena (representando vision y direccion portales) + vista FP

En la sección X anterior se explicó el funcionamiento y propiedades de una cámara. En la figura 3.1.1, se ha superpuesto una versión esquematizada del espacio de vista de la cámara principal, la del jugador. El cuerpo del jugador se representa con un cubo verde?
> Previamente explicado cámaras y espacios de vista, etc.

Ahora nos centraremos únicamente en el portal azul. En esta versión, el portal simplemente es un marco y se ve a través. Por ello se ve el cubo rojo. Cuando el par de portales sea funcional, queremos ver por el portal azul, la plataforma y cubo azul que están al otro lado del portal rojo.

> Foto de la vista superior de la escena con el espacio de vista partido - SIN FP?

> Punto de vista es el transform. Explicado antes? - revisar que digo mucho posicion y orient

Esta transición no es sencilla. Se necesita pintar la escena desde dos puntos de vista diferentes para poder componer la imagen. El primer punto de vista es el de la cámara principal. El otro lo representamos con una segunda cámara que denominaremos *virtual*. Es virtual porque en realidad no es necesario que sea un objeto cámara. Solo importa su posición y orientación, para poder asignárselas a cualquier objeto. Representarlo como una cámara *virtual* ayuda a entender toda la situación.

> Foto de la vista superior de la escena con el espacio de vista partido y camara virtual

La cámara virtual es azul porque ve lo que se debe mostrarse a través del portal azul. Para obtener su transformación hay que seguir dos pasos:
* 1. Calcular la transformación, dentro del espacio de coordenadas local del portal azul, equivalente a la transformación global de la cámara principal.
* 2. El segundo paso tiene dos alternativas lógicas:
	* A. Si la cámara virtual es hija del portal rojo, basta con aplicarle la transformación local calculada.
	* B. Si no es hija, se calcula la transformación global equivalente a la transformación local calculada, pero como si fuese local al portal rojo.

> Pseudo código de multiplicación matricial?. Explicado porque el inverso de la matriz de transformación obtiene la transformación en coordenadas locales¿?

Aplicada dicha transformación en todo momento, se puede mover cualquier elemento del sistema para apreciar el efecto. Mover o rotar el portal azul o el jugador altera la transformación local calculada en el paso 1. Mover o rotar el portal rojo altera la transformación global final calculada en el paso 2.

> Foto con diferentes posiciones y rotaciones de portal / cámara

Para terminar, introducimos una segunda cámara virtual para representar el punto de vista relativo al otro portal. El cálculo de su transformación es análogo al previo. Cabe destacar que éstos cálculos realizados en un esquema plano, se trasladan directamente al espacio tridimensional. Las multiplicaciones de matrices son las mismas.

> Foto con 3 posiciones con ambas camaras virtuales

### 3.2. Dibujado de las texturas

Hata ahora solo hemos calculado los puntos de vistas
Hasta ahora los portales no tenian texturadasdas

Para ser mas eficientes respecto a memoria utilizaremos un único buffer


## x. Esquema de desarrollo
* Render textures utilizando renderbuffers
	* vs stencils - mas sencillo y no tanto crecimiento de memoria
* Posicion relativa de la camara virtual
	* camara virtual o simplemente transform y utilizar la misma camara
	* desactivar la textura de cada portal antes de renderizar
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

## y. Para realizar explicación + capturas
* Camara orthogonal superior + visualizacion en pantalla
	* toggle para quitar poner + intercambiar con la principal?
* 3D axis en el hud + toggle
* Cuerpos y axis de las camaras representados + toggleable
	* Representar el FRUSTUM de cada camara + toggleable
* Toggle para desactivar portales y ver a traves etc
* Toggle mostrar dirección normal de los protales?
* Switch entre camara principal y extra?

## z. Optimizar
* no renderizar portal si esta fuera de pantalla
	* utilizar el estencil buffer para saber si algo se ha pintado
	* utilizar el frustum de la camara para ver si se va a renderizar
* evitar recursión si no hay portales superpuestos
	* utilizar el stencil para saber si algo ha utilizado recursión
	* utilizar bounding boxes en coordenadas de pantalla
* escalas modificadas?
