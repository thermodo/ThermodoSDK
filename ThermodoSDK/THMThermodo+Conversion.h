//
//  THMThermodo+Conversion.h
//  ThermodoSDK
//
//  Copyright (c) 2013 Robocat (http://robocatapps.com)
//  All rights reserved.

// Enumeration of available temperature scales
typedef NS_ENUM(NSInteger, THMThermodoTemperature) {
    THMThermodoCelsius = 0,
    THMThermodoFahrenheit,
    THMThermodoKelvin,
    THMThermodoRankine,
};

@interface THMThermodo (Conversion)

/*!
 * Convert the base temperature to another scale.
 * @param temperature The base temperature returned by Thermodo
 * @param unit Target unit from THMThermodoTemperature enumeration
 * @return Converted temperature
 */
- (CGFloat)convertTemperature:(CGFloat)temperature toUnit:(THMThermodoTemperature)unit;

@end
