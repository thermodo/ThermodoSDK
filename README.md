<p align="center">
  <a href="http://developer.thermodo.com/"><img src="http://thermodo.com/assets/images/thermodo_logo.jpg" alt="Thermodo" title="Thermodo" /></a>
</p>

The ThermodoSDK allows you to integrate [Thermodo](http://thermodo.com) into your iOS or OS X application. ThermodoSDK provides a simple interface for interacting with Thermodo and getting temperature readings into your application.

Thermodo is a tiny electrical thermometer for your mobile device that lets you measure the temperature right where you are. For more information about Thermodo please checkout our [website](http://thermodo.com) or watch the [Kickstarter Video](http://www.kickstarter.com/projects/robocat/thermodo-the-tiny-thermometer-for-mobile-devices).

## Installation with CocoaPods

[CocoaPods](http://cocoapods.org) is a dependency manager for Objective-C, which automates and simplifies the process of using 3rd-part libraries like ThermodoSDK in your application. See their website for a [Getting started guide](http://docs.cocoapods.org/guides/installing_cocoapods.html).

In your projects Podfile add ThermodoSDK and run ``pod install``

**Podfile**
```ruby
platform :ios, '7.0'
pod "ThermodoSDK", "~> 1.0"
```

## Manual installation

We highly encourage you to use CocoaPods for installation so you're always up to date with the latest version. If you don't want to use CocoaPods you can of course still install ThermodoSDK manually.

1. Download the lastest [zipped version](https://github.com/robocat/ThermodoSDK/archive/master.zip)
2. Drag all the ``.h`` and ``.a`` files into your Xcode project.
3. That's it!

## Usage

To get started you need to register a delegate so your application can ``start`` and``stop`` the measurements and get temperature readings from the device. Your delegate must implement the ``THMThermodoDelegate`` protocol. 

```objectivec
@protocol THMThermodoDelegate <NSObject>

@optional

- (BOOL)thermodoShouldUseAudioInputAsThermodoDevice:(THMThermodo *)thermodo;

/*!
 * This method will be called when -start is called on TMThermodo while the device is plugged in
 * or once the device has been plugged in after -start has been called.
 */
- (void)thermodoDidStartMeasuring:(THMThermodo *)thermodo;

/*!
 * This method will be called when -stop is called on TMThermodo or when the device is unplugged.
 * @param thermodo The shared THMThermodo instance
 */
- (void)thermodoDidStopMeasuring:(THMThermodo *)thermodo;

/*!
 * This method will be called every time the Thermodo device returns a new temperature reading.
 * @param thermodo The shared THMThermodo instance
 * @param temperature The measured temperature in celcius
 */
- (void)thermodo:(THMThermodo *)thermodo didGetTemperature:(CGFloat)temperature;

@end
```

To start measuring simply register your delegate and ask the ``THMThermodo`` instance to start measuring:

```objectivec
@interface MyViewController () <THMThermodoDelegate>
@end

@implementation MyViewController

- (void)viewDidLoad {
	[super viewDidLoad];

	[[THMThermodo sharedThermodo] setDelegate:self];
	[[THMThermodo sharedThermodo] start];
}

- (void)thermodo:(THMThermodo *)thermodo didGetTemperature:(CGFloat)temperature {
	// Display the temperature reading
}

@end
```

In this example we simply use our View Controller as the delegate for Thermodo. While this works perfectly fine you probably want to have your delegate decoupled from your View Controllers if you need to access the Thermodo readings from several places since there can only be one delegate for the Thermodo device.

## FAQ

### Can I try/use ThermodoSDK without a Thermodo Device?

No. In order to get device readings and any kind of reponse from SDK you must have Thermodo device to test with. You can order one from [our website](http://thermodo.com).

### The readings from the device are too hot

We have used a lot of time on making sure that Thermodo delivers accurate and consistent temperature readings. Unfortunately this precision also means that the Thermodo
sensor is easily affected by heat from your device (your iPhone / iPad / Macbook) or just the palm of your hand. To get the most accurate readings we recommend using an extension cord. For more 
information [this video update from the Kickstarter project](http://vimeo.com/76458958).

## Contributing

We love our community and our fellow developers. If you find some other way to improve ThermodoSDK please let us know by [opening issue](https://github.com/robocat/ThermodoSDK/issues/new).

## License

The MIT License (MIT)

Copyright (c) 2013 Robocat

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.