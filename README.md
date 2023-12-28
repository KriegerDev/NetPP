# NetPP
Simple C++ BSD/ws2 socket wrapper 

## TODO
- [ ] Add Examples
- [ ] Add TCP Support
- [ ] Add solid documentation

## Contributing
Fell free to contribute with this project, just fork it and make a pull request.

## Issues 
I'll be happy to help you with any issue you may have, just open an issue and I'll try to help you as soon as possible.

## Status
This project is under development, so it may have some bugs and missing features.

## Building from source and installing.
```bash 
# netpp root dir...
cmake --preset win32-release
cd build && cd win32-release
cmake --build . --config Release
cmake --install .
```
After these steps, you can use the 
[FindNetPP](cmake/FindNetPP.cmake) for use NetPP in your project.