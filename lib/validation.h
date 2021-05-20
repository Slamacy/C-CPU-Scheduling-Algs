#pragma once

// Validation fns & error handling fns declared here

// validate arguments from main
void validate_args(uint8_t argc);
uint32_t validate_arrival(int32_t arrival_t);
uint32_t validate_burst(int32_t burst_t);