SteamAPI_Init
Callbacks
Steam Game Servers
The Steamworks API includes support for running game servers as well as regular clients. A game server, in Steamworks API terms, is an entity in the system that normal users connect to to play multi-player games. This can be connecting over the Internet to a remote game server, or connecting locally to a game server that's in the same process as the client. Game servers have their own set of API functions to use, and their own unique Steam ID for other users to refer to them by.

SteamGameServer_Init
SteamGameServer_Shutdown
SteamGameServer_RunCallbacks
SteamGameServer_ReleaseCurrentThreadMemory
After initializing a game server you have access to the two game server exclusive interfaces ISteamGameServer and ISteamGameServerStats.

ISteamClient which you can access via the global interface: SteamGameServerClient()
ISteamUtils which you can access via the global interface: SteamGameServerUtils()
ISteamNetworking which you can access via the global interface: SteamGameServerNetworking()
ISteamHTTP which you can access via the global interface: SteamGameServerHTTP()
ISteamUGC which you can access via the global interface: SteamGameServerUGC()
ISteamApps which you can access via the global interface: SteamGameServerApps()
If you're running a dedicated game server (one which has no client component), you only have to initialize the game server API's, you don't have to initialize the normal user API.

See Steamworks API Example Application (SpaceWar) for a fully loaded example of using the game server API.

Unlike a game, a dedicated server will usually be run in an environment where there is no Steam Client installed to provide the latest steamworks binaries. In order for the dedicated server to have the latest steam binaries, you will need to include the Dedicated Server Redistributables with your app. Log into partner.steamgames.com and navigate to the technical settings for your app. Then look under "Installation / Redistributables" and check "Dedicated Server Redistributables"

Commercial engine and non-C++ language support
If you're using a commercial game engine or a language other than C or C++ you will want to see what level of support for the Steamworks API is provided for it.

In some engines they provide native built-in support, for others you may need a third-party solution.

If your engine does not have native support you can use the Steam Web API to access many features that Steam supports.

Regardless of how the Steamworks SDK is implemented in your engine you will need to have the latest Steamworks SDK to upload your application to Steam.

NOTE: If some of the software you are shipping on steam is available under a restrictive open source license then please see Distributing Open Source Applications on Steam.

Here are some common engines that people routinely use to ship games on Steam and the relevant documentation on how to get started using the Steamworks SDK with them.

NOTE: Valve does not in any way endorse any of these engines or the third-party solutions. This list is sorted exclusively by name, and is in no way comprehensive, it exists solely as a starting guide. Engines will only be listed if they include native support or have a third-party solution that fits the guidelines. Third-party solutions will only be listed if they are kept reasonably up to date with the Steamworks SDK, are freely available under a permissive license (See: Distributing Open Source Applications on Steam), and have a thread on the Steamworks Discussion Board. We recommend that you consult the community to see which option would work best for your specific setup.

Engine	Native support?	Information
CRYENGINE	✔️
GameMaker Studio 2	✔️	Using The Steamworks SDK With GameMaker: Studio
Godot	❌	Third Party: GodotSteam - Steamworks Developer Discussions support thread
Haxe	❌	Third Party: SteamWrap - Steamworks Developer Discussions support thread
Leadwerks Game Engine	✔️	Leadwerks API Reference › Steamworks
RPG Maker MV	❌	Third party: Greenworks - Steamworks Developer Discussions support thread
Source 2013	✔️	Distributing Source Engine Games / Mods
Unity	❌	Third party: Facepunch.Steamworks - Steamworks Developer Discussions support thread Third party: http://steamworks.github.io - Steamworks Developer Discussions support thread
Unreal Engine 4	✔️	Online Subsystem Steam
Visionaire Studio	✔️	Publish on Steam

ActionScript (Adobe Flash, AIR) Discussion thread
C# Discussion thread Facepunch.Steamworks - Steamworks Developer Discussions support thread http://steamworks.github.io - Steamworks Developer Discussions support thread D Discussion thread DerelictSteamworks - Steamworks Developer Discussions support thread Java Discussion thread steamworks4j - Steamworks Developer Discussions support thread JavaScript Discussion thread Greenworks - Steamworks Developer Discussions support thread Python Discussion thread SteamworksPy - Steamworks Developer Discussions support thread Rust Discussion Thread steamworks-rs - Steamworks Developer Discussions support thread
Discussion thread
C# Discussion thread Facepunch.Steamworks - Steamworks Developer Discussions support thread http://steamworks.github.io - Steamworks Developer Discussions support thread
Discussion thread
Facepunch.Steamworks - Steamworks Developer Discussions support thread
http://steamworks.github.io - Steamworks Developer Discussions support thread
D Discussion thread DerelictSteamworks - Steamworks Developer Discussions support thread
Discussion thread
DerelictSteamworks - Steamworks Developer Discussions support thread
Java Discussion thread steamworks4j - Steamworks Developer Discussions support thread
Discussion thread
steamworks4j - Steamworks Developer Discussions support thread
JavaScript Discussion thread Greenworks - Steamworks Developer Discussions support thread
Discussion thread
Greenworks - Steamworks Developer Discussions support thread
Python Discussion thread SteamworksPy - Steamworks Developer Discussions support thread
Discussion thread
SteamworksPy - Steamworks Developer Discussions support thread
Rust Discussion Thread steamworks-rs - Steamworks Developer Discussions support thread
Discussion Thread
steamworks-rs - Steamworks Developer Discussions support thread
Flat interface for binding to other languages
The SDK has a few features to facilitate the creation of binding layers for other languages.

steam_api.json describes (almost all of) the interfaces, types, and functions in the SDK. It is intended that this file be used by an automated process to generate binding layer. We hope that this can be used to automate 95% of the work, but there are still a few special cases that need to be handled manually. In particular, CSteamID and CGameID will probably require special handling by your binding layer to make it efficient.
Technical Details
Steam uses a variety of techniques to expose functionality to your application. It's by no means critical to understand exactly how the Steamworks API works but it's fairly simple and can be useful in planning out how to code your game with Steam integration in mind.

