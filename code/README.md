# 2D Strip Packing Problem - Exact Method - BT+CBJ - Bottom-Left-Fill 

Este repositorio tiene la implementacion de backtracking guiado por conflictos (BT+CBJ)

## Instrucciones

Para compilar debe correrse el comando `make` en el directorio raiz del proyecto, de esa forma se creará un ejecutable el cual puede correrse con `./a.out [filename]`, ya que muchas veces las instancias demoran mucho en recorrerse se recomienda correr con `timeout 30s ./a.out [filename]`

## Deploy Automatico de las Pruebas

Existe un Bash Script en el directorio llamado `runtest.bash`, el cual primero se le deben otorgar permisos mediante `chmod +x runtest.bash` y finalmente puede ser ejecutado con `./runtest.bash`, dicho script ejecutará las pruebas para todos los archivos con formato `.TXT` dentro de la carpeta `./inputs`.

## Pequeñas consideraciones

El output se renombro a `[filename].log`, ya que el archivo guarda todo el historial de soluciones mientras se corre el algoritmo. 