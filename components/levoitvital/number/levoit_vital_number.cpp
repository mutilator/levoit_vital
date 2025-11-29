
#include "esphome/core/log.h"
#include "levoit_vital_number.h"
#include "../settings.h"
namespace esphome
{
  namespace levoit_vital
  {

    static const char *const TAG = "levoit_vital.number";

    void LevoitNumber::setup() {}
    void LevoitNumber::control(float value)
    {
      switch (this->purpose_)
      {
      case EFFICIENT_NUM:

        int16_t tmpValue = static_cast<int16_t>(value);
        if (tmpValue < 100)
        {
          tmpValue = 100;
        }
        if (tmpValue > 1800)
        {
          tmpValue = 1800;
        }

        auto &settings = Vital200Settings::getInstance();
        settings.efficientValue = tmpValue;
        this->parent_->sendCommand(setAutoModeEfficient);
        break;
      }
    }

    void LevoitNumber::dump_config() {}
  } // namespace levoit_vital
} // namespace esphome
