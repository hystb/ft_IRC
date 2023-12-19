<div align="center">
<h1 align="center">
<img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" width="100" />
<br>FT_IRC</h1>
<h3>◦ ft_IRC: Connecting Codes, Crafting Future.</h3>
<h3>◦ Developed with the software and tools below.</h3>

<p align="center">

</p>
<img src="https://img.shields.io/github/license/hystb/ft_IRC?style=flat-square&color=5D6D7E" alt="GitHub license" />
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
    - [🧪 Tests](#-tests)
- [🛣 Roadmap](#-roadmap)
- [🤝 Contributing](#-contributing)
- [📄 License](#-license)
- [👏 Acknowledgments](#-acknowledgments)

---


## 📍 Overview

The ft_IRC repository houses a comprehensive IRC server and client system designed using C++. The system includes network and messages handlers, commands processing, and an IRC bot for autonomous actions. It comes with robust functionalities such as acknowledging and executing a variety of IRC commands, server-client interactions, error messaging, logging, and handles invitations. The highlight is the use of a CommandHandler which adds versatility to the system by allowing extension of commands. Network communication, error handling, logging, and compatibility with standard IRC protocols make it a valuable tool for creating tailored chat servers.

---

## 📦 Features

HTTPStatus Exception: 429

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

| File                                                           | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             |
| ---                                                            | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| [Makefile](https://github.com/hystb/ft_IRC/blob/main/Makefile) | The provided code is a structure for an IRC (Internet Relay Chat) server with a bot feature, written in C++. It includes commands, network and messages management, and configuration and logging functionalities. The Makefile eases compilation by transforming C++ files into object files, linking them, producing an executable, and maintaining a clean build environment. The bonus directive compiles the bot feature separately. Commands like clean, fclean and re are for cleaning the build, including the bot's build. |

</details>

<details closed><summary>Src</summary>

| File                                                               | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| ---                                                                | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| [main.cpp](https://github.com/hystb/ft_IRC/blob/main/src/main.cpp) | This code defines the entry point of an IRC (Internet Relay Chat) server. It validates user-provided port and password, outputs error or warning messages based on validation, and then starts the server. If the correct arguments are not provided, error messages are displayed. If the port is potentially restricted, a warning is issued. The `CommandHandler` and `Server` objects are also created and initialized with these validated inputs. |

</details>

<details closed><summary>Commandhandler</summary>

| File                                                                                                  | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| ---                                                                                                   | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     |
| [log.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/log.cpp)                       | The code includes a set of functions providing IRC (Internet Relay Chat) message formatting for client-server communication. Each function formats a specific type of server response or error message per IRC protocol. Responses include welcome messages, server info, channel topics, and operator status. Errors cover cases of invalid input like non-existing channels, occupied nicknames, or insufficient command parameters. Also, logging functions for actions such as joins, invites, kicks, and mode changes are present. |
| [CommandHandler.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/CommandHandler.cpp) | The provided code is part of an IRC (Internet Relay Chat) client. It leverages a CommandHandler class to handle commands received from a user. These include common IRC operations such as PASS, NICK, USER, and others. It includes a main function that takes in a string input, generates a Command object, logs the action, and calls the appropriate command function. Also, certain commands can only be executed if the client has unlocked the password or connected to the server.                                             |
| [Command.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/Command.cpp)               | The provided code defines the class `Command` within an Internet Relay Chat (IRC) system. The `Command` class has a constructor for initializing its properties including input, associated client, channels, and clients. Additionally, it entails getter methods for retrieving these properties. The `parse` function splits the input into components: command, content, and parameters. The parsed data helps in determining the command type and its requisite parameters.                                                        |

</details>

<details closed><summary>Commands</summary>

| File                                                                                             | Summary                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  |
| ---                                                                                              | ---                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      |
| [pass.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/pass.cpp)       | The code contains the CommandHandler class, specifically the pass method for handling pass commands in an IRC bot application. It processes the passed command parameters, disallowing an already authenticated client or incorrect number of arguments. If the provided password is incorrect, it refuses the connection. Proper error messages are logged in each of these cases, ensuring proper user interaction and debugging. The client's status is updated accordingly based on the authentication result.       |
| [ping.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/ping.cpp)       | This C++ code facilitates an IRC bot's response to a ping command. Within the CommandHandler class, the ping function receives the command, checks if it has exactly one parameter, and replies, repeating the received parameter. If the parameter count is incorrect, the bot sends an error message.                                                                                                                                                                                                                  |
| [invite.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/invite.cpp)   | The invite.cpp code outlines the functionality of inviting a client to a channel in the IRC (Internet Relay Chat) bot program. It validates arguments, identifies client names and channel names, confirms valid naming, checks for invite restrictions, membership status, operator status, and existing invitations, and sends error responses if necessary. If checks pass, it logs the invitation and adds the invited client to a channel's list of invites.                                                        |
| [quit.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/quit.cpp)       | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| [topic.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/topic.cpp)     | The code represents an Internet Relay Chat (IRC) bot function that handles topic commands. The `topic` function extracts parameters from a command object, verifies if sufficient parameters exist, and checks if the channel exists. If successful, it confirms if the client is a member and an operator in the channel. Depending on whether the topic content is specified or not, it either sets a new topic for the channel or retrieves the current topic. Error messages are returned if conditions are not met. |
| [mode.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/mode.cpp)       | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| [privmsg.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/privmsg.cpp) | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| [user.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/user.cpp)       | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| [join.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/join.cpp)       | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| [part.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/part.cpp)       | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| [kick.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/kick.cpp)       | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| [nick.cpp](https://github.com/hystb/ft_IRC/blob/main/src/commandhandler/commands/nick.cpp)       | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |

</details>

<details closed><summary>Messages</summary>

| File                                                                              | Summary                   |
| ---                                                                               | ---                       |
| [Client.cpp](https://github.com/hystb/ft_IRC/blob/main/src/messages/Client.cpp)   | HTTPStatus Exception: 429 |
| [Channel.cpp](https://github.com/hystb/ft_IRC/blob/main/src/messages/Channel.cpp) | HTTPStatus Exception: 429 |

</details>

<details closed><summary>Network</summary>

| File                                                                           | Summary                   |
| ---                                                                            | ---                       |
| [Server.cpp](https://github.com/hystb/ft_IRC/blob/main/src/network/Server.cpp) | HTTPStatus Exception: 429 |

</details>

<details closed><summary>Headers</summary>

| File                                                                                       | Summary                                                                                                                                                                                                                                                                                                                                                                                                                             |
| ---                                                                                        | ---                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| [Command.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/Command.hpp)               | The Command.hpp code provides the definition for the Command class in an Internet Relay Chat (IRC) Bot. The Command class stores and parses command messages (input), splitting it into the specific command and parameters. It also keeps references to the client sending the command and the servers and clients involved. It includes getter functions for each data member and throws an exception for invalid command syntax. |
| [config.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/config.hpp)                 | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                           |
| [Server.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/Server.hpp)                 | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                           |
| [Channel.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/Channel.hpp)               | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                           |
| [log.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/log.hpp)                       | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                           |
| [CommandHandler.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/CommandHandler.hpp) | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                           |
| [Client.hpp](https://github.com/hystb/ft_IRC/blob/main/headers/Client.hpp)                 | HTTPStatus Exception: 429                                                                                                                                                                                                                                                                                                                                                                                                           |

</details>

<details closed><summary>Bot</summary>

| File                                                                   | Summary                   |
| ---                                                                    | ---                       |
| [IRCBot.cpp](https://github.com/hystb/ft_IRC/blob/main/bot/IRCBot.cpp) | HTTPStatus Exception: 429 |
| [IRCBot.hpp](https://github.com/hystb/ft_IRC/blob/main/bot/IRCBot.hpp) | HTTPStatus Exception: 429 |
| [main.cpp](https://github.com/hystb/ft_IRC/blob/main/bot/main.cpp)     | HTTPStatus Exception: 429 |
| [Makefile](https://github.com/hystb/ft_IRC/blob/main/bot/Makefile)     | HTTPStatus Exception: 429 |

</details>

---

## 🚀 Getting Started

***Dependencies***

Please ensure you have the following dependencies installed on your system:

`- ℹ️ Dependency 1`

`- ℹ️ Dependency 2`

`- ℹ️ ...`

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
g++ -o myapp main.cpp
```

### 🤖 Running ft_IRC

```sh
./myapp
```

### 🧪 Tests
```sh
Insert test command.
```

---


## 🛣 Project Roadmap

> - [X] `ℹ️  Task 1: Implement X`
> - [ ] `ℹ️  Task 2: Implement Y`
> - [ ] `ℹ️ ...`


---

## 🤝 Contributing

Contributions are welcome! Here are several ways you can contribute:

- **[Submit Pull Requests](https://github.com/hystb/ft_IRC/blob/main/CONTRIBUTING.md)**: Review open PRs, and submit your own PRs.
- **[Join the Discussions](https://github.com/hystb/ft_IRC/discussions)**: Share your insights, provide feedback, or ask questions.
- **[Report Issues](https://github.com/hystb/ft_IRC/issues)**: Submit bugs found or log feature requests for HYSTB.

#### *Contributing Guidelines*

<details closed>
<summary>Click to expand</summary>

1. **Fork the Repository**: Start by forking the project repository to your GitHub account.
2. **Clone Locally**: Clone the forked repository to your local machine using a Git client.
   ```sh
   git clone <your-forked-repo-url>
   ```
3. **Create a New Branch**: Always work on a new branch, giving it a descriptive name.
   ```sh
   git checkout -b new-feature-x
   ```
4. **Make Your Changes**: Develop and test your changes locally.
5. **Commit Your Changes**: Commit with a clear and concise message describing your updates.
   ```sh
   git commit -m 'Implemented new feature x.'
   ```
6. **Push to GitHub**: Push the changes to your forked repository.
   ```sh
   git push origin new-feature-x
   ```
7. **Submit a Pull Request**: Create a PR against the original project repository. Clearly describe the changes and their motivations.

Once your PR is reviewed and approved, it will be merged into the main branch.

</details>

---

## 📄 License


This project is protected under the [SELECT-A-LICENSE](https://choosealicense.com/licenses) License. For more details, refer to the [LICENSE](https://choosealicense.com/licenses/) file.

---

## 👏 Acknowledgments

- List any resources, contributors, inspiration, etc. here.

[**Return**](#Top)

---

