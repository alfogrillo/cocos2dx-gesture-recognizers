Cocos2d-x Gesture Recognizers
=============================

<div style="text-align:center"><img src="http://www.cocos2d-x.org/attachments/801/cocos2dx_portrait.png" width=100></div>

This project is an extension of Cocos2d-x that provide touch Gesture Recognizers.

The classes recognize the following gestures :octocat:

- **Swipe** (one finger, 4 directions)
- **Long press** (one or multiple fingers)
- **Pinch** with rotation (two fingers)
- **Pan** (one or multiple fingers)
- **Tap** (one or multiple taps with one or multiple fingers)

My work was inspired by Apple documentation about the Gesture Recognizers:

[Apple Gesture Recognizers](https://developer.apple.com/library/ios/documentation/EventHandling/Conceptual/EventHandlingiPhoneOS/GestureRecognizer_basics/GestureRecognizer_basics.html) for iOS

The code was tested on
- Android 5.1.1 physical device
- iOS 10.1 physical devices (iPhone and iPad)

Latest version tested with: **Cocos2d-x 3.13** :+1:

Here Gestures in action on [YouTube](https://www.youtube.com/watch?v=Gnhj_x4aOwY)

How to build the sample project
----------

**iOS**

- Create a new cocos2d-x project:
```
	cocos new -l cpp TEST
```
- Copy the `cocos2d` folder from `TEST` to the repository root folder
- Open the Xcode project inside the `proj.ios_mac` folder
- Build

**Android**

- Create a new cocos2d-x project:
```
	cocos new -l cpp TEST
```
- Copy the `cocos2d` folder from `TEST` to the repository root folder
- With terminal go inside the repository root folder
- Run:
```
	cocos run -s . -p android --android-studio
```


How to integrate gestures code inside your (or new) project
----------

The repository contains two folders inside `Classes` folder:
- Gestures
- Test

The actual gesture recognition require **only** the `Gestures` folder.
The `Test` folder contains various example scenes.
To try the code you can do the following steps:

**iOS**

- Create a new cocos2d-x project:
```
	cocos new -l cpp <project name>
```
- Delete `Classes` e `Resources` folders from the sample project and add those of this repository
- Update your Xcode project with Classes and Resources folders
- Enable multi touch in file `ios/AppController.mm`. The line you must modify should look like this:
```
	[eaglView setMultipleTouchEnabled:YES]
```

   For further informations see how to enable multi-touch [here](http://www.cocos2d-x.org/wiki/How_to_Enable_Multi-Touch)


**Android**

- Create a new cocos2d-x project:
```
	cocos new -l cpp <project name>
```
- Delete `Classes` and `Resources` folders from the sample project and add those of this repository
- Add the source file of this repo in `proj.andorid/jni/Android.mk`

**Contact** drakon.cocos@gmail.com

**License** [MIT](https://opensource.org/licenses/MIT)
