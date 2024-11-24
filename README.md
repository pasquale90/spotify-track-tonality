# spotify-track-tonality
Retrieve tonality data from Spotify's current playback.

# Building

First, install necessary dependencies, if you don't already have them.

- [libcurl](https://github.com/curl/curl)
- [nlohmann/jsoncpp](https://github.com/nlohmann/json)

Clone the repository
```
git clone https://github.com/pasquale90/spotify-track-tonality.git
```

And finally, build using CMake

```
mkdir build
cd build
cmake ..
make
```

# Usage

After compilation, two independent scripts are generated:
- `authenticateUser`: Used to enable user authentication 

# Usage 

To run the app, you must:
1. Follow the [instructions](https://developer.spotify.com/documentation/web-api) to create an app in spotify's [dashboard](https://developer.spotify.com/dashboard)
2. Replace the values of the variables `client_id`, `client_secret`, and `redirect_uri` within the [spotify/credentials.json](spotify/credentials.json) file:
```
{
    "client_id": "...",
    "client_secret": "...",
    "redirect_uri": "...",
}
```
3. Run `./authenticateUser` to authenticate your account for using the Spotify API.
On first execution, paste the redirect URI into the command prompt to complete the verification process. A `refresh_token` field will be added to the [spotify/credentials.json](spotify/credentials.json) file:
```
{
    "client_id": "your_client_id",
    "client_secret": "your_client_secret",
    "redirect_uri": "your_redirect_uri",
    "refresh_token": "your_refresh_token"

}
```
5. Run `./getCurrentTone` each time you want to retrieve the current playback
3. Run `./authenticateUser` to authenticate your account for using the Spotify API

# Credits
It ought to be mentioned that this repo is based on work from [smaltby/spotify-api-plusplus](https://github.com/smaltby/spotify-api-plusplus) as a basis for its work.

## Todo
 - [] prevent bugs when ads are playing
 - [] add kms features