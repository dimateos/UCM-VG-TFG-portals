# MOTOR GRÁFICO CON PORTALES PARA SIMULAR ESCENAS 3D NO EUCLIDIANAS

* **Diego Mateos Arlanzón** *dimateos@ucm.es*
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
> Esta sección hace referencia a la parte escrita del trabajo. Se puede encontrar en la carpeta [docs](./.).

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
