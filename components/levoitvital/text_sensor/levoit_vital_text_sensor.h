#pragma once
#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "../levoit_vital.h"
#include "../enums.h"

namespace esphome
{
    namespace levoit_vital
    {
        class LevoitTextSensor : public text_sensor::TextSensor, public Component
        {
        public:
            LevoitTextSensor(LevoitVital *parent, LevoitTextSensorPurpose purpose) : parent_(parent), purpose_(purpose) {}
            void setup() override;
            void dump_config() override;

        protected:
            LevoitVital *parent_;
            LevoitTextSensorPurpose purpose_;
        };

    } // namespace levoit
} // namespace esphome
