#ifndef UTILS_H_
#define UTILS_H_

#define pin_on(port,pin_mask) do { (port) |= (pin_mask); } while (0);
#define pin_off(port,pin_mask) do { (port) &= ~(pin_mask); } while (0);
#define pin_set(port,pin_mask,on) do { if (on) { pin_on((port),(pin_mask)); } else { pin_off((port),(pin_mask)); } } while (0);
#define pin_check(port,pin_mask) (((port) & (pin_mask)) != 0)

#endif // UTILS_H_
