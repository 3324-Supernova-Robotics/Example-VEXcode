# Feedback Controller 

## Prerequisites 
One motor setup called `lift_motor`, and the `set_lift()` function below. 
```cpp
const int SCALE = 120;
void set_lift(int input) {
  lift_motor.spin(fwd, input*SCALE, voltageUnits::mV);
}
```

## How Feedback Controllers Work
Feedback controllers use sensors to react and adjust.  We want to tell our robot to move some distance, and have it move that distance.  When the robot detects it's not where we want it to be, we want it to react by moving to get there.  

For this example we will be using a P loop, the first part of PID.  

P loops work by running `taret - current`.  The chart below shows how error becomes smaller as the robot gets closer to the target. 

| target  | current | error |
| :---:   |  :----: | :---: |
| 100     | 0       | 100   |
| 100     | 25      | 75    |
| 100     | 50      | 50    |
| 100     | 75      | 25    |
| 100     | 100     | 0     |

Sometimes this won't be aggressive enough, or it will be too aggressive.  We can tune it by adding a scaler value called `kP`.  The motor would be set to `error * kP`.  

## Implementation
This code would move the motor one full rotation.  
```cpp
void feedback(double target) {
  double kP = 0.5;
  while (true) {
    double error = target - lift_motor.position(deg);
    set_lift(error * kP);

    wait(10, msec);
  }
}

void autonomous(void) {
  feedback(360); // Spin the motor 1 full rotation
}
```

## Exit Conditions
But the code above is in a while loop, so this would never exit and you wouldn't be able to do anything else in your autonomous!  We want this loop to run until the motor is there.  So we need some code to detect what "there" means.  We call this exit conditions. 

There's many ways to do this, one of the simpler and more consistent ways is to check if the velocity of the motor is 0 for some amount of time.  

When the velocity of the motor is 0, `x` increases by 10 (this is so x is in ms).  When `x` is greater than or equal to 50, this means the velocity has been 0 for 50ms, and the code `breaks` the while loop.  

```cpp
void feedback(double target) {
  double kP = 0.5;
  int x = 0;
  while (true) {
    double error = target - lift_motor.position(deg);
    set_lift(error * kP);

    if (lift_motor.velocity(pct) == 0) {
      x+=10;
      if (x >= 50) {
        break;
      }
    } 
    else {
      x = 0;
    }

    wait(10, msec);
  }
  set_lift(0);
}

void autonomous(void) {
  feedback(360); // Spin the motor 1 full rotation
  feedback(0); // Spin the motor back 1 full rotation
}
```