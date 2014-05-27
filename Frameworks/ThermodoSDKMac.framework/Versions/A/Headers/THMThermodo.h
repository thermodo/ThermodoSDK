//
//  THMThermodo.h
//  ThermodoSDK
//
//  Copyright (c) 2013 Robocat (http://robocatapps.com)
//  All rights reserved.

#import <Foundation/Foundation.h>
#import "THMError.h"

@class THMThermodo;

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

@interface THMThermodo : NSObject

+ (THMThermodo *)sharedThermodo;

/*!
 * Starts listening for a Thermodo device. When one is inserted, and the -thermodoShouldUseAudioInputAsThermodoDevice: delegate callback returns YES, it will start a test to determine if it's a Thermodo or just a headset.
 * If the device is in fact a Thermodo, it will start the temperature measurement and call -thermodoDidStartMeasuring:. When the Thermodo is unplugged, -thermodoDidStopMeasuring: is called, and we will go back to listening for devices.
 */
- (void)start;

/*!
 * Stop listening for Thermodos. If a Thermodo is currently plugged in and being measured, -thermodoDidStopMeasuring: is called and the measurement is stopped.
 */
- (void)stop;

/*!
 * The delegate of the THMThermodo instance. You mus set this to get temperature callbacks.
 */
@property (weak, nonatomic) id<THMThermodoDelegate> delegate;

/*!
 * The SDK will try to figure out if what is being plugged into the audio port is in fact a Thermodo.
 * Some users may experience issues with this and therefore we suggest to provide a setting
 * to the user that allows them to enable or disable this detection.
 */
@property (assign, nonatomic, getter = isDetectionEnabled) BOOL detectionEnabled;

/*!
 * If detection is enabled, this will be true when something is plugged into the audio port
 * and the SDK is currently detecting whether or no the input is a Thermodo.
 */
@property (assign, nonatomic, readonly, getter = isDetectingThermodo) BOOL detectingThermodo;

/*!
 * Whether or not a Thermodo is currently detected. This is true if something is plugged into the audio port
 * and it is determined to be a Thermodo or something is plugged in and detection is disabled.
 */
@property (assign, nonatomic, readonly, getter = isThermodoDetected) BOOL thermodoDetected;

/*!
 * True when something is plugged into the audio port.
 */
@property (assign, nonatomic, readonly, getter = isInputDetected) BOOL inputDetected;

/*!
 * The current status of the device
 * @return measuring YES if the deivce is currently measuring; otherwise NO
 */
@property (assign, nonatomic, readonly, getter = isMeasuring) BOOL measuring;

@end
