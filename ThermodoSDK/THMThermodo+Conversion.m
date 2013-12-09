//
//  THMThermodo+Conversion.m
//  ThermodoSDK
//
//  Copyright (c) 2013 Robocat (http://robocatapps.com)
//  All rights reserved.

#import "THMThermodo+Conversion.h"

@implementation THMThermodo (Conversion)

- (CGFloat)converTemperature:(CGFloat)temperature toUnit:(THMThermodoTemperature)unit {
    CGFloat convertedTemperature;
    
    switch (unit) {
        case THMThermodoFahrenheit:
            convertedTemperature = (temperature * (9.0f / 5.0f)) + 32.0f;
            break;
        case THMThermodoKelvin:
            convertedTemperature = temperature + 273.15f;
            break;
        case THMThermodoRankine:
            convertedTemperature = (temperature + 273.15f) * (9.0f / 5.0f);
            break;
        default:
            // All unknown units + celsius
            convertedTemperature = temperature;
            break;
    }
    
    return convertedTemperature;
}

@end
