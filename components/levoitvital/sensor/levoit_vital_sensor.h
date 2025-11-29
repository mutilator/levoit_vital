#pragma once
#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "../levoit_vital.h"
#include "../enums.h"

namespace esphome
{
    namespace levoit_vital
    {
        class LevoitSensor : public sensor::Sensor, public Component
        {
        public:
            LevoitSensor(LevoitVital *parent, LevoitSensorPurpose purpose) : parent_(parent), purpose_(purpose) {}
            void setup() override;
            void dump_config() override;

        protected:
            LevoitVital *parent_;
            LevoitSensorPurpose purpose_;
        };

    } // namespace levoit
} // namespace esphome
