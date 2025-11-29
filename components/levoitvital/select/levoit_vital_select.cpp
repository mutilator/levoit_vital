
#include "esphome/core/log.h"
#include "levoit_vital_select.h"
#include "../settings.h"

namespace esphome
{
  namespace levoit_vital
  {

    static const char *const TAG = "levoit_vital.select";

    void LevoitSelect::setup() {}
    void LevoitSelect::dump_config() {}

    void LevoitSelect::control(const std::string &value)
    {
      switch (this->purpose_)
      {
      case AUTOMODE:
      {
        if (value == "Default")
        {
          parent_->sendCommand(setAutoModeDefault);
        }
        else if (value == "Quiet")
        {
          parent_->sendCommand(setAutomodeQuiet);
        }
        else if (value == "Efficient")
        {
          parent_->sendCommand(setAutoModeEfficient);
        }
        break;
      }
      case FANLEVEL:
      {
        if (value == "1")
        {
          parent_->sendCommand(setDeviceFanLvl1);
        }
        else if (value == "2")
        {
          parent_->sendCommand(setDeviceFanLvl2);
        }
        else if (value == "3")
        {
          parent_->sendCommand(setDeviceFanLvl3);
        }
        else if (value == "4")
        {
          parent_->sendCommand(setDeviceFanLvl4);
        }
        else
        { // in case user selects a not working option like "NOT SET" the state is reset
          // not implemented yet
          // auto &settings = Vital200Settings::getInstance();
          // publish_state(settings.fanLevel);
        }

        break;
      }
      case FANMODE:
      {
        if (value == "Manual")
        {
          parent_->sendCommand(setFanModeManual);
        }
        if (value == "Sleep")
        {
          parent_->sendCommand(setFanModeSleep);
        }
        else if (value == "Automatic")
        {
          parent_->sendCommand(setFanModeAuto);
        }
        else if (value == "Pet")
        {
          parent_->sendCommand(setFanModePet);
        }
        break;
      }
      }
      ESP_LOGI(TAG, "Selected option: %s", value.c_str());
    }

  } // namespace levoit_vital
} // namespace esphome
