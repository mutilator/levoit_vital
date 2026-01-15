#pragma once
#include "esphome/core/component.h"
#include "esphome/components/fan/fan.h"
#include "../levoit_vital.h"

namespace esphome
{
    namespace levoit_vital
    {
        class LevoitVital; // forward declaration

        class LevoitFan : public fan::Fan, public Component
        {
        public:
            LevoitFan() = default;
            void setup() override;
            void dump_config() override;
            void set_parent(LevoitVital *parent) { parent_ = parent; }
            
            // Fan trait support
            fan::FanTraits get_traits() override;

        protected:
            void control(const fan::FanCall &call) override;
            LevoitVital *parent_;
        };

    } // namespace levoit_vital
} // namespace esphome
