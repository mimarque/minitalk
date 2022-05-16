# 42cursus - minitalk

The purpose of this project is to code a small data exchange program using UNIX signals

## Project Information

<sub>This Read me is based on [hanshazairi](https://github.com/hanshazairi/42-minitalk/blob/master/README.md)'s and  [Ysoroko](https://github.com/Ysoroko/minitalk/blob/master/README.md)'s guides</sub>

### About

The purpose of this project is to code a small data exchange program using *UNIX signals*.

### Mandatory

- Produce `server` & `client` executables
- `client` must communicate a string passed as a parameter to `server` *(referenced by its process ID)* which then displays it
- Use `SIGUSR1` & `SIGUSR2` signals **ONLY**

### Bonus

- Add reception acknowledgement system
- Support Unicode characters

### Allowed Functions

- [`malloc`](https://man7.org/linux/man-pages/man3/free.3.html)
- [`free`](https://man7.org/linux/man-pages/man3/free.3.html)
- [`write`](https://man7.org/linux/man-pages/man2/write.2.html)
- [`getpid`](https://man7.org/linux/man-pages/man2/getpid.2.html)
- [`signal`](https://man7.org/linux/man-pages/man2/signal.2.html)
- [`sigemptyset & sigaddset`](https://man7.org/linux/man-pages/man3/sigsetops.3.html)
- [`sigaction`](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [`pause`](https://man7.org/linux/man-pages/man2/pause.2.html)
- [`kill`](https://man7.org/linux/man-pages/man2/kill.2.html)
- [`sleep`](https://man7.org/linux/man-pages/man3/sleep.3.html)
- [`usleep`](https://man7.org/linux/man-pages/man3/usleep.3.html)
- [`exit`](https://man7.org/linux/man-pages/man3/exit.3.html)

### Behaviour:

1) By running the server executable we start up the server and it displays its process id:
![server start](https://imgur.com/JIMl5CY.png)

2) By running the client with the process id from the server we can send strings to the server
![starting client](https://imgur.com/IwbpQUy.png)

3) Server receives bits containing the information, translates them to characters and prints the result as a string:
![server receives message](https://imgur.com/Sj4z7ow.png)

#### Additional behaviour:
1) The client can also send Unicode format characters and recieve acknowledges
![sending emojies](https://imgur.com/kqJ4hem.png)

2) The server interprets and displays them correctly
![server receiving unicode](https://imgur.com/0Pi1qlM.png)

