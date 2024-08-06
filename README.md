# BD-cnCt



## TODOs, Ideas

- design how the panel looks
- each output needs to have its own attenuverter. the gain needs to go from -2 to 2 and he offset from -10 to 10
- add offset and gain controls to every output to standardize the way that users send commands no matter which output they are sending a value to
- add an option to set an output as unipolar? or should the user commands only ever be values from 0.0 to 10.0?
- when there is an improper input the twitch server could send back a message to the twitch chat showing proper usage guide for this patch. in fact it would be kinda tricky but there may be reasons to have the vcv module POST a usage guide specific to it's state back to the twitch server which then forwards it back to real twitch chat
- take advantage of the User Join message and maybe even the User List functionality. User list could be used to give users different access to certain params or chane the way their params are interpreted or something...