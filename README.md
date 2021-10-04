# Sistemas Operativos: Laboratorio 1 (VGA)

## Introducción

El laboratorio consiste en la implementación de un driver **VGA** (*Video Graphics Array*) en **xv6**, esté es un sistema operativo desarrollado con fines didácticos por MIT. El objetivo principal es poder pasar del modo texto al modo gráfico o viceversa y poder aprovecharlo para realizar un dibujo o animación por pantalla.

## Modo de ejecución

Una vez clonado el repositorio desde bitbuket, debemos escribir las siguientes instrucciones por lineas de comando:

```
> $ cd so21lab2g12/xv6/

> $ make qemu

> $ testplot
```
## Proceso de desarrollo

El desarrollo del laboratorio fue bastante confuso al principio debido a que no sabíamos muy bien que registros utilizar para cambiar de modo texto a modo gráfico, esto lo pudimos resolver por medio de la [super ayuda](http://files.osdev.org/mirrors/geezer/osd/graphics/modes.c) donde se describen los registros correspondientes a cada modo.

Una vez identificado los puertos que se utilizan para cambiar de modo gráfico. Implementamos la función `selec_mode` que cambia al modo gráfico con la opción `1` y a texto con `0`. Usamos la función `write_regs` para escribir los registros y poder pasar al modo gráfico. Luego para ir de modo gráfico a texto y poder recuperar las fuentes usamos la función `set_font` la cual modificamos de su implementación original propuesta [aquí](https://forum.osdev.org/viewtopic.php?f=1&t=25375). También implementamos la función `clear_screen` para poder limpiar la pantalla y no queda basura.

La función `vgainit` que imprime "SO2021" en el margen de la pantalla, inicialmente imprimía cada carácter por medio de la función `P2V`. Luego se decidió optimizar agregando la opción de imprimir cualquier palabra, modificando el arreglo de texto.

Para poder implementar las *syscall* `modeswitch` y` plotpixel` se tuvo que explorar el funcionamiento de las ya existentes en **xv6** por medio del comando `grep`. Para ello se modificaron los archivos` defs.h, syscall.c, syscall.h, sysproc.c, user.h` y `usys.S` para definirlos correctamente como llamadas al sistema. La llamada `modeswitch` se implementó como un programa de usuario creando el archivo` modeswitch.c` y modificando el `Makefile`.

Luego se implementaron otras *syscall* adicionales como `plotrectangle`, `plotcircle` para un mejor desarrollo del proyecto. Y también al cambiar a modo gráfico es posible utilizar la paleta de 256 colores disponible en [VGA](https://www.fountainware.com/EXPL/vga_color_palettes.htm).

Para poder realizar la animación se hicieron uso de las *syscall* y también se implementaron otras funciones como `plotsquare` que dibuja un cuadrado por pantalla, `random` para generar números aleatorios y de esta forma pintar pixeles,`plotgeneral` que sirve para pintar por pantalla los *arrays* de colores que definimos en `testplot.h` y también poder cambiarles de tamaño.  

## Modularización

Las principales funciones para el cambio de modo decidimos implementarla en los archivos para `vga.c` y `vga.h` para que el código del driver quede independiente del de `xv6`. Finalmente agregamos los archivos `testplot.c` donde se encuentran las funciones necesarias para plotear la animación y en `testplot.h` los *arrays* de colores.

## Integrantes del grupo:

* Castellaro, Agustín.
* Mansilla, Kevin Gaston.
* Ramirez, Lautaro.
