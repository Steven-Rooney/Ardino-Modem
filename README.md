# Ardino-Modem
transmit bianry in forms of frequency in binary form to another Arduino and have it recieved and translated

Transmitter:
The transmiter send a series of tones on a certain frequerncy in the form of bits, using RS32 serial. You can send any length of message

Reciever:
The reciever takes input via a microphone set-up on a bread board and proccess it through a Fast Fourier Transform that has been alter significantly for the limited amount of storage available on the arduino.

It then procceses either a higher freq as a 1 or a lower freq as a 0

it then reconstructs the bits into characters and then reads out your message

I have it set up right now so that it can also control the degree of a servo motor that was also sonnected to the bread board. The servo command always starts with the char 's' and then followed by a 3 digit number for the degree position for the servo.
