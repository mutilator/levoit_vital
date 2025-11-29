
#include "esphome/core/log.h"
#include "levoit_vital_switch.h"

namespace esphome
{
  namespace levoit_vital
  {

    static const char *const TAG = "levoit_vital.switch";

    void LevoitSwitch::setup() {}
    void LevoitSwitch::dump_config() {}
    void LevoitSwitch::write_state(bool state)
    {
      switch (this->purpose_)
      {
      case DEVICE_POWER:
      {
        this->parent_->sendCommand((state == true ? setDeviceON : setDeviceOFF));
        break;
      }
      case LIGHT_DETECT:
      {
        this->parent_->sendCommand((state == true ? setLightDetectOn : setLightDetectOff));
        break;
      }
      case DISPLAY_LOCK:
      {
        this->parent_->sendCommand((state == true ? setDisplayLockOn : setDisplayLockOff));
        break;
      }
      case DISPLAY:
      {
        this->parent_->sendCommand((state == true ? setDisplayOn : setDisplayOff));
        break;
      }
      }
    }

  } // namespace levoit_vital
} // namespace esphome
