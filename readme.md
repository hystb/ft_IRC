<div align="center">
<h1 align="center">
<img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" width="100" />
<br>FT_IRC</h1>
<h3>◦ Connect, collaborate, with ft_IRC!</h3>
<h3>◦ Developed with the software and tools below.</h3>

<p align="center">

</p>
<img src="https://img.shields.io/github/last-commit/hystb/ft_IRC?style=flat-square&color=5D6D7E" alt="git-last-commit" />
<img src="https://img.shields.io/github/commit-activity/m/hystb/ft_IRC?style=flat-square&color=5D6D7E" alt="GitHub commit activity" />
<img src="https://img.shields.io/github/languages/top/hystb/ft_IRC?style=flat-square&color=5D6D7E" alt="GitHub top language" />
</div>

---

## 📖 Table of Contents
- [📖 Table of Contents](#-table-of-contents)
- [📍 Overview](#-overview)
- [📦 Features](#-features)
- [📂 repository Structure](#-repository-structure)
- [⚙️ Modules](#modules)
- [🚀 Getting Started](#-getting-started)
    - [🔧 Installation](#-installation)
    - [🤖 Running ft_IRC](#-running-ft_IRC)
---


## 📍 Overview

The repository is an IRC (Internet Relay Chat) server program called ft_IRC. It allows users to connect to an IRC server, join channels, and communicate with other users. The program includes components such as the server, channels, clients, command handler, and logging functionality. It supports various commands such as join, quit, kick, invite, topic, mode, ping, and privmsg. The codebase also includes an IRC bot that can connect to a server, join channels, and respond to commands using an AI language model. The repository provides a Makefile for easy compilation and building of the program.

---

## 📦 Features

|    | Feature            | Description                                                                                                        |
|----|--------------------|--------------------------------------------------------------------------------------------------------------------|
| ⚙️ | **Architecture**   | The codebase follows a monolithic architecture. It consists of a server component that handles connections with clients, manages channels, and processes user commands. It also includes a bot component that connects to an IRC server, joins a channel, and responds to commands. The codebase has separate directories for headers, source files, and the bot. It follows a file-based organization where related files are grouped together.|
| 🔗 | **Dependencies**   | The codebase has dependencies on external libraries such as socket programming libraries for network communication. It also relies on standard C++ libraries for file handling and string manipulation. Additionally, the codebase includes dependencies on other files within the project, such as header files and source files. These dependencies are managed through include statements and Makefile configurations.|
| 🧩 | **Modularity**     | The codebase demonstrates some level of modularity by organizing related functionalities into separate components, directories, and files. The server component is organized into directories for headers, source files, and specific functionalities like command handling and network communication. The bot component is placed in a separate directory. However, there is room for improvement in terms of further breaking down the codebase into smaller, more interchangeable components.|

---


## 📂 Repository Structure

```sh
└── ft_IRC/
    ├── Makefile
    ├── bot/
    │   ├── IRCBot.cpp
    │   ├── IRCBot.hpp
    │   ├── Makefile
    │   └── main.cpp
    ├── headers/
    │   ├── Channel.hpp
    │   ├── Client.hpp
    │   ├── Command.hpp
    │   ├── CommandHandler.hpp
    │   ├── Server.hpp
    │   ├── config.hpp
    │   └── log.hpp
    └── src/
        ├── commandhandler/
        │   ├── Command.cpp
        │   ├── CommandHandler.cpp
        │   ├── commands/
        │   └── log.cpp
        ├── main.cpp
        ├── messages/
        │   ├── Channel.cpp
        │   └── Client.cpp
        └── network/
            └── Server.cpp

```

---


## ⚙️ Modules

<details closed><summary>Root</summary>

| File                                                           | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          |
| ---                                                            | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
| [Makefile](https://github.com/hystb/ft_IRC/blob/main/Makefile) | This Makefile is used to compile and build an IRC server program called ircserv. The program consists of various components, including the bot, headers, and source files.The main.cpp file is the entry point of the program, while the server.cpp, channel.cpp, and client.cpp files handle network-related functionalities. The commandhandler.cpp file contains command-handling logic, and the log.cpp file manages logging functionality. Additionally, there are separate source files for each command supported by the IRC server.The Makefile specifies the compiler and flags, as well as the target name. It compiles all the source files and creates corresponding object files in the.obj directory. The compiled object files are then linked together to generate the executable ircserv.There are additional targets defined in the Makefile, such as bonus to build the bot, clean to remove object files, fclean to remove the executable and object files, and re to perform a clean build. |

</details>

<details closed><summary>Src</summary>

| File                                                               | Summary                                                                                                                                                                                                                                                                                                              |
| ---                                                                | ---                                                                                                                                                                                                                                                                                                                  |
| [main.cpp](https://github.com/hystb/ft_IRC/blob/main/src/main.cpp) | The code in the main.cpp file checks the command line arguments, specifically the port and password, and then creates an instance of the Server class. If the command line arguments are not provided or are invalid, error messages are printed. The Server instance is then started by calling the start() method. |

</details>

<details closed><summary>Commandhandler</summary>

| File                                                                                                  | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| ---                                                                                                   | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| [log.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/log.cpp)                       | The code in the log.cpp file contains a collection of functions that handle various responses and error messages for an Internet Relay Chat (IRC) server. These functions are responsible for sending messages to clients, such as welcoming them to the network, providing server information, notifying about channel modes and topics, and handling errors related to clients and channels. Additionally, there are functions that log certain events, such as when a client joins a channel, invites another client, kicks a client, or modifies channel modes. |
| [CommandHandler.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/CommandHandler.cpp) | The code in `CommandHandler.cpp` defines the implementation of the `CommandHandler` class. It contains the constructor and destructor for the class, as well as the `commands` and `handleCommand` functions. The `commands` function handles the execution of different commands based on the input command string. The `handleCommand` function takes in an input string, a client object, a map of channels, and a map of clients, and creates a `Command` object to execute the command.                                                                        |
| [Command.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/Command.cpp)               | The code is a part of an IRC (Internet Relay Chat) bot implementation. It includes the Command class, which is responsible for parsing user input and extracting commands and parameters. The constructor takes in the user input, a pointer to the client object, a map of channels, and a map of clients. The parse function splits the input into the command, content, and parameters. The class also includes getter functions to access the parsed values.                                                                                                    |

</details>

<details closed><summary>Commands</summary>

| File                                                                                             | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| ---                                                                                              | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| [pass.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/pass.cpp)       | The code in `pass.cpp` is part of an IRC (Internet Relay Chat) bot. It handles the `PASS` command, which is used to authenticate a client with a password. The `refuseConnection` function is used to handle different scenarios in which the connection should be refused, such as when the command is missing arguments or when the password is incorrect. The `pass` function receives a command object and checks if the client's password is already unlocked. If it is, it returns an error indicating that the client is already registered. If not, it checks if the command has the correct number of parameters. If not, it calls `refuseConnection` with the appropriate reason. If the number of parameters is correct, it compares the password parameter with the stored password. If they match, it sets the password as unlocked for the client.                                                                                                                                                    |
| [ping.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/ping.cpp)       | The code is part of an IRC (Internet Relay Chat) bot application. It includes a command handler that handles the ping command. The ping function takes a Command object as a parameter and extracts the parameters and client information from it. If the number of parameters is not equal to 1, it returns an error message. Otherwise, it sends a PONG message back to the client.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               |
| [invite.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/invite.cpp)   | The code is a part of an IRC (Internet Relay Chat) server implementation. It contains a function called invite in the CommandHandler class. This function handles the invite command in IRC. It checks if the command has the correct number of arguments and if the specified channel and client exist. It then checks if the inviting client has the necessary privileges to invite a user to the channel. If all conditions are met, it adds the invited client to the channel's invited list and logs the invitation.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           |
| [quit.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/quit.cpp)       | The code is a part of an IRC (Internet Relay Chat) bot project. It consists of a directory structure with source code files, header files, and a Makefile for build automation. The specific code in quit.cpp defines functions related to handling the QUIT command in the IRC protocol. It includes a function that broadcasts a message to other clients when a client disconnects and a function that handles the QUIT command, setting the client's disconnection status and notifying other clients.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          |
| [topic.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/topic.cpp)     | The code above is a part of a larger codebase for an IRC bot. This specific file, topic.cpp, contains the implementation of the topic command handler. The topic command allows the bot to set or retrieve the topic of a specific channel in the IRC network. The code checks if the command has the necessary parameters, retrieves the channel name and checks if the channel exists. If the channel exists and the client is a member of the channel, the code sets or retrieves the topic accordingly. If any errors occur during the process, appropriate error messages are returned.                                                                                                                                                                                                                                                                                                                                                                                                                        |
| [mode.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/mode.cpp)       | The code is a part of an IRC (Internet Relay Chat) server implementation and specifically handles the mode command. This command allows users to modify various properties of a channel, such as adding or removing channel operator privileges, setting an invite-only mode, restricting topic changes, setting a channel password, and setting a user limit for the channel. The code verifies the command parameters, checks the validity of the mode string, and performs the requested action on the channel based on the flag provided.                                                                                                                                                                                                                                                                                                                                                                                                                                                                       |
| [privmsg.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/privmsg.cpp) | The code in privmsg.cpp is part of a larger project called ft_IRC. It handles the PRIVMSG command in an Internet Relay Chat (IRC) server. It checks the parameters passed with the command and performs different actions based on the target. If the target is a channel, it sends the message to all clients in the channel. If the target is a specific client, it sends the message directly to that client. If the target is invalid, it returns an error message.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| [user.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/user.cpp)       | The code in the user.cpp file is part of a larger project called ft_IRC. It is a command handler that handles the USER command in an IRC (Internet Relay Chat) bot. The user function takes a command object as its parameter and performs various checks and operations. It checks if the client is already connected, if the parameters of the command are correct, and sets the real name and username of the client accordingly. Finally, it calls the doLogin function of the client.Overall, this code is responsible for handling the USER command in the IRC bot and managing the relevant client information.                                                                                                                                                                                                                                                                                                                                                                                              |
| [join.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/join.cpp)       | The code is a part of an IRC (Internet Relay Chat) bot implemented in C++. It handles the join command, which allows clients to join a channel. The checkArgsJoin function checks the validity of the command's arguments, such as the channel name and password. The join function is called by the command handler and performs the necessary checks and actions to join a channel, including creating a new channel if it doesn't exist, checking channel membership, invite-only and password restrictions, adding the client to the channel, and updating the client and channel information.                                                                                                                                                                                                                                                                                                                                                                                                                  |
| [part.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/part.cpp)       | The code in the file part.cpp is part of a larger project called ft_IRC. It is a command handler for an IRC bot. The part command allows a client to leave a specific channel. The code checks if the necessary parameter is provided and returns an error message if not. It then checks if the channel exists and returns an error message if not. If the client is a member of the channel, it sends a message indicating that the client has left the channel, and removes the client from the channel's list of members. If the client is not a member of the channel, it returns an error message.                                                                                                                                                                                                                                                                                                                                                                                                            |
| [kick.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/kick.cpp)       | The code is a part of an IRC (Internet Relay Chat) bot application. It is responsible for handling the kick command. The checkArgsKick function validates the arguments of the command. The kick function checks if the client and channel exist, if the client has operator privileges, if the specified client is a member of the channel, and if the client is currently on the channel. If all conditions are met, it sends a kick message to the channel and removes the client from the channel.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
| [nick.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/nick.cpp)       | The code in the file nick.cpp is part of a larger codebase for an IRC (Internet Relay Chat) bot. This specific file contains a function called nick that handles the NICK command in the IRC protocol. The function takes a Command object as a parameter, which contains information about the command and the client who issued it. It extracts the parameters from the Command object and performs various checks on the nickname provided. If the nickname is invalid (contains certain characters or exceeds a certain length), the function returns an error message. If the nickname is already in use by another client, it also returns an error message. If the nickname passes all the checks, the function updates the client's nickname and broadcasts the change to all connected clients. If the client already had a nickname, it sends a message to update the nickname. If the client didn't have a nickname before, it sets the provided nickname and performs additional login-related actions. |

</details>

<details closed><summary>Messages</summary>

| File                                                                              | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  |
| ---                                                                               | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      |
| [Client.cpp](https://github.com/hystb/ft_IRC/blob/main/src/messages/Client.cpp)   | The code includes the implementation of the Client class, which represents a client connected to a server. It contains getters and setters for various attributes such as socket, buffer, nickname, username, realname, etc. It also includes methods for sending messages, performing login, and broadcasting messages to other clients in the same channels. The code also includes some helper functions, such as getting a client based on nickname and a method to format and send messages to the client's socket. |
| [Channel.cpp](https://github.com/hystb/ft_IRC/blob/main/src/messages/Channel.cpp) | The Channel class represents a channel in an Internet Relay Chat (IRC) system. It contains functions to add and remove clients, set and unset operators, add and remove invited clients, set various channel attributes such as password, topic, and limits, and retrieve information about the channel and its members. The class also includes functions to send messages to clients in the channel and to update the channel's mode and member list.                                                                  |

</details>

<details closed><summary>Network</summary>

| File                                                                           | Summary                                                                                                                                                                                                                                                                                                                                                                                                                      |
| ---                                                                            | ---                                                                                                                                                                                                                                                                                                                                                                                                                          |
| [Server.cpp](https://github.com/hystb/ft_IRC/blob/main/src/network/Server.cpp) | The code provided represents the implementation of a server in an Internet Relay Chat (IRC) system. The Server class manages connections with clients, receives and processes messages, and handles client disconnections. It listens for incoming connections, accepts clients, and manages client interactions using the CommandHandler class. The Server class also handles signals such as SIGINT, SIGQUIT, and SIGTSTP. |

</details>

<details closed><summary>Headers</summary>

| File                                                                                       | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| ---                                                                                        | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| [Command.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/Command.hpp)               | The Command.hpp file contains the declaration of the Command class. This class represents a command in an IRC (Internet Relay Chat) system. It has private member variables to store the input, command, parameters, content, client, channels, and clients associated with the command. The class has a parse() function to parse the command input. The public interface includes getters for the input, command, parameters, content, channels, clients, and client. It also includes a constructor and a destructor. The class also defines an exception class for invalid command syntax.                                                                                                             |
| [config.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/config.hpp)                 | The code provided is a configuration file `config.hpp` for an IRC (Internet Relay Chat) server. It defines various configurations such as maximum number of clients, network name, server name, server version, and rules for nickname and channel lengths. Additionally, it also defines color codes for different terminal text colors and formatting.                                                                                                                                                                                                                                                                                                                                                   |
| [Server.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/Server.hpp)                 | The code defines the Server class, which represents a server in an IRC (Internet Relay Chat) application. The class handles client connections, manages channels, and processes user commands. It includes functions for initializing the server, handling client disconnections, sending messages to clients, and managing server shutdown. The class also defines custom exceptions for handling errors during server execution.                                                                                                                                                                                                                                                                         |
| [Channel.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/Channel.hpp)               | The code provided is a C++ header file called Channel.hpp. It defines the class Channel, which represents a channel in an Internet Relay Chat (IRC) system. The Channel class has several member functions and attributes that allow for the management of clients, operators, invited users, and various channel settings such as password, topic, and mode. Additionally, it provides functions for sending messages, updating client lists, and more. The Channel class is intended to be used in conjunction with other classes and files in the ft_IRC project.                                                                                                                                       |
| [log.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/log.hpp)                       | The code in `log.hpp` defines various functions for logging different events and error messages in an IRC (Internet Relay Chat) application. These functions include logging welcome messages, server information, channel modes, topics, user lists, MOTD (Message of the Day), and various error messages. The functions take parameters such as clients, channels, nicknames, and other relevant information to generate the appropriate log message.                                                                                                                                                                                                                                                   |
| [CommandHandler.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/CommandHandler.hpp) | The code provided is a header file called CommandHandler.hpp. It contains a class called CommandHandler that handles various commands used in an Internet Relay Chat (IRC) system. The class has private member functions for different commands such as quit, pass, nick, and user. It also has public member functions for other commands like kick, join, invite, topic, mode, ping, privmsg, and part. The class takes a reference to a string as a parameter in the constructor and has a destructor. It also has a public member function called handleCommand that takes multiple parameters including input, client, channels, and clients, and is responsible for handling the incoming commands. |
| [Client.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/Client.hpp)                 | The code represents the header file Client.hpp which defines the class Client. The class contains various member functions and attributes related to a client in an IRC (Internet Relay Chat) system. It includes functions for getting and setting socket, buffer, username, nickname, and realname values. It also includes functions for sending messages, logging in, broadcasting messages from a client, and warning others when a client is leaving. The class also has attributes such as socketFd, passwordUnlocked, toDisconnect, and userConnected.                                                                                                                                             |

</details>

<details closed><summary>Bot</summary>

| File                                                                   | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           |
| ---                                                                    | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               |
| [IRCBot.cpp](https://github.com/hystb/ft_IRC/blob/main/bot/IRCBot.cpp) | The code represents an IRC (Internet Relay Chat) bot that connects to an IRC server, joins a channel, and responds to commands. It uses socket programming to establish a connection with the server, sends and receives messages, and executes commands. Features include creating a socket, connecting to the server, sending messages, receiving messages, parsing commands, generating responses using an AI language model (GPT-3), and handling signals for graceful termination.                                                                                                                           |
| [IRCBot.hpp](https://github.com/hystb/ft_IRC/blob/main/bot/IRCBot.hpp) | The code provided is the header file for an IRCBot class. It includes necessary libraries and defines the class with member variables and functions. The IRCBot class represents an Internet Relay Chat (IRC) bot, designed to connect to a server, join a specific channel, and interact with users. It has functions to create a socket, connect to the server, send and receive IRC messages, handle signals, manage connections, and generate responses using a GPT (Generative Pre-trained Transformer) model. The class also includes exception handling and a destructor.                                  |
| [main.cpp](https://github.com/hystb/ft_IRC/blob/main/bot/main.cpp)     | The code in bot/main.cpp is the entry point of the IRCBot application. It checks if the correct number of command line arguments (6 or 7) are provided. If the arguments are correct, it extracts the server address, port, channel name, password, API key, and an optional channel password from the command line arguments. Then, it creates an instance of the IRCBot class with the provided arguments and runs the bot. If any exception occurs during the execution, it catches the exception and prints the error message. If the incorrect number of arguments is provided, it displays a usage message. |
| [Makefile](https://github.com/hystb/ft_IRC/blob/main/bot/Makefile)     | This Makefile is used to compile the IRCBot program. The program consists of several source files located in the bot directory and its subdirectories. The Makefile sets the compiler to c++ and specifies the compilation flags. The program's name is set to rocketBot. The Makefile contains rules to compile the source files into object files and link them together to create the final executable. The all rule compiles the program, clean rule removes the object files, fclean rule removes the executable, and re rule cleans and recompiles the program.                                             |

</details>

---

## 🚀 Getting Started

***Dependencies***

Please ensure you have the following dependencies installed on your system:

`- ℹ️ jq if you want to run the bot`

### 🔧 Installation

1. Clone the ft_IRC repository:
```sh
git clone https://github.com/hystb/ft_IRC
```

2. Change to the project directory:
```sh
cd ft_IRC
```

3. Install the dependencies:
```sh
make
```
or to compile the bot
```
make bonus
```

### 🖧 Running ft_IRC

```sh
./ircserv <port> <password>
```

### 🤖 Running bot

```sh
cd bot
./rocketBot <Server Address> <Port> <Channel> <Password> <ApiKey> <Channel Password(optional)>
```
---

[**Return**](#Top)

---

