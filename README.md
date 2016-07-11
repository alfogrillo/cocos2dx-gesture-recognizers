Cocos2d-x Gesture Recognizers
=============================

This project is an extension of Cocos2d-x that provide touch Gesture Recognizers.

The classes recognize the following gestures:

- Swipe (one finger, 4 directions)
- Long press (one or multiple fingers)
- Pinch with rotation (two fingers)
- Pan (one or multiple fingers)
- Tap (one or multiple taps with one or multiple fingers)

My work was inspired by Apple documentation about the Gesture Recognizers:

https://developer.apple.com/library/ios/documentation/EventHandling/Conceptual/EventHandlingiPhoneOS/GestureRecognizer_basics/GestureRecognizer_basics.html

The code was tested on
- Android 5.1.1 physical device
- iOS 8.4 physical devices (iPhone and iPad)

Tested on: Cocos2d-x 3.9, Cocos2d-x 3.10, Cocos2d-x 3.11

Demo video (with a little bit different test scene):

https://www.youtube.com/watch?v=Gnhj_x4aOwY

How to build the sample projects
----------

**iOS**

- Create a new cocos2d-x project:
```
	cocos new -l cpp TEST
```
- Copy the 'cocos2d' folder from 'TEST' to the repository root folder
- Open the Xcode project inside the 'proj.ios_mac' folder
- Build

**Android**

- Create a new cocos2d-x project:
```
	cocos new -l cpp TEST
```
- Copy the 'cocos2d' folder from 'TEST' to the repository root folder
- With terminal go inside the repository root folder
- Run:
```
	cocos run -s . -p android --android-studio
```


How to integrate gestures code inside a new project
----------

The repository contains two folders inside Classes:
- Gestures
- Test

The actual gesture recognition require ONLY the "Gestures" folder.
The "Test" folder contains various example scenes.
To try the code you can do the following steps:

**iOS**

- Create a new cocos2d-x project:
```
	cocos new -l cpp <project name>
```
- Delete Classes e Resources classes of the sample project and add those of this repository
- Update your Xcode project with Classes and Resources folders
- Enable multi touch in file `ios/AppController.mm`. The line you must modify should look like this:
```
	[eaglView setMultipleTouchEnabled:YES]
```

   see http://www.cocos2d-x.org/wiki/How_to_Enable_Multi-Touch for further information


**Android**

- Create a new cocos2d-x project:
```
	cocos new -l cpp <project name>
```
- Delete Classes e Resources classes of the sample project and add those of this repository
- Add the source file of this repo in `proj.andorid/jni/Android.mk`

Contact: drakon.cocos@gmail.com

License: MIT License (https://opensource.org/licenses/MIT)
