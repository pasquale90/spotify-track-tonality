# spotify-track-tonality
This project retrieves tonality data from Spotify's current playback.

# Building
To build this project, please follow these steps:

### Install the following dependencies:

- [libcurl](https://github.com/curl/curl)
- [nlohmann/jsoncpp](https://github.com/nlohmann/json)

### Clone the repository:
```
git clone https://github.com/pasquale90/spotify-track-tonality.git
```

### Build using CMake:

```
mkdir build
cd build
cmake ..
make
```

# Usage

Upon successful compilation, two executables are generated:

- `authenticateUser`: Facilitates user authentication with Spotify.
- `getCurrentTone` : Retrieves the tonality of the current playback.

### To use the application:

1. Follow the [instructions](https://developer.spotify.com/documentation/web-api) to create a `Spotify Developer Application` using the Spotify's [dashboard](https://developer.spotify.com/dashboard).
 
2. Configure credentials, by editing the [spotify/credentials.json](spotify/credentials.json) file, replacing the placeholders for `client_id`, `client_secret`, and `redirect_uri`.
```
{
    "client_id": "...",
    "client_secret": "...",
    "redirect_uri": "..."
}
```
##### `hint`
```
{
    "redirect_uri_example": "http://localhost/8080/callback"
}
```

3. Run `./authenticateUser` to authenticate your account with the Spotify API.
During the first run, you will need to accept the access request, and paste the URL you've been redirected to into the command prompt, to complete the verification process. Upon successful verification, a `refresh_token` field will be added to the [spotify/credentials.json](spotify/credentials.json) file.
```
{
    "client_id": "your_client_id",
    "client_secret": "your_client_secret",
    "redirect_uri": "your_redirect_uri",
    "refresh_token": "your_refresh_token"
}
```
4. Run `./getCurrentTone` each time you want to retrieve the tonality of the current playing track.

# Credits
Please note, this repository selectively adapts elements the foundational work of [smaltby/spotify-api-plusplus](https://github.com/smaltby/spotify-api-plusplus).

## Todo
 - [x]  Implement bug prevention when ads are playing.

 - [] Add KMS features
