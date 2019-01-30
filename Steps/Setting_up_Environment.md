# Setting up Game Environment

## Libraries
**SFML**  
Download SFML library, extract it and place contents in a folder named SFML.

## Creating Project Template
1. Create C++ console project.  
2. In project properties, add include directories in C++ (path of _SFML/include_).  
3. Add path of _SFML/lib_ for Linker->general.  
4. In Debug configuration -> Linker -> Input add "_sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;sfml-network-d.lib;sfml-audio-d.lib;_".  
5. Export project as Template.  

## Creating Project Timber
1. Create new project from template.  
2. Copy _dll_ files from SFML to our project.