## **MINITALK**

<p align="center" width="100%">
    <img width="33%" src="https://github.com/Arcane-Jill/images/blob/main/minitalkm.png">
</p>

Minitalk is a rank 2 project at **Hive** Helsinki, which is a school in the 42 network. From the subject : *"The purpose of this project is to code a small data exchange program using UNIX signals.*

I learned a great deal about signals doing this project, including that signals are not meant to be used in the way we were using them. Signas are very temperamental and sometimes, if you forget to handle for negative numbers, an evaluator can turn off the whole computer just by adjusting the PID a little.

### **Description**

#### **mandatory**

We had to create a communication program which included a client and a server. They could only communicate using signals, specifically SIGUSR1 and SIGUSR2.

The user would enter a message (a string) and it would be converted to 1s and 0s via bitwise conversion and transmited to the server in binary. Then the server would convert it back to ASCII and print the original message on the standard output, on the terminal.

#### **bonus**

The binus consisted of 2 parts:
1. the server had to acknowledge that the message was received by sending a signal back to the client.
2. The system had to support unicode characters (emojis).
