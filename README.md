## Some Background
Well I made this thing called [Meme Bot](https://www.facebook.com/1memebot/), it's a messenger chat-bot that has the following features:

  - [x] Send and recieve messages through the facebook messenger app
  - [x] Replies with random, current memes upon request
  - [x] Several categories of memes

[Here's a link to the source code for MemeBot!](https://github.com/benwinding/Meme-Bot-Messenger-Client)

## But What Is This?
Well I thought it would be cool to see the statistics of which meme categories were being requested in realtime. So this is a arduino program that polls a webserver and displays the information on an LED screen... in 

\<buzzword> REALTIME \</buzzword>

![asss](http://i.imgur.com/u8YkXQt.gif)

## Project Overview
After a lot of trial and error I realised there would be 3 main parts to the system:

#### Cloud
 - Statistics API, a webserver to store the statistics I need

#### Arduino Devices
 - Wifi Network Module, to poll the server and retreive new information
 - LED Display Module, an arduino board to display the information
 
I tried to use one arduino module, but the network requests were taking to long to allow the display to update. This lead me to decouple the code into 2 modules. The network module would request and process the statistical data, then send it to the LED over a serial connection using the Wire library.

But I did need to alter a library in order to use the LED display I had, so I published my changes here:

[https://github.com/benwinding/LEDMatrix64-Arduino](https://github.com/benwinding/LEDMatrix64-Arduino)

![asss](http://i.imgur.com/yQ1Hfht.jpg)
![asss](http://i.imgur.com/LY8I7mK.jpg)
![asss](http://i.imgur.com/1fhEh9v.jpg)
![asss](http://i.imgur.com/6BAEv6e.jpg)
