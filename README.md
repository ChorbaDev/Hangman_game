
![😵HANGMAN_GAME😄 (1)](https://user-images.githubusercontent.com/53189749/149657701-486eb61b-99b7-4bc2-8a5a-f7300d1cc385.png)

![Lines of code](https://img.shields.io/tokei/lines/github.com/ChorbaDev/prj_HangmanC?style=for-the-badge)
![GitHub repo size](https://img.shields.io/github/repo-size/ChorbaDev/prj_HangmanC?style=for-the-badge)
![GitHub repo file count](https://img.shields.io/github/directory-file-count/ChorbaDev/prj_HangmanC?style=for-the-badge)
![lose](../../Personal-Portfolio-v1/img/portfolio/autres/SystemC/3.png)
![win](../../Personal-Portfolio-v1/img/portfolio/autres/SystemC/4.png)
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
![](../../Personal-Portfolio-v1/img/portfolio/autres/SystemC/5.png)
