//
//  THMThermodo.h
//  ThermodoSDK
//
//  Copyright (c) 2013 Robocat (http://robocatapps.com)
//  All rights reserved.

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@class THMThermodo;

@protocol THMThermodoDelegate <NSObject>

@optional

/*!
 * If this method is implemented, it will get called after -start has been called and
 * whenever something is plugged into or out of the headphone jack.
 * @param thermodo The shared THMThermodo instance
 */
- (BOOL)thermodoShouldUseAudioInputAsThermodoDevice:(THMThermodo *)thermodo;

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
- (void)thermodo:(THMThermodo *)thermodo didGetTemperature:(CGFloat)temperature;

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
 * The current status of the device
 * @return measuring YES if the deivce is currently measuring; otherwise NO
 */
@property (assign, nonatomic, readonly, getter = isMeasuring) BOOL measuring;

@end
