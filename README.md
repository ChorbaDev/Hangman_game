
<p align="center">
  <img src="https://user-images.githubusercontent.com/53189749/149657701-486eb61b-99b7-4bc2-8a5a-f7300d1cc385.png" />
</p>
<p align="center">
  <img src="https://img.shields.io/tokei/lines/github.com/ChorbaDev/prj_HangmanC?style=for-the-badge" />
  
  <img src="https://img.shields.io/github/repo-size/ChorbaDev/prj_HangmanC?style=for-the-badge" />
  <img src="https://img.shields.io/github/directory-file-count/ChorbaDev/prj_HangmanC?style=for-the-badge" />
  <img src="https://user-images.githubusercontent.com/53189749/149659532-1fda23f1-c3cc-4aef-9476-8fb06ab9edef.png" />
</p>

### Description
Hangman game written in C language using treads.
### What is Hangman?
Hangman is a paper and pencil guessing game
for two or more players. Player 1 thinks
of a word, phrase or sentence and the other(s)
tries to guess it by suggesting letters within
a certain number of guesses.
### Who's the players here?
The player 1 represents the <b>Server</b> and the other(s) are the <b>Clients</b>.
### What is this project?
So basically this project is a simulation of the hangman game using networking in c (Client/Server)
With <b>U</b>ser <b>D</b>atagram <b>P</b>rotocol (<b>UDP</b>) with max players of 10.
## Deployment
To launch the server:
```shell
  gcc server/server.c -o exserver -lpthread
  ./exserver
```
To launch the client:
```shell
  gcc client/client.c -o exclient
  ./exclient
```
## The game
First, the client will ask the server for the length of the chosen word, then the server will open the file txt and chose a random word and reply to the request of the client.
<br>
After that, the game begins and the client starts to send suggestions (letters) and the server respond whether it's true or false until the client loses the game or wins.
<br>
The client (Player) can see the dashboard that contains all the scores with a descending sort of the scores
and his score will appear in green.
![dashboard](https://user-images.githubusercontent.com/53189749/149659733-135f1c02-cdba-4339-87b7-4e49f42c4686.png)
