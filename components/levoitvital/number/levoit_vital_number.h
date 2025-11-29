#pragma once
#include "esphome/core/component.h"
#include "esphome/components/number/number.h"
#include "../levoit_vital.h"
#include "../enums.h"

namespace esphome
{
    namespace levoit_vital
    {
        class LevoitNumber : public number::Number, public Component
        {
        public:
            LevoitNumber(LevoitVital *parent, LevoitNumberPurpose purpose) : parent_(parent), purpose_(purpose) {}
            void setup() override;
            void dump_config() override;
            void control(float value) override;

        protected:
            LevoitVital *parent_;
            LevoitNumberPurpose purpose_;
        };

    } // namespace levoit
} // namespace esphome
