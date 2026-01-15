#include "esphome/core/log.h"
#include "levoit_vital_fan.h"
#include "../settings.h"

namespace esphome
{
  namespace levoit_vital
  {

    static const char *const TAG = "levoit_vital.fan";

    void LevoitFan::setup() 
    {
        // Initialize fan as off with no speed
        this->state = false;
        this->speed = 0;
    }

    void LevoitFan::dump_config() 
    {
        ESP_LOGCONFIG(TAG, "Levoit Vital Fan");
        ESP_LOGCONFIG(TAG, "  Speed levels: 4 (0=OFF, 1-4)");
    }

    fan::FanTraits LevoitFan::get_traits()
    {
        auto traits = fan::FanTraits();
        traits.set_speed(true);
        traits.set_supported_speed_count(4); // 4 speed levels (1, 2, 3, 4)
        return traits;
    }

    void LevoitFan::control(const fan::FanCall &call)
    {
        if (call.get_state().has_value())
        {
            this->state = *call.get_state();
            if (!this->state)
            {
                // Fan turned off - speed 0
                this->speed = 0;
                ESP_LOGI(TAG, "Fan turned OFF (speed 0)");
                parent_->sendCommand(setDeviceOFF);
            }
        }

        if (call.get_speed().has_value())
        {
            int speed_level = *call.get_speed();
            this->speed = speed_level;
            this->state = (speed_level > 0); // Auto turn on if speed > 0

            ESP_LOGI(TAG, "Fan speed set to: %d", speed_level);

            switch (speed_level)
            {
            case 0:
                // Speed 0 = OFF
                ESP_LOGI(TAG, "Fan speed 0 - turning OFF");
                parent_->sendCommand(setDeviceOFF);
                break;
            case 1:
                parent_->sendCommand(setDeviceFanLvl1);
                break;
            case 2:
                parent_->sendCommand(setDeviceFanLvl2);
                break;
            case 3:
                parent_->sendCommand(setDeviceFanLvl3);
                break;
            case 4:
                parent_->sendCommand(setDeviceFanLvl4);
                break;
            default:
                ESP_LOGW(TAG, "Invalid fan speed: %d", speed_level);
                break;
            }
        }

        this->publish_state();
    }

  } // namespace levoit_vital
} // namespace esphome
