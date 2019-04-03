## Punchinello
An overwhelmingly underwhelming OBSE-plugin-wannabe contraption that, while already being an excercise in futility in its own right, also persistently keeps dreaming of one day being able to provide JSON and INI file interfaces for Oblivion scripts, with support for both reading and writing of values. It would be worth a note that my skills when it comes to programming of any description are absolutely horrible, so whatever there may be here, it will probably *not* look pretty and will peform even worse than it looks. Indeed! You definitely *can* benefit from closing that browser tab. Just click the button...

On another note, [Punchinello](https://www.youtube.com/watch?v=ufIE9B3H85k) is also a march written by the British composer William Rimmer in the early 20<sup>th</sup> century.

### Third-Party Libraries
The plugin uses the following third-party libraries, available at Github, to provide the actual functionality:
* [nlohmann/json](https://github.com/nlohmann/json) is used for JSON interaction
* [brofield/simpleini](https://github.com/brofield/simpleini) is used for INI interaction

### Compiling the Plugin
The plugin has been compiled using the OBSE 0021.4 source code from [Alenett/TES-Reloaded-Source](https://github.com/Alenett/TES-Reloaded-Source), both the 'obse' and 'common' sources were the ones from there. Microsoft Visual Studio Community 2017 was used for compiling, on Windows 10 using Windows SDK 10. Folder structure:

    ...\common\
    ...\obse\
    ...\Punchinello\[this-repo-here]

Compiling should be straightforward. Building the solution, Punchinello.sln, should be enough. The 'common' project might need to be retargeted and the SDK version might need to be checked. Other than that, there should not be huge issues.

### Added Commands / Functionality
See the Github wiki for added commands and example usage.
