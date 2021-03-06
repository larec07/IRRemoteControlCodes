#include "RGBStrip.h"
#include "NumericHelper.hpp"

  RGBStrip::RGBStrip (short redPinValue,
                      short greenPinValue,
                      short bluePinValue)
  :
    redPin(redPinValue),
    greenPin(greenPinValue),
    bluePin(bluePinValue)
  {
    isOn = false;

    redValue = -1;
    greenValue = -1;
    blueValue = -1;

    changeInterval = MaxGlow/5;
  }

  RGBStrip::~RGBStrip () {}

  void RGBStrip::On ()
  {
    // if (isOn)
    // {
    //   return;
    // }
    //
    // isOn = true;

    SetWhiteColor(MaxGlow);
  }

  void RGBStrip::Off ()
  {
    // if (!isOn)
    // {
    //   return;
    // }
    //
    // isOn = false;

    SetWhiteColor(0);
  }

  bool RGBStrip::IsOn ()
  {
    return isOn;
  }

  void RGBStrip::SetRGBValues (int red, int green, int blue)
  {
    int constrainedRed = Constrain(red, 0, MaxGlow);
    int constrainedGreen = Constrain(green, 0, MaxGlow);
    int constrainedBlue = Constrain(blue, 0, MaxGlow);

    if (constrainedRed == redValue &&
        constrainedGreen == greenValue &&
        constrainedBlue  == blueValue)
        {
          return;
        }

    redValue = constrainedRed;
    greenValue = constrainedGreen;
    blueValue = constrainedBlue;

    OnRGBValuesChanged();
  }

// #pragma mark - Increment/Decrement each component separately
/// Red
  void RGBStrip::IncreaseRed ()
  {
    ProcessComponent(redValue, redValue + changeInterval);
  }

  void RGBStrip::DecreaseRed ()
  {
    ProcessComponent(redValue, redValue - changeInterval);
  }
/// Green
  void RGBStrip::IncreaseGreen ()
  {
    ProcessComponent(greenValue, greenValue + changeInterval);
  }

  void RGBStrip::DecreaseGreen ()
  {
    ProcessComponent(greenValue, greenValue - changeInterval);
  }
/// Blue
  void RGBStrip::IncreaseBlue ()
  {
    ProcessComponent(blueValue, blueValue + changeInterval);
  }

  void RGBStrip::DecreaseBlue ()
  {
    ProcessComponent(blueValue, blueValue - changeInterval);
  }

// #pragma mark - Change value of any component persistent for other
  void ChangeRedComponentTo (uint8_t value)
  {
    SetRGBValues(value, greenValue, blueValue);
  }
    
  void ChangeGreenComponentTo (uint8_t value)
  {
    SetRGBValues(redValue, value, blueValue);
  }
    
  void ChangeBlueComponentTo (uint8_t value)
  {
    SetRGBValues(redValue, greenValue, value);
  }

// #pragma mark - Set Constant Colors
  void RGBStrip::SetWhiteColor (int brightness)
  {
      SetRGBValues(brightness, brightness, brightness);
  }
  
  void RGBStrip::SetYellowColor (int brightness)
  {
    SetRGBValues(brightness, brightness, 0);
  }

  void RGBStrip::SetRedColor (int brightness)
  {
    SetRGBValues(brightness, 0, 0);
  }

  void RGBStrip::SetGreenColor (int brightness)
  {
    SetRGBValues(0, brightness, 0);
  }

  void RGBStrip::SetBlueColor (int brightness)
  {
    SetRGBValues(0, 0, brightness);
  }

  void RGBStrip::ProcessComponent (int &currentValue, int newValue)
  {
    int considerValue = Constrain(newValue, 0, MaxGlow);

    if (considerValue != currentValue)
    {
      currentValue = considerValue;
      OnRGBValuesChanged();
    }
  }

  void RGBStrip::OnRGBValuesChanged ()
  {
    UpdateStrip(redValue, greenValue, blueValue);
  }
