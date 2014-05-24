<p align="center">
  <a href="http://developer.thermodo.com/"><img src="https://raw.githubusercontent.com/thermodo/ThermodoSDK-iOS/master/thermodo-logo.png" alt="Thermodo" title="Thermodo" /></a>
</p>

The ThermodoSDK allows you to integrate [Thermodo](http://thermodo.com) into your iOS and OS X application. ThermodoSDK provides a simple interface for interacting with Thermodo and getting temperature readings into your application.

Thermodo is a tiny electrical thermometer for your mobile device that lets you measure the temperature right where you are. For more information about Thermodo please checkout our [website](http://thermodo.com) or watch the [Kickstarter Video](http://www.kickstarter.com/projects/robocat/thermodo-the-tiny-thermometer-for-mobile-devices).

## Installation with CocoaPods

[CocoaPods](http://cocoapods.org) is a dependency manager for Objective-C, which automates and simplifies the process of using 3rd-part libraries like ThermodoSDK in your application. See their website for a [Getting started guide](http://docs.cocoapods.org/guides/installing_cocoapods.html).

In your projects Podfile add ThermodoSDK and run ``pod install``

**Podfile**
```ruby
platform :ios, '7.0'
pod "ThermodoSDK", "~> 1.0"
```

For OS X your podfile should look like the following.

```ruby
platform :osx, '10.9'
pod "ThermodoSDK", "~> 1.0"
```

## Manual installation

We highly encourage you to use CocoaPods for installation so you're always up to date with the latest version. If you don't want to use CocoaPods you can of course still install ThermodoSDK manually.

1. Download the lastest [version](https://github.com/thermodo/ThermodoSDK-iOS)
2. Drag all the ``.h`` and the appropriate framework (``ThermodoSDK.framework`` for iOS and ``ThermodoSDKMac.framework`` for OS X) files into your Xcode project.
3. Make sure that the location where you put the framework is in your "Framework Search Paths" (Under your targets build settings).
4. If you are targeting OS X you should add a ``Copy Files`` build phase with the destination set to ``Frameworks`` and no subpath then add the framework to this build phase. If you are targeting iOS, you can skip this step.
5. That's it!

## Usage

To get started you need to register a delegate so your application can ``start`` and``stop`` the measurements and get temperature readings from the device. Your delegate must implement the ``THMThermodoDelegate`` protocol.

```objectivec
@protocol THMThermodoDelegate <NSObject>

@optional

/*!
 * If this method is implemented, it will get called after -start has been called and
 * whenever something is plugged into or out of the headphone jack.
 * @param thermodo The shared THMThermodo instance
 */
- (BOOL)thermodoShouldUseAudioInputAsThermodoDevice:(THMThermodo *)thermodo;

/**
 * This method is called when an input was detected.
 * @param thermodo The shared THMThermodo instance
 */
- (void)thermodoInputPluggedIn:(THMThermodo *)thermodo;

/**
 * This method is called when an input was unplugged.
 * @param thermodo The shared THMThermodo instance
 */
- (void)thermodoInputWasUnplugged:(THMThermodo *)thermodo;

/**
 * This method is called when the input was rejected as not being a Thermodo.
 * @param thermodo The shared THMThermodo instance
 */
- (void)thermodoDidRejectInput:(THMThermodo *)thermodo NS_AVAILABLE_IOS(6_0);

/*!
 * This method will be called when -start is called on TMThermodo while the device is plugged in
 * or once the device has been plugged in after -start has been called.
 * @param thermodo The shared THMThermodo instance
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
- (void)thermodo:(THMThermodo *)thermodo didGetTemperature:(float)temperature;

/*!
 * This method will be called when a failure occurs.
 * @param thermodo The shared THMThermodo instance
 * @param error The error describing why the failure occurred.
 */
- (void)thermodo:(THMThermodo *)thermodo didFailWithError:(NSError *)error NS_AVAILABLE_IOS(6_0);

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

## Detection

You can enable detection by setting ``detectionEnabled`` to true. Please note that detection is not currently supported in the OS X framework.

Due to the way detection works there are scenarios where a Thermodo may not be detected. This may occur if the user uses certain extension cables. Therefore we suggest that if you enable detection you should also give the usre the option to disable the detection.
While the detection does not cover all scenarios we strongly suggest that you enable it in your app. Otherwise your users may be confronted with a high pitch noise if they open your app with earpods plugged in.

When detection is enabled you probably want to implement the following three delegate methods in addition to ``thermodoDidStartMeasuring:``, ``thermodoDidStopMeasuring:`` and ``thermodo:didGetTemperature:``.

```objectivec
/**
 * This method is called when an input was detected.
 * @param thermodo The shared THMThermodo instance
 */
- (void)thermodoInputPluggedIn:(THMThermodo *)thermodo;

/**
 * This method is called when an input was unplugged.
 * @param thermodo The shared THMThermodo instance
 */
- (void)thermodoInputWasUnplugged:(THMThermodo *)thermodo;

/**
 * This method is called when the input was rejected as not being a Thermodo.
 * @param thermodo The shared THMThermodo instance
 */
- (void)thermodoDidRejectInput:(THMThermodo *)thermodo NS_AVAILABLE_IOS(6_0);

@end
```

``thermodoInplutPluggedIn:`` will inform you that some hardware was plugged into the audio port. At this point it is uncertain if the input is a Thermodo or earpods.
If the input is found not to be a Thermodo, the ``thermodoDidRejectInput:`` method will be called.
However, if a measurement starts and ``thermodoDidStartMeasuring:`` is called, the input is a Thermodo.
The ``thermodoInputWasUnplugged:`` method will be called when the hardware in the audio port is unplugged regardless of it being a Thermodo or not.

## OS X Beta

Please note that the OS X SDK is currently in beta. We have found that the SDK may not work properly on some Macs and we are constantly adding support for more machines. Please open an issue if you find that the SDK does not work properly on a certain hardware.

## FAQ

### Can I try/use ThermodoSDK without a Thermodo Device?

No. In order to get device readings and any kind of reponse from SDK you must have Thermodo device to test with. You can order one from [our website](http://thermodo.com).

### The readings from the device are too hot

We have used a lot of time on making sure that Thermodo delivers accurate and consistent temperature readings. Unfortunately this precision also means that the Thermodo
sensor is easily affected by heat from your device (your iPhone / iPad / Macbook) or just the palm of your hand. To get the most accurate readings we recommend using an extension cord. For more information [this video update from the Kickstarter project](http://vimeo.com/76458958).

## Contributing

We love our community and our fellow developers. If you find some way to improve ThermodoSDK or find a bug somewhere please let us know by [opening issue](https://github.com/thermodo/ThermodoSDK-iOS/issues/new).
