#ifndef UGO_LIB_PHASE
#define UGO_LIB_PHASE

#include <stm32l4xx_hal.h>

extern int sine1_idx;
extern int sine2_idx;
extern int sine3_idx;

extern int pwm_on;
extern int pwmn_on;

extern int pwm_on2;
extern int pwmn_on2;

extern int pwm_on3;
extern int pwmn_on3;

// Callback: timer has rolled over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // Check which version of the timer triggered this callback and toggle LED
  if (htim == &htim2)
  {
    sine1_idx++;
    sine2_idx++;
    sine3_idx++;

    if (sine1_idx > 319)
    {
      sine1_idx = 0;
      pwm_on = !pwm_on;
      pwmn_on = !pwmn_on;

      // Channel 1
      if (pwm_on)
      {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
      }
      else
      {
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
      }

      if (pwmn_on)
      {
        HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
      }
      else
      {
        HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
      }
    }
    TIM1->CCR1 = sine_vals[sine1_idx];

    if (sine2_idx > 319)
    {
      sine2_idx = 0;
      pwm_on2 = !pwm_on2;
      pwmn_on2 = !pwmn_on2;

      // Channel 2
      if (pwm_on2)
      {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
      }
      else
      {
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
      }

      if (pwmn_on2)
      {
        HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
      }
      else
      {
        HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
      }
    }
    TIM1->CCR2 = sine_vals[sine2_idx];

    if (sine3_idx > 319)
    {
      sine3_idx = 0;
      pwm_on3 = !pwm_on3;
      pwmn_on3 = !pwmn_on3;

      // Channel 3
      if (pwm_on3)
      {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
      }
      else
      {
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
      }

      if (pwmn_on3)
      {
        HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
      }
      else
      {
        HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
      }
    }
    TIM1->CCR3 = sine_vals[sine3_idx];
  }
}

#endif // UGO_LIB_PHASE
