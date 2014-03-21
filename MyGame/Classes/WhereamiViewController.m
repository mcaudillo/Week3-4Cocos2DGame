//
//  WhereamiViewController.m
//  MyGame
//
//  Created by Mario A Caudillo Melgoza on 3/21/14.
//
//

#import "WhereamiViewController.h"

@interface WhereamiViewController ()

@end

@implementation WhereamiViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        //create objects
        locationManager=[[CLLocationManager alloc]init];
        [locationManager setDelegate:self];
        [locationManager setDesiredAccuracy:kCLLocationAccuracyBest];
        [locationManager startUpdatingLocation];
    }
    float latitude=locationManager.location.coordinate.latitude;
    float longitude=locationManager.location.coordinate.longitude;
    
    return self;
}



- (void)locationManager:(CLLocationManager *)manager
            didUpdateToLocation:(CLLocation *)newLocation
            fromLocation:(CLLocation *)oldLocation
{
    NSLog(@"%@",newLocation);
}
- (void)locationManager:(CLLocationManager *)manager
    didFailWithError:(NSError *)error
{
    NSLog(@"Could not find location: %@",error);
}
-(void)dealloc
{
    [locationManager setDelegate:nil];
}



@end
