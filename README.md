Considering one of 2 routes (leaning toward former):
- use networking api built in to rack to GET JSON updates from a locally running server
- use sockets and parse the socket msgs into commands

- what is a good way to translate voltage commands like "/bpm -0.1" to values of output values on output ports 1-16 that can be used for multuple patches that will have different params to control 