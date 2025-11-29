import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.const import ICON_POWER, ICON_BRIGHTNESS_5, ICON_SECURITY, ICON_LIGHTBULB
from .. import LevoitVital, CONF_LEVOIT_ID, levoit_vital_ns

DEPENDENCIES = ["levoitvital"]


CONF_DEVICE_POWER = "device_power"
CONF_LIGHT_DETECT = "light_detect"
CONF_DISPLAY_LOCK = "display_lock"
CONF_DSIPLAY = "display"

LevoitSwitch = levoit_vital_ns.class_("LevoitSwitch", switch.Switch, cg.Component)
LevoitSwitchPurpose = levoit_vital_ns.enum("LevoitSwitchPurpose")


CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_LEVOIT_ID): cv.use_id(LevoitVital),
        cv.Optional(CONF_DEVICE_POWER): switch.switch_schema(
            LevoitSwitch, icon=ICON_POWER
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_LIGHT_DETECT): switch.switch_schema(
            LevoitSwitch, icon=ICON_BRIGHTNESS_5
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_DISPLAY_LOCK): switch.switch_schema(
            LevoitSwitch, icon=ICON_SECURITY
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_DSIPLAY): switch.switch_schema(
            LevoitSwitch, icon=ICON_LIGHTBULB
        ).extend(cv.COMPONENT_SCHEMA),
    }
)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_LEVOIT_ID])

    if config_device_power := config.get(CONF_DEVICE_POWER):
        var = await switch.new_switch(
            config_device_power, parent, LevoitSwitchPurpose.DEVICE_POWER
        )
        cg.add(parent.set_switch(var, LevoitSwitchPurpose.DEVICE_POWER))
        await cg.register_component(var, config_device_power)

    if config_light_detect := config.get(CONF_LIGHT_DETECT):
        var = await switch.new_switch(
            config_light_detect, parent, LevoitSwitchPurpose.LIGHT_DETECT
        )
        cg.add(parent.set_switch(var, LevoitSwitchPurpose.LIGHT_DETECT))
        await cg.register_component(var, config_device_power)

    if config_display_lock := config.get(CONF_DISPLAY_LOCK):
        var = await switch.new_switch(
            config_display_lock, parent, LevoitSwitchPurpose.DISPLAY_LOCK
        )
        cg.add(parent.set_switch(var, LevoitSwitchPurpose.DISPLAY_LOCK))
        await cg.register_component(var, config_display_lock)

    if config_display := config.get(CONF_DSIPLAY):
        var = await switch.new_switch(
            config_display, parent, LevoitSwitchPurpose.DISPLAY
        )
        cg.add(parent.set_switch(var, LevoitSwitchPurpose.DISPLAY))
        await cg.register_component(var, config_display)
