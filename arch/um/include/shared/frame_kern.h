/* 
 * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)
 * Licensed under the GPL
 */

#ifndef __FRAME_KERN_H_
#define __FRAME_KERN_H_

<<<<<<< HEAD
extern int setup_signal_stack_sc(unsigned long stack_top, int sig,
				 struct k_sigaction *ka,
				 struct pt_regs *regs,
				 sigset_t *mask);
extern int setup_signal_stack_si(unsigned long stack_top, int sig,
				 struct k_sigaction *ka,
				 struct pt_regs *regs, struct siginfo *info,
=======
extern int setup_signal_stack_sc(unsigned long stack_top, int sig, 
				 struct k_sigaction *ka,
				 struct pt_regs *regs, 
				 sigset_t *mask);
extern int setup_signal_stack_si(unsigned long stack_top, int sig, 
				 struct k_sigaction *ka,
				 struct pt_regs *regs, siginfo_t *info, 
>>>>>>> b65c8e5645808384eb66dcfff9a96bad1918e30f
				 sigset_t *mask);

#endif

