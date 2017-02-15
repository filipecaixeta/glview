Glview

Get data from Arduino to rotate a 3D model.

======

REQUISITOS
------------

* QT5
* QtOpenGL
* OpenGL
* Freeglut
* CMake MINIMUM VERSION 2.8.11 ou QMake
* Make

COMPILAR
------------

Considerando ja esteja no diretorio do projeto

Crie um diretorio para o binario
`mkdir build`

Entre no diretorio
`cd build`

Rode o cmake
`cmake ..`

Sempre que for compilar o projeto e não forem incluidos novos arquivos execulte o make
`make`

Caso algum arquivo seja adicionado ao projeto, adicione no CMakeLists.txt e execulte o cmake novamente
`cmake ..`

Para rodar o binario digite
`./gl`


