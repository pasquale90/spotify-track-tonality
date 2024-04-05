# spotify-track-tonality
Retrieve tonality data from Spotify's current playback

# Dependencies
 - [spotipy](https://pypi.org/project/spotipy/)
 - [pybind11](https://github.com/pybind/pybind11)

 # Compilation instructions
 System install:
 - G++ 
 - [Python](https://www.python.org/)
 - cmake
```
$ pip install spotipy
$ pip install pybind11 ([installation tutorial for Windows](https://kezunlin.me/post/8b9c051d/))
```

# Run app

To run the app, you must:
1. Follow the [instructions](https://developer.spotify.com/documentation/web-api) to create an app in spotify's [dashboard](https://developer.spotify.com/dashboard)
2. Replace the values of the variables client_id, secret_id, redirect_uri within the [main.cpp](spotify-track-tonality/main.cpp) file
3. Compile code and run the executatble
4. The first time of execution, a redirect URI will have to be pasted into the command prompt to complete the verification of the user.

# Examples

## Linux
```
mkdir build
cd build
cmake ..
make
mv getCurrentTone ../
cd ..
./getCurrentTone
```

## Windows

```
```