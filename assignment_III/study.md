**Caso de Estudio:**

Juego para que los niños aprendan el abecedario

Contexto:
Una aplicación educativa hecha para los niños que están aprendiendo a leer. El juego les pide que digan dos letras cualquiera del abecedario en la que los niños tendran que leer y decir si son mayusculas.

Problema
Hay que asegurarse de que los muchachos no ingresen números, signos o otro caracter que no sea de alfabeto.
Si ponen las letras al revés (como "Z" primero y luego "P"), el juego las ordena solo.

Solución
Este código hace eso mismo:

- Revisa que las letras sean del abecedario con isalpha().

- Las convierte en mayúsculas con toupper().

- Las organiza con swap() si están al revés.

- Y al final, te suelta todas las letras entre esas dos, una al lado de la otra.

Ejemplo
Entrada:

        Primera letra: g

        Segunda letra: c

    Salida:

    Las letras entre 'C' y 'G' son:

    C D E F G
