#pragma once
#include "esphome/core/component.h"
#include "esphome/components/select/select.h"
#include "../levoit_vital.h"
#include "../enums.h"

namespace esphome
{
    namespace levoit_vital
    {
        class LevoitSelect : public select::Select, public Component
        {
        public:
            LevoitSelect(LevoitVital *parent, LevoitSelectPurpose purpose) : parent_(parent), purpose_(purpose) {}
            void setup() override;
            void dump_config() override;
            void control(const std::string &value) override;

        protected:
            LevoitVital *parent_;
            LevoitSelectPurpose purpose_;
        };

    } // namespace levoit
} // namespace esphome
