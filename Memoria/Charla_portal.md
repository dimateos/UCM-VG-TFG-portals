Notas sobre la charla de portal (Ya tiene muy buenos timestamps en la descripcion)
> https://www.youtube.com/watch?v=ivyseNMVt-4

LICENSE: (CC BY-NC-SA 4.0) Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International Public License

* Parece estar dibujando igualmente toda la pantalla antes de hacer el mapeo de vertices en coordenadas de pantalla
* Parece que no hacen nada especial para evitar el clipping de la camara en el portal


# 00:00:00 - Introduction
## 00:01:58 - What is a Portal?

Un portal es una discontinuidad del espacio 3D donde la cara trasera de un rectángulo 2D es definida como la cara frontal de otro rectángulo 2D localizado en otra posición. Esta discontinuidad implica que no se desplace ninguna geometría ni se sobreponga el espacio de maneras incomprensibles.

> gráfico 2D mostrando efecto

Otra forma de pensarlo es como el marco de una puerta que separa dos estancias, solo que que en realidad éstas no son tangentes en el espacio 3D. La transición es totalmente inapreciable, como si ambos lugares estuviesen simplemente conectados. Ello no implica que un par de portales deban estar siempre contiguos a una pared, pero en estos casos, no existe forma de notar la diferencia. Podrian estar separados centimetros o millas.

> video mostrándolo en acción una puerta que en realidad es un portal por razones técnicas

La parte interesante de los portales ocurre en su superficie y no fuera de ella. Por ello se debe evitar que se vea cualquier cosa interesante que esté ocurriendo fuera de ella. Como un buen truco de magia, solo que ente caso serían situaciones visuales carentes de sentido.


# 00:04:40 - Rendering
## 00:04:52 - Texture vs Stencil Tradeoffs

Texture:
* Texturas separadas para cada vista del portal. Recursion necesita bastante memoria.
* Se necesita pintar primero los portales traseros.
* La textura 2D puede contener visual artifacts ya que realmente no tiene profundidad.
* La version mas simpre de implementar si se limita a 1 nivel de profundidad (nunca un portal se ve a traves de otro)

Stencil:
* Se renderiza todo en el mismo buffer
* Se dibuja primero la vista principal y posteriormente se renderiza si la recursion si es necesaria
* La profundidad es real, no textura 2D
* El orden de renderizado es complejo (recursion despues de opacos pero antes de transparencias etc)

> video mostrándolo en acción dos portales - todo es 1:1 - te puedes hacer TP a la camara virtual y las superficies coinciden exactamente. No se dibuja la pantalla entera en la textura, sino que solo lo que se ve a traves del mismo. Se utiliza las coordenadas en screen space. Se dibuja desde el mismo sitio el mismo trozo de pantalla.

> tmb se puede apreciar que son coplanares luego se utiliza un clip plane para no mostrar nada detras del portal de salida

## 00:09:35 - Rendering Using Stencils

En Portal se utiliza el stencil buffer para dibujar las secciones de pantalla adecuadas para cada portal. Pero ademas se entrelaza con la recursión dando valores al estencil buffer de 0-3 de manera muy inteligente. Se dibuja hasta maximo nivel de profundidad, posteriormente los objetos translucidos de ese mismo nivel de profundidad y se "borra" el portal de la escena reduciendo el stencil buffer. Asi hasta el nivel base que completa el renderizado. No usa memoria extra para superficies de portal.

> ejemplo usando puentes de luz uno encima del otro, con recursion.

## 00:15:36 - Duplicate Models

No usa copia física sino que transporta los pixeles al otro lado del portal? Sin copia sino que en cada frame lo dibuja movido? Te ahorras memoria de copia. Aun asi cre oque posteriormente habla de como si utilizan una copia al otro lado para la física.

## 00:16:36 - Clip Planes

Habla de como el objeto movido se ve también por la parte posterior del portal luego es necesario utilizar un clip plane para que no se vea la mitad incorrecta del slice. Supongo que utiliza los mismo clip planes para la proyección oblicua de las camaras virtuales.

## 00:17:44 - Banana Juice

Nombre extraño para el problema complicado de evitar la oculusion de objetos que esten entre la superficie del portal y la camara virtual. Y efectivamente usan sin mas el mismo clip plane que para las entidades. Le costo como 2 dias entenderlo y arreglarlo.

## 00:19:44 - Recursion

Solamente hacen recursion dos niveles y en ese nivel ya se ve la textura del nivel anterior de recursion del frame anterior copiada. Evitan el efecto de snake al mover lateralmente la camara. Si no se puede ver el segundo portal (faltaria textura) lo estiran proporcionalmente.

> se nota el efecto debido a que no varia el cono de vision con la profundidad

## 00:23:19 - Third Person Gotchas

Diferentes problemas al cambiar de modo de renderizado en primera y tercera persona. Dibujar tercera persona a traves de portales pero evitandolo cuando estas atravesando uno

## 00:24:48 - Pixel Queries

Screen space operations like dimmed lights glare close to edges of screen must be diferent for a portal view. Otherwise lights in different screen space are dimmed at unison.


# 00:26:34 - Design
No me interesan para este pryecto.


# 01:00:25 - Physics
## 01:00:43 - Volumes, Vectors, and Planes

Colliders para detectar objetos que pasan a estar proximos al portal y raycasts para los rayos que atraviesan el portal. No importa la parte trasera del portal (pared).

## 01:03:41 - Carving Holes

Replica del espacio local cercano al portal añadiendo un agujero a la pared.

## 01:07:20 - Collision Lists

Para determinar si el jugador debe colisionar con el mundo o con los objetos fisicos clonados. Se usan las listas que determinan los colliders cercanos al protal

## 01:08:50 - Shadow Clones

Para mantener la continuidad del espacio de objetos dinamicos que peuden atravesar el portal.


# 01:11:32 - Q&A (just the ones interesting for this project)

* Lights and shadows thorugh portals - no se notaba apenas, solamente en los momentos donde peor iba.
* Performance of multiple scenes with stencil buffer - 01:13:37 - Reduce Rendering Frustum
	* Custom frustum con 4 lados que confinen el minimo espacio a traves del portal para las camaras virtuales
	* No ayuda tanto ya que ya tienes el stencil buffer indicando que pixeles no dibujar
		* Stencil: post fragment calculation - Frustum clip: post vertex calculation

* ingame microphone and speaker for each side of the portal, but cheap.
* source vs unity - prebaked lightning?

* unanswered - escribo lo que supongo podrian decir
	* camera interpolation - como saben transformar la posicion de la camara virtual?
	* discontinuous interpolation - no lo hacen cada frame o quizas se refieren a las recursiones fake
	* moving portals - no aportaba mucho a puzles y complicaba las listas de colision de los portales
	* non rotating player bounding box - no aporta nada a sus niveles con esquinas de 90
	* Unstuck - smooth player controller haciendo steps adecuados para un movimiento suave
	* binary gravity - diseño de niveles con portales girados lateralmente

