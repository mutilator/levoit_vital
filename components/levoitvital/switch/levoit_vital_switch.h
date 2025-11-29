#pragma once
#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "../levoit_vital.h"
#include "../enums.h"

namespace esphome
{
    namespace levoit_vital
    {
        class LevoitSwitch : public switch_::Switch, public Component
        {
        public:
            LevoitSwitch(LevoitVital *parent, LevoitSwitchPurpose purpose) : parent_(parent), purpose_(purpose) {}
            void setup() override;
            void dump_config() override;
            void write_state(bool state) override;

        protected:
            LevoitVital *parent_;
            LevoitSwitchPurpose purpose_;
        };

    } // namespace levoit
} // namespace esphome
