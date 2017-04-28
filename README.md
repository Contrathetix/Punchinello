## Punchinello
An overwhelmingly bloatsome OBSE plugin to provide JSON file interface for Oblivion scripts, born out of my own need for a reasonable alternative to INI files. [An open source JSON library](https://github.com/nlohmann/json) is used for the actual JSON file interaction.

On another note, [Punchinello](https://www.youtube.com/watch?v=ufIE9B3H85k) is also a march written by the British composer William Rimmer in the early 20<sup>th</sup> century.

It would be worth a note that my skills at C++ are absolutely horrible, so that whatever there may be here, it will probably not look pretty and will peform even worse than it looks.

### Commands
The commands listed below are available for use in the Oblivion in-game scripting language. The following commands are available for reading from JSON files:

    (value:string_var) JsonGetString filename:string_var key:string_var default_return:string_var
    (value:float)      JsonGetFloat  filename:string_var key:string_var default_return:float
    (value:int)        JsonGetInt    filename:string_var key:string_var default_return:int
    (value:ref)        JsonGetForm   filename:string_var key:string_var default_return:ref

The following commands are available for writing to JSON files:

    (nothing) JsonSetString  filename:string_var  key:string_var  value:string_var
    (nothing) JsonSetFloat   filename:string_var  key:string_var  value:float
    (nothing) JsonSetInt     filename:string_var  key:string_var  value:int
    (nothing) JsonSetForm    filename:string_var  key:string_var  value:ref

The following miscellaneous commands are available:

    (nothing)        JsonEraseKey   filename:string_var  key:string_var
    (keys:array_var) JsonListKeys   filename:string_var  key:string_var

### Compiling the Plugin
For my own sake, I keep forgetting things. Folder structure:

    ...\[project-folder]\
    ...\[project-folder]\common\
    ...\[project-folder]\obse\
    ...\[project-folder]\obse\obse\
    ...\[project-folder]\Punchinello\[this-repo]
From obse and common, the respective .lib files need to be copied to:

    ...\[project-folder]\Punchinello\lib\obse.lib
    ...\[project-folder]\Punchinello\lib\common.lib

Compiled with Microsoft Visual Studio Community 2017, Windows SDK 10 and Windows 10.
