# Pong
Project to develop a SDL2 version of Atari's Pong in C++.

### About SDL2
To install SDL2, check this link [here](https://wiki.libsdl.org/Installation).

### SDL2 libraries
- If you're using Windows, you'll need to install the **developer** libraries below according to your architecture and compiler:
  - [SDL2](https://www.libsdl.org/download-2.0.php)
  - [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
  - [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
  - [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)

- If you're using Ubuntu, you can install it running on your terminal:
```
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

### Compiling on Ubuntu
  - To download and compile, you just have to run the following code:
    ```
    sudo apt-get install git
    git clone https://github.com/leo-ventura/sdl-pong.git
    cd sdl-pong/src
    make
    ./pong
    ``` 

### About the project
I started developing this game just to gain experience, I've never programmed in C++ before so many mistakes will be made along the way.
