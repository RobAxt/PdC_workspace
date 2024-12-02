# TP Final 2024 2C

## Herramientas
```bash
sudo apt install git
sudo apt install clang-format
sudo apt install pre-commit
sudo apt install valgrind
sudo apt install doxygen
```

## Inicializacion de entorno

```bash
:~/PdC_workspace$ git init
:~/PdC_workspace$ pre-commit install
```

## Estructura del Proyecto
```
TP_Final/
├── src/                     # Archivos fuente (.c)
├── inc/                     # Archivos de encabezado (.h)
├── bin/                     # Ejecutables generados
├── makefile                 # Archivo de construcción
├── doxyfile                 # Archivo de formato de documentacion
├── .clang-format            # Archivo oculto de formato de codigo
├── .pre-commit-config.yaml  # Archivo oculto de configuracion de Hooks de pre-commit
├── .gitignore               # Archivo oculto para ignorar archivos o carpetas a commitear
├── LICENSE.txt              # licencia MIT
└── README.md                # Este archivo
```

## Compilación

Para compilar el proyecto, asegúrate de tener instalado `gcc` y `make`. Luego, simplemente ejecuta el siguiente comando en la terminal dentro de la carpeta del proyecto:

```bash
make
```

## Ejecución

Una vez que el proyecto está compilado, puedes ejecutar el servidor con el siguiente comando:

```bash
make run
```

## Limpieza de Archivos

Si deseas limpiar los archivos compilados y eliminar el contenido del directorio de construcción (bin), ejecuta:

```bash
make clean
```

## Enunciado del proyecto

[TPF 2024 2C Enunciado](./TP%20final%202024%202C.pdf)

## Funcionamiento del Servidor

En funcionamiento normal el servidor responde de la siguiente manera:
