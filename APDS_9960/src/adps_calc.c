#include <msp430.h>
#include "adps_calc.h"
#include <stdlib.h>

int gesture_ud_count_;
int gesture_lr_count_;
int gesture_ud_delta_ = 0;
int gesture_lr_delta_ = 0;


MOTION gesture_find(gesture_type *FIFO_mem)
{
    MOTION ret = none;
    uint8_t u_first = 0;
    uint8_t d_first = 0;
    uint8_t l_first = 0;
    uint8_t r_first = 0;
    uint8_t u_last = 0;
    uint8_t d_last = 0;
    uint8_t l_last = 0;
    uint8_t r_last = 0;
    int ud_ratio_first;
    int lr_ratio_first;
    int ud_ratio_last;
    int lr_ratio_last;
    int ud_delta;
    int lr_delta;

    int i;

    for (i = 0; i < 16; i++)
    {
        if ((FIFO_mem->up[i] > THRESHOLD) &&
            (FIFO_mem->down[i] > THRESHOLD) &&
            (FIFO_mem->left[i] > THRESHOLD) &&
            (FIFO_mem->right[i] > THRESHOLD))
        {

            u_first = FIFO_mem->up[i];
            d_first = FIFO_mem->down[i];
            l_first = FIFO_mem->left[i];
            r_first = FIFO_mem->right[i];
            break;
        }
    }

    /* If one of the _first values is 0, then there is no good data */
    if ((u_first == 0) || (d_first == 0) ||
        (l_first == 0) || (r_first == 0))
    {

        ret = none;
    }
    /* Find the last value in U/D/L/R above the threshold */
    for (i = 15; i >= 0; i--)
    {
        if ((FIFO_mem->up[i] > THRESHOLD) &&
            (FIFO_mem->down[i] > THRESHOLD) &&
            (FIFO_mem->left[i] > THRESHOLD) &&
            (FIFO_mem->right[i] > THRESHOLD))
        {

            u_last = FIFO_mem->up[i];
            d_last = FIFO_mem->down[i];
            l_last = FIFO_mem->left[i];
            r_last = FIFO_mem->right[i];
            break;
        }
    }


/* Calculate the first vs. last ratio of up/down and left/right */
ud_ratio_first = ((u_first - d_first) * 100) / (u_first + d_first);
lr_ratio_first = ((l_first - r_first) * 100) / (l_first + r_first);
ud_ratio_last = ((u_last - d_last) * 100) / (u_last + d_last);
lr_ratio_last = ((l_last - r_last) * 100) / (l_last + r_last);

/* Determine the difference between the first and last ratios */
ud_delta = ud_ratio_last - ud_ratio_first;
lr_delta = lr_ratio_last - lr_ratio_first;


/* Accumulate the UD and LR delta values */
gesture_ud_delta_ += ud_delta;
gesture_lr_delta_ += lr_delta;

/* Determine U/D gesture */
if (gesture_ud_delta_ >= GESTURE_SENSITIVITY_1)
{
    gesture_ud_count_ = 1;
}
else if (gesture_ud_delta_ <= -GESTURE_SENSITIVITY_1)
{
    gesture_ud_count_ = -1;
}
else
{
    gesture_ud_count_ = 0;
}

/* Determine L/R gesture */
if (gesture_lr_delta_ >= GESTURE_SENSITIVITY_1)
{
    gesture_lr_count_ = 1;
}
else if (gesture_lr_delta_ <= -GESTURE_SENSITIVITY_1)
{
    gesture_lr_count_ = -1;
}
else
{
    gesture_lr_count_ = 0;
}

ret = gesture_detection();

return ret;

}

MOTION gesture_detection(void)
{
    MOTION dir;
    /* Determine swipe direction */
    if ((gesture_ud_count_ == -1) && (gesture_lr_count_ == 0))
    {
        dir = motion_up;
    }
    else if ((gesture_ud_count_ == 1) && (gesture_lr_count_ == 0))
    {
        dir = motion_down;
    }
    else if ((gesture_ud_count_ == 0) && (gesture_lr_count_ == 1))
    {
        dir = motion_right;
    }
    else if ((gesture_ud_count_ == 0) && (gesture_lr_count_ == -1))
    {
        dir = motion_left;
    }
    else if ((gesture_ud_count_ == -1) && (gesture_lr_count_ == 1))
    {
        if (abs(gesture_ud_delta_) > abs(gesture_lr_delta_))
        {
            dir = motion_up;
        }
        else
        {
            dir = motion_right;
        }
    }
    else if ((gesture_ud_count_ == 1) && (gesture_lr_count_ == -1))
    {
        if (abs(gesture_ud_delta_) > abs(gesture_lr_delta_))
        {
            dir = motion_down;
        }
        else
        {
            dir = motion_left;
        }
    }
    else if ((gesture_ud_count_ == -1) && (gesture_lr_count_ == -1))
    {
        if (abs(gesture_ud_delta_) > abs(gesture_lr_delta_))
        {
            dir = motion_up;
        }
        else
        {
            dir = motion_left;
        }
    }
    else if ((gesture_ud_count_ == 1) && (gesture_lr_count_ == 1))
    {
        if (abs(gesture_ud_delta_) > abs(gesture_lr_delta_))
        {
            dir =  motion_down;
        }
        else
        {
            dir = motion_right;
        }
    }
    else
    {
        return none;
    }

    return dir;
}




