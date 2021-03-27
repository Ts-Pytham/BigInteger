# BigInteger
 Una implementación del BigInteger en C++
<h2>Explicación </h2>

BigInteger es un código que tiene como fin, el manejo de datos numéricos enteros pero sin preocuparse mucho del desbordamiento porque al ser un tipo de dato abstracto y que por dentro tiene un tipo string es muy poco probable que el dato se desborde. Esta implementación de Biginteger puede sumar, restar, multiplicar y proximamente poder dividir, así como métodos lógicos para poder hacer comparaciones entre 2 objetos del mismo tipo.

<h2>Sintaxis para invocar el objeto</h2>

<code>BigInteger bi;</code>

<code>BigInteger bi = 4;</code>

<code>BigInteger bi = "4";</code>

<code>BigInteger bi(dato);</code>

Como podemos ver, para inicializar nuestro objeto podemos asignarle tanto un <code>int</code> como un <code>string</code> o en el caso anterior un <code>const char*</code>.

<h2>Métodos</h2>

Las funciones o métodos son muy sencillas, entre ellas tenemos:

* <code>int size()</code> Esta función obtiene el tamaño o cifras del número.
* <code>BigInteger length();</code> Esta función obtiene el tamaño o cifra del número pero devuelve un BigInteger.
* <code>string toString();</code> Convierte el objeto BigInteger en un string.

<h2>Imágenes</h2>

![image](https://user-images.githubusercontent.com/43942761/112734157-0c17c600-8f12-11eb-873c-b01c379d3404.png)
![image](https://user-images.githubusercontent.com/43942761/112734191-336e9300-8f12-11eb-8335-ba09add7aa49.png)


