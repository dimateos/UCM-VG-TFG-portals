# FOLDER STRUCTURE
The visual studio solution is structured as follows:

```
/Dependencies 	-> dependecies lib and includes
/Exes 		-> structured output with common assets
/Inter 		-> intermediate compilation files
/Projects 	-> visual studio projects
/Src 		-> source code
```

* All visual studio temporal files are ignored
* `/Dependencies` and `/Inter` are ignored
* All `.dll` and `.exe` inside `/Exes` are ignored
	* They share `/Assets`, thats why the whole folder cannot be ignored

## DEPENDENCIES

I provided an small `dependencies.zip` you can just unzip and merge all the folders to have the project compiling and running.

Anyway you can add the dependencies yourself:
* Add `glad`, `SDL2-2.0.10`, `glm` and `stb` inside `/Dependencies`
* Add the corresponding SDL `.dll` to `/Exes/x64` and `/Exes/Win32`
