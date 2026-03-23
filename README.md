# PROYECTO PROGRAMACION III
# BUSCAMINAS

## Integrantes
- Jiny Perez
- Luis Noriega
- Jose Garcia

## Estado actual para publicacion
- El proyecto usa Qt 6 con CMake.
- Ya puede generar un ejecutable de Windows.
- El ranking ahora se guarda en la carpeta de datos del usuario, lo cual evita errores de permisos al instalar en `Program Files`.

## Requisitos
- Qt 6.10.1 MinGW 64-bit
- MinGW 13.1.0
- CMake de Qt
- Ninja

Rutas detectadas en este proyecto:
- `C:/Qt/6.10.1/mingw_64`
- `C:/Qt/Tools/CMake_64/bin/cmake.exe`
- `C:/Qt/Tools/Ninja/ninja.exe`
- `C:/Qt/6.10.1/mingw_64/bin/windeployqt.exe`

## Compilar en Release
Desde PowerShell, en la raiz del proyecto:

```powershell
& "C:/Qt/Tools/CMake_64/bin/cmake.exe" -S . -B build/Release -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="C:/Qt/6.10.1/mingw_64"
& "C:/Qt/Tools/CMake_64/bin/cmake.exe" --build build/Release
```

El ejecutable debe quedar en:
- `build/Release/Proyecto_Buscaminas.exe`

## Preparar carpeta distribuible
Para copiar las DLLs y plugins de Qt necesarios:

```powershell
& "C:/Qt/6.10.1/mingw_64/bin/windeployqt.exe" --release "C:/C++/Proyecto_Buscaminas/build/Release/Proyecto_Buscaminas.exe"
```

Despues de eso, prueba abrir el `.exe` directamente desde `build/Release`.

## Generar paquete instalable
Si tienes NSIS instalado:

```powershell
& "C:/Qt/Tools/CMake_64/bin/cmake.exe" --install build/Release --prefix build/package
Set-Location build/Release
& "C:/Qt/Tools/CMake_64/bin/cpack.exe" -G NSIS
```

Si no tienes NSIS, puedes sacar al menos un paquete `.zip`:

```powershell
Set-Location build/Release
& "C:/Qt/Tools/CMake_64/bin/cpack.exe" -G ZIP
```

## Recomendaciones antes de publicar
- Probar el ejecutable en otra PC donde no este instalado Qt Creator.
- Verificar que el ranking se guarde y se vuelva a cargar.
- Agregar un icono de aplicacion y del instalador.
- Subir la version del proyecto en `CMakeLists.txt` cuando hagas una nueva entrega.
