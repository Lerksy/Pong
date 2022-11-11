# Pong
Old Atari game named "Pong" as test-task


## Development
Project was developed using MSVS 2019 and set of SDL libraries: SDL2, SDL_image, SDL_TTF.


## Structure

The structure of the project is very simple.

In our `main.cpp` we initialize `GameManager` object and running game event loop.

`GameManager` Object - controls all our entites such as players and ball, also handles game status and tell `SDLScene` to render that scene that is needed by game state.

`TextureLoader` loads all textures from "asset" folder and provides easy access for `SDLScene` to get thom for rendering.

`SDLScene` just gets all data from objects and render their positions.

Our entities (players and balls) controls their moves by them own. Its needed for simplifying controls and calculation logic as well as improve code readability.


## Building

`git clone https://github.com/Lerksy/Pong`, open `.sln` file in your Visual Studio and build.

After building you need add some `.dll` files from the `_include_libs` folder.

**WARNING**
*This project uses C++17 standart. Be careful if you are using old Visual Studio!*
