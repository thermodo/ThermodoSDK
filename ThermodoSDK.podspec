Pod::Spec.new do |s|
  s.name                = "ThermodoSDK"
  s.version             = "1.0"
  s.summary             = "The SDK for the Thermodo device."
  s.homepage            = "http://developer.thermodo.com"
  s.license             = { :type => 'MIT', :file => 'ThermodoSDK/LICENSE' }
  s.author              = { "Robocat" => "hello@robo.cat" }
  s.source              = { :git => "https://github.com/thermodo/ThermodoSDK-iOS.git", :tag => '1.0' }
  s.platform            = :ios, '7.0'
  s.source_files		= 'ThermodoSDK/*.h'
  s.preserve_paths		= 'ThermodoSDK/*.a'
  s.library				= 'libThermodoSDK'
  s.xcconfig			=  { 'LIBRARY_SEARCH_PATHS' => '"$(PODS_ROOT)/ThermodoSDK/ThermodoSDK"' }
  s.frameworks          = [ 'AVFoundation', 'MediaPlayer', 'UIKit', 'CoreGraphics' ]
  s.requires_arc        = true
  s.public_header_files = [ 'ThermodoSDK/*.h' ]
end
