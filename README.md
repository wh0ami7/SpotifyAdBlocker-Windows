# SpotifyAdBlocker-Windows

This project is a try to port [This one](https://github.com/abba23/spotify-adblock-linux) to windows
the way it is done is with dll redirection, the call to `cef_urlrequest_create` is traited with a custom function that blocks urls that are blacklisted, and it redirects the good URLs to the original function.

## Build

Prerequisites:

  * `Visual Studio 2019`
  
--------------------

  * Clone this repo
  * download `https://cef-builds.spotifycdn.com/cef_binary_89.0.18%2Bgb36241d%2Bchromium-89.0.4389.114_windows32_minimal.tar.bz2` and unzip the `include` folder to `SpotifyAdBlocker-Windows\extern` folder
  * open `SpotifyAdBlocker-Windows.sln`
  * build the project (of course after you take a look at what's going on there to make sure no nasty thing is happening :p )
  * locate where is the output libcef.dll, it should be in `$(SolutionDir)bin\$(Platform)\$(Configuration)\`
  * open Spotify folder, it should be in `%appdata%\Spotify`, or if you have a shortcut, then right click it and click on `Open File Location`
  * rename the `libcef.dll` in that folder to `libcefNative.dll`
  * move or copy the `libcef.dll` that you just compiled into the `Spotify` folder
  

### looks like you are done now! open Spotify and enjoy your music without ads.

## TODO:

  - [ ] the linux version wraps `getaddrinfo` to allow only URLs in the white list to be traited, but I couldn't do the same thing in windows because for security reasons, so as a todo try to find a work around.
